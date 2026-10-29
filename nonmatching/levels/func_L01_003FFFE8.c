/* Nonmatching event/transition controller, 2026-10-28. No C coverage credit.
 * Four US checks, 0/2. First macro-addressed flag body784/796B matched the
 * state/argument roles but incorrectly selected a GP delay-slot store where
 * retail is absolute. Incomplete NOT_SDA flag view gives792B and correct
 * address class, but saves an extra constant-one register and retains one
 * shorter boolean branch. Retained diagnostic profile -O2 -G0
 * -ffunction-sections -frac2-keep-block-order. Adding narrow unsplit edges
 * or broad -fno-gcse produces the same form: three equivalent forms, stop.
 * No option is retained in config. Reopen with an independent source/scope
 * witness for the one value and absolute flag accesses.
 *
 * Actual source contracts support the void variadic logger, object deletion,
 * transition setter, signed-int predicate and queue submission results,
 * slowdown publisher, music update, int action dispatcher, and64-bit formal
 * of002C1988. Ignored00288AA0/00288BE8/002BEB90 results remain int. Raw-only
 * B9D60,303530,AD7B8,DF3F8,29B3E0 return/formal hypotheses remain provisional;
 * complete extents are saved privately, not inferred from a missing result.
 * No local packet/vector. The indexed128-byte destination record supplies
 * complete16B position at+0x30 and16B orientation at+0x70 to B9D60. Globals,
 * error strings and history table remain incomplete. One macro mode-word
 * declaration models its observed GP delay-slot and absolute reads. The
 * separate flag uses only the observed absolute class, not an SDA alias.
 */

#include "common.h"
extern const char D_L01_001B1100[], D_L01_001B1140[], D_L01_001B1180[], D_L01_001B11B8[];
extern unsigned char D_0019B2E8[], D_00189EA0[], D_L01_001BF6C0[];
extern int D_001A79F0 __attribute__((sda));
extern unsigned char *D_L01_001B264C SDATA(D_L01_001B264C);
extern int D_L01_001B2094[] SDATA(D_L01_001B2094);
extern int D_L01_001B22A8[] NOT_SDA;
extern void func_0026FEB8(const char *, ...), func_0029F338(void *);
extern void func_002A7750(void *, int, int), func_0027D330(int);
extern int func_L00_00329520(void *, int);
extern void func_L00_002B9D60(const void *, const void *, int, int);
extern void func_L00_00303530(int, int);
extern int func_00288AA0(void *, int), func_00288BE8(void *);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_002AD7B8(int), func_002AF0A8(int), func_002A0430(unsigned int);
extern void func_002DF3F8(void *, void *);
extern void func_L01_002C1988(unsigned long);
extern int func_L01_002BEB90(int, int);
extern void func_L01_00323310(int, int), func_0029B3E0(int, int);

void func_L01_003FFFE8(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *row;
    int trigger, allowed;
    switch (object[0x20]) {
    case 0:
        if (*(int *)state == -1) func_0026FEB8(D_L01_001B1100, *(short *)(object + 0xB2));
        if (*(short *)(state + 4) == -1) func_0026FEB8(D_L01_001B1140, *(short *)(object + 0xB2));
        if (*(int *)(state + 8) == -1) func_0026FEB8(D_L01_001B1180, *(short *)(object + 0xB2));
        if (object[0xB0] != 0xFF) {
            if (D_0019B2E8[object[0xB0] + D_001A79F0 * 16] & 0x80) {
                func_0029F338(object);
                return;
            }
        } else func_0026FEB8(D_L01_001B11B8, *(short *)(object + 0xB2));
        func_002A7750(object, 1, -1);
        break;
    case 1:
        trigger = 0;
        if (!object[0xBC] && *(int *)state != -1 && func_L00_00329520(D_00189EA0, *(int *)state)) {
            if (*(int *)(state + 0x18)) trigger = 1;
            else if (*(int *)(D_00189EA0 + 0x2C0)) trigger = 1;
        }
        if (!trigger) return;
        object[0x30] = 0xFF;
        func_0027D330(20);
        if (*(int *)(state + 0xC) != -1) {
            row = D_L01_001B264C + *(int *)(state + 0xC) * 128;
            func_L00_002B9D60(row + 0x30, row + 0x70, 111, 1);
        }
        if (*(int *)(state + 8) != -1) func_L00_00303530(*(int *)(state + 8), 0);
        allowed = 1;
        if (D_001A79F0 == 8 && *(short *)(state + 4) == 0) {
            if (func_00288AA0(D_L01_001BF6C0, 87)) {
                func_00288AA0(D_L01_001BF6C0, 9);
                func_00288AA0(D_L01_001BF6C0, 88);
                func_00288BE8(D_L01_001BF6C0);
                func_002F5CC8();
                D_L01_001B2094[0] = 1;
            } else allowed = 0;
        }
        if (allowed) func_002A7750(object, 3, -1);
        break;
    case 3:
        D_L01_001B22A8[0] = 1;
        if (func_002F5D10()) return;
        D_L01_001B22A8[0] = 0;
        if (*(short *)(state + 6) != -1) {
            func_002AD7B8(*(short *)(state + 6));
            func_002AF0A8(*(short *)(state + 6));
        }
        func_002A7750(object, 4, -1);
        break;
    case 4:
        if (object[0xB0] != 0xFF && !(D_0019B2E8[object[0xB0] + D_001A79F0 * 16] & 0x80)) func_002A0430(object[0xB0]);
        func_002DF3F8(object + 0x10, object + 0xF0);
        func_L01_002C1988(0);
        func_L01_002BEB90(0, 1);
        func_L01_00323310(*(int *)(state + 0x14), *(int *)(state + 0x10));
        func_0029B3E0(0, -1);
        func_0029F338(object);
        break;
    }
}
