/* func_PAL_L06_004485C0, the PAL copy of func_L06_00443A38: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0ED8 becomes func_PAL_002B1A50; rename func_L06_00443F30 becomes func_PAL_L06_00448AB8; rename func_002A6C58 becomes func_PAL_002A7650; rename func_002AC728 becomes func_PAL_002AD288. */
#include "common.h"

extern void func_002A7750(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
extern int func_PAL_002B1A50(char *, char *, int);
typedef struct {
    char pad00[0x1830]; unsigned char *player;
    char pad1834[0xA60]; int mode;
} ControllerGlobals;
extern ControllerGlobals D_00189E20;
extern char D_L06_00188660[], D_L06_001B9840[];
extern int D_L06_001B1858[] SDATA(D_L06_001B1858);
extern int D_L06_001B187C SDATA(D_L06_001B187C);
extern int D_L06_001B1880 SDATA(D_L06_001B1880);
extern int D_L06_001B2838;
extern char *D_L06_001B2480;
extern float D_L06_001B1090 __attribute__((sda));
extern char D_L06_002E20C8[];
extern char D_L06_002E2128[];
extern void func_0026FEB8(const char *, ...);
extern void func_00282A28(void);
extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_L06_00443E88(u8 *);
extern void func_PAL_L06_00448AB8(char *);
extern void func_PAL_002A7650(void *, int, int);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern void func_0029F338(void *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);

/* A Notak enemy's update (spawn-time setup, then the shared distance, target and ground
   checks). The fields are indexed through typed pointers so their MEMs are in-struct: the
   sda and table loads after the angle call may then move above the word stores, as in
   retail. The setup's store order is the one that gives retail's schedule and FP registers. */
#define B(o) (v[o])
#define H(o) (((short *)v)[(o) / 2])
#define I(o) (((int *)v)[(o) / 4])
#define F(o) (((float *)v)[(o) / 4])

void func_PAL_L06_004485C0(u8 *m)
{
    u8 *v = *(u8 **)(m + 0x68);
    int hit;

    if (m[0x20] == 0) {
        char *rec;

        if (D_L06_001B2838 < m[0x21]) {
            func_0026FEB8(D_L06_002E20C8);
            func_0026FEB8(D_L06_002E2128);
            func_00282A28();
        }
        m[0x30] = 0x40;
        qcopy(v + 0x2E0, m + 0x10);
        F(0x324) = 1.0f;
        B(0x48) = func_00283CF0(15.0f);
        B(0x4A) = func_00283CF0(4.8f);
        H(0x88) = 0;
        B(0x60) = 8;
        I(0x98) = 3;
        F(0x108) = 0.5f;
        F(0x80) = 0.2f;
        F(0x84) = 0.2f;
        B(0x28) = 3;
        F(0x30) = 0.333f;
        F(0x8C) = 0.4f;
        F(0x100) = F(0x324) * 0.6f;
        F(0x134) = 0.05f;
        F(0x104) = F(0x324) * 0.5f;
        F(0x10C) = 0.5f;
        I(0x138) |= 0x80;
        F(0x110) = 1.57079649f;
        F(0x130) = 0.52359885f;
        F(0x1DC) = func_002A78D8(18.0f, 22.0f) * 0.0174532942f;
        B(0x1E8) = 7;
        B(0x1E9) = 6;
        H(0x1E2) = 100;
        H(0x1E4) = 150;
        F(0x1D4) = 3.0f;
        F(0x1D0) = D_L06_001B1090 * 0.020000001f;
        rec = D_L06_001B2480 + I(0x210) * 0x30;
        if (*(short *)(rec + 0x30) != 0)
            I(0x13C) = **(int **)(rec + 0x3C);
        F(0x328) = func_002A7940();
        if (I(0x214) != 0) {
            *(int *)(m + 0x98) = 0;
            *(unsigned short *)(m + 0x34) = (*(unsigned short *)(m + 0x34) | 0x41) & 0xEFFF;
            func_002A7750((char *)m, 9, 4);
            if (m[0x43] != 10)
                func_PAL_002A7E68((char *)m, 10, 0, 0);
        } else {
            func_002A7750((char *)m, 1, 0);
            if (m[0x43] != 0)
                func_PAL_002A7E68((char *)m, 0, 0, 0);
        }
    }
    if (m[0x31] != 0 && func_00282E48(m + 0x10, D_L06_001B9840) < 24.0f) {
        func_002A93B0(m);
        m[0x6F] = 0x16;
    }
    hit = func_PAL_002B1A50((char *)m, (char *)(v + 0x50), 0);
    if (hit != 0) {
        func_L06_00443E88(m);
        if (hit >= 4)
            func_PAL_L06_00448AB8((char *)m);
    }
    if (*(float *)(m + 0x18) < 48.0f) {
        func_PAL_002A7650(m, 0, 3);
        func_PAL_002AD288(m, m + 0x10, -1, 1.0f, 13.0f);
        func_0029F338(m);
    } else if (m[0x95] != 3 && m[0x95] != 4) {
        H(0x314) = func_002B3BA8(m, I(0x210), 16.0f, 0.0f, 0, 0);
    }
}

#undef B
#undef H
#undef I
#undef F

void func_L06_00443E88(u8 *arg0);

/* The id-list walks below read D_L06_001B281C as a bare symbol (a second name for the 4-byte
   `sda` pointer above, declared as a 12-byte array so the assembler keeps its loads absolute),
   while D_L06_001B2838 is a plain int: its `.extern` comes last in the file, which leaves a load
   in a branch delay slot on $gp and every other load on `lui`/`lw`. */
extern int D_L06_001B2838;
/* Overlays for an owner (L06Obj) and the state block it points to (L06Cfg); only the fields the
   next two functions touch are named. */
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L06Cfg;

typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L06Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L06Obj;

typedef struct {
    int a;
    int b;
} L06ColorPair;

extern void func_L06_00444300(L06Obj *);
extern L06ColorPair D_L06_001B1098[];
/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   colour pair and, when its stamp is not the current one, refreshes every live class-0xDB0
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L06_00444300 for the owner. */
/* D_L06_001B10A0 is only used for its address, taken through $gp. D_L06_001B10B0 is one 8-byte
   object: its first word is loaded in a branch delay slot (so on $gp), its second as a bare
   symbol, which is how retail loads the two colours. */
/* For every live class-0xDB0 entity in the owner's group, builds the marker's vector from the
   entity's size and stored position and hands it to func_L00_00325AE8 with the colour pair
   blended by the entity's pulse. */
void func_L06_00444300(L06Obj *self);

/* The level's three turn angles, in degrees (37, 41 and 70); the step below turns them into
   radians per frame. The first one is read through $gp, the other two absolutely. */
/* Turns the owner's three angles by the level's step, then walks the owner's eight records:
   each gets a fresh object, scaled and blended against the owner's own axes. `axes` is the
   scratch area func_32DE28 fills; its first vector is the one the objects are given. */
