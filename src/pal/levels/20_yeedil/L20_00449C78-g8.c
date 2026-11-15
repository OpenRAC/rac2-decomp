#include "names.h"
/* func_PAL_L20_00449C78, the PAL copy of func_L20_004441D8: the same C, where the acceleration factor
 * 1/60 becomes 0.02, the two lifetimes c and d are scaled to 50 Hz and 60 becomes 50.
 * Built with -frac2-sticky-volatile-refs: qzero_nc's volatile asm keeps the delay-slot search of
 * the func_002A7878 call in the i loop from taking the loop increment.
 * func_002A8F70 is declared with the definition's own types (src/game/002A7750-records.c) and its
 * float argument fourth: the bank-preserving typed interleaving AGENTS.md permits (integer bank
 * a0-t0 and $f12 unchanged). With the float last both calls schedule the $f12 move into the jal slot;
 * computing the arguments into locals first changes nothing (v3767). */
#include "common.h"

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))

extern unsigned short **D_L20_001A9014 __attribute__((section(".sdata")));
extern unsigned short *D_L20_001FBB20[] __attribute__((nosda));
extern char *D_L20_001B3614 __attribute__((section(".sdata")));
extern char *D_L20_001B2F9C __attribute__((section(".sdata")));
extern char *D_L20_001B308C __attribute__((section(".sdata")));
extern char *D_L20_001B2FA0 __attribute__((section(".sdata")));
extern char *g_hero_moby __attribute__((nosda));
extern char D_L20_001A8F20[] __attribute__((section(".sdata")));
extern int D_L20_001B2FB8 __attribute__((sda));
extern int D_L20_001B220C __attribute__((sda));
extern int D_L20_001B2210[] MACRO_ADDR;
extern int D_L20_001B2210_gp SDATA(D_L20_001B2210);
extern float D_L20_001B2220[2] __attribute__((sda));
extern int D_L20_001B222C __attribute__((sda));
extern int D_L20_001B2230[] MACRO_ADDR;
extern int D_L20_001B2230_gp SDATA(D_L20_001B2230);
extern float D_L20_001B2240[] MACRO_ADDR;
extern float D_L20_001B2240_gp[] SDATA(D_L20_001B2240);
extern int D_L20_001B2248 __attribute__((sda));
extern float D_L20_001B2250[] MACRO_ADDR;
extern float D_L20_001B2250_gp SDATA(D_L20_001B2250);
extern float D_L20_001B2BE8 __attribute__((sda));

extern void PlayMobySound(int, int, void *);
extern void moby_mark_spawned(void *);
extern void vec_store_helper(void *);
extern void vec_clear_128(void *);
extern void transform_vector(void *, void *, void *);
extern float math_fabs(float);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int FastTweenColor(int, int, float);
extern char *moby_get_private_value_0(void *);
extern void part_queue_impact_effect(char *object, int kind, int bits, float strength, void *position, void *vector);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern char *func_PAL_L20_0044E630(char *, char *, char *, char *);

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Vector;

typedef struct {
    char pad0[0x21C];
    int damageGroup0; /* 0x21C */
    char pad220[4];
    int groups[3]; /* 0x224 */
    int matrixIndex; /* 0x230 */
    char pad234[8];
    int damageGroup1; /* 0x23C */
    char pad240[0x1618];
    int groupIndex; /* 0x1858 */
} State;

void func_PAL_L20_00449C78(char *self) {
    State *s = (State *)P(self, 0x68);
    char *selfPos;
    char *obj;
    float height;
    float scale;
    Vector pos;
    Vector vel;
    Vector acc;
    int a;
    int b;
    int c;
    int d;
    float sample;

    PlayMobySound(17, 0, self);
    {
        unsigned short *list = D_L20_001A9014[s->groups[s->groupIndex]];

        if (list != 0) {
            do {
                char *info = D_L20_001B3614 + ((*list & 0x7FFF) << 5);

                if (info == 0) {
                    break;
                }
                info[0x1E] |= 4;
                list++;
                if (list == 0) {
                    break;
                }
            } while (*(short *)(list - 1) >= 0 || list == D_L20_001A9014[s->groups[s->groupIndex]]);
        }
    }
    s->groupIndex++;
    selfPos = self + 0x10;
    obj = D_L20_001B2F9C;
    if (obj <= D_L20_001B2FA0 && (unsigned char)obj[0x20] != 255) {
        char *bound;

        for (;;) {
            unsigned short type = *(unsigned short *)(obj + 0xAA);

            if ((unsigned short)(type - 0x1233) < 2) {
                goto hit;
            }
            if ((short)type == 0x1231) {
                goto hit;
            }
            if ((short)type == 0x1232) {
                goto hit;
            }
            if ((short)type != 0x1357) {
                bound = D_L20_001B2FA0;
                goto nextObject;
            }
        hit:
            if (!(math_fabs(F(self, 0x18) - F(obj, 0x18)) < 10.0f)) {
                bound = D_L20_001B2FA0;
                goto nextObject;
            }
            moby_mark_spawned(obj);
            bound = D_L20_001B2FA0;
        nextObject:
            obj += 256;
            if (bound < obj) {
                goto objectsDone;
            }
            if ((unsigned char)obj[0x20] != 255) {
                continue;
            }
            goto objectsDone;
        }
    }
objectsDone:
    {
        unsigned short *list;
        float damage = 0.0f;

        for (list = D_L20_001FBB20[s->damageGroup0];
             (s->damageGroup0 & 0xFF) != 0xFF && s->damageGroup0 <= D_L20_001B2FB8 && list != 0 &&
             ((list != 0 && (short)list[-1] >= 0) || list == D_L20_001FBB20[s->damageGroup0]);
             list++) {
            char *e = D_L20_001B2F9C + ((*list & 0x7FFF) << 8);

            if (e == 0) {
                break;
            }
            if ((*(unsigned short *)(e + 0x34) ^ 1) & 1) {
                if (damage == 0.0f) {
                    char *info = moby_get_private_value_0(e);

                    if (info == 0) {
                        continue;
                    }
                    damage = (float)*(short *)(info + 4) * 0.25f;
                }
                part_queue_impact_effect(e, (int)g_hero_moby, 0x10000, damage, e + 0x10, D_L20_001A8F20);
            }
        }
    }
    {
        unsigned short *list;
        float damage = 0.0f;

        for (list = D_L20_001FBB20[s->damageGroup1];
             (s->damageGroup1 & 0xFF) != 0xFF && s->damageGroup1 <= D_L20_001B2FB8 && list != 0 &&
             ((list != 0 && (short)list[-1] >= 0) || list == D_L20_001FBB20[s->damageGroup1]);
             list++) {
            char *e = D_L20_001B2F9C + ((*list & 0x7FFF) << 8);

            if (e == 0) {
                break;
            }
            if ((*(unsigned short *)(e + 0x34) ^ 1) & 1) {
                if (damage == 0.0f) {
                    char *info = moby_get_private_value_0(e);

                    if (info == 0) {
                        continue;
                    }
                    damage = (float)*(short *)(info + 4) * 0.25f;
                }
                part_queue_impact_effect(e, (int)g_hero_moby, 0x10000, damage, e + 0x10, D_L20_001A8F20);
            }
        }
    }
    sample = coll_probe_ground_height_below(selfPos, 0, 0.5f) - 2.0f;
    height = F(self, 0x18) - 0.5f;
    D_L20_001B2BE8 = sample;
    {
        int i;

        for (i = 0; i < D_L20_001B220C; i++) {
            vec_store_helper(&pos);
            pos.f[0] = math_random_float_range(-1.0f, 1.0f);
            pos.f[1] = math_random_float_range(-1.0f, 1.0f);
            transform_vector(&pos, &pos, D_L20_001B308C + s->matrixIndex * 128);
            pos.f[2] = height + math_random_float_range(-0.5f, 0.5f);
            sample = math_random_float_range(0.0f, 1.0f);
            a = FastTweenColor(D_L20_001B2210_gp, D_L20_001B2210[1], sample);
            sample = math_random_float_range(0.0f, 1.0f);
            b = FastTweenColor(D_L20_001B2210[2], D_L20_001B2210[3], sample);
            scale = D_L20_001B2220[math_random_int_below(2)];
            vec_clear_128(&vel);
            vel.f[3] = scale;
            vec_clear_128(&acc);
            acc.f[3] = scale;
            acc.f[2] = math_random_float_range(D_L20_001B2240_gp[0], D_L20_001B2240[1]) * 0.020000001f;
            c = (math_random_int_range(1, D_L20_001B2230_gp) * 5 + 2) / 6;
            d = (math_random_int_range(D_L20_001B2230[1], D_L20_001B2230[2]) * 5 + 2) / 6;
            part_spawn_trail(&pos, &vel, &acc, a, b, c, d, 50, D_L20_001B222C);
        }
    }
    {
        int i;

        for (i = 0; i < D_L20_001B2248; i++) {
            vec_store_helper(&pos);
            pos.f[0] = math_random_float_range(-1.0f, 1.0f);
            pos.f[1] = math_random_float_range(-1.0f, 1.0f);
            transform_vector(&pos, &pos, D_L20_001B308C + s->matrixIndex * 128);
            pos.f[2] = height + math_random_float_range(-0.5f, 0.5f);
            qzero_nc(&vel);
            vel.f[2] = math_random_angle();
            qzero_nc(&acc);
            acc.f[2] = math_random_float_range(D_L20_001B2240_gp[4], D_L20_001B2250[1]) * 0.020000001f;
            func_PAL_L20_0044E630(self, (char *)&pos, (char *)&vel, (char *)&acc);
        }
    }
}
