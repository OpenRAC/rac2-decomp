#include "common.h"
#include "structs.h"

   /* current buffer */
extern short r1_D_0015EDC4;
extern void flag_set_word(void);
extern int D_001A7B8C __attribute__((sda));

/* Sets a flag word. */
void flag_set_word(void) {
    D_001A7B8C = 1;
}


/* Returns the flag word. */
int flag_get_word(void) {
    return D_001A7B8C;
}
