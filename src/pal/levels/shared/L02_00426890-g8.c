#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern int ref_L02_00422270_00[6] __attribute__((sda));
extern int ref_L02_00422270_01[6] __attribute__((sda));
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
extern char *func_PAL_003096D0(char *, char *, char *, int, float, u8, u8, u8, u8);
/* Called with a constant radius: each ring loads it afresh instead of sharing one register. */
static __inline__ void spawn_ring(char *obj, char *pos, char *velocity, float radius, int type,
                                  u8 r, u8 g, u8 b, u8 a)
{
    func_PAL_003096D0(obj, pos, velocity, type, radius, r, g, b, a);
}

/* Bursts at pos: six sparks, three coloured rings, then a damage ring for an owner. */
void func_PAL_L02_00427320(char *obj, char *pos)
{
    float velocity[4];
    float scale, damage;
    float speed;
    int i, index, first, last, life;
    char *spark;

    *(u128 *)velocity = 0;
    velocity[2] = 0.16000001f;
    damage = 2.0f;
    scale = 1.0f;
    for (i = 0; i < 6; i++) {
        speed = func_002A7878(8.0f, 10.0f) * (0.020000001f);
        index = func_002A77E0(6);
        first = ref_L02_00422270_00[index];
        last = ref_L02_00422270_01[index];
        life = func_002A7820(12, 17);
        spark = func_002BBCB0(pos, velocity, first, last, scale * 400000.0f, life,
                              func_002A7820(25, 37), 0, 0, speed * scale);
        if (spark)
            spark[3] = 0x44;
    }
    spawn_ring(obj, pos, (char *)velocity, 4.0f, 13, ref_L02_00422270_02,
               ref_L02_00422270_05[1], ref_L02_00422270_05[2], ref_L02_00422270_05[3]);
    spawn_ring(obj, pos, (char *)velocity, 4.0f, 18, ref_L02_00422270_03,
               ref_L02_00422270_06[1], ref_L02_00422270_06[2], ref_L02_00422270_06[3]);
    spawn_ring(obj, pos, (char *)velocity, 4.0f, 25, ref_L02_00422270_04,
               ref_L02_00422270_07[1], ref_L02_00422270_07[2], ref_L02_00422270_07[3]);
    if (obj && damage > 0.0f)
        spawn_ring(obj, pos, (char *)velocity, damage, 22, 80, 50, 50, 20);
}
