#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef int s32;

extern void func_2EEF88(void *);
extern void func_2EEFE0(void *, void *, void *);
extern void func_2EF0C8(void *, void *, void *);
extern void func_2EF298(void *, void *, float);
extern float func_2EF0A0(void *, void *);
extern void func_2EEFF8(void *, void *, void *, float);
extern void func_2EEFB0(void *, void *, void *);
extern float func_2EF190(void *, void *);
extern float func_2EF158(void *, void *);
extern void func_31EBA8(void *, float, float);
extern int func_360A80(int, int, void *);
extern void func_360780(int);
extern void func_32CEA0(void *, void *);
extern u8 D_L03_00188660[];

extern void func_31B920(void *entity, int a, int b);
extern int func_31B9F0(int id);
extern void func_320318(void *entity, void *target);
extern void func_2EEC20(void *target);
extern void func_326730(void *entity, void *target, int a, int b, float scale);
extern void func_312550(void *entity, int id, void *target);
extern void func_2EFD00(void *target, int a, float f);
extern float func_2F0048(float f0, float f1);
extern void func_324210(void *entity, void *target, int a, float f0, float f1);
extern u32 func_31CFF8(void *a, void *b, u32 c);
extern int func_3437D8(int index, void *a, void *out, float f);
extern void func_3A2F48(void *entry);
extern int func_31BA30(int a, int b);
extern float func_2F0148(int a);
extern void func_2FD088(int a, int b, float f);
extern void func_2E77F0(void *fn, void *entity);

/* The entity's per-frame sub-states; several are still INCLUDE_ASM markers
 * further down this file, hence the prototypes that repeat their definition. */
extern void func_L03_003F5B70(u8 *entity);
extern void func_L03_003F6158(u8 *entity);
extern void func_L03_003F64E8(u8 *entity);
extern void func_L03_003F6610(u8 *entity);
extern void func_L03_003F6748(u8 *entity);
extern void func_L03_003F6948(u8 *entity);
extern void func_L03_003F6BA8(u8 *entity);

/* `lui $v0,%hi ; lw $v0,%lo($v0)` in the retail: one register, no HIGH/LO_SUM
 * split, which is what the sda attribute (SYMBOL_REF_FLAG) gives in -G0. */
extern u8 *D_L03_001B2A1C __attribute__((sda));
extern u8 *D_L03_001FB5A0[];

/* One word of a stream: bits 0..14 name a record, bit 15 ends the walk. */
typedef struct {
    u16 raw;
} StreamEntry;

/* Measured partial layouts; the original types and game roles are unknown. */
typedef struct {
    u8 pad0[0x340];
    u32 entries[30];      /* 0x340 */
    u32 unknown3B8;       /* 0x3B8 */
    s32 count;            /* 0x3BC */
} LevelState;

typedef struct {
    u8 pad0[0x2DC];
    s32 current;          /* 0x2DC */
    u8 pad1[0x34];
    s32 table[1];         /* 0x314 */
} PickerState;

typedef struct {
    u32 field00;
    u8 pad04[0x0C];
    u8 field10[1];
} Entry41D1D8;

extern Entry41D1D8 *D_L03_001FE700[];

/* func_L03_003F09C0 is in L03_003F09C0-help-g8.c. */

/* func_L03_003F11A0 is in L03_003F11A0-g8.c. */

extern void func_L02_00327350(s32, s32);
extern void func_00288308(s32);
extern s32 func_002AD860(s32);
extern void func_0029F338(u8 *);
extern void func_0029B3E0(s32, s32);

/* Two flag bytes of the boot's state block, reached as members of one object: the stores
 * are then `lui $at ; sb` pairs that stay out of the call's delay slot, as in retail (a
 * separate symbol per byte puts the second store into the slot). */
extern u8 D_001A7B08[0x40] __attribute__((sda));
extern s32 D_L03_001B2A38[] __attribute__((sda));

/* Raises the two flags, sets the entity up from the state's words 0x58 and 0x5C, runs the two
 * boot steps with 13 (func_002AD860 returns a value that the caller drops; declaring it that way
 * is what fixes the register choice of the table address), then hands every entity of the
 * state's group (word 0x80) to func_0029F338 and ends with func_0029B3E0(0, -1). */
void func_L03_003F1470(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u16 *p;
    u8 *e;

    func_L02_00327350(*(s32 *)(state + 0x58), *(s32 *)(state + 0x5C));
    D_001A7B08[0x04] = 1;
    D_001A7B08[0x3C] = 1;
    func_00288308(13);
    func_002AD860(13);
    for (p = (u16 *)D_L03_001FB5A0[*(s32 *)(state + 0x80)];
         (*(s32 *)(state + 0x80) & 0xFF) != 0xFF && *(s32 *)(state + 0x80) <= D_L03_001B2A38[0] &&
         p != 0 && ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L03_001FB5A0[*(s32 *)(state + 0x80)]);
         p++) {
        e = D_L03_001B2A1C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        func_0029F338(e);
    }
    func_0029B3E0(0, -1);
}

/* func_L03_003F4638 is in L03_003F4638-g8.c. */

/* func_L03_003F5590 is in L03_003F5590-g8.c. */

/* func_L03_003F5B70 is in L03_003F5B70-g8.c. */

/* ticks the entity's sub-states, feeds the 0x95 counter to the engine and
 * re-arms its 200-second timer */
void func_L03_003F6080(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u32 timer;

    func_320318(entity, state + 0x70);
    func_L03_003F5B70(entity);
    func_L03_003F64E8(entity);
    func_L03_003F6610(entity);
    func_L03_003F6748(entity);
    func_L03_003F6158(entity);
    if (*(u8 *)(entity + 0x95) >= 2)
        func_2FD088(5, 0, *(float *)(state + 0x20) / func_2F0148(*(s16 *)(state + 0x24)));
    if (*(s32 *)(state + 0x3BC) != 0)
        func_2E77F0(func_L03_003F6948, entity);
    if (*(u8 *)(entity + 0x31) != 0)
        func_2E77F0(func_L03_003F6BA8, entity);
    timer = *(u16 *)(entity + 0x96);
    if (timer <= 0xFFFE) *(u16 *)(entity + 0x96) = (u16)(timer + 1);
}

/* func_L03_003F62C8 lives in L03_003F09C0-g8.c (it reaches D_L03_001B108C
 * through $gp). */

/* draws a value distinct from the state's current one and stores the table word it names */
void func_L03_003F6458(u8 *entity, s32 selector) {
    PickerState *state = *(PickerState **)(entity + 0x68);
    s32 value;

    do {
        if (selector == 1)
            value = func_31B9F0(3) * 2 + 1;
        else if (selector == 0)
            value = func_31B9F0(4) * 2;
        else
            value = func_31B9F0(7);
    } while (value == state->current);
    state->current = state->table[value];
}

/* func_L03_003F64E8 lives in L03_003F64E8-g8.c */

/* steps the entity's two blend channels and its rate */
void func_L03_003F6610(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);

    if (*(u8 *)(state + 0xD1) == 0) func_312550(entity, 7, state + 0xD0);
    func_2EFD00(state + 0xE0, 2, *(float *)(state + 0x338));
    *(float *)(state + 0x338) = func_2F0048(*(float *)(state + 0x338), 0.41597018f);
    func_324210(entity, state + 0x110, 0, 0.03f, 0.3f);
    func_324210(entity, state + 0x190, 1, 0.03f, 0.3f);
}

/* hands every record of the stream at slot 0xAC to func_3A2F48 */
void func_L03_003F66D8(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    s32 index = *(s32 *)(state + 0xAC);
    StreamEntry *entry;

    if (index == -1) return;
    entry = (StreamEntry *)D_L03_001FB5A0[index];
    if (entry == 0) return;
    do {
        func_3A2F48(D_L03_001B2A1C + ((entry->raw & 0x7FFF) << 8));
        if ((s16)entry->raw < 0) break;
        entry++;
    } while (1);
}

/* func_L03_003F6748 is defined in L03_003F6748-g8.c. */

/* appends one word to the level state's 30-entry table */
void func_L03_003F68E8(u8 *entity, u32 value) {
    LevelState *state = *(LevelState **)(entity + 0x68);

    if (state->count < 30) {
        state->entries[state->count] = value;
        state->count = state->count + 1;
    }
}

void func_L03_003F6918(u8 *entity, s32 index) {
    LevelState *state = *(LevelState **)(entity + 0x68);

    state->entries[index] = state->entries[--state->count];
}

/* func_L03_003F6948 is defined in L03_003F6948-g8.c. */

INCLUDE_ASM("asm/levels", func_L03_003F6BA8);

/* func_L03_003F6E88 is defined in L03_003F6E88-g8.c. */

/* The voice-load state the level shares with the engine: the key at +0x24, a
   cleared word at +0x28 and the busy flag at +0x68. */
typedef struct {
    u8 pad00[0x24];
    s32 key;
    s32 unk28;
    u8 pad2C[0x3C];
    s32 active;
} L03VoiceState;

extern L03VoiceState D_001A63A8;

/* Picks the free voice slot the entity asks for, unless the engine is busy
   or already holds that slot. */
void func_L03_003F71E0(u8 *a0, s32 a1) {
    L03VoiceState *st = &D_001A63A8;
    s32 sel = a1;
    u8 *a3 = *(u8 **)(a0 + 0x68);
    u8 *slot;
    s32 *row;
    u32 v;

    if (st->active != 0) return;
    if (st->key != -1) return;
    if (sel == *(s32 *)(a3 + 0x40C)) return;
    slot = a3 + sel;
    row = (s32 *)(a3 + sel * 4);
    v = *(u32 *)((u8 *)row + 0x3D0);
    st->unk28 = 0;
    st->key = (v & 0x3FFF) + 0x7D0;
    *(u8 *)(slot + 0x410) = 1;
    *(s32 *)(a3 + 0x408) = 0x258;
    *(s32 *)(a3 + 0x40C) = sel;
}

/* func_L03_004198B0 lives in L03_003F09C0-g8.c (it reaches D_L03_001A8F00
 * through $gp). */

/* func_L03_00419CA0 is in L03_00419CA0-effects.c. */

/* func_L03_0041A570 is in L03_0041A570-g8.c. */

/* func_L03_0041BE50 is in L03_0041BE50-g8.c. */

INCLUDE_ASM("asm/levels", func_L03_0041CA78);

/* func_L03_0041CEB0 is defined in L03_0041CEB0.c. */

/* func_L03_0041D0A8 lives in L03_003F09C0-g8.c (it reaches D_L03_001B2A1C
 * through $gp). */

/* func_L03_003F6918 has a near miss in drafts/L03_003F09C0-w29-nearmiss.c: the
 * body is byte-identical except that the two `addu` come out (index, base)
 * instead of the retail's (base, index). */

/* walks entity's stream, asking func_31BA30 for the value it stores at +0x2D8
 * of every record whose halfword at +0xAA is 0xFF3 */
void func_L03_0041D128(u8 *entity) {
    StreamEntry *entry;
    StreamEntry *p;
    u8 *record;

    if (entity[0x21] == 0xFF) return;
    entry = (StreamEntry *)D_L03_001FB5A0[entity[0x21]];
    if (entry == 0) return;
    p = entry;
    do {
        record = D_L03_001B2A1C + ((p->raw & 0x7FFF) << 8);
        if (*(signed char *)(record + 0x20) >= 0) {
            if (*(short *)(record + 0xAA) == 0xFF3) {
                u8 *owner = *(u8 **)(record + 0x68);

                *(int *)(owner + 0x2D8) = func_31BA30(0x28, 0x32);
            }
        }
        if ((s16)p->raw < 0) break;
        p++;
    } while (1);
}

/* asks the current entry to resolve; 1 when it consumed the query */
u32 func_L03_0041D1D8(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *sub = entity + 0x10;
    Entry41D1D8 *entry = D_L03_001FE700[*(s32 *)(state + 0x290)];
    u32 local[4];

    if (func_31CFF8(sub, entry->field10, entry->field00)) {
        if (func_3437D8(*(s32 *)(state + 0x290), sub, local,
                        *(float *)(state + 0x50)) == 0)
            return 1;
    }
    return 0;
}

/* func_L03_0041D258 is in L03_0041D258-g8.c. */

INCLUDE_ASM("asm/levels", func_L03_0041DAD0);

/* Projects the state position onto its path, clamps lateral displacement,
 * advances the path blend nearby, and maintains its movement sound. */
void func_L03_0041DCE0(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *entry = (u8 *)D_L03_001FE700[*(int *)(state + 0x210)];
    float delta[4], along[4], across[4], axis[4], point[4], scaled[4];
    float distance;
    float side;
    func_2EEF88(axis);
    func_2EEFE0(along, entry + 0x20, entry + 0x10);
    along[2] = 0;
    func_2EF0C8(across, along, axis);
    func_2EF298(across, across, 1.0f);
    func_2EF298(along, along, 1.0f);
    func_2EEFE0(delta, state + 0x1F0, entry + 0x10);
    delta[2] = 0;
    distance = func_2EF0A0(delta, across);
    if (distance > *(float *)(state + 0x218)) distance = *(float *)(state + 0x218);
    else if (distance < -*(float *)(state + 0x218)) distance = -*(float *)(state + 0x218);
    func_2EEFF8(point, entry + 0x10, entry + 0x20, *(float *)(state + 0x340));
    func_2EF298(scaled, across, distance);
    func_2EEFB0(point, point, scaled);
    func_2EEFE0(delta, state + 0x1F0, point);
    delta[2] = 0;
    side = func_2EF0A0(delta, along);
    if (func_2EF190(state + 0x1F0, point) < 6.0f) {
        float target = (side < 0.0f);
        func_31EBA8(state + 0x340, target, 0.016666668f);
    }
    if (func_2EF158(entity + 0x10, point) >= 0.5f) {
        u8 *sound = D_L03_00188660 + *(int *)(state + 0x350) * 0x70;
        if (*(u8 **)(sound + 0x88) != entity || !sound[0x74])
            *(int *)(state + 0x350) = func_360A80(0, 4, entity);
    } else {
        int slot = *(int *)(state + 0x350);
        if (slot != -1) {
            u8 *sound = D_L03_00188660 + slot * 0x70;
            if (*(u8 **)(sound + 0x88) == entity && sound[0x74]) func_360780(slot);
        }
        *(int *)(state + 0x350) = -1;
    }
    func_32CEA0(entity, point);
    *(int *)(state + 0x1A8) = 0;
}

/* func_L03_0041DFA8 lives in L03_003F09C0-g8.c (it reaches D_L03_001B1BF0
 * through $gp). */

/* func_L03_0041E240 lives in L03_003F09C0-g8.c (same $gp access). */

/* func_L03_0041E2D8 lives in L03_0041E2D8-g8.c */

INCLUDE_ASM("asm/levels", func_L03_0041EAE0);

/* re-arms the entity's two channel counters and its 200-second timer */
void func_L03_0041EF90(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u32 timer;

    func_320318(entity, state + 0x50);
    func_2EEC20(state + 0x320);
    func_2EEC20(state + 0x322);
    timer = *(u16 *)(entity + 0x96);
    if (timer <= 0xFFFE) *(u16 *)(entity + 0x96) = (u16)(timer + 1);
    func_326730(entity, state + 0x200, 0, 1, 2.0f);
}

void func_L03_0041F008(u8 *entity, u32 value) {
    u8 *state = *(u8 **)(entity + 0x68);

    func_31B920(entity, 6, 2);
    *(u32 *)(state + 0x338) = value;
}

/* func_L03_0041F048 is defined in L03_0041F048-qcopy-barrier.c. */

/* func_L03_0041F090 lives in L03_003F09C0-g8.c (it reaches D_L03_001B1C00
 * and D_L03_001B1C04 through $gp). */

/* func_L03_0041F178 is defined in L03_0041F178-g8.c. */

/* func_L03_0041F410 is in L03_0041F410-g8.c. */
