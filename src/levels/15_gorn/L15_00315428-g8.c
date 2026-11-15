#include "include_asm.h"

#include "common.h"

/* Small-data unit: the bodies whose state lives at $gp-relative offsets. */

extern int D_L15_001B1530 __attribute__((sda));
extern int D_L15_001B1534 __attribute__((sda));
extern int D_L15_001B15C4 __attribute__((sda));

extern unsigned char D_L15_00221E10[];
extern unsigned char D_L15_0029FD80[];

extern int func_80381310(int a0);
extern void func_80380770(int a0, void *a1);
extern void func_80383FB8(void);
extern void func_803807B0(void);

/* Publishes the level's frame budget: seeds the counters and points the stage at
   the record the factory returned, then runs the three stage hooks. */
/* func_L15_0042FD40 is defined in L15_0042FD40-g8.c. */

extern int D_L15_001B1520 __attribute__((sda));
extern int D_L15_001B1524;
extern int D_L15_001B1528;
extern int D_L15_001B152C;
extern u8 D_L15_001395B8[];

/* Copies the four clamped channel bytes into the render block's colour slots. */

extern char *part_find_owned_effect_slot(char *a0, int a1, int a2);
extern void gfx_update_color_fade(char *a0, char *a1);
extern void gfx_start_color_fade(char *a0, char *a1);
extern int snd_play_from_class_bank(int index, int value, char *object, int kind);
/* The effect call is declared as returning int on purpose: its (unused) result
   stays in $v0, which is what keeps the $gp load below out of $v0. */
extern int part_spawn_shockwave_burst(void *a0, void *a1, int a2, int a3, int a4, int a5, int a6, int a7,
                             int a8, int a9, int a10, float f12);
extern void func_L05_00421908(char *a0, int a1, int a2);
extern int moby_is_in_use(char *a0);
extern void moby_release_from_group(char *a0);
extern void moby_reset_action_state(char *a0);

/* The moby's death timer: it ticks the stored time down and, once it reaches zero,
   fires the object's effect and takes the moby down, which it reports. */
int moby_l15_apply_hit_damage(char *obj, int flag)
{
    char *attachedPart;
    float *healthPtr;
    char *hitInfo;
    char *vars;
    short classId;
    int ret = 0;

    hitInfo = part_find_owned_effect_slot(obj, 0x230000, 0);
    *(unsigned char *)(obj + 0xA8) = 0xFF;
    vars = *(char **)(obj + 0x68);
    attachedPart = *(char **)(vars + 0x10);
    healthPtr = *(float **)(vars + 0x0);
    if (attachedPart != 0) {
        gfx_update_color_fade(obj, attachedPart);
    }
    if (hitInfo != 0) {
        if (attachedPart != 0) {
            *(unsigned char *)(attachedPart + 7) = 0xFF;
            gfx_start_color_fade(obj, attachedPart);
        }
        *healthPtr = *healthPtr - *(float *)(hitInfo + 0x2C);
        classId = *(short *)(obj + 0xAA);
        if (classId != 0xB73 /* moby class 2931 */) {
            if (classId == 0x1211 /* moby class 4625 */) {
                snd_play_from_class_bank(5, 0, obj, 0x1211);
            } else {
                snd_play_from_class_bank(0xD, 0, obj, 0xFBF);
            }
        }
        if (*healthPtr <= 0.0f) {
            *healthPtr = 0.0f;
            part_spawn_shockwave_burst(obj + 0x10, 0, 0x32, 0x1E, 0x1E, 0x1E, 0x28, 1, 1, 0, 0, 0.75f);
            if (D_L15_001B1520 == 0) {
                func_L05_00421908(obj, 1, 0xF);
            } else {
                func_L05_00421908(obj, 0, 0xF);
            }
            if (moby_is_in_use(obj)) {
                moby_release_from_group(obj);
            }
            if (flag == 0) {
                moby_reset_action_state(obj);
            }
            ret = 1;
        }
    }
    return ret;
}
