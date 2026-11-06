/* func_PAL_L05_003D3098, the PAL copy of func_L05_003CF350: the same C, where rename func_002BDCE8 becomes func_PAL_002BE9A8. */
#include "common.h"
extern char *func_002A9640(char *, unsigned int, int);
extern int func_L05_003CFC28(int);
extern float D_L05_001AFB68[] SDATA(D_L05_001AFB68);
extern int D_L05_001AFB80[] SDATA(D_L05_001AFB80);
extern int D_L05_001AFB98[] SDATA(D_L05_001AFB98);
extern int D_L05_001AFBB0[] SDATA(D_L05_001AFBB0);
extern int D_L05_001AFBC8[] SDATA(D_L05_001AFBC8);
extern float D_L05_001AFBDC __attribute__((sda));
extern float D_L05_001AFBE0 __attribute__((sda));
extern float D_L05_001AFBE8 __attribute__((sda));
extern float D_L05_001AFBEC __attribute__((sda));
extern char D_L05_001B96C0[];
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern float func_002A78D8(float, float);
extern char *func_L05_003CEFA0(char *, void *, int);
extern void func_002AF000(void *, float, float, float);
extern int func_002A7820(int, int);
extern int func_001163B0(void);
extern char *func_PAL_002BE9A8(void *, int, float, float, float, float, void *, int, int);
/* Spawns three particle bursts at obj when func_002A9640 returns a record, unless the record is
   type 1 and obj is class 0x956. Returns 1 if it spawned them. */
int func_PAL_L05_003D3098(char *obj)
{
    float pos[4], base[4], offset[4], center[4], vel[4];
    unsigned char *r;
    char *p, *s;
    int index, i, j, k, big;
    float radius, speed, angle, count, spread, size, a, b;
    int full;

    r = func_002A9640(obj, 0x230000, 0);
    full = 255;
    *(unsigned char *)(obj + 0xa8) = full;
    if (r) {
        unsigned short id = *(unsigned short *)(obj + 0xaa);

        if ((unsigned char)r[0x28] != 1 || (short)id != 0x956) {
            index = func_L05_003CFC28((short)id);
            {
                int kind = D_L05_001AFB80[index];

                radius = D_L05_001AFB68[index] * 0.5f;
                speed = D_L05_001AFBDC * 0.020000001f;
                if ((unsigned char)r[0x28] == 0)
                    speed *= 3.0f;
                func_00282F20(base, r + 0x10, speed);
                if ((unsigned char)r[0x28] != 0 && func_002A77E0(4) == 0) {
                    func_00282CF0(offset, obj + 0x10, D_L05_001B96C0);
                    func_00282DD8(center, offset, D_L05_001B96C0 + 0x250);
                    func_002ACEC0(offset, center, offset, func_002A7940());
                    func_00282F20(offset, offset, D_L05_001AFBE0 * 0.020000001f);
                    func_00282CC0(base, base, offset);
                }
                for (i = 0; i < D_L05_001AFBC8[index]; i++) {
                    char *p, *s;
                    float size, a, b;

                    pos[0] = *(float *)(obj + 0x10) + func_002A78D8(0.0f, radius);
                    pos[1] = *(float *)(obj + 0x14) + func_002A78D8(0.0f, radius);
                    pos[2] = *(float *)(obj + 0x18) + func_002A78D8(0.0f, radius);
                    p = func_L05_003CEFA0(obj, pos, kind);
                    if (p) {
                        s = *(char **)(p + 0x68);
                        size = D_L05_001AFBDC * 0.010000001f;
                        a = func_002A7940();
                        b = func_002A7940();
                        func_002AF000(center, size, a, b);
                        func_00282CC0(s + 0x10, base, center);
                        p[0x20] = 2;
                    }
                }
            }
            {
                int kind = 0x955;

                size = D_L05_001AFBDC * 0.010000001f;
                if (*(short *)(obj + 0xaa) == 0x956) {
                    size += size;
                    kind = 0x971;
                }
                for (j = 0; j < D_L05_001AFB98[index]; j++) {
                    pos[0] = *(float *)(obj + 0x10) + func_002A78D8(0.0f, radius);
                    pos[1] = *(float *)(obj + 0x14) + func_002A78D8(0.0f, radius);
                    pos[2] = *(float *)(obj + 0x18) + func_002A78D8(0.0f, radius);
                    p = func_L05_003CEFA0(obj, pos, kind);
                    big = 0x956;
                    if (p) {
                        s = *(char **)(p + 0x68);
                        if (*(short *)(obj + 0xaa) == big) {
                            func_00282CF0(center, pos, obj + 0x10);
                            func_00282F20(center, center, size);
                        } else {
                            a = func_002A7940();
                            b = func_002A7940();
                            func_002AF000(center, size, a, b);
                        }
                        func_00282CC0(s + 0x10, base, center);
                        p[0x20] = 3;
                    }
                }
            }
            spread = D_L05_001AFB68[index] * D_L05_001AFBEC;
            angle = D_L05_001AFBE8 * 0.020000001f;
            count = (float)D_L05_001AFBB0[index];
            qcopy(center, obj + 0x10);
            if ((unsigned char)r[0x28] == 0) {
                func_00282F20(base, D_L05_001B96C0 + 0x230, speed * 0.5f);
                func_00282F20(vel, D_L05_001B96C0 + 0x230, 0.5f);
                func_00282CC0(center, center, vel);
                angle = 0.060000002f;
                if (*(short *)(obj + 0xaa) == 0x955) {
                    count = 40.0f;
                    radius = 0.1f;
                    angle = 0.040000003f;
                    spread *= 3.0f;
                }
            } else
                qzero(base);
            {
                int color = full | 0x7fffff00;

                for (k = 0; (float)k < count; k++) {
                    int spin;

                    pos[0] = center[0] + func_002A78D8(0.0f, radius);
                    pos[1] = center[1] + func_002A78D8(0.0f, radius);
                    pos[2] = center[2] + func_002A78D8(0.0f, radius);
                    a = func_002A7940();
                    b = func_002A7940();
                    func_002AF000(vel, angle, a, b);
                    func_00282CC0(vel, vel, base);
                    spin = func_002A7820(-3, 3);
                    p = func_PAL_002BE9A8(pos, spin, 0.0f, 1.0f, 1.0f, spread * 210000.0f, vel, color, 0);
                    if (p) {
                        *(short *)(p + 0xa) = 100;
                        s = p + 0x20;
                        p[8] = func_002A77E0(255);
                        if ((unsigned short)(*(unsigned short *)(obj + 0xaa) - 0x953) < 3)
                            p[3] = (func_001163B0() & 1) ? 0x44 : 0x48;
                        else
                            p[3] = 0x44;
                        *(int *)(s + 4) = 2;
                        s[0xa] = 127;
                        s[0xb] = p[0xa];
                    }
                }
            }
            return 1;
        }
    }
    return 0;
}
