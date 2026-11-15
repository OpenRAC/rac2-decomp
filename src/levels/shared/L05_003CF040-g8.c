#include "common.h"
extern void func_L05_003CF9C8(char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float D_L05_001AFBE4 __attribute__((sda));
extern float D_L05_001AFB68[1] __attribute__((sda));
extern int func_002829D8(void *);
extern void func_0029F338(char *);
extern float func_00282C48(float);
extern int func_L05_003CFC28(int);
extern float func_00283B98(float, float);
extern void func_L05_003CFAB8(char *);
extern int func_L05_003CF350(char *);
extern int func_002E5DA0(int, int, char *, int);
extern int D_001A79F0;
extern unsigned char D_00139619[1] NOT_SDA;
extern void func_L05_003CFCF0(char *, int, int);
/* Moves a flying debris piece, slows it down, and removes it when it hits something or leaves
   the world. */
void func_L05_003CF040(unsigned char *obj)
{
    char *s = *(char **)(obj + 0x68);
    int kind;
    switch ((unsigned char)obj[0x20]) {
    case 0:
        obj[0x20] = 1;
        RandomizeObjectReachAndAngles(obj);
    case 2:
    case 3:
        FastVecAdd(obj + 0x10, obj + 0x10, s + 0x10);
        FastVecScale(s + 0x10, s + 0x10, (D_L05_001AFBE4 - 1.0f) + 1.0f);
        if ((unsigned char)obj[0x20] != 2) {
            if (FastVectorHelperB(s + 0xC) && (unsigned char)obj[0x31] == 0) {
                MarkMobySpawned(obj);
                return;
            }
        } else {
            if (FloatAbs(*(float *)(s + 0x10)) < 0.01f &&
                FloatAbs(*(float *)(s + 0x14)) < 0.01f &&
                FloatAbs(*(float *)(s + 0x18)) < 0.01f)
                obj[0x20] = 1;
        }
    case 1:
        kind = ClassIdToTableIndex(*(short *)(obj + 0xAA));
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * D_L05_001AFB68[kind];
        *(float *)(obj + 0xF0) = FastAddRotations(*(float *)s, *(float *)(obj + 0xF0));
        *(float *)(obj + 0xF4) = FastAddRotations(*(float *)(s + 4), *(float *)(obj + 0xF4));
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(s + 8), *(float *)(obj + 0xF8));
        ShakeCameraIfObjectNear(obj);
        if (func_L05_003CF350(obj) || *(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
            *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
            *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
            if (D_L05_001AFB68[kind] >= 5.0f) {
                PlaySoundFromClassBank(0, 0, obj, 0x956);
                if (gCurrentMapIndex == 5 && D_00139619[0] == 0)
                    func_L05_003CFCF0(obj, 1, 5);
                else
                    func_L05_003CFCF0(obj, 0, 5);
            } else {
                if (*(short *)(obj + 0xAA) == 0x954) PlaySoundFromClassBank(0, 0, obj, 0x954);
                if (*(short *)(obj + 0xAA) == 0x955) PlaySoundFromClassBank(0, 0, obj, 0x955);
            }
            MarkMobySpawned(obj);
        }
        break;
    }
}
