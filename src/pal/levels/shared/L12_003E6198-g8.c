#include "include_asm.h"

#include "common.h"
typedef int qword __attribute__((mode(TI)));
extern float g_enemy_path_speed __attribute__((sda));
extern u8 g_path_zone_table[];
extern void FastVecSub(float *, const float *, const float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);

/* Moves the enemy along a path toward the next point and says when it has reached the end (PAL: 50 Hz step). */
int AdvanceAlongPath_pal(u8 *moby, u8 *path) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *zone = *(u8 **)(g_path_zone_table + (*(s32 *)(vars + 0x158) << 2));
    float entry[4];
    float dir[4];
    float rot[4];
    float len;
    u8 *src;

    if (*(s32 *)(vars + 0x168) > 0) {
        src = (u8 *)(*(s32 *)(vars + 0x168) << 4);
        src += (s32)path;
        src += 0x10;
    }
    else
        src = zone + 0x10;
    qcopy(entry, src);
    if (*(s32 *)(vars + 0x168) > 0) {
        FastVecSub(rot, path + ((*(s32 *)(vars + 0x168) << 4) + 0x10),
                      path + (*(s32 *)(vars + 0x168) << 4));
        *(qword *)dir = *(qword *)rot;
        len = FastVecLength(dir);
        if (g_enemy_path_speed * 0.020000001f < len)
            vec_scale_to_length(dir, dir, g_enemy_path_speed * 0.020000001f);
        FastVecAdd(moby + 0x10, moby + 0x10, dir);
    } else {
        FastVecSub(rot, zone + 0x10, path + (*(s32 *)path << 4));
        *(qword *)dir = *(qword *)rot;
        len = FastVecLength(dir);
        if (g_enemy_path_speed * 0.020000001f < len)
            vec_scale_to_length(dir, dir, g_enemy_path_speed * 0.020000001f);
        FastVecAdd(moby + 0x10, moby + 0x10, dir);
    }
    if (fast_vec_dist(moby + 0x10, entry) <= 0.5f) {
        s32 index = *(s32 *)(vars + 0x168);

        if (index == -1)
            return 1;
        if (*(s32 *)path - 1 == index) {
            float ground;

            *(s32 *)(vars + 0x168) = -1;
            ground = coll_probe_ground_height_below(zone + 0x10, 0, 0.5f);
            if (*(float *)(zone + 0x18) - ground < 10.0f)
                *(float *)(zone + 0x18) = ground + 0.5f;
        } else {
            *(s32 *)(vars + 0x168) = index + 1;
        }
    }
    return 0;
}
