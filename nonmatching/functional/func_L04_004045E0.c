/* functional: medium. Written from the assembly, the jump table (states 0 to 4) read from the program's bytes; plain floats and local arrays for the three quadword vectors; the 16-byte copies are 4-int copies. */

extern char D_L04_001B9680[];               /* a point the object's distance is taken to */
extern char D_L04_001BFAF0[];               /* a fallback position (4 floats) */
extern char D_L04_001B0630[];               /* three 4-float vectors */

extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
extern int func_00277258(void *, float, int, void *);
extern void func_L04_00402C88(char *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_L04_00403530(unsigned char *, unsigned char *);
extern void func_L04_004027B0(unsigned char *, unsigned char *);
extern void func_L04_00400EE0(unsigned char *, unsigned char *);
extern void func_L04_004044B8(unsigned char *, unsigned char *);
extern void func_L04_00404100(unsigned char *, unsigned char *);
extern int func_L04_00400AB0(void *, void *, int);
extern float func_00283CE0(int);
extern void func_002C96F8(float, float, void *, int *, float *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282DB0(void *, void *);
extern void func_L04_00410518(void *object, void *state, int *link, int *point, float *result, int mode);

static void copy16_004045E0(void *dst, void *src)
{
    ((int *)dst)[0] = ((int *)src)[0];
    ((int *)dst)[1] = ((int *)src)[1];
    ((int *)dst)[2] = ((int *)src)[2];
    ((int *)dst)[3] = ((int *)src)[3];
}

/* Per-frame update of a route-following object (`m`, its variables at +104). It first sets its
   bounds from its type, and when it is close to the fixed point calls func_002A93B0 and marks
   byte 111. Then by state byte +32: 0 sets up (position, three scaled vectors, six random
   floats) and moves to 1; 1 does nothing; 2 runs the five movement steps unless the rider is in
   state 2 with byte 188 clear; 3 follows the route, counting frames at +150 and, after 300 and
   once it is near, hands over to func_L04_00410518 and state 2; 4 clears the link words and goes
   to 1. */
void func_L04_004045E0(unsigned char *m)
{
    unsigned char *vars = *(unsigned char **)(m + 104);
    unsigned char *p;
    float scratch[12];
    int i;

    m[48] = 255;
    *(short *)(m + 50) = 127;
    *(float *)(m + 44) = *(float *)(*(unsigned char **)(m + 36) + 36) * 0.25f;
    if (m[49] != 0) {
        if (func_00282E48(m + 16, D_L04_001B9680) < 9.0f) {
            func_002A93B0((char *)m);
            m[111] = 8;
        }
    }

    p = *(unsigned char **)(vars + 356);
    if (p != 0) {
        if (p[32] == 1) {
            return;
        }
        if (p[32] == 4 || p[32] == 0) {
            return;
        }
        if (p[32] == 2) {
            if ((unsigned int)(p[188] - 5) < 2) {
                *(int *)(vars + 440) = *(int *)(vars + 440) + 1;
            }
        }
    }

    switch (m[32]) {
    case 0: {
        float scale;

        if (func_00277258(m + 16, *(float *)(vars + 144), 4, m) != 0) {
            copy16_004045E0(m + 16, D_L04_001BFAF0);
        }
        copy16_004045E0(vars + 176, m + 16);
        copy16_004045E0(vars + 192, m + 240);
        func_L04_00402C88((char *)m);
        m[32] = 1;
        *(int *)(vars + 48) = 0;
        copy16_004045E0(scratch, D_L04_001B0630);
        copy16_004045E0(scratch + 4, D_L04_001B0630 + 16);
        copy16_004045E0(scratch + 8, D_L04_001B0630 + 32);
        *(unsigned short *)(m + 52) = *(unsigned short *)(m + 52) | 0x41;
        m[98] = 1;
        scale = *(float *)(m + 44) / *(float *)(*(unsigned char **)(m + 36) + 36);
        for (i = 0; i < 3; i++) {
            func_00282D30(vars + 512 + i * 16, scratch + i * 4, scale);
        }
        for (i = 0; i < 6; i++) {
            *(float *)(vars + 388 + i * 4) = func_002A7878(0.0f, 1.0f);
        }
        break;
    }
    case 1:
        break;
    case 2:
        p = *(unsigned char **)(vars + 356);
        if (p == 0 || p[32] != 2 || p[188] != 0) {
            func_L04_00403530(m, vars);
            func_L04_004027B0(m, vars);
            func_L04_00400EE0(m, vars);
            func_L04_004044B8(m, vars);
            func_L04_00404100(m, vars);
        }
        break;
    case 3:
        if (*(unsigned short *)(m + 150) == 0) {
            unsigned char *route = *(unsigned char **)(vars + 272);
            int idx = func_L04_00400AB0(m, route, 1);
            float f;

            route = *(unsigned char **)(vars + 272);
            copy16_004045E0(m + 16, route + idx * 16 + 16);
            f = func_00283CE0(idx);
            f = f * *(float *)(route + 28);
            f = f + (*(int *)(vars + 580) != 0 ? 15.0f : 5.0f);
            *(float *)(vars + 168) = f;
            route = *(unsigned char **)(vars + 272);
            func_002C96F8(f, *(float *)(route + 28), route, (int *)(vars + 276), (float *)(vars + 280), vars + 240);
        }
        if (*(unsigned short *)(m + 150) >= 300) {
            p = *(unsigned char **)(vars + 356);
            if (p != 0) {
                unsigned char *rvars = *(unsigned char **)(p + 104);

                func_00282CF0(scratch, m + 16, p + 16);
                if (func_00283DB8(m + 16, 60.0f) == -1) {
                    if (func_00282DB0(scratch, scratch) > 25.0f) {
                        *(unsigned short *)(m + 52) = (*(unsigned short *)(m + 52) & 0xFFBE) | 0x1400;
                        *(int *)(m + 152) = *(int *)(*(unsigned char **)(m + 36) + 16);
                        if (*(unsigned char **)(vars + 140) != 0) {
                            *(unsigned short *)(*(unsigned char **)(vars + 140) + 52) &= 0xFFBE;
                        }
                        func_L04_00410518(m, rvars, (int *)(vars + 288), (int *)(vars + 292),
                                          (float *)(vars + 284), *(int *)(vars + 352));
                        m[32] = 2;
                    }
                }
            }
        }
        *(unsigned short *)(m + 150) = *(unsigned short *)(m + 150) + 1;
        break;
    case 4:
        *(int *)(m + 72) = 0;
        if (*(unsigned char **)(vars + 140) != 0) {
            *(int *)(*(unsigned char **)(vars + 140) + 72) = 0;
        }
        m[32] = 1;
        break;
    default:
        break;
    }
}
