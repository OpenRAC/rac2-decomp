#include "include_asm.h"
#include "names.h"

/* The grouped quadword copy: the R5900 lq/sq pair with both addresses in registers. */
typedef int Rac2TI128 __attribute__((mode(TI)));

extern void *CreateMoby(int id);

extern int part_alloc_effect_slot(void *a0, void *a1, float f12, float f13, float f14);

extern int part_l00_alloc_effect_slot_2(void *a0, float f12, float f13, float f14, float f15, float f16);

extern float math_random_angle(void);

extern void euler_rotation_basis(void *a0, void *a1);

/* The counter the level keeps for these objects. The sda attribute and this unit's -G8
   make the reference to it $gp-relative, the way retail has it. */
extern unsigned int D_L00_001AFDA0 __attribute__((sda));

/* Creates the level's own object, fills the header the object carries, copies the two
   16-byte records it is given into it, and lets the shared helpers set the rest up.
   The object is returned; a null one is returned unchanged. */
void *effect_spawn_moby(char *owner, char *param, char *position, char *vector)
{
    char *newMoby;
    char *vars;
    char *posPtr;
    unsigned short flags;

    newMoby = (char *)CreateMoby(0x9A9 /* moby class 2473 */);
    if (newMoby != 0) {
        flags = *(unsigned short *)(newMoby + 0x34);
        *(unsigned char *)(newMoby + 0x30) = 0xFF;
        *(unsigned short *)(newMoby + 0x32) = 0x1FF;
        *(unsigned short *)(newMoby + 0x34) = flags | 0x100;

        vars = *(char **)(newMoby + 0x68);
        posPtr = newMoby + 0x10;
        *(int *)(vars + 0x44) = *(short *)(owner + 0xAA);
        *(int *)(vars + 0x34) = 0x78;
        *(float *)(vars + 0x4C) = 0.01f;
        *(int *)(vars + 0x40) = (int)param;

        *(Rac2TI128 *)posPtr = *(Rac2TI128 *)position;
        *(Rac2TI128 *)vars = *(Rac2TI128 *)vector;
        *(Rac2TI128 *)(vars + 0x20) = *(Rac2TI128 *)vector;

        *(int *)(vars + 0x50) = part_alloc_effect_slot(newMoby, 0, 1.0f, 1.0f, 1.0f);
        *(int *)(vars + 0x54) = 0;
        *(int *)(vars + 0x58) = 0;
        *(unsigned char *)(newMoby + 0x20) = 0;
        D_L00_001AFDA0 = D_L00_001AFDA0 + 1;
        *(int *)(vars + 0x5C) = part_l00_alloc_effect_slot_2(posPtr, 0.0f, 0.0f, 0.25f, 0.14f, 1.0f);
        *(float *)(newMoby + 0xF0) = math_random_angle();
        *(float *)(newMoby + 0xF4) = math_random_angle();
        *(float *)(newMoby + 0xF8) = math_random_angle();
        *(float *)(newMoby + 0xFC) = 0.0f;
        euler_rotation_basis(newMoby + 0xC0, newMoby + 0xF0);
    }
    return newMoby;
}
