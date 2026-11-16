#include "include_asm.h"
#include "common.h"

extern char *g_effect_object __attribute__((sda));
extern void moby_init_with_private_data(char *, int);
extern void anim_start_immediate(char *, int, int);
extern void func_002A0F48(char *);

/* Sets up the shared effect object with default size and position data and starts the chosen variant. */
char *part_init_shared_effect_object(int mode, int variant)
{
    char *object;
    object = g_effect_object;
    moby_init_with_private_data(object, mode);
    *(unsigned short *)(object + 0x34) &= 0xFFBC;
    *(unsigned char *)(object + 0x30) = 0xFF;
    *(short *)(object + 0x32) = 0x20;
    *(unsigned char *)(object + 0x31) = 1;
    *(float *)(object + 0x10) = 5.0f;
    *(float *)(object + 0x14) = 5.0f;
    *(float *)(object + 0x18) = 900.0f;
    *(float *)(object + 0x1C) = 1.0f;
    qzero(object + 0xF0);
    if (variant >= 0) {
        anim_start_immediate(object, variant, 0);
    } else {
        char *object_class = *(char **)(object + 0x24);
        if (object_class != 0 && *(unsigned char *)(object_class + 0xC) >= 2)
            anim_start_immediate(object, 1, 0);
    }
    if ((*(unsigned short *)(object + 0x34) & 4) == 0)
        func_002A0F48(object);
    return object;
}
