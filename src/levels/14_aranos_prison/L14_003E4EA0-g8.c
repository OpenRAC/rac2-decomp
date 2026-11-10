/* func_L14_003E4EA0 is a unit of its own: it reads four float constants through $gp (hence
   -g8), and it is built with -g, whose line label in front of the `mul.s` before the second
   division makes the assembler pad that `div.s` with retail's `nop` (the division-floor class
   of docs/build/compiler-notes.md, as in func_L23_004160B0). func_00282C48 is `fabs`. The state
   block is read as a halfword key table at +0x00, with the current position at +0x14 and the
   current key index at +0x16: the span runs from the key to the previous one (index != 0), or
   to one of three words (index == 0). Computing both results before the two stores gives
   retail's store order. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef int s32;

extern float D_L14_001B05C8 __attribute__((sda));
extern float D_L14_001B05CC __attribute__((sda));
extern float D_L14_001B05C0 __attribute__((sda));
extern float D_L14_001B05C4 __attribute__((sda));
extern float func_00282C48(float);

void func_L14_003E4EA0(char *self)
{
    char *s0 = *(char **)(self + 0x68);
    char *t = *(char **)(s0 + 0x30);
    char *s1;
    int a1;
    int v1;
    u16 a0;
    u16 a2;
    float k0;
    float d;
    float r1;
    float r2;
    float u;
    float out0;
    float out1;

    if (t == 0)
        return;
    s1 = *(char **)(t + 0x68);
    a2 = *(u16 *)(s0 + 0x16);
    if (*(s16 *)(s0 + 0x16) == 0) {
        v1 = *(int *)(s0 + 0x34);
        if (v1 > 0) {
            a1 = v1;
            a0 = *(u16 *)(s0 + 0x14);
        } else if (*(int *)(s0 + 0x38) >= 0) {
            a0 = *(u16 *)(s0 + 0x14);
            a1 = *(int *)(*(char **)(*(char **)(s0 + 0x3C) + 0x68) + 0x34);
        } else {
            a1 = *(s16 *)(s0 + 0x14);
            a0 = *(u16 *)(s0 + 0x14);
        }
    } else {
        a0 = *(u16 *)(s0 + 0x14);
        a1 = *(s16 *)(s0 + *(s16 *)(s0 + 0x16) * 2 - 2);
    }
    k0 = (float)*(s16 *)(s0 + (s16)a2 * 2);
    d = (float)(a1 - *(s16 *)(s0 + (s16)a2 * 2));
    r1 = func_00282C48((D_L14_001B05C8 - 1.0f) - (D_L14_001B05C8 + D_L14_001B05C8 - 2.0f) * ((float)(s16)a0 - k0) / d);
    u = D_L14_001B05C8 - r1;
    r2 = func_00282C48((D_L14_001B05CC - 1.0f) - (D_L14_001B05CC + D_L14_001B05CC - 2.0f) * ((float)*(s16 *)(s0 + 0x14) - k0) / d);
    out0 = u * D_L14_001B05C0;
    out1 = (D_L14_001B05CC - r2) * D_L14_001B05C4;
    *(float *)(s1 + 0x40) = out0;
    *(float *)(s1 + 0x44) = out1;
}
