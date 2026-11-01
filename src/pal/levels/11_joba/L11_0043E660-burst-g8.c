#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern int D_L11_001B12D0[6] __attribute__((sda));
extern int D_L11_001B12E0[6] __attribute__((sda));
extern u8 D_L11_001B12F0 __attribute__((sda));
extern u8 D_L11_001B12F8 __attribute__((sda));
extern u8 D_L11_001B1300 __attribute__((sda));
extern u8 D_L11_001B12F0_4[] MACRO_ADDR;
extern u8 D_L11_001B12F8_4[] MACRO_ADDR;
extern u8 D_L11_001B1300_4[] MACRO_ADDR;
typedef struct {
    char pad[0x20];
    float scale[3];
} BurstSphere;
extern BurstSphere D_L11_002B6BC0;
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern char *func_002BBCB0(void *, void *, int, int, float, int, int, int, int, float);
extern char *func_PAL_003096D0(char *, char *, char *, int, float, u8, u8, u8, u8);
extern int func_00283DB8(void *, float);
extern void func_00312B70(void *, void *, int, int);
extern void func_002E5DA0(int, int, char *, int);
/* Called with a constant radius: each ring loads it afresh instead of sharing one register. */
static __inline__ void spawn_ring(char *obj, char *pos, char *velocity, float radius, int type,
                                  u8 r, u8 g, u8 b, u8 a)
{
    func_PAL_003096D0(obj, pos, velocity, type, radius, r, g, b, a);
}

/* Bursts at pos: twelve sparks, three coloured rings, a damage ring for an owner, then the
   blast sphere and its sound. */
void func_PAL_L11_0043EBD0(char *obj, char *pos)
{
    float velocity[4], sphere[4];
    float size, scale, damage;
    float speed;
    int i, index, first, last, life;
    char *spark;

    *(u128 *)velocity = 0;
    velocity[2] = 0.16000001f;
    damage = 4.0f;
    size = 5.0f;
    scale = 2.0f;
    for (i = 11; i >= 0; i--) {
        speed = func_002A7878(8.0f, 10.0f) * (0.020000001f);
        index = func_002A77E0(6);
        first = D_L11_001B12D0[index];
        last = D_L11_001B12E0[index];
        life = func_002A7820(12, 17);
        spark = func_002BBCB0(pos, velocity, first, last, scale * 400000.0f, life,
                              func_002A7820(25, 37), 0, 0, speed * scale);
        if (spark)
            spark[3] = 0x44;
    }
    spawn_ring(obj, pos, (char *)velocity, 8.0f, 13, D_L11_001B12F0,
               D_L11_001B12F0_4[1], D_L11_001B12F0_4[2], D_L11_001B12F0_4[3]);
    spawn_ring(obj, pos, (char *)velocity, 8.0f, 18, D_L11_001B12F8,
               D_L11_001B12F8_4[1], D_L11_001B12F8_4[2], D_L11_001B12F8_4[3]);
    spawn_ring(obj, pos, (char *)velocity, 8.0f, 25, D_L11_001B1300,
               D_L11_001B1300_4[1], D_L11_001B1300_4[2], D_L11_001B1300_4[3]);
    if (obj && damage > 0.0f)
        spawn_ring(obj, pos, (char *)velocity, damage, 22, 80, 50, 50, 20);
    if (size != 0.0f) {
        qcopy(sphere, pos);
        sphere[3] = size;
        if (func_00283DB8(sphere, 100.0f) != -1) {
            if (size > 0.0f)
                D_L11_002B6BC0.scale[0] = D_L11_002B6BC0.scale[2] = D_L11_002B6BC0.scale[1] = size;
            else
                D_L11_002B6BC0.scale[0] = D_L11_002B6BC0.scale[2] = D_L11_002B6BC0.scale[1] = 15;
            func_00312B70(&D_L11_002B6BC0, pos, 0, 0);
        }
    }
    func_002E5DA0(0, 0, obj, 0xDF7);
}
