
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));


struct SpawnHeader {
    u8 unknown000[0x20];
    u8 mode;
    u8 unknown021[11];
    f32 rate;
    u8 flags, unknown031;
    u16 kind;
};

extern char *func_0029EFD0(int);

extern void func_002A0F48(void *);

char *func_L02_00401530(TI128 *a0, TI128 *a1, TI128 *a2, unsigned char a3,
                        unsigned char a4, unsigned char a5, float a6, float a7, float a8) {
    char *s0;
    char *v1;
    struct SpawnHeader *header;

    s0 = func_0029EFD0(0xB5A);
    if (s0 == 0)
        goto end;
    qcopy(s0 + 0x10, a0);
    header = (struct SpawnHeader *)s0;
    header->rate = 0.014999999664723873f;
    header->kind = 0xFF;
    header->flags = 0xFF;
    header->mode = 0;
    v1 = *(char **)(s0 + 0x68);
    qcopy(v1, a1);
    qcopy(v1 + 0x10, a2);
    *(int *)(v1 + 0x70) = 0x10E;
    *(unsigned char *)(v1 + 0x75) = a3;
    *(unsigned char *)(v1 + 0x76) = a4;
    *(unsigned char *)(v1 + 0x77) = a5;
    *(float *)(v1 + 0x68) = a7;
    *(float *)(v1 + 0x6C) = a6;
    *(float *)(v1 + 0x64) = a8;
    func_002A0F48(s0);
end:
    return s0;
}
