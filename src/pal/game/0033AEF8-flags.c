#include "include_asm.h"

extern void *func_PAL_0033CA78(void *);
extern void *func_003361A8(void *);

void *func_PAL_0033B520(char *object) {
    func_PAL_0033CA78(object + 0x8);
    func_003361A8(object + 0x2D8);
    return object;
}

extern void *func_00288FB8(int);
extern void func_PAL_0033CF78(void *, void *, void *, void *);
extern void func_PAL_0033CFD0(void *, float);

/* looks up three objects by numeric id, runs a four-argument routine and a (pointer,float) routine on a sub-object at self+8, then stores 1 at self+764 */
void func_PAL_0033B740(int *self)
{
    void *a;
    void *b;
    void *c;
    void *sub = (void *)(self + 2);

    a = func_00288FB8(2990);
    b = func_00288FB8(2989);
    c = func_00288FB8(2912);

    func_PAL_0033CF78(sub, a, b, c);
    func_PAL_0033CFD0(sub, 0.0f);

    self[203] = 1;
}

extern int D_L00_001A8FD8 __attribute__((sda));
extern int D_L00_001A8FDC __attribute__((sda));
extern void func_PAL_0033CD48(int *p, int flag);
extern void func_PAL_0033CE70(int *p);
extern void func_00336320(int *p);

/* Lazily initialises a sub-object of the argument behind two global flags and a field, runs one guarded setup step on it, then hands it to two callees. */
void func_PAL_0033B8D8(int *obj)
{
    if (D_L00_001A8FD8 != 0 || D_L00_001A8FDC != 0 || obj[204] != 0)
        func_PAL_0033CD48(obj + 2, 0);
    if (obj[203] == 1)
        func_PAL_0033CD48(obj + 2, 1);
    func_PAL_0033CE70(obj + 2);
    func_00336320(obj + 182);
}
