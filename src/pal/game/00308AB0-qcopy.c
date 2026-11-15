#include "include_asm.h"

#include "common.h"
typedef float V4_F307808[4] __attribute__((aligned(16)));
extern u8 g_item_slot_to_record[];
extern char g_weapon_table[];
extern s32 D_001AEC68 __attribute__((sda));
extern void moby_transform_joint_to_world(char *, s32, void *);
extern void moby_get_facing_direction(char *, void *);
extern char *moby_get_private_value_0(char *);
extern void FastVecScale(void *, char *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern s32 snd_play_from_class_bank(s32, s32, char *, s32);
extern char *func_PAL_0031E9F8(void *, void *, float, float, float, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned short, void *);
#define ENTRY() (D_00239BA0 + D_00139568[0x29] * 0xE0)

/* One step of an object's launch routine: fires the pending shot and counts it down. */
void func_PAL_00308AB0(char *obj)
{
    V4_F307808 a, b, c, d, e;
    char *rec = *(char **)(obj + 0x68);
    char *link;
    char *tgt;
    float scale;
    char *ent;
    char *fx;

    moby_transform_joint_to_world(obj, 1, d);
    moby_get_facing_direction(obj + 0x10, a);
    if (*(float *)(rec + 0x5C) == 0.0f) {
        if (*(s32 *)(rec + 0x50) != 0) {
            if (*(char **)(rec + 0x64) != 0) {
                link = moby_get_private_value_0(*(char **)(rec + 0x64));
                tgt = *(char **)(rec + 0x64);
                qcopy(b, tgt + 0x10);
                if (link != 0) {
                    FastVecScale(e, tgt + 0xE0, *(float *)(link + 0x10));
                    FastVecAdd(b, b, e);
                }
                ent = ENTRY();
                scale = *(float *)(ent + 0x50) * 0.020000001f;
                FastVecSub(c, b, d);
                vec_scale_to_length(c, c, scale);
                snd_play_from_class_bank(0, 0, obj, 0x1367);
                fx = func_PAL_0031E9F8(d, c, 2.0f, 15.0f, 0.5f, 3.0f, 0x50, 0xC8, 1, 0, 0x10E, *(char **)(rec + 0x64));
                if (fx != 0)
                    *(s32 *)(fx + 0xB8) = *(s32 *)(rec + 0x68);
                *(s32 *)(rec + 0x40) = ((s32)(D_001AEC68) * 5 + 2) / 6;
                *(s32 *)(rec + 0x44) = 5;
                if (--*(s32 *)(rec + 0x60) <= 0)
                    *(u8 *)(obj + 0x20) = 8;
                *(float *)(rec + 0x5C) = 0.6666667f;
            }
        }
    }
}
