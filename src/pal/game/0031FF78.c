#include "include_asm.h"
#include "names.h"

extern void F5a19df7a_FUN_002FC560(unsigned int a, unsigned long b);
extern void F5a19df7a_FUN_0031E2A0(char *p);
extern void F5a19df7a_FUN_0031E560(char *p);
extern int F5a19df7a_FUN_002A7820(int a, int b);
extern float F5a19df7a_FUN_002A7940(void);
extern void F5a19df7a_FUN_0031EB00(char *a, int b, float e, char *c, float f, int d, int g);

/* Spawns a burst of glowing sparks at the object. */
void part_spawn_spark_burst_pal(char *moby)
{
    char *position;
    char *data;
    char *alpha;
    float scale;
    float angle;

    position = moby + 16;
    data = *(char **)(moby + 104);
    F5a19df7a_FUN_002FC560(0x47, 0x53001UL);
    F5a19df7a_FUN_0031E2A0(moby);
    F5a19df7a_FUN_0031E560(moby);

    scale = *(float *)(data + 24);
    scale = scale * 0.5f;
    alpha = F5a19df7a_FUN_002A7820(80, 96);
    angle = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(position, 0x103080, scale, alpha, angle, 49, 2);

    scale = *(float *)(data + 24);
    scale = scale * 3.00000011920928955078125e-01f;
    alpha = F5a19df7a_FUN_002A7820(80, 96);
    angle = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(position, 0xFFFFFF, scale, alpha, angle, 49, 2);

    scale = *(float *)(data + 24);
    scale = scale * 6.99999988079071044921875e-01f;
    alpha = F5a19df7a_FUN_002A7820(8, 22);
    angle = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(position, 0x803010, scale, alpha, angle, 11, 2);

    scale = *(float *)(data + 24);
    scale = scale * 4.49999988079071044921875e-01f;
    alpha = F5a19df7a_FUN_002A7820(32, 64);
    angle = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(position, 0x803010, scale, alpha, angle, 11, 2);

    F5a19df7a_FUN_002FC560(0x47, 0x5360bUL);
}

