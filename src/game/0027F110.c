#include "common.h"
#include "structs.h"

   /* current buffer */
extern short r1_D_0015EDC4;
extern void func_0027F110(void);
extern int D_001B1668 __attribute__((sda));

/* Sets the flag D_001B1668 to 1. */
void func_0027F110(void) {
    D_001B1668 = 1;
}


/* Clears the flag D_001B1668. */
void func_0027F120(void) {
    D_001B1668 = 0;
}
