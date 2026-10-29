#include "common.h"

/* Partial layouts measured from this renderer and its neighboring menu functions. */
typedef unsigned int Quad __attribute__((mode(TI)));
typedef struct {
    char pad00[8];
    int state, initialize;
    int capture;
    char * buffer, *end;
    char pad1c[4];
    char * preview0, *preview1, *moby, *models;
    char pad30[4];
    int count;
    char pad38[4];
    char * text;
    char pad40[0x10];
    int mode, selected0, selected1;
    char pad5c[4];
    int use_camera;
    char pad64[0x24];
    int draw;
    char pad8c[4];
    int field90, field94;
    char pad98[0x48];
    Quad saved;
    char padf0[0x654];
    int auxiliary;
} MenuState;
extern char D_L00_0022F7C0[];

#define menu ((MenuState *)D_L00_0022F7C0)
typedef struct {
    char pad00[0x370];
    float x;
    char pad374[0x10];
    float y;
    char pad388[0x10];
    float z, w;
} CameraState;
extern CameraState D_L00_001B8C80;
extern char D_L00_001B8DD0[];
/* The incomplete array preserves the retail absolute address macro. */
extern Quad D_L00_001B25B0[] __attribute__((sda));
extern char D_L00_001B9000[], D_L00_001B9010[];
typedef struct {
    int words[2];
} Pair;
extern Pair D_L00_001AD858[];
extern int D_001A7340[] __attribute__((sda));
extern int D_001A7344[] __attribute__((sda));
extern int D_001A72DC[] __attribute__((sda));
extern int D_L00_001B25E4[] __attribute__((sda));
extern int D_L00_001B25E8[] __attribute__((sda));
extern int D_L00_001B25EC[] __attribute__((sda));
extern int D_L00_001B25F0[] __attribute__((sda));
extern int D_L00_001B25F4[] __attribute__((sda));
extern int D_L00_001B25F8[] __attribute__((sda));
extern char * D_L00_001A904C MACRO_ADDR;
extern float D_L00_001BD370[];
extern float D_L00_001AD570 __attribute__((sda));
extern float D_L00_001AD574 __attribute__((sda));
extern float D_L00_001AD578 __attribute__((sda));
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_L00_001B18D4 MACRO_ADDR;
extern int D_L00_001B18D8 MACRO_ADDR;
extern int D_L00_001B2610 __attribute__((sda));
extern int func_001261F0(int);
extern void func_L00_002D5000();
extern int func_00279D18();
extern void func_0027AB40(void);
extern void func_0027B858();
extern void func_0027BD70();
extern int func_0027C540();
extern void func_0027C660();
extern void func_L00_002E73E0();
extern void func_00282A88();
extern int func_00283678();
extern void func_00284F40();
extern void func_0028E458();
extern void func_0029BF08();
extern void func_L00_003116A8();
extern void func_0029FEE0();
extern void func_002A01C8();
extern void func_002A01F0();
extern void func_002A0220();
extern int func_002A0250();
extern void func_002A0300();
extern int func_002A0380();
extern void func_002A0468();
extern void func_002A0F48();
extern int func_002A10E8();
extern int func_002A9588();
extern void func_L00_00375718();
extern int func_002F9C80();
extern int func_002FA270();
extern int func_L00_00376600();
extern int func_L00_003769C0();
extern int func_002FA880();
extern void func_L00_00377330();
extern int func_L00_00377580();
extern int func_L00_003778F0();
extern int func_L00_00377C50();
extern int func_L00_003781B0();
extern int func_L00_00378388();
extern int func_L00_00378578();
extern int func_L00_00378818();
extern int func_L00_00378C18();
extern int func_L00_00378DE0();
extern void func_L00_00378E90();
extern void func_002FAE68();
extern int func_002FB1A0();
extern void ref_L00_0037A610_00();
extern void func_002FC220();
extern void func_002FC280(void);
extern void func_002FC3C0();
extern void func_002FC560(int, unsigned long long);
extern void func_002FC620();
extern void func_002FC990();
extern void func_00300A00(int, int, float, float, float, float, float);
extern int func_00336D50();
/* Initialize the selected menu view, draw its layered background, then render its models. */
void func_L00_0037A610(void)
{
    int ids[4];
    Pair pair;
    unsigned char matrices[128] __attribute__((aligned(16)));
    int r, g, b, color;
    float scale;
    int c;
    func_00284F40(0);
    D_L00_001BD370[0] = 0.62f;
    func_0027AB40();

    switch (menu->state) {
    case 0:
        if (menu->initialize)
            *(unsigned short *)(menu->moby + 0x34) |= 1;
        D_L00_001B18D4 = 0x100ff;
        if (menu->initialize)
            D_L00_001B18D4 = 127;
        func_0027BD70();
        *(unsigned short *)(menu->moby + 0x34) &= 0xfffe;
        if (!menu->initialize)
            break;
        {
            menu->state = 1;
            menu->initialize = 0;
            func_002FC3C0(1);
            func_001261F0(0);
            D_L00_001B18D8 = D_L00_001B18D8 + 1;
            func_002FC280();
            func_002FC220();
            D_L00_001B2610 = 0x60000;
            func_L00_002E73E0(menu->capture);
            if (menu->use_camera) {
                qcopy(&menu->saved, D_L00_001B8DD0);
                /* Save the three camera basis vectors before resetting the view. */
                {
                    Quad * src = (Quad *)(D_L00_001B8DD0 + 0x220);
                    Quad * dst = (Quad *)D_L00_001B25B0;
                    dst[0] = src[0];
                    dst[1] = src[1];
                    dst[2] = src[2];
                }
                qzero(D_L00_001B8DD0 + 0x220);
                qzero(D_L00_001B9000);
                qzero(D_L00_001B9010);
                D_L00_001B8C80.x = 1;
                D_L00_001B8C80.y = 1;
                D_L00_001B8C80.z = 1;
                D_L00_001B8C80.w = 1;
                func_00279D18();
            }
            {
                char * base = menu->buffer;
                menu->preview1 = base + 0x800;
                menu->preview0 = base;
                menu->models = base + 0x1000;
                menu->text = base + 0x2400;
                func_00282A88(base + 0x2400, 0x400);
            }
            menu->field94 = 0;
            menu->field90 = 0;
            menu->end = menu->text + 0x400;
            func_002FB1A0();
        }
        /* Initialization falls through into the first rendered frame. */
    case 1:
        func_002FC990(menu->capture, D_001A72DC[0], D_001A7344[0] << 11);
        func_0027C540(0);
        func_00279D18();
        func_0027B858();
        if (D_L00_001AD570 >= 1.0f && menu->draw) {
            func_002A0250();
            func_002A01C8();
            func_002A01F0();
        }
        func_002FC560(0x42, 0x8000000044ULL);
        {
            float dr = (float)(D_L00_001B25F0[0] - D_L00_001B25E4[0]);
            float dg = (float)(D_L00_001B25F4[0] - D_L00_001B25E8[0]);
            float db = (float)(D_L00_001B25F8[0] - D_L00_001B25EC[0]);
            float fr = (float)D_L00_001B25E4[0] + dr * D_L00_001AD570;
            float fb = (float)D_L00_001B25EC[0] + db * D_L00_001AD570;
            float fg = (float)D_L00_001B25E8[0] + dg * D_L00_001AD570;
            r = (int)fr;
            g = (int)fg;
            b = (int)fb;
        }
        scale = D_L00_001AD574 + (D_L00_001AD578 - D_L00_001AD574) * D_L00_001AD570;
        if (menu->mode == 0) {
            ids[0] = 0x67;
            ids[1] = 0x68;
            ids[2] = 0x69;
            ids[3] = 0x6a;
        } else if (menu->mode == 3) {
            ids[0] = 0x75;
            ids[1] = 0x76;
            ids[2] = 0x77;
            ids[3] = 0x78;
        } else if (menu->mode == 2) {
            ids[0] = 0x7c;
            ids[1] = 0x7d;
            ids[2] = 0x7e;
            ids[3] = 0x7f;
        } else if (menu->mode == 1) {
            ids[0] = 0x79;
            ids[1] = 0x7a;
            ids[2] = 0x7b;
        }
        c = func_00336D50(D_L00_001A904C + 0x8710, ids[0]);
        func_00300A00(c, (r << 24) | 0x442d00, (float)(D_001A7340[0] >> 1), (float)(D_001A7344[0] >> 1), scale, scale, 0.0f);
        c = func_00336D50(D_L00_001A904C + 0x8710, ids[1]);
        func_00300A00(c, (g << 24) | 0x241700, (float)(D_001A7340[0] >> 1), (float)(D_001A7344[0] >> 1), scale, scale, 0.0f);
        c = func_00336D50(D_L00_001A904C + 0x8710, ids[2]);
        color = (b << 24) | 0xf0c070;
        func_00300A00(c, color, (float)(D_001A7340[0] >> 1), (float)(D_001A7344[0] >> 1), scale, scale, 0.0f);
        if (menu->mode != 1) {
            c = func_00336D50(D_L00_001A904C + 0x8710, ids[3]);
            func_00300A00(c, color, (float)(D_001A7340[0] >> 1), (float)(D_001A7344[0] >> 1), scale, scale, 0.0f);
        }
        func_0028E458();
        func_0029BF08();
        if (D_L00_001AD570 >= 1.0f) {
            ref_L00_0037A610_00();
            if (menu->mode == 0) {
                func_002FA880();
                func_L00_00377C50();
                func_L00_00378818();
                func_002F9C80();
                func_L00_00375718();
                if (menu->auxiliary)
                    func_002FAE68();
                if (menu->draw) {
                    func_002FC620(158, 360, 115, 206);
                    func_002A0300(menu->models, 1);
                    func_002A0220();
                    func_002A0380();
                }
            } else if (menu->mode == 3) {
                func_L00_00377330();
                func_L00_003781B0();
                func_L00_00378C18();
                func_L00_00376600();
                func_L00_00375718();
                if (menu->draw) {
                    func_002FC620(0, D_001A7340[0] - 1, 0, D_001A7344[0] - 1);
                    func_L00_002D5000(menu->models, menu->models + 0x100);
                    pair = D_L00_001AD858[0];
                    func_L00_003116A8(menu->models, 2, &pair, matrices);
                    {
                        char * models = menu->models;
                        qcopy(models + 0x210, matrices + 0x30);
                        qcopy(models + 0x310, matrices + 0x70);
                        func_002A0F48(models + 0x200);
                    }
                    func_00283678(menu->models + 0x2c0, matrices);
                    func_00283678(menu->models + 0x3c0, matrices + 0x40);
                    func_002A10E8(menu->models + 0x200);
                    func_002A10E8(menu->models + 0x300);
                    func_002A0300(menu->models, menu->count + 2);
                    func_002A0220();
                    func_002A0380();
                }
            } else if (menu->mode == 2) {
                func_L00_00378578();
                func_L00_00378E90();
                func_L00_003769C0();
                func_L00_00375718();
                if (menu->draw) {
                    func_002FC620(32, 386, (int)(D_L00_001B25E0 * 64.0f + 0.5f), (int)(D_L00_001B25E0 * 229.0f + 0.5f));
                    c = func_002A9588(0xffffff, 0x606060, 30, 1, 0);
                    if (menu->selected0 != -1)
                        func_002A0468(menu->models + (menu->selected0 << 8), c, 14, 14, 0);
                    if (menu->selected1 != -1)
                        func_002A0468(menu->models + (menu->selected1 << 8), c, 14, 14, 0);
                    func_002A0300(menu->models, menu->count);
                    func_002A0220();
                    func_002A0380();
                    func_002FC620(0, D_001A7340[0] - 1, 0, D_001A7344[0] - 1);
                    func_L00_003778F0();
                }
            } else if (menu->mode == 1) {
                func_L00_00377580();
                func_L00_00378388();
                func_L00_00378DE0();
                func_002FA270();
                func_L00_00375718();
                if (menu->draw) {
                    func_002FC620(158, 360, 115, 206);
                    func_002A0300(menu->models, 1);
                    func_002A0220();
                    func_002A0380();
                }
            }
            func_002FC620(0, D_001A7340[0] - 1, 0, D_001A7344[0] - 1);
        }
        func_0027C660();
        func_002FC3C0(16);
        func_0029FEE0();
        break;
    }
}
