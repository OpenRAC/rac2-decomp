#include "include_asm.h"

#include "common.h"
typedef struct {
    f32 x, y, z, w;
} Vec4f __attribute__((aligned(16)));
typedef struct {
    u8 pad0[0xC];
    s16 unkC;
    u8 padE[2];
    Vec4f home;
    u8 pad20[0x60 - 0x20];
    f32 unk60;
    f32 unk64;
    f32 unk68;
    s32 timer;
} GoldBoltVars;
typedef struct {
    u8 pad0[0x24];
    f32 scale;
} GoldBoltClass;
typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 state;
    u8 pad21[3];
    GoldBoltClass *pclass;
    u8 pad28[4];
    f32 scale;
    u8 unk30;
    u8 visible;
    s16 unk32;
    u16 flags;
    u8 pad36[0x42 - 0x36];
    u8 seq;
    u8 prev_seq;
    u8 pad44[0x60 - 0x44];
    u8 anim_flags;
    u8 pad61[7];
    GoldBoltVars *pvars;
    u8 pad6C[0xF0 - 0x6C];
    Vec4f rot;
} GoldBoltMoby;
typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    Vec4f rot;
    u8 padA0[0xC28 - 0xA0];
    s32 anim_flags;
    u8 padC2C[0x22B4 - 0xC2C];
    u8 vehicle_mode;
    u8 pad22B5[0x22BF - 0x22B5];
    u8 unk22BF;
    u8 pad22C0[0x24CC - 0x22C0];
    s32 hp;
} GoldBoltHero;
extern GoldBoltHero D_00189E20;
extern u8 D_001A7B2A MACRO_ADDR;
extern u8 D_001A7A45 MACRO_ADDR;
extern f32 D_L01_001B1A58 __attribute__((sda));
extern f32 D_L01_001B1A68 __attribute__((sda));
extern f32 D_L01_001B1A6C __attribute__((sda));
extern f32 D_L01_001B1A70 __attribute__((sda));
extern f32 D_L01_001B1A74 __attribute__((sda));
extern s32 D_L01_001B1A98 __attribute__((sda));
extern s32 D_L01_001B21B0 MACRO_ADDR;
extern struct {
    s16 f0, f2, f4, pad6;
    s32 busy;
} D_L01_001B22A0 MACRO_ADDR;
extern s32 D_L01_001B1FA8 MACRO_ADDR;
extern s32 D_L01_001B1FA8_gp SDATA(D_L01_001B1FA8);
extern f32 func_002A7940(void);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00282E80(void *, void *);
extern f32 func_00282C48(f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern s32 func_002A77E0(s32);
extern s32 func_00282948(void *);
extern void func_L01_00416B30(void *);
extern void func_L01_00416C08(void *);
extern void func_L01_00417090(void *);
extern void func_L01_00416E78(void *);
extern void func_L01_00416A50(void *);
extern void func_US2_002B1880(s32, s32);
extern void func_00288308(s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void func_0029F338(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_0027D330(s32);
extern void func_L01_002B35E8(s32);
extern void func_L00_002B9D60(void *, void *, s32, s32);
extern void func_00335438(void *, void *, s32, s32, s32);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_003355A8(s32);
extern void func_002A7470(void *, s32, s32, s32);
extern void func_L00_002D2168(s32, s32, f32);
extern s32 func_0029B3E0(s32, s32);
#define SPIN 0.0002908882452175021f

/* Gold bolt update: idle spin, hero pickup check, pickup animation and camera, removal.
 * Adapted from RAC1's gold_bolt_update (GPL-3.0). */
void func_US2_L01_004179C0(GoldBoltMoby *moby) {
    GoldBoltVars *vars = moby->pvars;
    GoldBoltHero *h;
    Vec4f at, look, at2, look2;
    s32 i;

    switch (moby->state) {
    case 0:
        if (D_001A7B2A) {
            goto remove;
        }
        qcopy(&vars->home, &moby->pos);
        vars->home.w = moby->rot.z;
        moby->rot.x = func_002A7940();
        moby->rot.y = func_002A7940();
        moby->rot.z = func_002A7940();
        moby->rot.w = func_002A7940();
        vars->unk68 = D_L01_001B1A68 * SPIN;
        vars->unk64 = D_L01_001B1A6C * SPIN;
        vars->unk60 = D_L01_001B1A70 * SPIN;
        if (moby->unk32 < 0x40) {
            moby->unk32 = 0x40;
        }
        moby->state = 1;
        func_L01_00416B30(moby);
        break;
    case 1:
        moby->scale = moby->pclass->scale * D_L01_001B1A58;
        moby->rot.x = func_00283B98(moby->rot.x, D_L01_001B1A68 * SPIN);
        moby->rot.y = func_00283B98(moby->rot.y, D_L01_001B1A6C * SPIN);
        moby->rot.z = func_00283B98(moby->rot.z, D_L01_001B1A70 * SPIN);
        moby->rot.w = func_00283B98(moby->rot.w, D_L01_001B1A74 * SPIN);
        func_L01_00416C08(moby);
        if (!func_002A77E0(D_L01_001B1A98)) {
            func_L01_00417090(moby);
        }
        if (!(func_00282E80(&moby->pos, &D_00189E20.pos) < 3.0f)) {
            break;
        }
        if (!(func_00282C48(moby->pos.z - D_00189E20.pos.z) < 2.0f)) {
            break;
        }
        if (D_00189E20.hp == 0) {
            break;
        }
        if (D_00189E20.vehicle_mode != 3 && D_00189E20.vehicle_mode != 0) {
            break;
        }
        if (vars->unkC != 0) {
            D_L01_001B21B0 = 180;
            func_US2_002B1880(0x3315, -1);
            func_00288308(50);
            func_002E5CF8(1, 0, moby);
        remove:
            func_0029F338(moby);
            break;
        }
        at.x = func_00283180(vars->home.w) * 2.5f;
        at.y = func_00283198(vars->home.w) * 2.5f;
        at.z = 0.0f;
        func_00282CC0(&at, &at, &vars->home);
        func_00282C88(&look);
        look.z = func_00283B98(vars->home.w, 3.141593f);
        func_0027D330(10);
        if (D_00189E20.vehicle_mode == 3) {
            func_L01_002B35E8(0);
        }
        func_L00_002B9D60(&at, &look, 0x6F, 0);
        func_002E5CF8(0, 0, moby);
        at2.x = func_00283180(vars->home.w) * 1.25f;
        at2.y = func_00283198(vars->home.w) * 1.25f;
        at2.z = 0.0f;
        at2.x += func_00283180(func_00283B98(vars->home.w, 1.5707965f)) * 4.0f;
        at2.y += func_00283198(func_00283B98(vars->home.w, 1.5707965f)) * 4.0f;
        func_00282CC0(&at2, &at2, &vars->home);
        at2.z += 1.0f;
        func_00282C88(&look2);
        look2.z = func_00283BE0(vars->home.w, 1.5707965f);
        func_00335438(&at2, &look2, 1, 0, 0);
        func_00335370(&at2);
        func_003353C8(&look2);
        qcopy(&moby->pos, &D_00189E20.pos);
        qcopy(&moby->rot, &D_00189E20.rot);
        if (moby->prev_seq != 1) {
            func_002A7470(moby, 1, 0, 0);
        }
        func_L00_002D2168(0x7B, 0, 0.0f);
        if (D_001A7A45) {
            moby->flags |= 0x8000;
        }
        D_00189E20.unk22BF = 1;
        D_L01_001B1FA8 = 1;
        moby->state = 2;
        vars->timer = 60;
        break;
    case 2:
        D_L01_001B22A0.busy = 1;
        func_L01_00416E78(moby);
        qcopy(&moby->pos, &D_00189E20.pos);
        qcopy(&moby->rot, &D_00189E20.rot);
        if (moby->seq == 1) {
            func_L01_00416A50(moby);
            if (!func_002A77E0(10)) {
                func_L01_00417090(moby);
            }
            if (moby->anim_flags & 2) {
                if (moby->prev_seq != 0) {
                    func_002A7470(moby, 0, 0, 0);
                }
                moby->visible = 0;
                moby->flags |= 1;
                for (i = 0; i < 4; i++) {
                    func_L01_00417090(moby);
                }
            }
        }
        h = &D_00189E20;
        if (h->anim_flags & 2) {
            func_L00_002D2168(0, 0, 30.0f);
        }
        if (moby->seq != 0 || !func_00282948(&vars->timer)) {
            break;
        }
        D_L01_001B21B0 = 180;
        func_US2_002B1880(0x129A, -1);
        func_00288308(50);
        D_L01_001B1FA8_gp = 0;
        func_L00_002B9D60(&h->pos, &h->rot, 0, 0);
        func_003355A8(0);
        func_0029B3E0(0, -1);
        func_0029F338(moby);
        break;
    }
}
