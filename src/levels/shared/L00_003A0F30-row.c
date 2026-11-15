#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    char p0[16];
    char timer[2];
    short active;
    float value;
    float target;
    char p1[8];
    float scale;
    float pos[9];
    float vel[9];
} Particle;
extern Particle *level_get_slot_body(int, int);
extern int FastDecTimer(void *);
extern float FastAddRotations(float, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int D_L00_001A8FF0[] __attribute__((sda));

/* Moves every active beam particle along its path and counts how many are still alive. */
int beam_update_particles(char *object)
{
    float local[2][4] __attribute__((aligned(16)));
    Particle *base = level_get_slot_body(1483 /* Pulse Rifle */, *(short *)(*(char **)(object + 104) + 26));
    int i, j, k;
    int active = 0;
    for (i = 0; i < 80; i = j) {
        j = i + 1;
        if (base[i].active != 0) {
            if (FastDecTimer(base[i].timer) != 0) {
                base[i].active = 0;
            } else {
                float *scaled;
                active++;
                base[i].value = FastAddRotations(base[i].value, base[i].target);
                scaled = local[1];
                for (k = 0; k < 9; k++)
                    base[i].pos[k] += base[i].vel[k];
                *(TI128 *)local[0] = 0;
                local[0][2] = 1.0f;
                local[0][3] = 1.0f;
                if (D_L00_001A8FF0[0] != 0)
                    cam_compute_view_direction(&base[i], local[0], 1);
                FastVecScale(scaled, local[0], base[i].scale);
                FastVecAdd(&base[i], &base[i], scaled);
            }
        }
    }
    return active;
}
