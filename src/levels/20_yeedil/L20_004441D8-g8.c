/* func_L20_004441D8. Built with -frac2-sticky-volatile-refs: qzero_nc's volatile asm keeps the
 * delay-slot search of the func_002A7878 call in the i loop from taking the loop increment.
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
extern char *D_0018C0B0 __attribute__((nosda));
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

extern void func_002E5CF8(int, int, void *);
extern void func_0029F338(void *);
extern void func_00282C90(void *);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00282C48(float);
extern float func_002A89A8(void *, int, float);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_00283D38(int, int, float);
extern char *func_002AB1F0(void *);
extern void func_002A8F70(char *object, int kind, int bits, float strength, void *position, void *vector);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern char *func_L20_00448A18(char *, char *, char *, char *);

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

/* Runs the big enemy death. It stops its sounds, removes nearby leftovers, damages everything in its two groups and bursts out sparks and debris. */
void func_L20_004441D8(char *self) {
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

            if ((unsigned short)(type - 0x1233 /* moby classes 4659, 4660 */) < 2) {
                goto hit;
            }
            if ((short)type == 0x1231 /* moby class 4657 */) {
                goto hit;
            }
            if ((short)type == 0x1232 /* moby class 4658 */) {
                goto hit;
            }
            if ((short)type != 0x1357 /* moby class 4951 */) {
                bound = D_L20_001B2FA0;
                goto nextObject;
            }
        hit:
            if (!(FloatAbs(F(self, 0x18) - F(obj, 0x18)) < 10.0f)) {
                bound = D_L20_001B2FA0;
                goto nextObject;
            }
            MarkMobySpawned(obj);
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
                    char *info = GetMobyPrivateValue0(e);

                    if (info == 0) {
                        continue;
                    }
                    damage = (float)*(short *)(info + 4) * 0.25f;
                }
                QueueImpactEffect(e, (int)gHeroMoby_0018C0B0, 0x10000, damage, e + 0x10, D_L20_001A8F20);
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
                    char *info = GetMobyPrivateValue0(e);

                    if (info == 0) {
                        continue;
                    }
                    damage = (float)*(short *)(info + 4) * 0.25f;
                }
                QueueImpactEffect(e, (int)gHeroMoby_0018C0B0, 0x10000, damage, e + 0x10, D_L20_001A8F20);
            }
        }
    }
    sample = ProbeGroundHeightBelow(selfPos, 0, 0.5f) - 2.0f;
    height = F(self, 0x18) - 0.5f;
    D_L20_001B2BE8 = sample;
    {
        int i;

        for (i = 0; i < D_L20_001B220C; i++) {
            StoreVectorHelper(&pos);
            pos.f[0] = RandomFloatRange(-1.0f, 1.0f);
            pos.f[1] = RandomFloatRange(-1.0f, 1.0f);
            transform_vector(&pos, &pos, D_L20_001B308C + s->matrixIndex * 128);
            pos.f[2] = height + RandomFloatRange(-0.5f, 0.5f);
            sample = RandomFloatRange(0.0f, 1.0f);
            a = FastTweenColor(D_L20_001B2210_gp, D_L20_001B2210[1], sample);
            sample = RandomFloatRange(0.0f, 1.0f);
            b = FastTweenColor(D_L20_001B2210[2], D_L20_001B2210[3], sample);
            scale = D_L20_001B2220[RandomIntBelow(2)];
            ClearVector128(&vel);
            vel.f[3] = scale;
            ClearVector128(&acc);
            acc.f[3] = scale;
            acc.f[2] = RandomFloatRange(D_L20_001B2240_gp[0], D_L20_001B2240[1]) * 0.0166666675f;
            c = RandomIntRange(1, D_L20_001B2230_gp);
            d = RandomIntRange(D_L20_001B2230[1], D_L20_001B2230[2]);
            SpawnTrailParticle_002BAA28(&pos, &vel, &acc, a, b, c, d, 60, D_L20_001B222C);
        }
    }
    {
        int i;

        for (i = 0; i < D_L20_001B2248; i++) {
            StoreVectorHelper(&pos);
            pos.f[0] = RandomFloatRange(-1.0f, 1.0f);
            pos.f[1] = RandomFloatRange(-1.0f, 1.0f);
            transform_vector(&pos, &pos, D_L20_001B308C + s->matrixIndex * 128);
            pos.f[2] = height + RandomFloatRange(-0.5f, 0.5f);
            qzero_nc(&vel);
            vel.f[2] = RandomAngle();
            qzero_nc(&acc);
            acc.f[2] = RandomFloatRange(D_L20_001B2240_gp[4], D_L20_001B2250[1]) * 0.0166666675f;
            SpawnDebrisPiece_L20(self, (char *)&pos, (char *)&vel, (char *)&acc);
        }
    }
}
