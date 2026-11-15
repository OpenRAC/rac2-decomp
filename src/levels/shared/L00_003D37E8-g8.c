#include "include_asm.h"
#include "common.h"

/* func_L00_003DC2D0 is matched in its own unit, src/levels/shared/L00_003DC2D0.c (default flags). */

extern int D_L00_001B043C __attribute__((sda));

extern int D_L00_001B2B44 __attribute__((sda));

/* Returns 1 when the tracked object exists and is in one of its three active states (5 to 7). */
int func_L00_003DE260(void)
{
    char *tracked = (char *)gSpiderBotMoby;

    if (tracked == 0)
        return 0;
    return (unsigned int)((unsigned char)tracked[0x20] - 5) < 3;
}

/* Returns the tracked object's flag value, or 0 when there is no tracked object. */
int func_L00_003DF108(void)
{
    if (gSpiderBotMoby == 0)
        return 0;
    return D_L00_001B2B44;
}

extern void func_L00_003B8138(void);

/* Writes the object's state byte (7 when arg0 is zero, 5 otherwise), lets the shared
 * updater run, then writes the caller's value in the object's slot - 10 when it is -1. */
void func_L00_003DF6B0(int useFirstState, int slotValue)
{
    char *tracked = (char *)gSpiderBotMoby;
    int value = slotValue;
    char *vars;

    if (tracked == 0)
        return;
    vars = *(char **)(tracked + 0x68);
    if (useFirstState != 0)
        tracked[0x20] = 5;
    else
        tracked[0x20] = 7;
    SetActiveHelperObjectFlag();
    if (value != -1)
        *(int *)(vars + 0x20) = value;
    else
        *(int *)(vars + 0x20) = 10;
}

extern int D_L00_001B19C8[] __attribute__((sda));

extern char *D_L00_001B1EA8[] __attribute__((sda));

extern float D_L00_001B0430 __attribute__((sda));

extern float func_002EE2B0(char *a, char *b);

extern void func_00381F80(char *a, char *b);

/* walks the object list once the shared flag is set, stopping at either tracked state and
   otherwise acting on the entries whose handle reports type 0x13 */
/* Looks for other objects of the same kind that are close to the target and passes them to a helper. */
void func_L00_003DF030(char *target)
{
    char *entry;

    if ((gFrameCounter_L00[0] & 1) == 0)
        return;

    for (entry = D_L00_001B1EA8[0]; entry != 0; entry = *(char **)(entry + 40)) {
        unsigned char state = *(unsigned char *)(entry + 32);

        if (state == 0xFE)
            return;
        if (state == 0xFD)
            return;
        if (entry == 0 || *(int *)(entry + 36) == 0 || *(short *)(*(int *)(entry + 36) + 70) != 0x13)
            continue;
        if (func_002EE2B0(entry + 16, target + 16) < D_L00_001B0430)
            func_00381F80(entry, target);
    }
}

/* A moby's update distance (0x30) and draw distance (0x32), as in RAC1's moby layout. */
struct BFObject {
    char pad[0x30];
    unsigned char field_30;
    unsigned char field_31;
    unsigned short field_32;
};

extern char *ref_L00_003DBF50_00(int);
extern float ref_L00_003DBF50_01(void);
extern float ref_L00_003DBF50_02(float, float);
extern int ref_L00_003DBF50_03 SDATA(ref_L00_003DBF50_03);
extern char *ref_L00_003DBF50_04;
extern char *ref_L00_003DBF50_05;
extern char *ref_L00_003DBF50_06;
extern char *ref_L00_003DBF50_07(char *);
extern void ref_L00_003DBF50_08(void);
/* The resident block at 0x189E20 (hero position at +0x80, hero moby at +0x2290). */
extern struct BFPlayer { char pad[0xbf8]; char *target; } D_00189E20 NOT_SDA;
extern float ref_L00_003DBF50_10(char *);
extern void ref_L00_003DBF50_11(char *, char *, char *, float);
extern void ref_L00_003DBF50_12(char *, char *);
extern float ref_L00_003DBF50_13 SDATA(ref_L00_003DBF50_13);
extern float ref_L00_003DBF50_14 SDATA(ref_L00_003DBF50_14);
extern void ref_L00_003DBF50_15(void *, void *, float);
extern int ref_L00_003DBF50_16(char *, float, float, float, int);

/* Spawns moby class 0xB2E at pos for parent and sets its state up (the three shared buffers
 * on first use), hands dir to the target record at D_00189E20 + 0xBF8 when there is one,
 * and passes dir with a random spread and a random speed through ref_L00_003DBF50_15. */
/* Creates a small projectile for the parent, aimed with a little random spread. */
char *func_L00_003DBF50(char *parent, int arg, char *pos, char *dir)
{
    float velocity[4];
    char *object = ref_L00_003DBF50_00(0xb2e /* moby class 2862 */);
    char *state;
    float length;

    if (object) {
        object[0x20] = 0;
        state = *(char **)(object + 0x68);
        ((struct BFObject *)object)->field_30 = 255;
        ((struct BFObject *)object)->field_32 = 255;
        *(float *)(state + 0x64) = ref_L00_003DBF50_01();
        *(float *)(state + 0x68) = ref_L00_003DBF50_02(0.3723369836807251f, 0.6283186078071594f);
        *(int *)(state + 0x74) = *(short *)(parent + 0xaa);
        *(int *)(state + 0x7c) = 0;
        qcopy(object + 0x10, pos);
        *(float *)(object + 0x2c) = ref_L00_003DBF50_02(0.01f, 0.0125f);
        *(unsigned short *)(object + 0x34) |= 0x100;
        *(int *)(object + 0x78) = 0x7f4080ff;
        *(int *)(state + 0x70) = arg;
        {
            char *parentState = *(char **)(parent + 0x68);

            if (!ref_L00_003DBF50_03) {
                char *buffer = *(char **)(parentState + 8);

                ref_L00_003DBF50_04 = buffer;
                buffer = ref_L00_003DBF50_07(buffer + 0x100);
                ref_L00_003DBF50_05 = buffer;
                buffer = ref_L00_003DBF50_07(buffer + 0x4b00);
                ref_L00_003DBF50_06 = buffer;
                ref_L00_003DBF50_07(buffer + 0xa0);
                ref_L00_003DBF50_08();
                ref_L00_003DBF50_03 = 1;
            }
        }
        if (gHeroState.target) {
            length = ref_L00_003DBF50_10(dir);
            if (length == 0.0f)
                length = 1.0f;
            ref_L00_003DBF50_11(gHeroState.target, pos, dir, length);
            qcopy(state, dir);
        } else {
            ref_L00_003DBF50_12(object, state);
        }
        qcopy(velocity, dir);
        velocity[0] += ref_L00_003DBF50_02(-0.15f, 0.15f);
        velocity[1] += ref_L00_003DBF50_02(-0.15f, 0.15f);
        length = ref_L00_003DBF50_02(ref_L00_003DBF50_13 * (1.0f / 60.0f),
                                     ref_L00_003DBF50_14 * (1.0f / 60.0f));
        ref_L00_003DBF50_15(velocity, velocity, length * 0.5f);
        *(int *)(state + 0x6c) = 96;
        *(int *)(state + 0x60) = 680;
        *(int *)(state + 0x78) = ref_L00_003DBF50_16(object, 1.0f, 1.0f, 1.0f, 0);
    }
    return object;
}


extern float func_00283B98(float, float);
extern void func_00282C88(void *);
extern void func_002833F0(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A8C00(void *, int, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern int func_002A8C28(int, float, void *, int, float, float, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002AD330(void *, int, void *, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void func_002AD0E0(void *, int, void *, void *, void *, void *);
extern void func_002AD250(void *, int, void *, void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int,
                          float, int, int, int, int, int);
extern void func_0029F338(void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L00_003DFDC0(void *);
extern int D_L00_001BF218 NOT_SDA;
extern int D_L00_001B0518 __attribute__((sda));
extern char D_L00_001A8F20[] MACRO_ADDR;

/* state 0: advances the object by its data's velocity; a collision deals damage and destroys it unless
   D_L00_001BF218 equals the data's type, otherwise it spawns three trail particles and grows its scale
   factor; state 1: spawns an explosion and deletes the object */
/* Per-frame update of a small flying projectile. It moves, damages what it hits, leaves a smoke trail, and explodes when it hits something. */
void func_L00_003DF710(char *object)
{
    float scale[4];
    float next[4];
    char query[48];
    float velocity[4];
    float zero[4];
    float pos[4];
    char *vars = *(char **)(object + 0x68);
    float size0, size1, size2, spread;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(float *)(vars + 0x18) = FastAddRotations(*(float *)(vars + 0x18), *(float *)(vars + 0x1c));
        ClearVector128(scale);
        scale[1] = *(float *)(vars + 0x18) * 0.25f;
        scale[0] = *(float *)(vars + 0x18) * 0.5f;
        scale[2] = *(float *)(vars + 0x18);
        euler_rotation_basis(object + 0xc0, scale);
        FastVecAdd(next, object + 0x10, vars);
        make_hit_descriptor(query, *(int *)(vars + 0x10), 1, vars, *(float *)(vars + 0x14));
        *(unsigned short *)(query + 0x1a) = *(unsigned short *)(object + 0xaa);
        if (CollLine(object + 0x10, next, 0, object, query) || TestPointAgainstCollision(object + 0x10, 0, object, 0.3f)) {
            if (D_L00_001BF218) {
                if (D_L00_001BF218 != *(int *)(vars + 0x10)) {
                    SweepCollisionFromObject(*(int *)(vars + 0x10), 0.3f, object + 0x10, 0x10001, *(float *)(vars + 0x14), 0, 0, 1, 0);
                    SetMobyState(object, 1, -1);
                    return;
                }
            } else {
                SweepCollisionFromObject(*(int *)(vars + 0x10), 0.3f, object + 0x10, 0x10001, *(float *)(vars + 0x14), 0, 0, 1, 0);
                SetMobyState(object, 1, -1);
                return;
            }
        }
        qcopy(object + 0x10, next);
        FastVecScale(velocity, vars, -0.5f);
        ClearVector128(zero);
        if (*(int *)(vars + 0x24)) {
            TransformPointByMobyAttachment(object, *(int *)(vars + 0x24), object + 0x10, pos);
            FastVecAdd(velocity, velocity, pos);
        }
        size0 = RandomFloatRange(1.0f, 1.5f) * (*(float *)(vars + 0x20) * 210000.0f);
        spread = RandomFloatRange(0.2f, 0.4f);
        SpawnGravityFadeParticle(object + 0x10, velocity, 5, D_L00_001B0518, 3, 0x4f, 0, size0,
                      spread * (*(float *)(vars + 0x20) * 210000.0f), 0.0f, 0);
        qcopy(pos, object + 0x10);
        pos[0] += RandomSignedFloatRange(0.0f, 0.15f);
        pos[1] += RandomSignedFloatRange(0.0f, 0.15f);
        pos[2] += RandomSignedFloatRange(0.0f, 0.15f);
        size1 = RandomFloatRange(1.0f, 1.5f) * (*(float *)(vars + 0x20) * 210000.0f);
        spread = RandomFloatRange(0.1f, 0.3f);
        SpawnGravityFadeParticle(pos, velocity, 5, D_L00_001B0518, 7, 0x5f, 0, size1,
                      spread * (*(float *)(vars + 0x20) * 210000.0f), 0.0f, 0);
        pos[0] += RandomSignedFloatRange(0.0f, 0.15f);
        pos[1] += RandomSignedFloatRange(0.0f, 0.15f);
        pos[2] += RandomSignedFloatRange(0.0f, 0.15f);
        size2 = RandomFloatRange(1.0f, 1.5f) * (*(float *)(vars + 0x20) * 210000.0f);
        spread = RandomFloatRange(0.2f, 0.4f);
        SpawnGravityFadeParticle(pos, velocity, 5, D_L00_001B0518, 12, 0x7f, 0, size2,
                      spread * (*(float *)(vars + 0x20) * 210000.0f), 0.0f, 0);
        if (*(int *)(vars + 0x24)) {
            TransformPointAndRotationByParent(object, *(int *)(vars + 0x24), object + 0x10, object + 0xf0, object + 0x10, object + 0xf0);
            GetParentTransformedPoint(object, *(int *)(vars + 0x24), vars, vars);
        }
        break;
    case 1:
        SpawnExplosionEffects(object, D_L00_001A8F20, object + 0x10, 0.0f, 0.0f, 10, 0, 16, 0.0f, 0.0f, 9.0f, 1.0f, -1,
                      15.0f, 0, 9, -1, 0, 0x810001);
        MarkMobySpawned(object);
        return;
    }
    if (*(float *)(vars + 0x20) < 1.0f)
        *(float *)(vars + 0x20) += 0.025f;
    *(float *)(object + 0x2c) = RandomFloatRange(0.01f, 0.0125f) * *(float *)(vars + 0x20);
    AddDrawCallbackToList3(SpawnParticleBurstsAtMoby, object);
}
