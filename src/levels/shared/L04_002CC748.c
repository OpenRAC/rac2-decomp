#include "common.h"

extern void func_00282D30(void *, void *, float);
extern float D_L04_001AD848 MACRO_ADDR, D_L04_001AD84C MACRO_ADDR;
extern char D_L04_001B9680[];
extern void func_002830C0(void *, void *, void *);
extern int func_00282BE0(void *);
extern void func_L04_0032F994(int, int);

extern int D_001A8F00[] __attribute__((sda));
extern unsigned char D_001A7A33 MACRO_ADDR;
extern unsigned char D_001A7A32 MACRO_ADDR;
extern char D_L04_001C3D40[];
extern float func_L00_0037E668(void);
extern float func_L00_0037E5F0(float);
extern void func_L00_002A6708(void);
extern void func_00282CF0(f32 *,f32 *,f32 *);
extern void func_L00_002D36E0(void *,int,float,float,float);
extern void func_L04_002E7C08(int,int);
extern char *func_002A9640(void *,int,int);
extern void func_L00_002A4EF8(int);
extern void func_L00_002B9B88(int,int);
extern void func_L00_002B2C58(void *,int,float,float);
extern void func_L00_002D3C68(void *,void *,float);
#define AB(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define AH(p,o) (*(short *)((char *)(p)+(o)))
#define AI(p,o) (*(int *)((char *)(p)+(o)))
#define AF(p,o) (*(float *)((char *)(p)+(o)))
#define AP(p,o) (*(char **)((char *)(p)+(o)))
typedef union {
    unsigned char b[0x2500];
    short h[0x1280];
    int i[0x940];
    float f[0x940];
    char *p[0x940];
} GroundHero;
#define GROUND_HERO (*(GroundHero *)&D_00189E20)

typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8, field7AC, field7B0, field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290, field2294, field2298, field229C;
} RippleHero;
#define RIPPLE_HERO (*(RippleHero *)&D_00189E20)
extern void func_0026FEB8(void *, int, int, int, int);
extern void func_L04_003A1578(void *, int, int);
extern float func_002A7878(float, float);
extern void func_002FD1B8_ripple(void *, int, int, float, float, float, float) __asm__("func_002FD1B8");
extern int func_002A8AF0(void *, void *, int);
extern float func_00283B98(float, float);
extern int func_002A77E0(int);
extern char D_L04_001ADA00[];
extern char *D_L04_001FE340[];
#define WBYTE(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define WSHORT(p,o) (*(short *)((char *)(p)+(o)))
#define WINT(p,o) (*(int *)((char *)(p)+(o)))
#define WFLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define WPTR(p,o) (*(char **)((char *)(p)+(o)))

extern u32 func_00282978(u8 *);
extern void func_002B9180(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);

extern void func_00282F20(float *, float *, float);
extern float func_00282DB0(void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_L00_002D3A58(void *);
extern void func_L00_002D3BD8(void *, void *, float);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002B54F8(float, float);
extern float func_002AA2E8(float *, float, float);
extern void func_L00_002B41B8(float, float);
extern void func_L00_002D3798(void *, void *, float);
extern void func_L00_002B3EF8(int, float, float, float);
extern void func_L00_002B6198(float);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283C80(float, float);
extern float func_00283BE0(float, float);
extern void func_L00_002AA0F0(float, float, float);
extern void func_L00_002B47A8(void *, void *, int, float, float);
extern int func_00278E78(void);
extern void func_L00_002B39F0(int, float);
extern int D_001A8FF0 MACRO_ADDR;
extern float D_001A7DC0 MACRO_ADDR;
extern unsigned char D_L04_001B9540[];
typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} HopVector;
typedef struct {
    unsigned char pad0[0x20];
    HopVector field20;
    unsigned char pad30[0x68];
    float yaw;
    unsigned char pad9C[0x54];
    HopVector velocity;
    unsigned char pad100[0x60];
    HopVector momentum;
    unsigned char pad170[0x4];
    float flat_speed;
    unsigned char pad178[0x18];
    HopVector move_dir;
    float move_yaw;
    float yaw_rate;
    float yaw_error;
    unsigned char pad1AC[0x4];
    float target_speed;
    float ground_speed;
    int state_timer;
    unsigned char pad1BC[0x164];
    float field320;
    unsigned char pad324[0x24];
    short field348;
    short field34A;
    unsigned char pad34C[0x108];
    float field454;
    unsigned char pad458[0x18];
    HopVector field470;
    HopVector field480;
    unsigned char pad490[0x4];
    float field494;
    unsigned char pad498[0x6];
    unsigned char field49E;
    unsigned char pad49F[0xF];
    short field4AE;
    unsigned char pad4B0[0xC];
    float ledge_jump_speed;
    float high_jump_drift_yaw;
    float takeoff_yaw;
    unsigned char pad4C8[0xC];
    int field4D4;
    float air_target_speed;
    float high_jump_drift_speed;
    unsigned char pad4E0[0x10];
    HopVector field4F0;
    unsigned char pad500[0x20];
    float jump_gravity;
    short field524;
    unsigned char pad526[0x2];
    short field528;
    unsigned char pad52A[0x3];
    unsigned char field52D;
    unsigned char pad52E[0x532];
    HopVector move_impulse;
    unsigned char padA70[0x14];
    float fieldA84;
    unsigned char padA88[0x1B0];
    float anim_frame;
    unsigned char padC3C[0x804];
    HopVector field1440;
    unsigned char pad1450[0x4];
    short field1454;
    unsigned char pad1456[0x2];
    float field1458;
    unsigned char pad145C[0x36];
    unsigned char field1492;
    unsigned char pad1493[0xE01];
    int state;
    unsigned char pad2298[0x4];
    int control_mode;
    unsigned char pad22A0[0x23];
    unsigned char field22C3;
    unsigned char pad22C4[0x1F4];
    float stick_magnitude;
} HopPlayer;
typedef struct {
    unsigned char pad0[0x158];
    float yaw;
    unsigned char pad15C[0x370 - 0x15C];
    HopVector direction;
} HopSavedState;
#define HOP_SAVED (*(HopSavedState *)D_L04_001B9540)
#define HOP_PLAYER (*(HopPlayer *)&D_00189E20)

extern f32 func_002AA898(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);

typedef struct {
    u32 unknown;
    s32 data_offset;
    s32 length;
    s32 extra;
} PackedHeaderCountView;


typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8;
    f32 field7AC;
    f32 field7B0;
    f32 field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290;
    u32 field2294;
} D00189E20;
extern D00189E20 D_00189E20;
extern void func_002AEE70(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);
extern void func_002AEF28(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);
void func_L04_002CE810(void) {
    if (D_00189E20.field2294 != 0x7C)
        return;
    func_002AEE70(D_00189E20.field2290, &D_00189E20.field7A8, &D_00189E20.field7AC,
                  0.3f, 0.116355299949646f, -1.0f);
}

void func_L04_002CE870(void) {
    if (D_00189E20.field2294 != 0x7C)
        return;
    func_002AEF28(D_00189E20.field2290, &D_00189E20.field7B0, &D_00189E20.field7B4,
                  0.174532949924469f, 0.02617994323372841f, 0.03490659222006798f);
}

/* Check the hero's surface contact and optionally apply its movement impulse. */
int func_L04_002D91B8(int update) {
    char *entry, *m;
    HopVector delta;
    int special;
    float amount;

    if (GROUND_HERO.i[0x229C / 4] == 20) return 0;
    if (GROUND_HERO.i[0x229C / 4] == 7) return 0;
    if (GROUND_HERO.i[0x2294 / 4] == 0x31) return 0;
    if (GROUND_HERO.h[0x1DC / 2]) return 0;
    if (D_001A8F00[0]) return 0;
    GROUND_HERO.i[0x249C / 4] = 0;
    m = GROUND_HERO.p[0x2290 / 4];
    if (AB(m, 0xA8) == 255) return 0;
    entry = D_L04_001C3D40 + AB(m, 0xA8) * 64;
    if (AP(entry, 0x38) != m) return 0;
    if (!(AI(entry, 0x24) & 9)) return 0;
    if (AF(entry, 0x2C) != 0.0f) {
        D_001A7A33 = 0;
        D_001A7A32 = 1;
    }
    if (func_L00_0037E668() != 0.0f && !GROUND_HERO.b[0x22B4]) {
        AF(entry, 0x2C) = func_L00_0037E5F0(AF(entry, 0x2C));
        if (AF(entry, 0x2C) == 0.0f) return 0;
    }
    GROUND_HERO.p[0x249C / 4] = AP(entry, 0x20);
    if (!update) return 1;
    func_L00_002A6708();
    special = 0;
    if (AI(entry, 0x30) & 1) {
        qcopy(&delta, entry + 0x10);
        if (AF(entry, 0x1C) == 5627.925f) special = 1;
    } else if (AP(entry, 0x20)) {
        func_00282CF0(delta.f, (float *)(GROUND_HERO.b + 0x80),
                     (float *)(AP(entry, 0x20) + 0x10));
    } else {
        func_L00_002D36E0(&delta, 0, -1.0f, 0.0f, 0.0f);
    }
    if (!GROUND_HERO.b[0x22B4]) {
        char *m = GROUND_HERO.p[0x249C / 4];
        if (m && (AH(m, 0xAA) == 0x4EB || AH(m, 0xAA) == 0x558)) {
            func_L04_002E7C08(0x7D, 1);
            return 1;
        }
        if ((GROUND_HERO.i[0x2294 / 4] == 1 ||
             GROUND_HERO.i[0x2294 / 4] == 0x1D || GROUND_HERO.i[0x1500 / 4]) &&
            !(AI(entry, 0x24) & 8)) {
            char *m = func_002A9640(GROUND_HERO.p[0x2290 / 4], 1, 0);
            if (m) func_L00_002A4EF8(func_00283CF0(AF(m, 0x2C)));
            if (!GROUND_HERO.i[0x24CC / 4]) func_L04_002E7C08(0x16, 1);
            GROUND_HERO.h[0x1DC / 2] = 0x4D;
            if (!GROUND_HERO.h[0x21C / 2]) GROUND_HERO.h[0x21C / 2] = 0x12;
            func_L00_002B9B88(20, 0);
            return 0;
        }
        if (GROUND_HERO.i[0x229C / 4] == 0x12) func_L04_002E7C08(0x72, 1);
        else if (GROUND_HERO.i[0x229C / 4] == 0x11) func_L04_002E7C08(0x73, 1);
        else if (AI(entry, 0x24) & 8) func_L04_002E7C08(0x8C, 1);
        else func_L04_002E7C08(0x16, 1);
        if (GROUND_HERO.i[0x2294 / 4] == 0x8C) {
            qzero(&delta);
        } else {
            amount = 0.055000003427267075f;
            if (GROUND_HERO.b[0x1497]) amount = 0.0f;
            func_L00_002B2C58(&delta, special, amount, 0.028333336f);
            if (special && AB(entry, 0x28) == 4)
                func_L00_002D3C68(&delta, &delta, 2.0f);
        }
    }
    func_00282CC0(GROUND_HERO.b + 0xF0, GROUND_HERO.b + 0xF0, &delta);
    func_00282CC0(GROUND_HERO.b + 0x110, GROUND_HERO.b + 0x110, &delta);
    return 1;
}


/* func_L04_002DB970 is defined in L04_002CC748-collision-g8.c. */

/* func_L04_002DBE70 is defined in L04_002CC748-movement.c. */

/* Per-state airborne steering; shares the hop-velocity state cases with
   rac1-decomp's hero_update_hop_velocity. */
void func_L04_002DCE78(void) {
    float probe_start[4], probe_end[4], yaw, speed, rate;

    if (HOP_PLAYER.state == 10) {
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(HOP_PLAYER.momentum.f, HOP_PLAYER.move_impulse.f);
        HOP_PLAYER.ground_speed = HOP_PLAYER.flat_speed;
    } else if (HOP_PLAYER.state == 16) {
        if (HOP_PLAYER.state_timer >= 55) {
            func_002AA2E8(&HOP_PLAYER.jump_gravity, 0.0069444444961845875f, 0.0019444444915279746f);
        }
        if (HOP_PLAYER.state_timer < 55) {
            HOP_PLAYER.target_speed = HOP_PLAYER.field454;
        } else {
            HOP_PLAYER.target_speed = 0.05833333730697632f;
        }
        func_L00_002B41B8(0.012222222983837128f, 0.0125f);
        func_L00_002D3BD8(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, 0.0f);
        func_L00_002D3798(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, HOP_PLAYER.ground_speed);
    } else if (HOP_PLAYER.state == 27) {
        if (HOP_PLAYER.state_timer >= 41) {
            func_L00_002B3EF8(0, 0.04f, 0.2f, 0.2501639127731323f);
            func_L00_002B6198(0.0055555556900799274f);
        }
        if (HOP_PLAYER.anim_frame >= 13.0f && HOP_PLAYER.anim_frame <= 30.0f) {
            if (HOP_PLAYER.anim_frame > 27.0f) {
                func_002AA2E8(&HOP_PLAYER.ledge_jump_speed, 0.0f, 0.002222222276031971f);
            } else {
                func_002AA2E8(&HOP_PLAYER.ledge_jump_speed, 0.03333333507180214f, 0.002222222276031971f);
            }
        }
        probe_start[1] = 0.0f;
        probe_start[0] = HOP_PLAYER.ledge_jump_speed;
        probe_start[2] = func_00282DB0(HOP_PLAYER.velocity.f, HOP_PLAYER.field20.f);
        func_00283098(HOP_PLAYER.velocity.f, probe_start, &HOP_PLAYER);
    } else if (HOP_PLAYER.state == 11) {
        HOP_PLAYER.move_yaw = HOP_PLAYER.takeoff_yaw;
        qcopy(HOP_PLAYER.move_dir.f, HOP_PLAYER.field480.f);
        func_L00_002B3EF8(0, 0.04f, 0.2f, 0.116355299949646f);
        if (HOP_PLAYER.field4D4 != 3) {
            HOP_PLAYER.ground_speed = HOP_PLAYER.air_target_speed;
        } else {
            HOP_PLAYER.ground_speed = 0.0f;
        }
        if (HOP_PLAYER.field52D) {
            float drift = HOP_PLAYER.stick_magnitude * 0.0833333358168602f;

            if (drift < 0.03333333507180214f) drift = 0.03333333507180214f;
            func_002AA2E8(&HOP_PLAYER.high_jump_drift_speed, drift, 0.010277777910232544f);
            HOP_PLAYER.ground_speed = HOP_PLAYER.flat_speed;
        } else if (HOP_PLAYER.field49E && HOP_PLAYER.field4AE < 12) {
            func_002AA2E8(&HOP_PLAYER.high_jump_drift_speed, 0.0f, 0.002222222276031971f);
        } else {
            func_002AA2E8(&HOP_PLAYER.high_jump_drift_speed, 0.07f, 0.002222222276031971f);
        }
        if (!HOP_PLAYER.field22C3) {
            HOP_PLAYER.velocity.f[0] = func_00283180(HOP_PLAYER.high_jump_drift_yaw) * HOP_PLAYER.high_jump_drift_speed;
            HOP_PLAYER.velocity.f[1] = func_00283198(HOP_PLAYER.high_jump_drift_yaw) * HOP_PLAYER.high_jump_drift_speed;
        } else {
            func_L00_002D3BD8(probe_start, HOP_PLAYER.field470.f, HOP_PLAYER.high_jump_drift_speed);
            func_L00_002D3B58(probe_start, probe_start, 0.0f);
            func_L00_002D3BD8(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, 0.0f);
            func_00282CC0(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, probe_start);
        }
        if (!HOP_PLAYER.field22C3 && !HOP_PLAYER.field52D) {
            float drift = HOP_PLAYER.air_target_speed * func_00283198(func_00283C80(HOP_PLAYER.takeoff_yaw, HOP_PLAYER.high_jump_drift_yaw));

            HOP_PLAYER.velocity.f[0] += func_00283180(HOP_PLAYER.takeoff_yaw) * drift;
            HOP_PLAYER.velocity.f[1] += func_00283198(HOP_PLAYER.takeoff_yaw) * drift;
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(HOP_PLAYER.momentum.f, HOP_PLAYER.move_impulse.f);
    } else if (HOP_PLAYER.state == 17) {
        HOP_PLAYER.move_yaw = HOP_PLAYER.field4F0.f[3];
        qcopy(HOP_PLAYER.move_dir.f, HOP_PLAYER.field4F0.f);
        if (HOP_PLAYER.state_timer >= 10) {
            func_L00_002B3EF8(-1, 0.041999999433755875f, 0.2f, 0.1978040188550949f);
        }
        if (HOP_PLAYER.state_timer >= 9) {
            if (!HOP_PLAYER.field348) {
                HOP_PLAYER.velocity.f[0] = func_00283180(HOP_PLAYER.move_yaw) * 0.08166667073965073f;
                HOP_PLAYER.velocity.f[1] = func_00283198(HOP_PLAYER.move_yaw) * 0.08166667073965073f;
            } else {
                func_L00_002D3BD8(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, 0.0f);
                func_00282F20(probe_start, HOP_PLAYER.move_dir.f, 0.08166667073965073f);
                func_00282CC0(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, probe_start);
            }
        }
        HOP_PLAYER.ground_speed = HOP_PLAYER.flat_speed;
    } else if (HOP_PLAYER.state == 0x81 && !D_001A8FF0) {
        func_L00_002B3EF8(0, 0.04f, 0.2f, HOP_PLAYER.field494);
        HOP_PLAYER.ground_speed = 0.0f;
    } else {
        if (HOP_PLAYER.state == 44) {
            yaw = HOP_PLAYER.yaw;
            HOP_PLAYER.yaw_error = func_002AA898(&yaw, HOP_PLAYER.move_yaw, &HOP_PLAYER.yaw_rate,
                                      0.018f, 0.2f, 0.12217307090759277f, 0);
            {
                float delta = func_00283BE0(yaw, HOP_PLAYER.yaw);

                func_L00_002AA0F0(0.0f, 0.0f, delta);
            }
        } else {
            float saved = HOP_PLAYER.move_yaw;

            qcopy(probe_start, HOP_PLAYER.move_dir.f);
            if (HOP_PLAYER.field1454) {
                HOP_PLAYER.move_yaw = HOP_SAVED.yaw;
                qcopy(HOP_PLAYER.move_dir.f, HOP_SAVED.direction.f);
            }
            func_L00_002B3EF8(0, 0.04f, 0.2f, HOP_PLAYER.field494);
            if (HOP_PLAYER.field1454) {
                HOP_PLAYER.field1458 = saved;
                qcopy(HOP_PLAYER.field1440.f, probe_start);
                HOP_PLAYER.move_yaw = saved;
                qcopy(HOP_PLAYER.move_dir.f, HOP_PLAYER.field1440.f);
            }
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(HOP_PLAYER.momentum.f, HOP_PLAYER.move_impulse.f);
        rate = 0.0055555556900799274f;
        if (HOP_PLAYER.target_speed < D_001A7DC0 * 0.0033333336468786f) {
            if (HOP_PLAYER.control_mode == 2) {
                float decel = HOP_PLAYER.fieldA84;

                if (HOP_PLAYER.field1492) decel = 0.000047222223947152495f;
                speed = func_L00_002D3A58(HOP_PLAYER.velocity.f);
                func_002AA2E8(&speed, 0.0f, decel);
                func_L00_002D3BD8(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, speed);
                return;
            }
            if (HOP_PLAYER.field34A) {
                rate = 0.003055555745959282f;
            } else if (HOP_PLAYER.field524) {
                rate = 0.0005555555690079927f;
            } else {
                rate = 0.002222222276031971f;
            }
        }
        if (HOP_PLAYER.field528 && HOP_PLAYER.field1492) {
            rate = 0.00013888889225199819f;
            if (HOP_PLAYER.stick_magnitude > 0.9f) {
                func_L00_002B47A8(probe_start, probe_end, 0, 0.5f, -1.5f);
                probe_start[0] += func_00283180(HOP_PLAYER.move_yaw) * 0.7f;
                probe_start[1] += func_00283198(HOP_PLAYER.move_yaw) * 0.7f;
                probe_end[0] += func_00283180(HOP_PLAYER.move_yaw) * 0.7f;
                probe_end[1] += func_00283198(HOP_PLAYER.move_yaw) * 0.7f;
                if (func_002761F8(probe_start, probe_end, 2, 0, 0) && func_00278E78() != 7) {
                    HOP_PLAYER.target_speed = 0.0833333358168602f;
                    rate = 0.0027777778450399637f;
                }
            }
            if (HOP_PLAYER.state == 15) {
                func_L00_002B39F0(0, 0.0416666679084301f);
                rate = 0.0008333333535119891f;
            }
            if (HOP_PLAYER.field320 > 0.2617994248867035f) {
                HOP_PLAYER.target_speed = 0.0f;
                rate = HOP_PLAYER.field320 * 0.003183098277077079f;
            }
        }
        func_L00_002B6198(rate);
    }
}
#undef HOP_PLAYER
#undef HOP_SAVED

#define NOT_SDA __attribute__((section(".data")))

extern int r1_D_0012FCF0 NOT_SDA;

/* rac1-decomp src/core/00118A40.c: func_00118EC0 */
void func_L04_002FB920(void) {
    r1_D_0012FCF0 = 0;
}

typedef int L04Quad __attribute__((mode(TI)));

/* the record the level's spawner builds: flag bytes, a halfword, a float,
   two sixteen-byte blocks and the fields that follow them */
typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    u8  pad04[4];
    u8  field08;
    u8  field09;
    u16 field0A;
    f32 field0C;
    L04Quad field10;
    L04Quad field20;
    f32 field30;
    f32 field34;
    u16 field38;
} L04Record;

/* the second half of the record, at +0x20 */
typedef struct {
    u8  pad00[0xC];
    u32 field0C;
    f32 field10;
    f32 field14;
    u16 field18;
} L04RecordTail;

/* the record the level's other spawner builds: the same flag bytes, a word
   and a colour, then a sixteen-byte block and the fields that follow it */
typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    u32 field04;
    u8  field08;
    u8  field09;
    u16 field0A;
    u32 field0C;
    L04Quad field10;
    u8  pad20[0xC];
    f32 field2C;
    L04Quad field30;
} L04Spawned;

/* the block at +0x30: a sixteen-byte vector and the float inside its last word */
typedef struct {
    L04Quad v;
} L04Vector;

extern void *func_002B9030(s32 kind);
extern s32 func_00283CF0(f32 value);
extern s32 func_002A77E0(s32 limit);
extern void func_00282F20(f32 *dst, f32 *a, f32 len);
extern void func_00282CF0(f32 *dst, f32 *a, f32 *b);

/* the level's pointer to the byte the record carries in its second flag byte */
extern u32 ref_L04_00362768_00;
extern u32 ref_L04_00362940_00;

/* func_L04_0030C4C0 is matched in L04_0030C4C0.c (built with -frac2-qcopy and -g). */

INCLUDE_ASM("asm/levels", func_L04_0030C948);

ASM_FUNC("asm/levels", func_L04_0030EDE0);

ASM_FUNC("asm/levels", func_L04_0030FA30);

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} MobStruct;

typedef struct {
    u8 pad00[0x44];
    s16 count;
    u8 pad46[0x18C - 0x46];
    u32 mobs[1];          /* the array the count field bounds */
} MobListStruct;

/* the list of mobs: level 04 has it at 0x001BD380, every level at its own address */
extern MobListStruct ref_L04_0031D630_00;

/* shared callee, named by its catalogue row (04:0031D3C8) */
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *mob);
extern void func_L00_00326048(void *mob, void *p, s32 a2, s32 a3, f32 alpha);

/* Walks the list of mobs: the ones of type 0xE29 get the 0x800 flag, the ones of type
   0xD54 are handed to func_002E64A0, and the ones of type 0xFA0 with a 0x68 pointer
   get that pointer's block (from +0xC) to func_L00_00326048. */
void func_L04_0031D630(void) {
    s32 i;

    func_L00_002FC980();
    for (i = 0; i < ref_L04_0031D630_00.count; i++) {
        MobStruct *mob = (MobStruct *)ref_L04_0031D630_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29) {
            mob->flags |= 0x800;
        }
        if (mob->type == 0xD54) {
            func_002E64A0(mob);
        }
        if (mob != 0 && mob->type == 0xFA0 && mob->p68 != 0) {
            func_L00_00326048(mob, (void *)((u8 *)mob->p68 + 0xC), 0x80AAAAD2, 0x80396464, 0.0610865355f);
        }
    }
}

ASM_FUNC("asm/levels", func_L04_0032F1D8);

ASM_FUNC("asm/levels", func_L04_0032F340);

ASM_FUNC("asm/levels", func_L04_0032F3C0);

ASM_FUNC("asm/levels", func_L04_0032F62C);

ASM_FUNC("asm/levels", func_L04_0032F994);


/* sched1 hoists the last statement of */
void func_L04_0033CB88(char *p)
{
    *(int *)(p + 0) = 640;
    *(float *)(p + 8) = 0.5f;
    *(int *)(p + 20) = 0;
    *(float *)(p + 4) = 1.0f;
    *(float *)(p + 12) = 0.5f;
    *(int *)(p + 16) = 0;
    *(float *)(p + 36) = 2.7f;
    *(int *)(p + 24) = 0;
    *(float *)(p + 32) = 0.3f;
    *(float *)(p + 28) = 0.3f;
    *(float *)(p + 40) = 1.57f;
    *(float *)(p + 44) = 0.1f;
}

/* func_L04_0033CC00 is defined in L04_002CC748-movement.c. */

/* func_L04_0033D0C0 is defined in L04_0033D0C0.c. */

extern s32 func_002A8600(u32 *out, s32 kind, s32 arg2, s32 arg3);
extern s32 func_002A86E8(u32 *out, u32 value, s32 arg2, s32 arg3);
s32 func_L04_0033D4B0(u8 *a0) {
    u32 out = 0;
    if (func_002A8600(&out, *(u8 *)(a0 + 0x21), 0, 0) == -1)
        return 0;
    if (out != (u32)a0)
        return out;
    if (func_002A86E8(&out, out, 0, 0) != -1)
        return out;
    return 0;
}

INCLUDE_ASM("asm/levels", func_L04_003429F8);

extern void func_00282D60(void *buf, u32 value, float scale);
extern void func_00283DB8(void *buf, float value);
void func_L04_00343498(u32 value, float f) {
    u8 buf[16];
    func_00282D60(buf, value, 0.0009765625f);
    func_00283DB8(buf, f);
}

/* func_L04_00344568 is in L04_002CC748-axis.c. */

extern void func_00283658(void *dst, void *src);
extern f32 func_00282DB0(void *a, void *b);
extern f32 func_00282C10(f32 x);
extern f32 func_00283248(f32 a, f32 b);
extern void func_00282DD8(void *dst, void *a, void *b);
extern void func_00283430(void *dst, void *src);
extern void func_00283788(void *a, void *b, void *c);
extern void func_002830C0(void *a, void *b, void *c);
extern void func_002AB6D8(f32 *src, f32 *out);

/* Copies the caller's matrix into a local one, takes the two aim angles off
   the target vector, springs one of them, and turns the copy by the three
   angles before handing its axes to the caller. */
void func_L04_00347AB8(void *a0, void *a1, void *a2, void *a3, f32 f1, f32 f2, f32 f3)
{
    f32 pos;
    f32 buf0[16];
    f32 buf1[16];
    f32 mat[16];
    f32 vec[4];
    f32 res[4];
    f32 v;
    f32 d;
    f32 ang;
    f32 base;

    v = *(f32 *)((u8 *)a1 + 8);
    pos = 0.0f;
    func_00283658(mat, a0);
    d = func_00282DB0(a3, mat + 8);
    base = func_00283248(d, func_00282C10(1.0f - d * d));
    func_00282DD8(res, a3, mat + 8);
    if (res[2] < 0.99f) {
        ang = func_00283248(res[0], res[1]);
        vec[0] = 0.0f;
        vec[1] = 0.0f;
        vec[2] = -ang;
        func_00283430(buf1, vec);
        func_00283788(mat, buf1, mat);
        func_002830C0(res, res, buf1);
        d = func_00283248(res[2], res[0]);
        vec[0] = 0.0f;
        vec[1] = -d;
        vec[2] = 0.0f;
        func_00283430(buf0, vec);
        func_00283788(mat, buf0, mat);
        func_002830C0(res, res, buf0);
    } else {
        ang = 0.0f;
        d = 0.0f;
    }
    func_002AA898(&pos, base, (f32 *)a2, f1, f2, f3, 0);
    vec[0] = 0.0f;
    vec[1] = 0.0f;
    vec[2] = pos;
    func_00283430(buf1, vec);
    func_00283788(mat, buf1, mat);
    vec[1] = d;
    vec[2] = 0.0f;
    func_00283430(buf0, vec);
    func_00283788(mat, buf0, mat);
    vec[1] = 0.0f;
    vec[2] = ang;
    func_00283430(buf1, vec);
    func_00283788(mat, buf1, mat);
    func_002AB6D8(mat, (f32 *)a1);
    *(f32 *)((u8 *)a1 + 8) = v;
}

typedef struct {
    u8 pad00[0x18E];
    s16 head;
    s32 count;
    u8 pad194[0x13C];
    f32 history[30];
} PadHistory;

extern PadHistory D_00138180;

/* Returns the float steps entries back from the head of a 30-entry history ring (steps capped
   at the ring's count); RAC1's read_pad_float_history. */
float func_L04_003524D0(int steps)
{
    if (D_00138180.count < steps)
        steps = D_00138180.count;
    return D_00138180.history[(D_00138180.head - steps + 30) % 30];
}

extern s32 func_001163B0(void);
extern void func_0029FCC0(void *moby, s32 joint, void *out);
/* the level's pointer to the byte the record carries in its second flag byte */
extern u8 *ref_L04_00358868_00[];

/* the block at +0x20 of the record of kind 0x1A: what func_002BE7E8 reads to keep
   the effect on its target or on one of the target's joints */
typedef struct {
    void *target;
    u16 timer;
    s16 joint;
    u32 duration;
    s32 alpha;
} L04Follow;

typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    s32 color;
    u8  seed;
    u8  field09;
    u16 field0A;
    f32 field0C;
    s32 position[4];
    L04Follow follow;
} L04Effect1A;

/* Builds the record of kind 0x1A that follows TARGET for DURATION frames, with COLOR
   and its alpha byte: it starts at the target, or at its joint JOINT moved 0.4 toward
   D_L04_001B9680 when JOINT is not -1. */
L04Effect1A *func_L04_00358868(void *target, s32 color, u32 duration, u32 joint, f32 value)
{
    L04Effect1A *p = func_002B9030(0x1A);

    if (p != 0) {
        L04Follow *f = &p->follow;

        f->target = target;
        f->alpha = color >> 24;
        f->joint = joint;
        f->duration = duration;
        f->timer = duration;
        if ((s16)joint == -1) {
            qcopy(p->position, (u8 *)target + 0x10);
        } else {
            f32 pos[4], dir[4];

            func_0029FCC0(f->target, (s16)joint, pos);
            func_00282CF0(dir, (f32 *)D_L04_001B9680, pos);
            func_00282F20(dir, dir, 0.4f);
            func_00282CC0(p->position, pos, dir);
        }
        p->seed = func_001163B0();
        p->color = color;
        p->field09 = func_00283CF0(4.0f) + 0x70;
        p->field03 = 0x48;
        p->field0C = value;
        p->field01 = 0;
        p->field02 = *ref_L04_00358868_00[0];
    }
    return p;
}


extern s32 func_00283CF0(f32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002A77E0(s32);
/* func_L04_0035F3E0 is defined in L04_0035F3E0-qcopy.c. */

void *func_L04_00362768(void *a0, void *a1, u32 a2, f32 f3) {
    L04Record *p = (L04Record *)(u32)func_002B9030(0x5E);
    L04RecordTail *q;
    L04Quad t;

    if ((u32)p != 0) {
        p->field10 = *(L04Quad *)a0;
        q = (L04RecordTail *)((u8 *)p + 0x20);
        p->field09 = (u8)(func_00283CF0(2.0f) + 0x40);
        p->field03 = 0x48;
        p->field01 = 0;
        p->field02 = *(u8 *)ref_L04_00362768_00;
        p->field0C = f3 * 105000.0f;
        p->field08 = (u8)func_002A77E0(0xFF);
        p->field0A = (u16)a2;
        t = *(L04Quad *)a1;
        p->field20 = t;
        q->field0C = 0;
        q->field10 = 0.5f;
        q->field14 = f3;
        q->field18 = (u16)(func_002A77E0(2) - 1);
    }
    return (u32)p;
}

void *func_L04_00362940(void *a0, void *a1, u32 a2, f32 f3) {
    L04Spawned *p = (L04Spawned *)(u32)func_002B9030(0x5F);
    L04Vector *q;
    f32 v[4];

    if ((u32)p != 0) {
        p->field04 = 0x7F003CFF;
        p->field0C = 0x7F003CFF;
        p->field09 = (u8)(func_00283CF0(2.0f) + 0x20);
        p->field03 = 0x48;
        p->field01 = 3;
        q = (L04Vector *)((u8 *)p + 0x30);
        p->field02 = *(u8 *)ref_L04_00362940_00;
        q->v = *(L04Quad *)a1;
        *(f32 *)((u8 *)q + 0xC) = f3;
        p->field10 = *(L04Quad *)a0;
        func_00282F20(v, (f32 *)q, 0.5f);
        func_00282CF0((f32 *)((u8 *)p + 0x20), (f32 *)a0, v);
        p->field0A = (u16)a2;
        *(f32 *)((u8 *)p + 0x1C) = 0.005f;
        p->field08 = (u8)(*(u8 *)&p->field0A - 5);
        p->field2C = 1.0f;
    }
    return (u32)p;
}

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 word; float values[4]; } Vec4;
extern int func_00282978_2a50(void *);
extern void func_002B9180(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20_2a50(void *, void *, float);
extern void func_00282CF0_2a50(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0_2a50(float);

/* Same body as func_002C7620, with this function's own callees. */
void func_L04_00362A50(char *self) {
    Vec4 buf, offset;
    char *s0;
    char *s2 = self + 0x30;
    float t;
    int color;

    if (func_00282978_2a50(self + 0xA) != 0) {
        func_002B9180(self);
        return;
    }
    s0 = self + 0x10;
    buf.word = *(TI128 *)s0;
    func_00282CC0(s0, s0, s2);
    *(float *)(s2 + 8) = *(float *)(s2 + 8) - *(float *)(s2 + 0xC);
    t = func_00282DF0(s2);
    func_00282F20_2a50(&offset, s2, t * 0.4f);
    func_00282CF0_2a50(self + 0x20, s0, &offset);
    *(float *)(self + 0x2C) = 1.0f;
    if (*(short *)(self + 0xA) < *(unsigned char *)(self + 8)) {
        t = func_00283CE0(*(short *)(self + 0xA)) / func_00283CE0(*(unsigned char *)(self + 8));
        color = (func_00283CF0_2a50(t * 127.0f) << 24) | 0x00FFFFFF;
        *(int *)(self + 0xC) = color;
        *(int *)(self + 4) = color;
    }
}

/* func_L04_00363690 is defined in L04_00363690-qcopy.c. */

/* func_L04_00363CA0 is matched in L04_00363CA0.c (built with -frac2-qcopy). */

/* func_L04_00365300 is defined in L04_00365300.c. */

/* func_L04_00378838 is defined in L04_00378838-g8.c (it reads its list through $gp). */

/* func_L04_003A0FC8 is in L04_003A0FC8-g8.c. */


extern void func_00115484(void *dst, s32 value, s32 size);

/* the header of one 0x1190-byte ripple patch */
typedef struct {
    u8 pad00[0x20];
    s32 field20;
    s32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    s32 field44;
} RipplePatch;

/* clears the three grids of every ripple patch and sets the patch's header fields */
void func_L04_0039FA08(u8 *base, s32 count) {
    s32 i;
    s32 j;
    u8 *g1;
    u8 *g2;
    u8 *g3;
    u8 *g4;
    u8 *g5;
    u8 *g6;
    u8 *g7;
    u8 *g8;
    f32 small;

    for (i = 0; i < count; i++) {
        g8 = base + (i * 0x1190 + 0x5D0);
        g7 = base + (i * 0x1190 + 0x590);
        g6 = base + (i * 0x1190 + 0x510);
        g5 = base + (i * 0x1190 + 0x550);
        g4 = base + (i * 0x1190 + 0x4D0);
        g3 = base + (i * 0x1190 + 0x490);
        g2 = base + (i * 0x1190 + 0x450);
        g1 = base + (i * 0x1190 + 0x50);
        small = -0.0016f;
        for (j = 0; j < 3; j++) {
            func_00115484(g1, 0, 0x400);
            g1 += 0x5C0;
            func_00115484(g2, 0, 0x40);
            g2 += 0x5C0;
            func_00115484(g3, 0, 0x40);
            g3 += 0x5C0;
            func_00115484(g4, 0, 0x40);
            g4 += 0x5C0;
            func_00115484(g5, 0, 0x40);
            g5 += 0x5C0;
            func_00115484(g6, 0, 0x40);
            g6 += 0x5C0;
            func_00115484(g7, 0, 0x40);
            g7 += 0x5C0;
            func_00115484(g8, 0, 0x18);
            g8 += 0x5C0;
        }
        {
            RipplePatch *q = (RipplePatch *)(base + i * 0x1190);

            q->field30 = 1.5707964f;
            q->field34 = -1.5707964f;
            q->field38 = 0.02f;
            q->field3C = -0.031f;
            q->field40 = 0.03f;
            q->field20 = 0;
            q->field24 = 0;
            q->field28 = small;
            q->field2C = small;
            q->field44 = 0;
        }
    }
}


/* func_L04_0039FEA8 is matched in L04_0039FEA8.c (built with -g). */

/* func_L04_0039FEF0 is matched in L04_0039FEF0-g8.c (built with -G8). */


typedef struct {
    u8 pad00[0x20];
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
} D002A00E8Self;
extern f32 D_002A7A40[];
extern f32 D_002A7BC0[];
extern s32 D_002A7D90[];
extern f32 func_30F3A0(f32 x);
extern f32 func_30F3B8(f32 x);
extern f32 func_30FE40(f32 a, f32 b);

void func_L04_003A00E8(D002A00E8Self *p) {
    f32 a, b, c, d;
    s32 i;
    p->field20 = p->field20 + p->field28;
    if (p->field20 > 1.0f)
        p->field20 = p->field20 - 1.0f;
    if (p->field20 < 0.0f)
        p->field20 = p->field20 + 1.0f;
    p->field24 = p->field24 + p->field2C;
    if (p->field24 > 1.0f)
        p->field24 = p->field24 - 1.0f;
    if (p->field24 < 0.0f)
        p->field24 = p->field24 + 1.0f;
    p->field30 = func_30FE40(p->field30, p->field38);
    p->field34 = func_30FE40(p->field34, p->field3C);
    a = p->field20 + func_30F3A0(p->field30) * p->field40;
    b = p->field24 + func_30F3B8(p->field30) * p->field40;
    c = p->field20 + func_30F3A0(p->field34) * p->field40;
    d = p->field24 + func_30F3B8(p->field34) * p->field40;
    for (i = 0; i < 0x5C; i += 2) {
        if (D_002A7D90[i >> 1] == 0) {
            D_002A7A40[i] = D_002A7BC0[i] + a;
            D_002A7A40[i + 1] = D_002A7BC0[i + 1] + b;
        } else {
            D_002A7A40[i] = D_002A7BC0[i] + c;
            D_002A7A40[i + 1] = D_002A7BC0[i + 1] + d;
        }
    }
}

extern void func_002FD1B8(u32 a0, u32 a1, void *a2);
void func_L04_003A02A0(u32 a0, u32 a1) {
    func_002FD1B8(a0, a1, 0);
}


/* Cull a water grid tile against the near and far clip volumes, then submit it.
 * Adapted from RAC1 cull_and_submit_water_grid_tile (GPL-3.0), itself adapted
 * from Lombyte src/overlays/shared/gameplay/entities/002b8c08.c. */
void func_L04_003A0CE8(f32 *pos, s32 index, s32 mode) {
    f32 corners[4][4];
    f32 near_clip[4];
    f32 far_clip[4];
    f32 offsets[4][4];
    f32 x_offset, y_offset, x_end, y_end;
    f32 half_x, half_y;
    f32 x, y;
    u32 near_bits, far_bits;
    s32 i, value, row, column;

    if (mode != 0) {
        row = index >> 2;
        column = index & 3;
        half_x = 0.5f * -D_L04_001AD848;
        half_y = 0.5f * -D_L04_001AD84C;
        x_offset = half_x * (f32)column;
        y_offset = half_y * (f32)row;
        y_end = y_offset + half_y;
        x_end = x_offset + half_x;
        offsets[0][1] = y_offset;
        offsets[0][0] = x_offset;
        offsets[1][1] = y_offset;
        offsets[1][0] = x_end;
        offsets[2][0] = x_offset;
        offsets[2][1] = y_end;
        offsets[3][0] = x_end;
        offsets[3][1] = y_end;
        x = pos[0] + D_L04_001AD848;
        y = pos[1] + D_L04_001AD84C;
        corners[0][0] = x + offsets[2][0];
        corners[0][1] = y + offsets[0][1];
        corners[0][2] = pos[2];
        corners[0][3] = 1.0f;
        corners[1][0] = x + offsets[1][0];
        corners[1][1] = y + offsets[1][1];
        corners[1][2] = pos[2];
        corners[1][3] = 1.0f;
        corners[2][0] = corners[0][0];
        corners[2][1] = y + offsets[2][1];
        corners[2][2] = pos[2];
        corners[2][3] = 1.0f;
        corners[3][0] = corners[1][0];
        corners[3][1] = corners[2][1];
        corners[3][2] = pos[2];
        corners[3][3] = 1.0f;
        near_bits = 0;
        far_bits = 0;
        for (i = 0; i < 4; i++) {
            func_00282CF0(near_clip, corners[i], (float *)D_L04_001B9680);
            func_00282D30(far_clip, near_clip, 1024.0f);
            func_00282D30(near_clip, near_clip, 1024.0f);
            func_002830C0(far_clip, far_clip, D_L04_001B9680 - 0x80);
            func_002830C0(near_clip, near_clip, D_L04_001B9680 - 0x40);
            far_bits = (far_bits << 8) | func_00282BE0(far_clip);
            near_bits = (near_bits << 8) | func_00282BE0(near_clip);
        }
        if (mode == 1) {
            if ((near_bits & 0x01010101) == 0x01010101) return;
            if ((near_bits & 0x02020202) == 0x02020202) return;
            if ((near_bits & 0x04040404) == 0x04040404) return;
            if ((near_bits & 0x08080808) == 0x08080808) return;
            if (far_bits == 0) mode = 0;
            if ((near_bits & 0x20202020) == 0x20202020) return;
        } else {
            if ((near_bits & 0x01010101) == 0x01010101) return;
            if ((near_bits & 0x02020202) == 0x02020202) return;
            if ((near_bits & 0x04040404) == 0x04040404) return;
            if ((near_bits & 0x08080808) == 0x08080808) return;
            if ((near_bits & 0x20202020) == 0x20202020) return;
            mode = 0;
        }
    }
    value = (index & 3) * 4 + (index >> 2) * 0x44;
    if (mode != 0) {
        mode = 0xe;
    } else {
        mode = 0xc;
    }
    func_L04_0032F994(mode, value);
}

/* Build the eight cardinal and diagonal neighbor indices for each water tile. */
extern float func_00282C48(float);

/* Record the neighboring cells of the 16-unit grid. */
void func_L04_003A1240(unsigned char *cells, int count)
{
    int i, j;
    for (i = 0; i < count; i++) {
        unsigned char *cell = cells + i * 0x1190;
        cell[0xC] = 255;
        cell[0xE] = 255;
        cell[0xD] = 255;
        cell[0xF] = 255;
        cell[0x10] = 255;
        cell[0x11] = 255;
        cell[0x12] = 255;
        cell[0x13] = 255;
        for (j = 0; j < count; j++) {
            if (i != j) {
                unsigned char *cell = cells + i * 0x1190;
                float dx = *(float *)cell - *(float *)(cells + j * 0x1190);
                float dy = *(float *)(cell + 4) - *(float *)(cells + j * 0x1190 + 4);
                if (func_00282C48(dx) < 0.1f) {
                    if (func_00282C48(dy - 16.0f) < 0.1f) cell[0xC] = j;
                    if (func_00282C48(dy + 16.0f) < 0.1f) cell[0xE] = j;
                } else if (func_00282C48(dy) < 0.1f) {
                    if (func_00282C48(dx - 16.0f) < 0.1f) cell[0xD] = j;
                    if (func_00282C48(dx + 16.0f) < 0.1f) cell[0xF] = j;
                } else if (func_00282C48(dx + 16.0f) < 0.1f) {
                    if (func_00282C48(dy - 16.0f) < 0.1f) cell[0x11] = j;
                    if (func_00282C48(dy + 16.0f) < 0.1f) cell[0x13] = j;
                } else if (func_00282C48(dx - 16.0f) < 0.1f) {
                    if (func_00282C48(dy - 16.0f) < 0.1f) cell[0x10] = j;
                    if (func_00282C48(dy + 16.0f) < 0.1f) cell[0x12] = j;
                }
            }
        }
    }
}


/* Sets the 6-bit tag (bits 24-29) of every word in the state block's sub-array. */
void func_L04_003A14B8(u8 *object, u32 value) {
    u8 *state = *(u8 **)(object + 0x98);
    u32 tag;
    u8 *base;
    u32 *p;
    s32 count;
    s32 offset;
    s32 i;

    count = *(s32 *)(state + 0x8) / 4;
    tag = value & 0x3F;
    tag <<= 24;
    offset = *(s32 *)(state + 0xC) / 8;
    base = state + *(s32 *)(state + 0x4) + 0x10;
    p = (u32 *)(base + offset * 8);

    for (i = 0; i < count; i++) {
        p[i] = (p[i] & 0xC0FFFFFF) | tag;
    }
}


/* returns the packed header's signed rounded sixteen-byte block count in word units */
s32 func_L04_003A1540(const PackedHeaderCountView *header) {
    s32 fixed = header->extra + 16;
    s32 total = header->data_offset + fixed + header->length;
    return ((total + 15) / 16) * 4;
}

/* func_L04_003A15C0 is in L04_002CC748-water-header.c. */

/* func_L04_003A1868 is in L04_002CC748-lighting-g8.c. */

void func_L04_003A1A48(u8 *dst, u16 *src, s32 count) {
    if (count <= 0)
        return;
    dst += 0x1E;
    do {
        *(u16 *)dst = *src;
        src++;
        dst += 0x1190;
        count--;
    } while (count != 0);
}

/* Toggle the water controller, animate its height, and disturb its ripple tiles. */
void func_L04_003A1C98(char *self) {
    char *state = WPTR(WPTR(self, 0x28), 0x68);
    float x, y, half, r;

    if (WBYTE(WPTR(self, 0x28), 0xBC) >= WBYTE(state, 0x15)) {
        func_0026FEB8(D_L04_001ADA00, WSHORT(WPTR(self, 0x28), 0xB2),
                      WSHORT(WPTR(self, 0x28), 0xAA), WBYTE(WPTR(self, 0x28), 0xBC),
                      WBYTE(state, 0x15));
        WBYTE(WPTR(self, 0x28), 0x20) = 2;
        WBYTE(WPTR(self, 0x28), 0xBC) = 0;
        WSHORT(state, 0x16) = 60;
        WBYTE(state, 0x14) ^= 1;
        func_L04_003A1578(WPTR(self, 0x28), WINT(self, 0x1C), WINT(self, 0x18));
        if (WINT(state, 0x10) >= 0 && !WBYTE(state, 0x14)) {
            int i;
            for (i = WINT(state, 0x10); i < WINT(self, 4); i++) {
                r = func_002A7878(-4.0f, 4.0f);
                x = WFLOAT(WPTR(self, 8) + i * 0x1190, 0);
                x += r;
                y = WFLOAT(WPTR(self, 8) + i * 0x1190, 4) + func_002A7878(-4.0f, 4.0f);
                func_002FD1B8_ripple(WPTR(self, 8) + i * 0x1190, 1, 1,
                                     x, y, 1.0f, -0.05f);
            }
        }
    }
    if (WBYTE(state, 0x14)) return;
    if (WINT(state, 0x20) != -1) {
        char *p = D_L04_001FE340[WINT(state, 0x20)];
        if (func_002A8AF0((char *)&D_00189E20 + 0x80, p + 0x10, WINT(p, 0)))
            WFLOAT(&D_00189E20, 0x330) = WFLOAT(WPTR(self, 0x28), 0x18);
    }
    half = (WFLOAT(state, 0) - WFLOAT(state, 4)) * 0.5f;
    WFLOAT(WPTR(self, 0x28), 0x18) =
        WFLOAT(state, 4) + (func_00283180(WFLOAT(state, 8)) * half + half);
    if (RIPPLE_HERO.field229C != 20 && RIPPLE_HERO.field229C != 25 &&
        RIPPLE_HERO.field2294 != 0x39 && RIPPLE_HERO.field2294 != 0x78 &&
        RIPPLE_HERO.field2294 != 0x79)
        WFLOAT(state, 8) = func_00283B98(WFLOAT(state, 8), WFLOAT(state, 0xC));
    if (WINT(state, 0x10) >= 0 && !func_002A77E0(200)) {
        int i;
        for (i = WINT(state, 0x10); i < WINT(self, 4); i++) {
            r = func_002A7878(-4.0f, 4.0f);
            x = WFLOAT(WPTR(self, 8) + i * 0x1190, 0);
            x += r;
            y = WFLOAT(WPTR(self, 8) + i * 0x1190, 4) + func_002A7878(-4.0f, 4.0f);
            func_002FD1B8_ripple(WPTR(self, 8) + i * 0x1190, 1, 1,
                                 x, y, 1.0f, -0.05f);
        }
    }
}


extern u32 func_00282978(u8 *ptr);
void func_L04_003A1FA0(u8 *self) {
    if (func_00282978((u8 *)(*(u32 *)(*(u32 *)(self + 0x28) + 0x68) + 0x16)) != 0)
        *(u8 *)(*(u32 *)(self + 0x28) + 0x20) = 1;
}

/* func_L04_003A1FE0 is matched in L04_002CC748-g8.c (built with -G8). */

INCLUDE_ASM("asm/levels", func_L04_003A21F8);

typedef struct {
    u32 value;
    float factor;
    u32 pad[2];
} TblEntry;
typedef struct {
    TblEntry entries[64];
    u32 count;
} Tbl;
extern Tbl D_L04_00231E00;
void func_L04_003A5C08(u32 value, float factor) {
    D_L04_00231E00.entries[D_L04_00231E00.count].value = value;
    D_L04_00231E00.entries[D_L04_00231E00.count].factor = factor;
    D_L04_00231E00.count++;
}

extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038E880(void *, void *, void *);
extern void func_L00_0038F3D8(void *);
typedef unsigned int B352Quad __attribute__((mode(TI)));
typedef union { B352Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern char *D_0018C0B0 NOT_SDA;
extern int D_L04_001AC790 __attribute__((sda));
extern Collision D_L04_001BFAC0;
extern Material D_L04_0027B470[];
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00283028(void *, void *, void *);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);

void func_L04_003B3580(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, position, ctx);
    func_002AFFD8(position, &frame.surface, 0);
    func_00282D30(&frame.surface, &frame.surface, 0.0003055556f);
    func_L00_0038F3D8(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L04_0027B470)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L04_001BFAC0;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L04_001BFAC0;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L04_001AC790 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            func_00283028(&frame.velocity, ctx, &reread->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L04_001BFAC0;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            func_00283028(&frame.velocity, ctx, &collision->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
        else
            func_L00_0038E880(obj, &frame.velocity, &frame.normal);
    }
}


/* func_L04_003C3BA0 is matched in L04-particle-emitter-g8.c. */

INCLUDE_ASM("asm/levels", func_L04_003C4050);

/* Initialises particle i of this emitter: a random unit-cube direction, a random
   speed, size and lifetime from the emitter's three ranges, a zero age, the current
   colour, cleared flags and a start delay staggered by the particle's index. */
typedef struct {
    short first;
    u8 pad2[6];
    float life_min;
    float life_max;
    float speed_min;
    float speed_max;
    float size_min;
    float size_max;
} ParticleRanges3C4858;
/* A sixteen-byte record per spawn slot: three floats the level fills in. */
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} L04SpawnRecord;

extern L04SpawnRecord D_L04_0023BDD0[];
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
#ifndef MACRO_ADDR
#define MACRO_ADDR __attribute__((section(".sdata")))
#endif
extern s32 D_L04_001B2E70 MACRO_ADDR;
extern u16 D_L04_001B2E74 MACRO_ADDR;
extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7878(f32 a0, f32 a1);

void func_L04_003C4858(void *emitter, s32 i)
{
    ParticleRanges3C4858 *ranges = *(ParticleRanges3C4858 **)((u8 *)emitter + 0x68);
    L04SpawnRecord *rec;
    f32 v;

    v = func_002A78D8(0.0f, 1.0f);
    rec = &D_L04_0023BDD0[i];
    rec->x = v;
    rec->y = func_002A78D8(0.0f, 1.0f);
    rec->z = func_002A78D8(0.0f, 1.0f);
    D_L04_0023CA50[i] = func_002A7878(ranges->speed_min, ranges->speed_max);
    D_L04_0023CD70[i] = func_002A7878(ranges->size_min, ranges->size_max);
    D_L04_0023D220[i] = 0.0f;
    D_L04_0023D540[i] = func_002A7878(ranges->life_min, ranges->life_max);
    D_L04_0023D860[i] = D_L04_001B2E74;
    D_L04_0023D9F0[i] = 0;
    D_L04_0023DB80[i] = (i - ranges->first + 1) * D_L04_001B2E70;
    D_L04_0023D158[i] = 0;
}

/* A sixteen-byte record per spawn slot (L04SpawnRecord, above). */

extern L04SpawnRecord D_L04_0023BDD0[];
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
extern s32 D_L04_001B2E70;
extern u16 D_L04_001B2E74;

extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7878(f32 a0, f32 a1);


void func_L04_003C49C0(void *a0, u32 a1) {
    f32 *obj = *(f32 **)((u8 *)a0 + 0x68);
    L04SpawnRecord *rec;
    f32 v;

    v = func_002A78D8(0.0f, 1.0f);
    rec = &D_L04_0023BDD0[a1];
    rec->x = v;
    rec->y = func_002A78D8(0.0f, 1.0f);
    rec->z = func_002A78D8(0.0f, 1.0f);
    {
        f32 v44 = obj[0x11];
        f32 v4c = obj[0x13];

        D_L04_0023CA50[a1] = func_002A7878(v44, v44 + 2.0f);
        D_L04_0023CD70[a1] = func_002A7878(v4c, v4c + 4.0f);
    }
    D_L04_0023D220[a1] = 0.0f;
    D_L04_0023D540[a1] = func_002A7878(0.003f, 0.005f);
    D_L04_0023D158[a1] = 1;
}


extern u32 D_L04_001B2E84 __attribute__((sda));

/* adds VALUE to the running total and returns the total as it was before */
u32 func_L04_003C70C8(u32 value) {
    u32 old = D_L04_001B2E84;
    D_L04_001B2E84 = old + value;
    return old;
}
