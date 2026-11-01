/* SPDX-License-Identifier: MIT
 *
 * Near miss: func_00327038, the moby object's 32-step ground probe, 840 bytes
 * in the retail boot and in every level, 28 places.
 *
 * Profile: -O2 -G8 -ffunction-sections, in a source unit named
 * 00327038-probe-g8.c. The -G8 is required: retail reads the two constants of
 * the small-data area (0.375 at 0x1B0108 and 0.6 at 0x1B010C) $gp-relative,
 * which this compiler only does for an `sda' global in a small-data unit.
 *
 * Result: 840/840 bytes, 0/28 places in USA v1.01. The first difference is at
 * +0x4: retail saves $s1 where this source saves $s2. The frame size (0x130),
 * the stack layout (the eleven vector locals at 0x00..0xA0 and the eight
 * scalars at 0xB0..0xCC), the call sequence, the 32-step loop with its
 * delay-slot increment and its extra increment, the dead -1.0f store and the
 * epilogue all match. What differs is the local-register assignment: retail
 * gives $s1 to the object, $s0 to the probe pointer, $s2 to the ninth vector,
 * $s3 to the loop counter and $s4/$s5/$s6/$s7/$fp to the five vector
 * addresses; this source gives $s1 to the loop counter, $s2 to the object and
 * $s3 to the ninth vector, and moves the object and the counter around the
 * ninth vector. Everything that follows the swap (the argument setup in the
 * branch delay slots, the epilogue's restore order) follows from it.
 *
 * The remaining difference is the local-registers pass: the same source with
 * the vector at +0x70 read through its pointer instead of directly changes
 * which of the two is promoted, so the assignment is decided by how often the
 * pointer and the array are named, not by their size. A source that names the
 * object and the loop counter in the order retail allocates them is the next
 * experiment.
 */

#include "common.h"

/* func_00327038: the 32-step ground probe of a moby object.
 *
 * The object holds a state record at +0x68; its radius at +0x18 decides whether
 * the probe runs at all (a vanishing radius gives up) and whether the sampled
 * angle is mirrored. The probe starts from the object's own basis and sweeps a
 * quarter turn, looking for a ground hit under the object. A hit records the
 * hit point, and a hit on a surface of the fifth kind stops the sweep and puts
 * the object into state 9 (the state record into 10).
 *
 * Every address the function names differs from program to program: the boot
 * keeps its helpers and its constants at their own places, and each level has
 * its own copy of them. The names below are the boot's; the build reads each
 * program's own value from the retail bytes under the relocations.
 *
 * The unit needs -G8: the two small constants of the small-data area are read
 * $gp-relative, as retail does.
 */
extern float func_00282C48(float);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(float *, float *, char *);
extern void func_00282D30(void *, void *, float);
extern void func_00282D90(float, void *);
extern void func_00282F20(float *, float *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002837D0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00278870(void *, float);
extern int func_002761F8(void *, void *, int, void *, int);

/* The unit direction and the level's own target flag. */
extern float D_001B27B0[4];
extern int D_001B27C8;
/* The block of per-object vectors: the target pointers at +0x18, the hit point
 * at +0x20, the other vector at +0x30 and the normal at +0x40. */
extern int D_001BAF80[];
/* The two small constants of the small-data area: 0.375 and 0.6. */
extern float D_001B0108 __attribute__((sda));
extern float D_001B010C __attribute__((sda));

void func_00327038(char *object)
{
    float v0[4], v1[4], v2[4], v3[4], v4[4], v5[4];
    float v6[4], v7[4], v8[4], v9[4], v10[4];
    char *state;
    int negative;
    int hits;
    char *rowD;
    char *rowE;
    float *p6;
    float *p7;
    char *target;
    int i;
    float t;
    float angle;
    float s;
    float c;

    state = *(char **)(object + 0x68);
    if (func_00282C48(*(float *)(state + 0x18)) < 0.0001f)
        return;
    negative = (*(float *)(state + 0x18) <= 0.0f);
    target = object + 0x10;

    func_00282C88(v1);
    func_00282F20(v0, D_001B27B0, -D_001B0108);
    func_00282CC0(v0, v0, object + 0x10);

    if (D_001B27C8 == 0) {
        target = (char *)v2;
        if (func_00278870(v0, D_001B010C) != 0) {
            func_00282CF0(v2, (float *)&D_001BAF80[12], v0);
            func_00282CC0(object + 0x10, v2, object + 0x10);
        }
    }

    rowD = object + 0xD0;
    rowE = object + 0xE0;
    p6 = v6;
    p7 = v7;
    hits = 0;
    for (i = 0; i < 32; i++) {
        t = func_00283CE0(i) / func_00283CE0(31);
        func_00282F20(target, rowD, D_001B010C);
        angle = t * 1.5707964f;
        s = func_00283198(angle);
        if (!negative)
            s = -s;
        func_00282D30(v4, rowE, s);
        c = func_00283180(angle);
        v5[0] = -v4[0];
        v5[1] = -v4[1];
        v5[2] = -v4[2];
        v5[3] = c;
        v4[3] = c;
        func_002837D0(v5, v4, target);
        func_002837D0(v3, v5, p6);
        func_00282CC0(v7, v3, v0);
        if (func_002761F8(v0, v7, 0, object, 0) != 0) {
            void *owner;

            func_00282D30(v8, D_001B27B0, -1.0f);
            hits++;
            func_00282D30(v9, (float *)&D_001BAF80[16], 0.0009765625f);
            func_00282F20(v9, v9, 1.0f);
            func_00282CF0(v10, (float *)&D_001BAF80[8], p7);
            func_00282CC0(v1, v1, v10);
            owner = (void *)D_001BAF80[6];
            if (owner != 0) {
                if (*(short *)(*(char **)(owner + 0x24) + 0x46) == 5) {
                    object[0x20] = 9;
                    *(int *)(state + 0x20) = 10;
                    i++;
                }
            }
        }
    }

    if (hits != 0) {
        func_00282D90((float)hits, v1);
        func_00282CC0(object + 0x10, object + 0x10, v1);
    }
}
