#include "include_asm.h"

#include "common.h"
extern s32  func_32AB10(char *a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern f32  math_random_signed_float_range(f32 a0, f32 a1);
extern f32  FastAddRotations(f32 a0, f32 a1);
extern char g_sound_l03_slot_table[];
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern u8  *g_moby_record_base;
extern f32  D_00189E20_19;
extern u8   g_clank_scene_done_flag;
extern u8   g_remote_view_done_flag;
extern u8   g_barlow_hint_inside_flag;
extern u8   g_unused_byte_c;
extern u8   g_unused_byte_a;
extern u8   g_unused_byte_d;
extern u8   g_unused_byte_b;
extern u8   g_unused_byte_e;
extern u8 *D_L03_001B2A1C_tbl[] __asm__("D_L03_001B2A1C") __attribute__((sda));

/* func_L03_003C8660 is matched in its own unit, src/levels/03_endako/L03_003C8660-qcopy.c (-frac2-qcopy). */

/* func_L03_003C8698 is defined in L03_003C8698.c. */

/* func_L03_003CA938 lives in the -G8 sibling L03_00399230-g8.c. */


/* func_L03_003CAD78 is defined in L03_003CAD78-g8.c. */

/* func_L03_003CB398 is defined in L03_003CB398-g8.c. */

/* func_L03_003CBC40 is defined in L03_003CBC40-g8.c. */

/* Picks the actor's next motion slot: case 0 draws a random turn rate, case 1
   re-checks the 0x70-stride table entry before refreshing the aim. */
void func_PAL_L03_003CFE58(char *a0)
{
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);

    switch (*(u8 *)(s0 + 0x20)) {
    case 0:
        moby_set_state(s0, 1, -1);
        *(f32 *)(s1 + 4) = math_random_signed_float_range(60.0f, 90.0f) * 0.0003490659f;
        *(s32 *)(s1 + 8) = -1;
        break;
    case 1: {
        s32 v = *(s32 *)s1;

        if (v != 0) {
            char *p = g_sound_l03_slot_table + *(s32 *)(s1 + 8) * 0x70;

            if (*(char **)(p + 0x88) != s0 || *(u8 *)(p + 0x74) == 0)
                *(s32 *)(s1 + 8) = PlayMobySound(0, 4, s0);
        }
        *(f32 *)(s0 + 0xF8) = FastAddRotations(*(f32 *)(s0 + 0xF8),
            *(f32 *)(s1 + 4));
        break;
    }
    }
}


