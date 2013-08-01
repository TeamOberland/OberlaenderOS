/*
 * main.c
 */

#include <oos/types.h>
#include <oos/device.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

device_handle_t out;

void task_print(char* message);
void task_println(char* message);
void task_printf(char* message, ...);
char** task_split_cmd(char* cmd, uint32_t length, uint32_t* argc);
void task_newline(void);
char* task_readline(uint32_t* length);

#define TASK_CMD_MAXLENGTH 40
void task_printf(char* message, ...)
{
    char c[TASK_CMD_MAXLENGTH];
    memset(c, 0, TASK_CMD_MAXLENGTH);
    va_list args;
    va_start(args, message);
    vsprintf(c, message, args);
    va_end(args);

    task_print(c);
}

void task_print(char* message)
{
    api_device_write(out, message, strlen(message) + 1);
}

void task_newline()
{
    api_device_write(out, "\n", 3);
}

void task_println(char* message)
{
    task_print(message);
    task_newline();
}

#define TASK_CMD_MAXPARTS 5
char** task_split_cmd(char* cmd, uint32_t length, uint32_t* argc)
{
    char** argv = malloc(TASK_CMD_MAXPARTS * sizeof(char*));

    uint32_t i, j = 0, argStart, argEnd, argLength;
    char* arg;
    bool_t inQuote = FALSE;
    *argc = 0;

    argStart = 0;
    argEnd = 0;
    bool_t argFinished = FALSE;

    for (i = 0; i < length; i++)
    {
        if (cmd[i] == '"') // handle quotes
        {
            inQuote = !inQuote;

            if (inQuote)
            {
                argStart = i + 1;
                argEnd = argStart - 1;
                argFinished = TRUE;
            }
            else
            {
                argEnd = i - 1;
            }
        }
        else if (cmd[i] == ' ' && !inQuote) // a space ouside quotes
        {
            argEnd = i - 1;
            argFinished = TRUE;
        }
        else // include other chars in arg
        {
            argFinished = FALSE;
            argEnd++;
        }

        if (argFinished)
        {
            argLength = argEnd - argStart + 1;
            arg = malloc(sizeof(char) * (argLength + 1));
            memcpy(arg, cmd + argStart, argLength);
            cmd[argLength] = '\0';
            argFinished = FALSE;
            argv[j] = arg;
            j++;
            *argc += 1;
            argStart = i + 1;
        }
    }

    return argv;
}

char* task_readline(uint32_t* length)
{
    char* line = malloc(TASK_CMD_MAXLENGTH);
    memset(line, 0, TASK_CMD_MAXLENGTH);

    char c = 0;
    uint32_t i, j = 0;
    uint32_t nl = 0;
    for (i = 0; i < TASK_CMD_MAXLENGTH; i++)
    {
        api_device_read(out, &c, 1);

        if (c == '\n')
        {
            nl++;
            if (nl == 2)
                break;
        }
        else
        {
            line[j] = c;
            j++;
        }
    }

    *length = j;

    return line;
}

bool_t task_init(void)
{
    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, 3);
    out = api_device_open(uartDevice);
    if (!out)
    {
        return FALSE;
    }
    return TRUE;
}

void main(void)
{
    char* line = NULL;
    uint32_t lineLength = 0;

    char** argv = NULL;
    uint32_t argc = 0;

    uint32_t i;

    if (task_init())
    {
        task_println("Welcome To OberlaenderOS!");

        while (TRUE)
        {
            task_print("root@oos> ");

            // read user input
            line = task_readline(&lineLength);

            // parse into argc/argv
            argv = task_split_cmd(line, lineLength, &argc);
            free(line);

            // print the user input
            task_printf("argc: %i \n", argc);
            task_println("argv");
            for (i = 0; i < argc; i++)
            {
                task_printf("%i) %s\n", argv[i]);
            }
        }
    }
}
