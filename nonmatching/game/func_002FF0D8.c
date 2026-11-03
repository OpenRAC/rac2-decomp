/* 3 November 2026: owning resident-view repair, original G0/g profile.
 * The resident byte object remains incomplete; only its actual preview-vector
 * prefix is typed. Model lookup preserves the observed 0x1220 + index*0x50
 * addressing without declaring the owner as a made-up one-slot model array.
 * All captures, request stores, inputs and pointer results are unchanged.
 * Fresh GNU-default check: 428/428 bytes, 0/28 USA, first mismatch +0x90.
 * The voice selection/key/constant scheduling residual remains. No matching
 * published macro was established in the consulted current RAC1 interfaces;
 * no do/while wrapper, volatility or dependency is invented to simulate one.
 * Reopen on actual request-source/control-flow evidence. No alternate-release
 * or linked build was run for this failed candidate.
 */
/* Historical notes describe the preceding retained source. */
/* Closer C, 3 November 2026 (opus-1, task v2129): 428/428 bytes, 0/28 places, 3 rows differ.
 * Build: its own unit (e.g. src/game/002FC8D0-start.c) with config/cflags.txt line "-O2 -G0 -ffunction-sections -g";
 * without -g the two nops before div.s go and it is 420 bytes. Declarations below (VoiceRequest = D_001A63A8 as in
 * 00289178.c; resident block D_00189E20 with model slots at 0x1220; Transition as one incomplete sda array).
 * Left: in the voice-request block retail stores selection, key, then loads 1 for D_001AD7E4; here sched1 hoists
 * both constants (priority 2 over the stores) and the reg-weight tie puts key/E4 first. Retail's order needs a
 * scheduling barrier between the key store and "li 1" (a loop note, as a do { } while (0) macro body would give;
 * a do-while(0) test changes the size to 432 and is disallowed anyway). volatile on the fields does not give it.
 * Per-arm scoped record pointers matter: one shared record pointer loses its base value and reorders the else arm.
 */
#include "common.h"

extern u16 D_001AD7F8 SDATA(D_001AD7F8);
typedef struct {
    s16 elapsed;
    s16 count;
    float rate;
    s16 item;
    s16 pad1A;
    u8 flag1C;
    u8 flag1D;
    u8 pad1E[2];
    float from[4];
    float to[4];
    unsigned char *model;
    u8 pad44;
    u8 owned;
} Transition;
extern Transition D_001B2310[] __attribute__((sda));
extern int D_001AD7E4[] SDATA(D_001AD7E4);
extern int D_001AD7E8[] SDATA(D_001AD7E8);
/* Real preview vectors in the owning resident byte object. The model-slot
 * table is addressed from that complete object, without a made-up one-slot bound. */
typedef struct {
    unsigned char pad00[0x80];
    float previewFrom[4], previewTo[4];
} ResidentPreviewPrefix;
extern unsigned char D_00189E20[];
#define PREVIEW ((ResidentPreviewPrefix *)D_00189E20)
/* The voice player's request block (see 00289178.c). */
typedef struct {
    char pad00[0x24];
    int key, selection;
    char pad2C[0x3C];
    int active;
} VoiceRequest;
extern VoiceRequest D_001A63A8;
extern unsigned char D_00139568[];
extern unsigned char D_00239BA0[];
extern float func_00283CE0(int);
extern char *func_002FF300(int, int);

void func_002FF0D8(void)
{
    D_001B2310[0].count = D_001AD7F8;
    D_001B2310[0].rate = 1.0f / func_00283CE0(D_001B2310[0].count);
    qcopy(D_001B2310[0].from, PREVIEW->previewFrom);
    qcopy(D_001B2310[0].to, PREVIEW->previewTo);
    D_001B2310[0].elapsed = 0;
    if (!D_001A63A8.active && D_001A63A8.key == -1) {
        D_001A63A8.selection = 0;
        D_001A63A8.key = 0xDB7;
        D_001AD7E4[0] = 1;
        D_001AD7E8[0] = 0;
    }
    D_001B2310[0].flag1C = 0;
    D_001B2310[0].flag1D = 0;
    if (D_001B2310[0].item == 31) {
        unsigned char *record = D_00139568[31] * 0xE0 + D_00239BA0;
        D_001B2310[0].model = (unsigned char *)func_002FF300(*(int *)(record + 0x14), 1);
        D_001B2310[0].owned = 0;
    } else if (D_001B2310[0].item == 45) {
        unsigned char *record = D_00139568[45] * 0xE0 + D_00239BA0;
        D_001B2310[0].model = (unsigned char *)func_002FF300(*(int *)(record + 0x14), -1);
        D_001B2310[0].owned = 0;
    } else if (D_001B2310[0].item == 9) {
        D_001B2310[0].model = (unsigned char *)func_002FF300(601, 0);
        D_001B2310[0].owned = 0;
    } else {
        unsigned char *record;
        char *resident;
        D_001B2310[0].owned = 1;
        record = D_00239BA0 + D_00139568[D_001B2310[0].item] * 0xE0;
        resident = (char *)D_00189E20;
        D_001B2310[0].model = *(unsigned char **)(resident + *(int *)(record + 0xC) * 0x50 + 0x1220);
    }
}
