#include "include_asm.h"
#include "names.h"
extern void moby_set_state(char *, int, int);
extern int D_L02_001CAA80[3];
extern int g_hovering_object_count;
extern int D_L02_001B41DC;
extern int g_frame_l02_counter;
extern int D_L02_001B0A60 __attribute__((sda));
extern float D_L02_001B0A20 __attribute__((sda));
extern float D_L02_001B0A28 __attribute__((sda));
extern float D_L02_001B0A30 __attribute__((sda));
extern void moby_set_state();
extern void *part_find_owned_effect_slot(void *, int, int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void DrawRotatingObjectGroupEffects();
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void part_spawn_scaled_bolts(void *, int, float);
extern void SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

/* One step of an actor, by its state byte (+0x20). State 0 marks the actor (+0x30), moves it to
   state 1 and lowers the counter D_L02_001AEC78 when its private word is set. Unless
   D_L02_001CAA80 is 1, state 1 registers the callback func_L02_003E80F8 once per value of
   D_L02_001B30C8 and, when func_002A9640 finds something and the private word is clear, lowers
   the counter and moves to state 2; it always ends by setting the byte at +0xA8. State 2 starts
   the effects and moves to state 3, which sets the half-word at +0x7C. */
void func_PAL_L02_003EC318(unsigned char *a0) {
    int state = a0[0x20];
    int *s = *(int **)(a0 + 0x68);

    switch (state) {
    case 0:
        a0[0x30] = 0xFF;
        moby_set_state(a0, 1, -1);
        if (*s != 0)
            g_hovering_object_count--;
        break;
    case 1:
        if (D_L02_001CAA80[0] != 1) {
            if (D_L02_001B41DC != g_frame_l02_counter) {
                D_L02_001B41DC = g_frame_l02_counter;
                gfx_add_draw_callback_first(DrawRotatingObjectGroupEffects, a0);
            }
            if (part_find_owned_effect_slot(a0, 0x4010000, 0) != 0 && *s == 0) {
                g_hovering_object_count--;
                moby_set_state(a0, 2, -1);
            }
            a0[0xA8] = 0xFF;
        }
        break;
    case 2:
        part_explode_object_into_pieces(a0, &D_L02_001B0A30, &D_L02_001B0A28, &D_L02_001B0A20, 0xFFFF, 0,
                          D_L02_001B0A60, 1, 0xFFFF, 0xFF, 0);
        part_spawn_scaled_bolts(a0, 5, 0.5f);
        SpawnExplosion(a0 + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        moby_set_state(a0, 3, -1);
        break;
    case 3:
        *(unsigned short *)(a0 + 0x7C) = 0x8020;
        break;
    }
}
