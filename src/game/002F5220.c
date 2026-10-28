#include "include_asm.h"

extern int D_L05_001B1FC8;

extern int D_L05_001B1FD0;

extern int D_L05_001B1FD4;

extern int D_L05_001B1FCC;

extern int D_L05_001B1FF8;

extern int D_L05_001B1FFC;

extern int D_L05_001A8F00;

extern int D_L05_001A8F08;

extern unsigned char D_0018C0D4[];

extern int D_00138320[];

extern short D_L05_001B225C;

extern short D_L05_001B225E;

extern short D_L05_001B2260;

extern short D_L05_001B2262;

extern short D_L05_001B2264;

#ifndef RAC2_T_F32_F2144BF3D
#define RAC2_T_F32_F2144BF3D
typedef float f32_F2144bf3d;
#endif

#ifndef RAC2_T_S32_F2144BF3D
#define RAC2_T_S32_F2144BF3D
typedef int s32_F2144bf3d;
#endif

/* Resident record reached through a fixed core symbol: the retail body keeps
   the base in a register and addresses every field by displacement. */
#ifndef RAC2_T_RESIDENT138180_F2144BF3D
#define RAC2_T_RESIDENT138180_F2144BF3D
typedef struct {
    char  pad0[0x100];
    f32_F2144bf3d   f100;                 /* 0x100 */
    f32_F2144bf3d   f104;                 /* 0x104 */
    f32_F2144bf3d   f108;                 /* 0x108 */
    f32_F2144bf3d   f10C;                 /* 0x10C */
    char  pad1[0x1A0 - 0x110];
    s32_F2144bf3d   i1A0;                 /* 0x1A0 */
} Resident138180_F2144bf3d;
#endif

extern char D_00138180[];

extern s32_F2144bf3d D_0018D198[];

extern s32_F2144bf3d D_L06_001AD3A0 __attribute__((sda));

extern s32_F2144bf3d D_001A7390;

extern s32_F2144bf3d D_001A79F0;

extern s32_F2144bf3d D_L06_001B2348;

extern s32_F2144bf3d D_L06_001A8FC0;

extern s32_F2144bf3d D_L06_001B2900;

extern s32_F2144bf3d D_L06_001AA0F0;

void func_002F5220(void)
{
    unsigned char mode;

    D_L05_001B1FC8 = 0;
    mode = D_0018C0D4[0];
    D_L05_001B1FD0 = 0;
    D_L05_001B1FD4 = 0;
    D_L05_001B1FCC = 0;
    D_L05_001B1FF8 = 0;
    D_L05_001B1FFC = 0;

    if (mode == 1)
    {
        if ((D_00138320[0] & 0x10) == 0)
        {
            if (D_L05_001A8F00 != 4 && D_L05_001A8F08 != 4)
            {
                D_L05_001B225C = 0;
                D_L05_001B225E = 0;
                D_L05_001B2260 = 0;
                D_L05_001B2262 = 0;
                D_L05_001B2264 = 0;
            }
        }
    }
}

void func_002F52B8(void)
{
    Resident138180_F2144bf3d *p = (Resident138180_F2144bf3d *)D_00138180;

    if (p->i1A0 != 0) goto mismatch;
    if (p->f108 != 0.0f) goto mismatch;
    if (p->f10C != 0.0f) goto mismatch;
    if (p->f100 != 0.0f) goto mismatch;
    if (p->f104 == 0.0f) goto match;
mismatch:
    D_L06_001AD3A0 = 0;
    goto gated;
match:
    D_L06_001AD3A0 = D_L06_001AD3A0 + 1;
gated:
    D_L06_001B2348 = D_L06_001B2348 + 1;
    D_001A7390 = D_001A7390 + 1;

    if (D_L06_001A8FC0 != 0) {
        if (D_L06_001AD3A0 < 900) {
            D_0018D198[D_001A79F0] = D_0018D198[D_001A79F0] + 1;
        }
    }

    if (D_L06_001B2900 != D_001A7390 - 1) {
        D_L06_001AA0F0 = -1;
    }
}


INCLUDE_ASM("asm/game", func_002F53C8);

INCLUDE_ASM("asm/game", func_002F57A8);


#include "common.h"

typedef struct { u8 pad00[0xC]; u8 kind; u8 pad0D[3]; f32 w0[4]; } CamRec_2F5AF8;
typedef struct { u8 pad00[0x38]; s32 index; u8 pad3C[0x68 - 0x3C]; CamRec_2F5AF8 *recs; } CamList_2F5AF8;
typedef struct { u8 pad[0xB0]; f32 scale; } CamView_2F5AF8;
typedef struct {
    u8 pad000[0x140];
    f32 pos[4];
    u8 pad150[0x370 - 0x150];
    f32 row0[3];
    f32 pad37C;
    f32 row1[3];
    f32 pad38C;
    f32 row2[3];
} Cam_2F5AF8;

extern CamList_2F5AF8 D_001B8840;
extern CamView_2F5AF8 D_001B9040;
extern Cam_2F5AF8 D_001B5200;
extern u8 D_001A7A40;
extern f32 D_001A8C74;
extern f32 D_001A8C78;
extern f32 D_001B5360[12];
extern void func_0027AB40(void);
extern void func_00129178(f32 *);
extern void func_001292C0(f32 *, f32 *, f32);
extern void func_00129368(f32 *, f32 *, f32);
extern void func_00129218(f32 *, f32 *, f32);
extern void func_00282F20(f32 *, f32 *, f32);
extern void func_00282CF0(f32 *, f32 *, f32 *);
extern void func_00271958(f32 *, int);

u8 func_002F5AF8(void)
{
    f32 m[16] __attribute__((aligned(16)));
    f32 t[4] __attribute__((aligned(16)));
    CamRec_2F5AF8 *rec;
    f32 *w;
    f32 scale;
    f32 k;
    u8 kind;

    rec = &D_001B8840.recs[D_001B8840.index];
    w = rec->w0;
    kind = rec->kind;
    scale = w[3];
    D_001B9040.scale = scale;
    if (D_001A7A40 != 0)
        D_001B9040.scale = scale * D_001A8C74;
    func_0027AB40();
    qcopy(D_001B5200.pos, rec);
    func_00129178(m);
    func_001292C0(m, m, w[0]);
    func_00129368(m, m, w[1]);
    func_00129218(m, m, w[2]);
    D_001B5200.row0[0] = -m[8];
    D_001B5200.row1[0] = -m[0];
    D_001B5200.row2[0] = m[4];
    D_001B5200.row0[1] = -m[9];
    D_001B5200.row1[1] = -m[1];
    D_001B5200.row2[1] = m[5];
    D_001B5200.row0[2] = -m[10];
    D_001B5200.row1[2] = -m[2];
    D_001B5200.row2[2] = m[6];
    if (D_001A7A40 != 0 && (k = D_001A8C78) != 0.0f) {
        qcopy(t, D_001B5200.row0);
        func_00282F20(t, t, k);
        func_00282CF0(D_001B5200.pos, D_001B5200.pos, t);
    }
    func_00271958(&D_001B5360[0], 0);
    func_00271958(&D_001B5360[4], 1);
    func_00271958(&D_001B5360[8], 2);
    return kind;
}

extern int D_001A8C80[] __attribute__((sda));
extern int D_001A8C84 __attribute__((sda));

void func_002F5CB8(int first, int second) {
    D_001A8C80[0] = first;
    D_001A8C84 = second;
}

extern float D_001A8C7C __attribute__((sda));
extern float D_001B15A0;
extern void func_0027D330(int);

/* Publishes the slow-down factor and, while the frame rate is below one, asks
   for the six-frame path. */
void func_002F5CC8(void)
{
    D_001A8C7C = 1.2f;
    if (D_001B15A0 < 1.0f)
        func_0027D330(6);
}

int func_002F5D10(void)
{
    return D_L05_001A8F08 == 2 || D_L05_001A8F00 == 2;
}

INCLUDE_ASM("asm/game", func_002F5D40);


extern int D_001A7478;
extern int D_001B221C;
extern unsigned char D_00188660[];
extern int D_001BAD78[];
extern int D_001A8BB8;
extern void (*ref_L00_002F5EF8_00)(int);
extern int ref_L00_002F5EF8_01;
extern void func_002B6E78(int, int, int);
extern void func_002B7320(void);
extern void func_002FC1D8(void);

void func_002F5EF8(void)
{
    if (D_001A7478 == 2)
        *(volatile int *)&D_001A7478 = 0;
    func_0027D330(4);
    func_002B6E78(D_001B221C, 1, 0x400);
    func_002B7320();
    D_00188660[0x6B] |= 0x10;
    func_002FC1D8();
    if (ref_L00_002F5EF8_00 != 0 && D_001BAD78[0] == 0) {
        if (D_001A8BB8 == 2)
            goto done;
        if (D_001A8BB8 == 1)
            goto done;
        {
            ref_L00_002F5EF8_00(D_001A8C84);
            *(void (*volatile *)(int))&ref_L00_002F5EF8_00 = 0;
            *(volatile int *)&ref_L00_002F5EF8_01 = 0;
        }
    }
done:
    ;
}

INCLUDE_ASM("asm/game", func_002F5FB8);

extern void func_288CB0(int, int);
void func_002F6458(void) { char *base = D_00138180 + 0x1260; int index = *(int *)(base + 0x148); if (index != -1) { if (*(short *)(base + index * 0xA0 + 0x18) >= 0) *(int *)(base + 0x17C) = 1; } func_288CB0(0, 0); }



INCLUDE_ASM("asm/game", func_002F6510);

INCLUDE_ASM("asm/game", func_002F6608);

INCLUDE_ASM("asm/game", func_002F7320);

INCLUDE_ASM("asm/game", func_002F73A8);

INCLUDE_ASM("asm/game", func_002F7738);

INCLUDE_ASM("asm/game", func_002F8178);


typedef struct { unsigned char pad0[0x3C]; char *destination; unsigned char pad1[0x24]; int clear; } Func_002F88D8State;
extern Func_002F88D8State ref_L00_002F88D8_00;
extern void func_00115DA8(char *, const char *, ...);
extern const char D_001AD2B8[];

void func_002F88D8(void *arg) { func_00115DA8(ref_L00_002F88D8_00.destination, D_001AD2B8, arg); ref_L00_002F88D8_00.clear = 0; }

INCLUDE_ASM("asm/game", func_002F8918);

INCLUDE_ASM("asm/game", func_002F9198);


INCLUDE_ASM("asm/game", func_002F93B0);

extern void func_002F93B0(void);

void func_002F9778(void)
{
    func_002F93B0();
}


INCLUDE_ASM("asm/game", func_002F97A0);
