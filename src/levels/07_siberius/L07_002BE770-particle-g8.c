#include "include_asm.h"

#include "common.h"

typedef struct {
    float x, y, z, w;
} V;

/* Mixed address forms are deliberate: retail loads these with lui+lw (MACRO_ADDR),
 * a split %sideMax/%sideMin pair (nosda) or $gp (sda/SDATA). */
extern int g_current_map_index MACRO_ADDR;
extern int g_frame_l07_counter MACRO_ADDR;
extern int g_cutscene_l07_active_flag __attribute__((nosda));
extern char *g_snowfall_moby __attribute__((sda));
extern char *g_snowfall_target_moby MACRO_ADDR;
extern float g_snowfall_side_min_table[] SDATA(D_L07_001AEC10);
extern float g_snowfall_side_max_table[] MACRO_ADDR;
extern V g_hero_position_block[];   /* hero position (hero + 0x140) */
extern float g_hero_l07_state_block[]; /* hero */
extern V g_snow_velocity_vec MACRO_ADDR;

extern void part_scatter_around_camera(void *);
extern void moby_set_state(void *, int, int);
extern void math_random_planar_offset(void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecLength(void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int flag_set_first_pending(void *);
extern int coll_point_inside_region(void *, int);
extern char *part_spawn_snow(void *, void *, int, int);

typedef struct {
    char pad00[0x20];
    unsigned char state;
    char pad21[0xF];
    unsigned char alpha;
    char pad31[3];
    unsigned short flags;
    char pad36[0x32];
    void *data;
} Object;

typedef struct {
    float speed;
    float fall;
    int enabled;
    float scale;
    int group;
    char pad14[0x1C];
    V axisA;
    V axisB;
    V origin;
    V previous;
} Data;

/* Makes snow fall around the hero, with a stronger burst when the hero moves fast or is in a snow zone. */
void snowfall_update(Object *obj) {
    V pos, vel, tmp, point;
    Data *data = (Data *)obj->data;
    int last_index, i, burst_index;
    float side_min, side_max;
    V *hero_pos;

    switch (obj->state) {
    case 0:
        obj->alpha = 255;
        obj->flags |= 0x100;
        if (g_current_map_index == 7 && g_frame_l07_counter) {
            part_scatter_around_camera(obj);
            moby_set_state(obj, 1, -1);
        }
        data->speed = 1.5f;
        data->fall = 2.5f;
        data->enabled = 1;
        g_snowfall_moby = (char *)obj;
        break;
    case 1:
        if (g_current_map_index == 7 && g_cutscene_l07_active_flag == 1) {
            moby_set_state(obj, 2, -1);
            break;
        }
        for (i = 0; i < math_random_int_below(2); i++) {
            math_random_planar_offset(&pos, 15.0f);
            pos.z += 7.0f;
            FastVecAdd(&pos, &pos, &g_hero_position_block);
            FastVecScale(&tmp, &g_hero_position_block[35], 4.0f);
            FastVecAdd(&pos, &tmp, &pos);
            math_random_planar_offset(&vel, data->speed * (1.0f / 60.0f));
            vel.z = -(data->fall * (1.0f / 60.0f)) * math_random_float_range(0.8f, 1.2f);
            if (!coll_point_inside_region(&pos, data->group))
                part_spawn_snow(&pos, &vel, 0, 0);
        }
        FastVecScale(&point, &g_hero_position_block[35], 4.0f);
        FastVecAdd(&tmp, &point, &g_hero_position_block);
        FastVecSub(&g_snow_velocity_vec, &tmp, &data->previous);
        data->scale = FastVecLength(&g_snow_velocity_vec) * 4.0f;
        if (data->scale > 1.0f)
            data->scale = 1.0f;
        else if (data->scale < 0.0f)
            data->scale = 0.0f;
        FastVecScale(&g_snow_velocity_vec, &g_snow_velocity_vec, data->scale);
        qcopy_nc(&data->previous, &tmp);
        break;
    case 2:
        if (flag_set_first_pending(obj))
            g_snow_velocity_vec.z -= 60.0f;
        if (g_current_map_index == 7 && g_cutscene_l07_active_flag != 1) {
            moby_set_state(obj, 1, -1);
            break;
        }
        if (!g_snowfall_target_moby)
            break;
        hero_pos = g_hero_position_block;
        last_index = *(short *)(g_snowfall_target_moby + 0xAA) - 0x11D9;
        side_min = g_snowfall_side_min_table[last_index * 2];
        side_max = g_snowfall_side_max_table[last_index * 2];
        for (burst_index = 0; burst_index < 6; burst_index++) {
            FastVecScale(&tmp, &data->axisA, math_random_float_range(-25.0f, 25.0f));
            FastVecAdd(&pos, &tmp, &data->origin);
            FastVecScale(&tmp, &data->axisB, math_random_float_range(side_min, side_max));
            FastVecAdd(&pos, &tmp, &pos);
            FastVecAdd(&pos, &pos, hero_pos);
            FastVecSub(&pos, &pos, g_snowfall_target_moby + 0x10);
            pos.z -= g_hero_l07_state_block[0x148 / 4] - *(float *)(g_snowfall_target_moby + 0x18);
            math_random_planar_offset(&vel, 1.0f / 24.0f);
            vel.z = data->fall * (math_random_float_range(0.8f, 1.2f) * (-1.0f / 120.0f));
            part_spawn_snow(&pos, &vel, 1, 0);
        }
        FastVecSub(&g_snow_velocity_vec, hero_pos, &data->previous);
        FastVecScale(&tmp, g_snowfall_target_moby + 0xC0, 1.0f);
        FastVecAdd(&g_snow_velocity_vec, &tmp, &g_snow_velocity_vec);
        qcopy_nc(&data->previous, hero_pos);
        break;
    }
}
