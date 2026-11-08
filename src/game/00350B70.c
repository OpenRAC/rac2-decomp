#include "ps2_hw.h"
#include "include_asm.h"

typedef int s32;

typedef unsigned char u8;

/* func_003512B8 : rounds a field to a multiple of 2048 under a semaphore */
extern s32 func_0011AC60(s32);

extern s32 func_0011AC40(s32);

/* func_00351268 : waits, then combines two fields shifted by 11 */
extern s32 func_0011AC60(s32 a0);

extern s32 func_0011AC40(s32 a0);

typedef struct ViBuf {
    int base;               /* 0x0 */
    unsigned char *tags;    /* 0x4 */
    int count;              /* 0x8 */
    int fC;                 /* 0xC */
    int f10;                /* 0x10 */
    int f14;                /* 0x14 */
    int f18;
    char pad1C[0x24];
    int sema;               /* 0x40 */
    int f44;                /* 0x44 */
} ViBuf;

extern void func_0034F780(char *);
extern char D_001AE848[];
extern void func_00350808(unsigned int);
extern int func_00350750(ViBuf *, unsigned int);
extern void func_00350878(unsigned long *, unsigned long, unsigned long, unsigned long);

void func_00350B70(u8 *a0, s32 a1) {
    func_0011AC60(*(s32 *)(a0+0x40));
    *(s32 *)(a0+0x14) += (s32)a1;
    *(long *)(a0+0x48) = (long)a1 + *(long *)(a0+0x48);
    func_0011AC40(*(s32 *)(a0+0x40));
}
int func_00350BC8(ViBuf *vb) {
    int ok = 0;
    unsigned int chcr;
    int idx;
    int done;
    int n;
    int i;
    int rd;
    int pos;

    func_0011AC60(vb->sema);
    if (vb->f44 == 0) {
        func_0034F780(D_001AE848);
        return 0;
    }
    func_00350808(5);
    chcr = D4_CHCR;
    rd = func_00350750(vb, D4_MADR);
    done = (rd + vb->count - vb->fC) % vb->count;
    vb->fC = (vb->fC + done) % vb->count;
    vb->f10 -= done;
    pos = (vb->fC + vb->f10) % vb->count;

    n = vb->f14 / 0x800;
    vb->f14 -= n << 11;
    if (n > 0) {
        int last = vb->count - 1;
        int prev = (vb->fC + vb->f10 + last) % vb->count;
        func_00350878((unsigned long *)(vb->tags + prev * 16), vb->base + (prev << 11), 3, 0x80);
        ok = 1;
    }
    idx = pos;
    for (i = 0; i < n; i++) {
        int t = 0;
        if (i != n - 1) {
            t = 3;
        }
        func_00350878((unsigned long *)(vb->tags + idx * 16), vb->base + (idx << 11), t, 0x80);
        idx = (idx + 1) % vb->count;
    }
    vb->f10 += n;
    if (vb->f10 != 0) {
        if (ok) {
            chcr = (chcr & 0x0FFFFFFF) | 0x30000000;
        }
        func_00350808(chcr | 0x100);
    }
    func_0011AC40(vb->sema);
    return 1;
}
