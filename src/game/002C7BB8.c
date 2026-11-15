#include "common.h"
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern char *func_002B9030(int);
extern int func_002A7820(int, int);
extern unsigned char *D_001F26C8;
void func_002C7D58(char *);
/* Creates a particle that fades and changes size over its life, pulled down by gravity. Returns the new particle, or null if none are free. */
char *func_002C7BB8(char *pos, char *vel, int life, int color, int speed, int alpha, int endAlpha, float size, float endSize, float gravity, int kind)
{
    char *particle = AllocParticle(0x62);
    char *motion;
    if (particle) {
        qcopy(particle + 16, pos);
        *(int *)(particle+4) = (alpha << 24) | color;
        motion = particle+32;
        particle[9] = FloatToInt(4.0f)+64;
        particle[1] = 0;
        *(float *)(particle+12) = size;
        particle[3] = 72;
        particle[8] = RandomIntRange(0, speed*100)%255;
        particle[2] = D_001F26C8[kind];
        *(short *)(particle+10) = life;
        *(float *)(particle+32) = *(float *)vel;
        *(float *)(motion+4) = *(float *)(vel+4);
        *(float *)(motion+8) = *(float *)(vel+8);
        *(float *)(motion+12) = gravity;
        motion[21] = speed;
        *(float *)(motion+16) = (endSize-size)/IntToFloat(life);
        { int delta = (endAlpha-alpha)/life;
        motion[20] = delta; }
        *(void (**)(char *))(motion+28) = UpdateSizeChangingParticle;
        *(int *)(motion+24) = 60;
    }
    return particle;
}
