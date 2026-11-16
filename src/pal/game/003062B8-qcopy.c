#include "include_asm.h"

#include "common.h"
typedef float V4_F305058[4] __attribute__((aligned(16)));
extern u8 g_item_slot_to_record[];
extern char g_weapon_table[];
extern s32 g_miniturret_shot_param __attribute__((sda));
extern void moby_transform_joint_to_world(char *, s32, void *);
extern void moby_get_facing_direction(char *, void *);
extern char *moby_get_private_value_0(char *);
extern void FastVecScale(void *, char *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_add_transformed_or_copy(void *, void *, void *);
extern void part_add_trail_entry_pal(char *, void *);
extern s32 PlayMobySound(s32, s32, char *);
#define ENTRY() (D_00239BA0 + D_00139568[0x29] * 0xE0)

/* One step of an object's launch routine: aims the pending hit and counts it down. */
void func_PAL_003062B8(char *obj)
{
    V4_F305058 a, b, c, d, e;
    char *rec = *(char **)(obj + 0x68);
    char *link;
    char *tgt;
    float scale;
    char *ent;

    moby_transform_joint_to_world(obj, 1, d);
    moby_get_facing_direction(obj + 0x10, a);
    if (*(float *)(rec + 0x5C) == 0.0f) {
        if (*(s32 *)(rec + 0x50) != 0) {
            if (*(char **)(rec + 0x68) != 0) {
                link = moby_get_private_value_0(*(char **)(rec + 0x68));
                tgt = *(char **)(rec + 0x68);
                qcopy(b, tgt + 0x10);
                if (link != 0) {
                    FastVecScale(e, tgt + 0xE0, *(float *)(link + 0x10));
                    FastVecAdd(b, b, e);
                }
                ent = ENTRY();
                scale = *(float *)(ent + 0x50) * 0.020000001f;
                FastVecSub(c, b, d);
                vec_scale_to_length(c, c, scale);
                vec_add_transformed_or_copy(c, c, d);
                part_add_trail_entry_pal(obj, c);
                PlayMobySound(0, 0, obj);
                *(s32 *)(rec + 0x40) = ((s32)(g_miniturret_shot_param) * 5 + 2) / 6;
                *(s32 *)(rec + 0x44) = 5;
                if (--*(s32 *)(rec + 0x60) <= 0)
                    *(u8 *)(obj + 0x20) = 8;
                ent = ENTRY();
                *(float *)(rec + 0x5C) = 1.0f / *(float *)(ent + 0x54);
            }
        }
    }
}
