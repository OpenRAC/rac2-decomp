#include "include_asm.h"

#include "common.h"
extern int FloatToInt(f32);
extern u8 *part_l17_spawn_fading(f32, s32, s32, s32);
extern f32 D_L17_001B04B8 __attribute__((sda));
extern void moby_set_state(void *, s32, s32);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 D_L17_001B1E00 __attribute__((sda));
extern s32 D_L17_001B1DE0 __attribute__((sda));
extern s32 D_L17_001B1DD8 __attribute__((sda));
extern s32 D_L17_001B1DD0 __attribute__((sda));
extern char *g_moby_l17_pool __attribute__((sda));
typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(short *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
typedef struct {
    s32 i00;
    f32 f04;
    f32 f08;
    f32 f0C;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[8];
} L17Timer;
typedef struct {
    u8 pad000[0x28];
    u8 b28;
    u8 b29;
    u8 pad02A[6];
    f32 f30;
    u8 b34;
    u8 pad035[0x13];
    u8 b48;
    u8 pad049;
    u8 b4A;
    u8 pad04B[0x15];
    u8 ai[0x10];
    u8 b70;
    u8 b71;
    u8 pad072[4];
    u8 b76;
    u8 b77;
    u8 pad078[4];
    f32 f7C;
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8C;
    f32 f90;
    f32 f94;
    u8 pad098[4];
    f32 f9C;
    u8 pad0A0[8];
    s32 iA8;
    u8 pad0AC[0x20];
    u8 bCC;
    u8 bCD;
    u8 bCE;
    u8 bCF;
    u8 pad0D0[2];
    u8 bD2;
    u8 bD3;
    u8 pad0D4[0x1C];
    s32 iF0;
    f32 fF4;
    u8 pad0F8[0x18];
    Quad v110;
    f32 f120;
    u8 pad124[0x1C];
    L17Timer t140;
    u8 pad170[0x30];
    u8 *target;
    u8 pad1A4[0x16C];
    u8 *p310;
    u8 pad314[0x1C];
    f32 f330;
    u8 pad334[0xC];
    f32 f340;
    u8 pad344[0x8C];
    union { Quad q; f32 f[4]; } v3D0;
    u8 pad3E0[0x20];
    s16 h400;
    u8 pad402[2];
    s16 h404;
    u8 pad406[2];
    u8 *p408;
    f32 f40C;
    u8 pad410[8];
    s32 i418;
    s32 i41C;
    s32 i420;
    s32 i424;
    s32 i428;
    u8 pad42C[4];
    f32 f430;
    u8 pad434[0x1C];
    s32 i450;
} L17Vars;
extern float D_L17_001B0CA8 __attribute__((sda));
extern u8 D_L17_001B0CB8[4] __attribute__((sda));
extern u8 D_L17_001B9BC0[];
extern char D_L17_001B0CC8[];
extern u8 *g_hero_moby NOT_SDA;
extern float coll_probe_ground_height_below(void *, int, float);
extern void MoveCtl_Init(void *);
extern int math_random_int_range(int, int);
extern void hero_copy_field_to_moby(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern void moby_l17_set_group_alert_flag(void *);
extern int weapon_select_aim_target(void *, int, int, int, float, float);
extern void STUB_printf(void *, ...);
extern s32 g_current_map_index MACRO_ADDR;
extern u8 D_0019B4A8[];
extern u8 D_0019B2E8[];
extern u8 *g_path_l17_table[];
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_random_angle(void);
extern s32 flag_set_first_pending(void *);
extern s32 IsPointInCuboid(void *, s32);
extern s32 PlayMobySound(s32, s32, void *);

/* Sets the state record up on the first update (the tuning block in field order), then
   handles damage and keeps a target, falling back to D_0018C0B0 when the record has none. */
void func_PAL_L17_003E89B0(u8 *obj)
{
    L17Vars *p = *(L17Vars **)(obj + 0x68);
    u8 *hit;
    u8 *target;
    int result;

    obj[0x23] = 128;
    if (obj[0x20] == 0) {
        float ground = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
        float radius = F(*(u8 **)(obj + 0x24), 0x24);

        F(obj, 0x18) = ground;
        F(obj, 0x2C) = radius;
        qzero_nc(obj + 0xF0);
        if (p->i428 != -1) {
            F(obj, 0x18) = F((u8 *)g_moby_l17_pool + p->i428 * 256, 0x18) + 1.4f;
            H(obj, 0x34) |= 0x41;
            I(obj, 0x98) = 0;
        }
        p->i420 = 0;
        p->i424 = 0;
        p->b48 = FloatToInt(15.0f);
        p->b4A = FloatToInt(4.0f);
        p->b29 = 1;
        p->b70 = 7;
        p->iA8 = 3;
        p->b71 = 9;
        p->b76 = 12;
        p->b77 = 15;
        p->f7C = 0.50000006f;
        p->f80 = 0.060000002f;
        p->f84 = 0.0044f;
        p->f88 = 0.008f;
        p->f8C = 0.00080000004f;
        p->f90 = 0.35f;
        p->f94 = 0.35f;
        p->f9C = 0.4f;
        p->bCC = 6;
        p->bCD = 11;
        p->bCE = 6;
        p->bCF = 11;
        p->bD2 = 6;
        p->bD3 = 11;
        MoveCtl_Init(&p->t140);
        p->t140.f0C = 2.5f;
        p->t140.f08 = 2.0f;
        p->t140.i00 = FloatToInt(D_L17_001B0CA8 * 1024.0f);
        p->t140.f04 = D_L17_001B0CA8;
        p->t140.f24 = p->f40C * (0.020000001f);
        if (p->v3D0.f[3] != 12439.4f) {
            p->v3D0.q = *(Quad *)(obj + 0x10);
            p->v3D0.f[3] = 12439.4f;
        }
        qcopy_nc(&p->v110, &p->v3D0);
        p->f120 = 0.5f;
        p->h400 = math_random_int_range(100, 583);
        p->i41C = 0;
        hero_copy_field_to_moby(obj);
        p->f340 = F(obj, 0x2C);
        p->f330 = p->f30;
        p->b28 = 0;
        p->i418 = 0;
        p->p310 = D_L17_001B0CB8;
        p->f430 = (float)p->b34;
        moby_set_state(obj, 1, 0);
        if (obj[0x43])
            func_PAL_002A7E68(obj, 0, 0, 0);
        p->i450 = p->i428;
    }
    if (obj[0x31] && fast_vec_dist(obj + 0x10, D_L17_001B9BC0) < 24.0f) {
        moby_update_ground_check(obj);
        obj[0x6F] = 22;
    }
    hit = (u8 *)part_find_owned_effect_slot(obj, 0x230000, 0);
    if (hit && hit[0x28] == 8) {
        obj[0x20] = 9;
        obj[0xBC] = 4;
    }
    result = func_PAL_002B1A50(obj, p->ai, 0);
    if (result) {
        if (result == 5) {
            p->iF0 = 0;
            p->fF4 = 1.0053098f;
        }
        moby_l17_set_group_alert_flag(obj);
    }
    p->h404 = weapon_select_aim_target(obj, -1, 0, 0, 15.0f, 3.0f);
    target = p->target;
    if (!target) {
        STUB_printf(D_L17_001B0CC8);
        target = g_hero_moby;
    }
    p->p408 = target;
}
