/* func_PAL_L14_003E92D8, the PAL copy of func_L14_003E4EA0: the same C, where both ends of the
   span are key positions scaled to 50 Hz and the current position stays unscaled. A unit of its
   own: it reads four float constants through $gp (hence -g8), and it is built with -g, whose line
   label in front of the `mul.s` before the second division makes the assembler pad that `div.s`
   with retail's `nop` (the division-floor class of docs/build/compiler-notes.md, as in
   func_L23_004160B0). func_00282C48 is `fabs`. The state block is read as a halfword key table at
   +0x00, with the current position at +0x14 and the current key index at +0x16: the span runs
   from the key to the previous one (index != 0), or to one of three words (index == 0). `raw`
   serves two blocks, as the far object's state pointer and as the unscaled key: retail allocates
   it as one multi-block variable. Computing both results before the two stores gives retail's
   store order. */

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

void func_PAL_L14_003E92D8(char *self)
{
    char *state = *(char **)(self + 0x68);
    char *target = *(char **)(state + 0x30);
    char *out;
    int end;
    int word;
    int key;
    int raw;
    u16 pos;
    u16 index;
    float start;
    float span;
    float r1;
    float r2;
    float u;
    float out0;
    float out1;

    if (target == 0)
        return;
    out = *(char **)(target + 0x68);
    index = *(u16 *)(state + 0x16);
    if (*(s16 *)(state + 0x16) == 0) {
        word = *(int *)(state + 0x34);
        if (word > 0) {
            end = (word * 5 + 2) / 6;
            pos = *(u16 *)(state + 0x14);
        } else if (*(int *)(state + 0x38) >= 0) {
            raw = *(int *)(*(char **)(state + 0x3C) + 0x68);
            pos = *(u16 *)(state + 0x14);
            end = (*(int *)(raw + 0x34) * 5 + 2) / 6;
        } else {
            end = (*(s16 *)(state + 0x14) * 5 + 2) / 6;
            pos = *(u16 *)(state + 0x14);
        }
    } else {
        end = (*(s16 *)(state + *(s16 *)(state + 0x16) * 2 - 2) * 5 + 2) / 6;
        pos = *(u16 *)(state + 0x14);
    }
    raw = *(s16 *)(state + (s16)index * 2);
    key = (raw * 5 + 2) / 6;
    start = (float)key;
    span = (float)(end - key);
    r1 = func_00282C48((D_L14_001B05C8 - 1.0f) - (D_L14_001B05C8 + D_L14_001B05C8 - 2.0f) * ((float)(s16)pos - start) / span);
    u = D_L14_001B05C8 - r1;
    r2 = func_00282C48((D_L14_001B05CC - 1.0f) - (D_L14_001B05CC + D_L14_001B05CC - 2.0f) * ((float)*(s16 *)(state + 0x14) - start) / span);
    out0 = u * D_L14_001B05C0;
    out1 = (D_L14_001B05CC - r2) * D_L14_001B05C4;
    *(float *)(out + 0x40) = out0;
    *(float *)(out + 0x44) = out1;
}
