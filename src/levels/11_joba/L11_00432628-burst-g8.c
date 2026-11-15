#include "common.h"

/* Own unit: -G8 -Wa,-G32 for the colour tables' $gp reads, -frac2-zero-ti-por for the
   velocity clear. */

typedef unsigned int u128 __attribute__((mode(TI)));

/* Spark colour tables, six words each. */
extern int D_L11_001B12D0[6] __attribute__((sda));
extern int D_L11_001B12E0[6] __attribute__((sda));

/* Three four-byte ring colours: retail reads byte 0 through $gp and bytes 1-3 as absolute
   loads from the colour's own name, so each colour has both names. */
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
extern char *func_00308408(char *, char *, char *, int, float, u8, u8, u8, u8);
extern int func_00283DB8(void *, float);
extern void func_00312B70(void *, void *, int, int);
extern void func_002E5DA0(int, int, char *, int);

/* Called with a constant radius: each ring loads it afresh instead of sharing one register. */
static __inline__ void spawn_ring(char *obj, char *pos, char *velocity, float radius, int type,
                                  u8 r, u8 g, u8 b, u8 a)
{
    SpawnShockwaveRing(obj, pos, velocity, type, radius, r, g, b, a);
}

/* Bursts at pos: twelve sparks, three coloured rings, a damage ring for an owner, then the
   blast sphere and its sound. */
void func_L11_00439640(char *obj, char *pos)
{
    float velocity[4], sphere[4];
    float size, scale, damage;
    float speed;
    int i, index, first, last, life;
    char *spark;

    *(u128 *)velocity = 0;
    velocity[2] = 0.13333334f;
    damage = 4.0f;
    size = 5.0f;
    scale = 2.0f;
    for (i = 11; i >= 0; i--) {
        speed = RandomFloatRange(8.0f, 10.0f) * (1.0f / 60.0f);
        index = RandomIntBelow(6);
        first = D_L11_001B12D0[index];
        last = D_L11_001B12E0[index];
        life = RandomIntRange(15, 20);
        spark = SpawnFireworkSparkParticle(pos, velocity, first, last, scale * 400000.0f, life,
                              RandomIntRange(30, 45), 0, 0, speed * scale);
        if (spark)
            spark[3] = 0x44;
    }
    spawn_ring(obj, pos, (char *)velocity, 8.0f, 16, D_L11_001B12F0,
               D_L11_001B12F0_4[1], D_L11_001B12F0_4[2], D_L11_001B12F0_4[3]);
    spawn_ring(obj, pos, (char *)velocity, 8.0f, 22, D_L11_001B12F8,
               D_L11_001B12F8_4[1], D_L11_001B12F8_4[2], D_L11_001B12F8_4[3]);
    spawn_ring(obj, pos, (char *)velocity, 8.0f, 30, D_L11_001B1300,
               D_L11_001B1300_4[1], D_L11_001B1300_4[2], D_L11_001B1300_4[3]);
    if (obj && damage > 0.0f)
        spawn_ring(obj, pos, (char *)velocity, damage, 27, 80, 50, 50, 20);
    if (size != 0.0f) {
        qcopy(sphere, pos);
        sphere[3] = size;
        if (FastMathHelperA(sphere, 100.0f) != -1) {
            if (size > 0.0f)
                D_L11_002B6BC0.scale[0] = D_L11_002B6BC0.scale[2] = D_L11_002B6BC0.scale[1] = size;
            else
                D_L11_002B6BC0.scale[0] = D_L11_002B6BC0.scale[2] = D_L11_002B6BC0.scale[1] = 15;
            SpawnTemplateEffectMoby(&D_L11_002B6BC0, pos, 0, 0);
        }
    }
    PlaySoundFromClassBank(0, 0, obj, 0xDF7);
}
