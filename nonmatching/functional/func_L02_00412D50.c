/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * Claude Opus 5.5 (xhigh) tier, task v1936, 31 October 2026.
 * Profile: -O2 -G16 -Wa,-G16 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier
 * (the existing L02_003DAF90-g16.c profile; -g and -frac2-gcse-unsplit-edges
 * were measured to change nothing and are dropped). Unit used for the test:
 * src/levels/02_maktar_nebula/L02_00412D50-g16.c plus that cflags line.
 * Final check.py: 2528/2528 bytes, 0/1 US places, first difference +0x6b0.
 * Exactly two instructions differ: at 0x413400/0x413404 retail loads
 * point.f[0] into $f0 and then point.f[1] into $f13; this draft emits the
 * same two loads (same registers) in the opposite order. Everything else,
 * including the 0xE0 frame and every register, matches (relocation addends
 * aside). Not linked; US2/PAL not checked.
 *
 * What fixed the earlier differences (keep these):
 * - The flag byte is D_001A7B00[0x1E] on `extern u8 D_001A7B00[] sda`.
 *   simple_memory_operand treats (const (plus sym N)) as two instructions
 *   (its CONST case is under #if 0), so reorg never puts the load in a
 *   delay slot; D_001A7B1E[0] (a bare symbol, length 1) went into the beq
 *   slot and took the $gp form there. This alone fixed case 0/case 1 CFG,
 *   argument hoisting and hero lui placement (250 -> 11 differing rows).
 * - D_0019B2E8 plain (not MACRO_ADDR) so its address splits and the
 *   state->flag load schedules between lui and addiu.
 * - Spill slots 0x70/0x74 (&state->position, aim.f + 2): gcse numbers the
 *   PRE reaching registers in bucket order, hash(plus(reg85,144)) = 14258
 *   and hash(plus(at,72)) = 14102, mod (n_insns/2)|1. At n_insns 580
 *   (291 buckets) aim.f + 2 gets the lower pseudo; 289, 295, 297, 301 or 303
 *   buckets swap them. The eight declaration initializers below (side,
 *   distance, target, i, index, both records, current) give 295 buckets.
 *   NOTE REVIEW: they exist only for this count.
 * - Yaw registers: point.f[1] read into a local before point.f[0] makes
 *   sched1 emit hero1, point1, point0, hero0, which gives local-alloc
 *   retail's $f1/$f13/$f0/$f12. sched2 then keeps point1 before point0
 *   (equal priority 18, six dependents each, LUID tie).
 *
 * Remaining: retail's final order (hero1, point0, point1, hero0 with those
 * registers) needs sched1 to emit hero1, point0, hero0, point1, which the
 * measured rules forbid (hero1 goes first because the hero base dies there,
 * register weight 0; point loads have 6 dependents and hero0 has 3). Or it
 * needs an extra non-memory insn between hero1 and point0 in sched1's
 * output that later vanishes. Direct expression, dx/dy or dy/dx locals,
 * a nested call and a hero pointer local were tried: no gain.
 * Opus G2, 1 November 2026: both sub.s operands get the argument register as a suggestion and the
 * shorter life wins, so $f13 on point1 and $f12 on hero0 fit a sched1 order of hero1, point0, then
 * those two. A two-death variable for hero1 (target, current) gives $f13 to it instead, and x/y, h/x/y
 * and dy locals tie. The eight initial values are dead and must go: read named constants or argument
 * copies in a later block instead (func_L08_0042A0B0), to reach 588 to 591 insns (295 buckets).
 * Declarations below are complete.
 */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } LiftVector;
typedef struct {
    u8 pad0[0x80];
    float position[4];
    u8 pad90[0x33C - 0x90];
    u8 *lift;
    s32 active;
    u8 pad344[0x22B6 - 0x344];
    u8 boarding;
} LiftHero;
extern LiftHero D_00189E20;
typedef struct {
    u8 pad0[0x60];
    s32 launch_nodes[2];
    s32 cameras[2];
    u8 pad70[8];
    s32 flag;
    s32 stops[2];
    s32 sound;
    u8 pad88[8];
    LiftVector position;
    LiftVector rotation;
    u8 padB0[12];
    s32 side;
    u8 padC0[12];
    float speed;
} LiftState;
extern u8 D_0019B2E8[];
typedef struct { u8 bytes[0x70]; } LiftSoundStride;
extern LiftSoundStride D_00188660[];
extern u8 D_001A7B00[] __attribute__((sda));
extern s32 D_001A79F0[] MACRO_ADDR;
typedef struct {
    LiftVector axes[3];
    LiftVector position;
    u8 pad40[0x30];
    LiftVector rotation;
} LiftNode;
extern LiftNode *D_L02_001B368C MACRO_ADDR;
extern s32 D_L02_001B30C8[] MACRO_ADDR;
extern float D_L02_001B2FE0[] MACRO_ADDR;
extern float D_L02_001B1C50 __attribute__((sda));
extern float D_L02_001B1C54 __attribute__((sda));
extern LiftVector D_L02_001B1C60 __attribute__((sda));
extern float D_L02_001B1C6C[] MACRO_ADDR;
extern char D_L02_001B1C70[];
extern u8 D_L02_001BA500[];
extern void func_00282A28(void);
extern void func_002A7750(u8 *, s32, s32);
extern void func_002A7470(void *, s32, s32, s32);
extern void func_00282D60(void *, void *, float);
extern s32 func_00283DB8(void *, float);
extern void func_0029F338(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_002AFDD8(char *, char *, char *, char *);
extern double func_001234F0(float);
extern void func_0026FEB8(const char *, ...);
extern void func_L00_002C42E0(s32, s32);
extern float func_00282E80(void *, void *);
extern void func_003355A8(s32);
extern s32 func_002B3868(u8 *);
extern void func_00335438(void *, void *, s32, s32, s32);
extern void func_L00_002D40A0(void *, s32, float);
extern s32 func_002E5CF8(s32, s32, char *);
extern float func_002AA2E8(float *, float, float);
extern void func_00282F20(void *, void *, float);
extern s32 func_002A8C28(void *, void *, u32, float, float, float, s32, s32, s32);
extern float func_00283248(float, float);
extern void func_002AA800(float *, s32, float, float);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_002E59F8(s32);
extern void func_002A7398(s8 *, s32, s32);
extern void func_002833F0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_L00_002B9D60(void *, void *, s32, s32);
extern void func_L00_0042A500(s32);
extern void func_L02_00413730(u8 *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Move between the two lift poses, coordinating the camera and boarding state. */
void func_L02_00412D50(u8 *object)
{
    LiftVector old_position;
    LiftVector old_rotation;
    LiftVector delta;
    LiftVector point;
    LiftVector aim;
    LiftVector launch;
    LiftVector rotation;
    LiftState *state = *(LiftState **)(object + 0x68);
    s32 side = 0;
    float distance = 0.0f;
    float target = 0.0f;
    s32 i = 0;

    qcopy_nc(&old_position, (object + 0x10));
    qcopy_nc(&old_rotation, (object + 0xF0));
    switch (object[0x20]) {
    case 0: {
        s32 index = 0;
        object[0x30] = 0xFF;
        state->sound = -1;
        if (state->stops[0] == -1 || state->stops[1] == -1) {
            func_0029F338(object);
            return;
        }
        if (state->launch_nodes[0] == -1 || state->launch_nodes[1] == -1)
            func_00282A28();
        if (state->cameras[0] == -1 || state->cameras[1] == -1)
            func_00282A28();
        if (state->flag != -1) {
            if (D_001A7B00[0x1E]) {
                func_0029F338(object);
                return;
            }
            *(s32 *)(object + 0x98) = 0;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
            func_002A7750(object, 4, -1);
        } else
            func_002A7750(object, 1, -1);
        if (object[0x43] != 2)
            func_002A7470(object, 2, 0, 1);
        index = state->stops[0];
        qcopy_nc(&state->position, &D_L02_001B368C[index].position);
        qcopy_nc(&state->rotation, &D_L02_001B368C[index].rotation);
        break;
    }
    case 4:
        if (D_0019B2E8[state->flag + (D_001A79F0[0] << 4)] & 0x80) {
            func_00282D60(&delta, object, 0.0009765625f);
            if (func_00283DB8(&delta, 64.0f) == -1) {
                *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xFFBE) | 0x1000;
                *(u32 *)(object + 0x98) = *(u32 *)(*(u8 **)(object + 0x24) + 0x10);
                func_002A7750(object, 1, -1);
            }
        }
        break;
    case 1: {
        LiftNode *record = 0;
        if (state->flag != -1 && D_001A7B00[0x1E]) {
            func_0029F338(object);
            return;
        }
        if (D_00189E20.lift == object && D_00189E20.active) {
            func_00282CF0(&delta, D_00189E20.position, object + 0x10);
            point.quad = 0;
            point.f[0] = -1.2f;
            point.f[2] = -0.69f;
            func_00283098(&point, &point, object + 0xC0);
            func_00282CC0(&point, &point, object + 0x10);
            func_00282CF0(&aim, &point, D_00189E20.position);
            distance = func_00282E20(&aim);
            func_002AFDD8((char *)object, (char *)&delta, (char *)&delta, 0);
            if (delta.f[2] < -0.6f) {
                func_0026FEB8(D_L02_001B1C70, func_001234F0(distance));
                func_L00_002C42E0(0x6F, 1);
                func_002A7750(object, 2, -1);
            }
        } else if ((D_L02_001B30C8[0] & 0x3F) == 0) {
            float current = 0.0f;
            side = (state->side + 1) & 1;
            record = &D_L02_001B368C[state->stops[side]];
            distance = func_00282E80(D_00189E20.position, &record->position);
            record = &D_L02_001B368C[state->stops[state->side]];
            current = func_00282E80(D_00189E20.position, &record->position);
            if (distance < current) {
                s32 index;
                state->side = side;
                index = state->stops[side];
                qcopy_nc(&state->position, &D_L02_001B368C[index].position);
                qcopy_nc(&state->rotation, &D_L02_001B368C[index].rotation);
                qcopy_nc((object + 0x10), (&state->position));
                qcopy_nc((object + 0xF0), (&state->rotation));
            }
        }
        break;
    }
    case 2: {
        LiftNode *record = 0;
        if (D_00189E20.active == 0) {
            func_003355A8(0);
            break;
        }
        if (func_002B3868(object)) {
            func_00335438(D_L02_001BA500, D_L02_001BA500 + 0x10, 1, 0, 0);
            delta.quad = 0;
            delta.f[0] = -1.2f;
            delta.f[2] = -0.69f;
            func_00283098(&delta, &delta, object + 0xC0);
            func_00282CC0(&delta, &delta, object + 0x10);
            func_L00_002D40A0(&delta, 0, *(float *)(object + 0xF8));
            D_00189E20.boarding = 1;
            func_002E5CF8(1, 0, (char *)object);
            if (object[0x43])
                func_002A7470(object, 0, 0, 45);
        }
        func_002AA2E8(&state->speed, D_L02_001B1C50 * 0.016666668f, D_L02_001B1C54 * 0.00027777778f);
        func_00282F20(&delta, object + 0xC0, state->speed);
        delta.f[2] = 0.0f;
        func_00282CC0(&state->position, &state->position, &delta);
        i = 0;
        do {
            qcopy_nc(&point, &D_L02_001B1C60);
            if (i)
                point.f[1] = -point.f[1];
            func_00283098(&point, &point, object + 0xC0);
            func_00282CC0(&point, &point, object + 0x10);
            func_002A8C28(object, &point, 0x10000, D_L02_001B1C6C[0], 1.0f, 1.0f, 0, 1, 0);
        } while (++i < 2);
        qcopy_nc(&point, D_L02_001BA500);
        point.f[2] += 0.016666668f;
        qcopy_nc(&aim, (D_L02_001BA500 + 0x10));
        distance = func_00282E80(&point, D_00189E20.position);
        target = func_00283248(distance, D_00189E20.position[2] - point.f[2]);
        func_002AA800(aim.f + 1, 0, -target, 0.013089971616864204f);
        {
            float y = point.f[1];
            float x = point.f[0];
            target = func_00283248(D_00189E20.position[0] - x, D_00189E20.position[1] - y);
        }
        func_002AA800(aim.f + 2, 0, target, 0.02617994323372841f);
        func_00335370(&point);
        func_003353C8(&aim);
        {
            u16 previous = *(u16 *)(object + 0x96);
            s32 ticks = previous + 1;
            *(u16 *)(object + 0x96) = ticks;
            if (previous >= 121)
                func_002AA2E8(&D_L02_001B2FE0[0], 1.0f, 0.033333335f);
            else {
                s32 slot;
                u8 *sound_record;
                if ((u16)ticks == 45)
                    func_L00_002C42E0(0x6F, 1);
                slot = state->sound;
                sound_record = (u8 *)&D_00188660[slot];
                if (*(u8 **)(sound_record + 0x88) != object || !sound_record[0x74])
                    state->sound = func_002E5CF8(0, 4, (char *)object);
            }
        }
        if (D_L02_001B2FE0[0] >= 1.0f) {
            s32 slot;
            func_L00_002C42E0(0, 1);
            slot = state->sound;
            if (slot != -1) {
                u8 *sound_record = (u8 *)&D_00188660[slot];
                if (*(u8 **)(sound_record + 0x88) == object && sound_record[0x74])
                    func_002E59F8(slot);
            }
            state->sound = -1;
            func_002A7398((s8 *)object, 2, 0);
            func_002A7750(object, 3, -1);
            state->side = (state->side + 1) & 1;
            {
                s32 index = state->stops[state->side];
                qcopy_nc(&state->position, &D_L02_001B368C[index].position);
                qcopy_nc(&state->rotation, &D_L02_001B368C[index].rotation);
            }
            func_002833F0(object + 0xC0, &state->rotation);
            record = &D_L02_001B368C[state->launch_nodes[state->side]];
            func_00282D30(&launch, record, -0.9f);
            func_00282CC0(&launch, &launch, &record->position);
            qcopy_nc(&rotation, (&record->rotation));
            func_L00_002B9D60(&launch, &rotation, 0, 1);
            func_L00_002D40A0(&record->position, 1, record->rotation.f[2]);
            func_003355A8(0);
            func_L00_0042A500(state->cameras[state->side]);
            func_L02_00413730(object);
        }
        break;
    }
    case 3:
        func_002AA2E8(&D_L02_001B2FE0[0], 0.0f, 0.033333335f);
        if (D_L02_001B2FE0[0] <= 0.0f) {
            state->speed = 0.0f;
            func_002A7750(object, 1, -1);
        }
        break;
    }
    if (object[0x31])
        func_L02_00413730(object);
    func_00282CF0(&delta, object + 0x10, &old_position);
    func_002AD6F0((u8 *)state + 0x20, &delta, &old_rotation, object + 0xF0);
}
