#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern void part_kill(void *);
extern int g_current_game_mode;
typedef struct {
    float vx, vy, vz;    
    char *owner;         
    float ox, oy, oz;    
    int *rec;            
} SparkMotion_C4D18;
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern int math_lerp_int_fraction(int, int, float);
extern int FastDecTimer(short *);

/* The velocity decays by 0.98 per frame. While D_001A8BB0 is clear the spark
   follows its owner (its offset moved by the velocity, then rotated by the
   owner's matrix at 0xC0) and dies with it; otherwise it drifts. */
void part_update_spark_follow_owner_pal(char *self)
{
    float velocity[4], offset[4], rotated[4];
    SparkMotion_C4D18 *motion = (SparkMotion_C4D18 *)(self + 0x20);
    int *rec = motion->rec;
    char *owner;

    *(float *)(self + 0xC) =
        IntToFloat(*(short *)((char *)rec + 8) * (rec[3] - *(short *)(self + 0xA)) / rec[3]
                      + *(short *)((char *)rec + 0xA)) * 1000.0f;
    velocity[0] = motion->vx;
    velocity[1] = motion->vy;
    velocity[2] = motion->vz;
    FastVecScale(velocity, velocity, 0.976f);
    motion->vx = velocity[0];
    motion->vy = velocity[1];
    motion->vz = velocity[2];
    if (g_current_game_mode == 0) {
        owner = motion->owner;
        if (owner != 0 && *(unsigned char *)(owner + 0x20) != 0xFE && *(unsigned char *)(owner + 0x20) != 0xFD) {
            offset[0] = motion->ox;
            offset[1] = motion->oy;
            offset[2] = motion->oz;
            FastVecAdd(offset, offset, velocity);
            motion->ox = offset[0];
            motion->oy = offset[1];
            motion->oz = offset[2];
            matrix_mul_vec3(rotated, offset, motion->owner + 0xC0);
            FastVecAdd(self + 0x10, motion->owner + 0x10, rotated);
        } else {
            part_kill(self);
            return;
        }
    } else {
        FastVecAdd(self + 0x10, self + 0x10, velocity);
    }
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + 1;
    *(int *)(self + 4) = math_lerp_int_fraction(rec[1], rec[0], (float)*(short *)(self + 0xA) / IntToFloat(rec[3]));
    if (FastDecTimer((short *)(self + 0xA)) != 0)
        part_kill(self);
}
