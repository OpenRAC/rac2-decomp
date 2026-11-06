#include "include_asm.h"
#include "common.h"

/* func_US2_L10_00318158, the v2.00 copy of func_L10_00317528, written as its Feltzin sibling
   func_US2_L05_00315A58: the same C, with a new test of D_001A79F0 against 0x33 before the
   class 0xFA0 update. class_id holds its constant before the load, so loop.c's lifetime test
   hoists it in the first pass, ahead of the array giv. */

extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002FC980(void);
extern void func_US2_002E72D8(char *);
extern void func_L00_00326048(char *, char *, int, int, float);
extern void func_00283AF0(char *, char *);
extern void func_00283958(char *, char *);
extern void func_L01_0031A278(char *, char *, float, float, float);
extern void func_L05_00424990(char *, int, int, int, int, int, int, int, int, int, int, float);
extern int func_002A77E0(int kind);
extern float func_002A78D8(float, float);
extern char *func_L05_00419CC8(char *, char *, char *, int, int, int, int, int, float);

typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap[0xC];
    short count;
    char gap2[0x146];
    char *objects[3];
} Scene10;
extern Scene10 D_L10_001BD380;
extern char D_L10_00296F00[];
extern int D_001A79F0 __attribute__((sda));

void func_US2_L10_00318158(void)
{
    float pos[4] __attribute__((aligned(16)));
    union {
        float matrix[12];
        struct { float dest[4], delta[4]; } vectors;
    } scratch __attribute__((aligned(16)));
    int i;
    char *obj;
    func_L00_002FC980();
    for (i = 0; i < D_L10_001BD380.count; i++) {
        char *current = D_L10_001BD380.objects[i];
        if (current && *(short *)(current + 0xAA) == 0xE29)
            *(unsigned short *)(current + 0x34) |= 0x800;
        if (*(short *)(current + 0xAA) == 0xD54) func_US2_002E72D8(current);
        if (current) {
            int class_id = 0xFA0;
            if (*(short *)(current + 0xAA) == class_id && D_001A79F0 != 0x33) {
                char *state = *(char **)(current + 0x68);
                if (state) func_L00_00326048(current, state + 0xC, 0x80AAAAD2, 0x80396464, 0.06108653545379639f);
            }
        }
    }
    if (D_001A79F0 != 10 || D_L10_001BD380.mode) return;
    obj = D_L10_001BD380.objects[2];
    if (D_L10_001BD380.timer == 0x195) {
        func_00283AF0(*(char **)(obj + 0x58) + 0x10, (char *)scratch.matrix);
        func_00283958((char *)scratch.matrix, obj + 0xC0);
        func_L01_0031A278(obj, (char *)pos, 4.0f, 3.0f, 5.0f);
        func_L05_00424990((char *)pos, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 1.5f);
        func_L01_0031A278(obj, (char *)pos, 9.0f, 4.0f, 4.0f);
        func_L05_00424990((char *)pos, 35, 50, 30, 30, 30, 50, 1, 1, 1, 1, 1.0f);
    }
    if (((unsigned int)(D_L10_001BD380.timer - 0x187) < 0x79 || D_L10_001BD380.timer >= 0x327) && !func_002A77E0(4)) {
        float sign = 1.0f;
        float *entry;
        if (func_002A77E0(2)) sign = -1.0f;
        entry = (float *)(D_L10_00296F00 + func_002A77E0(3) * 32);
        func_L01_0031A278(obj, (char *)pos, entry[0], entry[1], entry[2]);
        func_L01_0031A278(obj, (char *)scratch.vectors.dest, entry[4], entry[5], entry[6]);
        scratch.vectors.dest[0] += func_002A78D8(0.5f, 1.5f);
        scratch.vectors.dest[1] += func_002A78D8(0.5f, 1.5f);
        scratch.vectors.dest[2] += func_002A78D8(0.5f, 1.5f);
        func_00282CF0((char *)scratch.vectors.delta, (char *)scratch.vectors.dest, (char *)pos);
        func_00282F20((char *)scratch.vectors.delta, (char *)scratch.vectors.delta, 1.1666667461395264f);
        func_L05_00419CC8(obj, (char *)pos, (char *)scratch.vectors.delta, 0x46BE20, 0x327814, 1, 0, 1, sign);
    }
}


