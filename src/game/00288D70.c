#include "common.h"
#include "structs.h"

   /* current buffer */
extern short r1_D_0015EDC4;
extern void flag_set_word(void);
extern int g_flag_word __attribute__((sda));

/* Sets a flag word. */
void flag_set_word(void) {
    g_flag_word = 1;
}


/* Returns the flag word. */
int flag_get_word(void) {
    return g_flag_word;
}
