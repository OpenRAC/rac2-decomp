/* func_PAL_L00_00362A88, the PAL copy of func_L00_003603C0: the same C, where func_002E64A0
   becomes func_PAL_002E7270; 0x2798 becomes 0x12ea. */
#include "include_asm.h"
#include "common.h"

typedef struct Rac2Native_acdcf1600d770d3b_ScalarConfigure116State {
    unsigned char prefix_00[0x60];
    unsigned int value_60;
    int value_64;
    unsigned char selector_68;
    unsigned char axis_69;
    unsigned char mode_6a;
    unsigned char dirty_6b;
} Rac2Native_acdcf1600d770d3b_ScalarConfigure116State;

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef void (*DrawCallback)(void *);
extern int D_L00_001A8F00 __attribute__((sda));
extern char *D_L00_00220DA0[];
extern short D_L00_001A8F80[2] MACRO_ADDR;
extern unsigned int g_equipment_bits __attribute__((sda));
extern Vector g_camera_l00_position;
extern char g_hero_position[];

extern unsigned int D_00138324;
extern char g_hero_moby_default[];
extern int D_L00_001B1AE0 __attribute__((sda));
extern void func_PAL_002E7270(void *);
extern void ref_L00_003603C0_00(DrawCallback, void *);
extern void gfx_add_draw_callback_first(DrawCallback, void *);
extern void render_environment_mapped_object(void *);
extern void gfx_draw_ground_shadow(void *);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_a(float);
extern int TryClaimNotice(int, int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern float FastAddRotations(float, float);
extern int level_release_matching_resource(int);

#define HERO_RIDING_D54() \
    ((*(unsigned char **)(D_00189EA0 + 0x2BC)) && *(short *)((*(unsigned char **)(D_00189EA0 + 0x2BC)) + 0xAA) == 0xD54 && \
     (unsigned char)(*(unsigned char **)(D_00189EA0 + 0x2BC))[0x20] != 254 && (unsigned char)(*(unsigned char **)(D_00189EA0 + 0x2BC))[0x20] != 253)

void func_PAL_L00_00362A88(unsigned char *object) {
    Vector position;
    Vector offset;
    Vector angles;
    unsigned char *private = *(unsigned char **)(object + 0x68);
    char **slot;
    int index;
    short key;
    char *spawn;
    unsigned int shade;
    int available;
    if (!D_L00_001A8F00) func_PAL_002E7270(object);
    if ((unsigned char)object[0x31]) {
        private[0xE] = (unsigned char)private[0xE] + 2;
        key = D_L00_001A8F80[(g_equipment_bits >> 4) & 1];
        for (index = 0; D_L00_00220DA0[index]; index++) {
            slot = D_L00_00220DA0 + index;
            if (*(short *)(D_L00_00220DA0[index] + 0xAA) == key) {
                shade = (int)(math_fast_sin_or_cos_a(IntToFloat((unsigned char)private[0xE] - 128) * 0.024543693f) * 50.0f) + 140;
                *(unsigned int *)(*slot + 0x78) = shade | (shade << 8) | (shade << 16);
                *(unsigned short *)(*slot + 0x34) |= 0x10;
                break;
            }
        }
        ref_L00_003603C0_00(render_environment_mapped_object, object);
        if (vec_distance_xy(object + 0x10, &g_camera_l00_position) < 32.0f)
            gfx_add_draw_callback_first(gfx_draw_ground_shadow, object);
    }
    if (*(short *)(private + 0xC) != 0) {
        if (fast_vec_dist(object + 0x10, &g_hero_position) > 6.1f && !HERO_RIDING_D54())
            *(short *)(private + 0xC) = 0;
    } else {
        if (vec_distance_xy(object + 0x10, &g_hero_position) < 8.0f || HERO_RIDING_D54()) {
            if (fast_vec_dist(object + 0x10, &g_hero_position) < 6.0f || HERO_RIDING_D54())
                *(short *)(private + 0xC) = 1;
        }
    }
    if (*(unsigned short *)(object + 0x34) & 1) *(short *)(private + 0xC) = 0;
    if (*(short *)(private + 0xC)) {
        available = TryClaimNotice(2, 0x12ea, 1) != 0;
        if ((D_00138324 & 0x10) && available) {
            offset.q = 0;
            angles.q = 0;
            offset.f[0] = 1.48f;
            offset.f[1] = 2.64f;
            angles.f[0] = -0.021118486f;
            angles.f[1] = 0.0588176f;
            angles.f[2] = 1.2252212f;
            matrix_mul_vec3(&position, &offset, object + 0xC0);
            FastVecAdd(&position, &position, object + 0x10);
            position.f[2] = coll_probe_ground_height_below(&position, 0, 0.5f);
            angles.f[2] = FastAddRotations(angles.f[2], *(float *)(object + 0xF8));
            spawn = g_hero_moby_default + 0x70;
            qcopy(spawn, &position);
            qcopy(spawn + 0x10, &angles);
            level_release_matching_resource(2);
            *(short *)(spawn - 0x4A) = 0;
            D_L00_001B1AE0 = 1;
        }
    }
}
