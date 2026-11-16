#include "names.h"
/* func_PAL_L07_0037B708, the PAL copy of func_L07_00378AE0: the same C, where rename func_L07_00379020 becomes func_PAL_L07_0037BC50; rename func_L07_00336860 becomes func_PAL_L07_00338B98; expr 0.055555556f becomes 0.020000001f; expr 0.027777778f becomes 0.010000001f; expr 0.13888888f becomes 0.050000004f; lit 4.0f becomes 4.8f. */

#include "common.h"

typedef struct {
    float x, y, z, w;
} V;

/* Mixed address forms are deliberate: retail loads these with lui+lw (MACRO_ADDR),
 * a split %hi/%lo pair (nosda) or $gp (sda/SDATA). */
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

extern void part_scatter_around_camera_pal(void *);
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
extern char *part_spawn_snow_pal(void *, void *, int, int);

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

/* Makes snow fall around the hero, with a stronger burst when the hero moves fast or is in a snow zone (PAL: 50 Hz timings). */
void snowfall_update_pal(Object *moby) {
    V pos, vel, tmp_vec, point;
    Data *data = (Data *)moby->data;
    int j, i, k;
    float lo, hi;
    V *hero_pos;

    switch (moby->state) {
    case 0:
        moby->alpha = 255;
        moby->flags |= 0x100;
        if (g_current_map_index == 7 && g_frame_l07_counter) {
            part_scatter_around_camera_pal(moby);
            moby_set_state(moby, 1, -1);
        }
        data->speed = 1.5f;
        data->fall = 2.5f;
        data->enabled = 1;
        g_snowfall_moby = (char *)moby;
        break;
    case 1:
        if (g_current_map_index == 7 && g_cutscene_l07_active_flag == 1) {
            moby_set_state(moby, 2, -1);
            break;
        }
        for (i = 0; i < math_random_int_below(2); i++) {
            math_random_planar_offset(&pos, 15.0f);
            pos.z += 7.0f;
            FastVecAdd(&pos, &pos, &g_hero_position_block);
            FastVecScale(&tmp_vec, &g_hero_position_block[35], 4.0f);
            FastVecAdd(&pos, &tmp_vec, &pos);
            math_random_planar_offset(&vel, data->speed * (0.020000001f));
            vel.z = -(data->fall * (0.020000001f)) * math_random_float_range(0.8f, 1.2f);
            if (!coll_point_inside_region(&pos, data->group))
                part_spawn_snow_pal(&pos, &vel, 0, 0);
        }
        FastVecScale(&point, &g_hero_position_block[35], 4.0f);
        FastVecAdd(&tmp_vec, &point, &g_hero_position_block);
        FastVecSub(&g_snow_velocity_vec, &tmp_vec, &data->previous);
        data->scale = FastVecLength(&g_snow_velocity_vec) * 3.3333333f;
        if (data->scale > 1.0f)
            data->scale = 1.0f;
        else if (data->scale < 0.0f)
            data->scale = 0.0f;
        FastVecScale(&g_snow_velocity_vec, &g_snow_velocity_vec, data->scale);
        qcopy_nc(&data->previous, &tmp_vec);
        break;
    case 2:
        if (flag_set_first_pending(moby))
            g_snow_velocity_vec.z -= 60.0f;
        if (g_current_map_index == 7 && g_cutscene_l07_active_flag != 1) {
            moby_set_state(moby, 1, -1);
            break;
        }
        if (!g_snowfall_target_moby)
            break;
        hero_pos = g_hero_position_block;
        j = *(short *)(g_snowfall_target_moby + 0xAA) - 0x11D9;
        lo = g_snowfall_side_min_table[j * 2];
        hi = g_snowfall_side_max_table[j * 2];
        for (k = 0; k < 6; k++) {
            FastVecScale(&tmp_vec, &data->axisA, math_random_float_range(-25.0f, 25.0f));
            FastVecAdd(&pos, &tmp_vec, &data->origin);
            FastVecScale(&tmp_vec, &data->axisB, math_random_float_range(lo, hi));
            FastVecAdd(&pos, &tmp_vec, &pos);
            FastVecAdd(&pos, &pos, hero_pos);
            FastVecSub(&pos, &pos, g_snowfall_target_moby + 0x10);
            pos.z -= g_hero_l07_state_block[0x148 / 4] - *(float *)(g_snowfall_target_moby + 0x18);
            math_random_planar_offset(&vel, 0.050000004f);
            vel.z = data->fall * (math_random_float_range(0.8f, 1.2f) * (-0.010000001f));
            part_spawn_snow_pal(&pos, &vel, 1, 0);
        }
        FastVecSub(&g_snow_velocity_vec, hero_pos, &data->previous);
        FastVecScale(&tmp_vec, g_snowfall_target_moby + 0xC0, 1.2f);
        FastVecAdd(&g_snow_velocity_vec, &tmp_vec, &g_snow_velocity_vec);
        qcopy_nc(&data->previous, hero_pos);
        break;
    }
}
