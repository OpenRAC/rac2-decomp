#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Mat3[12] __attribute__((aligned(16)));
typedef float Mat4[16] __attribute__((aligned(16)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;

typedef struct {
    float timer;          /* 0x00 */
    s16 t4;               /* 0x04 */
    s16 t6;               /* 0x06 */
    s16 t8;               /* 0x08 */
    s16 tA;               /* 0x0A */
    float fC;             /* 0x0C */
    Vec4 v10; /* 0x10 */
    float f20;            /* 0x20 */
    float f24;            /* 0x24 */
    int t28;              /* 0x28 */
    float f2C;            /* 0x2C */
    Vec4 q30; /* 0x30 */
    int t40;              /* 0x40 */
    int t44;              /* 0x44 */
    float f48;            /* 0x48 */
    int t4C;              /* 0x4C */
    int handle;           /* 0x50 */
} TurretState;

typedef struct {
    Vec4 pos;             /* 0x00: copied by the request consumer as one quadword */
    u8 *source;           /* 0x10 */
    int flags;            /* 0x14 */
    u8 b18;               /* 0x18 */
    u8 b19;               /* 0x19 */
    u16 oclass;           /* 0x1A */
    float damage;         /* 0x1C */
    int count;            /* 0x20 */
    float extra;          /* 0x24: consumed by func_002A8E20 */
} Hit;

typedef struct { u8 pad0[0x28]; int id; u8 pad2C[0x28]; float rate; u8 pad58[0x18]; float damage; u8 pad74[0x6C]; } WeaponEntry;

extern u8 D_00189E20[];
extern u8 D_00138180[];
extern u8 D_00139568[];
extern u8 D_001395AC NOT_SDA;
extern float D_0018A580[4] NOT_SDA;
extern WeaponEntry D_L00_00262570[];
extern u8 D_L00_00296120[];
extern u8 D_L00_001A8F20[] MACRO_ADDR;
typedef struct { u8 pad[0x160]; float f160; int pad164; int i168; int i16C; float f170; int pad174; int i178; } Shake;
extern Shake D_L00_001B8C80;
extern u8 *D_L00_001C3280[];
extern float D_L00_001B0190[16] __attribute__((sda));
extern u16 D_L00_001B01E8 __attribute__((sda));
extern u16 D_L00_001B01EC __attribute__((sda));
extern int D_L00_001B020C __attribute__((sda));
extern u16 D_L00_001B0214 __attribute__((sda));
extern int D_L00_001B021C __attribute__((sda));
extern float D_L00_001B0220 __attribute__((sda));
extern float D_L00_001B0224 __attribute__((sda));
extern float D_L00_001B0228 __attribute__((sda));
extern int D_L00_001B0238 __attribute__((sda));

extern s32 func_00282978(s16 *);
extern int func_00282948(void *);
extern void func_002829D8(void *);
extern void ref_L00_003D1D28_00(int, int);
extern int func_L00_002D4040(int);
extern int func_L00_002D3F30(int, int);
extern void func_00273318(void *, float, u32, void *, int, float, int, float, int);
extern void func_L00_002AF7D0(void);
extern void func_L00_002AF568(void);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_L00_002D6998(void *);
extern void func_L00_002D6B70(int);
extern float func_002A7940(void);
extern float func_00283CE0(int);
extern int func_002E5CF8(int, int, void *);
extern void ref_L00_003D1D28_01(void *, void *);
extern void func_L00_003D2ED0(u8 *);
extern void func_L00_003D3388(u8 *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern u8 *func_L00_0033EC48(void *, int, float, float, u32, int, int, void *, int, int, int, int);
extern void func_L00_003D2C00(u8 *, void *, int);
extern s32 func_00277F48(f32, void *, s32, void *, s32);
extern void func_002A8E20(u8 *, Hit *);
extern void func_0032D758(u8 *, int, u8 *);
extern void func_00283410(void *, void *);
extern void func_00283678(void *, void *);
extern void func_0029FCC0(u8 *, int, void *);
extern void func_00283738(void *, void *, void *);
extern float func_002A7878(float, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern float func_00283B98(float, float);
extern int func_L00_003D2A00(u8 *, void *, void *, Hit *);


static inline void SetShake(float amount)
{
    D_L00_001B8C80.f160 = amount;
    D_L00_001B8C80.i168 = 30;
    D_L00_001B8C80.f170 = amount;
    D_L00_001B8C80.i178 = 30;
    D_L00_001B8C80.i16C = 0;
}

/* Per-frame update of the Blitz Cannon weapon (moby class 2801). It charges while fire is held, flashes and shakes the screen on firing, then hits nearby enemies and sends out 20 random damage bolts. */
void func_L00_003D1D28(u8 *self)
{
    Vec4 localPos;
    Vec4 worldPos;
    TurretState *st = *(TurretState **)(self + 0x68);
    int ready;
    u8 *hitObject;

    if (self[0x20] == 0) {
        self[0x20] = 1;
        st->handle = -1;
        st->t8 = 0;
        st->tA = 0;
        st->t28 = 0;
        st->t44 = 0;
        st->t4C = 0;
    }
    if (self[0x20] == 6) {
        if (FastDecTimer(&st->t4))
            self[0x20] = 1;
    }
    if (((Hero *)gHeroState)->i[0x2294 / 4] == 1)
        ref_L00_003D1D28_00(0x1D, 1);
    FastVectorHelperB(st);
    if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x1D) {
        u32 color;
        if (st->timer > 0.0f && get_ammo(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        AddMobyMarker(self, 1.3f, color, 0, 0x21, 0.0f, -1, 90.0f, 4);
    }
    if (st->t4C != 0 && FastFloatHelperD(&st->t4C))
        cancel_hero_item_animation();
    if (self[0x42] == self[0x43] && (self[0x60] & 2))
        StartAnimationBlendedWithFlags(self, 1, 0, 2, 0);
    /* moby/state and turret/shot are copies, and large..none are named constants, that gcse's cprop folds back:
     * they keep the insn count and the PRE expression numbers that give retail's spill slots at 0x23C-0x270. */
    {
        u8 *moby = self;
        TurretState *state = st;
        int large = 7;
        int small = 4;
        int mode = 2;
        int variant = 3;
        int none = 0;
        ready = 1;
        if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x1D) {
            if (FastFloatHelperD(&((Hero *)gHeroState)->i[0x2534 / 4]) == 0)
                ready = 0;
        } else {
            ((Hero *)gHeroState)->i[0x2534 / 4] = 0x28;
        }
        if (self[0x20] == 1 && ((Hero *)gHeroState)->b[0x22BC] == 0 && st->timer == 0.0f && ((Hero *)gHeroState)->i[0x1240 / 4] >= 0x17 && ready) {
            if ((((Hero *)gPadState)->i[0x1A0 / 4] & ((Hero *)gHeroState)->i[0x1230 / 4]) && SpendWeaponAmmo(-1, 1)) {
                if (((Hero *)gHeroState)->ptr[0x2290 / 4][0x43] == ((WeaponEntry *)((u8 *)gWeaponTable_L00 + D_001395AC * 0xE0))->id || ((Hero *)gHeroState)->i[0x229C / 4] != 0 || ((Hero *)gHeroState)->h[0x24EC / 2] != 0) {
                    st->t40 = 1;
                    st->t6 = D_L00_001B01E8;
                } else {
                    st->t40 = 0;
                    st->t6 = 2;
                }
                start_equipped_item_animation();
                st->handle = CopyRecordsToFreeSlots(D_L00_00296120);
                StartAnimationBlendedWithFlags(self, 2, 0, 2, 0);
                st->t4C = D_L00_001B0238;
                self[0x20] = 2;
                st->fC = RandomAngle();
                st->t8 = D_L00_001B01EC;
                st->f20 = 1.0f / IntToFloat(st->t8);
                st->tA = D_L00_001B0214;
                st->t8 += 2;
                st->f24 = 1.0f / IntToFloat(st->tA);
                st->t28 = D_L00_001B020C;
                st->f2C = 1.0f / IntToFloat(st->t28);
                st->t44 = D_L00_001B021C;
                st->f48 = 1.0f / IntToFloat(st->t44);
                st->t44 += 2;
            } else if (((Hero *)gPadState)->i[0x1A4 / 4] & ((Hero *)gHeroState)->i[0x1230 / 4]) {
                PlayMobySound(5, 0, self);
            }
            if (!(((Hero *)gPadState)->i[0x1A0 / 4] & ((Hero *)gHeroState)->i[0x1230 / 4]) || !get_ammo(-1) || ((Hero *)gHeroState)->b[0x22B8] == 0) {
                if (st->handle >= 0) {
                    ResetActiveSlots(st->handle);
                    st->handle = -1;
                }
            }
        }
        if (st->t6 == 0) {
            FastDecTimer(&st->tA);
            FastDecTimer(&st->t8);
            FastFloatHelperD(&st->t28);
            FastFloatHelperD(&st->t44);
            if (st->t8 != 0 || st->tA != 0 || st->t28 != 0 || st->t44 != 0)
                ref_L00_003D1D28_01(RenderRadialRingAndQuad, self);
            UpdateLightningArcs_L00(self);
        }
        if (self[0x20] == 2 || self[0x20] == 3) {
            u8 *cannon = moby;
            TurretState *shotState = state;
            if (FastDecTimer(&shotState->t6)) {
                if (cannon[0x20] == 2) {
                    cannon[0x20] = 3;
                    qcopy(shotState->q30, D_0018A580);
                    localPos[0] = D_L00_001B0220;
                    localPos[1] = D_L00_001B0224 - 0.25f;
                    localPos[2] = D_L00_001B0228;
                    localPos[3] = 1.0f;
                    matrix_mul_vec3(worldPos, localPos, cannon + 0xC0);
                    FastVecAdd(worldPos, worldPos, cannon + 0x10);
                    {
                        u8 *flash = SpawnPulledParticle(worldPos, large, 0.4f, 8.0f, 0x80FFFFFF, mode, none, D_L00_001A8F20, 0, 0, 6, 0);
                        if (flash)
                            *(TI128 *)(flash + 0x10) = *(TI128 *)(worldPos);
                    }
                    {
                        u8 *flash = SpawnPulledParticle(worldPos, small, 0.5f, 12.0f, 0x3CFF1010, mode, none, D_L00_001A8F20, variant, 0, 6, 0);
                        if (flash)
                            *(TI128 *)(flash + 0x10) = *(TI128 *)(worldPos);
                    }
                    {
                        u8 *flash = SpawnPulledParticle(worldPos, small, 0.5f, 4.0f, 0x80FFFFFF, mode, none, D_L00_001A8F20, variant, 0, 6, 0);
                        if (flash)
                            *(TI128 *)(flash + 0x10) = *(TI128 *)(worldPos);
                    }
                    localPos[2] = -localPos[2];
                    matrix_mul_vec3(worldPos, localPos, cannon + 0xC0);
                    FastVecAdd(worldPos, worldPos, cannon + 0x10);
                    {
                        u8 *flash = SpawnPulledParticle(worldPos, large, 0.4f, 8.0f, 0x80FFFFFF, mode, none, D_L00_001A8F20, 0, 0, 6, 0);
                        if (flash)
                            *(TI128 *)(flash + 0x10) = *(TI128 *)(worldPos);
                    }
                    {
                        u8 *flash = SpawnPulledParticle(worldPos, small, 0.5f, 12.0f, 0x3CFF1010, mode, none, D_L00_001A8F20, variant, 0, 6, 0);
                        if (flash)
                            *(TI128 *)(flash + 0x10) = *(TI128 *)(worldPos);
                    }
                    {
                        u8 *flash = SpawnPulledParticle(worldPos, small, 0.5f, 4.0f, 0x80FFFFFF, mode, none, D_L00_001A8F20, variant, 0, 6, 0);
                        if (flash)
                            *(TI128 *)(flash + 0x10) = *(TI128 *)(worldPos);
                    }
                    localPos[2] = 0.0f;
                    localPos[1] = D_L00_001B0224;
                    matrix_mul_vec3(worldPos, localPos, cannon + 0xC0);
                    FastVecAdd(shotState->v10, worldPos, cannon + 0x10);
                    InitEffectStrips(cannon, shotState->v10, 0);
                    ref_L00_003D1D28_01(RenderRadialRingAndQuad, cannon);
                    PlayMobySound(0, 0, cannon);
                    if (shotState->t40)
                        SetShake(0.12f);
                    else
                        SetShake(0.06f);
                } else {
                    Hit hit;
                    Vec4 up;
                    Vec4 side;
                    Vec4 fwd;
                    Mat3 basis;
                    Mat3 inv;
                    Mat4 mtx;
                    Vec4 origin;
                    Vec4 offs;
                    u8 *list[20];
                    int saved[20];
                    Vec4 rot;
                    Vec4 dir;
                    Vec4 from;
                    Vec4 to;
                    int count, i, nearbyCount, nearbyIndex, clearIndex, restoreIndex;
                    float angle, spread;

                    cannon[0x20] = 6;
                    shotState->t4 = 0x1C;
                    hit.flags = 0x10000;
                    hit.count = 1;
                    hit.b18 = 3;
                    hit.b19 = 2;
                    hit.oclass = *(u16 *)(cannon + 0xAA);
                    hit.damage = ((WeaponEntry *)((u8 *)gWeaponTable_L00 + gItemSlotToRecord[0x1A] * 0xE0))->damage;
                    hit.source = cannon;
                    FastVecScale(localPos, cannon + 0xD0, -1.35f);
                    FastVecAdd(localPos, localPos, cannon + 0x10);
                    FastVecScale(worldPos, cannon + 0xC0, 0.275f);
                    FastVecAdd(localPos, localPos, worldPos);
                    nearbyCount = ProcessCollisionHit(1.5f, localPos, 1, ((Hero *)gHeroState)->ptr[0x2290 / 4], 0);
                    for (nearbyIndex = 0; nearbyIndex < nearbyCount; nearbyIndex++) {
                        if (gAreaHitTargets[nearbyIndex] != ((Hero *)gHeroState)->ptr[0x2290 / 4]) {
                            FastVecScale(hit.pos, cannon + 0xD0, -1.5f);
                            hit.pos[3] = 5627.925f;
                            QueueMobyImpact(gAreaHitTargets[nearbyIndex], &hit);
                            StartAttachedEffect(gAreaHitTargets[nearbyIndex], 0x44, cannon);
                        }
                    }
                    euler_to_matrix(mtx, D_L00_001B0190);
                    copy_matrix3x4(inv, mtx);
                    TransformMobyJointToWorld(cannon, 0, origin);
                    if (((Hero *)gHeroState)->h[0x24EC / 2] == 1) {
                        FastVecScale(up, cannon + 0xD0, -1.0f);
                        FastVecScale(side, cannon + 0xC0, -1.0f);
                        FastVecScale(fwd, cannon + 0xE0, 0.1f);
                        multiply_matrix3x3(basis, cannon + 0xC0, inv);
                    } else {
                        qcopy(up, ((Hero *)gHeroState)->b + 0x730);
                        qcopy(side, ((Hero *)gHeroState)->b + 0x740);
                        FastVecScale(fwd, ((Hero *)gHeroState)->b + 0x750, -0.1f);
                        multiply_matrix3x3(basis, ((Hero *)gHeroState)->b + 0x730, inv);
                    }
                    qcopy(shotState->q30, up);
                    spread = 1.0471977f;
                    count = 0;
                    angle = 0.0f;
                    for (clearIndex = 0; clearIndex < 20; clearIndex++) {
                        list[clearIndex] = 0;
                        saved[clearIndex] = 0;
                    }
                    for (i = 0; i < 20; i++) {
                        BuildAxisAngleQuaternion(rot, side, RandomFloatRange(0.01f, 0.52359885f));
                        RotateVectorByQuaternion(dir, up, rot);
                        RotateVectorByQuaternion(offs, fwd, rot);
                        angle = FastAddRotations(RandomFloatRange(spread * 0.5f, spread * 1.5f), angle);
                        BuildAxisAngleQuaternion(rot, up, angle);
                        RotateVectorByQuaternion(dir, dir, rot);
                        RotateVectorByQuaternion(offs, offs, rot);
                        FastVecScale(dir, dir, 38.0f);
                        FastVecAdd(from, origin, offs);
                        FastVecAdd(to, from, dir);
                        hitObject = ((u8 *)FireDamageRayAtTarget(cannon, from, to, &hit));
                        if (hitObject) {
                            saved[count] = *(int *)(hitObject + 0x98);
                            list[count] = hitObject;
                            *(int *)(hitObject + 0x98) = 0;
                            count++;
                        }
                    }
                    for (restoreIndex = 0; restoreIndex < count; restoreIndex++)
                        *(int *)(list[restoreIndex] + 0x98) = saved[restoreIndex];
                    {
                        WeaponEntry *w = (WeaponEntry *)((u8 *)gWeaponTable_L00 + gItemSlotToRecord[0x1A] * 0xE0);
                        shotState->timer = 1.0f / w->rate;
                    }
                }
            }
        }
    }
}
