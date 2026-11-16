#include "include_asm.h"
#include "names.h"

extern int g_color_timer_decrement __attribute__((sda));
extern int moby_decrement_top_byte(void *, int);
extern int FastDecTimer(void *);
extern void part_kill(void *);

/* Updates the colour of a particle and removes it when its timer runs out. */
void part_update_color_and_timer(char *object)
{
    moby_decrement_top_byte(object + 4, g_color_timer_decrement);
    if (FastDecTimer(object + 0xA))
        part_kill(object);
}
