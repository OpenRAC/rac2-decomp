/* functional: high. Same calls with the same arguments in the same order; the result of func_L00_00324D18 is returned as retail leaves it in v0. */
/*
 * func_L00_00324E48 (196 bytes): targeting from the hero's view. Takes the
 * point 0.75 along the camera object's vector (D_00189E20+0x2290 -> +0xE0),
 * adds the hero position (+0x80), and runs the cone search
 * func_L00_00324D18 from there along dir with the caller's mode and five
 * angles/ranges; returns the moby it found (or 0).
 */
typedef struct {
    unsigned char pad0[0x80];
    float pos[4];
    unsigned char pad90[0x2290 - 0x90];
    unsigned char *obj;
} Hero_324E48;

extern Hero_324E48 D_00189E20;

extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_L00_00324D18(void *, void *, int, float, float, float, float, float);

char *func_L00_00324E48(void *dir, int mode, float f0, float f1, float f2, float f3, float f4)
{
    Hero_324E48 *h = &D_00189E20;
    float origin[4];

    func_00282D30(origin, h->obj + 0xE0, 0.75f);
    func_00282CC0(origin, h->pos, origin);
    return func_L00_00324D18(origin, dir, mode, f0, f1, f2, f3, f4);
}
