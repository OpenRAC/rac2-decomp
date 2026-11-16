#include "include_asm.h"

#include "common.h"
typedef struct { char pad[0x464]; unsigned char collected[0]; } ControllerLevelState;
extern ControllerLevelState g_controller_level_state;
extern unsigned char g_moby_nibble_table[];
extern int g_current_map_index __attribute__((sda));
extern int g_game_l00_mode __attribute__((sda));
extern unsigned char *g_moby_array_base __attribute__((sda));
extern char g_default_vector[] __attribute__((sda));
extern char g_str_aranos_debug_message[];
typedef struct { char pad[0x30]; int phase, frame; char pad2[0x15c]; int first, second; } Controller10;
extern Controller10 g_tutorial_probe_context;
extern void moby_mark_spawned(void *);
extern void enemy_spawn_child_parts(int, void *, int, int);
extern void enemy_attach_turn_child_parts_pal(int, float, void *, int, void *);
extern float FastAddRotations(float, float);
extern int PlayMobySound(int, int, void *);
extern void STUB_printf(void *);
typedef struct { char pad[0x20]; unsigned char state; char pad2[3]; char *classData; char pad3[0xC]; unsigned short flags; char pad4[0x62]; int field98; } ControllerMoby10;

void aranos_controller_update_pal(unsigned char *object)
{
    int *state = *(int **)(object + 0x68);
    unsigned char *counter;

    switch (object[0x20]) {
    case 0:
        state[9] = 0;
        state[10] = 0;
        state[12] = 0;
        state[13] = 0;
        object[0x30] = 255;
        object[0x20] = 1;
        if (!g_controller_level_state.collected[(short)*(unsigned short *)(object + 0xb2)]) {
            int n = g_moby_nibble_table[((short)*(unsigned short *)(object + 0xb2) >> 1) + (g_current_map_index << 10)];
            /* One 3-bit count per nibble; the low bit of the number picks the nibble. */
            if (!((*(unsigned short *)(object + 0xb2) & 1) ? (n >> 4) & 7 : n & 7)) {
                return;
            }
        }
        if (state[17] != -1) {
            moby_mark_spawned(g_moby_array_base + (state[17] << 8));
        }
        if (state[16] != -1) {
            moby_mark_spawned(g_moby_array_base + (state[16] << 8));
        }
        break;
    case 1:
        if (g_game_l00_mode != 2 && state[8] != -1) {
            ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (state[8] << 8));
            other->flags = (other->flags & 0xffbe) | 0x1000;
            other->field98 = *(int *)(other->classData + 0x10);
        }
        if (g_tutorial_probe_context.phase == 1 && g_game_l00_mode == 2) {
            if (g_tutorial_probe_context.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (state[8] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                if (state[17] != -1) {
                    moby_mark_spawned(g_moby_array_base + (state[17] << 8));
                }
                if (state[16] != -1) {
                    moby_mark_spawned(g_moby_array_base + (state[16] << 8));
                }
                if (*(unsigned short *)(object + 0xb2) & 1) {
                    counter = g_moby_nibble_table + (((short)*(unsigned short *)(object + 0xb2) >> 1) + (g_current_map_index << 10));
                    if (((*counter >> 4) & 7) != 7) {
                        *counter += 16;
                    }
                } else {
                    counter = g_moby_nibble_table + (((short)*(unsigned short *)(object + 0xb2) >> 1) + (g_current_map_index << 10));
                    if ((*counter & 7) != 7) {
                        ++*counter;
                    }
                }
                enemy_spawn_child_parts(g_tutorial_probe_context.first, state + 9, 0, 2);
            } else {
                int first = g_tutorial_probe_context.first;
                if (g_tutorial_probe_context.frame >= 1976) {
                    *(float *)(state + 11) = FastAddRotations(*(float *)(state + 11), 0.436332345f);
                    enemy_attach_turn_child_parts_pal(first, *(float *)(state + 11), state + 9, 1, g_default_vector);
                } else {
                    enemy_attach_turn_child_parts_pal(first, *(float *)(state + 11), state + 9, 0, g_default_vector);
                }
            }
            if (g_tutorial_probe_context.frame == 223) {
                int i;
                for (i = 0; i < 2; i++) {
                    ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (state[i] << 8));
                    if (other && other->state != 254 && other->state != 253) {
                        PlayMobySound(0, 0, other);
                        other->state = 1;
                    }
                }
            }
            if (g_tutorial_probe_context.frame == 226) {
                STUB_printf(g_str_aranos_debug_message);
            }
        }
        if (g_game_l00_mode != 2) {
            if (state[9]) {
                moby_mark_spawned((void *)state[9]);
                moby_mark_spawned((void *)state[10]);
                state[9] = 0;
                state[10] = 0;
            }
            if (state[12]) {
                moby_mark_spawned((void *)state[12]);
                moby_mark_spawned((void *)state[13]);
                state[12] = 0;
                state[13] = 0;
            }
        }
        if (g_tutorial_probe_context.phase == 2 && g_game_l00_mode == 2) {
            if (g_tutorial_probe_context.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (state[4] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                {
                    int i;
                    for (i = 0; i < 3; i++) {
                        ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (state[5 + i] << 8));
                        other->field98 = 0;
                        other->flags = (other->flags | 0x41) & 0xefff;
                    }
                }
                enemy_spawn_child_parts(g_tutorial_probe_context.first, state + 9, 0, 2);
                enemy_spawn_child_parts(g_tutorial_probe_context.second, state + 12, 0, 2);
            } else {
                int first = g_tutorial_probe_context.first, second = g_tutorial_probe_context.second;
                if (g_tutorial_probe_context.frame < 780) {
                    *(float *)(state + 11) = FastAddRotations(*(float *)(state + 11), 0.261799425f);
                    *(float *)(state + 14) = FastAddRotations(*(float *)(state + 14), 0.261799425f);
                    enemy_attach_turn_child_parts_pal(first, *(float *)(state + 11), state + 9, 1, g_default_vector);
                    enemy_attach_turn_child_parts_pal(second, *(float *)(state + 14), state + 12, 1, g_default_vector);
                } else {
                    *(float *)(state + 11) = FastAddRotations(*(float *)(state + 11), 0.087266475f);
                    *(float *)(state + 14) = FastAddRotations(*(float *)(state + 14), 0.087266475f);
                    enemy_attach_turn_child_parts_pal(first, *(float *)(state + 11), state + 9, 0, g_default_vector);
                    enemy_attach_turn_child_parts_pal(second, *(float *)(state + 14), state + 12, 0, g_default_vector);
                }
            }
        }
        break;
    }
}

