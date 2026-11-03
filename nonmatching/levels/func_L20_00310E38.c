/* Claude Opus 5.5 (xhigh effort), task v2214, 2026-11-03; retained near miss.
 * Default -O2 -G8 -ffunction-sections: 1212/1212 bytes, 0/1 USA v1.01 places;
 * 13 reloc-masked rows differ, 11 of them only from truncated branch columns.
 * Changes from v0753 (1204/1212): the CE0 call runs when mode != 3 (semantic
 * fix); func_0032C700 returns void * (fixes the final effect-base allocation);
 * the second loop reads D_L20_001BDCC0 directly (gives retail's v1 base, the
 * s2 copy after blez, the loop-top nop and the plain bne); the mask is stored
 * through a chained assignment, which keeps the u16 ?: in HImode, so jump1
 * cannot form movz and retail's 0xD0F branch appears. A plain ?: store, the
 * separate store and (u16) arm casts all give movz or worse.
 * Remaining, both allocation/scheduling:
 *  1. owner/hero v1/a2 swap. Ours: owner (pseudo 131) is block-local, so
 *     local-alloc gives it v1 and global hero gets a2. Retail fits owner being
 *     a global pseudo allocated after hero (v0 local, v1 hero, a0/a1 globals).
 *  2. else arm loads target before lower: the target load carries REG_DEAD of
 *     the D_L20_001BDCC0 base, so sched1's register weight puts it first.
 *     Retail's source order (lower, target, upper) needs that base to stay
 *     live past the else arm.
 * Next useful experiment: a wording in which the base pointer and owner are
 * referenced in more than one block with no extra instruction.
 * Needs the declarations below. No linked equality is claimed.
 */

#include "common.h"

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
extern void func_L03_00326458(void);
extern void *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);

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
                    func_L03_00326458();
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
