#include "include_asm.h"

#include "common.h"
extern void func_002B60B0(char *, float, float, float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A0F68(char *);
extern void func_002A0488(char *, int, int, int);
extern void func_L11_003973F8(char *, int, float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_002A0F68(char *);
extern void func_002A7750(void *, int, int);

void func_PAL_L11_0043BE90(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    unsigned short flags;
    char *definition;
    int cache;

    *(short *)(state + 0x282) = 0;
    *(short *)(state + 0x88) = 0;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x286) = active;
    func_002B60B0(object, 0.0064000003f, 0.16000001f,
                  0.010053098f, 0.25132746f);
    flags = *(unsigned short *)(object + 0x34);
    definition = *(char **)(object + 0x24);
    cache = *(int *)(definition + 0x10);
    *(unsigned short *)(object + 0x34) = (flags | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = cache;
    *(unsigned char *)(object + 0x7F) = 0;
    if (*(short *)(state + 0x286) != 0) {
        func_002A7750(object, 7, 3);
        *(unsigned short *)(object + 0x34) |= 0x100;
        func_PAL_002A7E68(object, 1, 0, 0);
        func_PAL_002A0F68(object);
        func_L11_003973F8(object, 0, 2.0f, 2.0f);
    } else {
        func_002A7750(object, 3, 0);
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned short *)(object + 0x34) &= 0xFEFE;
    }
    *(unsigned char *)(state + 0x2E) = 1;
    *(short *)(state + 0x284) = mode;
    *(unsigned char *)(state + 0x6A) = 0;
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_002A0488(object, *(unsigned char *)(state + 0x54),
                      *(unsigned char *)(state + 0x55), *(unsigned char *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}
