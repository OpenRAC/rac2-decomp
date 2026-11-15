#include "include_asm.h"

#include "common.h"
typedef unsigned int UpdateQuad __attribute__((mode(TI)));
typedef union { UpdateQuad q; float f[4]; } UpdateVec;
extern int D_L17_001B2748 MACRO_ADDR;
extern int D_L17_001C0018 NOT_SDA;
extern float D_L17_001B0390 __attribute__((sda));
extern UpdateVec D_L17_001B0380 __attribute__((sda));
extern char g_hero_position[];
extern void *g_hero_moby NOT_SDA;
extern char D_L17_001A8F20[] __attribute__((sda));
extern float coll_probe_ground_height_below(void *, int, float);
extern int platform_is_player_inside_footprint(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern float fast_vec_dist(void *, void *);
extern void part_spawn_effect_burst(void *, int, int, int, int, int, int, void *);
extern void PlayMobySound(int, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

void func_PAL_L17_003CB334(char *self) {
    UpdateVec oldpos, delta;
    char collision[0x30];
    char *position;
    char *data = *(char **)(self + 0x68);
    float ground;
    if (*(int *)(data + 0xAC) == 1) return;
    position = self + 0x10;
    oldpos.q = *(UpdateQuad *)(self + 0x10);
    if (*(unsigned char *)(self + 0x20) == 0) {
        if (*(int *)(data + 0x90) != -1) {
            ground = coll_probe_ground_height_below(position, 0, 0.5f);
            *(int *)(data + 0x9C) = D_L17_001C0018;
            if (ground < *(float *)(self + 0x18)) {
                *(float *)(data + 0x98) += D_L17_001B0390 * 0.00040000002f;
                *(float *)(self + 0x18) -= *(float *)(data + 0x98);
            } else {
                *(int *)(data + 0x98) = 0;
                *(float *)(self + 0x18) = ground;
            }
            if (platform_is_player_inside_footprint(self)) {
                matrix_mul_vec3(&delta, &D_L17_001B0380, self + 0xC0);
                make_hit_descriptor(collision, self, 0x10001, &delta, 2.0f);
                QueueMobyImpact(g_hero_moby, collision);
            }
        }
    }
    if (D_L17_001B2748 >= 31) {
        if (*(int *)(data + 0xA4) == 0 && *(int *)(data + 0xA8) >= 43 &&
            fast_vec_dist(position, g_hero_position) < 15.0f && *(unsigned char *)(self + 0x20) == 0) {
            part_spawn_effect_burst(self, 0x931, 0, 0x931, 4, 6, 0, D_L17_001A8F20);
            PlayMobySound(0, 0, self);
            *(unsigned char *)(self + 0x20) = 1;
            *(int *)(self + 0x98) = 0;
            *(unsigned short *)(self + 0x34) |= 0x41;
            return;
        } else if (*(int *)(data + 0xA4)) {
            *(int *)(data + 0xA4) = 0;
            *(int *)(data + 0xA8) = 0;
        } else {
            *(int *)(data + 0xA8) += 1;
        }
    }
    FastVecSub(&delta, position, &oldpos);
    mat_combine_and_store(data + 0x50, &delta, self + 0xF0, self + 0xF0);
}
