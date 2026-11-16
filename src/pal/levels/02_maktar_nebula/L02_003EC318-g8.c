#include "include_asm.h"
#include "names.h"
extern void moby_set_state(char *, int, int);
extern int g_arena_l02_active_flag[3];
extern int g_hovering_object_count;
extern int g_effect_spawner_last_frame;
extern int g_frame_l02_counter;
extern int g_spawner_explode_param __attribute__((sda));
extern float g_piece_explode_param_c __attribute__((sda));
extern float g_piece_explode_param_b __attribute__((sda));
extern float g_piece_explode_param_a __attribute__((sda));
extern void moby_set_state();
extern void *part_find_owned_effect_slot(void *, int, int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void DrawRotatingObjectGroupEffects();
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void part_spawn_scaled_bolts(void *, int, float);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

/* One step of an actor, by its state byte (+0x20). State 0 marks the actor (+0x30), moves it to
   state 1 and lowers the counter D_L02_001AEC78 when its private word is set. Unless
   D_L02_001CAA80 is 1, state 1 registers the callback func_L02_003E80F8 once per value of
   D_L02_001B30C8 and, when func_002A9640 finds something and the private word is clear, lowers
   the counter and moves to state 2; it always ends by setting the byte at +0xA8. State 2 starts
   the effects and moves to state 3, which sets the half-word at +0x7C. */
void effect_l02_spawner_update_pal(unsigned char *moby) {
    int state = moby[0x20];
    int *vars = *(int **)(moby + 0x68);

    switch (state) {
    case 0:
        moby[0x30] = 0xFF;
        moby_set_state(moby, 1, -1);
        if (*vars != 0)
            g_hovering_object_count--;
        break;
    case 1:
        if (g_arena_l02_active_flag[0] != 1) {
            if (g_effect_spawner_last_frame != g_frame_l02_counter) {
                g_effect_spawner_last_frame = g_frame_l02_counter;
                gfx_add_draw_callback_first(DrawRotatingObjectGroupEffects, moby);
            }
            if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0 && *vars == 0) {
                g_hovering_object_count--;
                moby_set_state(moby, 2, -1);
            }
            moby[0xA8] = 0xFF;
        }
        break;
    case 2:
        part_explode_object_into_pieces(moby, &g_piece_explode_param_a, &g_piece_explode_param_b, &g_piece_explode_param_c, 0xFFFF, 0,
                          g_spawner_explode_param, 1, 0xFFFF, 0xFF, 0);
        part_spawn_scaled_bolts(moby, 5, 0.5f);
        SpawnExplosion(moby + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        moby_set_state(moby, 3, -1);
        break;
    case 3:
        *(unsigned short *)(moby + 0x7C) = 0x8020;
        break;
    }
}
