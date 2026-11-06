#include "include_asm.h"
#include "common.h"

extern void func_0029F978(unsigned char *, int, unsigned char *);
extern void func_L15_003804B8(int, void *);
#define GF(offset) (((GornState *)state)->f[(offset) / 4])
#define GI(offset) (((GornState *)state)->i[(offset) / 4])

/* Measured prefixes with integer/float views of the same game records. */
typedef union { float f[0x660 / 4]; int i[0x660 / 4]; } GornState;
typedef union { float f[0x80 / 4]; unsigned short h[0x80 / 2]; unsigned char b[0x80]; } GornOwnerFields;

typedef int GornQuad __attribute__((mode(TI)));
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

extern void func_00283098(void *, void *, void *);
extern void func_0029FC20(void *, int, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002831B0(float);
extern float func_00283180(float);
extern char D_L15_001B97C0[];

extern void func_L06_00382608(char *, int, int, int, float, int);
extern int func_002EEB00(char *);
extern void func_002EE920(char *, char *);
extern void func_002EE678(char *, int);
extern void func_L05_0037C160(char *);
extern void func_L05_0037B538(char *, int, int, int);
typedef struct GornPathPoint {
    float position[3];
    float action;
} GornPathPoint;

typedef struct GornPath {
    int count;
    int pad[3];
    GornPathPoint points[1];
} GornPath;
extern char *D_L15_001FE480[];
extern void func_L15_00436BA8(char *);
extern void func_L15_00436C68(void);

/* ---- shared declarations ---- */

extern int func_002ED688(unsigned char *owner);
extern void func_PAL_L05_0037D610(char *object, int flag);
extern void func_L05_00379C68(int arg0, int value);
extern void func_L00_002E6DB8(void *, void *);
extern void func_L00_002E6CF0(void *a0, void *a1);
extern void func_L00_002E6EF8(void *, int);
extern void func_L15_00438238(void);
extern void func_L15_00438260(void);
extern void func_L15_00438518(void);

extern void func_002FC560(int, int);
extern void func_0027DE50(int, int, int, int, long);
extern int func_00282948(void *);
extern void func_L15_00432A60(void *, int, int, float, float, float, int, int, int);
extern short D_001A6480[];
extern char D_L15_00269FE0[];

/* func_L15_00432A60 is in L15_00432A60-ribbon.c. */

extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern int func_L00_00367720(void);
extern void func_L05_00379E60(void *, void *, int, int);
extern void func_L05_0037AE40(void *);
extern void func_PAL_L15_0043B0D8(char *);
extern void func_L15_00434610(void *, int);
extern void func_L15_00435E80(void);
extern void func_L15_00434D28(void *);
extern void func_L05_00424990(void *, int, int, int, int, int, int, int, float, int, int, int);
extern int func_002A77E0(int);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);

extern s32 D_L15_001AEE20[] __attribute__((sda));
extern s32 D_L15_001B1780[] SDATA(D_L15_001B1780);
extern s32 D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern u8 D_L15_00188660[];
extern s32 func_002E5CF8(s32 a, s32 b, void *c);
extern s32 func_002A77E0(s32 a);
extern f32 func_002A7878(f32 a, f32 b);
extern void func_0029FCC0(void *obj, s32 a, void *out);
extern void func_L10_0039D5E0(void *a, void *b, s32 c, s32 d, f32 e, f32 f, f32 g, f32 h, s32 i, s32 j, s32 k, s32 l);
extern s32 func_00283CF0(f32 a);
extern void func_L15_00434F90(char *object, int a1, int joint, float radius);
/* The particle helper has a different catalogue body in PAL. */
extern void ref_L15_00434D28_00(char *object, int joint, int unused, float radius);



typedef struct GornEffectCamera {
    char pad00[0x140];
    float position[4];
} GornEffectCamera;
extern GornEffectCamera D_L15_001B9680;
extern unsigned char *D_L15_001FF4AC;
extern void func_0029FCC0(void *, int, void *);
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(void *, float, float, float);
extern unsigned char *func_002BDCE8(float, float, float, float,
                                   void *, int, void *, int, int);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);

void func_PAL_L15_0043B0D8(char *object)
{
    GornOwnerFields *fields = (GornOwnerFields *)object;
    char *state = *(char **)(object + 0x68);
    char *record;
    char *a = state + 0x2B0;
    char *b = state + 0x2F0;
    char *c = state + 0x330;
    char *d = state + 0x370;
    char *e = state + 0x3B0;
    char *f = state + 0x3F0;
    char *position = object + 0x10;
    record = (char *)func_002ED688((unsigned char *)object);
    *(int *)(record + 0x148) = func_00283CF0(150.0f);
    func_PAL_L05_0037D610(object, 1);
    GF(0x180) = 150.0f;
    object[0x20] = 1;
    *(unsigned char *)(object + 0x30) = 255;
    *(unsigned short *)(object + 0x32) = 0x1FF;
    *(float *)(object + 0x2C) = 0.675f;
    *(unsigned short *)(object + 0x34) |= 0x100;
    *(unsigned short *)(object + 0x7C) = 63;
    GI(0x458) = -1;
    GI(0x268) = 1;
    GI(0x270) = 0;
    GI(0x27C) = 0;
    GI(0x45C) = 0;
    GI(0x278) = 0;
    func_0029FC20(object, 14, state + 0x280);
    func_0029FC20(object, 16, state + 0x2C0);
    func_0029FC20(object, 18, state + 0x300);
    func_0029FC20(object, 15, state + 0x340);
    func_0029FC20(object, 17, state + 0x380);
    func_0029FC20(object, 19, state + 0x3C0);
    func_00282CF0(a, a, position);
    func_00282CF0(d, d, position);
    func_00282CF0(d, d, a);
    func_00282D30(a, a, 1.0f / fields->f[0x2C / 4]);
    func_00282D30(d, d, 1.0f / fields->f[0x2C / 4]);
    func_00282CF0(b, b, position);
    func_00282CF0(e, e, position);
    func_00282CF0(e, e, b);
    func_00282D30(b, b, 1.0f / fields->f[0x2C / 4]);
    func_00282D30(e, e, 1.0f / fields->f[0x2C / 4]);
    func_00282CF0(c, c, position);
    func_00282CF0(f, f, position);
    func_00282CF0(f, f, c);
    func_00282D30(c, c, 1.0f / fields->f[0x2C / 4]);
    func_00282D30(f, f, 1.0f / fields->f[0x2C / 4]);
    func_0029F978((unsigned char *)object, 12, (unsigned char *)(state + 0x460));
    func_0029F978((unsigned char *)object, 13, (unsigned char *)(state + 0x4A0));
    func_0029F978((unsigned char *)object, 14, (unsigned char *)(state + 0x4E0));
    func_0029F978((unsigned char *)object, 15, (unsigned char *)(state + 0x520));
    func_0029F978((unsigned char *)object, 16, (unsigned char *)(state + 0x560));
    func_0029F978((unsigned char *)object, 17, (unsigned char *)(state + 0x5A0));
    func_0029F978((unsigned char *)object, 18, (unsigned char *)(state + 0x5E0));
    func_0029F978((unsigned char *)object, 19, (unsigned char *)(state + 0x620));
    GF(0x510) = GF(0x2B0) * 1024.0f;
    GF(0x514) = GF(0x2B4) * 1024.0f;
    GF(0x518) = GF(0x2B8) * 1024.0f;
    GF(0x550) = GF(0x370) * 1024.0f;
    GF(0x554) = GF(0x374) * 1024.0f;
    GF(0x558) = GF(0x378) * 1024.0f;
    GF(0x590) = GF(0x2F0) * 1024.0f;
    GF(0x594) = GF(0x2F4) * 1024.0f;
    GF(0x598) = GF(0x2F8) * 1024.0f;
    GF(0x5D0) = GF(0x3B0) * 1024.0f;
    GF(0x5D4) = GF(0x3B4) * 1024.0f;
    *(unsigned char *)(state + 0x4E3) = 1;
    *(unsigned char *)(state + 0x523) = 1;
    *(unsigned char *)(state + 0x563) = 1;
    *(unsigned char *)(state + 0x5A3) = 1;
    GF(0x4EC) = 1.0f;
    GF(0x51C) = 1.0f;
    GF(0x52C) = 1.0f;
    GF(0x55C) = 1.0f;
    GF(0x56C) = 1.0f;
    GF(0x59C) = 1.0f;
    GF(0x5AC) = 1.0f;
    GF(0x5D8) = GF(0x3B8) * 1024.0f;
    GF(0x5DC) = 1.0f;
    *(unsigned char *)(state + 0x5E3) = 1;
    GF(0x610) = GF(0x330) * 1024.0f;
    GF(0x614) = GF(0x334) * 1024.0f;
    GF(0x618) = GF(0x338) * 1024.0f;
    GF(0x650) = GF(0x3F0) * 1024.0f;
    GF(0x654) = GF(0x3F4) * 1024.0f;
    GF(0x658) = GF(0x3F8) * 1024.0f;
    *(unsigned char *)(state + 0x623) = 1;
    GF(0x5EC) = 1.0f;
    GF(0x61C) = 1.0f;
    GF(0x62C) = 1.0f;
    GF(0x65C) = 1.0f;
    GI(0x444) = 250;
    GI(0x440) = 0;
    func_L05_00379C68((int)object, 0xFFFF);
    func_L15_003804B8((int)object, (void *)1);
}

/* func_L15_004360D8 is in L15_004360D8.c. */

extern int func_002E5CF8(int, int, void *);
extern void func_L05_00379FA0(void *, int, int, float, int, float, float, float,
                              int, int, int);



/* func_L15_00438260 is in L15_00438260-g8.c. */

/* func_L15_00438518 is in L15_00438518-g8.c. */

extern int D_L15_001A8FF0[] __attribute__((sda));
extern char D_00189ED0[];
extern int func_002A77E0(int);
extern int func_001163B0(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern unsigned char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);


/* The level's id lists: the number of groups, the table of the groups' lists (a pointer, read
   through $gp in a branch delay slot and as a bare lui/lw elsewhere: `sda` arrays of unknown size
   give that), the base of the 64-byte records of the first walk, the base of the 32-byte records
   of the second, and the table that maps a record's byte at +0x1D to a class. */
extern int D_L15_001A9018[] __attribute__((sda));
extern unsigned short **D_L15_001A9014[] __attribute__((sda));
extern unsigned char *D_L15_001B2C9C[] __attribute__((sda));
extern unsigned char *D_L15_001B2C94[] __attribute__((sda));
extern short D_L15_00227500[];

extern float func_00282E80(void *, void *);
extern float func_002A7940(void);
extern float func_00283198(float);
extern void func_002AEE70(void *, void *, void *, float, float, float);
extern void func_L00_00323448(void *, void *, int, int, int, int, int, int);
extern void func_L00_00323E48(void *, int, int, void *);
extern void func_L00_00323958(void *, void *);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);