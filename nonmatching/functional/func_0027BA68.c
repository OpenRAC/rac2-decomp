/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* func_0027BA68 - 772 bytes, 28 places. Claude Opus 5.5 (xhigh), task v1962, USA v1.01.
 * Best check: 772/772 bytes, 0/28 places, check.py first mismatch +0x78, 12 rows really differ
 * (cdiff prints 53 of 193, the rest being masked relocations), in a unit of its own built with
 * -O2 -G16 -Wa,-G16 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier. Needs the declarations
 * below; cflags line: src/game/0027BA68-qcopy.c with those flags.
 * What differs in the C below:
 * 1. view_matrix $s4 / view_position $s1, retail $s1 / $s4 (8 of the 12 rows).
 * 2. lhu, a0, a1, a2, andi, jal [sh]; retail lhu, a0, andi, a1, sh, jal [a2] (4 rows).
 * Probe, not landable (do-while wrappers are forbidden): replace the `first` block with
 *     do { view_position = view_matrix - 0x230; } while (0);
 *     qcopy(&saved_position, view_position);
 * That fixes every register and leaves only the 4 rows of item 2. Why (priorities worked out by
 * hand from the sched dump's insn numbers; their order agrees with every allocation seen):
 * - Local-alloc order. Retail needs view_matrix > moby > D_001B9040 > view_position. The lui and
 *   addiu tie, so view_matrix's qty has 7 refs: 14/150, below moby's 14/146. It needs 8 refs
 *   (24/150). REG_N_REFS counts by loop depth, so one read inside loop notes supplies the eighth
 *   (the dump shows view_matrix used 6 times instead of 5).
 *   view_position must then stay under D_001B9040 (10/106): 5 refs do, 6 refs in 124 (the `first`
 *   tie, 12/124) do not.
 * - Position after the first func_00282B50. sched1 fills the free slot beside the func_002A01F0
 *   call with the addiu. A set of a pseudo crossing no call gets an anti-dependence on the last
 *   call (haifa sched_analyze_1), and LOG_LINKS are not cleared between passes, so it also holds
 *   in sched2. `first` below does that; so does a loop note.
 * Tried for the eighth view_matrix ref without a loop: a copy just before the third
 * func_00282B50, kept alive by a dead store after the loop or after the if/else. With the store
 * after the loop it is still in the gcse dump but gone by sched (cse2 is the likely cause, not
 * confirmed), and either way view_matrix stays at 5 refs. A copy right after the first
 * func_00282B50 does survive, but sched1 lifts it above the a1 read, which adds a daddu (129 rows).
 * Item 2: with lhu at t, a1 and a2 are issued at t+1 here; retail's order implies they are not
 * ready until t+2. They read only s1 and a constant. Ties, same 4 rows, on the probe: flag restore
 * through a short local, an int local, a pointer local, a one-bit bitfield; a long byte count;
 * dst/src/n in locals before the restore. A loop note should not be able to do it: it would have
 * to fall after the lhu and before a1, a2 and sh, but the a-register moves follow the store in RTL
 * order. Measured on the probe, none matches: do-while around the restore (15 rows), the call (4
 * rows, another order), both (15), the first restore and call (18), the first call (8), and a
 * restore split around one (15). Next idea, untested: whatever gives a1 and a2 a one-cycle-later
 * dependence; a no-code insn such as a same-register extendsidi2 would fit the timing.
 */
#include "common.h"

typedef struct { float x, y, z, w; } QuadPoint;
extern void func_0027B9C0(int, int, float);
extern void func_0027BA48(void);
extern void func_002FC560(unsigned int, unsigned long);
/* Snapshot the view, render the selected object into a texture, then draw
   its four-corner world-space quad after restoring the view. */
typedef struct {
    QuadPoint vertices[4];
    unsigned int colors[4];
    float uv[4][2];
    unsigned long state[4];
} CaptureQuad;
typedef struct { char pad[0x34]; unsigned short flags; } CaptureMoby;
typedef struct { QuadPoint position; float angles[4]; QuadPoint vertices[4]; float width, height; CaptureMoby *moby; } CaptureObject;
typedef struct { char pad[0x50]; CaptureObject *capture; } CaptureState;
extern CaptureState D_001B8840;
extern char D_001B5570[];
typedef struct { char pad[0xB0]; float scale; } CaptureView;
extern CaptureView D_001B9040;
extern char D_001C2AC0[];
extern QuadPoint D_001A8820 __attribute__((sda));
extern QuadPoint D_001A8830 __attribute__((sda));
extern QuadPoint D_001A8840 __attribute__((sda));
extern QuadPoint D_001A8850 __attribute__((sda));
extern float D_001A87F8[4] __attribute__((sda));
extern float D_001A8808[4] __attribute__((sda));
extern unsigned long D_001A7470[] __attribute__((sda));
extern int D_001B1B58[] __attribute__((sda));
extern void func_002A0250(void), func_002A01C8(void), func_002A01F0(void);
extern void func_002A0300(void *, int);
extern void func_00282B50(void *, void *, int);
extern void func_00129178(void *);
extern void func_001292C0(void *, void *, float);
extern void func_00129368(void *, void *, float);
extern void func_00129218(void *, void *, float);
extern void func_00279D18(void);
extern void func_002A0468(void *, int, int, int, int);
extern void func_0027AB40(void), func_002FC748(void), func_002A0220(void), func_002A0380(void), func_002A03C0(void);
extern void func_00280B90(void *, int, int);

void func_0027BA68(void)
{
    CaptureObject *object = D_001B8840.capture;
    QuadPoint saved_matrix[4], saved_position, matrix[4];
    CaptureQuad quad;
    if (object) {
        CaptureMoby *moby = object->moby;
        QuadPoint *position = &object->position;
        char *view_matrix;
        char *view_position;
        float saved_scale;
        void *scene;
        int i;
        func_002A0250();
        func_002A01C8();
        view_matrix = D_001B5570;
        func_002A01F0();
        scene = (void *)D_001B1B58[1];
        moby->flags |= 1;
        func_002A0300(scene, -1);
        moby->flags &= ~1;
        func_00282B50(saved_matrix, view_matrix, 0x40);
        {
            char *first = view_matrix - 0x230;
            qcopy(&saved_position, first);
            view_position = first;
        }
        saved_scale = D_001B9040.scale;
        func_0027B9C0(8, 8, 1.0f);
        func_00129178(matrix);
        func_001292C0(matrix, matrix, object->angles[0]);
        func_00129368(matrix, matrix, object->angles[1]);
        func_00129218(matrix, matrix, object->angles[2]);
        func_00282B50(view_matrix, matrix, 0x40);
        qcopy(view_position, position);
        func_00279D18();
        func_002A0468(moby, 0x404040, 0xE, 0, 0);
        qcopy(D_001C2AC0, &D_001A8820);
        qcopy(D_001C2AC0 + 0x20, &D_001A8830);
        qcopy(D_001C2AC0 + 0x10, &D_001A8840);
        qcopy(D_001C2AC0 + 0x30, &D_001A8850);
        func_002A0300(moby, 1); func_0027BA48();
        D_001B9040.scale = saved_scale;
        func_0027AB40();
        func_00282B50(view_matrix, saved_matrix, 0x40);
        qcopy(view_position, &saved_position);
        func_00279D18();
        func_002FC560(0x42, 0x8000000044UL); func_002FC560(8, 5);
        func_002FC748(); func_002A0220(); func_002A0380();
        quad.state[1] = D_001A7470[0];
        quad.state[2] = 0xFF9000000260UL;
        quad.state[0] = 5;
        quad.state[3] = 0x8000000044UL;
        for (i = 0; i < 4; i++) {
            quad.colors[i] = 0x80808080;
            quad.uv[i][0] = object->width * D_001A87F8[i] + 0.5f;
            quad.uv[i][1] = object->height * D_001A8808[i] + 0.5f;
            qcopy(&quad.vertices[i], &object->vertices[i]);
        }
        func_00280B90(&quad, 0, 0);
    } else func_002A03C0();
}
