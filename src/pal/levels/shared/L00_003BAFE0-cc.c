/* func_PAL_L00_003BAFE0, the PAL copy of func_L00_003B74A8: the same C, where expr 0.016666668f becomes 0.020000001f; scale func_002A7820(D_L00_001AFB5C[1], D_L00_001AFB5C[2]); wrap func_002A7820(D_L00_001AFB58, D_L00_001AFB5C[0]) (((int. */

extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002A7A00(float *, float, float);
extern void *func_002C3150(void *, void *, int, int, int, int, float);
extern float D_L00_001AFB30 __attribute__((sda));
extern float D_L00_001AFB34;
extern float D_L00_001AFB40 __attribute__((sda));
extern float D_L00_001AFB44;
extern int D_L00_001AFB48[2][2] __attribute__((sda));
extern int D_L00_001AFB58 __attribute__((sda));
extern int D_L00_001AFB5C[] __attribute__((sda));

void func_PAL_L00_003BAFE0(char *object, void *position)
{
    float velocity[4];
    void *first = *(void **)(object + 0x68);
    unsigned char kind = (((int)(func_002A7820(D_L00_001AFB58, D_L00_001AFB5C[0])) * 5 + 2) / 6);
    int *color = &D_L00_001AFB48[(unsigned char)object[0xbc]][0];
    int *color2;
    unsigned char random = func_002A77E0(255);
    func_002C3150(position, first, *color, kind, random, 0, D_L00_001AFB40);
    func_002A7A00(velocity, D_L00_001AFB30 * (0.020000001f), D_L00_001AFB34 * (0.020000001f));
    kind = (((int)(func_002A7820(D_L00_001AFB5C[1], D_L00_001AFB5C[2])) * 5 + 2) / 6);
    color2 = (int *)((char *)D_L00_001AFB48 + (((unsigned char)object[0xbc] << 3) | 4));
    random = func_002A77E0(255);
    func_002C3150(position, velocity, *color2, kind, random, 0, D_L00_001AFB44);
}
