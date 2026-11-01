#include "include_asm.h"

#include "common.h"
extern void func_00283698(void *dst, void *src);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_002AFDD8(char *a, char *b, char *c, char *d);
extern float func_00282C48(float a);
extern void func_002830C0(void *dst, void *a, void *b);
extern float func_002A7878(float a, float b);
extern float func_00282C10(float a);
extern void func_00282D30(void *dst, void *src, float s);
extern void func_L14_003C96E0(char *e, void *v, float a, float b, float c);
extern void func_PAL_L00_002C4480(int a0, int a1);
extern unsigned short *D_L14_001FB060[];
extern unsigned char *D_L14_001B259C MACRO_ADDR;
extern int D_L14_001B25B8 __attribute__((sda));
struct Projection { char pad[0x38]; float height; char tail[0x44]; };
extern struct Projection *D_L14_001B268C MACRO_ADDR;
extern char D_00189E20[];
struct OwnerPrefix { char reserved00[0x60]; int tableIndex, groupIndex; };

void func_PAL_L14_003CF6C8(char *self) {
    float mtx[16] __attribute__((aligned(16)));
    float off[4] __attribute__((aligned(16)));
    float tmp[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    struct OwnerPrefix *state = *(struct OwnerPrefix **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;
    char *hero;
    char *hero2;
    int inside;
    float a;
    float b;
    float c;
    float duration;

    func_00283698(mtx, self + 0xC0);
    for (p = D_L14_001FB060[state->groupIndex];
         (state->groupIndex & 0xFF) != 0xFF && state->groupIndex <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[state->groupIndex]);
         p++) {
        e = ((*p & 0x7FFF) << 8) + D_L14_001B259C;
        if (e == 0)
            break;
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                func_00282CF0(off, e + 0x10, self + 0x10);
                func_002AFDD8(self, (char *)off, (char *)off, (char *)mtx);
                off[3] = 1.0f;
                off[0] = off[0] + 2.0f;
                inside = func_00282C48(off[0]) < 1.0f && func_00282C48(off[1]) < 1.0f;
                if (inside) {
                    func_002830C0(tmp, off, &D_L14_001B268C[state->tableIndex]);
                    func_L14_003C96E0((char *)e, tmp,
                                      D_L14_001B268C[state->tableIndex].height +
                                          func_002A7878(1.0f, 2.0f),
                                      0.008f, 0.008f);
                }
            }
        }
    }
    hero = D_00189E20;
    if ((*(char **)(hero + 0x33C) == self && *(int *)(hero + 0x340) != 0) ||
        *(float *)(hero + 0x31C) < 0.5f) {
        func_00282CF0(off, D_00189E20 + 0x80, self + 0x10);
        func_002AFDD8(self, (char *)off, (char *)off, (char *)mtx);
        off[3] = 1.0f;
        off[0] = off[0] + 2.0f;
        inside = func_00282C48(off[0]) < 1.0f && func_00282C48(off[1]) < 1.0f;
        if (inside) {
            func_002830C0(tmp, off, &D_L14_001B268C[state->tableIndex]);
            hero2 = D_00189E20;
            a = D_L14_001B268C[state->tableIndex].height + 1.5f;
            b = a - *(float *)(hero2 + 0x88);
            b *= 2.0f; duration = func_00282C10(b / 0.008f);
            c = (a - tmp[2]) * 2.0f; duration += func_00282C10(c / 0.008f);
            func_00282CF0(vec, tmp, hero2 + 0x80); func_00282D30(vec, vec, 1.0f / duration);
            vec[2] = func_00282C10(b * 0.008f);
            func_PAL_L00_002C4480(0x44, 1);
            qcopy(hero2 + 0xF0, vec);
        }
    }
}
