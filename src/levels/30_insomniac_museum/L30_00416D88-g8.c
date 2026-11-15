#include "common.h"
extern char *func_316A50(int);
extern float func_2F5508(float, float);
extern float func_2F5E58(float, float);
extern float func_2F4FC8(void *);
extern float func_321230(void);
extern void func_326C10(void *, void *, void *, float);
extern void func_2F56B0(void *, void *);
extern float func_321168(float, float);
extern void func_33A020(void *, int, int, float, float, int, int, void *, float, int);
extern float D_L30_001B1FAC __attribute__((sda));
extern int D_L30_001B1F08 __attribute__((sda)), D_L30_001B1F0C __attribute__((sda));
extern char D_L30_001A8F20[] __attribute__((sda)) NOT_SDA;
/* Spawns a museum projectile with a given velocity, points it along its flight direction and adds a trail of particles. */
char *museum_projectile_spawn(char *owner, float *velocity, void *position, int type, float scale) {
    char *moby = func_316A50(0x11EA /* moby class 4586 */);
    char *vars;
    float angle, size;
    if (moby) {
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(unsigned char *)(moby + 0x31) = 1;
        *(unsigned char *)(moby + 0xBC) = type;
        *(unsigned char *)(moby + 0x20) = 0;
        *(unsigned long long *)(moby + 0x38) = *(unsigned long long *)(owner + 0x38);
        qcopy(moby + 0x10, position);
        vars = *(char **)(moby + 0x68);
        qcopy(vars, velocity);
        *(char **)(vars + 0x10) = owner;
        *(float *)(vars + 0x14) = scale;
        *(float *)(vars + 0x20) = 0.15f;
        *(unsigned short *)(moby + 0x34) |= 0x208;
        *(float *)(moby + 0xF8) = func_2F5E58(func_2F5508(velocity[0], velocity[1]), 1.5707964897155762f);
        *(float *)(moby + 0xF0) = -func_2F5508(func_2F4FC8(velocity), velocity[2]);
        angle = func_321230();
        func_326C10(moby + 0xE0, moby + 0xE0, moby + 0xD0, angle);
        func_326C10(moby + 0xC0, moby + 0xC0, moby + 0xD0, angle);
        func_2F56B0(moby + 0xC0, moby + 0xF0);
        *(unsigned char *)(moby + 0x23) = 0x80;
        *(float *)(moby + 0x2C) = D_L30_001B1FAC;
        *(unsigned short *)(moby + 0x34) |= 0x100;
        *(int *)(vars + 0x24) = 0;
        size = func_321168(8.0f, 10.0f);
        func_33A020(moby + 0x10, 15, D_L30_001B1F08, size * 0.3f, size, 0, 10, D_L30_001A8F20, 0.0f, 0);
        func_33A020(moby + 0x10, 15, D_L30_001B1F0C, size * 0.04f, size * 0.4f, 1, -10, D_L30_001A8F20, 0.0f, 0);
    }
    return moby;
}
