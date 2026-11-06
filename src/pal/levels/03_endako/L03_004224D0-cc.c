/* func_PAL_L03_004224D0, the PAL copy of func_L03_0041D128: the same C, where scale func_31BA30(0x28, 0x32); lit 0x6 becomes 0x5; rename func_31BA30 becomes func_002A7820. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef int s32;

extern int func_002A7820(int a, int b);
/* The entity's per-frame sub-states; several are still INCLUDE_ASM markers
 * further down this file, hence the prototypes that repeat their definition. */
extern void func_L03_003F6610(u8 *entity);
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
    u32 field00;
    u8 pad04[0x0C];
    u8 field10[1];
} Entry41D1D8;

extern Entry41D1D8 *D_L03_001FE700[];

/* func_L03_003F09C0 is in L03_003F09C0-help-g8.c. */

/* func_L03_003F11A0 is in L03_003F11A0-g8.c. */

/* Two flag bytes of the boot's state block, reached as members of one object: the stores
 * are then `lui $at ; sb` pairs that stay out of the call's delay slot, as in retail (a
 * separate symbol per byte puts the second store into the slot). */
/* Raises the two flags, sets the entity up from the state's words 0x58 and 0x5C, runs the two
 * boot steps with 13 (func_002AD860 returns a value that the caller drops; declaring it that way
 * is what fixes the register choice of the table address), then hands every entity of the
 * state's group (word 0x80) to func_0029F338 and ends with func_0029B3E0(0, -1). */
/* func_L03_003F4638 is in L03_003F4638-g8.c. */

/* func_L03_003F5590 is in L03_003F5590-g8.c. */

/* func_L03_003F5B70 is in L03_003F5B70-g8.c. */

/* ticks the entity's sub-states, feeds the 0x95 counter to the engine and
 * re-arms its 200-second timer */
/* func_L03_003F62C8 lives in L03_003F09C0-g8.c (it reaches D_L03_001B108C
 * through $gp). */

/* draws a value distinct from the state's current one and stores the table word it names */
/* func_L03_003F64E8 lives in L03_003F64E8-g8.c */

/* steps the entity's two blend channels and its rate */
void func_L03_003F6610(u8 *entity);

/* hands every record of the stream at slot 0xAC to func_3A2F48 */
/* func_L03_003F6748 is defined in L03_003F6748-g8.c. */

/* appends one word to the level state's 30-entry table */
/* func_L03_003F6948 is defined in L03_003F6948-g8.c. */

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
/* func_L03_004198B0 lives in L03_003F09C0-g8.c (it reaches D_L03_001A8F00
 * through $gp). */

/* func_L03_00419CA0 is in L03_00419CA0-effects.c. */

/* func_L03_0041A570 is in L03_0041A570-g8.c. */

/* func_L03_0041BE50 is in L03_0041BE50-g8.c. */

/* func_L03_0041CA78 is in L03_0041CA78-g8.c. */

/* func_L03_0041CEB0 is defined in L03_0041CEB0.c. */

/* func_L03_0041D0A8 lives in L03_003F09C0-g8.c (it reaches D_L03_001B2A1C
 * through $gp). */

/* func_L03_003F6918 has a near miss in drafts/L03_003F09C0-w29-nearmiss.c: the
 * body is byte-identical except that the two `addu` come out (index, base)
 * instead of the retail's (base, index). */

/* walks entity's stream, asking func_002A7820 for the value it stores at +0x2D8
 * of every record whose halfword at +0xAA is 0xFF3 */
void func_PAL_L03_004224D0(u8 *entity) {
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
            if (*(short *)(record + 0xAA) == 0xff3) {
                u8 *owner = *(u8 **)(record + 0x68);

                *(int *)(owner + 0x2D8) = (((int)(func_002A7820(0x28, 0x32)) * 5 + 2) / 6);
            }
        }
        if ((s16)p->raw < 0) break;
        p++;
    } while (1);
}

/* asks the current entry to resolve; 1 when it consumed the query */
/* func_L03_0041D258 is in L03_0041D258-g8.c. */

/* Projects the state position onto its path, clamps lateral displacement,
 * advances the path blend nearby, and maintains its movement sound. */
/* func_L03_0041DFA8 lives in L03_003F09C0-g8.c (it reaches D_L03_001B1BF0
 * through $gp). */

/* func_L03_0041E240 lives in L03_003F09C0-g8.c (same $gp access). */

/* func_L03_0041E2D8 lives in L03_0041E2D8-g8.c */

/* func_L03_0041EAE0 lives in L03_0041EAE0-g8.c */

/* re-arms the entity's two channel counters and its 200-second timer */
/* func_L03_0041F048 is defined in L03_0041F048-qcopy-barrier.c. */

/* func_L03_0041F090 lives in L03_003F09C0-g8.c (it reaches D_L03_001B1C00
 * and D_L03_001B1C04 through $gp). */

/* func_L03_0041F178 is defined in L03_0041F178-g8.c. */

/* func_L03_0041F410 is in L03_0041F410-g8.c. */
