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
extern Particle *func_L00_0032A088(int, int);
extern int func_00282978(void *);
extern float func_00283B98(float, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int D_L00_001A8FF0[] __attribute__((sda));

int func_L00_003A87D8(char *object)
{
    float local[2][4] __attribute__((aligned(16)));
    Particle *base = func_L00_0032A088(1483, *(short *)(*(char **)(object + 104) + 26));
    int i, j, k;
    int active = 0;
    for (i = 0; i < 80; i = j) {
        j = i + 1;
        if (base[i].active != 0) {
            if (func_00282978(base[i].timer) != 0) {
                base[i].active = 0;
            } else {
                float *scaled;
                active++;
                base[i].value = func_00283B98(base[i].value, base[i].target);
                scaled = local[1];
                for (k = 0; k < 9; k++)
                    base[i].pos[k] += base[i].vel[k];
                *(TI128 *)local[0] = 0;
                local[0][2] = 1.0f;
                local[0][3] = 1.0f;
                if (D_L00_001A8FF0[0] != 0)
                    func_002AFFD8(&base[i], local[0], 1);
                func_00282D30(scaled, local[0], base[i].scale);
                func_00282CC0(&base[i], &base[i], scaled);
            }
        }
    }
    return active;
}
