#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef long long s64;

typedef struct {
    char pad0[0x8];
    int unk008;
    char pad1[0xAC - 0xC];
    int unk0AC;
    char pad2[0x118 - 0xB0];
    int unk118;
    char pad3[0x820 - 0x11C];
    int unk820;
} Obj40;

/* Marks the MPEG picture decoder as finished with the current picture. */
s32 func_0012DA98(void *decoder) {
    Obj40 *dec = (Obj40 *)decoder;
    s32 one = 1;

    if (dec->unk008 != 2) {
        s32 savedValue = dec->unk118;
        dec->unk008 = 2;
        dec->unk0AC = savedValue;
    }
    dec->unk820 = one;
    return one;
}

/* The MPEG library's picture timestamp and flags: the picture's presentation
   timestamp, its decoding timestamp and a packed word of the picture's coding
   fields. Carried from rac1-decomp's func_00129CA0 (src/core/00125630.c), the
   same library with this image's +0x3E20 core shift; func_00121AB8 is its
   __muldi3. */
extern s64 func_00121AB8(s64 a, s64 b);

/* Works out the timestamp and flags for an MPEG picture and writes them to the output slots. */
s64 func_0012DAC0(void *decoder, void *picture, void *outPts, void *outDts, void *outFlags) {
    char *dec = decoder;
    char *pic = picture;
    s64 *pts = outPts;
    s64 v;
    s64 packed;

    if (*(s32 *)(dec + 0x70) != 0) {
        s32 base;
        v = *(s64 *)(pic + 0x18);
        if (v >= 0 || (base = *(s32 *)(dec + 0x80)) < 0) {
            *pts = v;
        } else {
            s32 n = *(s64 *)(dec + 0x88);
            s64 r = MultiplyLongLong(n & 1, *(s64 *)(dec + 0x78) & 1);
            s32 cnt = *(s32 *)(dec + 0x90);
            s32 a = MultiplyLongLong(r, cnt & 1);
            *pts = base + ((s32)(MultiplyLongLong(*(s64 *)(dec + 0x78), n) >> 1) + a);
            if (MultiplyLongLong(n & 1, *(s64 *)(dec + 0x78) & 1)) {
                *(s32 *)(dec + 0x90) = cnt + 1;
            }
        }
    } else {
        *pts = *(s64 *)(pic + 0x18);
    }
    if (*(s32 *)(dec + 0xF8) == 2 && (v = *(s64 *)(dec + 0xF0)) >= 0) {
        *pts = v;
        *(s32 *)(dec + 0xF8) = 0;
        *(s64 *)(dec + 0xF0) = -1;
    }
    *(s64 *)outDts = *(s64 *)(pic + 0x20);
    packed = ((s64)*(s32 *)(pic + 0x34) << 8) | ((s64)*(s32 *)(pic + 0x38) << 7)
           | ((s64)*(s32 *)(pic + 0x3C) << 6) | ((s64)*(s32 *)(pic + 0x40) << 5)
           | ((s64)*(s32 *)(pic + 0x30) << 3) | *(s32 *)(pic + 0x2C);
    *(s64 *)outFlags = packed;
    return packed;
}

extern void func_0012DC50();
extern long r1_func_00129CA0(void *s, void *t, void *o1, void *o3, void *o4);
extern unsigned int r1_D_00132F98[];
extern void r1_func_0012A7E8(void *arg0, void *arg1);

/* rac1-decomp src/core/00125630.c: func_0012DC50 */
/* Hands a decoded MPEG picture over to the video output and starts the copy to the screen. */
void func_0012DC50(char *dec, char *pic) {
    char *transfer;
    long flags;

    transfer = *(char **)(dec + 0x858);
    r1_func_00129CA0(dec, pic, transfer + 0x10, transfer + 0x18, transfer + 0x20);
    transfer = *(char **)(dec + 0x858);
    flags = *(long *)(transfer + 0x20);
    *(int *)(dec + 0x80) = *(int *)(transfer + 0x10);
    *(unsigned long *)(dec + 0x88) = r1_D_00132F98[(int)(flags >> 5) & 0xF];
    *(int *)(dec + 0xCC) = *(int *)(pic + 0x5C);
    *(int *)(dec + 0xD0) = *(int *)(pic + 0x60);
    *(int *)(dec + 0xB4) = *(int *)(pic + 0x44);
    *(int *)(dec + 0xB8) = *(int *)(pic + 0x48);
    *(int *)(dec + 0xBC) = *(int *)(pic + 0x4C);
    *(int *)(dec + 0xC0) = *(int *)(pic + 0x50);
    *(int *)(dec + 0xC4) = *(int *)(pic + 0x54);
    *(int *)(dec + 0xC8) = *(int *)(pic + 0x58);
    if (r1_func_00129948(dec, pic) == 0) return;
    if (*(int *)(pic + 0x28) != 1) return;
    if (*(int *)(dec + 0xB0) != 0) {
        r1_func_0012A7E8(dec, pic);
    } else {
        r1_func_001299E8((void *)dec, (void *)pic);
    }
    r1_func_00129C78(dec);
}

ASM_FUNC("asm/core", func_0012DF18);
