/* func_00273730 - 580 bytes.  Worker attempt, 27 October 2026 (draft below).

   Goes at the end of src/game/0026EA00-qcopy.c (needs `#include "common.h"`
   for qcopy, which the file now has); marker removed from 0026EA00.c. It is
   the creator that calls func_00273978 (extern decl in draft).
   584 vs 580 B. Everything structural matches; remaining ~10 lines are all
   register/ordering at the start: retail `daddu s0,v0` (moby) comes BEFORE
   `jal func_2AB220` with `a0=s1` in its delay slot, info pointer in $a1 and
   the 0x80000000 constant in $a0 (mine: info $a0, const $a1, s0 move filling
   the delay slot). No spelling of the packing expression or of `if (m != 0)`
   changed it.
   Signature: (char *parent, int mode, int type, int idx, void *srcA, void
   *srcB, void *src0, unsigned char flag, float angle, float scale), returns
   the moby. Constants: angle*0.00014544412f; func_00310C88 stored at +0x64. */

extern char *func_0029EFD0(int);
extern unsigned char *func_002AB220(char *);
extern void func_002B37E8(void *, void *);
extern void func_002AEC18(void *, int);
extern void func_002833F0(char *, char *);
extern void func_002A10E8(char *);
extern float func_00283198(float);
extern void func_002A7A00(float *, float, float);
extern float func_00282C10(float);
extern void func_0029F390(char *);
extern void func_002A05A8(char *);
extern void func_00273978(char *, int, int, void *, void *, unsigned char, float);
extern void func_00310C88(void);

char *func_00273730(char *parent, int mode, int type, int idx, void *srcA, void *srcB, void *src0,
                    unsigned char flag, float angle, float scale) {
    char *m;
    unsigned char *info;
    unsigned int packed = 0;
    unsigned short flags;
    float buf[4] __attribute__((aligned(16)));
    float c;

    m = func_0029EFD0(type);
    info = func_002AB220(parent);
    if (info != 0)
        packed = ((info[6] << 16) | ((info[5] << 8) | 0x80000000)) | info[4];
    if (m != 0) {
    func_002B37E8(m, parent);
    if (packed != 0)
        func_002AEC18(m, packed);
    qcopy(m + 0x10, srcA);
    qcopy(m + 0xF0, srcB);
    func_002833F0(m + 0xC0, m + 0xF0);
    if (parent != 0)
        *(float *)(m + 0x2C) = *(float *)(*(char **)(m + 0x24) + 0x24) *
                               (*(float *)(parent + 0x2C) / *(float *)(*(char **)(parent + 0x24) + 0x24));
    func_002A10E8(m);
    flags = (*(unsigned short *)(m + 0x34) | 0x100) & 0xFFDF;
    *(unsigned short *)(m + 0x34) = flags;
    if (parent != 0 && (*(unsigned short *)(parent + 0x34) & 0x800))
        *(unsigned short *)(m + 0x34) = flags | 0x800;
    *(int *)(m + 0x98) = 0;
    *(char **)(*(char **)(m + 0x68) + 0x54) = parent;
    c = func_00283198(angle * 0.00014544412f);
    func_002A7A00(buf, c, c);
    buf[3] = func_00282C10(1.0f - c * c);
    if (mode == 1) {
        if (parent != 0) {
            m[0x42] = parent[0x43];
            m[0x43] = parent[0x43];
        }
        func_0029F390(m);
        *(int *)(m + 0x48) = 0;
        *(int *)(m + 0x44) = 0;
        func_002A05A8(m);
    }
    func_00273978(m, mode, idx, src0, buf, flag, scale);
    if (*(unsigned short *)(m + 0x7C) & 0x8000) {
        if (*(unsigned short *)(m + 0x34) & 0x10)
            *(unsigned short *)(m + 0x34) = *(unsigned short *)(m + 0x34) & 0xFFEF;
    }
    *(void (**)(void))(m + 0x64) = func_00310C88;
    }
    return m;
}
