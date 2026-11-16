#include "include_asm.h"

#include "common.h"
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern unsigned char *part_spawn_spinning_spark_pal(void *, float, float, float, int, void *, float, int, int);

/* Spawns three particle bursts at the object. The second burst updates the first
 * particle's header, as retail does. */
void part_spawn_three_bursts_pal(unsigned char *moby)
{
    float vel[4], pos[4];
    float one = 1.0f;
    int n;
    unsigned char *first, *second, *third;
    unsigned char *particle1, *particle2, *particle3;

    vel[0] = 0.0f;
    vel[1] = -0.5f;
    vel[2] = 0.0f;
    vel[3] = one;
    n = math_random_int_below(16);
    if (math_random_int_below(2)) {
        n = -n;
    }
    qcopy(pos, moby + 0x10);
    first = part_spawn_spinning_spark_pal(pos, 0.1f, 1.0f, 0.9f, n, vel, 630000.0f, 0xDF204080, 0);
    if (first) {
        particle1 = first + 0x20;
        *(unsigned short *)(first + 0xA) = 21;
        first[9] = FloatToInt(4.0f) + 112;
        *(int *)(particle1 + 4) = 2;
        particle1[0xA] = 0xDF;
        particle1[0xB] = first[0xA];
    }
    second = part_spawn_spinning_spark_pal(pos, 0.1f, 1.0f, 0.9f, n, vel, 630000.0f, 0xDF204080, 0);
    if (second) {
        particle2 = second + 0x20;
        *(unsigned short *)(first + 0xA) = 21;
        first[9] = FloatToInt(4.0f) + 112;
        *(int *)(particle2 + 4) = 2;
        particle2[0xA] = 0xDF;
        particle2[0xB] = first[0xA];
    }
    third = part_spawn_spinning_spark_pal(pos, 0.05f, 1.0f, 0.97f, 16, vel, 315000.0f, 0xDFFFFFFF, 0);
    if (third) {
        int value;
        particle3 = third + 0x20;
        value = FloatToInt(4.0f);
        *(unsigned short *)(third + 0xA) = 29;
        third[9] = value + 112;
        third[8] = math_random_int_below(255);
        *(int *)(particle3 + 4) = 2;
        particle3[0xA] = 0xDF;
        particle3[0xB] = first[0xA];
    }
}

