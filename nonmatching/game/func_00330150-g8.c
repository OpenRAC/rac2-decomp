/* SPDX-License-Identifier: MIT
 *
 * Near miss: func_00330150, the moby object's 32-step ground probe on the
 * state's own radius at +0x58, 904 bytes in the retail boot and in every
 * level, 28 places.
 *
 * Profile: -O2 -G8 -ffunction-sections, in a source unit named
 * 00330150-probe-g8.c. The -G8 is required: retail reads the two constants of
 * the small-data area (0.375 at 0x1B096C and 0.6 at 0x1B0970) $gp-relative,
 * which this compiler only does for an `sda' global in a small-data unit.
 *
 * Result: 904/904 bytes, 0/28 places in USA v1.01. The first difference is at
 * +0x0: retail's frame is 0x160 and this source's is 0x150, because retail
 * keeps one more word in the frame (its ninth scalar, the row at +0xE0) and
 * starts the saved registers at 0x100 where this source starts them at 0xF0.
 * The prologue, the copy of the game's probe order (six words from 0x1B09B0),
 * the radius test, the branch on the level's target flag, the call sequence
 * and the 32-step loop with its delay-slot increment all match in shape.
 *
 * The remaining difference is the local-registers pass again, and it decides
 * the frame size with it: retail gives $s0 to the tenth vector, $s3 to the
 * loop counter and keeps the object's row at +0xE0 in the frame, while this
 * source gives $s0 to the loop counter and $s3 to the tenth vector, which
 * leaves the row in a register and frees the frame's ninth word. The same
 * source shape as func_00327038's near miss moves the counter in the same way.
 */

#include "common.h"

/* func_00330150: the 32-step ground probe of a moby object, the sibling of
 * func_00327038: it reads the radius from the state's +0x58 (the other reads
 * +0x18) and writes the state field at +0x60 (the other writes +0x20). It
 * also starts from the game's own probe order, a six-entry permutation the
 * game keeps in the small-data area.
 *
 * Every address the function names differs from program to program: the boot
 * keeps its helpers and its constants at their own places, and each level has
 * its own copy of them. The names below are the boot's; the build reads each
 * program's own value from the retail bytes under the relocations.
 *
 * The unit needs -G8: the two small constants of the small-data area are read
 * $gp-relative, as retail does.
 */
typedef struct {
    int a, b, c, d, e, f;
} ProbeOrder;

/* The probe's vectors are 16-byte aligned, as the game's own are. */
typedef float Vec4[4] __attribute__((aligned(16)));

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

/* The game's probe order and the unit direction. */
extern ProbeOrder D_001B09B0;
extern float D_001B2830[4];
extern int D_001B2848;
/* The block of per-object vectors: the target pointers at +0x18, the hit point
 * at +0x20, the other vector at +0x30 and the normal at +0x40. */
extern int D_001BAF80[];
/* The two small constants of the small-data area: 0.375 and 0.6. */
extern float D_001B096C __attribute__((sda));
extern float D_001B0970 __attribute__((sda));

void func_00330150(char *object)
{
    ProbeOrder order;
    Vec4 v20, v30, v40, v50, v60, v70;
    Vec4 v80, v90, va0, vb0, vc0;
    char *state;
    int positive;
    int hits;
    float *p20;
    float *p80;
    char *origin;
    float *p90;
    char *rowD;
    char *rowE;
    char *target;
    int i;
    float t;
    float angle;
    float s;
    float c;

    state = *(char **)(object + 0x68);
    if (func_00282C48(*(float *)(state + 0x58)) < 0.0001f)
        return;
    positive = (*(float *)(state + 0x58) > 0.0f);
    target = object + 0x10;
    origin = object + 0x10;
    order = D_001B09B0;

    func_00282C88(v30);
    func_00282F20(v20, D_001B2830, -D_001B096C);
    func_00282CC0(v20, v20, object + 0x10);

    if (D_001B2848 == 0) {
        target = (char *)v40;
        if (func_00278870(v20, D_001B0970) != 0) {
            func_00282CF0(v40, (float *)&D_001BAF80[12], v20);
            func_00282CC0(origin, v40, origin);
        }
    }

    rowD = object + 0xD0;
    rowE = object + 0xE0;
    p20 = v20;
    p80 = v80;
    p90 = v90;
    hits = 0;
    for (i = 0; i < 32; i++) {
        t = func_00283CE0(i) / func_00283CE0(31);
        func_00282F20(target, rowD, D_001B0970);
        angle = t * 1.5707964f;
        s = func_00283198(angle);
        if (!positive)
            s = -s;
        func_00282D30(v60, rowE, s);
        c = func_00283180(angle);
        v70[0] = -v60[0];
        v70[1] = -v60[1];
        v70[2] = -v60[2];
        v70[3] = c;
        v60[3] = c;
        func_002837D0(v70, v60, target);
        func_002837D0(v50, v70, p80);
        func_00282CC0(v90, v50, p20);
        if (func_002761F8(p20, v90, 0, object, 0) != 0) {
            void *owner;

            func_00282D30(va0, D_001B2830, -1.0f);
            hits++;
            func_00282D30(vb0, (float *)&D_001BAF80[16], 0.0009765625f);
            func_00282F20(vb0, vb0, 1.0f);
            func_00282CF0(vc0, (float *)&D_001BAF80[8], p90);
            func_00282CC0(v30, v30, vc0);
            owner = (void *)D_001BAF80[6];
            if (owner != 0) {
                if (*(short *)(*(char **)(owner + 0x24) + 0x46) == 5) {
                    object[0x20] = 9;
                    *(int *)(state + 0x60) = 10;
                    i++;
                }
            }
        }
    }

    if (hits != 0) {
        func_00282D90((float)hits, v30);
        func_00282CC0(origin, origin, v30);
    }
}
