#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;
typedef struct Ent {
    unsigned char pad00[0x31];
    unsigned char f31;
    unsigned char pad32[2];
    unsigned short f34;
    unsigned char pad36[0x98 - 0x36];
    int f98;
} Ent;
extern unsigned int g_entity_group_lists[];
extern char *g_moby_l02_pool;
extern int g_group_max_index __attribute__((sda));
extern int g_destroyed_target_count;
extern float g_target_spin_rate __attribute__((sda));
extern float g_explode_piece_params_a[2] __attribute__((sda));
extern float g_explode_piece_params_b[2] __attribute__((sda));
extern float g_explode_piece_params_c[2] __attribute__((sda));
extern int g_explode_color __attribute__((sda));
extern float math_fast_sin_or_cos_b(float x);
extern float FastAddRotations(float a, float b);
extern float fast_subtract_rotations(float a, float b);
extern void path_sample_position(int *path, int seg, void *pos, void *rot, int flags, float t);
extern void *part_find_owned_effect_slot(void *e, int a1, int a2);
extern void part_explode_object_into_pieces_pal(void *a0, void *a1, void *a2, void *a3, int t0, int t1, int t2, int t3,
                              int s0, int s1, int s2);
extern void moby_compute_local_point(char *a0, float *a1, float f12, float f13, float f14);
extern int PlayMobySound(int a0, int a1, void *a2);
extern void SpawnExplosionEffects_pal(void *a0, float f12, void *a1, float f13, void *a2, float f14, int a3,
                          float f15, int t0, int t1, float f16, float f17, int t2, float f18,
                          int t3, int s0, int s1, int s2, int s3);
extern float ApproachValue(float *p, float a, float b);
extern void update_lamp_glow_effects_pal(void *e);
extern void blinking_lamp_update_pal(void *e);
extern void func_002A0F48(void *e);

/* Walks the group's entity list: each one moves along the path object (func_002C9828), turns its
   angle and advances its phase; a hit by the player while it is active switches it off and spawns
   the debris (func_PAL_L00_0032C328, func_PAL_002AC718); a live one tilts toward its turning speed
   (func_002AA2E8) and runs the level's two update calls. */
void target_update_moving_on_path_pal(unsigned char *group_owner) {
    unsigned char *path_vars = *(unsigned char **)(group_owner + 0x68);
    int *path = *(int **)(path_vars + 0x60);
    float range = (float)*path;
    float step = *(float *)(path_vars + 0x14);
    int seg = *(short *)(path_vars + 0x70);
    float rate = g_target_spin_rate * 0.0003490659f;
    unsigned short *list;
    unsigned char *moby;
    unsigned char *moby_vars;
    float prev;
    float height;

    list = (unsigned short *)g_entity_group_lists[group_owner[0x21]];
    while (group_owner[0x21] != 0xFF && group_owner[0x21] <= g_group_max_index && list != 0 &&
           ((list != 0 && (short)list[-1] >= 0) || list == (unsigned short *)g_entity_group_lists[group_owner[0x21]])) {
        moby = (unsigned char *)(g_moby_l02_pool + ((*list & 0x7FFF) << 8));
        if (moby == 0)
            break;
        moby_vars = *(unsigned char **)(moby + 0x68);
        prev = *(float *)(moby + 0xF8);
        height = *(float *)(moby_vars + 0x10) + *(float *)(moby_vars + 0x7C) * math_fast_sin_or_cos_b(*(float *)(moby_vars + 0x80));
        if (range <= height)
            height -= range;
        else if (height < 0.0f)
            height += range;
        path_sample_position(path, seg, moby + 0x10, moby + 0xF0, 0, height);
        *(float *)(moby_vars + 0x68) = FastAddRotations(*(float *)(moby_vars + 0x68), *(float *)(moby_vars + 0x6C));
        *(float *)(moby + 0x18) += math_fast_sin_or_cos_b(*(float *)(moby_vars + 0x68));
        *(float *)(moby_vars + 0x10) += step;
        if (range <= *(float *)(moby_vars + 0x10))
            *(float *)(moby_vars + 0x10) -= range;
        *(float *)(moby_vars + 0x80) = FastAddRotations(*(float *)(moby_vars + 0x80), *(float *)(moby_vars + 0x84));
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0) {
            if (moby[0x31] != 0) {
                Vec4 dir;
                float pos[4] __attribute__((aligned(16)));

                ((Ent *)moby)->f31 = 0;
                ((Ent *)moby)->f34 |= 1;
                ((Ent *)moby)->f98 = 0;
                g_destroyed_target_count++;
                part_explode_object_into_pieces_pal(moby, g_explode_piece_params_a, g_explode_piece_params_b, g_explode_piece_params_c, 0x3F, 2,
                                  g_explode_color, 0, 0xFFFF, 0xFF, 0);
                dir.q = 0;
                dir.f[2] = 0.060000002f;
                moby_compute_local_point((char *)moby, pos, 0.0f, 0.0f, 0.0f);
                if (*(short *)(moby + 0xAA) == 0x1290)
                    PlayMobySound(0, 0, moby);
                if (*(short *)(moby + 0xAA) == 0x134B)
                    PlayMobySound(0, 0, moby);
                if (*(short *)(moby + 0xAA) == 0xB15)
                    PlayMobySound(1, 0, moby);
                if (*(short *)(moby + 0xAA) == 0xB13)
                    PlayMobySound(1, 0, moby);
                SpawnExplosionEffects_pal(moby, 0.0f, &dir, 0.0f, pos, 5.0f, 0x23, 2.5f, 8, 0x10, 0.0f, 3.0f, -1,
                              15.0f, 1, 10, -1, 0, 0x810001);
            }
        }
        moby[0xA8] = 0xFF;
        if (moby[0x31] != 0) {
            if ((*(unsigned short *)(moby + 0x34) ^ 1) & 1) {
                height = -fast_subtract_rotations(*(float *)(moby + 0xF8), prev) * 50.0f;
                if (0.78539824f < height)
                    height = 0.78539824f;
                if (height < -0.78539824f)
                    height = -0.78539824f;
                ApproachValue((float *)(moby + 0xF0), height, rate);
                if (*(short *)(moby_vars + 0x72) != 0)
                    update_lamp_glow_effects_pal(moby);
                blinking_lamp_update_pal(moby);
            }
        }
        func_002A0F48(moby);
        list++;
    }
}
