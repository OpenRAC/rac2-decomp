#include "include_asm.h"

#include "common.h"
extern void func_00283698(void *dst, void *src);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_002AFDD8(void *a, void *b, void *c, void *d);
extern float func_00282C48(float a);
extern void func_00283098(void *dst, void *a, void *mtx);
extern void func_00282CC0(void *dst, void *a, void *b);
extern void func_L14_003C9658(char *e, void *v);
extern unsigned short *D_L14_001FB060[];
extern unsigned char *D_L14_001B259C __attribute__((sda));
extern int D_L14_001B25B8 __attribute__((sda));
extern float func_00282C48(float a);
extern void func_00283698(void *dst, void *src);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_002AFDD8(void *a, void *b, void *c, void *d);
extern void func_00283098(void *dst, void *a, void *mtx);
extern void func_00282CC0(void *dst, void *a, void *b);
extern void func_L14_003C9658(char *e, void *v);
extern unsigned short *D_L14_001FB060[];
extern unsigned char *D_L14_001B259C __attribute__((sda));
extern int D_L14_001B25B8 __attribute__((sda));

/* The twin of func_L14_003DF200 for the group word at +0x64: the same pass over the entities
   of the owner's group (not the states 0xFE and 0xFD, not the class 0xA59, accepted by
   func_L14_003C9548), with the box centred at -2.0 on the first axis: beyond 0.8 of it the
   offset is pulled back to -1.5 or -2.5, beyond 0.8 on the second axis to +-0.5, and the entity
   is handed the corrected world position (func_L14_003C9658). */
void func_PAL_L14_003CF468(char *self) {
    float mtx[16];
    float off[4];
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;
    int clamped;

    func_00283698(mtx, self + 0xC0);
    for (p = D_L14_001FB060[*(int *)(state + 0x64)];
         (*(int *)(state + 0x64) & 0xFF) != 0xFF && *(int *)(state + 0x64) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[*(int *)(state + 0x64)]);
         p++) {
        e = D_L14_001B259C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                if (*(short *)(e + 0xAA) != 0xA59) {
                    if (func_L14_003C9548((char *)e) != 0) {
                        func_00282CF0(off, e + 0x10, self + 0x10);
                        clamped = 0;
                        func_002AFDD8(self, off, off, mtx);
                        if (func_00282C48(off[0] + 2.0f) > 0.8f) {
                            clamped = 1;
                            if (off[0] > -1.5f)
                                off[0] = -1.5f;
                            else if (off[0] < -2.5f)
                                off[0] = -2.5f;
                        }
                        if (func_00282C48(off[1]) > 0.8f) {
                            clamped = 1;
                            if (off[1] > 0.5f)
                                off[1] = 0.5f;
                            else if (off[1] < -0.5f)
                                off[1] = -0.5f;
                        }
                        if (clamped) {
                            func_00283098(off, off, self + 0xC0);
                            func_00282CC0(off, off, self + 0x10);
                            func_L14_003C9658((char *)e, off);
                        }
                    }
                }
            }
        }
    }
}

