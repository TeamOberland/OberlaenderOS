/*
 * main_matthias.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */


//#include "kernel/generic/asm.h"
//#include "kernel/MMU/MMU.h"
#include "kernel/generic/kernel.h"

#include "kernel/generic/scheduler/scheduler.h"
#include <oos/scheduler.h>
#include <oos/video.h>
#include "kernel/generic/driver/driver.h"
#include "kernel/generic/driver/device_manager.h"
#include "kernel/generic/io/file.h"

#include "driver/gpio/gpio_driver.h"
#include "driver/video/video_driver.h"
#include <stdlib.h>
#include <string.h>

#include "tasks/task_blink.h"
#include "tasks/task_hello_world.h"

#include <oos/uart.h>
#include "driver/uart/uart_driver.h"
#include "kernel/generic/log/logger.h"
#include <oos/device.h>



//#define UART0       ((volatile unsigned int*)0x101f1000)
//#define UARTFR      0x06
//#define UARTFR_TXFF 0x20

//void bwputs(char *s){
/*while(*s){
 while(*(UART0 + UARTFR) & UARTFR_TXFF);
 *UART0 = *s;
 s++;
 }*/
//printf(&s);
//}
//void first(void){   //user programm
//  bwputs("I`m in user mode\n");
//  while(1);
//}
//MMU
/*typedef struct{
 unsigned int vAddress;
 unsigned int ptAddress;
 unsigned int masterPTAddress;
 unsigned int type;
 unsigned int domain;
 }Pagetable;

 #define FAULT 0
 #define COARSE 1
 #define MASTER 2
 #define FINE 3

 typedef struct{
 unsigned int vAddress;
 unsigned int pageSize;
 unsigned int numPages;
 unsigned int AP;
 unsigned int CB;
 unsigned int pAddress;
 Pagetable *PT;
 }Region;

 #define NANA 0x00
 #define RWNA 0x01
 #define RWRO 0x02
 #define RWRW 0x03
 */
/*NA = no access, RO = read only, RW = read write*/
/*#define cb 0x0  //not cached/ not buffered
 #define cB 0x1  //not cached/ Buffered
 #define WT 0x2  //write through cache
 #define WB 0x3  //write back cache


 void init_MMU(Region region){
 int i;
 unsigned int *pPTE, PTE;
 pPTE = (unsigned int *)region->PT->ptAddress;
 pPTE += region->vAddress>>20;
 pPTE +=region->numPages - 1;

 PTE = region->pAddress & 0xfff000000;
 PTE |= (region->AP & 0x3) << 10;
 PTE |= region->PT->domain << 5;
 PTE |= (region->CB & 0x3) << 2;
 PTE |= 0x12;

 for(i = region->numPages - 1; i <= 0; i--){
 *pPTE-- = PTE + (i<<20);    //i = 1MB section
 }
 }
 */
/*
 void controlSet(unsigned int value, unsigned int mask){
 unsigned int c1format;
 __asm{MRC p15,0,c1format,c1,c0,0};  //read control register
 c1format &= ~mask;                  //clear bits that change
 c1format |= value;                  //set bits that change
 __asm{MCR p15,0,c1format,c1,c0,0};  //write control register

 }
 */

#define SCREEN_WIDTH    1366
#define SCREEN_HEIGHT   768

typedef struct{
    uint32_t x;
    uint32_t y;
} mouse_position_t;


typedef struct
{
    int32_t x;
    int32_t y;
    int32_t mouse_event;

} mouse_input_t;

extern device_manager_t* global_device_manager;
device_handle_t mouse_input_handler;

mouse_position_t global_mouse_position;

bool_t mouse_click_fetched;

int32_t __check_mouse_border(int32_t value, int32_t maxValue)
{
    if(&value > maxValue)
    {
        return maxValue;
    }
    else if(&value < 0)
    {
        return 0;
    }
    return value;
}

void __mouse_position_calculation(mouse_input_t* input)
{
    int32_t newMousePositionX = global_mouse_position.x + input->x;
    int32_t newMousePositionY = global_mouse_position.y + input->y;

    // Check if over the boarders
    global_mouse_position.x = __check_mouse_border(newMousePositionX, SCREEN_WIDTH);
    global_mouse_position.y = __check_mouse_border(newMousePositionY, SCREEN_HEIGHT);

    if(input->mouse_event != 0)
    {
        mouse_click_fetched = TRUE;
    }
}

bool_t is_mouse_clicked()
{
    if(mouse_click_fetched)
    {
        mouse_click_fetched = FALSE;
        return TRUE;
    }
    return FALSE;
}


void init_mouse_handler(void)
{
    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, 3);
    mouse_input_handler = device_open(global_device_manager, uartDevice);
    device_ioctl(global_device_manager,mouse_input_handler,UART_DRIVER_INIT,(uint32_t)&uart_protocol_rs232);


    global_mouse_position.x = SCREEN_WIDTH / 2;
    global_mouse_position.y = SCREEN_HEIGHT / 2;

    mouse_click_fetched = FALSE;
}


void mouse_read_input(void)
{
    mouse_input_t mouseInput;
    mouseInput.mouse_event=0;
    mouseInput.x=0;
    mouseInput.y=0;

    device_read(global_device_manager, mouse_input_handler, &mouseInput, sizeof(mouse_input_t));


    __mouse_position_calculation(&mouseInput);
}
//
//void setup_device_manager()
//{
//    global_device_manager = device_manager_init();
//
//    // load drivers
//    device_manager_register_driver(global_device_manager, &gpio_driver);
//    device_manager_register_driver(global_device_manager, &uart_driver);
//    device_manager_register_driver(global_device_manager, &video_driver);
//}

void draw_tictactoe(void){
    uint32_t x = 10;
    uint32_t y = 10;
    uint32_t w = 600;
    uint32_t h = 600;
    color_t c;
    c.rgb = 0xFFF0F0FF;
    color_t c1;
    c1.rgb = 0x00000000;

    api_video_fill_rect(c1, 0, 0, 1366, 768, TRUE);
    api_video_fill_rect(c, x, y, w, h, TRUE);
    api_video_fill_line(c1,x + w / 3, y, x + w / 3, y + h, TRUE);
    api_video_fill_line(c1,x + w * 2 / 3, y, x + w * 2 / 3, y + h, TRUE);
    api_video_fill_line(c1,x, y + h / 3, x + w, y + h / 3, TRUE);
    api_video_fill_line(c1,x, y + h * 2 / 3, x + w, y + h * 2 / 3, TRUE);
}

void draw_tictactoe_field(uint8_t x, uint8_t y, bool_t player){
    color_t c;
    if(player == 1){
        c.rgb = 0xFF0000FF;
    }
    else{
        c.rgb = 0xFFFF00FF;
    }
    api_video_fill_rect(c, 10 + (x * 200) + 2, 10 + (y * 200) + 2, 196, 196, TRUE);
}

bool_t game_won(int *m){
    if(m[0] == m[1] && m[1] == m[2] && m[2] != 0){
        return TRUE;
    }
    if(m[3] == m[4] && m[4] == m[5] && m[5] != 0){
        return TRUE;
    }
    if(m[6] == m[7] && m[7] == m[8] && m[8] != 0){
        return TRUE;
    }
    if(m[0] == m[3] && m[3] == m[6] && m[6] != 0){
        return TRUE;
    }
    if(m[1] == m[4] && m[4] == m[7] && m[7] != 0){
        return TRUE;
    }
    if(m[2] == m[5] && m[5] == m[8] && m[8] != 0){
        return TRUE;
    }
    if(m[0] == m[4] && m[4] == m[8] && m[8] != 0){
        return TRUE;
    }
    if(m[6] == m[4] && m[4] == m[2] && m[2] != 0){
        return TRUE;
    }
    return FALSE;
}

bool_t game_finish(int *m){
    int i;
    for(i = 0; i < 9; i++){
        if(m[i] == 0){
            return FALSE;
        }
    }
    return TRUE;
}

//TestVariable
uint8_t test = 0;

void manuel_setup_device_manager()
{
    global_device_manager = device_manager_init();

    // load drivers
    device_manager_register_driver(global_device_manager, &gpio_driver);
    device_manager_register_driver(global_device_manager, &uart_driver);
}

void draw_current_tictactoe(int *m){
    draw_tictactoe();
    int i;
    for(i = 0; i < 9; i++){
        if(m[i] != 0){
            draw_tictactoe_field(i % 3, i / 3, m[i] - 1);
        }
    }
}

void draw_curser(uint32_t x, uint32_t y, int *m){
    draw_current_tictactoe(m);
    api_video_draw_raw_image( x, y, "/sd/arrow_cursor.raw", TRUE);
}

uint8_t get_field_from_uart(int* m){

    uint8_t retVal;
    while(TRUE){
        mouse_read_input();

        //Test
        int x = global_mouse_position.x;
        int y = global_mouse_position.y;
        bool_t mouseclick = is_mouse_clicked();
        draw_curser(x,y,m);

        if(mouseclick == TRUE){
            if(x >= 10 && x <= 610 && y >= 10 && y <= 610){
                retVal = ((y - 10) / 200) * 3 + (x - 10) / 200;
                return retVal;
            }
        }
    }


    /*while(TRUE)
    {
        device_read(global_device_manager,handle,buffer,messagelength);

        for (i = 0; i < messagelength; i++){
            message[i] = ((char*)buffer)[i];
        }
    }*/
}


char * getline(void) {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}
uint8_t get_from_console(bool_t player){
    int x = -1;
    int y = -1;

    while(x < 0 || x > 2 || y < 0 || y > 2){
        printf("Player %p: x = ", (player + 1));
        char *in;
        in = getline();
        char *end;
        strtol(in, &end, 10);
        if(end == in){
            x = -1;
            printf("Value has to be a INTEGER!\n");
        }
        else{
            x = atoi(in);

            printf("Player %p: y = ", (player + 1));
            in = getline();
            strtol(in, &end, 10);
            if(end == in){
                y = -1;
                printf("Value has to be a INTEGER!\n");
            }
            else{
                y = atoi(in);
                if(x < 0 || x > 2 || y < 0 || y > 2){
                    printf("Index out if range: x,y from 0 to 2! \n");
                }
            }

        }
    }

    uint8_t retVal = 0 + (y * 3) + x;
    return retVal;
}

void draw_won_player(bool_t player){
    color_t c;
    if(player == 1){
        c.rgb = 0xFF0000FF;
    }
    else{
        c.rgb = 0xFFFF00FF;
    }
    api_video_fill_rect(c, 0, 0, 1366, 768, TRUE);
    int i;
    for(i = 0; i < 4000000;i++);
}

void play_game(void){
    while(TRUE){
        draw_tictactoe();

        int m[]  = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        bool_t player = FALSE;
        bool_t won = FALSE;

        while ((won = game_won(&m)) == FALSE && game_finish(&m) == FALSE){
        //    uint8_t pos = get_field_from_uart(&m);
            uint8_t pos = get_from_console(player);
            uint8_t x = pos % 3;
            uint8_t y = pos / 3;
            if(m[pos] == 0){
                draw_tictactoe_field(x, y, player);
                m[pos] = player + 1;
                player = (player + 1) % 2;
            }
            else{
                printf("Field is already selected!\n");
            }


        }
        if(won == TRUE){
            draw_won_player((player + 1) % 2);
        }
    }
}

void main_matthias(void)
{
    printf("Setup kernel\n");
    setup_kernel();

    setup_device_manager();
    mount_init();

    __enable_interrupts();
    __switch_to_user_mode();

    init_mouse_handler();

    //manuel_setup_device_manager();

    play_game();
    /*int m[] = {0, 1, 2, 1, 1, 0, 2, 2, 0};
    draw_current_tictactoe(&m);

    int i;
    for(i = 5; i < 650; i+=4){
        draw_curser(i, 30, &m);
    }
*/
//    api_video_draw_raw_image( 0, 0, "/sd/Banner.raw", TRUE);

    /*draw_tictactoe();

    int p1[]  = {0, 0, 0, 1, 1, 1, 0, 0, 0};
    int p2[]  = {0, 0, 0, 1, 1, 1, 0, 0, 0};


    game_won(&p1);

    draw_tictactoe_field(1, 1, TRUE);
    draw_tictactoe_field(0, 1, FALSE);
    draw_tictactoe_field(0, 0, TRUE);
    draw_tictactoe_field(2, 2, FALSE);
    draw_tictactoe_field(1, 0, TRUE);
    draw_tictactoe_field(1,2, FALSE);
    draw_tictactoe_field(0, 2, TRUE);
    draw_tictactoe_field(2, 0, FALSE);*/

    //color_t c;
    //c.rgb = 0xFF0000FF;

    //api_video_fill_rect(c, 10, 10, 200, 200, TRUE);

    //printf("Test");
    //mmuInit();
    /*
     //Pagetables
     Pagetable masterPT = {0x00000000, 0x18000, 0x18000, MASTER, 3};
     Pagetable systemPT = {0x00000000, 0x1c000, 0x18000, COARSE, 3};
     Pagetable task1PT = {0x00400000, 0x1c400, 0x18000, COARSE, 3};
     Pagetable task2PT = {0x00400000, 0x1c800, 0x18000, COARSE, 3};
     Pagetable task3PT = {0x00400000, 0x1cc00, 0x18000, COARSE, 3};

     //Region Tables
     Region kernelRegion = {0x00000000, 4, 16, RWNA, WT, 0x00000000, &systemPT};
     Region sharedRegion = {0x00010000, 4, 8, RWRW, WT, 0x00010000, &systemPT};
     Region pageTableRegion = {0x00018000, 4, 8, RWNA, WT, 0x00018000, &systemPT};
     Region peripheralRegion = {0x10000000, 1024, 256, RWNA, cb, 0x10000000, &masterPT};

     init_MMU(kernelRegion);
     init_MMU(sharedRegion);
     init_MMU(pageTableRegion);
     init_MMU(peripheralRegion);

     //Set TTB
     asm("MCR p15,0,ttb,c2,c0,0");

     //Enabling MMU
     asm("MRC p15,0,r1,c1,c0,0");
     asm("ORR r1,r1,#0x1");
     asm("MCR p15,0,r1,c1,c0,0");


     */

    /*User Mode Cernel Mode
     unsigned int first_stack[256];
     unsigned int *first_stack_start = first_stack + 256 - 16;
     first_stack_start[0] = 0x10;
     printf("Erste\n");
     first_stack_start[1] = (unsigned int)&first;
     bwputs("Starting\n");
     printf("Zweite\n");
     activate(first_stack_start);
     printf("Dritte\n");
     while(1){
     printf("Das ist ein test2\n");
     }
     */
}

/*int copyThread(unsigned long clone_flags, unsigned long sp, unsigned long unused, struct task_struct *p, struct pt_regs *regs){
 struct pt_regs *childregs;


 childregs = task_pt_regs(p);
 *childregs = *regs;
 childregs->ax = 0;
 childregs->sp = sp;

 p->thread.sp = (unsigned long) childregs;
 p->thread.sp0 = (unsigned long) (childregs+1);
 p->thread.ip = (unsigned long) ret_from_fork;

 }*/

