/* Complete nonmatching reconstruction; 1648/1628 bytes.
 * -O2 -G8 -ffunction-sections.
 * Local release results: US 0/1, US2 absent, PAL absent.
 * 2 bounded source hypotheses. Remaining: Activation branches, linked-object reload lifetimes and checkpoint table addressing.
 * Reopen with independent original lifetime/control-flow evidence.
 * Retained code reads the linked index and trigger after 002B38B8,
 * preserving the observed call/reload order. The earlier 1644-byte form
 * captured them before the call and is not retained as production-quality C.
 */
#include "common.h"
typedef struct { float v[4]; } MovingPlatformVector __attribute__((aligned(16)));
typedef u8 MovingPlatformActor[0x100];
typedef u8 MovingPlatformMarker[0x80];
extern MovingPlatformActor *D_L19_001B2A1C __attribute__((sda));
extern MovingPlatformMarker *D_L19_001B2B0C;
extern u8 D_L19_0021EA30[] MACRO_ADDR, D_0019B2E8[] MACRO_ADDR, D_00189EA0[];
extern int D_001A79F0, D_L19_001B9D00;
extern void func_002A7750(void *, int, int), func_0029F338(void *), func_002A0430(int);
extern int func_L00_00329520(void *, int), func_002B38B8(void *), func_002B3868(void *);
extern u8 *func_002A9640(void *, int, int);
extern void func_00282CC0(void *, const void *, const void *), func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float), func_00282D30(void *, const void *, float);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int func_002E5CF8(int, int, void *);
extern float func_00283180(float), func_002AA150(float, float, float);
extern void func_L18_002CFF48(int), func_002AD6F0(void *, void *, void *, void *);

/* Trigger, destroy or move the platform between its saved and marker transforms. */
void func_L19_00411890(u8 *object)
{
    MovingPlatformVector oldPosition, oldRotation, delta, point;
    u8 *state = *(u8 **)(object + 0x68);
    int trigger, linked;
    float phase;
    qcopy(&oldPosition, object + 0x10);
    qcopy(&oldRotation, object + 0xF0);
    switch (object[0x20]) {
    case 0:
        if (*(int *)(state + 0x80) == -1) {
            *(u16 *)(object + 0x34) |= 2;
            func_002A7750(object, 4, -1);
            break;
        }
        *(int *)(state + 0x88) = 0;
        *(int *)(state + 0x5C) |= 1;
        qcopy(state + 0x60, object + 0x10);
        qcopy(state + 0x70, object + 0xF0);
        trigger = object[0xB0];
        if (D_L19_0021EA30[*(int *)(state + 0x8C) + 0x464] ||
            ((trigger = object[0xB0]) != 255 && state[0x92] && (D_0019B2E8[trigger + (D_001A79F0 << 4)] & 0x80)) ||
            (*(int *)(state + 0x98) != -1 && func_L00_00329520(D_00189EA0, *(int *)(state + 0x98)))) {
            qcopy(object + 0x10, D_L19_001B2B0C[*(int *)(state + 0x80)] + 0x30);
            qcopy(object + 0xF0, D_L19_001B2B0C[*(int *)(state + 0x80)] + 0x70);
            *(u16 *)(object + 0x34) |= 2;
            if (!state[0x91]) {
                func_0029F338(object);
                return;
            }
            func_002A7750(object, 3, -1);
        } else func_002A7750(object, 1, -1);
        break;
    case 1:
        if (object[0xBC] || func_002B38B8(object) || (linked = *(int *)(state + 0x8C)) == -1 ||
            D_L19_001B2A1C[linked][0x20] == 0xFE || D_L19_001B2A1C[linked][0x20] == 0xFD ||
            ((trigger = object[0xB0]) != 255 && state[0x92] && (D_0019B2E8[trigger + (D_001A79F0 << 4)] & 0x80)) ||
            (*(int *)(state + 0x98) != -1 && func_L00_00329520(D_00189EA0, *(int *)(state + 0x98)))) {
            if (*(int *)(state + 0x94) != -1) D_L19_001B2A1C[*(int *)(state + 0x94)][0xBC] = 1;
            if (state[0x93]) func_002A0430(object[0xB0]);
            func_002A7750(object, 2, -1);
        }
        if (!state[0x91] && func_002A9640(object, 0x40000, 0)) {
            if (*(int *)(state + 0x94) != -1) D_L19_001B2A1C[*(int *)(state + 0x94)][0xBC] = 1;
            func_00282CC0(&delta, object + 0xD0, object + 0xE0);
            func_00282F20(&delta, &delta, 0.083333336f);
            func_00282CC0(&point, object + 0x10, object + 0xE0);
            func_002ABBB8(object, &delta, &point, 0.0f, 0.0f, 10, 3, 16,
                          4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
            func_002B0A68(object, 31, &delta, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            *(u16 *)(object + 0x34) |= 1;
            object[0x31] = 0;
            *(int *)(object + 0x98) = 0;
            if (*(short *)(object + 0xAA) == 0x10ED) func_002E5CF8(0, 0, object);
            if (state[0x93]) func_002A0430(object[0xB0]);
            func_002A7750(object, 2, -1);
        }
        object[0xA8] = 255;
        break;
    case 2:
        if (func_002B3868(object) && (*(short *)(object + 0xAA) == 0xEDB || *(short *)(object + 0xAA) == 0x1146))
            func_002E5CF8(0, 0, object);
        *(float *)(state + 0x88) += 1.0f / *(float *)(state + 0x84);
        if (*(float *)(state + 0x88) > 1.0f) *(float *)(state + 0x88) = 1.0f;
        phase = (1.0f - func_00283180(*(float *)(state + 0x88) * 3.1415927f)) * 0.5f;
        func_00282CF0(&delta, D_L19_001B2B0C[*(int *)(state + 0x80)] + 0x30, state + 0x60);
        func_00282D30(&delta, &delta, phase);
        func_00282CC0(object + 0x10, state + 0x60, &delta);
        *(float *)(object + 0xF8) = func_002AA150(*(float *)(state + 0x78), *(float *)(D_L19_001B2B0C[*(int *)(state + 0x80)] + 0x78), phase);
        *(float *)(object + 0xF4) = func_002AA150(*(float *)(state + 0x74), *(float *)(D_L19_001B2B0C[*(int *)(state + 0x80)] + 0x74), phase);
        *(float *)(object + 0xF0) = func_002AA150(*(float *)(state + 0x70), *(float *)(D_L19_001B2B0C[*(int *)(state + 0x80)] + 0x70), phase);
        if (*(float *)(state + 0x88) >= 1.0f) func_002A7750(object, 3, -1);
        break;
    case 3:
        if (*(int *)(state + 0x94) == -1 || D_L19_001B2A1C[*(int *)(state + 0x94)][0xBC] == 0) {
            if (state[0x90]) {
                D_L19_001B9D00 = 0;
                func_L18_002CFF48(0);
            }
            *(u16 *)(object + 0x34) |= 2;
        }
        break;
    }
    if (object[0x20] < 3) {
        func_00282CF0(&delta, object + 0x10, &oldPosition);
        func_002AD6F0(state + 0x20, &delta, &oldRotation, object + 0xF0);
    }
}
