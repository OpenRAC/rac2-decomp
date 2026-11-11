#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef union {
    TI128 q;
    float f[4];
} L20_0039BB18_V4;

extern float D_L20_001AEC68 __attribute__((sda));

extern int func_00282948(int *);
extern float func_00282E80(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern void func_0029F338(void *);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern void *func_002C3150(void *, void *, int, u8, u8, int, float);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L20_0039BEC8(void *);

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
/* Measured level-state prefix; no full allocation size is inferred. */
typedef struct {
    u8 before_mode[0x30];
    int mode, state;
    u8 before_count[0xC];
    s16 count;
    u8 before_objects[0x146];
    union {
        void *objects[0];
        struct {
            u8 before_target[0xC];
            void *target;
            int owner;
            u8 before_alternate[8];
            void *alternate;
            u8 before_secondary_owner[8];
            int secondary_owner;
            void *secondary_target;
        } named;
    } refs;
} YeedilStatePrefix;
extern YeedilStatePrefix D_L20_001BDCC0;
extern u32 D_001A79F0;
typedef struct { u8 before_owner[0x5C0]; int owner; } YeedilHeroPrefix;
extern YeedilHeroPrefix D_00189E20;
extern u8 D_0018A550[];
typedef struct {
    Vector origin, point;
    float unknown20, scale;
} YeedilCameraPrefix;
extern YeedilCameraPrefix D_L20_001C6AE0;
extern u8 D_L20_001BA1F0[];
typedef struct {
    u8 before_effect[0x160];
    float scale1;
    int unknown164, count1, state1;
    u8 before_effect2[0x10];
    float scale2;
    int unknown184, count2;
} YeedilEffectPrefix;
extern YeedilEffectPrefix D_L20_001B9E80;
extern int D_L20_001A9430 __attribute__((sda));
extern int D_L20_001A9434 __attribute__((sda));
extern int D_L20_001A9438 __attribute__((sda));
extern int D_L20_001A943C __attribute__((sda));
extern int D_L20_001A9440 __attribute__((sda));
extern Vector D_L20_001A9420 SDATA(D_L20_001A9420);
extern int D_L20_001AF3B0[] __attribute__((sda));
extern void func_L00_002FC980(void *);
extern void func_002E64A0(void *);
extern void func_L00_00326048(char *,float *,s32,s32,float);
extern void func_00282A60(void *,int,int);
extern void func_0029FC20(void *,int,void *);
extern void func_0029FCC0(void *,int,void *);
extern void func_00283678(void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_0030CAD0(void *);
extern void func_0030CCD0(void *);
extern void func_L00_002E6EF8(void (*)(void *),void *);
extern void func_0030D430(void *);
extern void func_0032DA58(void *,void *,void *,float);
extern void func_L03_00326458(void *);
extern void *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);

void func_L20_0039BB18(void *arg0)
{
    L20_0039BB18_V4 pos;
    L20_0039BB18_V4 vel;
    u32 s0;
    float g;
    float angle;
    float rnd01;
    float rnd;
    float zero_arg;
    u32 old;
    unsigned long long c64;
    int m;
    int r;
    float r2;
    float rr;
    float rr2;

    s0 = *(u32 *)((u32)arg0 + 0x68);
    if (func_00282948((int *)(s0 + 4)) != 0)
        goto pathA;
    old = *(u16 *)((u32)arg0 + 0x96);
    c64 = old++;
    *(u16 *)((u32)arg0 + 0x96) = old;
    if (c64 < 11)
        goto check;
    if (*(u16 *)(*(u32 *)((u32)arg0 + 0xB8) + 0x34) & 1)
        goto pathA;
check:
    if (func_00282E80((void *)((u32)arg0 + 0x10),
                      (void *)(*(u32 *)((u32)arg0 + 0xB8) + 0x10)) > 0.1f) {
pathA:
        zero_arg = 0.0f;
        func_002AA2E8((float *)s0, zero_arg, 0.016666667f);
        if (*(float *)s0 == 0.0f) {
            func_0029F338(arg0);
            goto end;
        }
    } else {
        func_002AA2E8((float *)s0, 1.0f, 0.016666667f);
    }

    g = D_L20_001AEC68;
    {
        float v = *(float *)(s0 + 0xC) + g * 0.016666667f;
        *(float *)(s0 + 0xC) = v;
        if (v > 1.0f) {
            *(float *)(s0 + 0xC) = v - 1.0f;
        } else if (v < -1.0f) {
            *(float *)(s0 + 0xC) = v + 1.0f;
        } else {
            goto skip;
        }
    }
skip:
    rnd = func_002A7878(0.1f, 0.3f);
    m = func_002A7820(30, 60);
    vel.q = 0;
    r2 = func_002A7878(0.5f, 2.0f);
    vel.f[2] = -r2 * 0.016666667f;
    pos.q = vel.q;
    rnd01 = func_002A7878(0.0f, 1.0f);
    angle = func_002A7940();
    vel.f[0] = func_00283180(angle) * rnd01;
    vel.f[1] = func_00283198(angle) * rnd01;
    vel.f[2] = 0.0f;
    rr = func_002A7878(1.0f, 10.0f);
    vel.f[2] = rr;
    rr2 = func_002A7878(1.0f, 10.0f);
    if (!(vel.f[2] > rr2)) {
        ;
    } else {
        vel.f[2] = rr2;
    }
    func_00282CC0(&vel, &vel, arg0 + 0x10);
    {
        u8 particle_count = m;
        r = func_002A77E0(255);
        func_002C3150(&vel, &pos, 0x60107080, particle_count, r & 0xFF, 0, rnd);
    }
    func_L00_002E6CF0(func_L20_0039BEC8, arg0);
end:
    return;
}


void func_L20_00310E38(void *incoming)
{
    int lower, upper;
    void *target;
    /* 29FC20 uses the fourth row at output+0x30; 83678 copies only
    * the first three rows. The same workspace later holds one vector. */
    Vector matrix[4], work, offset;
    float value;

    func_L00_002FC980(incoming);
    {
        int i;
        for (i = 0; i < D_L20_001BDCC0.count; ++i) {
            u8 *object;
            object = D_L20_001BDCC0.refs.objects[i];
            if (object && *(s16 *)(object+0xAA) == 0xE29)
                *(u16 *)(object+0x34) |= 0x800;
            if (*(s16 *)(object+0xAA) == 0xD54)
                func_002E64A0(object);
            if (object && *(s16 *)(object+0xAA) == 0xFA0 && *(void **)(object+0x68))
                func_L00_00326048((char *)object,(float *)(*(u8 **)(object+0x68)+0xC),
                                  0x80AAAAD2,0x80396464,0.06108653545f);

        }
    }
    if (D_001A79F0 != 20) return;
    {
        if ((u32)(D_L20_001BDCC0.mode-4) < 2) {
            {
                YeedilHeroPrefix *hero = &D_00189E20;
                int owner = D_L20_001BDCC0.refs.named.owner;
                hero->owner = owner;
                if (D_L20_001BDCC0.mode == 4) {
                    hero->owner = D_L20_001BDCC0.refs.named.secondary_owner;
                    target = D_L20_001BDCC0.refs.named.secondary_target;
                    lower = D_L20_001A9434;
                    upper = D_L20_001A9438;
                } else {
                    lower = D_L20_001A943C;
                    /* Same value as the store above. It leaves no instruction of its
                     * own, but it keeps owner live into this arm. */
                    hero->owner = owner;
                    target = D_L20_001BDCC0.refs.named.alternate;
                    upper = D_L20_001A9440;
                }
                {
                    YeedilCameraPrefix *camera = &D_L20_001C6AE0;
                    if (D_L20_001BDCC0.state == lower) {
                        func_00282A60(camera,0,0x50);
                        D_L20_001AF3B0[0] = 1;
                        camera->scale = 0.8f;
                    }
                    if (lower < D_L20_001BDCC0.state && D_L20_001BDCC0.state < upper) {
                        func_0029FC20(target,0,matrix);
                        func_00283678(D_0018A550,matrix);
                        value = camera->scale;
                        value += (12.0f-value)*0.07f;
                        camera->scale = value;
                        func_0029FCC0(target,0,camera);
                        func_00282F20(&camera->point,D_0018A550,camera->scale);
                        func_00282CC0(&camera->point,camera,&camera->point);
                        func_0030CAD0(target);
                        func_0030CCD0(target);
                        func_L00_002E6EF8(func_0030D430,target);
                        if (D_L20_001BDCC0.mode == 5 && D_L20_001BDCC0.state == upper-1) {
                            offset.q = 0;
                            offset.f[0] = 18.0f; offset.f[1] = -2.5f; offset.f[2] = 1.0f;
                            func_00283098(&offset,&offset,D_L20_001BA1F0);
                            func_00282CC0(&offset,&offset,D_L20_001BA1F0-0x230);
                            func_00282CF0(&work,D_L20_001BA1F0-0x230,&offset);
                            func_00282F20(&work,&work,1.0f);
                            func_0032DA58(*(void **)(D_0018A550-0x170),&offset,&work,0.0f);
                        }
                    } else D_00189E20.owner = 0;
                }
            }
        }
    }
    {
        int i;
        u8 *object;
        if ((u32)(D_L20_001BDCC0.mode-2) < 3) {
            for (i = 0; i < D_L20_001BDCC0.count; ++i) {
                u16 word;
                object = D_L20_001BDCC0.refs.objects[i];
                word = *(u16 *)(object+0xAA);
                if ((u32)(word-0xD0E) < 2) {
                    *(u16 *)(object+0x7C) = word = (s16)word == 0xD0F ? 15 : 0x3FF;
                }
                if (*(s16 *)(object+0xAA) == 0xCE0 && (D_L20_001BDCC0.mode != 3 || D_L20_001BDCC0.state < D_L20_001A9430))
                    func_L03_00326458(object);
            }
        }
        if (D_L20_001BDCC0.mode == 3 && D_L20_001BDCC0.state == D_L20_001A9430) {
            qcopy(matrix,(u8 *)D_L20_001BDCC0.refs.named.target+0x10);
            func_00282CC0(matrix,matrix,&D_L20_001A9420);
            func_0032C700(matrix,0,0x19,0x14,0x14,0x14,0x2D,1,1.0f,20.0f,1,1,0,0);
            {
                YeedilEffectPrefix *effect = &D_L20_001B9E80;
                effect->scale1 = 0.09f;
                effect->count1 = 0x37;
                effect->scale2 = 0.08f;
                effect->count2 = 0x46;
                effect->state1 = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/levels", func_L20_0039BEC8);

/* func_L20_002DEBE0 is in the sibling file L20_002DEBE0-decider.c. */
