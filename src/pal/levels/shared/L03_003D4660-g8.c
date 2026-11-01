#include "include_asm.h"

#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern int D_L03_001A8F00;
extern char D_L03_001A8F20[] __attribute__((sda)), D_L03_001BFDE0[], D_00188660[];
extern float D_L03_001B0590 __attribute__((sda)), D_L03_001B0594 __attribute__((sda));
extern void func_0029F338(void *);
extern int func_002AD0E0(void *,void *,void *,void *,void *,void *);
extern void func_00282CF0(void *,void *,void *),func_002AFDD8(void *,void *,void *,int);
extern void func_00282D08(void *,void *,void *,float),func_00282CC0(void *,void *,void *);
extern float func_002AA2E8(void *,float,float);
extern void func_00283098(void *,void *,void *);
extern void func_002A7750(void *,int,int),func_002A8C00(void *,void *,int,void *,float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_002A7940(void),func_002A7878(float,float),func_00283180(float),func_00283198(float);
extern void func_PAL_L03_003D5148(void *,void *,void *),func_002A7A00(void *,float,float);
extern int func_002A77E0(int),func_002E5CF8(int,int,void *),func_00282948(void *);
extern void func_002E59F8(int),func_L00_002E6CF0(void *,void *),func_L03_003D0AE0(void *);

/* Interpolates the emitter position, keeps it relative to its attachment,
 * emits particles while active, and releases its sound and object after fading. */
void func_PAL_L03_003D4660(char *m) {
    float tmp[4], a[4], b[4], hit[12], pos[4], vel[4];
    char *v = P(m, 0x68), *p, *e;
    float angle, speed;

    if (D_L03_001A8F00 == 2) {
        func_0029F338(m);
        return;
    }
    p = m + 0x10;
    if (P(v, 0x40)) {
        func_002AD0E0(m, P(v, 0x40), p, m + 0xF0, p, m + 0xF0);
        func_00282CF0(p, p, P(v, 0x40) + 0x10);
        func_002AFDD8(P(v, 0x40), p, p, 0);
    }
    func_00282D08(tmp, v, v + 0x10, F(v, 0x20));
    func_00282CC0(p, p, tmp);
    func_002AA2E8(v + 0x20, 1.0f, F(v, 0x24));
    if (P(v, 0x40)) {
        func_00283098(p, p, P(v, 0x40) + 0xC0);
        func_00282CC0(p, p, P(v, 0x40) + 0x10);
    }
    switch ((unsigned char)m[0x20]) {
    case 0:
        I(v, 0x3C) = -1;
        if (F(v, 0x20) > 0.5f)
            func_002A7750(m, 1, -1);
        break;
    case 1:
        qcopy(a, p);
        qcopy(b, p);
        b[2] -= F(v, 0x20) * 5.0f;
        func_002A8C00(hit, m, 0x10001, D_L03_001A8F20, (float)I(v, 0x38));
        if (func_002761F8(a, b, 0, m, hit) && !P(v, 0x40)) {
            angle = func_002A7940();
            speed = func_002A7878(0, 0.5f) * (0.020000001f);
            pos[0] = func_00283180(angle) * speed;
            pos[1] = func_00283198(angle) * speed;
            pos[2] = 0;
            pos[2] = func_002A7878(1, 2) * (0.020000001f);
            func_PAL_L03_003D5148(m, D_L03_001BFDE0, pos);
        }
        if (!P(v, 0x40) && !func_002A77E0(2)) {
            qcopy(pos, p);
            pos[2] -= func_002A7878(0, 5);
            func_002A7A00(vel, 0, 0.040000003f);
            func_PAL_L03_003D5148(m, pos, vel);
        }
        e = (char *)(I(v, 0x3C) * 0x70);
        e = (char *)((int)e + (int)D_00188660);
        if (P(e, 0x88) != m || !((unsigned char *)e)[0x74])
            I(v, 0x3C) = func_002E5CF8(0, 4, m);
        if (F(v, 0x34) < 1)
            func_002AA2E8(v + 0x34, 1, 0.080000006f);
        if (func_00282948(v + 0x28))
            func_002A7750(m, 2, -1);
        break;
    case 2:
        func_002AA2E8(v + 0x34, 0, 0.040000003f);
        if (F(v, 0x34) <= 0) {
            int handle = I(v, 0x3C);
            if (handle != -1) {
                int offset = handle * 0x70;
                char *slot = D_00188660 + offset;
                if (P(slot, 0x88) == m && ((unsigned char *)slot)[0x74])
                    func_002E59F8(handle);
            }
            I(v, 0x3C) = -1;
            func_0029F338(m);
            return;
        }
        break;
    }
    F(v, 0x2C) += D_L03_001B0590 * (0.020000001f);
    if (F(v, 0x2C) > 1)
        F(v, 0x2C) -= 1;
    else if (F(v, 0x2C) < 1)
        F(v, 0x2C) += 1;
    F(v, 0x30) += D_L03_001B0594 * (0.020000001f);
    if (F(v, 0x30) > 1)
        F(v, 0x30) -= 1;
    func_L00_002E6CF0(func_L03_003D0AE0, m);
}
