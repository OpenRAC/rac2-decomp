/* func_L09_002F89F8 - 424 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Flags -O2 -G8 -ffunction-sections -Wa,-G64 (new unit; gp array
   D_L09_001A93F0 is 64 bytes). 420 vs 424 B. Retail keeps the high part of
   &D_L09_001BD700 in fp and recomputes fp-0x2900 per use (mine keeps one s1
   pointer), uses 'slt v0,9999,v1' for the upper bound (mine slti), and zeroes
   pos with 'sq $zero,0(v1)' (mine por+sq; a pointer var to the local gets
   folded away). Decoded semantics are in the draft. */

#include "include_asm.h"

typedef int Quadword __attribute__((mode(TI)));

typedef struct {
    char pad0[0x30];
    int mode;
    int value;
    char pad1[0x18];
    char *rig;
    char pad2[0x144];
    char *model;
    char pad3[0x28];
    int zero;
} L09_BD700;

extern int D_001A79F0;
extern int D_L09_00281210;
extern L09_BD700 D_L09_001BD700;
extern char D_L09_001B9A00[];
extern float D_L09_001A93E0 __attribute__((sda));
extern float D_L09_001A93F0[4][4] __attribute__((sda));

extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

void func_L09_002F89F8(void) {
    int sel = -1;
    int n = 0;
    char *model;

    if (D_001A79F0 == 9) {
        if (D_L09_001BD700.mode == 3) {
            sel = 1;
            n = 2;
        }
        if (sel != -1) {
            model = D_L09_001BD700.model;
            if (D_L09_001BD700.value >= sel && D_L09_001BD700.value <= 9999) {
                float matrix[12];
                float pos[4];
                float scratch[4];
                float *pp = pos;
                int k;
                int off = 0x20;

                D_L09_001BD700.rig = (char *)&D_L09_00281210;
                *(Quadword *)pp = 0;
                pos[2] = D_L09_001A93E0;
                func_002833F0(matrix, pos);
                for (k = 3; k >= 0; k--) {
                    func_00283098(D_L09_001BD700.rig + off, D_L09_001A93F0[3 - k], matrix);
                    func_00282CC0(D_L09_001BD700.rig + off, D_L09_001BD700.rig + off, model + 0x10);
                    func_00282CF0(scratch, D_L09_001B9A00, D_L09_001BD700.rig + off);
                    func_00282F20(scratch, scratch, 0.05f);
                    func_00282CC0(D_L09_001BD700.rig + off, D_L09_001BD700.rig + off, scratch);
                    off += 0x10;
                }
                *(int *)(D_L09_001BD700.rig + 0x68) = *(int *)((char *)&D_L09_001BD700 + 0x18C + n * 4);
                return;
            }
        }
        D_L09_001BD700.rig = 0;
    }
}
