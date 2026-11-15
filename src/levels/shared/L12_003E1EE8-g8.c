#include "common.h"
typedef int qword __attribute__((mode(TI)));

extern float D_L12_001B0B10 __attribute__((sda));
extern u8 D_L12_001FEAC0[];

extern void FastVecSub(float *, const float *, const float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);

/* Moves the enemy along a path toward the next point and says when it has reached the end. */
int AdvanceAlongPath(u8 *moby, u8 *route) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *home_path = *(u8 **)(D_L12_001FEAC0 + (*(s32 *)(vars + 0x158) << 2));
    float entry[4];
    float dir[4];
    float rot[4];
    float len;
    u8 *src;

    if (*(s32 *)(vars + 0x168) > 0) {
        src = (u8 *)(*(s32 *)(vars + 0x168) << 4);
        src += (s32)route;
        src += 0x10;
    }
    else
        src = home_path + 0x10;
    qcopy(entry, src);
    if (*(s32 *)(vars + 0x168) > 0) {
        FastVecSub(rot, route + ((*(s32 *)(vars + 0x168) << 4) + 0x10),
                      route + (*(s32 *)(vars + 0x168) << 4));
        *(qword *)dir = *(qword *)rot;
        len = FastVecLength(dir);
        if (D_L12_001B0B10 * 0.016666668f < len)
            vec_scale_to_length(dir, dir, D_L12_001B0B10 * 0.016666668f);
        FastVecAdd(moby + 0x10, moby + 0x10, dir);
    } else {
        FastVecSub(rot, home_path + 0x10, route + (*(s32 *)route << 4));
        *(qword *)dir = *(qword *)rot;
        len = FastVecLength(dir);
        if (D_L12_001B0B10 * 0.016666668f < len)
            vec_scale_to_length(dir, dir, D_L12_001B0B10 * 0.016666668f);
        FastVecAdd(moby + 0x10, moby + 0x10, dir);
    }
    if (fast_vec_dist(moby + 0x10, entry) <= 0.5f) {
        s32 point_index = *(s32 *)(vars + 0x168);

        if (point_index == -1)
            return 1;
        if (*(s32 *)route - 1 == point_index) {
            float ground_height;

            *(s32 *)(vars + 0x168) = -1;
            ground_height = coll_probe_ground_height_below(home_path + 0x10, 0, 0.5f);
            if (*(float *)(home_path + 0x18) - ground_height < 10.0f)
                *(float *)(home_path + 0x18) = ground_height + 0.5f;
        } else {
            *(s32 *)(vars + 0x168) = point_index + 1;
        }
    }
    return 0;
}
