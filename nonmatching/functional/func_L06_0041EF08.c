/* functional: medium. Written from the assembly: plain floats (constants taken from the immediates), 16-byte copies as four ints; the first call passes the moby in a0 as retail does (it reads that register unchanged). */

extern char D_L06_001B9840[];               /* a point the moby's distance is taken to */

extern int func_L02_0032E508(unsigned char *, int, unsigned char *, int);
extern void func_0026FEB8(char *, ...);
extern float func_002A78D8(float, float);
extern int func_002A7820(int, int);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_00283CF0(float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L06_0041F798(char *);
extern int func_002B3BA8(void *, int, void *, int, float, float);
extern void func_002A6C58(char *, int, int);
extern void func_002AC728(char *a0, char *a1, float f12, float f13, int a2);
extern void func_0029F338(void *);

/* Per-frame update of a moby (`m`, its variables at +104). On its first frame (state 0) it
   asks func_L02_0032E508 for its areas (stored at +1152, printed), fills the variables (a copy
   of the position, sizes, speeds and angles, one random angle from func_002A78D8 and one random
   value from func_002A7820) and starts animation 1 with randomised timings. Every frame it dies
   (byte 111 = 22) when close to a fixed point, reacts to func_002B0ED8's hit result (10 in byte 55
   sets byte 215; 5 resets the slope pair at +240) and calls func_L06_0041F798, refreshes the two
   ints at +552/+556, and when it is low enough (y < 48) plays the effect and removes itself. */
void func_L06_0041EF08(char *m)
{
    char *vars = *(char **)(m + 104);
    int hit;

    if (m[32] == 0) {
        int areas;
        int i;
        float angle;
        int number;

        areas = func_L02_0032E508((unsigned char *)m, *(int *)(vars + 560), (unsigned char *)(vars + 608), 16);
        *(int *)(vars + 1152) = areas;
        func_0026FEB8("%d areas\n", areas);
        for (i = 0; i < 4; i++) {
            ((int *)(vars + 1120))[i] = ((int *)(m + 16))[i];
        }
        vars[212] = 0;
        *(short *)(vars + 38) = 0;
        vars[114] = 16;
        *(float *)(vars + 1132) = *(float *)(m + 248);
        vars[118] = 14;
        vars[119] = 15;
        *(float *)(vars + 124) = 0.200000018f;
        *(float *)(vars + 128) = 0.125f;
        *(float *)(vars + 132) = 0.00555555569f;
        *(float *)(vars + 136) = 0.00972222257f;
        *(float *)(vars + 148) = 0.5f;
        *(float *)(vars + 156) = 0.4f;
        vars[204] = 7;
        vars[205] = 12;
        vars[206] = 3;
        vars[207] = 5;
        vars[210] = 10;
        vars[211] = 17;
        *(float *)(vars + 1452) = (float)(int)(unsigned char)vars[52];
        vars[41] = 1;
        *(float *)(vars + 48) = 0.75f;
        vars[112] = 15;
        *(int *)(vars + 168) = 3;
        vars[113] = 12;
        *(float *)(vars + 144) = 0.5f;
        vars[40] = 1;
        *(float *)(vars + 140) = 0.00416666688f;
        angle = func_002A78D8(10.0f, 25.0f);
        *(int *)(vars + 1144) = 0;
        number = func_002A7820(0, 95);
        *(float *)(vars + 1148) = angle * 0.017453294f;
        *(int *)(vars + 1176) = -1;
        *(int *)(vars + 1440) = *(short *)(vars + 1168);
        *(short *)(vars + 588) = number;
        for (i = 0; i < 4; i++) {
            ((int *)(vars + 1456))[i] = 0;
        }
        func_002A7750(m, 1, 0);
        if (m[67] != 1) {
            func_002A7470(m, 1, 0, 0);
        }
        vars[72] = (char)func_00283CF0(20.0f);
        vars[74] = (char)func_00283CF0(8.0f);
        if (*(short *)(vars + 1170) != 0) {
            if (m[67] != 3) {
                func_002A7470(m, 3, 0, 0);
            }
            vars[72] = (char)func_00283CF0(20.0f);
            vars[74] = (char)func_00283CF0(24.0f);
        }
    }

    if (m[49] != 0) {
        if (func_00282E48(m + 16, D_L06_001B9840) < 24.0f) {
            func_002A93B0(m);
            m[111] = 22;
        }
    }

    hit = func_002B0ED8(m, vars + 96, 0);
    if (hit != 0) {
        if ((unsigned char)vars[55] == 10) {
            vars[215] = 1;
        }
        if (hit == 5) {
            *(int *)(vars + 240) = 0;
            *(float *)(vars + 244) = 0.837758183f;
        }
        func_L06_0041F798(m);
        m[168] = (char)255;
    }

    *(int *)(vars + 552) = func_002B3BA8(m, *(int *)(vars + 544), 0, 0, *(float *)(vars + 576), 10.0f);
    *(int *)(vars + 556) = func_002B3BA8(m, *(int *)(vars + 548), 0, 0, *(float *)(vars + 580), 10.0f);

    if (*(float *)(m + 24) < 48.0f) {
        func_002A6C58(m, 0, 3);
        func_002AC728(m, m + 16, 1.0f, 13.0f, -1);
        func_0029F338(m);
    }
}
