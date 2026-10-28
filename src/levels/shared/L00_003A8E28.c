#include "include_asm.h"

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

extern void func_3251D0();

extern int func_31E7A8();

extern float func_2EE238();

extern void func_2EE178(void *, void *, float);

extern void func_2EE108();

extern void func_2EE138();

extern void func_2EE3D0(void *, void *, float);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


INCLUDE_ASM("asm/levels", func_L00_003A91A0);


INCLUDE_ASM("asm/levels", func_L00_003A98E8);

INCLUDE_ASM("asm/levels", func_L00_003A9C58);

INCLUDE_ASM("asm/levels", func_L00_003AA4C8);

INCLUDE_ASM("asm/levels", func_L00_003AA708);

INCLUDE_ASM("asm/levels", func_L00_003AB388);

/* Applies a state record to a 3D point when the record carries a live tag. */
void func_L00_003AB618(char *a0, char *a1, char *a2)
{
    if (a2 != 0) {
        unsigned char t = *(unsigned char *)(a2 + 0x20);

        if (t != 0xFE)
            if (t != 0xFD) {
                char b0[16];
                char b1[16];
                char b2[16];
                float f;

                func_3251D0(a0, b0, 1);
                f = *(float *)(func_31E7A8(a2) + 0x10);
                func_2EE178(b1, b0, f);
                func_2EE108(b2, a2 + 0x10, b1);
                f = func_2EE238(a1);
                func_2EE138(a1, b2, a0);
                func_2EE3D0(a1, a1, f);
            }
    }
}

INCLUDE_ASM("asm/levels", func_L00_003AB6F0);


INCLUDE_ASM("asm/levels", func_L00_003AB8B8);

INCLUDE_ASM("asm/levels", func_L00_003AB9C0);

INCLUDE_ASM("asm/levels", func_L00_003ABEC0);


INCLUDE_ASM("asm/levels", func_L00_003ACA60);

/* func_L00_003ACC88 is defined in L00_003A8E28-g8.c (the scale is read through $gp). */


INCLUDE_ASM("asm/levels", func_L00_003AD7C8);

INCLUDE_ASM("asm/levels", func_L00_003ADA30);

INCLUDE_ASM("asm/levels", func_L00_003ADCD8);


INCLUDE_ASM("asm/levels", func_L00_003ADEA0);

INCLUDE_ASM("asm/levels", func_L00_003AE550);

INCLUDE_ASM("asm/levels", func_L00_003AE900);

INCLUDE_ASM("asm/levels", func_L00_003B0A28);


typedef struct {
    char pad0[0xC];
    int used;
    int pad10;
    unsigned char next[8];
} PathNode;

extern PathNode D_L00_0023BB78[];
extern void func_002EDE60(void *dst, int value, int size);
extern void func_002EDEB0(void *dst, void *src, int size);

int func_L00_003B0B20(unsigned char from, unsigned char to, unsigned char *out)
{
    unsigned char path[256];
    unsigned char tried[256];
    unsigned char cur;
    unsigned char next;
    unsigned char len;
    int best;
    int done;

    if (D_L00_0023BB78[from].used == 0 || D_L00_0023BB78[to].used == 0)
        return 0;
    func_002EDE60(path, 0, 256);
    len = 0;
    func_002EDE60(tried, 0, 256);
    cur = from;
    done = 0;
    best = 0;
    do {
        while (D_L00_0023BB78[cur].next[tried[cur]] == cur) {
            tried[cur]++;
            if (tried[cur] == 8)
                break;
        }
        if (tried[cur] == 8) {
            if (len == 0) {
                done = 1;
            } else {
                tried[cur] = 0;
                len--;
                cur = path[len];
            }
        } else {
            next = D_L00_0023BB78[cur].next[tried[cur]];
            tried[cur]++;
            if (next == to) {
                if (best < len + 2) {
                    if (out) {
                        out[0] = from;
                        func_002EDE60(out, 0, 256);
                        func_002EDEB0(out + 1, path, len);
                        out[len + 2] = next;
                        out[len + 1] = cur;
                    }
                    best = len + 3;
                }
            } else {
                path[len++] = cur;
                cur = next;
            }
        }
    } while (!done);
    return best;
}


INCLUDE_ASM("asm/levels", func_L00_003B0DA0);

INCLUDE_ASM("asm/levels", func_L00_003B1270);

INCLUDE_ASM("asm/levels", func_L00_003B14D0);

/* A variadic forwarder whose whole retail body is the register save area the EE compiler
   emits for a variadic function: four named integer arguments consume $a0-$a3, so the
   variadic ones are saved out of $t0-$t3 and $f12/$f18. Nothing else is left of it. */
void func_L00_003B1A08(int a0, int a1, int a2, int a3, ...)
{
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003B2900(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void func_L00_003B2B60(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

/* func_L00_003B3090 is matched in its own unit, src/levels/shared/L00_003B3090-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */
