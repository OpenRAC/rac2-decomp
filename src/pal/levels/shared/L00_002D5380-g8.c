/* func_PAL_L00_002D5380, the PAL copy of func_L00_002D4E58: the same C with the callees are PAL's
   func_PAL_L00_002D52C0 and func_PAL_L00_002D5150. */
#include "common.h"

typedef struct {
    unsigned char pad0;
    unsigned char initialized;
    unsigned char pad2[0x20 - 2];
    float scale[3];
    unsigned char pad2C[0x40 - 0x2C];
} Manipulator4E58;

extern unsigned char D_001A7A40[] __attribute__((sda));
extern float D_L00_001A7CF4 __attribute__((sda));
extern float D_L00_001A7CF8 __attribute__((sda));
extern Manipulator4E58 D_L00_001B16D0 __attribute__((sda));
extern Manipulator4E58 D_L00_001B2D80[];
extern int D_0018B090[];
extern void func_0029F978(char *, int, Manipulator4E58 *);
extern void func_PAL_L00_002D52C0(char *);
extern void func_PAL_L00_002D5150(char *);

/* Sets the two option-dependent scales, attaches manipulator 24 to the object (scaled 0.92, or
   0.97 of the first scale and the first scale itself) unless object kind 0xF6B, then either
   runs the one-shot spawn or attaches manipulators 22 and 23 at scale 0.01 and runs
   func_PAL_L00_002D5150. */
void func_PAL_L00_002D5380(char *object, int spawn)
{
    Manipulator4E58 *record;
    int i;

    if (D_001A7A40[1])
        D_L00_001A7CF4 = 1.57f;
    else
        D_L00_001A7CF4 = 0.875f;
    if (D_001A7A40[3])
        D_L00_001A7CF8 = 1.8f;
    else
        D_L00_001A7CF8 = 1.0f;
    if (D_L00_001B16D0.initialized == 0) {
        func_0029F978(object, 24, &D_L00_001B16D0);
        if (*(short *)(object + 0xAA) == 0xF6B) {
            D_L00_001B16D0.scale[0] = 0.92f;
            D_L00_001B16D0.scale[1] = 0.92f;
            D_L00_001B16D0.scale[2] = 0.92f;
        } else {
            D_L00_001B16D0.scale[0] = D_L00_001A7CF4 * 0.97f;
            D_L00_001B16D0.scale[1] = D_L00_001A7CF4 * 0.97f;
            D_L00_001B16D0.scale[2] = D_L00_001A7CF4;
        }
    }
    if (*(short *)(object + 0xAA) == 0xF6B)
        return;
    if (spawn) {
        func_PAL_L00_002D52C0(object);
        return;
    }
    if (D_0018B090[0]) {
        record = D_L00_001B2D80;
        for (i = 0; i < 2; i++, record++) {
            if (record->initialized == 0) {
                func_0029F978(object, i + 22, record);
                record->scale[0] = 0.01f;
                record->scale[1] = 0.01f;
                record->scale[2] = 0.01f;
            }
        }
    }
    func_PAL_L00_002D5150(object);
}
