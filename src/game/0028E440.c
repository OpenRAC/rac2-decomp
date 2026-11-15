#include "include_asm.h"
#include "common.h"

extern unsigned int ref_L00_002F9D30_00 __attribute__((sda));

void func_0028E440(void)
{
    if (ref_L00_002F9D30_00 != 0)
        --ref_L00_002F9D30_00;
}

typedef struct Task28E458 {
    u8 pad00[0x18];
    void (*update)(struct Task28E458 *);
    u8 pad1C[0x90 - 0x1C];
} Task28E458;

extern s32 D_001B18A4[] __attribute__((sda));
extern s32 D_001B15A8[] __attribute__((sda));
extern s32 D_001B187C[] __attribute__((sda));
extern s32 D_001B17B0[] __attribute__((sda));
extern s32 D_001B17B4[] __attribute__((sda));
extern s32 D_001B17B8[] __attribute__((sda));
extern s32 D_001A8BB0[] __attribute__((sda));
extern Task28E458 D_00255330[];

void func_0028E458(void) {
    Task28E458 *t;
    s32 i;

    if (D_001B18A4[1] != 0 || D_001B15A8[0] != 0) {
        D_001B18A4[1] = 0;
        return;
    }
    t = D_00255330;
    D_001B187C[0] = 0xFFFFF0;
    for (i = 12; i >= 0; i--) {
        if (t->update != 0) {
            t->update(t);
        }
        t++;
    }
    if ((D_001B17B0[0] != 0 || D_001B17B4[0] != 0) && D_001A8BB0[0] == 0) {
        if (D_001B17B0[0] != 0) {
            D_001B17B4[0] += 0x10;
            if (D_001B17B4[0] > 0x80) {
                D_001B17B4[0] = 0x80;
            }
        } else {
            D_001B17B4[0] -= 0x10;
            if (D_001B17B4[0] < 0) {
                D_001B17B4[0] = 0;
            }
        }
        if (D_001B17B0[0] != 0) {
            D_001B17B0[0]--;
        }
        if (D_001B17B0[0] == 1000) {
            D_001B17B0[0] = 0;
        }
    } else {
        D_001B17B8[0] = 100;
    }
}

extern int func_0028AB20(int);
extern unsigned short *D_001B188C;
extern short *D_001B1890;
extern unsigned int *D_001B1898;
extern unsigned int *D_001B1894;

int func_0028E588(int key, int index)
{
    int number = func_0028AB20(key);
    unsigned short *row = (unsigned short *)(number * 8 + (unsigned int)D_001B188C);
    if (row[0] == 65535)
        goto fail;
    if (index >= row[1])
        goto fail;
    {
        unsigned int mask = 0x80000000u;
        int offset = row[2] + index;
        short *pair = (short *)(offset * 4 + (unsigned int)*(short *volatile *)&D_001B1890);
        if (D_001B1898[pair[0] * 2] & mask)
            goto fail;
        return (D_001B1894[pair[1] * 2] & mask) ? 0 : offset;
    }
fail:
    return 0;
}


extern int *ref_L00_001B2608_00;
extern int ref_L00_001B1BBC_01;
extern int D_001A7350;
extern int D_001A7354;
extern int func_0028E640(int);

void func_0028E868(int a0, int a1, int a2, int a3, int a4, int a5)
{
    short *row = (short *)((a0 << 2) + (unsigned int)D_001B1890);
    unsigned char *entry = (unsigned char *)((unsigned int)D_001B1894 + (row[1] << 3));
    int mask6 = 1 << entry[6];
    int mask7 = 1 << entry[7];
    int *p;
    char *q;
    int result;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    p = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = p + 4;
    q = (char *)ref_L00_001B2608_00;
    *(long long *)(p + 4) = 0x7400000000008001LL;
    *(long long *)(q + 8) = 0x05353106;
    result = GetFrameTexture(a0);
    *(long long *)(q + 16) = result;
    *(long long *)(q + 24) = 0x156;
    *(long long *)(q + 32) = ((long long)a5 << 24) | 0x7F7F7F;
    *(long long *)(q + 40) = 0;
    *(long long *)(q + 48) = ((a1 << 4) + D_001A7350 - 8) | ((long long)((a2 << 4) + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 56) = (mask7 << 20) + (mask6 << 4);
    *(long long *)(q + 64) = (((a1 + a3) << 4) + D_001A7350 - 8) | ((long long)(((a2 + a4) << 4) + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}


void func_0028ECD8(int a0, int a1, int a2, int a3, int a4, int a5)
{
    int *p;
    char *q;
    int result;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    p = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = p + 4;
    q = (char *)ref_L00_001B2608_00;
    *(long long *)(p + 4) = 0x7400000000008001LL;
    *(long long *)(q + 8) = 0x05353106;
    result = GetFrameTexture(a0);
    *(long long *)(q + 16) = result;
    *(long long *)(q + 24) = 0x156;
    *(long long *)(q + 32) = ((long long)a5 << 24) | 0x7F7F7F;
    *(long long *)(q + 40) = 0;
    *(long long *)(q + 48) = ((a1 << 4) + D_001A7350 - 8) | ((long long)((a2 << 4) + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 56) = (a4 << 20) + (a3 << 4);
    *(long long *)(q + 64) = (((a1 + a3) << 4) + D_001A7350 - 8) | ((long long)(((a2 + a4) << 4) + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}


void func_0028EE98(int a0, int a1, int a2, int a3, int a4, int a5)
{
    short *row = (short *)((a0 << 2) + (unsigned int)D_001B1890);
    unsigned char *entry = (unsigned char *)((unsigned int)D_001B1894 + (row[1] << 3));
    int mask6 = 1 << entry[6];
    int mask7 = 1 << entry[7];
    int *p;
    char *q;
    int result;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    p = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = p + 4;
    q = (char *)ref_L00_001B2608_00;
    *(long long *)(p + 4) = 0x7400000000008001LL;
    *(long long *)(q + 8) = 0x05353106;
    result = GetFrameTexture(a0);
    *(long long *)(q + 16) = result;
    *(long long *)(q + 24) = 0x156;
    *(long long *)(q + 32) = ((long long)a5 << 24) | 0x7F7F7F;
    *(long long *)(q + 40) = 0;
    *(long long *)(q + 48) = (a1 + D_001A7350 - 8) | ((long long)(a2 + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 56) = (mask7 << 20) + (mask6 << 4);
    *(long long *)(q + 64) = (a1 + a3 + D_001A7350 - 8) | ((long long)(a2 + a4 + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}

void func_0028F078(int a0, int a1, int a2, int a3, int a4, int a5, unsigned int color)
{
    short *row = (short *)((a0 << 2) + (unsigned int)D_001B1890);
    unsigned char *entry = (unsigned char *)((unsigned int)D_001B1894 + (row[1] << 3));
    int mask6 = 1 << entry[6];
    int mask7 = 1 << entry[7];
    int *p;
    char *q;
    int result;
    long long rgba;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    p = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = p + 4;
    q = (char *)ref_L00_001B2608_00;
    *(long long *)(p + 4) = 0x7400000000008001LL;
    *(long long *)(q + 8) = 0x05353106;
    result = GetFrameTexture(a0);
    *(long long *)(q + 16) = result;
    *(long long *)(q + 24) = 0x156;
    rgba = (unsigned char)color;
    rgba |= (unsigned int)(unsigned char)(color >> 8) << 8;
    rgba |= (long long)(unsigned char)(color >> 16) << 16;
    rgba |= (long long)a5 << 24;
    *(long long *)(q + 32) = rgba;
    *(long long *)(q + 40) = 0;
    *(long long *)(q + 48) = (a1 + D_001A7350 - 8) | ((long long)(a2 + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 56) = (mask7 << 20) + (mask6 << 4);
    *(long long *)(q + 64) = (a1 + a3 + D_001A7350 - 8) | ((long long)(a2 + a4 + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}

/* alpha is copied before a9 is reused for the texture height: retail loads the
   stack argument at the top and sign-extends it in place for the colour word.
   With a9 used only there, combine folds the load into the extension behind the
   header stores, and the colour loses $v1 to the cursor reloads. */
void func_0028F278(long long a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int *p;
    char *q;
    int alpha = a9;

    a9 = 1 << (a4 + 4);
    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    p = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = p + 4;
    q = (char *)ref_L00_001B2608_00;
    *(long long *)(p + 4) = 0x7400000000008001LL;
    *(long long *)(q + 8) = 0x05353106;
    *(long long *)(q + 16) = a0;
    *(long long *)(q + 24) = 0x156;
    *(long long *)(q + 32) = ((long long)alpha << 24) | 0x7F7F7F;
    *(long long *)(q + 40) = a7 | ((long long)a8 << 16);
    *(long long *)(q + 48) = (a1 + D_001A7350 - 8) | ((long long)(a2 + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 56) = (a7 + (1 << (a3 + 4))) | ((long long)(a8 + a9) << 16);
    *(long long *)(q + 64) = (a1 + a5 + D_001A7350 - 8) | ((long long)(a2 + a6 + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}



/* The command cursor and the third coordinate word sit at a different address in
   every program, so they are per-level externals named after their level-00 place.
   The retail reaches them with lui+%lo, so they carry no sda attribute here: in this
   -G8 unit the bare symbol form would put them in small data and make the access
   $gp-relative. */
extern int *ref_L00_001B2608_00;
extern int ref_L00_001B1BBC_01;
extern int D_001A7350;
extern int D_001A7354;
extern int func_0028E640(int);

void func_0028F788(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int *p;
    char *q;
    int result;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    p = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = p + 4;
    q = (char *)ref_L00_001B2608_00;
    *(long long *)(p + 4) = 0x7400000000008001LL;
    *(long long *)(q + 8) = 0x05353106;
    result = GetFrameTexture(a0);
    *(long long *)(q + 16) = result;
    *(long long *)(q + 24) = 0x156;
    *(long long *)(q + 32) = ((long long)a9 << 24) | 0x7F7F7F;
    *(long long *)(q + 40) = a5 | ((long long)a6 << 16);
    *(long long *)(q + 48) = (a1 + D_001A7350 - 8) | ((long long)(a2 + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 56) = a7 | ((long long)a8 << 16);
    *(long long *)(q + 64) = (a3 + D_001A7350 - 8) | ((long long)(a4 + D_001A7354 - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}
