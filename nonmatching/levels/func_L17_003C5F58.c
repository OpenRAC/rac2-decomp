/* func_L17_003C5F58 - 472 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Draft logic is decoded fully (loop i<5; slot checks; copy pos (Quad), atan2
   via func_00283248, state 2). Needs -g8 sibling (D_L17_001B0344 sda at
   gp+0x1354).
   420 vs 472 bytes. Retail does NOT strength-reduce the loop: s5=i, `sll
   s1,s5,2` each iteration (in loop-bottom delay slot), `addu v0,s3,s1` per
   use,
   hoists lui s2 (0x19 = D_00189EA0 hi, later reused as &st[0xD8+4i]), lui s4
   0x20 (table hi), fp=table, s7=obj+0x10.
   Mine reduces the i*4 giv into a pointer (s1 += 4). Tried: while(++i<5),
   int* p = st+i*4. */

#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

extern int func_002ACBC8(void *);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern char D_00189EA0[];
extern char *D_L17_001FE880[];
extern float D_L17_001B0344 __attribute__((sda));

void func_L17_003C5F58(u8 *obj) {
    u8 *st = *(u8 **)(obj + 0x68);
    int i;
    int t;
    u8 *target;

    for (i = 0; i < 5; i++) {
        if (*(int *)(st + i * 4 + 0xB0) == -1 && *(int *)(st + 0xA4) != i) {
            continue;
        }
        if (func_002ACBC8(D_00189EA0) == 0 && *(int *)(st + 0xA4) != i) {
            continue;
        }
        target = *(u8 **)(obj + 0x24);
        *(int *)(obj + 0x98) = *(int *)(target + 0x10);
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(obj + 0x98) = *(int *)(target + 0x10);
        t = *(int *)(st + i * 4 + 0xC4);
        if (t != -1) {
            target = (u8 *)D_L17_001FE880[t];
            *(Quad *)(obj + 0x10) = *(Quad *)(target + 0x10);
            *(f32 *)(obj + 0xF8) = func_00283248(*(f32 *)(target + 0x20) - *(f32 *)(obj + 0x10), *(f32 *)(target + 0x24) - *(f32 *)(obj + 0x14));
        } else {
            t = *(int *)(st + i * 4 + 0xD8);
            if (t != -1 && func_00282E80(obj + 0x10, D_L17_001FE880[t] + 0x10) > 2.0f) {
                target = (u8 *)D_L17_001FE880[*(int *)(st + i * 4 + 0xD8)];
                *(Quad *)(obj + 0x10) = *(Quad *)(target + 0x10);
                *(f32 *)(obj + 0xF8) = func_00283248(*(f32 *)(target + 0x20) - *(f32 *)(obj + 0x10), *(f32 *)(target + 0x24) - *(f32 *)(obj + 0x14));
            }
        }
        obj[0xBC] = i;
        obj[0x20] = 2;
        *(u16 *)(obj + 0x32) = 0x80;
        *(f32 *)(st + 0x90) = D_L17_001B0344 * 0.008333334f;
        *(int *)(st + 0xA4) = -1;
        *(int *)(st + 0x94) = 1;
        return;
    }
}
