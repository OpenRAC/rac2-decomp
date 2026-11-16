#include "include_asm.h"
#include "common.h"

extern int math_fast_float_d(int *);
extern int math_random_int_range(int, int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
/* EE integer and floating-point argument banks retain their independent order. */
extern void *aranos_spark_spawn(void *, void *, int, float, int, int);



extern void gfx_init_large_sprite_packet_b(char *);
extern long long GetEffectTextureDescriptor(int);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern float math_random_angle(void);
extern void euler_to_matrix(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void draw_world_quad(void *, void *, int);
typedef struct { char pad[0x140]; float x,y,z; } AimVector10;
extern AimVector10 g_scalar_transition_state;
/* Draws a two-layer glowing sprite stretched between a point and the hero, used for the tutorial aim marker. */
void tutorial_draw_aim_marker_sprite(int unused, char *pos, int color, int first, int second, float scale)
{
    char sprite[144];
    float matrix[16];
    float rotation[4];
    float mid_offset[4];
    long long texture;
    float dx, dy;

    gfx_init_large_sprite_packet_b(sprite);
    *(int *)(sprite + 80) = 0;
    *(float *)(sprite + 92) = 1.0f;
    *(float *)(sprite + 96) = 1.0f;
    *(float *)(sprite + 104) = 1.0f;
    *(float *)(sprite + 108) = 1.0f;
    *(int *)(sprite + 84) = 0;
    *(int *)(sprite + 88) = 0;
    *(int *)(sprite + 100) = 0;
    texture = GetEffectTextureDescriptor(11);
    *(long long *)(sprite + 112) = 0;
    *(long long *)(sprite + 120) = texture;
    *(long long *)(sprite + 128) = 0xFF9000000260LL;
    *(long long *)(sprite + 136) = 0x8000000048LL;
    dx = g_scalar_transition_state.x - *(float *)pos;
    dy = g_scalar_transition_state.y - *(float *)(pos + 4);
    *(int *)(sprite + 76) = color + first;
    *(int *)(sprite + 72) = color + first;
    *(int *)(sprite + 68) = color + first;
    *(int *)(sprite + 64) = color + first;
    rotation[3] = 0;
    rotation[2] = mat_fast_helper_a(dx, dy);
    rotation[1] = -mat_fast_helper_a(vec_distance_xy(pos, &g_scalar_transition_state.x),
                              g_scalar_transition_state.z - *(float *)(pos + 8));
    rotation[0] = math_random_angle();
    euler_to_matrix(matrix, rotation);
    FastVecSub(mid_offset, &g_scalar_transition_state.x, pos);
    vec_scale_to_length(mid_offset, mid_offset, 0.5f);
    matrix[12] = *(float *)(pos) + mid_offset[0];
    matrix[13] = *(float *)(pos + 4) + mid_offset[1];
    matrix[14] = *(float *)(pos + 8) + mid_offset[2];
    matrix[15] = 1.0f;
    FastVecScale(sprite, sprite, scale);
    FastVecScale(sprite + 16, sprite + 16, scale);
    FastVecScale(sprite + 32, sprite + 32, scale);
    FastVecScale(sprite + 48, sprite + 48, scale);
    draw_world_quad(sprite, matrix, 0);
    *(int *)(sprite + 76) = color + second;
    *(int *)(sprite + 72) = color + second;
    *(int *)(sprite + 68) = color + second;
    *(int *)(sprite + 64) = color + second;
    FastVecScale(sprite, sprite, 0.5f);
    FastVecScale(sprite + 16, sprite + 16, 0.5f);
    FastVecScale(sprite + 32, sprite + 32, 0.5f);
    FastVecScale(sprite + 48, sprite + 48, 0.5f);
    draw_world_quad(sprite, matrix, 0);
}



/* Tutorial prompts, interaction locks and traversal visibility. */
extern char g_hero_position[];
typedef struct { char pad[0x2290]; unsigned char *moby; char pad2[0x238]; int count; } TutorialPlayer;
extern TutorialPlayer g_hero_state;
extern unsigned short g_subtitle_history[];
extern unsigned short g_tutorial_flag_third[],g_tutorial_flag_first[],g_tutorial_flag_second[];
extern int g_player_stats __attribute__((sda)),g_menu_choice_table __attribute__((sda));
extern unsigned char *g_moby_l00_list_head __attribute__((sda));
typedef struct {int active;char pad[0x20];int id;} TutorialPromptState;
extern TutorialPromptState g_tutorial_prompt_state;
extern float fast_vec_dist(void *,void *);
extern int moby_is_state_one(void *);
extern int subtitle_request_voice_line(int,int);
extern int IsPointInCuboid(void *,int);
extern int moby_count_group_not_in_state(int,int), flag_is_byte_set(void);
extern char *GetLocalizedString(int);
extern void settings_store_four(int,int,int,int), menu_set_size_limits(int,int);
extern int request_begin_slot(int,int,int,int,int);
/* Shows tutorial help prompts when the hero reaches the matching trigger area, and locks interaction while a prompt is up. */
void tutorial_prompt_trigger_update(unsigned char *object) {
    int *zones=*(int **)(object+0x68);
    unsigned char *nearby;
    switch(object[0x20]) {
    case 0:
        object[0x30]=255; object[0x20]=1; break;
    case 1:
        if(!g_subtitle_history[0x48/2]) {
            for(nearby=g_moby_l00_list_head;nearby;nearby=*(unsigned char **)(nearby+0x28)) {
                if(*(short *)(nearby+0xaa)==0x326 && fast_vec_dist(nearby+0x10,g_hero_position)<10.0f && !g_tutorial_prompt_state.active && g_tutorial_prompt_state.id==-1 && !g_subtitle_history[0x48/2] && !moby_is_state_one(nearby)) {
                    if(g_hero_state.count<g_player_stats) subtitle_request_voice_line(0x9af,6);
                    else if(fast_vec_dist(nearby+0x10,g_hero_position)<1.0f && !g_subtitle_history[0x2e8/2]) subtitle_request_voice_line(0x9e7,0x3e);
                }
            }
        }
        if(IsPointInCuboid(g_hero_position,zones[0]) && !g_tutorial_prompt_state.active && g_tutorial_prompt_state.id==-1 && !g_subtitle_history[0x18/2]) subtitle_request_voice_line(0x9ab,2);
        if(IsPointInCuboid(g_hero_position,zones[1]) && !g_tutorial_prompt_state.active && g_tutorial_prompt_state.id==-1 && !g_subtitle_history[0x24/2] && !g_subtitle_history[0x30/2]) {
            if(g_menu_choice_table==30) subtitle_request_voice_line(0x9ac,3);
            else if(g_menu_choice_table==42) subtitle_request_voice_line(0x9ad,4);
        }
        if(IsPointInCuboid(g_hero_position,zones[3]) && !g_tutorial_prompt_state.active && g_tutorial_prompt_state.id==-1 && !g_subtitle_history[0x54/2] && !g_subtitle_history[0x60/2] && !g_subtitle_history[0x6c/2] && moby_count_group_not_in_state(zones[5],-1)) {
            if(g_menu_choice_table==42) subtitle_request_voice_line(0x9b0,7);
            else if(g_tutorial_flag_third[0]) subtitle_request_voice_line(0x9b1,8);
            else subtitle_request_voice_line(0x9b2,9);
        }
        if(IsPointInCuboid(g_hero_position,zones[2]) && !g_tutorial_prompt_state.active && g_tutorial_prompt_state.id==-1) {
            if(flag_is_byte_set() && !g_subtitle_history[0x5a0/2]) {
                int first,second;
                g_subtitle_history[0x5a0/2]=1;
                first=GetLocalizedString(0x112b);second=GetLocalizedString(0xa21);
                settings_store_four(first,0,second,1);menu_set_size_limits(0x40,0);request_begin_slot(4,1,10,0,0);
            } else if(!flag_is_byte_set() && !g_subtitle_history[0x3c/2] && !g_tutorial_flag_first[0]) subtitle_request_voice_line(0x9ae,5);
        }
        if(IsPointInCuboid(g_hero_position,zones[4]) && !g_tutorial_flag_second[0] && !g_tutorial_prompt_state.active && g_tutorial_prompt_state.id==-1 && !g_subtitle_history[0x78/2]) subtitle_request_voice_line(0x9b3,10);
        break;
    }
    g_hero_state.moby[0x7e]|=1;
    { unsigned char *scan_moby; for(scan_moby=g_moby_l00_list_head;scan_moby;scan_moby=*(unsigned char **)(scan_moby+0x28)) if(*(short *)(scan_moby+0xaa)==0xac1) scan_moby[0x7e]|=1; }
    if(IsPointInCuboid(g_hero_position,zones[6]) || IsPointInCuboid(g_hero_position,zones[7])) g_hero_position[0x2470]=1;
    else g_hero_position[0x2470]=0;
}

/* Emits bursts of small particles from the object, waiting a random time between bursts. */
void particle_burst_emitter_update(unsigned char *moby) {
    float velocity[4], pos[4];
    float first_size, secondRadius, z;
    int *vars = *(int **)(moby + 0x68);
    unsigned char *origin;

    if (moby[0x20] == 0) {
        moby[0x30] = 0x80;
        moby[0x20] = 1;
        vars[1] = 20;
        vars[0] = 0;
    }
    if (moby[0x20] == 1) {
        if (math_fast_float_d(vars)) {
            moby[0x20] = 2;
            vars[0] = math_random_int_range(50, 120);
        }
    }
    if (moby[0x20] == 2) {
        if (math_fast_float_d(vars + 1)) {
            moby[0x20] = 1;
            vars[1] = math_random_int_range(10, 25);
        } else {
            velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xf8) - 1.570796489715576171875f)
                   * 0.416666686534881591797f;
            velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xf8) - 1.570796489715576171875f)
                   * 0.416666686534881591797f;
            velocity[2] = 0.0f;
            origin = moby + 0x10;
            qcopy(pos, origin);
            z = velocity[2];
            pos[2] += math_random_signed_float_range(z, 0.5f);
            first_size = math_random_float_range(0.1f, 3.0f);
            aranos_spark_spawn(pos, velocity, 300, first_size,
                             FloatToInt(math_random_signed_float_range(1.0f, 4.0f)), 0x40808080);
            qcopy(pos, origin);
            pos[2] += math_random_signed_float_range(z, 0.5f);
            secondRadius = math_random_float_range(0.1f, 3.0f);
            aranos_spark_spawn(pos, velocity, 300, secondRadius,
                             FloatToInt(math_random_signed_float_range(1.0f, 4.0f)), 0x40808080);
        }
    }
}

extern int IsPointInCuboid(void *a0, int a1);
extern char g_hero_position[];
extern float g_hero_proximity_threshold __attribute__((sda));

/* Sets a global value to 30 when the hero is inside the area, otherwise to 95. */
void hero_proximity_value_update(void *moby) {
    int hero_inside = IsPointInCuboid(g_hero_position,
                               *(int *)*(int *)((char *)moby + 0x68));
    if (hero_inside != 0) {
        g_hero_proximity_threshold = 30.0f;
    } else {
        g_hero_proximity_threshold = 95.0f;
    }
}


extern int math_random_int_below(int);
/* EE integer and floating-point argument banks retain their independent order. */
extern unsigned char *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, float, int, int);
/* Spawns three particle bursts at the object. The second burst updates the first
 * particle's header, as retail does. */
/* Spawns three particle bursts at the object. */
void part_spawn_three_bursts(unsigned char *moby)
{
    float velocity[4], pos[4];
    float one = 1.0f;
    int spin;
    unsigned char *first, *second, *third;
    unsigned char *particle1, *particle2, *particle3;

    velocity[0] = 0.0f;
    velocity[1] = -0.5f;
    velocity[2] = 0.0f;
    velocity[3] = one;
    spin = math_random_int_below(16);
    if (math_random_int_below(2)) {
        spin = -spin;
    }
    qcopy(pos, moby + 0x10);
    first = SpawnSpinningSparkParticle(pos, 0.1f, 1.0f, 0.9f, spin, velocity, 630000.0f, 0xDF204080, 0);
    if (first) {
        particle1 = first + 0x20;
        *(unsigned short *)(first + 0xA) = 25;
        first[9] = FloatToInt(4.0f) + 112;
        *(int *)(particle1 + 4) = 2;
        particle1[0xA] = 0xDF;
        particle1[0xB] = first[0xA];
    }
    second = SpawnSpinningSparkParticle(pos, 0.1f, 1.0f, 0.9f, spin, velocity, 630000.0f, 0xDF204080, 0);
    if (second) {
        particle2 = second + 0x20;
        *(unsigned short *)(first + 0xA) = 25;
        first[9] = FloatToInt(4.0f) + 112;
        *(int *)(particle2 + 4) = 2;
        particle2[0xA] = 0xDF;
        particle2[0xB] = first[0xA];
    }
    third = SpawnSpinningSparkParticle(pos, 0.05f, 1.0f, 0.97f, 16, velocity, 315000.0f, 0xDFFFFFFF, 0);
    if (third) {
        int v;
        particle3 = third + 0x20;
        v = FloatToInt(4.0f);
        *(unsigned short *)(third + 0xA) = 35;
        third[9] = v + 112;
        third[8] = math_random_int_below(255);
        *(int *)(particle3 + 4) = 2;
        particle3[0xA] = 0xDF;
        particle3[0xB] = first[0xA];
    }
}


/* Aranos controller: initialize linked objects and drive the two scripted sequences. */
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
extern void enemy_attach_turn_child_parts(int, float, void *, int, void *);
extern float FastAddRotations(float, float);
extern int PlayMobySound(int, int, void *);
extern void STUB_printf(void *);
typedef struct { char pad[0x20]; unsigned char state; char pad2[3]; char *classData; char pad3[0xC]; unsigned short flags; char pad4[0x62]; int field98; } ControllerMoby10;
/* Updates the Aranos controller object, which runs the two scripted camera and object sequences. */
void aranos_controller_update(unsigned char *object)
{
    int *vars = *(int **)(object + 0x68);
    unsigned char *counter;

    switch (object[0x20]) {
    case 0:
        vars[9] = 0;
        vars[10] = 0;
        vars[12] = 0;
        vars[13] = 0;
        object[0x30] = 255;
        object[0x20] = 1;
        if (!g_controller_level_state.collected[(short)*(unsigned short *)(object + 0xb2)]) {
            int count_byte = g_moby_nibble_table[((short)*(unsigned short *)(object + 0xb2) >> 1) + (g_current_map_index << 10)];
            /* One 3-bit count per nibble; the low bit of the number picks the nibble. */
            if (!((*(unsigned short *)(object + 0xb2) & 1) ? (count_byte >> 4) & 7 : count_byte & 7)) {
                return;
            }
        }
        if (vars[17] != -1) {
            moby_mark_spawned(g_moby_array_base + (vars[17] << 8));
        }
        if (vars[16] != -1) {
            moby_mark_spawned(g_moby_array_base + (vars[16] << 8));
        }
        break;
    case 1:
        if (g_game_l00_mode != 2 && vars[8] != -1) {
            ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (vars[8] << 8));
            other->flags = (other->flags & 0xffbe) | 0x1000;
            other->field98 = *(int *)(other->classData + 0x10);
        }
        if (g_tutorial_probe_context.phase == 1 && g_game_l00_mode == 2) {
            if (g_tutorial_probe_context.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (vars[8] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                if (vars[17] != -1) {
                    moby_mark_spawned(g_moby_array_base + (vars[17] << 8));
                }
                if (vars[16] != -1) {
                    moby_mark_spawned(g_moby_array_base + (vars[16] << 8));
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
                enemy_spawn_child_parts(g_tutorial_probe_context.first, vars + 9, 0, 2);
            } else {
                int first = g_tutorial_probe_context.first;
                if (g_tutorial_probe_context.frame >= 1976) {
                    *(float *)(vars + 11) = FastAddRotations(*(float *)(vars + 11), 0.436332345f);
                    enemy_attach_turn_child_parts(first, *(float *)(vars + 11), vars + 9, 1, g_default_vector);
                } else {
                    enemy_attach_turn_child_parts(first, *(float *)(vars + 11), vars + 9, 0, g_default_vector);
                }
            }
            if (g_tutorial_probe_context.frame == 223) {
                int i;
                for (i = 0; i < 2; i++) {
                    ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (vars[i] << 8));
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
            if (vars[9]) {
                moby_mark_spawned((void *)vars[9]);
                moby_mark_spawned((void *)vars[10]);
                vars[9] = 0;
                vars[10] = 0;
            }
            if (vars[12]) {
                moby_mark_spawned((void *)vars[12]);
                moby_mark_spawned((void *)vars[13]);
                vars[12] = 0;
                vars[13] = 0;
            }
        }
        if (g_tutorial_probe_context.phase == 2 && g_game_l00_mode == 2) {
            if (g_tutorial_probe_context.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (vars[4] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                {
                    int i;
                    for (i = 0; i < 3; i++) {
                        ControllerMoby10 *other = (ControllerMoby10 *)(g_moby_array_base + (vars[5 + i] << 8));
                        other->field98 = 0;
                        other->flags = (other->flags | 0x41) & 0xefff;
                    }
                }
                enemy_spawn_child_parts(g_tutorial_probe_context.first, vars + 9, 0, 2);
                enemy_spawn_child_parts(g_tutorial_probe_context.second, vars + 12, 0, 2);
            } else {
                int first = g_tutorial_probe_context.first, second = g_tutorial_probe_context.second;
                if (g_tutorial_probe_context.frame < 780) {
                    *(float *)(vars + 11) = FastAddRotations(*(float *)(vars + 11), 0.261799425f);
                    *(float *)(vars + 14) = FastAddRotations(*(float *)(vars + 14), 0.261799425f);
                    enemy_attach_turn_child_parts(first, *(float *)(vars + 11), vars + 9, 1, g_default_vector);
                    enemy_attach_turn_child_parts(second, *(float *)(vars + 14), vars + 12, 1, g_default_vector);
                } else {
                    *(float *)(vars + 11) = FastAddRotations(*(float *)(vars + 11), 0.087266475f);
                    *(float *)(vars + 14) = FastAddRotations(*(float *)(vars + 14), 0.087266475f);
                    enemy_attach_turn_child_parts(first, *(float *)(vars + 11), vars + 9, 0, g_default_vector);
                    enemy_attach_turn_child_parts(second, *(float *)(vars + 14), vars + 12, 0, g_default_vector);
                }
            }
        }
        break;
    }
}

/* func_L00_0040EAA0 is in L00_003D54A8-f7-g8.c. */



/* Marks the object as ready on its first frame by setting a flag. */
void moby_init_on_first_frame_a(void *moby) {
    unsigned char *moby_bytes = (unsigned char *)moby;
    if (moby_bytes[0x20] == 0) {
        moby_bytes[0x20] = 1;
        *(unsigned short *)(moby_bytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void moby_init_on_first_frame_b(void *moby) {
    unsigned char *moby_bytes = (unsigned char *)moby;
    if (moby_bytes[0x20] == 0) {
        moby_bytes[0x20] = 1;
        *(unsigned short *)(moby_bytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void moby_init_on_first_frame_c(void *moby) {
    unsigned char *moby_bytes = (unsigned char *)moby;
    if (moby_bytes[0x20] == 0) {
        moby_bytes[0x20] = 1;
        *(unsigned short *)(moby_bytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void moby_init_on_first_frame_d(void *moby) {
    unsigned char *moby_bytes = (unsigned char *)moby;
    if (moby_bytes[0x20] == 0) {
        moby_bytes[0x20] = 1;
        *(unsigned short *)(moby_bytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void moby_init_on_first_frame_e(void *moby) {
    unsigned char *moby_bytes = (unsigned char *)moby;
    if (moby_bytes[0x20] == 0) {
        moby_bytes[0x20] = 1;
        *(unsigned short *)(moby_bytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void moby_init_on_first_frame_f(void *moby) {
    unsigned char *moby_bytes = (unsigned char *)moby;
    if (moby_bytes[0x20] == 0) {
        moby_bytes[0x20] = 1;
        *(unsigned short *)(moby_bytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void moby_init_on_first_frame_g(void *moby) {
    unsigned char *moby_bytes = (unsigned char *)moby;
    if (moby_bytes[0x20] == 0) {
        moby_bytes[0x20] = 1;
        *(unsigned short *)(moby_bytes + 0x34) |= 0x800;
    }
}
