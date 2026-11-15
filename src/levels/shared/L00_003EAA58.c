#include "include_asm.h"

extern void func_L00_003EAC88(char *);
/* Partial resident state layout measured from this handler's accesses. */
typedef struct {
    char p0[0xBF8];
    int field_BF8;
    char p1[0x1230 - 0xBFC];
    int field_1230;
    char p2[0x1240 - 0x1234];
    int field_1240;
    char p3[0x1450 - 0x1244];
    int field_1450;
    char p4[0x2294 - 0x1454];
    int field_2294;
    char p5[0x22BC - 0x2298];
    unsigned char field_22BC;
    char p6[0x2534 - 0x22BD];
    int field_2534;
} HeroState;
extern HeroState D_00189E20;

extern char D_00138180[];
extern void func_0029FCC0(char *, int, void *), func_002FDF40(void *, void *, float, float, float, float, int, int);
extern int func_002FE5A0(void *, void *, void *, void *, char *, int, int, float);
extern int func_00282948(void *), func_L00_002D3F30(int, int);
extern void func_L00_002AF568(void), func_002E5CF8(int, int, char *), func_L00_002AF7D0(void), ref_L00_003EAA58_00(void *, char *);
extern char *func_L00_00387CA8(void *, void *);
/* Moby update: Miniturret Glove (class 3162). */
void func_L00_003EAA58(char *self)
{
    char a[16], b[16];
    char *bp;
    char *st = *(char **)(self + 0x68);
    int ready;
    float scale;
    char *shot;
    func_0029FCC0(self, 0, a);
    bp = b;
    scale  =  D_00189E20.field_2294 == 29 ? 11.0f : 4.5f;
    func_002FDF40(bp, a, 1.5f, scale, 0.25f, 0.003055555745959282f, 0, 0);
    *(int *)(st + 0x24) = func_002FE5A0(a, bp, st, st + 0x10, self, 0, 0, 0.003055555745959282f);
    ready = 1;
    if (D_00189E20.field_2294 == 29) {
        if (!func_00282948(&D_00189E20.field_2534)) ready = 0;
    } else D_00189E20.field_2534 = 40;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        self[0x20] = 1;
        *(int *)(st + 0x24) = 0;
        /* Fall through. */
    case 1:
        if ((*(int *)(D_00138180 + 0x1A4) & D_00189E20.field_1230) &&
            !D_00189E20.field_22BC && ready) {
            if (func_L00_002D3F30(-1, 1)) {
                func_L00_002AF568();
                self[0x20] = 2;
                *(int *)(st + 0x20) = 20;
            } else func_002E5CF8(2, 0, self);
        }
        break;
    case 2:
        if (func_00282948(st + 0x20)) {
            func_002E5CF8(0, 0, self);
            shot = func_L00_00387CA8(a, bp);
            *(char **)(shot + 0xB8) = self;
            func_L00_002AF7D0();
            self[0x20] = 3;
            *(int *)(st + 0x20) = 10;
        }
        break;
    case 3:
        if (func_00282948(st + 0x20)) self[0x20] = 1;
        break;
    }
    ref_L00_003EAA58_00(func_L00_003EAC88, self);
}
