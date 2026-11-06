/* func_PAL_L02_00426700, the PAL copy of func_L02_004216F0: the same C, where scale func_00283CF0(D_L02_001B1FA4 / t). */

/* func_PAL_L02_00426700 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it;
   -g gives the two nops retail has before its `div.s` (a -g unit's line labels). */

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));

extern void *func_0029EFD0(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern void func_L02_004224C8(u8 *);
extern int func_002E5CF8(int, int, void *);
extern char D_0018A0E0[];
extern float D_L02_001B1F98 __attribute__((sda));
extern float D_L02_001B1FA0 __attribute__((sda));
extern float D_L02_001B1FA4 __attribute__((sda));

u8 *func_PAL_L02_00426700(u8 *a0, int a1, u8 *a2, float a3) {
    u8 *obj = func_0029EFD0(0xD08);
    u8 *v;
    int n;
    float t;

    if (obj != 0) {
        *(u8 *)(obj + 0x20) = 0;
        *(u8 *)(obj + 0x30) = 0xFF;
        t = D_L02_001B1FA0 * 0.020000001f;
        v = *(u8 **)(obj + 0x68);
        *(float *)(v + 0x64) = a3;
        func_00282F20(v + 0x40, a2, t);
        *(TI128 *)(obj + 0x10) = *(TI128 *)a0;
        *(TI128 *)(obj + 0xC0) = *(TI128 *)(v + 0x40);
        func_00282DD8(obj + 0xD0, obj + 0xC0, D_0018A0E0);
        func_00282F20(obj + 0xD0, obj + 0xD0, -1.0f);
        func_00282DD8(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        t = D_L02_001B1FA0 * 0.020000001f;
        n = (((int)(func_00283CF0(D_L02_001B1FA4 / t)) * 5 + 2) / 6);
        *(int *)(v + 0x58) = n;
        *(float *)(v + 0x5C) = 1.0f / func_00283CE0(n);
        *(int *)(v + 0x50) = a1;
        *(u8 *)(obj + 0x20) = 0;
        *(float *)(v + 0x60) = D_L02_001B1F98;
        func_L02_004224C8(obj);
        func_002E5CF8(1, 0, obj);
    }
    return obj;
}
