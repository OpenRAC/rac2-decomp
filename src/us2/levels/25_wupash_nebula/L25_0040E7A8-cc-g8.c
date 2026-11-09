/* func_US2_L25_0040E7A8, the USA v2.00 copy of func_L25_0040D208: the same C, where rename func_L05_003263F8 becomes func_US2_L05_00327640; rename func_L00_0030CF60 becomes func_US2_0029CC48. */
#include "common.h"

extern char D_L25_00221850[] __attribute__((nosda));
extern char D_L25_001B0D20[] __attribute__((nosda)), D_L25_001B0D58[] __attribute__((nosda));
extern char *D_L25_001B0CE0 __attribute__((sda));
extern char *D_L25_001B0CD0 __attribute__((sda)), *D_L25_001B0CD4 __attribute__((sda));
extern char *D_L25_001B0CD8 __attribute__((sda));
extern char *D_L25_001A904C MACRO_ADDR;
extern float D_L25_001B2904 MACRO_ADDR;
extern int func_00282948(void *);
#define I(p,o) (*(int *)((char *)(p)+(o)))

extern char *D_L25_001B0CE4 __attribute__((sda)), *D_L25_001B0CE8 __attribute__((sda));
extern char *D_L25_001B0CEC __attribute__((sda));
extern int D_L25_001B0CF0 __attribute__((sda));
extern int D_L25_001B0D10 __attribute__((sda)), D_L25_001B0D18 __attribute__((sda));
extern int D_L25_001B0D14 MACRO_ADDR, D_L25_001B0D1C MACRO_ADDR;
extern int D_L25_001B2900 MACRO_ADDR;
extern float D_L25_001AC4E0 MACRO_ADDR, D_L25_001AC4E4 MACRO_ADDR;
extern int D_001A7340 MACRO_ADDR;
typedef struct { int active, pad1[2], capacity, maximum, count; short pad2[2], icon, pad3[5]; } InventoryEntry;
extern InventoryEntry D_L25_0029C320[] __attribute__((nosda));
typedef struct { u8 r, g, b, a; } Rgba;
extern void func_L25_0040DE40(int,int,int,int);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *,char *,...);
extern void func_0027F5B8(int,int,u64,char *,int);
extern void func_0027F538(int,int,u64,char *,int);
extern char *func_00336D50(char *,int);
extern float func_00283CE0(int);
extern void func_00300968(char *,float,float,int,float,float);
extern int func_002ED8A0(int);
extern int func_00283D38(unsigned int,unsigned int,float);
extern void func_0027EAE8(int,int,int,int,int,void *);
extern int func_0028E588(int,int);
extern void func_0028EA58(int,int,int,int,int,void *);
extern void func_US2_L05_00327640(int);
extern int func_L05_00324DB8(void);
extern void func_US2_0029CC48(void);
extern void func_L05_0037A5F8(void);

/* func_US2_L25_0040E7A8 draws this level's HUD: two counters, the gauges of the selected item, its
   icon panels and the last three sprites. A unit of its own: its .rodata holds the panel colours.
   func_00300968 (src/game/00300618.c) is declared object, x, y, colour: each register bank keeps
   the definition's order. */
typedef struct { char pad[0x10]; int count1, count2; char pad2[0x10]; int health; } HudState;

/* A label's y coordinate (a text line or a sprite) scaled for the display and rounded to a whole
   pixel. Its display-mode and handle tests do not change the result: flow deletes them after
   allocation, as with scaled_coord in src/levels/02_maktar_nebula/L02_003FF6E8-g8.c. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L25_001B2900;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

/* A screen coordinate scaled for the display; mode 1 also takes an offset in unscaled pixels
   (the same shape as scaled_screen_coord in src/game/002D3390.c). */
static __inline__ int hud_coord(int mode, float value, float half, float offset, int active)
{
    float scaled = value * D_L25_001B2904 + half;
    if (mode == active)
        return (int)(scaled + offset);
    return (int)scaled;
}

int func_US2_L25_0040E7A8(void)
{
    char text[128];
    int colors[2], colors2[2];
    char *state=*(char **)(D_L25_001B0CE0+0x68);
    char *row;
    float x,y,a,fill;
    int selection=1, color, result;
    char *message;
    float edge, ammoCount, ammoStart, ammoWidth;
    float half;
    HudState *hud=(HudState *)D_L25_00221850;
    char *fmt;
    int textX, textX2;
    func_L25_0040DE40(0,selection,selection,selection);
    half=0.5f;
    message=func_00288FB8(0x3067);
    func_00115DA8(text,fmt=D_L25_001B0D20,message,hud->count1);
    textX=D_L25_001B0D10-60;
    func_0027F5B8(textX,label_y((void *)textX,D_L25_001B0D14-8,D_L25_001B2904,half,1),0x80808080,text,128);
    message=func_00288FB8(0x3068);
    func_00115DA8(text,fmt,message,hud->count2+1);
    textX2=D_L25_001B0D18-60;
    func_0027F5B8(textX2,label_y((void *)textX2,D_L25_001B0D1C-8,D_L25_001B2904,half,1),0x80808080,text,128);
    if (D_L25_001A904C) {
        D_L25_001B0CD0=func_00336D50(D_L25_001A904C+0x8710,128);
        D_L25_001B0CD4=func_00336D50(D_L25_001A904C+0x8710,129);
        D_L25_001B0CD8=func_00336D50(D_L25_001A904C+0x8710,130);
        D_L25_001B0CE4=func_00336D50(D_L25_001A904C+0x8710,131);
        D_L25_001B0CE8=func_00336D50(D_L25_001A904C+0x8710,132);
        D_L25_001B0CEC=func_00336D50(D_L25_001A904C+0x8710,133);
        x=func_00283CE0(D_001A7340)*half;
        y=(float)hud_coord(D_L25_001B2900,200.0f,half,4.0f,selection);
        func_00300968(D_L25_001B0CD0,x,y,0x60442d00,1.0f,0.0f);
        func_00300968(D_L25_001B0CD4,x,y,0x55f0c070,1.0f,0.0f);
        selection=func_002ED8A0(6);
        a=func_00283CE0(D_L25_0029C320[selection].count);
        a/=func_00283CE0(D_L25_0029C320[selection].capacity);
        switch(selection) {
        case 6:
            if(a>0.0f) func_00300968(D_L25_001B0CE4,x,y,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a),1.0f,0.0f);
            break;
        case 12:
            if(a>0.5f) {
                a-=0.5f;
                func_00300968(D_L25_001B0CE8,x,y,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a+a),1.0f,0.0f);
                func_00300968(D_L25_001B0CE4,x,y,0x8000ff00,1.0f,0.0f);
            } else if(a>0.0f) {
                func_00300968(D_L25_001B0CE4,x,y,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a+a),1.0f,0.0f);
            }
            break;
        case 14:
            if(a>0.666666687f) {
                a-=0.666666687f;
                func_00300968(D_L25_001B0CEC,x,y,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a*3.0f),1.0f,0.0f);
                func_00300968(D_L25_001B0CE8,x,y,0x8000ff00,1.0f,0.0f);
                func_00300968(D_L25_001B0CE4,x,y,0x8000ff00,1.0f,0.0f);
            } else if(a>0.333333343f) {
                a-=0.333333343f;
                func_00300968(D_L25_001B0CE8,x,y,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a*3.0f),1.0f,0.0f);
                func_00300968(D_L25_001B0CE4,x,y,0x8000ff00,1.0f,0.0f);
            } else if(a>0.0f) {
                func_00300968(D_L25_001B0CE4,x,y,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a*3.0f),1.0f,0.0f);
            }
            break;
        }
        fill=(float)((HudState *)D_L25_00221850)->health*0.01f;
        if(fill>0.3f) {
            I(state,0x28)=1;
        } else if(func_00282948(state+0x24)) {
            I(state,0x24)=5; I(state,0x28)^=1;
        }
        colors[1]=func_00283D38(0x800000ff,0x8000ff00,fill);
        colors[0]=0x800000ff;
        edge=fill*200.0f+156.0f;
        if(I(state,0x28)) func_0027EAE8(156,14,(int)edge,27,1,colors);
        selection=func_002ED8A0(7);
        ammoCount=func_00283CE0(D_L25_0029C320[selection].count);
        fill=ammoCount/func_00283CE0(D_L25_0029C320[selection].maximum);
        color=func_00283D38(0x800000ff,0x8000ff00,fill);
        ammoStart=func_00283CE0(450);
        ammoWidth=func_00283CE0(386);
        ammoWidth-=func_00283CE0(450);
        colors2[0]=0x800000ff; colors2[1]=color;
        ammoWidth*=fill;
        edge=ammoStart+ammoWidth;
        if(fill>0.0f) func_0027EAE8(450,8,(int)edge,19,1,colors2);
        {
        Rgba rect[4]={{0x70,0xc0,0xf0,0x55},{0x70,0xc0,0xf0,0x55},{0x70,0xc0,0xf0,0x55},{0x70,0xc0,0xf0,0x55}};
        Rgba rect1[4]={{0x00,0x2d,0x44,0x60},{0x00,0x2d,0x44,0x60},{0x00,0x2d,0x44,0x60},{0x00,0x2d,0x44,0x60}};
        Rgba rect2[4]={{0x80,0x80,0x80,0x80},{0x80,0x80,0x80,0x80},{0x80,0x80,0x80,0x80},{0x80,0x80,0x80,0x80}};
        func_0028EA58(func_0028E588(0xea97,1),21,7,30,30,rect1);
        func_0028EA58(func_0028E588(0xea97,0),21,7,30,30,rect);
        row=(char *)&D_L25_0029C320[func_002ED8A0(D_L25_001B0CF0)];
        func_0028EA58(func_0028E588(0xea97,*(short *)(row+0x1c)),21,7,30,30,rect2);
        func_0028EA58(func_0028E588(0xea97,1),462,9,30,30,rect1);
        row=(char *)&D_L25_0029C320[func_002ED8A0(7)];
        func_0028EA58(func_0028E588(0xea97,*(short *)(row+0x1c)),462,9,30,30,rect2);
        }
        func_00115DA8(text,D_L25_001B0D58,D_L25_0029C320[func_002ED8A0(D_L25_001B0CF0)].count,D_L25_0029C320[func_002ED8A0(D_L25_001B0CF0)].maximum);
        func_0027F538(67,5,0x80808080,text,128);
        func_US2_L05_00327640(2);
        result=func_L05_00324DB8();
        if(result>=0) {
            D_L25_0029C320[func_002ED8A0(D_L25_001B0CF0)].active=0;
            D_L25_001B0CF0=result;
            D_L25_0029C320[func_002ED8A0(result)].active=1;
        }
        func_00300968(D_L25_001B0CD8,x,y,0x80f0f0f0,1.0f,0.0f);
    }
    func_US2_0029CC48();
    {
    float four=4.0f, half2=0.5f;
    char *tex0, *tex2;
    int iy;
    float px;
    tex0=func_00336D50(D_L25_001A904C+0x8710,186);
    state=func_00336D50(D_L25_001A904C+0x8710,187);   /* the second texture reuses state */
    tex2=func_00336D50(D_L25_001A904C+0x8710,188);
    px=D_L25_001AC4E0+four;
    iy=label_y(tex0,D_L25_001AC4E4+four,D_L25_001B2904,half2,1);
    func_00300968(tex0,px,(float)iy,0x60442d00,0.8f,0.0f);
    px=D_L25_001AC4E0+four;
    iy=label_y(state,D_L25_001AC4E4+four,D_L25_001B2904,half2,1);
    func_00300968(state,px,(float)iy,0x60241700,0.8f,0.0f);
    px=D_L25_001AC4E0+four;
    iy=label_y(tex2,D_L25_001AC4E4+four,D_L25_001B2904,half2,1);
    func_00300968(tex2,px,(float)iy,0x55f0c070,0.8f,0.0f);
    }
    func_L05_0037A5F8();
    return 1;
}
