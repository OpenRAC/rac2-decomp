#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(char *arg, int mode, int value);

extern void func_L00_003FF7B8_1(char *arg);

extern void func_L00_003FF890(char *arg);

extern float func_00282E80_3(char *arg, char *table);

extern float func_00282C48_10(float value);

extern void func_002B0A18(int arg, int value);

extern void func_00288308(int arg);

extern void func_002AD860(int arg);

extern void func_0029F338_4(char *arg);

extern char D_00189EA0_2[];

extern unsigned char D_001A7B2E __attribute__((sda));

/* two-state update on a record: state 0 marks a byte with 255 and either runs a shared two-call teardown when a global latch byte is set and a sub-object field is non-zero, or plays a mode/value pair plus a call; state 1 runs a setup call and two float queries against a stored table and, when both are below 2.0, plays three fixed calls and either tears down or writes 120 into a sub-object field */
void func_L00_003FFA70(char *arg)
{
    int *object = *(int **)(arg + 104);
    unsigned char state = *(unsigned char *)(arg + 32);

    switch (state) {
    case 0:
        *(unsigned char *)(arg + 48) = 255;
        if (D_001A7B2E != 0 && object[17] != 0) {
            func_0029F338_4((char *)object[17]);
            func_0029F338_4(arg);
            return;
        } else {
            func_002A7750(arg, 1, -1);
            func_L00_003FF7B8_1(arg);
        }
        break;
    case 1:
        func_L00_003FF890(arg);
        if (func_00282E80_3(arg + 16, D_00189EA0_2) < 2.0f) {
            if (func_00282C48_10(*(float *)(arg + 24) - *(float *)(D_00189EA0_2 + 8)) < 2.0f) {
                func_002B0A18(4658, -1);
                func_00288308(54);
                func_002AD860(54);
                if (object[17] != 0) {
                    func_0029F338_4((char *)object[17]);
                    func_0029F338_4(arg);
                    return;
                }
                object[16] = 120;
            }
        }
        break;
    }
}

/* func_L00_003FFBA0 is defined in L00_003FFBA0-g8.c. */


/* func_L00_004005B0 is matched in L00_004005B0-g8.c (a -G8 unit built with -frac2-qcopy
   -frac2-qcopy-barrier). */



/* func_L00_00401168 is defined in L00_00401168-basis-g8.c. */

/* func_L00_00401668 is defined in L00_00401668-ground-g8.c. */


/* func_L00_00402068 is defined in L00_003FFA70-ring-g8.c. */

/* func_L00_004029E8 is matched in L00_003FFA70-g8.c. */


extern void func_002FDBD8(void *obj, float f, void *p, void *q);
typedef struct __attribute__((packed)) { unsigned char b[8]; } Blob8;
extern Blob8 D_L00_001B0DB8 __attribute__((nosda));

void func_L00_00402DD8(char *arg)
{
    int *o = *(int **)(arg + 104);
    if (o[9] != 0) {
        if (o[11] == 0) {
            func_002FDBD8(o, 1.0f, (char *)o + 16, 0);
        } else {
            Blob8 tmp = D_L00_001B0DB8;
            func_002FDBD8(o, 1.0f, (char *)o + 16, &tmp);
        }
    }
}

/* func_L00_00402E50 is defined in L00_003FFA70-wander-g8.c. */

/* func_L00_00403730 is defined in L00_00403730.c. */

extern int D_L00_001B2C6C __attribute__((nosda));

extern int D_L00_001B2C30[] __attribute__((sda));

/* clears the 16 words ending at D_L00_001B2C6C, from the top down */
void func_L00_00403BF8(void)
{
    int i;

    for (i = 15; i >= 0; i--)
        D_L00_001B2C30[i] = 0;
}

/* true when none of the 16 words is zero */
int func_L00_00403C30(void)
{
    int i;

    for (i = 0; i < 16; i++) {
        if (D_L00_001B2C30[i] == 0)
            return 0;
    }
    return 1;
}

extern int func_0031A728(int range);
extern void func_L00_00403900(int value);
extern void func_L00_00403C68(int value);

/* func_L00_00403CB8 is matched in its own unit, src/levels/shared/L00_00403CB8.c (default flags). */

extern void func_002EE108(char *a, int *b, char *c);
extern void func_0037F9A0(char *a, char *b);
extern void func_0037E1D8(int a, int *b, int c);
extern int func_002EDD48(char *a);
extern void func_002E6EF8(void (*f)(char *), char *arg);
extern void func_0037E1B8(int a);
extern void func_00310440(char *arg);
extern void func_L00_00404168(char *arg);
extern void func_L00_00403F90(char *arg, void *p);

/* func_L00_00403D58 is matched in L00_003FFA70-qcopy.c (built with -frac2-qcopy
   -frac2-qcopy-barrier). */

/* func_L00_00403F90 is matched in L00_00403F90.c. */

/* func_L00_00404168 is matched in L00_00404168-por.c (-frac2-zero-ti-por). */

extern void func_L00_00418730(void *pos, int a, int b, int c, int d, int e, int f, int g, int h,
                              int k, float scale);
extern float func_002A7878(float lo, float hi);
extern float func_002A7940(void);
extern float func_002A78D8(float a, float b);
extern int func_002A7820(int lo, int hi);
extern void func_002AF000(void *out, float x, float y, float z);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00282CC0(void *out, void *a, void *b);
extern void func_00282F20(void *out, void *a, float scale);
extern void func_L00_0033E888(void *pos, void *velocity, float speed, float size,
                              unsigned int colour, unsigned int colour2, int life, int a, int b,
                              int c, int d);
extern char D_L00_001B8DC0[];

/* one func_L00_00418730 effect at pos, then two func_L00_0033E888 particles with random
   velocities; before each, pos moves 0.3 of the way towards D_L00_001B8DC0 (FastVecSub,
   scale, FastVecAdd) */
void func_L00_00404368(float *pos, int unused, int mode)
{
    float velocity[4], offset[4], point[4];
    float pitch, heading, speed;
    int i;

    func_L00_00418730(pos, 0, 15, 10, 0, 20, 0, 0, 1, 0, 0.1f);
    for (i = 0; i < 2; i++) {
        pitch = func_002A7878(-0.9599312f, -1.3962636f);
        heading = func_002A7940();
        speed = func_002A7878(0.0f, 0.5f);
        func_002AF000(velocity, speed * 0.016666668f, heading, pitch);
        func_00282CF0(offset, D_L00_001B8DC0, pos);
        func_00282F20(offset, offset, 0.3f);
        func_00282CC0(pos, pos, offset);
        speed = func_002A7878(25000.0f, 50000.0f);
        point[0] = pos[0] + func_002A78D8(0.0f, 0.02f);
        point[1] = pos[1] + func_002A78D8(0.0f, 0.02f);
        point[2] = pos[2] + func_002A78D8(0.0f, 0.02f);
        if (mode)
            func_L00_0033E888(point, velocity, speed, 0.1f, 0x78ffffff, 0x101e1e1e,
                              func_002A7820(10, 20), 1, 1, -1, 1);
        else
            func_L00_0033E888(point, velocity, speed, 0.1f, 0x78ffffff, 0x101e1e1e,
                              func_002A7820(25, 60), 1, 1, -1, 1);
    }
}

/* func_L00_004045E8 is defined in L00_004045E8.c. */

/* func_L00_00404B48 is defined in L00_00404B48-g8.c. */

extern TI128 D_L00_001BF220;
extern void func_00310440(char *arg);
extern int func_002DE4B0(void *a, void *b, int c, void *d, int e);
extern void func_0035F450(int a, int b, void *c, int d);

/* func_L00_00404DD8 is matched in L00_003FFA70-qcopy.c (built with -frac2-qcopy
   -frac2-qcopy-barrier). */

/* func_L00_00404ED8 is defined in L00_00404ED8-g.c. */


/* func_L00_00405808 is defined in L00_00405808-g8.c. */

/* func_L00_00406040 is defined in L00_00406040-g8.c. */



/* func_L00_00406FB0 is defined in L00_00406FB0-g8.c. */


/* func_L00_004079C8 is defined in L00_004079C8-g64.c. */

/* func_L00_00407C18 is defined in L00_00407C18-g64.c. */

/* func_L00_00407E38 is defined in L00_00407E38-g8.c. */

/* func_L00_00408E58 is defined in L00_003FFA70-reaction-g8.c. */

/* shared native body of family af5b3bc3a678ed5c */
void func_L00_00409420(char *object)
{
    char *o = object;
    int *q = *(int **)(o + 104);

    if (*(unsigned char *)(o + 32))
        return;

    q[2] = 64;
    q[4] = 50;
    q[0] = 0;
    q[3] = -1;
    q[5] = 0;
    *(unsigned char *)(o + 32) = 1;
    q[6] = -1;

    *(float *)(o + 44) = *(float *)(*(int *)(o + 36) + 36) * 0.8f;
}


/* func_L00_00409558 is in L00_00409558-g8.c. */
