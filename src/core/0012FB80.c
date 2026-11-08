#include "common.h"
#include "structs.h"

extern void func_00130288(void *, void *);

extern unsigned int func_0012FB80(void *, char *, unsigned int, unsigned int);

extern char r1_D_00153B38[];

extern void func_0012FAE8(int);

extern int r1_func_00129690(void *, int);

extern int r1_func_00129530(void *);

extern void r1_func_00129600(void *, int, int);

extern int func_0012FD60(void *, int, int);

extern int r1_func_00129530();

extern int r1_func_00129690();

extern void r1_func_00129600();

/* rac1-decomp src/core/0012AC80.c: func_0012BD60 */
/* Bump allocator out of a region {base, size, used}: round `used` up to
   `align`, reserve `size` bytes, and hand back the aligned offset. On
   overflow it reports through func_00130288 and returns 0 WITHOUT
   touching `used`.

   The fitting case is written first (`>=`): 2.9-ee then branches to the
   report on the true side (bnel) and puts the `used` store in the slot
   of the fall-through `b`, as retail. Written overflow-first, as 2.95.3
   needed, 2.9-ee inverts the test and puts the store in a beql slot,
   one instruction short (SIZE 104/108). */
unsigned int func_0012FB80(void *arg0, char *r, unsigned int size,
                           unsigned int align) {
    unsigned int aligned;
    unsigned int end;

    aligned = ((*(unsigned int *)(r + 0x8) + align - 1) / align) * align;
    end = aligned + size;
    if (*(unsigned int *)(r + 0x0) + *(unsigned int *)(r + 0x4) >= end) {
        *(unsigned int *)(r + 0x8) = end;
        return aligned;
    }
    func_00130288(arg0, r1_D_00153B38);
    return 0;
}

extern int func_0012FBF0(void *);
extern int r1_func_00128C90(void *);
extern int r1_func_0012C200(void *);
extern int r1_func_0012C058(void *, int, int);
extern void r1_func_0012C430();
extern char r1_D_00153B58[];

/* rac1-decomp src/core/0012AC80.c: func_0012FBF0 */
/*
 * _getpic (libmpeg.a:mpeg.o): fetch and start decoding one picture.
 * The image buffer (inner +0xD8) must be 64-byte aligned; if not, it is
 * reported through _errMessage with the address and the call fails with
 * -1. Otherwise loop: fetch headers (r1_func_00128C90) until one yields no
 * picture (0), the picture counter reaches its target (+0x174 == +0xD4)
 * or the fault flag (+0x848) clears, skipping the fetch when the last
 * decode returned -1. picture_coding_type 1/2/3 call r1_func_0012C058 with
 * that type's running index (+0xA0/+0xA4/+0xA8, I resetting all three)
 * and slot (+0x94/+0x98/+0x9C) and bump the index; type 4 shares the B
 * arm (retail's jump table maps 3 and 4 to one handler); 0 ends the
 * stream through r1_func_0012C200 and sets inner->0; anything above 4 does
 * nothing. Returns 1 once +0x820 or inner->0 is set.
 *
 * pictureType's initializer and lastResult declared first put both in
 * retail's saved registers and hoist lastResult's 0 into the prologue.
 */
int func_0012FBF0(void *arg0) {
    int pictureType = 1;
    int lastResult = 0;
    char *w = (char *)arg0;
    char *inner = *(char **)(w + 0x40);

    *(int *)inner = 0;
    if ((*(int *)(inner + 0xD8) & 0x3F) != 0) {
        r1_func_0012C430(inner, r1_D_00153B58, *(int *)(inner + 0xD8));
        return -1;
    }
    *(int *)(inner + 0x820) = 0;

    do {
        if (lastResult != -1) {
            for (;;) {
                pictureType = r1_func_00128C90(inner);
                if (pictureType == 0) break;
                if (*(int *)(inner + 0x174) == *(int *)(inner + 0xD4)) break;
                if (*(int *)(inner + 0x848) == 0) break;
            }
        }

        switch (pictureType) {
        case 0:
            r1_func_0012C200(w);
            *(int *)inner = 1;
            break;
        case 1:
            *(int *)(inner + 0xA8) = 0;
            *(int *)(inner + 0xA4) = 0;
            *(int *)(inner + 0xA0) = 0;
            lastResult = r1_func_0012C058(w, 0, *(int *)(inner + 0x94));
            *(int *)(inner + 0xA0) = *(int *)(inner + 0xA0) + 1;
            break;
        case 2:
            lastResult = r1_func_0012C058(w, *(int *)(inner + 0xA4), *(int *)(inner + 0x98));
            *(int *)(inner + 0xA4) = *(int *)(inner + 0xA4) + 1;
            break;
        case 3:
        case 4:
            lastResult = r1_func_0012C058(w, *(int *)(inner + 0xA8), *(int *)(inner + 0x9C));
            *(int *)(inner + 0xA8) = *(int *)(inner + 0xA8) + 1;
            break;
        }

        if (*(int *)(inner + 0x820) != 0) {
            return 1;
        }
    } while (*(int *)inner == 0);

    return 1;
}

/* rac1-decomp src/core/0012AC80.c: func_0012BF40 */
/* _decodeOrSkipFrame (libmpeg): sibling of func_0012FEC0
   (_decodeOrSkipField), for the frame-picture path. Adapted from
   Lombyte (GPL-3.0) for PAL. */
int func_0012FD60(void *arg0, int arg1, int arg2) {
    Wrapper *w = (Wrapper *)arg0;
    Obj40 *p = w->obj;
    int flag = 0;
    int t;
    int ret;

    if (arg2 == -1 || arg1 < arg2) {
        if (p->unk008 == 0) {
            w->unk08 = 0;
            p->unk008 = 1;
        }
        if (r1_func_00129690(p, 0) == 0) {
            t = 0;
        } else {
            t = 0;
            t = r1_func_00129530(p) != t;
        }
        ret = t;
    } else {
        flag = 1;
        ret = r1_func_00129690(p, 0);
        func_0012FAE8((int)w);
    }
    r1_func_00129600(p, p->unk118, p->unk004);
    if (p->unk174 != 3 && flag == 0) {
        p->unk120 = (p->unk120 == 0);
    }
    w->unk08 = p->unk118 - p->unk0AC;
    if (p->unk120 == 0) {
        p->unk118 = p->unk118 + 1;
        p->unk004 = p->unk004 + 1;
    }
    return ret;
}
