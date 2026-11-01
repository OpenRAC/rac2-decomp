#include "common.h"

extern void func_00282D30(void *, void *, float);
extern float D_L04_001AD848 MACRO_ADDR, D_L04_001AD84C MACRO_ADDR;
extern char D_L04_001B9680[];
extern void func_002830C0(void *, void *, void *);

extern void func_00282CF0(f32 *,f32 *,f32 *);
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
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
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
extern unsigned char D_L00_001B8C80[];
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
#define HOP_SAVED (*(HopSavedState *)D_L00_001B8C80)
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

/* Check the hero's surface contact and optionally apply its movement impulse. */

/* func_L04_002DB970 is defined in L04_002CC748-collision-g8.c. */

/* func_L04_002DBE70 is defined in L04_002CC748-movement.c. */

/* Per-state airborne steering; shares the hop-velocity state cases with
   rac1-decomp's hero_update_hop_velocity. */
void func_L00_002B6BC8(void) {
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
    } else if (HOP_PLAYER.state == 72) {
        if (HOP_PLAYER.anim_frame >= 5.0f && HOP_PLAYER.anim_frame <= 18.0f) {
            if (HOP_PLAYER.anim_frame > 15.0f) {
                func_002AA2E8(&HOP_PLAYER.ledge_jump_speed, 0.0f, 0.002222222276031971f);
            } else {
                func_002AA2E8(&HOP_PLAYER.ledge_jump_speed, 0.02083333395421505f, 0.002222222276031971f);
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


/* rac1-decomp src/core/00118A40.c: func_00118EC0 */

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

extern s32 func_00283CF0(f32 value);
extern s32 func_002A77E0(s32 limit);
extern void func_00282F20(f32 *dst, f32 *a, f32 len);
extern void func_00282CF0(f32 *dst, f32 *a, f32 *b);

/* the level's pointer to the byte the record carries in its second flag byte */
extern u32 ref_L04_00362768_00;
extern u32 ref_L04_00362940_00;

/* func_L04_0030C4C0 is matched in L04_0030C4C0.c (built with -frac2-qcopy and -g). */

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
extern void func_002E64A0(void *mob);
extern void func_L00_00326048(void *mob, void *p, s32 a2, s32 a3, f32 alpha);

/* Walks the list of mobs: the ones of type 0xE29 get the 0x800 flag, the ones of type
   0xD54 are handed to func_002E64A0, and the ones of type 0xFA0 with a 0x68 pointer
   get that pointer's block (from +0xC) to func_L00_00326048. */

/* sched1 hoists the last statement of */

/* func_L04_0033D0C0 is defined in L04_0033D0C0.c. */



/* func_L04_00344568 is in L04_002CC748-axis.c. */

extern f32 func_00282DB0(void *a, void *b);
extern void func_002830C0(void *a, void *b, void *c);

/* Copies the caller's matrix into a local one, takes the two aim angles off
   the target vector, springs one of them, and turns the copy by the three
   angles before handing its axes to the caller. */

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

/* the level's pointer to the byte the record carries in its second flag byte */

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

extern s32 func_00283CF0(f32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002A77E0(s32);
/* func_L04_0035F3E0 is defined in L04_0035F3E0-qcopy.c. */

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 word; float values[4]; } Vec4;
extern void func_002B9180(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00283CE0(int);

/* Same body as func_002C7620, with this function's own callees. */

/* func_L04_00363690 is defined in L04_00363690-qcopy.c. */

/* func_L04_00363CA0 is matched in L04_00363CA0.c (built with -frac2-qcopy). */

/* func_L04_00365300 is defined in L04_00365300.c. */

/* func_L04_003A0FC8 is in L04_003A0FC8-g8.c. */


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

extern void func_002FD1B8(u32 a0, u32 a1, void *a2);

/* Cull a water grid tile against the near and far clip volumes, then submit it.
 * Adapted from RAC1 cull_and_submit_water_grid_tile (GPL-3.0), itself adapted
 * from Lombyte src/overlays/shared/gameplay/entities/002b8c08.c. */

/* Build the eight cardinal and diagonal neighbor indices for each water tile. */

/* Record the neighboring cells of the 16-unit grid. */

/* returns the packed header's signed rounded sixteen-byte block count in word units */

/* func_L04_003A15C0 is in L04_002CC748-water-header.c. */

/* func_L04_003A1868 is in L04_002CC748-lighting-g8.c. */

/* Toggle the water controller, animate its height, and disturb its ripple tiles. */

extern u32 func_00282978(u8 *ptr);

/* func_L04_003A1FE0 is matched in L04_002CC748-g8.c (built with -G8). */

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

extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
typedef unsigned int B352Quad __attribute__((mode(TI)));
typedef union { B352Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern int D_L04_001AC790 __attribute__((sda));
extern Collision D_L04_001BFAC0;
extern int func_002761F8(void *, void *, int, void *, void *);

/* func_L04_003C3BA0 is matched in L04-particle-emitter-g8.c. */

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

extern u32 D_L04_001B2E84 __attribute__((sda));

/* adds VALUE to the running total and returns the total as it was before */
