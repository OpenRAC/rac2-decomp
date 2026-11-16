#include "include_asm.h"
#include "common.h"

/* func_L09_003AE8C8 needs -g (its divisions keep their two-nop hazard pairs). */

typedef int TI128 __attribute__((mode(TI)));

/* The spawned projectile's state block (object + 0x68). */
typedef struct {
    char pad00[0x30];
    TI128 direction;
    char *owner;
    int pad44;
    int ticks;
    float inverseTicks, d, f, range;
    int pad5c;
    float c;
    int a, b;
} ProjectileState;

extern char *CreateMoby(int);
extern char g_hero_state_block[];
extern float g_projectile_spawn_factor __attribute__((sda));
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecLength(void *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern void projectile_init_direction(char *);
extern int PlayMobySound(int, int, char *);
extern void func_002A0F48(char *);

/* Integer arguments stay pos, owner, dir, a, b ($a0-$t0) and float arguments f, range, c, d
   ($f12-$f15); only the interleaving of the two banks is chosen. */
/* Spawns a projectile at a position flying along a direction, works out how many frames it lives and returns it. */
char *projectile_l09_spawn(void *pos, char *owner, float f, float range, float c, void *dir, int a,
                        int b, float d)
{
    char *obj = CreateMoby(0x5DE /* moby class 1502 */);

    if (obj) {
        float length, ticks, factor;
        ProjectileState *st = *(ProjectileState **)(obj + 0x68);

        *(unsigned char *)(obj + 0x30) = 255;
        *(short *)(obj + 0x34) = 256;
        *(unsigned char *)(obj + 0x20) = 0;
        qcopy(&st->direction, dir);
        qcopy(obj + 0x10, pos);
        st->range = range;
        qcopy(obj + 0xC0, &st->direction);
        FastVecCross(obj + 0xD0, obj + 0xC0, g_hero_state_block);
        vec_scale_to_length(obj + 0xD0, obj + 0xD0, -1.0f);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        length = FastVecLength(dir);
        ticks = st->range / length;
        st->ticks = FloatToInt(ticks);
        length = IntToFloat(st->ticks);
        factor = g_projectile_spawn_factor;
        st->owner = owner;
        st->f = f;
        st->a = a;
        st->b = b;
        st->inverseTicks = 1.0f / length;
        st->c = c;
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * factor;
        *(unsigned char *)(obj + 0x20) = 0;
        st->d = d;
        projectile_init_direction(obj);
        PlayMobySound(0, 0, obj);
        func_002A0F48(obj);
    }
    return obj;
}
