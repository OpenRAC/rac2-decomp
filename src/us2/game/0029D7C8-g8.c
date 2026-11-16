#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int audio_menu_update(void *, int);

int func_US2_0029D7C8(int value) {
    if (g_resident_data_base != 0)
        return audio_menu_update(g_resident_data_base + 0x3DA78, value);
    return 0;
}

extern void audio_menu_draw(void *);

void func_US2_0029D808(void) {
    if (g_resident_data_base != 0)
        audio_menu_draw(g_resident_data_base + 0x3DA78);
}
