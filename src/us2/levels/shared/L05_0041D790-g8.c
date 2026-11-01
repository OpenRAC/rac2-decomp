#include "include_asm.h"

#include "common.h"
typedef struct { int bolts; int counter; u8 suffix[0x38]; } PlayerStatBlock;
extern PlayerStatBlock D_001A79F8 __attribute__((sda));
extern int D_L05_001B1300 __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern unsigned short D_0018D030 __attribute__((nosda));
extern float func_00282E48(void *, void *);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern float func_00283B98(float, float);
extern int func_002E5DA0(int, int, char *, int);
extern void func_0029F338(void *);
extern void func_L05_0041C4E8(char *);
extern int func_US2_00289840(int, int);
extern int func_00288FB8(int);
extern void func_US2_L00_0030EFB8(int, int);

/* Flies the object at the cached class-0xFBF moby. On arrival it plays a sound, bumps the
   player-stat counter and deletes itself; until then it keeps turning. */
void func_US2_L05_0041D790(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001B1300 != 0) {
        scale = func_00282E48((void *)(D_L05_001B1300 + 0x10), object + 0x10);

        if (D_001A79F0[0] == 0x14) {
            func_002AA458(object + 0x10, (void *)(D_L05_001B1300 + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
        } else if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            func_002AA458(object + 0x10, (void *)(D_L05_001B1300 + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
        if (scale < 0.5f) {
            if (D_001A79F8.counter == 0) {
                if (D_0018D030 == 0 && D_001A79F0[0] == 0x19)
                    func_US2_00289840(0xA3B, 0x92);
            } else {
                func_US2_L00_0030EFB8(func_00288FB8(0x1282), -1);
            }
            func_002E5DA0(0xC, 0, object, 0xFBF);
            D_001A79F8.counter = D_001A79F8.counter + 1;
            func_0029F338(object);
            return;
        }
    }
    func_L05_0041C4E8(object);
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.03f);
    *(float *)(object + 0xF0) = func_00283B98(*(float *)(object + 0xF0), 0.01f);
}
