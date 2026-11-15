#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int audio_menu_update(void *, int);

int func_US2_0029D7C8(int value) {
    if (D_001A8CFC != 0)
        return audio_menu_update(D_001A8CFC + 0x3DA78, value);
    return 0;
}

extern void audio_menu_draw(void *);

void func_US2_0029D808(void) {
    if (D_001A8CFC != 0)
        audio_menu_draw(D_001A8CFC + 0x3DA78);
}
