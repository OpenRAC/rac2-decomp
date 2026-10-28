/* functional: high. Hand-written from the assembly (not byte-matched: 25 calls, two loops); same reads, writes and calls in order; fcheck SAME on 4 calls. The third argument to func_00282E80 is passed as retail does. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int Quad __attribute__((mode(TI)));

extern void *D_00214920[];
extern char D_00214970[];
extern char D_00214978[];
extern int D_001A8BB0;
extern int D_001A79F0;
extern int D_001A9BC0;
extern float D_001ACF94;
extern float D_001ACF98;
extern char D_001ACF9C[];
extern char D_001ACF28[], D_001ACF38[], D_001ACF48[], D_001ACF58[], D_001ACF68[], D_001ACF78[], D_001ACF88[];
extern char D_00199E20[];
extern char D_00199EA0[];

extern void func_002E6178(void);
extern float func_002A89A8(void *, int, float);
extern void func_002B41A8(char *, void *, int, int, void *, void *, void *, void *, void *, void *, void *);
extern void func_00282D60(void *, void *, float);
extern int func_00283DB8(void *, float);
extern float func_00282E80(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_0029FC20(char *, int, void *);
extern void func_0029FCC0(char *, int, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_002A10E8(void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_002B44C0(char *, void *, void *);

void func_002E64A0(char *mob)
{
    float v20[4] __attribute__((aligned(16)));
    float v30[4] __attribute__((aligned(16)));
    float v40[12] __attribute__((aligned(16)));
    float v80[4] __attribute__((aligned(16)));
    float v90[4] __attribute__((aligned(16)));
    float vA0[4] __attribute__((aligned(16)));
    void *best = 0;
    int i, t, s0;
    char *e;

    if (D_00214920[0] == 0) {
        func_002E6178();
        if (D_001A8BB0 == 0) {
            float d = func_002A89A8(mob + 0x10, 0, 0.5f);
            if (d != 0.0f)
                *(float *)(mob + 0x18) = d + D_001ACF94;
            D_001ACF98 = *(float *)(mob + 0x18);
        }
        func_002B41A8(mob, D_00214970, 0, 0, D_001ACF58, D_001ACF68, D_001ACF28, D_001ACF88,
                      D_001ACF78, D_001ACF38, D_001ACF48);
    }

    if (D_001A8BB0 == 0) {
        func_00282D60(v20, mob, 0.0009765625f);
        v20[3] = v20[3] + 1.0f;
        if (func_00283DB8(v20, 50.0f) == -1)
            return;
        if (D_001A9BC0 == 0) {
            char *s1 = D_00199EA0;
            char *s5 = mob + 0x10;
            float dist = func_00282E80(s5, s1, v40);
            s0 = 0;
            if (dist < 6.0f) {
                if (*(u8 *)(mob + 0xBC) != 0) {
                    *(Quad *)v20 = *(Quad *)(s1 + 0x60);
                    v20[2] = v20[2] + 2.0f;
                    if (func_002761F8(s1 + 0x60, v20, 0, *(int *)(s1 + 0x2210), 0) == 0) {
                        func_00282CF0(v30, s5, s1);
                        *(int *)&v30[2] = 0;
                        func_00282F20(v30, v30, 0.4f);
                        func_00282CC0(v20, v20, v30);
                        s0 = func_002761F8(s1 + 0x60, v20, 0, *(int *)(s1 + 0x2210), 0) != 0;
                    } else {
                        s0 = 1;
                    }
                } else {
                    *(Quad *)v20 = *(Quad *)(s1 + 0x60);
                    v20[2] = v20[2] + 2.0f;
                    s0 = func_002761F8(s1 + 0x60, v20, 0, *(int *)(s1 + 0x2210), 0) != 0;
                }
            }
            *(u8 *)(mob + 0xBC) = s0;
            if (s0)
                func_002AA548(D_00214978, D_001ACF9C, D_001ACF98 + 0.75f, 0.0005555555690079927f, 0.0005555555690079927f, 0.01666666753590107f);
            else
                func_002AA548(D_00214978, D_001ACF9C, D_001ACF98, 0.0005555555690079927f, 0.0005555555690079927f, 0.01666666753590107f);
        }
    }
    func_0029FC20(mob, 1, v40);
    func_0029FCC0(mob, 1, v20);

    if (D_00214920[0] != 0) {
        i = 0;
        do {
            e = (char *)D_00214920[i];
            if (*(u16 *)(mob + 0x34) & 1)
                *(u16 *)(e + 0x34) = *(u16 *)(e + 0x34) | 0x41;
            else
                *(u16 *)(e + 0x34) = *(u16 *)(e + 0x34) & 0xFFBE;
            e = (char *)D_00214920[i];
            *(Quad *)v30 = *(Quad *)(e + 0x10);
            *(Quad *)v80 = *(Quad *)(e + 0xF0);
            *(Quad *)(e + 0x10) = *(Quad *)(mob + 0x10);
            for (t = 0; t < 3; t++) {
                e = (char *)D_00214920[i];
                *(float *)(e + 0xC0 + t * 16) = v40[t * 4];
                *(float *)(e + 0xC4 + t * 16) = v40[t * 4 + 1];
                *(float *)(e + 0xC8 + t * 16) = v40[t * 4 + 2];
            }
            if (D_001A8BB0 == 2 && D_001A79F0 == 5) {
                e = (char *)D_00214920[i];
                *(Quad *)vA0 = 0;
                vA0[0] = -0.33719998598098755f;
                vA0[1] = -0.5364000201225281f;
                vA0[2] = -1.79489004611969f;
                func_00283098(vA0, vA0, e + 0xC0);
                func_00282CC0(v90, v20, vA0);
                *(Quad *)(e + 0x10) = *(Quad *)v90;
            }
            e = (char *)D_00214920[i];
            func_002AB6D8(e + 0xC0, e + 0xF0);
            func_002A10E8(e);
            e = (char *)D_00214920[i];
            {
                char *obj = *(char **)(e + 0x68);
                func_00282CF0(v90, e + 0x10, v30);
                func_002AD6F0(obj + 0x20, v90, v80, (char *)D_00214920[i] + 0xF0);
            }
            if (*(int *)(D_00199E20 + 0x340) >= 2) {
                if (*(char **)(D_00199E20 + 0x33C) == (char *)D_00214920[i])
                    best = D_00199EA0;
            }
            if (D_001A8BB0 == 0) {
                if (*(int *)(mob + 0x98) != 0) {
                    e = (char *)D_00214920[i];
                    *(int *)(e + 0x98) = *(int *)(*(char **)(e + 0x24) + 0x10);
                }
            } else {
                e = (char *)D_00214920[i];
                *(int *)(e + 0x98) = 0;
                *(int *)(mob + 0x98) = 0;
            }
            i++;
        } while (D_00214920[i] != 0);
    }
    if (D_001A8BB0 == 0)
        func_002B44C0(mob, D_00214970, best);
}
