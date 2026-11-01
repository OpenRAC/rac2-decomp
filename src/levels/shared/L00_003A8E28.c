#include "include_asm.h"

typedef struct { char pad[12]; int active; char gap[4]; unsigned char links[8]; } PathSearchNode;

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


/* func_L00_003AA4C8 is defined in L00_003AA4C8-effects-g.c. */

/* func_L00_003AA708 is defined in L00_003AA708-g.c. */

/* func_L00_003AB388 is defined in L00_003AB388-hit.c. */

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

extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern char *func_002BDCE8(void *, int, void *, float, float, unsigned int, float, float, int);
extern char D_L00_001A8F20[] __attribute__((section(".sdata")));
void func_L00_003AB6F0(void *unused, void *position)
{
    int i, sign;
    char *p, *q;
    for (i=1; i>=0; i--) {
        int n=func_002A77E0(16);
        sign=func_002A77E0(2);
        p=func_002BDCE8(position, sign ? -n : n, D_L00_001A8F20, 0.04f, 1.0f, 0x7f204080, 0.9f, 50000.0f, 1);
        q=p+32;
        if(p) {
            *(short *)(p+10)=10;
            p[9]=func_00283CF0(4.0f)+64;
            *(int *)(q+4)=2;
            q[10]=127;
            q[11]=*(unsigned char *)(p+10);
        }
    }
    { int n=16;
    int j;
    for(j=0;j<2;j++) {
        p=func_002BDCE8(position,n,D_L00_001A8F20,0.02f,1.0f,0x7fffffff,0.97f,15000.0f,1);
        n=-n;
        q=p+32;
        if(p) {
            p[9]=func_00283CF0(4.0f)+64;
            *(short *)(p+10)=2;
            p[8]=func_002A77E0(255);
            *(int *)(q+4)=2;
            q[10]=127;
            q[11]=*(unsigned char *)(p+10);
        }
    }
    }
}


/* func_L00_003AB8B8 is defined in L00_003AB8B8.c. */

INCLUDE_ASM("asm/levels", func_L00_003AB9C0);

INCLUDE_ASM("asm/levels", func_L00_003ABEC0);


/* func_L00_003ACA60 is defined in L00_003ACA60-particles-g.c. */

/* func_L00_003ACC88 is defined in L00_003A8E28-g8.c (the scale is read through $gp). */


/* func_L00_003AD7C8 is defined in L00_003AD7C8.c. */


typedef int TI128_ADA30 __attribute__((mode(TI)));
typedef float VecADA30[4] __attribute__((aligned(16)));

/* The quad record handed to func_00280B90, as in RAC1 sentrybot.c draw_spiderbot_effect_quad. */
typedef struct {
    VecADA30 v[4];
    unsigned int col[4];
    float uv[4][2];
    long a, b, c, d;
} QuadADA30;

/* Per-row lists of linked mobys (eight entries and a null terminator), filled by func_L00_003ADEA0. */
extern char *ref_L00_003ADA30_0[10][9];
extern float ref_L00_003ADA30_1[];
/* The quad's four (u, v) pairs. With sda cc1 costs each address as one instruction, so the u and v
   streams keep separate bases (the assembler still expands each to lui/addiu at -G0). */
extern float ref_L00_003ADA30_2[][2] __attribute__((sda));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);

/* Draws an effect quad (texture 14) from this moby to every active moby of its class linked in its row. */
void func_L00_003ADA30(char *moby)
{
    QuadADA30 q;
    VecADA30 left, right, diff, pos, tmp;
    char *vars = *(char **)(moby + 0x68);
    char *other;
    int n, i;

    n = 0;
    while (n < 9 && (other = ref_L00_003ADA30_0[*(short *)(vars + 0x4A)][n++]) != 0) {
        if (*(unsigned char *)(other + 0x20) == 6 && other != moby && other
            && *(short *)(other + 0xAA) == *(short *)(moby + 0xAA)) {
            *(TI128_ADA30 *)pos = *(TI128_ADA30 *)(moby + 0x10);
            func_00282CF0(diff, pos, other + 0x10);
            func_00282CF0(left, pos, ref_L00_003ADA30_1);
            func_00282CF0(right, other + 0x10, ref_L00_003ADA30_1);
            func_00282DD8(left, left, diff);
            func_00282F20(left, left, 0.1f);
            func_00282DD8(right, right, diff);
            func_00282F20(right, right, 0.1f);
            q.b = func_0027C878(14);
            q.c = 0xFF9000000260L;
            q.d = 0x8000000048L;
            q.a = 0;
            q.col[3] = 0x80243278;
            q.col[2] = 0x80243278;
            q.col[1] = 0x80243278;
            q.col[0] = 0x80243278;
            for (i = 0; i < 4; i++) {
                q.uv[i][0] = ref_L00_003ADA30_2[i][0];
                q.uv[i][1] = ref_L00_003ADA30_2[i][1];
            }
            func_00282CF0(tmp, pos, left);
            *(TI128_ADA30 *)q.v[0] = *(TI128_ADA30 *)tmp;
            func_00282CC0(tmp, pos, left);
            *(TI128_ADA30 *)q.v[1] = *(TI128_ADA30 *)tmp;
            func_00282CF0(tmp, other + 0x10, right);
            *(TI128_ADA30 *)q.v[2] = *(TI128_ADA30 *)tmp;
            func_00282CC0(tmp, other + 0x10, right);
            *(TI128_ADA30 *)q.v[3] = *(TI128_ADA30 *)tmp;
            func_00280B90(&q, 0, 0);
        }
    }
}

INCLUDE_ASM("asm/levels", func_L00_003ADCD8);


/* func_L00_003ADEA0 is defined in L00_003A8E28-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_003AE550);

INCLUDE_ASM("asm/levels", func_L00_003AE900);

/* func_L00_003B0A28 is defined in L00_003B0A28-g8.c. */


/* Searches the node adjacency table with a byte-indexed backtracking stack. */
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

/* func_L00_003B1270 is defined in L00_003A8E28-g8.c. */

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
