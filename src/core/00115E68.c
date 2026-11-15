#include "common.h"

/* $ra is saved in a TImode slot (`sq $ra,0($sp)`), so this unit is built with
   the -mastra-quad-saves profile. The 64-bit result comes back truncated to
   the 32-bit return type, which is retail's dsll32/dsra32 pair. */
extern long strtol(int arg0, int arg1, int arg2);

/* Turns a text string of digits into a whole number. */
int atoi(int text) {
    return (int)strtol(text, 0, 10);
}
