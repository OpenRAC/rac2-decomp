#include "include_asm.h"

typedef int Quad_0031D3E0 __attribute__((mode(TI)));
extern int D_L00_001B1DC0 __attribute__((sda));
extern void func_00282F20(void *dst, void *src, float scale);
extern char *func_0029EFD0(int kind);
extern int func_002FED90(void *object, void *position, float x, float y, float z);
extern void func_002A0F48(void *object);

/* Initialize a kind-0xA82 object and its private record. */
char *func_PAL_0031E9F8(void *position, void *direction,
                  float value60, float value68, float value70, float value74,
                  unsigned char color0, unsigned char color1,
                  unsigned char color2, unsigned char color3,
                  unsigned short flags, void *owner)
{
    char *object;
    char *data;
    unsigned int initial;

    if (D_L00_001B1DC0 < 17)
        return 0;
    object = func_0029EFD0(0xA82);
    if (object != 0) {
        data = *(char **)(object + 0x68);
        *(Quad_0031D3E0 *)(object + 0x10) = *(Quad_0031D3E0 *)position;
        func_00282F20(data, direction, value60 * 0.020000001f);
        initial = 255;
        object[0x20] = 0;
        *(short *)(object + 0x32) = initial;
        *(unsigned char *)(object + 0x30) = initial;
        *(void **)(data + 0x50) = owner;
        *(int *)(data + 0x54) = 0;
        *(float *)(object + 0x2C) = 0.015f;
        *(unsigned short *)(object + 0x34) |= 0x100;
        *(float *)(data + 0x60) = value60;
        *(float *)(data + 0x68) = value68;
        *(float *)(data + 0x70) = value70;
        data[0x78] = color0;
        data[0x79] = color1;
        data[0x7A] = color2;
        data[0x7B] = color3;
        *(float *)(data + 0x74) = value74;
        *(int *)(data + 0x5C) = 0;
        *(unsigned short *)(data + 0x7E) = flags;
        *(int *)(data + 0x58) = 0;
        if (owner == 0)
            data[0x7C] = 1;
        else
            data[0x7C] = 0;
        *(short *)(data + 0x6E) = func_002FED90(object, 0, 1.0f, 1.0f, 1.0f);
        func_002A0F48(object);
    }
    return object;
}
