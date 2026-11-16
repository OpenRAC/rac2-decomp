#include "include_asm.h"

#include "common.h"
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern void moby_set_state(unsigned char *, int, int);
extern void moby_transform_joint_to_world(char *, int, char *);
extern float vec_distance_xy(void *, void *);
extern void moby_set_flag_bit(unsigned char *, int);
extern void moby_mark_table_entry_flagged(unsigned int);
extern void hero_exit_vehicle_mode_us2(int);
typedef struct {
    char reserved00[0xBC];
    unsigned char enabled;
    char reservedBD[0x100 - 0xBD];
} YeedilObject;
extern YeedilObject *g_group_l20_member_table;
extern YeedilObject *yeedilObjectsGp SDATA(D_L20_001B2F9C);
extern struct {
    char reserved00[0x80];
    float position[4];
    char reserved90[0x33C - 0x90];
    unsigned char *owner;
    int active;
} D_00189E20;
typedef struct {
    int objects[4];
    int modes[4];
    float angle;
    int activated;
    unsigned int event;
    int callback;
} YeedilActivation;

void floor_l20_switch_update_us2(unsigned char *object)
{
    float point[4] __attribute__((aligned(16)));
    YeedilActivation *state = *(YeedilActivation **)(object + 0x68);
    int color;
    if (!state) return;
    state->angle = FastAddRotations(state->angle, 0.10471977f);
    color = FloatToInt((math_fast_sin_or_cos_b(state->angle) * 4.0f - 3.0f) * 128.0f);
    if (color > 128) color = 128;
    else if (color < 32) color = 32;
    if (object[0x20] == 0) {
        *(unsigned short *)(object + 0x34) |= 0x10;
        moby_set_state(object, 1, -1);
    } else if (object[0x20] == 1) {
        float distance;
        moby_transform_joint_to_world((char *)object, 0, (char *)point);
        distance = vec_distance_xy(g_hero_state.position, point);
        state->activated = 0;
        if (g_hero_state.owner == object && g_hero_state.active &&
            distance < *(float *)(object + 0x2C) * 0.5f / *(float *)(*(char **)(object + 0x24) + 0x24)) {
            int missing = -1;
            int enabled;
            int *entry;
            int remaining;
            moby_set_state(object, 2, missing);
            enabled = 1;
            entry = state->objects;
            for (remaining = 3; remaining >= 0; entry++, remaining--) {
                int index = *entry;
                if (index != missing) {
                    if (entry[4]) {
                        moby_set_flag_bit((unsigned char *)&yeedilObjectsGp[index], enabled);
                    } else {
                        g_group_l20_member_table[index].enabled = enabled;
                    }
                }
            }
            moby_mark_table_entry_flagged(state->event);
            if (state->callback) hero_exit_vehicle_mode_us2(0);
        }
        *(unsigned int *)(object + 0x78) = color | (0x80 << 24);
    } else if (object[0x20] == 2) {
        if (!state->activated) state->activated = 1;
        {
            unsigned int green = (color << 8) | (0x80 << 24);
            unsigned int blue = color << 16;
            *(unsigned int *)(object + 0x78) = blue | green;
        }
    }
}
