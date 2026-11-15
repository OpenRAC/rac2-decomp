#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[0x10];
    float v10[4];
    unsigned char pad20[0x98 - 0x20];
    float f98;
    unsigned char pad9C[0x1270 - 0x9C];
    int f1270;
    unsigned char pad1274[0x1298 - 0x1274];
    int f1298;
    unsigned char pad129C[0x149D - 0x129C];
    unsigned char b149D;
    unsigned char pad149E[0x2290 - 0x149E];
    void *f2290;
    int f2294;
    int f2298;
    int f229C;
} Hero_L00_002A61C8;
extern Hero_L00_002A61C8 g_hero_state;
extern int g_current_map_index MACRO_ADDR;
extern int FloatToInt(float);
extern int snd_start_from_weights(int, int, int, int, int, int);
extern void moby_transform_joint_to_world(char *, int, char *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float coll_probe_ground_height_below(void *, int, float);
extern float FastAddRotations(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
typedef struct Obj_L00_0033BA68 Obj_L00_0033BA68;
extern Obj_L00_0033BA68 *func_PAL_L00_0033DE50(char *, int, float);

void func_PAL_L00_002A6058(int kind, int side, int play_sound, int duration) {
    float point[4];
    float offset[4];
    float heading;
    int special;
    int ticks;
    if (play_sound) {
        special = 0;
        if (g_hero_state.f1270) {
            int mode = g_hero_state.f1298;
            if ((unsigned int)(mode - 19) < 2 || mode == 54)
                special = 1;
        }
        ticks = FloatToInt((float)((duration << 10) / 30));
        snd_start_from_weights(kind, side, special, 0, (int)g_hero_state.f2290, ticks);
    }
    if (g_current_map_index == 7) {
        if (g_hero_state.b149D == 0) goto effect;
    }
    if (g_current_map_index != 19) return;
    if (g_hero_state.b149D != 2) return;
effect:
    moby_transform_joint_to_world(g_hero_state.f2290, side + 22, (char *)point);
    point[0] += math_fast_sin_or_cos_a(g_hero_state.f98) * 0.05f;
    point[1] += math_fast_sin_or_cos_b(g_hero_state.f98) * 0.05f;
    point[2] = coll_probe_ground_height_below(point, 0, 0.5f) + 0.057f;
    heading = g_hero_state.f98;
    if (g_hero_state.f2294 == 0 || g_hero_state.f229C == 4) {
        if (side == 0) {
            heading = FastAddRotations(heading, 0.436332345f);
            vec_scale_to_length(offset, g_hero_state.v10, 0.037f);
            FastVecAdd(point, point, offset);
        } else {
            heading = FastAddRotations(heading, -0.436332345f);
            vec_scale_to_length(offset, g_hero_state.v10, -0.037f);
            FastVecAdd(point, point, offset);
        }
    }
    func_PAL_L00_0033DE50((char *)point, !side, heading);
}
