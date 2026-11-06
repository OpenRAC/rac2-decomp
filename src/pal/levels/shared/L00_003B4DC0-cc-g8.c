/* func_PAL_L00_003B4DC0, the PAL copy of func_L00_003B14D0: the same C, where expr 0.033333335f becomes 0.040000003f; expr 0.016666668f becomes 0.020000001f. */
/* func_L00_003A8E28: store a fresh trail sample in the source's slot (flags in config/cflags.txt). */
#include "common.h"
/* func_PAL_L00_003B4DC0: a burst of particles and glows where a consumed trail
 * group ends (flags in config/cflags.txt: the zeroed vectors are por/sq). */
typedef struct { float x, y, z, w; } Vec16_Fc936841d;
typedef int EffectQuad __attribute__((mode(TI)));
typedef struct { char pad[0x2290]; int owner; } EffectContext;
typedef struct { unsigned char pad[0x23]; unsigned char index; } EffectSelector;
typedef struct { unsigned int tag; unsigned char enabled; unsigned char tail[0xDB]; } EffectMaterial;
typedef struct { int v[6]; } EffectSix;

extern EffectContext D_00189E20 __attribute__((nosda));
extern EffectSelector D_00139568 __attribute__((nosda));
extern EffectMaterial D_L00_00262570[] __attribute__((nosda));
extern char D_L00_001C3280[] __attribute__((nosda));
extern char D_L00_001B8DC0[] __attribute__((nosda));
extern EffectSix D_L00_001AF858 __attribute__((nosda));
extern EffectSix D_L00_001AF870 __attribute__((nosda));

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern int func_00277F48(void *, int, int, int, float);
extern void func_002A9850(int, void *, void *, int, int, int, int, int, float, float, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_002AAFA0(unsigned int, int);
extern void func_002AAF40(int *, int *, int *, int);
extern char *func_002BBCB0(void *, void *, int, int, float, int, int, float, int, int);
extern char *func_L00_003A0DA0(int, void *, void *, int, unsigned char, unsigned char,
                               unsigned char, unsigned char, float);

void func_PAL_L00_003B4DC0(float x, float y, float z)
{
    Vec16_Fc936841d p, v;
    Vec16_Fc936841d delta;
    EffectSix a, b;
    int c0, c1, c2, r, g, blue;
    /* The initial value only changes gcse's table size, which orders the three
       RGB pointer spills as retail has them; flow deletes the store. */
    int n = 0, ca, cb, t0, t1;
    float distance, fade, speed, one;

    *(EffectQuad *)&p = 0;
    p.x = x;
    p.y = y;
    p.z = z;
    n = func_00277F48(&p, 16, D_00189E20.owner, 0, 3.0f);
    one = 1.0f;
    func_002A9850(D_00189E20.owner, &p, D_L00_001C3280, n, 0, 0x830000, 2, 1, 8.0f, one, one);
    *(EffectQuad *)&v = 0;
    v.z = 0.040000003f;
    func_00282CF0(&delta, D_L00_001B8DC0, &p);
    distance = func_00282DF0(&delta);
    n = distance < 6.0f ? func_00283CF0(distance) + 1 : 4;
    fade = 0.0f;
    if (distance < 7.0f)
        fade = 7.0f - distance;
    {
        int count;
        for (count = 0; count < n; count++) {
            speed = func_002A7878(8.0f, 10.0f) * (0.020000001f);
            speed -= fade * (0.020000001f);
            a = D_L00_001AF858;
            b = D_L00_001AF870;
            {
                int choice = func_002A77E0(6);
                EffectMaterial *entry = D_L00_00262570 + D_00139568.index;
                ca = func_002AAFA0(a.v[choice], entry->enabled != 0);
                choice = func_002A77E0(6);
                entry = D_L00_00262570 + D_00139568.index;
                cb = func_002AAFA0(b.v[choice], entry->enabled != 0);
            }
            t0 = func_002A7820(12, 17);
            t1 = func_002A7820(21, 25);
            func_002BBCB0(&p, &v, ca, cb, 400000.0f, t0, t1, speed, 0, 0);
        }
    }
    if (distance > 9.0f) {
        func_L00_003A0DA0(D_00189E20.owner, &p, &v, 12, 127, 127, 127, 32, one * 4.0f);
        r = 127;
        g = 32;
        blue = 0;
        func_002AAF40(&r, &g, &blue, D_L00_00262570[D_00139568.index].enabled != 0);
        func_L00_003A0DA0(D_00189E20.owner, &p, &v, 20, r, g, blue, 32, one * 4.0f);
    }
    c0 = 127;
    c1 = 63;
    c2 = 0;
    func_002AAF40(&c0, &c1, &c2, D_L00_00262570[D_00139568.index].enabled != 0);
    func_L00_003A0DA0(D_00189E20.owner, &p, &v, 17, c0, c1, c2, 48, one * 4.0f);
    c0 = 96;
    c1 = 16;
    c2 = 0;
    func_002AAF40(&c0, &c1, &c2, D_L00_00262570[D_00139568.index].enabled != 0);
    func_L00_003A0DA0(D_00189E20.owner, &p, &v, 22, c0, c1, c2, 64, one * 3.5f);
    c0 = 32;
    c1 = 0;
    c2 = 0;
    func_002AAF40(&c0, &c1, &c2, D_L00_00262570[D_00139568.index].enabled != 0);
    func_L00_003A0DA0(D_00189E20.owner, &p, &v, 24, c0, c1, c2, 32, one * 3.0f);
}
