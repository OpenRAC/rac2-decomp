#include "common.h"

extern void *D_L11_001FC420[];

/* Reached with `lw $a2,0x45AC($gp)`, so this unit is built -G8. */
extern u8 *D_L11_001B359C;

extern s32 D_L11_001AED04;
extern f32 func_002A89A8(void *, s32, f32);
extern s32 func_00283CF0(f32);
extern s32 func_L02_0032E508(void *, s32, void *, s32);
extern void func_0026FEB8(void *, ...);
extern char D_L11_001B1008[];
extern f32 func_002A78D8(f32, f32);
extern s32 func_002A77E0(s32);
extern void func_L00_003294F0(void *, s32);
/* Void: no direct call reads $v0, and a void definition matches every place. */
extern void func_002B60B0(void *, f32, f32, f32, f32);

extern char D_L11_002BADF8[];
extern char D_L11_001BA8C0[];
extern s32 D_L11_001AED00, D_L11_001B35B8, D_L11_001B30C8;
extern u8 *func_0029EFD0(s32);
extern void func_0029F338(void *);
extern void func_002A7750(void *, s32, s32);
extern void func_002A7470(void *, s32, s32, s32);
extern void func_002A0F48(void *);
extern void func_002AF1D0(void *, void *, s32, s32);
extern f32 func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_0029FC20(void *, s32, void *);
extern void func_0029FCC0(void *, s32, void *);
extern void func_002A05A8(void *);
extern void func_00283678(void *, void *);
extern void func_002ACEC0(void *, void *, void *, f32);
extern void func_002AB028(void *);
extern void func_002A10E8(void *);
extern void func_002AC728(void *, void *, f32, f32, s32);
extern s32 func_002B0ED8(void *, void *, s32);
extern void func_L11_0042A5B0(void *, s32);
extern void func_002AB800(void *, void *);
extern void func_L11_0042A4C8(void *);
extern s32 func_002A8508(s32, s32);
extern s32 func_002B3670(void *, void *, s32, s32, f32, f32, s32);
extern void func_002A6C58(void *, s32, s32);

/* Initializes linked objects, updates damage, and releases children on removal. */
s32 func_L11_004295A0(u8 *object) {
    f32 vectors[16];
    s32 damage;
    u16 *ids;
    u8 *data = *(u8 **)(object + 0x68);
    if (object[0x20] == 0) {
        object[0x30] = 0x80;
        D_L11_001AED04++;
        *(s32 *)(data + 0x5B0) = 0;
        *(void **)(data + 0x18) = data + 0x140;
        *(f32 *)(object + 0x18) = ProbeGroundHeightBelow(object + 0x10, 0, 0.5f);
        *(s32 *)(data + 0x554) = 0;
        *(s32 *)(data + 0x560) = 0;
        *(s32 *)(data + 0x568) = 0;
        data[0x48] = FloatToInt(20.0f);
        data[0x4A] = FloatToInt(14.0f);
        if (*(s32 *)(data + 0x528)) {
            *(s32 *)(data + 0x520) = BuildRouteNodes(object, *(s32 *)(data + 0x524), data + 0x320, 16);
            STUB_printf(D_L11_001B1008, *(s32 *)(data + 0x520));
        }
        if (*(f32 *)(data + 0x298) == 0.0f)
            *(f32 *)(data + 0x298) = RandomSignedFloatRange(15.0f, 25.0f) * 0.01745329424738884f;
        else
            *(f32 *)(data + 0x298) *= 0.01745329424738884f;
        if (RandomIntBelow(2) == 1) {
            *(u16 *)(object + 0x34) |= 0x8000;
            SetObjectFlagBit(object, 1);
        }
        data[0x70] = 31;
        *(s32 *)(data + 0xA8) = 4;
        data[0x72] = 7;
        data[0x71] = 6;
        data[0x76] = 8;
        *(f32 *)(data + 0x7C) = 0.20000002f;
        *(f32 *)(data + 0x80) = 0.125f;
        *(f32 *)(data + 0x84) = 0.00555555569f;
        *(f32 *)(data + 0x88) = 0.00972222257f;
        *(f32 *)(data + 0x8C) = 0.00416666688f;
        *(f32 *)(data + 0x90) = 0.75f;
        *(f32 *)(data + 0x94) = 0.75f;
        *(s32 *)(data + 0x9C) = 0;
        data[0xCC] = 5;
        data[0xCD] = 10;
        data[0xCE] = 8;
        data[0xCF] = 15;
        data[0xD2] = 6;
        data[0xD3] = 11;
        *(f32 *)(data + 0x10C) = 0.5f;
        *(f32 *)(data + 0xB8) = 0.18f;
        if (*(s32 *)(data + 0x5B8) != -1)
            *(s32 *)(data + 0xDC) = *(s32 *)(data + 0x5B8);
        *(void **)(data + 0x188) = data + 0x2A0;
        *(f32 *)(data + 0x174) = 0.25f;
        *(f32 *)(data + 0x140) = 0.75f;
        *(f32 *)(data + 0x144) = 0.75f;
        *(f32 *)(data + 0x148) = 0.6f;
        *(f32 *)(data + 0x14C) = 0.6f;
        if (*(s32 *)(data + 0x288) != -1)
            *(s32 *)(data + 0x17C) = *(s32 *)(data + 0x288);
        *(f32 *)(data + 0x150) = 1.483530044555664f;
        *(f32 *)(data + 0x16C) = 0.00138888892f;
        *(f32 *)(data + 0x170) = 1.483530044555664f;
        *(f32 *)(data + 0x174) = 1.5f;
        SetControllerSpeedLimits(object, 0.00152777787f, 0.0458333343f, 0.00116355298f, 0.104719773f);
        data[0x28] = 3;
        data[0x29] = 1;
        *(f32 *)(data + 0x30) = 0.75f;
        *(f32 *)(data + 0x28C) = data[0x34];
        data[0x2E] = 1;
        if (*(s32 *)(data + 0x26C)) {
            SetMobyState(object, 1, 5);
            if (*(s32 *)(data + 0x270) != -1) {
                *(u8 **)(data + 0x274) = gMobyTable_L11 + (*(s32 *)(data + 0x270) << 8);
                qcopy_nc(object + 0x10, *(u8 **)(data + 0x274) + 0x10);
                qcopy_nc(object + 0xF0, *(u8 **)(data + 0x274) + 0xF0);
                *(s32 *)(object + 0x98) = 0;
                *(u16 *)(object + 0x34) &= 0xAFFF;
                *(u8 **)(*(u8 **)(*(u8 **)(data + 0x274) + 0x68) + 0x27C) = object;
                *(u8 **)(data + 0x280) = CreateMoby(0x911 /* moby class 2321 */);
                if (!*(u8 **)(data + 0x280)) return 1;
                (*(u8 **)(data + 0x280))[0x30] = object[0x30];
                (*(u8 **)(data + 0x280))[0x31] = 0;
                func_002A0F48(*(u8 **)(data + 0x280));
                qcopy_nc(*(u8 **)(data + 0x280) + 0x10, object + 0x10);
                *(f32 *)(*(u8 **)(data + 0x280) + 0x18) += 0.75f;
                *(u8 **)(data + 0x278) = CreateMoby(0xFF9 /* moby class 4089 */);
                if (!*(u8 **)(data + 0x278)) return 1;
                (*(u8 **)(data + 0x278))[0x30] = object[0x30];
                *(u16 *)(*(u8 **)(data + 0x278) + 0x32) = *(u16 *)(object + 0x32);
                (*(u8 **)(data + 0x278))[0x31] = 1;
                *(u64 *)(*(u8 **)(data + 0x278) + 0x38) = *(u64 *)(object + 0x38);
                func_002A0F48(*(u8 **)(data + 0x278));
                CopyJointTransformToObject(object, *(u8 **)(data + 0x278), 1, 0);
                *(s32 *)(data + 0x290) = 0;
            } else {
                STUB_printf(D_L11_002BADF8);
                *(s32 *)(data + 0x26C) = 0;
                SetMobyState(object, 4, 0);
                return 1;
            }
        } else {
            SetMobyState(object, 4, 0);
            if (object[0x43]) StartAnimationBlended(object, 0, 0, 0);
            if (*(s32 *)(data + 0x540) == 1) {
                *(u8 **)(data + 0x55C) = gMobyTable_L11 + (*(s32 *)(data + 0x544) << 8);
                SetMobyState(object, 5, 0);
                if (object[0x43] != 13) StartAnimationBlended(object, 13, 0, 0);
            } else if (*(s32 *)(data + 0x540) == 2) {
                *(u8 **)(data + 0x55C) = gMobyTable_L11 + (*(s32 *)(data + 0x544) << 8);
                SetMobyState(object, 5, 0);
                if (object[0x43] != 15) StartAnimationBlended(object, 15, 5, 0);
            } else if (*(s32 *)(data + 0x540) == 3) {
                *(u8 **)(data + 0x55C) = gMobyTable_L11 + (*(s32 *)(data + 0x544) << 8);
                SetMobyState(object, 5, 0);
                if (object[0x43] != 15) StartAnimationBlended(object, 15, 0, 0);
            } else if (*(s32 *)(data + 0x54C) != -1) {
                SetMobyState(object, 11, 0);
                if (object[0x43] != 4) StartAnimationBlended(object, 4, 0, 0);
            }
            *(u8 **)(data + 0x29C) = CreateMoby(0x9AC /* moby class 2476 */);
            if (!*(u8 **)(data + 0x29C)) return 1;
            (*(u8 **)(data + 0x29C))[0x30] = object[0x30];
            *(u16 *)(*(u8 **)(data + 0x29C) + 0x32) = *(u16 *)(object + 0x32);
            (*(u8 **)(data + 0x29C))[0x31] = 1;
            *(u64 *)(*(u8 **)(data + 0x29C) + 0x38) = *(u64 *)(object + 0x38);
            func_002A0F48(*(u8 **)(data + 0x29C));
            *(s32 *)(*(u8 **)(data + 0x29C) + 0x98) = 0;
            CopyJointTransformToObject(object, *(u8 **)(data + 0x29C), 3, 0);
            *(u8 **)(data + 0x278) = CreateMoby(0xFF9 /* moby class 4089 */);
            if (!*(u8 **)(data + 0x278)) return 1;
            (*(u8 **)(data + 0x278))[0x30] = object[0x30];
            *(u16 *)(*(u8 **)(data + 0x278) + 0x32) = *(u16 *)(object + 0x32);
            (*(u8 **)(data + 0x278))[0x31] = 1;
            *(u64 *)(*(u8 **)(data + 0x278) + 0x38) = *(u64 *)(object + 0x38);
            func_002A0F48(*(u8 **)(data + 0x278));
            CopyJointTransformToObject(object, *(u8 **)(data + 0x278), 2, 0);
        }
        qcopy_nc(data + 0x110, object + 0x10);
        *(f32 *)(data + 0x120) = 1.0f;
        *(f32 *)(data + 0x12C) = 8.0f;
        *(f32 *)(data + 0x130) = 10.0f;
    }
    if (object[0x31] && fast_vec_dist(object + 0x10, D_L11_001BA8C0) < 24.0f) {
        UpdateMobyGroundCheck(object);
        object[0x6F] = 22;
    }
    if (data[0x2E] == 2) {
        if (*(void **)(data + 0x29C)) {
            MarkMobySpawned(*(void **)(data + 0x29C));
            *(void **)(data + 0x29C) = 0;
        }
        if (*(void **)(data + 0x278)) {
            MarkMobySpawned(*(void **)(data + 0x278));
            *(void **)(data + 0x278) = 0;
        }
        if (*(void **)(data + 0x280)) {
            MarkMobySpawned(*(void **)(data + 0x280));
            *(void **)(data + 0x280) = 0;
        }
        return 1;
    }
    if (*(void **)(data + 0x29C)) CopyJointTransformToObject(object, *(void **)(data + 0x29C), 3, 0);
    if (*(u8 **)(data + 0x278)) {
        TransformMobyJointPoint(object, 2, vectors);
        qcopy_nc(*(u8 **)(data + 0x278) + 0x10, vectors + 12);
        func_002A05A8(*(void **)(data + 0x278));
        func_002A0F48(*(void **)(data + 0x278));
        copy_matrix3x4(*(u8 **)(data + 0x278) + 0xC0, vectors);
        ApplyAxisRotationToQuaternion(*(u8 **)(data + 0x278) + 0xD0, *(u8 **)(data + 0x278) + 0xD0, *(u8 **)(data + 0x278) + 0xE0, 3.14159298f);
        NormalizeMatrixColumns(*(u8 **)(data + 0x278) + 0xC0);
        func_002A10E8(*(void **)(data + 0x278));
        *(u16 *)(*(u8 **)(data + 0x278) + 0x34) |= 6;
    }
    if (*(f32 *)(data + 0x20) <= 1.0f) {
        if (*(u8 **)(data + 0x29C)) {
            SpawnExplosionWithSparks(object, *(u8 **)(data + 0x29C) + 0x10, 0.5f, 3.0f, -1);
            MarkMobySpawned(*(void **)(data + 0x29C));
            *(void **)(data + 0x29C) = 0;
        }
        *(s32 *)(data + 0x290) = 0;
    }
    *(s32 *)(data + 0x290) = 0;
    damage = ApplyDamageToObject(object, data + 0x60, 0);
    if (damage) {
        u8 *attacker = *(u8 **)(data + 0x38);
        if (attacker) {
            s32 cls = *(s16 *)(attacker + 0xAA);
            if (cls != 0x47 /* moby class 71 */ && cls != 0xDD9 /* moby class 3545 */ && cls != 0xD1B /* moby class 3355 */ && cls != 0xCE7 /* moby class 3303 */ && cls != 0xD07 /* Jobian Saur-Beast */ && cls != 0)
                D_L11_001AED00 = 0;
        }
        if (object[0xBC] == 1)
            (gMobyTable_L11 + (*(s32 *)(data + 0x548) << 8))[0x20] = 4;
        if (*(f32 *)(object + 0x48) != 1.0f) *(f32 *)(object + 0x48) = 1.0f;
        if (*(s32 *)(data + 0x290)) {
            TransformMobyJointToWorld(object, 3, vectors);
            SpawnPairedSparkParticles_L11(vectors, 8);
        }
        if (damage == 5) {
            *(f32 *)(data + 0xF4) = 0.837758183f;
            *(s32 *)(data + 0xF0) = 0;
            if (*(u8 **)(data + 0x29C)) {
                SpawnExplosionWithSparks(object, *(u8 **)(data + 0x29C) + 0x10, 0.5f, 3.0f, -1);
                MarkMobySpawned(*(void **)(data + 0x29C));
                *(void **)(data + 0x29C) = 0;
            }
        }
        *(s32 *)(data + 0x290) = 0;
        data[0x57] = 0xD2;
        StartColorFade(object, data + 0x50);
        if (object[0x95] != 2) MarkGroupClassCF5CF6Members(object);
        if ((u32)(damage - 4) < 2 && D_L11_001B35B8 >= object[0x21] && CountMobysInGroupNotInState(object[0x21], -1) >= 2) {
            ids = gGroupIdLists[object[0x21]];
            do {
                u8 *entry = gMobyTable_L11 + ((*ids & 0x7FFF) << 8);
                if (*(s16 *)(entry + 0xAA) == 0xCF6 /* moby class 3318 */ && !*(s32 *)(*(u8 **)(entry + 0x68) + 0x294)) {
                    *(s32 *)(*(u8 **)(entry + 0x68) + 0x294) = 1;
                    break;
                }
            } while (*(s16 *)ids++ >= 0);
        }
    }
    *(s16 *)(data + 0x264) = CheckHeroDistanceZones(object, data + 0x268, *(s32 *)(data + 0x250), *(s32 *)(data + 0x254), *(f32 *)(data + 0x258), *(f32 *)(data + 0x25C), 0);
    if (object[0x95] != 4) {
        f32 floor = ProbeGroundHeightBelow(object + 0x10, 0, 0.5f);
        *(f32 *)(object + 0x18) -= 0.313333333f;
        if (*(f32 *)(object + 0x18) < floor) *(f32 *)(object + 0x18) = floor;
    }
    if (*(f32 *)(object + 0x18) < 61.0f && D_L11_001B30C8 >= 6) {
        MarkMobySpawned(*(void **)(data + 0x278));
        SetDeathBits(object, 0, 3);
        if (D_L11_001B35B8 >= object[0x21] && CountMobysInGroupNotInState(object[0x21], -1) >= 2) {
            u16 *deathIds = gGroupIdLists[object[0x21]];
            do {
                u8 *entry = gMobyTable_L11 + ((*deathIds & 0x7FFF) << 8);
                if (!*(s32 *)(*(u8 **)(entry + 0x68) + 0x294)) {
                    *(s32 *)(*(u8 **)(entry + 0x68) + 0x294) = 1;
                    break;
                }
            } while (*(s16 *)deathIds++ >= 0);
        }
        if (*(u8 **)(data + 0x29C)) {
            SpawnExplosionWithSparks(object, *(u8 **)(data + 0x29C) + 0x10, 0.5f, 3.0f, -1);
            MarkMobySpawned(*(void **)(data + 0x29C));
            *(void **)(data + 0x29C) = 0;
        }
        D_L11_001AED04--;
        return 1;
    }
    return 0;
}

/* Flags every record of the id list whose class halfword is 0xD07. */
void func_L11_00431DB0(u8 *moby) {
    void *list;
    u16 *idPtr;
    u8 *mobyTable;

    if (moby[0x21] == 0xFF)
        return;
    list = gGroupIdLists[moby[0x21]];
    if (list == 0)
        return;
    idPtr = list;
    mobyTable = gMobyTable_L11;
    do {
        u8 *entry = mobyTable + ((*idPtr & 0x7FFF) << 8);

        if (*(s8 *)(entry + 0x20) >= 0 && *(s16 *)(entry + 0xAA) == 0xD07 /* Jobian Saur-Beast */)
            *(s16 *)(*(u8 **)(entry + 0x68) + 0x276) = 1;
    } while (*(s16 *)idPtr++ >= 0);
}

typedef int TI128 __attribute__((mode(TI)));

/* The flat quad the effect submits: four positions, four colours, four uv
   pairs and the four GS words (primitive, texture, mode, registers). */
typedef struct {
    TI128 position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectQuad;

typedef struct {
    TI128 saved;
    EffectQuad quad;
    float a[4];
    float b[4];
    float c[4];
    TI128 corner;
} EffectQuadFrame;

extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern char D_L11_001BA8C0[];
/* The two uv columns: macro-addressed tables, so each base is one la. */
extern float D_L11_001B1138[] __attribute__((sda));
extern float D_L11_001B113C[] __attribute__((sda));

/* The quad between the two end points at +0x230 and +0x240: each side
   is pulled a tenth of the way toward the level's anchor, then the four
   corners are crossed out from the span and submitted. */
void func_L11_00431EE8(char *obj, void *q)
{
    EffectQuadFrame quadFrame;
    char *vars;
    int i;

    quadFrame.saved = *(TI128 *)q;
    vars = *(char **)(obj + 0x68);
    FastVecSub(quadFrame.c, vars + 0x230, vars + 0x240);
    FastVecSub(quadFrame.a, vars + 0x230, D_L11_001BA8C0);
    FastVecSub(quadFrame.b, vars + 0x240, D_L11_001BA8C0);
    FastVecCross(quadFrame.a, quadFrame.a, quadFrame.c);
    vec_scale_to_length(quadFrame.a, quadFrame.a, 0.1f);
    FastVecCross(quadFrame.b, quadFrame.b, quadFrame.c);
    vec_scale_to_length(quadFrame.b, quadFrame.b, 0.1f);
    quadFrame.quad.texture = GetEffectTextureDescriptor(7);
    quadFrame.quad.mode = 0x0000ff9000000260UL;
    quadFrame.quad.registers = 0x7000000048UL;
    quadFrame.quad.primitive = 0;
    quadFrame.quad.color[0] = quadFrame.quad.color[1] = quadFrame.quad.color[2] = quadFrame.quad.color[3] = 0x2F0000FF;
    for (i = 0; i < 4; i++) {
        quadFrame.quad.uv[i][0] = D_L11_001B1138[i * 2];
        quadFrame.quad.uv[i][1] = D_L11_001B113C[i * 2];
    }
    FastVecSub(&quadFrame.corner, vars + 0x230, quadFrame.a);
    quadFrame.quad.position[0] = quadFrame.corner;
    FastVecAdd(&quadFrame.corner, vars + 0x230, quadFrame.a);
    quadFrame.quad.position[1] = quadFrame.corner;
    FastVecSub(&quadFrame.corner, vars + 0x240, quadFrame.b);
    quadFrame.quad.position[2] = quadFrame.corner;
    FastVecAdd(&quadFrame.corner, vars + 0x240, quadFrame.b);
    quadFrame.quad.position[3] = quadFrame.corner;
    draw_world_quad(&quadFrame.quad, 0, 0);
}

extern char D_L11_001BA8C0[];
/* The two uv columns: macro-addressed tables, so each base is one la. */
extern float D_L11_001B1138[] __attribute__((sda));
extern float D_L11_001B113C[] __attribute__((sda));

/* The quad between the two end points at +0x230 and +0x240: each side
   is pulled a twentieth of the way toward the level's anchor, then the four
   corners are crossed out from the span and submitted (then drawn again as the overlay). */
void func_L11_004320F8(char *obj, void *q)
{
    EffectQuadFrame quadFrame;
    char *vars;
    int i;

    quadFrame.saved = *(TI128 *)q;
    vars = *(char **)(obj + 0x68);
    FastVecSub(quadFrame.c, vars + 0x230, vars + 0x240);
    FastVecSub(quadFrame.a, vars + 0x230, D_L11_001BA8C0);
    FastVecSub(quadFrame.b, vars + 0x240, D_L11_001BA8C0);
    FastVecCross(quadFrame.a, quadFrame.a, quadFrame.c);
    vec_scale_to_length(quadFrame.a, quadFrame.a, 0.05f);
    FastVecCross(quadFrame.b, quadFrame.b, quadFrame.c);
    vec_scale_to_length(quadFrame.b, quadFrame.b, 0.05f);
    quadFrame.quad.texture = GetEffectTextureDescriptor(0x13);
    quadFrame.quad.mode = 0x0000ff9000000260UL;
    quadFrame.quad.registers = 0x8000000048UL;
    quadFrame.quad.primitive = 0;
    quadFrame.quad.color[0] = quadFrame.quad.color[1] = quadFrame.quad.color[2] = quadFrame.quad.color[3] = 0x2FFFFFFF;
    for (i = 0; i < 4; i++) {
        quadFrame.quad.uv[i][0] = D_L11_001B1138[i * 2];
        quadFrame.quad.uv[i][1] = D_L11_001B113C[i * 2];
    }
    FastVecSub(&quadFrame.corner, vars + 0x230, quadFrame.a);
    quadFrame.quad.position[0] = quadFrame.corner;
    FastVecAdd(&quadFrame.corner, vars + 0x230, quadFrame.a);
    quadFrame.quad.position[1] = quadFrame.corner;
    FastVecSub(&quadFrame.corner, vars + 0x240, quadFrame.b);
    quadFrame.quad.position[2] = quadFrame.corner;
    FastVecAdd(&quadFrame.corner, vars + 0x240, quadFrame.b);
    quadFrame.quad.position[3] = quadFrame.corner;
    draw_world_quad(&quadFrame.quad, 0, 0);
    quadFrame.quad.texture = GetEffectTextureDescriptor(0x10);
    quadFrame.quad.mode = 0x0000ff9000000260UL;
    quadFrame.quad.registers = 0x8000000048UL;
    quadFrame.quad.primitive = 0;
    draw_world_quad(&quadFrame.quad, 0, 0);
}
