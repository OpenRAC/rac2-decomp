#include "include_asm.h"

#include "common.h"
extern float FastAddRotations(float a0, float a1);
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} Aimvec_F0b10;
extern Aimvec_F0b10 g_scalar_transition_state;
extern Aimvec_F0b10 g_scalar_transition_state;
extern void moby_mark_spawned(char *);
extern int IsPointInCuboid(void *, int);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern void func_L00_0036EF68(char *, int, int, int);
extern void ref_L00_003F3160_00(void *, void *);
extern void gfx_draw_lit_group_points(char *);
extern int g_tie_group_count __attribute__((sda));
extern unsigned short **g_level_reloc_record __attribute__((sda));
extern unsigned char *g_tie_table __attribute__((sda));
extern void moby_mark_spawned(char *a0);

/* A three-state object whose record (the pointer at +0x68) carries a group index at +0, two
   RGB triples and two RGBA quadruples as separate bytes, a packed colour at +0x10 and a few
   angle and flag words. State 0 arms it: an index outside the group table releases the object;
   otherwise the two angles are turned into radians, the byte triples are packed into the words
   at +0x14, +0x18, +0x30 and +0x34, and the object is handed to the binder with
   func_L00_003F3518 as its handler (state 2), or parked in state 1 when the word at +0x1C is set.
   State 1 steps the angle at +0xC and eases the colour at +0x10 towards one of the two packed
   colours; when it changed, its three bytes go to every entity of the group's id list. State 2
   re-binds the handler. The two stores of the byte at +0x30 sit in the arms of the select: the
   record's word at +0x68 either supplies its low byte or the object gets 0xFF. */
void color_l00_fade_update_pal(char *obj)
{
    unsigned char *vars = *(unsigned char **)(obj + 0x68);
    int group;
    int prev_color;
    int stamp;
    int word_a, word_b;
    int target;
    float angle;
    unsigned short *group_list;
    unsigned char *tie;
    int r, g, b;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        group = *(int *)vars;
        if (group >= g_tie_group_count || g_level_reloc_record[group] == 0 || group == -1) {
            moby_mark_spawned(obj);
            return;
        }
        *(float *)(vars + 8) = *(float *)(vars + 8) * 0.017453294f;
        *(float *)(vars + 4) = *(float *)(vars + 4) * 0.0003490659f;
        *(int *)(vars + 0x14) = vars[0x22] << 16 | vars[0x21] << 8 | vars[0x20];
        *(int *)(vars + 0x18) = vars[0x25] << 16 | vars[0x24] << 8 | vars[0x23];
        if (*(int *)(vars + 0x68) != 0) {
            stamp = vars[0x68];
            obj[0x30] = stamp;
        } else {
            stamp = 0xFF;
            obj[0x30] = stamp;
        }
        if (*(int *)(vars + 0x1C) != 0) {
            obj[0x20] = 1;
            return;
        }
        word_a = vars[0x29] << 24 | vars[0x28] << 16;
        word_a |= vars[0x27] << 8;
        word_a |= vars[0x26];
        *(int *)(vars + 0x30) = word_a;
        word_b = vars[0x2D] << 24 | vars[0x2C] << 16;
        word_b |= vars[0x2B] << 8;
        word_b |= vars[0x2A];
        *(int *)(vars + 0x34) = word_b;
        if (*(float *)(vars + 0x40) == 0.0f && *(float *)(vars + 0x44) == 0.0f &&
            *(float *)(vars + 0x48) == 0.0f)
            *(int *)(vars + 0x6C) = 1;
        ref_L00_003F3160_00((void *)gfx_draw_lit_group_points, obj);
        obj[0x20] = 2;
        return;
    case 1:
        if (*(int *)(vars + 0x64) != -1) {
            if (IsPointInCuboid(&g_scalar_transition_state.x_140, *(int *)(vars + 0x64)) == 0)
                return;
        }
        angle = FastAddRotations(*(float *)(vars + 0xC), *(float *)(vars + 4));
        prev_color = *(int *)(vars + 0x10);
        *(float *)(vars + 0xC) = angle;
        if (*(float *)(vars + 8) != 0.0f) {
            target = *(int *)(vars + 0x14);
            if (angle > *(float *)(vars + 8))
                target = *(int *)(vars + 0x18);
            *(int *)(vars + 0x10) = FastTweenColor(prev_color, target, 0.120000005f);
        } else {
            *(int *)(vars + 0x10) = FastTweenColor(*(int *)(vars + 0x14), *(int *)(vars + 0x18),
                                                math_fast_sin_or_cos_b(angle) * 0.5f + 0.5f);
        }
        if (*(int *)(vars + 0x10) == prev_color)
            return;
        group_list = g_level_reloc_record[*(int *)vars];
        r = *(int *)(vars + 0x10) & 0xFF;
        g = (*(int *)(vars + 0x10) >> 8) & 0xFF;
        b = (*(int *)(vars + 0x10) >> 16) & 0xFF;
        for (; group_list != 0 && ((short)group_list[-1] >= 0 || group_list == g_level_reloc_record[*(int *)vars]) &&
               (tie = g_tie_table + ((*group_list & 0x7FFF) << 5)) != 0;
             group_list++)
            func_L00_0036EF68((char *)tie, r, g, b);
        return;
    case 2:
        if (*(int *)(vars + 0x64) == -1 ||
            IsPointInCuboid(&g_scalar_transition_state.x_140, *(int *)(vars + 0x64)) != 0)
            ref_L00_003F3160_00((void *)gfx_draw_lit_group_points, obj);
        return;
    }
}

