#include "common.h"
extern float IntToFloat(int);
extern int FloatToInt(float);
extern char *part_alloc(int);
extern int math_random_int_range(int, int);
extern unsigned char *g_part_tex_size_changing_table;
void part_update_size_changing(char *);
/* Creates a particle that fades and changes size over its life, pulled down by gravity. Returns the new particle, or null if none are free. */
char *part_spawn_size_changing(char *pos, char *vel, int life, int color, int speed, int alpha, int endAlpha, float size, float endSize, float gravity, int kind)
{
    char *particle = part_alloc(0x62);
    char *motion;
    if (particle) {
        qcopy(particle + 16, pos);
        *(int *)(particle+4) = (alpha << 24) | color;
        motion = particle+32;
        particle[9] = FloatToInt(4.0f)+64;
        particle[1] = 0;
        *(float *)(particle+12) = size;
        particle[3] = 72;
        particle[8] = math_random_int_range(0, speed*100)%255;
        particle[2] = g_part_tex_size_changing_table[kind];
        *(short *)(particle+10) = life;
        *(float *)(particle+32) = *(float *)vel;
        *(float *)(motion+4) = *(float *)(vel+4);
        *(float *)(motion+8) = *(float *)(vel+8);
        *(float *)(motion+12) = gravity;
        motion[21] = speed;
        *(float *)(motion+16) = (endSize-size)/IntToFloat(life);
        { int delta = (endAlpha-alpha)/life;
        motion[20] = delta; }
        *(void (**)(char *))(motion+28) = part_update_size_changing;
        *(int *)(motion+24) = 60;
    }
    return particle;
}
