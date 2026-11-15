#include "common.h"

extern char *CreateMoby(int);
extern int FloatToInt(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float D_L05_001B154C __attribute__((sda));
extern float D_L05_001B1550 __attribute__((sda));
extern int D_L05_001B1554 __attribute__((sda));
extern float D_L05_001B155C __attribute__((sda));
extern float D_L05_001B1560 __attribute__((sda));
extern float D_L05_001B1514 __attribute__((sda));
extern float D_L05_001B1518 __attribute__((sda));
extern int D_L05_001B151C __attribute__((sda));
extern float D_L05_001B1524 __attribute__((sda));
extern float D_L05_001B1528 __attribute__((sda));

/* Creates a moving projectile object that travels from a position along a direction, with a lifetime counted in frames. */
char *projectile_spawn_with_target(char *pos, char *vec, int a2, char *target, int flag, int extra_param)
{
    char *projectile = CreateMoby(0x1182);

    if (projectile != 0) {
        char *vars = *(char **)(projectile + 0x68);
        float one;
        float travel_frames;
        float frame_time;
        int count;

        *(unsigned char *)(projectile + 0x30) = 0xFF;
        *(unsigned short *)(projectile + 0x32) = 0x1FF;
        *(unsigned char *)(projectile + 0x31) = 1;
        *(unsigned char *)(projectile + 0x20) = 1;
        *(int *)(vars + 0x24) = flag;
        frame_time = (flag ? D_L05_001B1518 : D_L05_001B1514) * (1.0f / 60.0f);
        travel_frames = (flag ? D_L05_001B1528 : D_L05_001B1524) / frame_time;
        one = 1.0f;
        count = FloatToInt(travel_frames);
        *(int *)(vars + 0x28) = D_L05_001B151C;
        *(int *)(vars + 0x18) = count;
        *(int *)(vars + 0x10) = a2;
        *(int *)(vars + 0x2C) = extra_param;
        *(char **)(vars + 0x20) = target;
        *(int *)(vars + 0x14) = 0;
        *(float *)(vars + 0x1C) = one / travel_frames;
        *(unsigned short *)(projectile + 0x34) = *(unsigned short *)(projectile + 0x34) | 0x100;
        qcopy(projectile + 0x10, pos);
        vec_scale_to_length(vars, vec, frame_time);
        vec_scale_to_length(projectile + 0xC0, vars, one);
        FastVecCross(projectile + 0xD0, projectile + 0xC0, target + 0xE0);
        vec_scale_to_length(projectile + 0xD0, projectile + 0xD0, one);
        FastVecCross(projectile + 0xE0, projectile + 0xD0, projectile + 0xC0);
    }
    return projectile;
}

/* Creates a second kind of moving projectile object, like the one above but without the extra value. */
char *projectile_l05_spawn(char *pos, char *vec, int a2, char *target, int flag)
{
    char *projectile = CreateMoby(0x1191);

    if (projectile != 0) {
        char *vars = *(char **)(projectile + 0x68);
        float one;
        float travel_frames;
        float frame_time;
        int count;

        *(unsigned char *)(projectile + 0x30) = 0xFF;
        *(unsigned short *)(projectile + 0x32) = 0x1FF;
        *(unsigned char *)(projectile + 0x31) = 1;
        *(unsigned char *)(projectile + 0x20) = 1;
        *(int *)(vars + 0x24) = flag;
        frame_time = (flag ? D_L05_001B1550 : D_L05_001B154C) * (1.0f / 60.0f);
        travel_frames = (flag ? D_L05_001B1560 : D_L05_001B155C) / frame_time;
        one = 1.0f;
        count = FloatToInt(travel_frames);
        *(int *)(vars + 0x28) = D_L05_001B1554;
        *(int *)(vars + 0x18) = count;
        *(int *)(vars + 0x10) = a2;
        *(char **)(vars + 0x20) = target;
        *(int *)(vars + 0x14) = 0;
        *(float *)(vars + 0x1C) = one / travel_frames;
        *(unsigned short *)(projectile + 0x34) = *(unsigned short *)(projectile + 0x34) | 0x100;
        qcopy(projectile + 0x10, pos);
        vec_scale_to_length(vars, vec, frame_time);
        vec_scale_to_length(projectile + 0xC0, vars, one);
        FastVecCross(projectile + 0xD0, projectile + 0xC0, target + 0xE0);
        vec_scale_to_length(projectile + 0xD0, projectile + 0xD0, one);
        FastVecCross(projectile + 0xE0, projectile + 0xD0, projectile + 0xC0);
    }
    return projectile;
}
