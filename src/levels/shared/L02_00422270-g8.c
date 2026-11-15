#include "common.h"

/* Own unit: -G8 -Wa,-G32 for the colour tables' $gp reads, -frac2-zero-ti-por for the
   velocity clear (as func_L11_00439640, whose burst this is a smaller copy of). */

typedef unsigned int u128 __attribute__((mode(TI)));

/* Spark colour tables, six words each; their place differs between levels 02 and 11. */
extern int ref_L02_00422270_00[6] __attribute__((sda));
extern int ref_L02_00422270_01[6] __attribute__((sda));

/* Three four-byte ring colours: retail reads byte 0 through $gp and bytes 1-3 as absolute
   loads, so each colour has both names (as in func_L11_00439640). */
extern u8 ref_L02_00422270_02 __attribute__((sda));
extern u8 ref_L02_00422270_03 __attribute__((sda));
extern u8 ref_L02_00422270_04 __attribute__((sda));
extern u8 ref_L02_00422270_05[] MACRO_ADDR;
extern u8 ref_L02_00422270_06[] MACRO_ADDR;
extern u8 ref_L02_00422270_07[] MACRO_ADDR;

extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern char *func_002BBCB0(void *, void *, int, int, float, int, int, int, int, float);
extern char *func_00308408(char *, char *, char *, int, float, u8, u8, u8, u8);

/* Called with a constant radius: each ring loads it afresh instead of sharing one register. */
static __inline__ void spawn_ring(char *obj, char *pos, char *velocity, float radius, int type,
                                  u8 r, u8 g, u8 b, u8 a)
{
    SpawnShockwaveRing(obj, pos, velocity, type, radius, r, g, b, a);
}

/* Bursts at pos: six sparks, three coloured rings, then a damage ring for an owner. */
void func_L02_00422270(char *obj, char *pos)
{
    float velocity[4];
    float scale, damage;
    float speed;
    int i, index, first, last, life;
    char *spark;

    *(u128 *)velocity = 0;
    velocity[2] = 0.13333334f;
    damage = 2.0f;
    scale = 1.0f;
    for (i = 0; i < 6; i++) {
        speed = RandomFloatRange(8.0f, 10.0f) * (1.0f / 60.0f);
        index = RandomIntBelow(6);
        first = ref_L02_00422270_00[index];
        last = ref_L02_00422270_01[index];
        life = RandomIntRange(15, 20);
        spark = SpawnFireworkSparkParticle(pos, velocity, first, last, scale * 400000.0f, life,
                              RandomIntRange(30, 45), 0, 0, speed * scale);
        if (spark)
            spark[3] = 0x44;
    }
    spawn_ring(obj, pos, (char *)velocity, 4.0f, 16, ref_L02_00422270_02,
               ref_L02_00422270_05[1], ref_L02_00422270_05[2], ref_L02_00422270_05[3]);
    spawn_ring(obj, pos, (char *)velocity, 4.0f, 22, ref_L02_00422270_03,
               ref_L02_00422270_06[1], ref_L02_00422270_06[2], ref_L02_00422270_06[3]);
    spawn_ring(obj, pos, (char *)velocity, 4.0f, 30, ref_L02_00422270_04,
               ref_L02_00422270_07[1], ref_L02_00422270_07[2], ref_L02_00422270_07[3]);
    if (obj && damage > 0.0f)
        spawn_ring(obj, pos, (char *)velocity, damage, 27, 80, 50, 50, 20);
}
