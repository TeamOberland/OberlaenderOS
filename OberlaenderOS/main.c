/*
 * main.c
 */

#if defined(Daniel)
#define ENTRY_POINT main_daniel
#elif defined(Manuel)
#define ENTRY_POINT main_manuel
#elif defined(Martin)
#define ENTRY_POINT main_martin
#elif defined(Matthias)
#define ENTRY_POINT main_matthias
#endif

extern void ENTRY_POINT(void);

void main(void) {
    ENTRY_POINT();
}
