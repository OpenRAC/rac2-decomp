#include "include_asm.h"
typedef float f32_F2144bf3d;
typedef int s32_F2144bf3d;
typedef struct {
    char  pad0[0x100];
    f32_F2144bf3d   f100;                  
    f32_F2144bf3d   f104;                  
    f32_F2144bf3d   f108;                  
    f32_F2144bf3d   f10C;                  
    char  pad1[0x1A0 - 0x110];
    s32_F2144bf3d   i1A0;                  
} Resident138180_F2144bf3d;
extern char D_00138180[];
extern s32_F2144bf3d D_0018D198[];
extern s32_F2144bf3d D_L06_001AD3A0 __attribute__((sda));
extern s32_F2144bf3d D_001A7390;
extern s32_F2144bf3d D_001A79F0;
extern s32_F2144bf3d D_L06_001B2348;
extern s32_F2144bf3d D_L06_001A8FC0;
extern s32_F2144bf3d D_L06_001B2900;
extern s32_F2144bf3d D_L06_001AA0F0;

void func_PAL_002F6208(void)
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
        if (D_L06_001AD3A0 < 750) {
            D_0018D198[D_001A79F0] = D_0018D198[D_001A79F0] + 1;
        }
    }

    if (D_L06_001B2900 != D_001A7390 - 1) {
        D_L06_001AA0F0 = -1;
    }
}

#include "common.h"
extern char D_001BAD40[];
typedef struct { char pad[0xC]; unsigned char n; char padD[0x3B]; int slots[1]; } CutsceneParts;
typedef struct { char pad[0x24]; CutsceneParts *parts; } CutsceneMoby;
typedef struct {
    char pad0[0x10];
    float pos[4];              
    float rot[4];              
    int id;                    
    int unk34;                 
    int index;                 
    int unk3C;                 
    char pad40[4];
    short count;               
    short restore;             
    short wait;                
    char pad4A[0x22];
    int base6C;                
    int base70;                
    char pad74[0x118];
    CutsceneMoby *mobys[1];    
} CutsceneState;
typedef struct {
    char pad0[4];
    short active;              
    char pad6[0x1E];
    int id;                    
    int flag;                  
    char pad2C[0x40];
    short timer;               
    char pad6E[4];
    short state;               
} CutsceneHelp;
typedef struct {
    char pad0[0x80];
    float pos[4];              
    char pad90[0x2200];
    int active;                
    char pad2294[0x21];
    char flag;                 
} CutsceneHero;
typedef struct { char pad[0xFC]; char *moby; } CutsceneMenu;
typedef struct { int unk0; char *moby; void *data; } CutsceneTalk;
typedef struct { char pad[0xC]; int baseC, base10; } CutsceneResources;
extern CutsceneState D_001B8840;
extern CutsceneHelp D_001A63A8;
extern CutsceneHero D_00189E20;
extern CutsceneMenu D_001F2840;
extern CutsceneTalk D_001B178C MACRO_ADDR;
extern CutsceneResources D_001BAEC0;
extern float D_001A8C74, D_001A8C78, D_001A8C7C, D_001B15A0;
extern int D_001A79F0, D_001A8BB0, D_001B15A4, D_001B15A8, D_001B15AC;
extern int D_001B22B0[] __attribute__((sda));
extern char *D_001B1B60;
extern int D_00139768[];
extern char D_001B1450[] MACRO_ADDR, D_001B1390[] MACRO_ADDR, D_001B13D0[] MACRO_ADDR, D_001B1410[] MACRO_ADDR;
extern char D_001B2980[], D_0021F080[];
extern void func_00288B38(void *);
extern int func_002EF010(int);
extern void func_002B72E8(int);
extern void func_PAL_002B8898(int);
extern void func_00282A60(void *, int, int);
extern void func_00288EA0(void);
extern unsigned int func_PAL_0026F5B8(int, int);
extern void func_0026F728(void);
extern int func_PAL_002945B8(int);
extern void func_00293D30(void);
extern void func_002912F0(void);
extern void func_PAL_002E5898(void);
extern int func_001261F0(int);
extern int func_002B6D28(void);

/* Starts cutscene n: marks it seen, clears the cutscene state and buffers, sets
   up the resource bases and hero, then waits for the dialog stream and three
   frames. */
void func_PAL_002F6318(int n)
{
    int index, i, v;
    char *p, *o;

    if ((unsigned)n < 0xB1)
        *(D_00139768 + ((unsigned)n >> 2)) |= 1 << (n & 31);
    func_00288B38(D_001BAD40);
    index = func_002EF010(n);
    if (index < 0)
        return;
    func_002B72E8(0);
    func_PAL_002B8898(0);
    func_00282A60(&D_001B8840, 0, 0x1D0);
    func_00282A60(D_001B1450, 0, 0x40);
    func_00282A60(D_001B1390, 0, 0x40);
    func_00282A60(D_001B2980, 0, 0x40);
    func_00282A60(D_001B2980 + 0x40, 0, 0x40);
    func_00282A60(D_001B13D0, 0, 0x40);
    func_00282A60(D_001B1410, 0, 0x40);
    p = D_0021F080;
    for (i = 0; i < 7; i++) {
        char *entry = p;
        p += 0x40;
        func_00282A60(entry, 0, 0x40);
    }
    D_001A8C74 = 1.0f;
    D_001B8840.id = index;
    D_001A8C78 = 0;
    D_001B8840.unk34 = 0;
    D_001B8840.unk3C = 0;
    if (D_001A79F0 == 20)
        v = D_001B22B0[0] - 0x60000;
    else
        v = D_001B22B0[0] - 0x40000;
    D_001B22B0[0] = v;
    D_001B8840.base6C = D_001BAEC0.baseC + v;
    D_001B8840.base70 = D_001BAEC0.base10 + v;
    func_00288EA0();
    D_001B15A0 = 1.0f;
    D_001A8BB0 = 2;
    D_001B15A4 = 0;
    D_001A8C7C = 0;
    if (D_00189E20.active) {
        func_PAL_0026F5B8(0x61, 2);
        D_00189E20.flag = 1;
        func_0026F728();
    }
    if (D_001B178C.moby)
        *(unsigned short *)(D_001B178C.moby + 0x34) |= 1;
    if (D_001F2840.moby)
        *(unsigned short *)(D_001F2840.moby + 0x34) |= 1;
    D_001B15A8 = 1;
    D_001B15AC = 52;
    if (D_001A63A8.active) {
        func_PAL_002B8898(1);
        func_PAL_002945B8(0);
    } else
        func_PAL_002945B8(0);
    if (D_001A63A8.active)
        func_PAL_002B8898(1);
    func_00293D30();
    func_002912F0();
    for (o = D_001B1B60; (unsigned char)o[0x20] != 255; o += 0x100) {
        if (!((unsigned char)o[0x20] & 0x80) && *(short *)(o + 0xAA) == 0xCB)
            *(unsigned short *)(o + 0x34) |= 0x80;
    }
    D_001A63A8.id = D_001B8840.id;
    D_001A63A8.flag = 0;
    while (D_001A63A8.state != 3 || D_001A63A8.timer >= 6000) {
        func_PAL_002E5898();
        func_001261F0(0);
    }
    {
        int ticks = 0;
        CutsceneState *state = &D_001B8840;

        state->wait = -3;
        func_002B6D28();
        func_PAL_002945B8(1);
        for (; state->wait < ticks; ticks--)
            func_001261F0(0);
    }
}

typedef struct { char pad[0xB0]; float fov; } CutsceneCamVars;
extern CutsceneCamVars D_001B9040;
extern void (*D_001A8C80)(int);
extern int D_001A8C84, D_001A8BB8;
extern int D_001BAD78[];
extern void func_002FC138(void);
extern void func_0027D330(int);
extern void func_00272198(float);
extern void func_002F5220(void);
extern void func_0027AB40(void);
extern void func_0029F338(void *);
extern void func_0026F758(int);
extern float func_002A89A8(void *, int, float);
extern float func_00282C48(float);
extern void func_PAL_0026F598(void);
extern void func_0026F780(void *, void *, int, int);
extern void func_002B8108(void *, void *, int);
extern void func_002B7340(int);
extern void func_002E6120(void);

/* Ends the cutscene: restores the frame rate, camera field of view and the
   cutscene mobys, drops the hero and camera back to the ground, clears the
   talk and menu mobys and runs the pending end callback. */
void func_PAL_002F66F8(void)
{
    char *o;
    CutsceneHero *p;
    CutsceneState *b;
    float g, f;
    int i;

    if ((unsigned short)(D_001A63A8.state - 6) >= 2)
        D_001A63A8.state = 5;
    func_002FC138();
    func_0027D330(6);
    D_001B15A8 = 0;
    D_001B15AC = 0;
    D_001B15A4 = 0;
    D_001A8C7C = 0;
    func_00272198(5.0f);
    func_002F5220();
    D_001B9040.fov = 0.62f;
    func_0027AB40();
    for (i = 0; i < D_001B8840.count; i++) {
        CutsceneMoby *m = D_001B8840.mobys[i];
        if (m) {
            m->parts->n--;
            m->parts->slots[m->parts->n] = 0;
            func_0029F338(m);
        }
    }
    for (o = D_001B1B60; (unsigned char)o[0x20] != 255; o += 0x100) {
        if (!((unsigned char)o[0x20] & 0x80) && *(short *)(o + 0xAA) == 0xCB)
            *(unsigned short *)(o + 0x34) &= 0xFF7F;
    }
    p = &D_00189E20;
    if (p->active) {
        func_0026F758(1);
        g = func_002A89A8(p->pos, 0, 0.5f);
        if (2.0f < g) {
            if (func_00282C48(p->pos[2] - g) < 4.5f)
                p->pos[2] = g;
        }
        D_00189E20.flag = 0;
        func_PAL_0026F598();
        b = &D_001B8840;
        if (b->restore) {
            f = func_002A89A8(b->pos, 0, 0.5f);
            if (2.0f < f && func_00282C48(b->pos[2] - f) < 2.0f)
                b->pos[2] = f;
            func_0026F780(D_001B8840.pos, D_001B8840.rot, 0, 1);
        }
    }
    if (D_001B178C.moby)
        *(unsigned short *)(D_001B178C.moby + 0x34) &= 0xFFFE;
    if (D_001F2840.moby) {
        *(unsigned short *)(D_001F2840.moby + 0x34) &= 0xFFFE;
        D_001F2840.moby = 0;
    }
    if (D_001B178C.moby) {
        char *moby = D_001B178C.moby;
        void *data = D_001B178C.data;
        D_001B178C.moby = 0;
        D_001B178C.data = 0;
        func_002B8108(moby, data, 1);
    }
    func_002B7340(25);
    if (D_001A8C80 && !D_001BAD78[0] && D_001A8BB8 != 2 && D_001A8BB8 != 1) {
        D_001A8C80(D_001A8C84);
        D_001A8C80 = 0;
        D_001A8C84 = 0;
    }
    func_002E6120();
}
