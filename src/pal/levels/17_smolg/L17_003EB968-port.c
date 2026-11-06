#include "common.h"

/* This unit is built with -G8: every body here reaches a global through $gp. */

extern int func_00283CF0(f32);

extern s32 func_L17_00340DD0(f32, s32, s32, s32);

extern f32 D_L17_001B04B8 __attribute__((sda));

extern void func_002A7750(void *, s32, s32);

extern s32 func_002A9640(void *, s32, s32);

extern void func_L00_0032A258(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);

extern void func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32, s32);

extern void func_0029F338(void *);

extern s32 D_L17_001B1E00 __attribute__((sda));

extern s32 D_L17_001B1DE0 __attribute__((sda));

extern s32 D_L17_001B1DD8 __attribute__((sda));

extern s32 D_L17_001B1DD0 __attribute__((sda));


extern char *D_L17_001B2C1C __attribute__((sda));

typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(short *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))

/* The 0x30-byte record func_L04_0033CB88 fills with its defaults. */
typedef struct {
    s32 i00;
    f32 f04;
    f32 f08;
    f32 f0C;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[8];
} L17Timer;

/* The object's state record, as far as func_L17_003E41A8 uses it. Its stores are struct
   members, so the sda float D_L17_001B0CA8 (a fixed scalar) is read ahead of them. */
typedef struct {
    u8 pad000[0x28];
    u8 b28;
    u8 b29;
    u8 pad02A[6];
    f32 f30;
    u8 b34;
    u8 pad035[0x13];
    u8 b48;
    u8 pad049;
    u8 b4A;
    u8 pad04B[0x15];
    u8 ai[0x10];
    u8 b70;
    u8 b71;
    u8 pad072[4];
    u8 b76;
    u8 b77;
    u8 pad078[4];
    f32 f7C;
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8C;
    f32 f90;
    f32 f94;
    u8 pad098[4];
    f32 f9C;
    u8 pad0A0[8];
    s32 iA8;
    u8 pad0AC[0x20];
    u8 bCC;
    u8 bCD;
    u8 bCE;
    u8 bCF;
    u8 pad0D0[2];
    u8 bD2;
    u8 bD3;
    u8 pad0D4[0x1C];
    s32 iF0;
    f32 fF4;
    u8 pad0F8[0x18];
    Quad v110;
    f32 f120;
    u8 pad124[0x1C];
    L17Timer t140;
    u8 pad170[0x30];
    u8 *target;
    u8 pad1A4[0x16C];
    u8 *p310;
    u8 pad314[0x1C];
    f32 f330;
    u8 pad334[0xC];
    f32 f340;
    u8 pad344[0x8C];
    union { Quad q; f32 f[4]; } v3D0;
    u8 pad3E0[0x20];
    s16 h400;
    u8 pad402[2];
    s16 h404;
    u8 pad406[2];
    u8 *p408;
    f32 f40C;
    u8 pad410[8];
    s32 i418;
    s32 i41C;
    s32 i420;
    s32 i424;
    s32 i428;
    u8 pad42C[4];
    f32 f430;
    u8 pad434[0x1C];
    s32 i450;
} L17Vars;

extern float D_L17_001B0CA8 __attribute__((sda));
extern u8 D_L17_001B0CB8[4] __attribute__((sda));
extern u8 D_L17_001B9BC0[];
extern char D_L17_001B0CC8[]; /* "returned null\n" */
extern u8 *D_0018C0B0 NOT_SDA;
extern float func_002A89A8(void *, int, float);
extern void func_L04_0033CB88(void *);
extern int func_002A7820(int, int);
extern void func_002AB650(void *);
extern void func_002A7470(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L17_003E4860(void *);
extern int func_002B3BA8(void *, int, int, int, float, float);
extern void func_0026FEB8(void *, ...);


/* The player block at D_00189E20, as far as the two updates below use it. */
typedef struct {
    u8 pad000[0x80];
    f32 pos[4];                 /* 0x80: the point IsPointInCuboid tests */
    u8 pad090[0x162];
    u16 status;                 /* 0x1F2 */
    u8 pad1F4[0x148];
    u8 *target;                 /* 0x33C: compared with the updating object */
    u8 pad340[0xE];
    s16 state;                  /* 0x34E */
    u8 pad350[0x268];
    f32 speed;                  /* 0x5B8 */
    u8 pad5BC[0x1CD8];
    s32 mode;                   /* 0x2294 */
} L17Player;
extern L17Player D_00189E20;

/* The level's save record: one collected flag per object id from 0x464. */
typedef struct { u8 pad[0x464]; u8 collected[0]; } L17SaveState;
extern L17SaveState D_L17_0021EBB0;

/* The current level, read with the lw macro: absolute in ordinary flow, $gp in a
   delay slot. */
extern s32 D_001A79F0 MACRO_ADDR;
/* Per-level save nibbles, 0x400 bytes a level, two object ids a byte. */
extern u8 D_0019B4A8[];
/* Per-level object flags, 16 bytes a level. */
extern u8 D_0019B2E8[];

/* Paths: a count, then 16-byte points from 0x10. */
extern u8 *D_L17_001FE880[];

extern f32 func_00283B98(f32, f32);
extern f32 func_00283198(f32);
extern f32 func_002A7940(void);
extern s32 func_002B3868(void *);
extern s32 func_002ACBC8(void *, s32);
extern void func_002B0CE0(s32, s32, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void func_L00_003294F0(void *, s32);
extern void func_L00_00429020(s32);
extern void func_PAL_L13_002CF0A0(s32, s32);

/* func_PAL_L17_00424368's state record. */
typedef struct {
    s32 group;                  /* 0x0: handed to func_L00_00429020 once, then -1 */
    f32 phase;                  /* 0x4: colour pulse angle */
    s32 cuboid;                 /* 0x8: IsPointInCuboid index, negative for none */
    s32 linked;                 /* 0xC: 0x100-byte record at D_L17_001B2C1C, -1 for none */
    f32 speed;                  /* 0x10: given to the player block when nonzero */
} L17PadVars;

/* Pulses the object's colour. While the player block's target is this object it shows
   the lit colour and sets the player's status and speed; the first time (group set, id
   not collected, save nibble still zero) it also hands its group to func_L00_00429020,
   counts the id in its save nibble and passes the linked record to func_L00_003294F0.
   With the player inside its cuboid in mode 0x82 it calls func_PAL_L13_002CF0A0(6, 1). */
void func_PAL_L17_00424368(u8 *obj)
{
    L17PadVars *vars = *(L17PadVars **)(obj + 0x68);
    s32 shade, nibble;
    u16 id;
    u8 *counter;

    vars->phase = func_00283B98(vars->phase, 0.12566373f);
    shade = FloatToInt(func_00283198(vars->phase) * 128.0f);
    if (shade > 128)
        shade = 128;
    else if (shade < 32)
        shade = 32;
    switch (obj[0x20]) {
    case 0:
        if (func_002B3868(obj))
            *(u16 *)(obj + 0x34) |= 0x10;
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        func_002B3868(obj);
        if (D_00189E20.target == obj) {
            if (vars->group != -1) {
                id = *(u16 *)(obj + 0xB2);
                if (!D_L17_0021EBB0.collected[(s16)id]) {
                    nibble = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];
                    nibble = ((id & 1) ? nibble >> 4 : nibble) & 7;
                    if (!nibble) {
                        u16 slot;

                        func_L00_00429020(vars->group);
                        slot = *(u16 *)(obj + 0xB2);
                        if (slot & 1) {
                            counter = D_0019B4A8 + (((s16)slot >> 1) + (D_001A79F0 << 10));
                            if (((*counter >> 4) & 7) != 7)
                                *counter += 16;
                        } else {
                            counter = D_0019B4A8 + (((s16)slot >> 1) + (D_001A79F0 << 10));
                            if ((*counter & 7) != 7)
                                *counter += 1;
                        }
                        if (vars->linked != -1)
                            func_L00_003294F0(D_L17_001B2C1C + (vars->linked << 8), 1);
                        vars->group = -1;
                    }
                }
            }
            func_002B0CE0(12, 0x1349, 1);
            *(s32 *)(obj + 0x78) = (0x80 << 24) | (shade << 8);
            D_00189E20.status = 2;
            if (vars->speed != 0)
                D_00189E20.speed = vars->speed;
        } else
            *(s32 *)(obj + 0x78) = (0x80 << 24) | shade;
        break;
    }
    if (vars->cuboid >= 0 && IsPointInCuboid(D_00189E20.pos, vars->cuboid)
        && D_00189E20.mode == 0x82)
        func_PAL_L13_002CF0A0(6, 1);
}

/* func_L17_00420E08's state record. */
typedef struct {
    s32 path;                   /* 0x0: index into D_L17_001FE880, -1 for none */
    f32 marker;                 /* 0x4: point w values equal to it are cleared */
    s32 trigger;                /* 0x8: nonzero activates the object as well */
    f32 phase;                  /* 0xC: colour pulse angle */
} L17SwitchVars;

/* A path seen from its i-th point, i * 16 bytes in: the points follow a 16-byte header. */
typedef struct { u8 header[0x10]; f32 x, y, z, w; } L17PathPoint;