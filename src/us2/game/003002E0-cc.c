/* func_US2_003002E0, the USA v2.00 copy of func_002FF450: the same C, where rename func_00288508 becomes func_US2_00288F30. */
#include "common.h"

/* The object preview's sequencer (func_US2_003002E0), in a unit of its own: it is
   built with -g, whose line label before each division keeps the two padding
   nops retail has in front of div.s, and its jump table is the unit's only
   .rodata. */

/* State of the object preview (PreviewState in 002FC8D0.c), seen whole. It is
   a small-data object: fields past the first halfword are offsets from it
   (two-word macros that never fill a delay slot), while the state halfword is
   a one-word access that the assembler turns into a $gp store in a delay
   slot. */
typedef struct {
    short state;              /* 0x00 */
    short frames;             /* 0x02 */
    float rate;               /* 0x04 */
    short s08;                /* 0x08 */
    char pad0A[0x0D - 0x0A];
    unsigned char b0D;        /* 0x0D */
    short s0E;                /* 0x0E */
    char pad10[0x30 - 0x10];
    char *object;             /* 0x30 */
    unsigned char phase;      /* 0x34 */
    unsigned char spin;       /* 0x35 */
    short alpha;              /* 0x36 */
} PreviewState;

/* The camera (PreviewCameraPrefix in 002FC8D0.c). */
typedef struct {
    char reserved000[0x140];
    float position[4];        /* 0x140 */
    float rotation[4];        /* 0x150 */
    char reserved160[0x370 - 0x160];
    float forward[4];         /* 0x370 */
} PreviewCamera;

/* The subtitle owner (SubtitleOwnerUpdate in 00289178.c). */
typedef struct {
    char pad00[0x6C];
    short id;
    char pad6E[4];
    short state;
} PreviewSubtitleOwner;

extern PreviewState D_001B2310 __attribute__((sda));
extern PreviewCamera D_001B5200;
extern PreviewSubtitleOwner D_001A63A8;
extern int D_001AD7E4 SDATA(D_001AD7E4) __attribute__((sda));
extern int D_001AD7E8 SDATA(D_001AD7E8) __attribute__((sda));
extern int D_001AD7F8 SDATA(D_001AD7F8) __attribute__((sda));
extern int D_001AD7FC SDATA(D_001AD7FC) __attribute__((sda));
extern int D_001AD800 SDATA(D_001AD800) __attribute__((sda));
extern int D_001AD804 SDATA(D_001AD804) __attribute__((sda));
extern float D_001B90F0;
extern short D_0018A000;

extern int func_00282978(short *);
extern int func_002B6D28(void);
extern void func_00283360(float *);
extern void func_0027AB40(void);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_0027D098(void (*)(void), int);
extern void func_002FFCF8(void);
extern void func_002FFFE0(void);
extern void func_002FF3F8(void);
extern void func_002FF968(char *);
/* Retail passes the object in $a0; the matched body does not read it. */
extern void func_002FFD78(char *);
extern char *func_002FFB68(char *);
extern void func_00287EB0(int);
extern void func_US2_00288F30(int);
extern void func_002AD860(int);
extern int func_002B49E0(int, int, int, int, int);

/* Steps the object preview through its eight states: wait for the subtitle
   owner (at most 181 frames), set up the camera and the object, show it,
   fade, release it and hand control back. */
void func_US2_003002E0(void)
{
    char *object, *current;
    float angle, sine, tangent, zero;

    switch (D_001B2310.state) {
    case 0:
        if (func_00282978(&D_001B2310.frames)
            && !(D_001AD7E4 && (D_001A63A8.state != 3 || D_001A63A8.id >= 6000)
                 && D_001AD7E8++ < 181)) {
            func_002B6D28();
            D_001B5200.position[0] = 25.0f;
            D_001B5200.position[2] = 900.0f;
            D_001B5200.position[1] = 25.0f;
            D_001AD7E4 = 0;
            D_001AD7E8 = 0;
            func_00283360(D_001B5200.forward);
            object = D_001B2310.object;
            zero = 0.0f;
            D_001B5200.rotation[2] = zero;
            D_001B5200.rotation[1] = zero;
            D_001B5200.rotation[0] = zero;
            D_001B2310.state = 1;
            D_001B2310.frames = D_001AD7FC;
            D_001B2310.s0E = 0;
            qcopy(object + 0xF0, D_001B5200.rotation);
            if (D_001B2310.spin)
                *(float *)(object + 0xF4) = func_00283B98(*(float *)(object + 0xF4), -1.5707964897155762f);
            angle = 0.5621705651283264f;
            sine = func_00283198(angle);
            tangent = sine / func_00283180(angle);
            D_001B90F0 = tangent;
            func_0027AB40();
            *(unsigned short *)(object + 0x34) &= ~0x41;
        } else {
            func_0027D098(func_002FFCF8, 0);
        }
        break;
    case 1:
        func_002FF968(D_001B2310.object);
        if (func_00282978(&D_001B2310.frames)) {
            D_001B2310.frames = D_001AD800;
            D_001B2310.rate = 1.0f / func_00283CE0(D_001B2310.frames);
            D_001B2310.state = 2;
            D_001B2310.phase = 0;
        }
        break;
    case 2:
        current = D_001B2310.object;
        func_002FF968(current);
        func_002FFD78(current);
        if (func_00282978(&D_001B2310.frames)) {
            D_001B2310.frames = 2;
            D_001B2310.state = 3;
            D_001B2310.alpha = 128;
            func_0027D098(func_002FFFE0, 0);
        }
        break;
    case 3:
        current = D_001B2310.object;
        func_0027D098(func_002FFFE0, 0);
        if (func_00282978(&D_001B2310.frames)) {
            D_001B2310.frames = 12;
            D_001B2310.state = 4;
            D_001B2310.object = func_002FFB68(current);
        }
        break;
    case 4:
        if (D_001B2310.object)
            func_002FF968(D_001B2310.object);
        func_0027D098(func_002FFFE0, 0);
        D_001B2310.alpha = func_00283CF0(func_00283CE0(D_001B2310.frames) * (1.0f / 12.0f) * 128.0f);
        if (func_00282978(&D_001B2310.frames)) {
            D_001B2310.state = 5;
            D_001B2310.frames = D_001AD804;
            D_001B2310.alpha = 0;
        }
        break;
    case 5:
        if (D_001B2310.object)
            func_002FF968(D_001B2310.object);
        if (func_00282978(&D_001B2310.frames)) {
            D_001B2310.frames = 3;
            D_001B2310.state = 6;
        }
        break;
    case 6:
        if (D_001B2310.object)
            func_002FF968(D_001B2310.object);
        func_0027D098(func_002FFCF8, 0);
        if (func_00282978(&D_001B2310.frames)) {
            D_001B2310.frames = 0;
            D_001B2310.rate = 1.0f / func_00283CE0(D_001AD7F8);
            D_001B2310.b0D = D_001B2310.s0E = 1;
            D_0018A000 = D_001AD7F8 + 5;
            func_002FF3F8();
            D_001B2310.object = 0;
            func_00287EB0(D_001B2310.s08);
            func_US2_00288F30(D_001B2310.s08);
            if (D_001B2310.spin)
                func_002AD860(D_001B2310.s08);
            D_001B2310.state = 7;
        }
        break;
    case 7:
        if (D_001B2310.frames++ >= D_001AD7F8)
            func_002B49E0(0, 2, 0, 0, 0);
        else
            func_0027D098(func_002FFCF8, 0);
        break;
    }
}
