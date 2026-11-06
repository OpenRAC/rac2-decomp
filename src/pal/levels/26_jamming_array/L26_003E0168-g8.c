/* func_PAL_L26_003E0168, the PAL copy of func_L26_003DBE18: the same C, where the two tuning
   words are read as ints and scaled to 50 Hz before they go to the halfwords at 0x1E2 and 0x1E4. */
#include "common.h"

extern float D_L26_001B05D8 __attribute__((sda));
extern int D_L26_001B05E0 __attribute__((sda));
extern int D_L26_001B05E4;
extern float D_L26_001B8B80[4];
extern float func_002B0360(char *);
extern int func_002A77E0(int);
extern void func_00325B70(char *, char **, int, int);
extern void func_002A7750(unsigned char *, unsigned char, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L26_003DC128(void *);
extern int func_002B3BA8(void *, int, void *, int, float, float);
extern void func_00283698(void *, void *);
extern void func_002AFFD8(char *, char *, int);
extern void func_00325D30(char *, char *);

int func_PAL_L26_003E0168(unsigned char *object) {
    char *private = *(char **)(object + 0x68);
    float height;
    float turn;
    if (object[0x20] == 0) {
        *(int *)(private + 0x98) = 3;
        *(float *)(private + 0x80) = 1.0f;
        private[0x60] = 7;
        *(float *)(private + 0x84) = 0.8f;
        *(float *)(private + 0x8C) = 0.15f;
        height = func_002B0360((char *)object + 0x10) - 1.5f;
        turn = D_L26_001B05D8;
        *(float *)(private + 0x100) = 1.0f;
        turn *= 0.017453294f;
        *(float *)(private + 0x90) = height;
        *(float *)(private + 0x104) = 0.5f;
        {
            int flip = func_002A77E0(2);
            float angle = turn;
            if (flip) angle = -angle;
            *(float *)(private + 0x1DC) = angle;
        }
        *(unsigned short *)(private + 0x1E2) = ((s32)(D_L26_001B05E0) * 5 + 2) / 6;
        *(unsigned short *)(private + 0x1E4) = ((s32)(D_L26_001B05E4) * 5 + 2) / 6;
        private[0x2E] = 1;
        *(unsigned short *)(object + 0x34) |= 0x100;
        if (*(float *)(private + 0x20) == 0.0f) {
            *(short *)(private + 0x24) = 3;
            *(float *)(private + 0x20) = 3.0f;
        }
        func_00325B70((char *)object, (char **)(private + 0x270), 0, 2);
        func_002A7750(object, 1, 0);
        if (object[0x43]) func_PAL_002A7E68(object, 0, 0, 0);
    }
    if (object[0x31] && func_00282E48(object + 0x10, D_L26_001B8B80) < 24.0f) {
        func_002A93B0(object);
        object[0x6F] = 0x16;
    }
    if (func_002B0ED8(object, private + 0x50, 0)) func_L26_003DC128(object);
    *(short *)(private + 0x224) = func_002B3BA8(object, *(int *)(private + 0x210), 0, 0, 16.0f, 0.0f);
    func_00283698(private + 0x230, object + 0xC0);
    func_002AFFD8((char *)object + 0x10, private + 0x260, 0);
    if ((unsigned char)private[0x2E] == 2) {
        func_00325D30((char *)object, private + 0x270);
        return 1;
    }
    return 0;
}
