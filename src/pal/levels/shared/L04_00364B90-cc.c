/* func_PAL_L04_00364B90, the PAL copy of func_L04_00362768: the same C, where scale a2. */
#include "common.h"
extern void func_00282DD8(void *, void *, void *);

extern void func_00282D30(void *, void *, float);
extern float D_L04_001AD848 MACRO_ADDR, D_L04_001AD84C MACRO_ADDR;
extern void func_002830C0(void *, void *, void *);
extern unsigned char D_001A7A33 MACRO_ADDR;
extern unsigned char D_001A7A32 MACRO_ADDR;
extern void func_00282CF0(f32 *,f32 *,f32 *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern u32 func_00282978(u8 *);
extern void func_002B9180(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);

extern void func_00282F20(float *, float *, float);
extern float func_00282DB0(void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
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
#undef HOP_PLAYER
#undef HOP_SAVED

#define NOT_SDA __attribute__((section(".data")))

extern int r1_D_0012FCF0 NOT_SDA;

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
/* the block at +0x30: a sixteen-byte vector and the float inside its last word */
extern void *func_002B9030(s32 kind);
extern s32 func_00283CF0(f32 value);
extern s32 func_002A77E0(s32 limit);
extern void func_00282F20(f32 *dst, f32 *a, f32 len);
extern void func_00282CF0(f32 *dst, f32 *a, f32 *b);

/* the level's pointer to the byte the record carries in its second flag byte */
extern u32 ref_L04_00362768_00;
/* func_L04_0030C4C0 is matched in L04_0030C4C0.c (built with -frac2-qcopy and -g). */

/* Draws a camera-facing ribbon along a polyline, one quad per segment; each point's fourth
   float is its half width.  The first segment uses first_texture, the last one last_texture
   and the others middle_texture. */
typedef struct {
    u8 pad00[0x44];
    s16 count;
    u8 pad46[0x18C - 0x46];
    u32 mobs[1];          /* the array the count field bounds */
} MobListStruct;

/* the list of mobs: level 04 has it at 0x001BD380, every level at its own address */
extern MobListStruct ref_L04_0031D630_00;

/* shared callee, named by its catalogue row (04:0031D3C8) */
/* Walks the list of mobs: the ones of type 0xE29 get the 0x800 flag, the ones of type
   0xD54 are handed to func_002E64A0, and the ones of type 0xFA0 with a 0x68 pointer
   get that pointer's block (from +0xC) to func_L00_00326048. */
/* sched1 hoists the last statement of */
/* func_L04_0033CC00 is defined in L04_002CC748-movement.c. */

/* func_L04_0033D0C0 is defined in L04_0033D0C0.c. */

/* func_L04_00344568 is in L04_002CC748-axis.c. */

extern f32 func_00282DB0(void *a, void *b);
extern void func_00282DD8(void *dst, void *a, void *b);
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
L04Effect1A *func_L04_00358868(void *target, s32 color, u32 duration, u32 joint, f32 value);

extern s32 func_00283CF0(f32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002A77E0(s32);
/* func_L04_0035F3E0 is defined in L04_0035F3E0-qcopy.c. */

void *func_PAL_L04_00364B90(void *a0, void *a1, u32 a2, f32 f3) {
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
        p->field0A = (u16)(((int)(a2) * 5 + 2) / 6);
        t = *(L04Quad *)a1;
        p->field20 = t;
        q->field0C = 0;
        q->field10 = 0.5f;
        q->field14 = f3;
        q->field18 = (u16)(func_002A77E0(2) - 1);
    }
    return (u32)p;
}

extern void func_002B9180(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00283CE0(int);
/* Same body as func_002C7620, with this function's own callees. */
/* func_L04_00363690 is defined in L04_00363690-qcopy.c. */

/* func_L04_00363CA0 is matched in L04_00363CA0.c (built with -frac2-qcopy). */

/* func_L04_00365300 is defined in L04_00365300.c. */

/* func_L04_00378838 is defined in L04_00378838-g8.c (it reads its list through $gp). */

/* func_L04_003A0FC8 is in L04_003A0FC8-g8.c. */

/* the header of one 0x1190-byte ripple patch */
/* clears the three grids of every ripple patch and sets the patch's header fields */
/* func_L04_0039FEA8 is matched in L04_0039FEA8.c (built with -g). */

/* func_L04_0039FEF0 is matched in L04_0039FEF0-g8.c (built with -G8). */

/* Cull a water grid tile against the near and far clip volumes, then submit it.
 * Adapted from RAC1 cull_and_submit_water_grid_tile (GPL-3.0), itself adapted
 * from Lombyte src/overlays/shared/gameplay/entities/002b8c08.c. */
/* Build the eight cardinal and diagonal neighbor indices for each water tile. */
/* Record the neighboring cells of the 16-unit grid. */
/* Sets the 6-bit tag (bits 24-29) of every word in the state block's sub-array. */
/* returns the packed header's signed rounded sixteen-byte block count in word units */
/* func_L04_003A15C0 is in L04_002CC748-water-header.c. */

/* func_L04_003A1868 is in L04_002CC748-lighting-g8.c. */

/* Toggle the water controller, animate its height, and disturb its ripple tiles. */
extern u32 func_00282978(u8 *ptr);
/* func_L04_003A1FE0 is matched in L04_002CC748-g8.c (built with -G8). */

/* func_L04_003A21F8 is matched in L04_002CC748-water-g8.c (built with -G8). */

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
extern void func_00282D30(void *, void *, float);
typedef unsigned int B352Quad __attribute__((mode(TI)));
typedef union { B352Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern char *D_0018C0B0 NOT_SDA;
extern Collision D_L04_001BFAC0;
extern Material D_L04_0027B470[];
extern int func_002761F8(void *, void *, int, void *, void *);
/* func_L04_003C3BA0 is matched in L04-particle-emitter-g8.c. */

/* Initialises particle i of this emitter: a random unit-cube direction, a random
   speed, size and lifetime from the emitter's three ranges, a zero age, the current
   colour, cleared flags and a start delay staggered by the particle's index. */
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

/* adds VALUE to the running total and returns the total as it was before */
