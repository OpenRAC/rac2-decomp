/* functional: high. Same compares, stores and calls in retail order; this cc1 allocates one extra register move, which does not change behaviour. */
#include "include_asm.h"
typedef struct {
    int unk00;
    int flags;
    char pad08[0x18];
    int a;
    int key;
    int f;
    int e;
    int b;
    int c;
    int d;
    char pad3C[0x28];
    int stamp;
    int active;
    char pad6C[4];
    int unk70;
    char pad74[8];
    int unk7C;
    char pad80[0x10];
} SlotRecord;

typedef struct { unsigned char pad00[0x64]; int key; unsigned char pad68[0x28]; } SearchRow_28B5D0;
extern SearchRow_28B5D0 D_00255330[];
extern int D_001A8BB0[] __attribute__((sda));
extern int D_001B1870[] __attribute__((sda));
extern void func_0028B4D8(char *);

/* Starts (or keeps) the request id in its slot (the id's low four bits): a
   changed parameter set restamps the slot from the frame counter and resets it.
   Returns the slot's stamp, or 0 when state 5 locks every slot but 0 and 2. */
int func_0028B3D0(int id, int a, int b, int c, int d, int e, int f)
{
    int slot = id & 0xF;
    int key = id & 0xFFF0;
    SlotRecord *r = (SlotRecord *)&D_00255330[slot];

    if (D_001A8BB0[0] == 5 && slot != 2 && slot != 0)
        return 0;
    if (r->e != e || r->f != f || r->a != a || r->key != key || r->b != b || r->c != c
        || r->d != d) {
        r->stamp = D_001B1870[0];
        r->e = e;
        r->f = f;
        r->a = a;
        r->b = b;
        r->c = c;
        r->d = d;
        D_001B1870[0]++;
        r->active = 1;
        r->key = key;
        r->unk7C = 0;
        r->unk70 = 0;
        if (key & r->flags & 0x20)
            func_0028B4D8((char *)r);
    }
    return r->stamp;
}
