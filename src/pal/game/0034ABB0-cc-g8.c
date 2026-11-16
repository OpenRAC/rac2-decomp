#include "names.h"
/* func_PAL_0034ABB0, the PAL copy of func_003489E8: the same C, where rename func_002A9588 becomes func_PAL_002A9FA0. */

/* Menu list update: shows the widgets for the current mode, places the five fixed widgets and
   the list rows relative to the menu origin, greys out disabled rows, then steps the selection
   on up/down (wrapping at both ends, skipping disabled rows) and highlights it. Its own unit:
   - -G8 for the $gp-relative D_001AE5EC;
   - -frac2-hazard-labels: the branch out of the `if` arm lands on the hazard nop after the
     shared `mtc1` of the origin height, as in retail;
   - -frac2-gcse-unsplit-edges: with the low wrap through a pointer (WrapLow, as in
     func_00347F80), its branch only becomes a conditional move after the loop pass, which
     keeps retail's -1 inside the selection loop;
   - -fmove-all-movables: loop.c's pass 1 would otherwise leave the 0x80808080 constant of the
     row loop for the rerun pass, after the induction-variable inits.
   The four initialised locals (i, v, start, lim) bring the RTL to 284 insns, so gcse's PRE table
   has 143 buckets and numbers the E4 widget copy before the `pad & 0x1000` mask: the two spilled
   values then take retail's stack slots (4 and 8). The enabled flags are read through a struct
   pointer so that the index is added to its own base register (`addu base, index`). */

typedef unsigned char u8;
typedef struct { int enabled[7]; } EnabledSet; /* at menu + 0x418, one per list row */

extern float g_list_menu_value_float __attribute__((sda));
extern const float g_list_menu_positions[10] __attribute__((section(".sdata")));

extern void object_set_flag_value(void *, int);
extern void object_set_value_float(void *, float);
extern float *object_get_first_field(void *);
extern int *object_get_fourth_field(void *);
extern void object_set_second_float4(void *, float, float, float, float);
extern int math_ping_pong_blend_values_pal(int, int, int, int, int);
extern int snd_play_from_global_bank(int, int, void *);

static inline void WrapLow(int *index, int last)
{
    if (*index < 0)
        *index = last;
}

#define MODE (*(int *)(m + 0x4bc))
#define ORG (*(float **)(m + 0x4a4))

int UpdateMenuChoiceListWidgets_pal(u8 *m, int buttons)
{
    u8 *w98 = m + 0x98;
    u8 *w4C = m + 0x4C;
    u8 *w130 = m + 0x130;
    u8 *w17C = m + 0x17C;
    u8 *w1C8 = m + 0x1C8;
    u8 *widget_130, *widget_4c, *widget_98;
    float *pos;
    EnabledSet *enabled_flags;
    int step, i = 0, next_index = 0, original = 0, last = 0;

    object_set_flag_value(m, MODE == 0);
    object_set_flag_value(w98, MODE == 0);
    object_set_flag_value(w4C, MODE == 0);
    object_set_flag_value(m + 0xE4, MODE == 0);
    object_set_flag_value(w130, MODE == 0);
    object_set_flag_value(w17C, MODE == 1);
    object_set_flag_value(w1C8, MODE == 1);
    object_set_value_float(w17C, g_list_menu_value_float);
    object_set_value_float(w1C8, g_list_menu_value_float);

    if (MODE == 0 && *(int *)(m + 0x4b8) != 0) {
        object_set_value_float(m, 1.0f);
        object_set_value_float(m + 0x98, 1.0f);
        object_set_value_float(m + 0x4C, 1.0f);
        object_set_value_float(m + 0x130, 1.0f);
        widget_98 = m + 0x98;
        widget_4c = m + 0x4C;
        widget_130 = m + 0x130;
        ORG[1] = 170.0f;
    } else {
        object_set_value_float(m, 0.0f);
        object_set_value_float(m + 0x98, 0.0f);
        object_set_value_float(m + 0x4C, 0.0f);
        object_set_value_float(m + 0x130, 0.0f);
        widget_98 = m + 0x98;
        widget_4c = m + 0x4C;
        widget_130 = m + 0x130;
        ORG[1] = 190.0f;
    }

    pos = ((float *)object_get_first_field(m));
    pos[0] = g_list_menu_positions[0] + ORG[0];
    pos[1] = g_list_menu_positions[1] + ORG[1];
    pos = ((float *)object_get_first_field(widget_130));
    pos[0] = g_list_menu_positions[2] + ORG[0];
    pos[1] = g_list_menu_positions[3] + ORG[1];
    pos = ((float *)object_get_first_field(widget_4c));
    pos[0] = g_list_menu_positions[4] + ORG[0];
    pos[1] = g_list_menu_positions[5] + ORG[1];
    pos = ((float *)object_get_first_field(widget_98));
    pos[0] = g_list_menu_positions[6] + ORG[0];
    pos[1] = g_list_menu_positions[7] + ORG[1];
    pos = ((float *)object_get_first_field(m + 0xE4));
    pos[0] = g_list_menu_positions[8] + ORG[0];
    pos[1] = g_list_menu_positions[9] + ORG[1];

    for (i = 0; i < *(int *)(m + 0x4b4); i++) {
        u8 *row = m + 0x218 + i * 0x58;

        pos = ((float *)object_get_first_field(row));
        pos[0] = ((float *)(*(int *)(m + 0x484) + i * 12))[0] + ORG[0];
        pos[1] = ((float *)(*(int *)(m + 0x484) + i * 12))[1] + ORG[1];
        object_set_second_float4(row, ((float *)(*(int *)(m + 0x484) + i * 12))[2], 0.0f, 0.0f, 0.0f);
        if (*(int *)(m + 0x488 + i * 4) != 0)
            *((unsigned int *)object_get_fourth_field(row)) = 0x80F0F0F0;
        else
            *((unsigned int *)object_get_fourth_field(row)) = 0x80808080;
    }

    step = 0;
    if (buttons & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        step = -1;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        step = 1;
    }
    if (step != 0) {
        original = *(int *)(m + 0x4ac);
        math_ping_pong_blend_values_pal(0, 0, 1, 0, 1);
        last = *(int *)(m + 0x4b4) - 1;
        enabled_flags = (EnabledSet *)(m + 0x488);
        do {
            int wrapped;
            next_index = *(int *)(m + 0x4ac) + step;
            if (last < next_index)
                next_index = 0;
            wrapped = next_index;
            WrapLow(&wrapped, last);
            *(int *)(m + 0x4ac) = wrapped;
            if (enabled_flags->enabled[wrapped] != 0)
                break;
        } while (original != *(int *)(m + 0x4ac));
    }
    object_set_value_float(m + 0xE4, (float)*(int *)(m + 0x4ac));
    *((unsigned int *)object_get_fourth_field(m + (*(int *)(m + 0x4ac) * 0x58 + 0x218))) = 0x70FFFEED;
    return *(int *)(m + 0x4ac);
}
