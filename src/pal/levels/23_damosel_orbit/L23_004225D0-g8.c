/* func_PAL_L23_004225D0, the PAL copy of func_L23_0041D398: the same C, where
 * the timer limits take the 50 Hz scale and the release's own callees their names.
 * Level 23 encounter damage phases. The function reads $gp data (hence -G8)
 * and lives in a unit of its own, like its neighbours.
 * The effect phases keep their index, table base, slot and direction in
 * block locals: sched1 then keeps the slot address after the random call,
 * and local-alloc gives direction, slot and index $s0, $s1 and $s2.
 * The local holding 10 puts its load ahead of the 1 while the stores keep
 * their order, as in retail.
 * The byte at PlayerStats +0xFD is read at a nonzero offset: that is a tied
 * two-word macro load, so reorg leaves the reread at its join instead of
 * copying it into the two branch slots as a $gp load.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
/* Two five-part windows share this ten-pointer table. */
typedef struct { u8 prefix[0x358]; char *parts[10]; } PartState;
extern char *D_L23_001B1484 __attribute__((sda));
extern int D_L23_001B1468 __attribute__((sda));
extern int D_L23_001B1434 __attribute__((sda));
extern char *D_L23_001B13D0 __attribute__((sda));
extern float D_L23_001B16D0 __attribute__((sda));
extern int D_L23_001B3720;
/* PlayerStats. */
extern u8 D_001A7A00[] __attribute__((sda));
extern int func_002F5D10(void);
extern void func_PAL_002A7650(char *, int, int);
extern void func_PAL_L23_00422C78(void);
extern void func_L00_003294F0(unsigned char *, int);
extern void func_0029F338(void *);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern int func_002E5CF8(int, int, char *);
extern void func_0029FC20(char *, int, char *);
extern void func_00282D30(char *, char *, float);
extern float func_002A7878(float, float);
extern void func_00282CC0(char *, char *, char *);
extern char *func_PAL_002735D0(char *, int, int, int, char *, char *, float *, int, float, float);
extern void func_00310C88(u8 *);
extern int func_002A77E0(int);

/* Move through the encounter's damage phases, detaching pieces and spawning debris. */
void func_PAL_L23_004225D0(char *object) {
    struct { Quad velocity, matrix[4], random; } local;
    /* The encounter state becomes a cursor into its part table in each phase. */
    union { PartState *state; char **parts; } cursor;
    char *particle;
    unsigned short timer;
    float scale;
    cursor.state = *(PartState **)(D_L23_001B1484 + 0x68);
    if (D_001A7A00[0xFD]) {
        if (*(unsigned short *)(object + 0x96) > (((int)(D_L23_001B1468 + 60) * 5 + 2) / 6)) {
            func_PAL_002A7650(object, 0, 3);
            func_PAL_L23_00422C78();
            return;
        }
    } else {
        if (*(unsigned short *)(object + 0x96) > (((int)(D_L23_001B1468 + 200) * 5 + 2) / 6) && !func_002F5D10()) {
            func_PAL_002A7650(object, 0, 3);
            func_PAL_L23_00422C78();
            return;
        }
        if (!D_001A7A00[0xFD] && *(unsigned short *)(object + 0x96) > (((int)(D_L23_001B1468 + 60) * 5 + 2) / 6)) {
            char *entryState;
            if (!D_L23_001B13D0) return;
            entryState = *(char **)(D_L23_001B13D0 + 0x68);
            entryState[13] = 1;
            entryState[8] = 0;
            func_L00_003294F0((unsigned char *)D_L23_001B13D0, 1);
            D_L23_001B13D0 = 0;
            return;
        }
    }
    if (D_L23_001B1434) {
        int i;
        cursor.parts = cursor.state->parts + 5;
        for (i = 5; i < 10; i++, cursor.parts++) {
            if (!D_L23_001B3720) {
                func_0029F338(*cursor.parts);
                *cursor.parts = 0;
                *(unsigned short *)(object + 0x34) |= 0x41;
                func_PAL_L00_003FB330(object + 16, 1, 135, 120, 120, 115, 125, 1, 6.5f, 20.0f, 1, 1, 1, 0);
                func_002E5CF8(12, 0, object);
            } else if (*cursor.parts) {
                int debrisIndex = 10 - D_L23_001B3720;
                func_0029FC20(object, i - 4, (char *)local.matrix);
                func_00282D30((char *)&local.velocity, (char *)&local.matrix[1], D_L23_001B16D0);
                scale = func_002A7878(0.0f, D_L23_001B16D0 * 0.5f);
                func_00282D30((char *)&local.random, object + 0xE0, scale);
                func_00282CC0((char *)&local.velocity, (char *)&local.velocity, (char *)&local.random);
                {
                    char *oldPart = *cursor.parts;
                    particle = func_PAL_002735D0(oldPart, 1, *(short *)(oldPart + 0xAA), debrisIndex, oldPart + 16, oldPart + 0xF0, (float *)&local.velocity, 255, 140.0f, 25.0f);
                    if (particle) *(void (**)(u8 *))(particle + 0x64) = func_00310C88;
                }
            }
        }
        D_L23_001B3720--;
        return;
    }
    timer = *(unsigned short *)(object + 0x96);
    if ((((int)((D_L23_001B1468 << 1) / 3) * 5 + 2) / 6) < timer) {
        int i;
        cursor.parts = cursor.state->parts;
        func_PAL_L00_003FB330(object + 16, 1, 45, 30, 40, 25, 85, 1, 4.5f, 20.0f, 1, 1, 1, 0);
        func_002E5CF8(11, 0, object);
        for (i = 4; i >= 0; i--, cursor.parts++) {
            char *replacement = cursor.parts[5];
            if (replacement) {
                char *old = *cursor.parts;
                if (!old) continue;
                qcopy(replacement + 0xC0, old + 0xC0);
                qcopy(replacement + 0xD0, old + 0xD0);
                qcopy(replacement + 0xE0, old + 0xE0);
                qcopy(replacement + 0x10, old + 0x10);
                *(unsigned short *)(replacement + 0x34) &= 0xFFF9;
                *(unsigned short *)(cursor.parts[5] + 0x34) |= 0x4000;
                *(unsigned short *)(cursor.parts[5] + 0x34) &= 0xFFBE;
                func_0029F338(*cursor.parts);
                *cursor.parts = 0;
            }
        }
        {
            int countdown = 10;
            D_L23_001B1434 = 1;
            D_L23_001B3720 = countdown;
        }
        return;
    }
    if ((((int)(D_L23_001B1468 / 3) * 5 + 2) / 6) < timer) {
        if (timer & 15) return;
        {
            int index = func_002A77E0(5);
            char **base = cursor.state->parts;
            char **slot = base + index;
            char *direction = *slot + 0xD0;
            int parity;
            scale = func_002A7878(4.0f, 12.0f);
            func_00282D30((char *)&local.velocity, direction, scale);
            func_00282CC0((char *)&local.velocity, (char *)&local.velocity, *slot + 16);
            scale = func_002A7878(2.3f, 3.7f);
            parity = index & 1;
            func_PAL_L00_003FB330(&local.velocity, parity, 20, 10, 14, 15, 25, 0, scale, 20.0f, parity, 0, 0, 0);
        }
        func_002E5CF8(func_002A77E0(3) + 13, 0, object);
        return;
    }
    if (timer & 31) return;
    {
        int index = func_002A77E0(5);
        char **base = cursor.state->parts;
        char **slot = base + index;
        char *direction = *slot + 0xD0;
        int parity;
        scale = func_002A7878(4.0f, 12.0f);
        func_00282D30((char *)&local.velocity, direction, scale);
        func_00282CC0((char *)&local.velocity, (char *)&local.velocity, *slot + 16);
        scale = func_002A7878(2.3f, 3.7f);
        parity = index & 1;
        func_PAL_L00_003FB330(&local.velocity, parity, 20, 10, 14, 15, 25, 0, scale, 20.0f, parity, 0, 0, 0);
    }
    func_002E5CF8(func_002A77E0(3) + 13, 0, object);
}
