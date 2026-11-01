#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;
extern char *D_L20_001B2F9C __attribute__((sda));
extern void func_002A7750(char *, int, int);
extern float func_00283BE0(float, float);
extern void func_00282CC0(char *, char *, char *);
extern unsigned char D_0019B2E8[];
extern float func_002AA548(char *, char *, float, float, float, float);
extern int D_001A79F0 __attribute__((sda));
extern void func_PAL_L09_003EF588(char *);
extern void func_00282F20(void *, void *, float);
extern int func_002B38B8(char *);
extern int func_002B3868(char *);
extern int func_002E5CF8(int, int, char *);
extern void func_L20_004450D8(char *);
extern void *jtbl_002B5940[];

void func_PAL_L20_0044A780(char *obj) {
    /* Keep all eight destinations represented by the level's dispatch table. */
    static void *volatile states[] = {
        &&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7
    };
    Vec4 v, w;
    unsigned int sel;
    char *state = *(char **)(obj + 0x68);
    char *target = D_L20_001B2F9C + (*(int *)state << 8);

    sel = *(unsigned char *)(obj + 0x20);
    if (sel >= 8) goto c7;
    goto *jtbl_002B5940[sel];
    c0:
        if (*(int *)(state + 8)>=0) *(char **)(state + 0x10)=(char *)(D_L20_001B2F9C+(*(int *)(state + 8)<<8));
        else *(char **)(state + 0x10)=0;
        func_002A7750(obj, 1, -1); goto c7;
    c1:
        if (func_002B38B8(target)) {
            func_002E5CF8(0, 0, obj);
            func_002A7750(obj, 2, -1);
        }
        if (D_0019B2E8[(unsigned char)obj[0xB0]+D_001A79F0*16]&0x80) {
            *(float *)(obj + 0xF0)=func_00283BE0(*(float *)(obj + 0xF0), 1.5707965f);
            func_002A7750(obj, 6, -1);
        }
        goto c7;
    c2:
        func_002AA548(obj + 0xF0, state + 4, -1.5707965f, 0.000767945f, 251.32744f, 349.06592f);
        if (*(float *)(obj + 0xF0)<=-0.785398245f) {
            char *other=*(char **)(state + 0x10);
            if (other && *(short *)(other + 0xAA)==0xCBC && (unsigned char)other[0x20]!=0xFE && (unsigned char)other[0x20]!=0xFD)
                func_PAL_L09_003EF588(other);
        }
        if (*(float *)(obj + 0xF0)<=-1.5707965f) { *(int *)(state + 4)=0; func_002A7750(obj, 3, -1); func_002E5CF8(1, 0, obj); }
        goto c7;
    c3:
        func_002AA548(obj + 0xF0, state + 4, -1.308997f, 0.025132746f, 0.00062831864f, 1.0471977f);
        if (*(float *)(obj + 0xF0)>=-1.308997f) { *(int *)(state + 4)=0; func_002A7750(obj, 4, -1); }
        goto c7;
    c4:
        func_002AA548(obj + 0xF0, state + 4, -1.5707965f, 0.00062831864f, 0.25132746f, 3.4906592f);
        if (*(float *)(obj + 0xF0)<=-1.5707965f) { *(int *)(state + 4)=0; func_002A7750(obj, 5, -1); func_002E5CF8(1, 0, obj); }
        goto c7;
    c5:
        func_002AA548(obj + 0xF0, state + 4, -1.48353f, 0.025132746f, 0.00062831864f, 1.0471977f);
        if (*(float *)(obj + 0xF0)>=-1.48353f) { *(int *)(state + 4)=0; func_002A7750(obj, 6, -1); }
        goto c7;
    c6:
        if (func_002B3868(obj)) func_L20_004450D8(obj);
        func_002AA548(obj + 0xF0, state + 4, -1.5707965f, 0.00062831864f, 0.25132746f, 3.4906592f);
        if (*(float *)(obj + 0xF0)<=-1.5707965f) { *(int *)(state + 4)=0; func_002A7750(obj, 7, -1); func_002E5CF8(1, 0, obj); }
        goto c7;
    c7:
    {
        char *pos = target + 0x10;

        qcopy(pos, obj + 0x10);
        func_00282F20(&v, obj + 0xE0, 5.7f);
        func_00282CC0(pos, pos, (char *)&v);
        func_00282F20(&w, obj + 0xD0, 0.35f);
        func_00282CC0(pos, pos, (char *)&w);
    }
}

