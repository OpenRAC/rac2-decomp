/* functional: medium. Written from the assembly: plain floats (constants read from the immediates), 16-byte copy as four ints; the debug text printed for a moby with no group is the retail string. */

extern int D_L06_001B2838;                  /* highest group number */
extern char *D_L06_001B2480;                /* table of 48-byte records */
extern float D_L06_001B1090;
extern char D_L06_001B9840[];               /* a point the moby's distance is taken to */

extern void func_0026FEB8(char *, ...);
extern void func_00282A28(void);
extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L06_00443E88(unsigned char *);
extern void func_L06_00443F30(char *);
extern void func_002A6C58(char *, int, int);
extern void func_002AC728(char *a0, char *a1, float f12, float f13, int a2);
extern void func_0029F338(void *);
extern int func_002B3BA8(void *, int, void *, int, float, float);

/* Per-frame update of a moby (`m`, its variables at +104). On its first frame (state 0) it
   checks its group number, sets up the variables (a copy of the position, the sizes, angles and
   timings, one random angle and one random value) and picks the starting animation. Every frame
   it dies (byte 111 = 22) when close to a fixed point, runs the two follow-up routines when
   func_002B0ED8 reports hits, and when it is low enough (y < 48) plays the effect and removes
   itself, otherwise refreshes the short at +788. */
void func_L06_00443A38(char *m)
{
    char *vars = *(char **)(m + 104);
    int hits;

    if (m[32] == 0) {
        char *rec;
        int i;

        if (D_L06_001B2838 < (unsigned char)m[33]) {
            func_0026FEB8("Moby 3504: Oh Oh! Somebody decided to place me down in the game, but didn't give me a group\n");
            func_0026FEB8("I will now do horrible things to the game which cause Tony to be here until 4 in the morning.\n");
            func_00282A28();
        }
        m[48] = 64;
        for (i = 0; i < 4; i++) {
            ((int *)(vars + 736))[i] = ((int *)(m + 16))[i];
        }
        *(float *)(vars + 804) = 1.0f;
        vars[72] = (char)func_00283CF0(15.0f);
        vars[74] = (char)func_00283CF0(4.8f);
        *(short *)(vars + 136) = 0;
        vars[96] = 8;
        vars[40] = 3;
        *(float *)(vars + 48) = 0.333f;
        *(float *)(vars + 256) = *(float *)(vars + 804) * 0.6f;
        *(float *)(vars + 268) = 0.5f;
        *(int *)(vars + 312) = *(int *)(vars + 312) | 0x80;
        *(int *)(vars + 152) = 3;
        *(float *)(vars + 264) = 0.5f;
        *(float *)(vars + 132) = 0.2f;
        *(float *)(vars + 140) = 0.4f;
        *(float *)(vars + 308) = 0.05f;
        *(float *)(vars + 260) = *(float *)(vars + 804) * 0.5f;
        *(float *)(vars + 272) = 1.5707964f;
        *(float *)(vars + 304) = 0.5235988f;
        *(float *)(vars + 128) = 0.2f;
        {
            float angle = func_002A78D8(18.0f, 22.0f);

            vars[488] = 7;
            vars[489] = 6;
            *(float *)(vars + 476) = angle * 0.017453294f;
        }
        *(short *)(vars + 482) = 120;
        *(short *)(vars + 484) = 180;
        *(float *)(vars + 468) = 3.0f;
        *(float *)(vars + 464) = D_L06_001B1090 * 0.016666668f;
        rec = D_L06_001B2480 + *(int *)(vars + 528) * 48;
        if (*(short *)(rec + 48) != 0) {
            *(int *)(vars + 316) = **(int **)(rec + 60);
        }
        *(float *)(vars + 808) = func_002A7940();
        if (*(int *)(vars + 532) != 0) {
            *(unsigned short *)(m + 52) = (*(unsigned short *)(m + 52) | 0x41) & 0xEFFF;
            *(int *)(m + 152) = 0;
            func_002A7750(m, 9, 4);
            if (m[67] != 10) {
                func_002A7470(m, 10, 0, 0);
            }
        } else {
            func_002A7750(m, 1, 0);
            if (m[67] != 0) {
                func_002A7470(m, 0, 0, 0);
            }
        }
    }

    if (m[49] != 0) {
        if (func_00282E48(m + 16, D_L06_001B9840) < 24.0f) {
            func_002A93B0(m);
            m[111] = 22;
        }
    }

    hits = func_002B0ED8(m, vars + 80, 0);
    if (hits != 0) {
        func_L06_00443E88((unsigned char *)m);
        if (!(hits < 4)) {
            func_L06_00443F30(m);
        }
    }

    if (*(float *)(m + 24) < 48.0f) {
        func_002A6C58(m, 0, 3);
        func_002AC728(m, m + 16, 1.0f, 13.0f, -1);
        func_0029F338(m);
        return;
    }
    if ((unsigned int)((unsigned char)m[149] - 3) >= 2) {
        *(short *)(vars + 788) = func_002B3BA8(m, *(int *)(vars + 528), 0, 0, 16.0f, 0.0f);
    }
}
