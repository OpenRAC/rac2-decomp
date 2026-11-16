#include "include_asm.h"
#include "names.h"

typedef int Rac2TI128 __attribute__((mode(TI)));
extern void *CreateMoby(int id);
extern int part_alloc_effect_slot(void *a0, void *a1, float f12, float f13, float f14);
extern int part_l00_alloc_effect_slot_2(void *a0, float f12, float f13, float f14, float f15, float f16);
extern float math_random_angle(void);
extern void euler_rotation_basis(void *a0, void *a1);
extern unsigned int g_effect_moby_count __attribute__((sda));

/* Creates the level's own object, fills the header the object carries, copies the two
   16-byte records it is given into it, and lets the shared helpers set the rest up.
   The object is returned; a null one is returned unchanged. */
void *effect_spawn_moby_pal(char *owner, char *param, char *position, char *vector)
{
    char *new_moby;
    char *vars;
    char *position_ptr;
    unsigned short flags;

    new_moby = (char *)CreateMoby(0x9A9 /* moby class 2473 */);
    if (new_moby != 0) {
        flags = *(unsigned short *)(new_moby + 0x34);
        *(unsigned char *)(new_moby + 0x30) = 0xFF;
        *(unsigned short *)(new_moby + 0x32) = 0x1FF;
        *(unsigned short *)(new_moby + 0x34) = flags | 0x100;

        vars = *(char **)(new_moby + 0x68);
        position_ptr = new_moby + 0x10;
        *(int *)(vars + 0x44) = *(short *)(owner + 0xAA);
        *(int *)(vars + 0x34) = 0x64;
        *(float *)(vars + 0x4C) = 0.01f;
        *(int *)(vars + 0x40) = (int)param;

        *(Rac2TI128 *)position_ptr = *(Rac2TI128 *)position;
        *(Rac2TI128 *)vars = *(Rac2TI128 *)vector;
        *(Rac2TI128 *)(vars + 0x20) = *(Rac2TI128 *)vector;

        *(int *)(vars + 0x50) = part_alloc_effect_slot(new_moby, 0, 1.0f, 1.0f, 1.0f);
        *(int *)(vars + 0x54) = 0;
        *(int *)(vars + 0x58) = 0;
        *(unsigned char *)(new_moby + 0x20) = 0;
        g_effect_moby_count = g_effect_moby_count + 1;
        *(int *)(vars + 0x5C) = part_l00_alloc_effect_slot_2(position_ptr, 0.0f, 0.0f, 0.25f, 0.14f, 1.0f);
        *(float *)(new_moby + 0xF0) = math_random_angle();
        *(float *)(new_moby + 0xF4) = math_random_angle();
        *(float *)(new_moby + 0xF8) = math_random_angle();
        *(float *)(new_moby + 0xFC) = 0.0f;
        euler_rotation_basis(new_moby + 0xC0, new_moby + 0xF0);
    }
    return new_moby;
}
