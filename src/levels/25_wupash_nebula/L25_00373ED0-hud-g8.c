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
extern void func_L05_003263F8(int);
extern int func_L05_00324DB8(void);
extern void func_L00_0030CF60(void);
extern void func_L05_0037A5F8(void);

/* func_L25_0040D208 draws this level's HUD: two counters, the gauges of the selected item, its
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

/* Draws the whole HUD: counters, health and ammo bars, the selected item icons and the corner sprites. */
int func_L25_0040D208(void)
{
    char text[128];
    int healthColors[2], ammoColors[2];
    char *state=*(char **)(D_L25_001B0CE0+0x68);
    char *row;
    float iconX,iconY,fillRatio,fill;
    int selection=1, color, result;
    char *message;
    float edge, ammoCount, ammoStart, ammoWidth;
    float half;
    HudState *hud=(HudState *)D_L25_00221850;
    char *fmt;
    int textX, textX2;
    DrawFadingHudIconPairs_L25(0,selection,selection,selection);
    half=0.5f;
    message=GetLocalizedString(0x31d1);
    Sprintf(text,fmt=D_L25_001B0D20,message,hud->count1);
    textX=D_L25_001B0D10-60;
    DrawTextMediumFont(textX,label_y((void *)textX,D_L25_001B0D14-8,D_L25_001B2904,half,1),0x80808080,text,128);
    message=GetLocalizedString(0x31d2);
    Sprintf(text,fmt,message,hud->count2+1);
    textX2=D_L25_001B0D18-60;
    DrawTextMediumFont(textX2,label_y((void *)textX2,D_L25_001B0D1C-8,D_L25_001B2904,half,1),0x80808080,text,128);
    if (D_L25_001A904C) {
        D_L25_001B0CD0=FindTableEntryById(D_L25_001A904C+0x8710,128);
        D_L25_001B0CD4=FindTableEntryById(D_L25_001A904C+0x8710,129);
        D_L25_001B0CD8=FindTableEntryById(D_L25_001A904C+0x8710,130);
        D_L25_001B0CE4=FindTableEntryById(D_L25_001A904C+0x8710,131);
        D_L25_001B0CE8=FindTableEntryById(D_L25_001A904C+0x8710,132);
        D_L25_001B0CEC=FindTableEntryById(D_L25_001A904C+0x8710,133);
        iconX=IntToFloat(gScreenWidth)*half;
        iconY=(float)hud_coord(D_L25_001B2900,200.0f,half,4.0f,selection);
        DrawScaledObjectUniform(D_L25_001B0CD0,iconX,iconY,0x60442d00,1.0f,0.0f);
        DrawScaledObjectUniform(D_L25_001B0CD4,iconX,iconY,0x55f0c070,1.0f,0.0f);
        selection=FindLastUsedChainEntry(6);
        fillRatio=IntToFloat(D_L25_0029C320[selection].count);
        fillRatio/=IntToFloat(D_L25_0029C320[selection].capacity);
        switch(selection) {
        case 6:
            if(fillRatio>0.0f) DrawScaledObjectUniform(D_L25_001B0CE4,iconX,iconY,(int)(float)FastTweenColor(0x800000ff,0x8000ff00,fillRatio),1.0f,0.0f);
            break;
        case 12:
            if(fillRatio>0.5f) {
                fillRatio-=0.5f;
                DrawScaledObjectUniform(D_L25_001B0CE8,iconX,iconY,(int)(float)FastTweenColor(0x800000ff,0x8000ff00,fillRatio+fillRatio),1.0f,0.0f);
                DrawScaledObjectUniform(D_L25_001B0CE4,iconX,iconY,0x8000ff00,1.0f,0.0f);
            } else if(fillRatio>0.0f) {
                DrawScaledObjectUniform(D_L25_001B0CE4,iconX,iconY,(int)(float)FastTweenColor(0x800000ff,0x8000ff00,fillRatio+fillRatio),1.0f,0.0f);
            }
            break;
        case 14:
            if(fillRatio>0.666666687f) {
                fillRatio-=0.666666687f;
                DrawScaledObjectUniform(D_L25_001B0CEC,iconX,iconY,(int)(float)FastTweenColor(0x800000ff,0x8000ff00,fillRatio*3.0f),1.0f,0.0f);
                DrawScaledObjectUniform(D_L25_001B0CE8,iconX,iconY,0x8000ff00,1.0f,0.0f);
                DrawScaledObjectUniform(D_L25_001B0CE4,iconX,iconY,0x8000ff00,1.0f,0.0f);
            } else if(fillRatio>0.333333343f) {
                fillRatio-=0.333333343f;
                DrawScaledObjectUniform(D_L25_001B0CE8,iconX,iconY,(int)(float)FastTweenColor(0x800000ff,0x8000ff00,fillRatio*3.0f),1.0f,0.0f);
                DrawScaledObjectUniform(D_L25_001B0CE4,iconX,iconY,0x8000ff00,1.0f,0.0f);
            } else if(fillRatio>0.0f) {
                DrawScaledObjectUniform(D_L25_001B0CE4,iconX,iconY,(int)(float)FastTweenColor(0x800000ff,0x8000ff00,fillRatio*3.0f),1.0f,0.0f);
            }
            break;
        }
        fill=(float)((HudState *)D_L25_00221850)->health*0.01f;
        if(fill>0.3f) {
            I(state,0x28)=1;
        } else if(FastFloatHelperD(state+0x24)) {
            I(state,0x24)=5; I(state,0x28)^=1;
        }
        healthColors[1]=FastTweenColor(0x800000ff,0x8000ff00,fill);
        healthColors[0]=0x800000ff;
        edge=fill*200.0f+156.0f;
        if(I(state,0x28)) DrawScreenRectangle(156,14,(int)edge,27,1,healthColors);
        selection=FindLastUsedChainEntry(7);
        ammoCount=IntToFloat(D_L25_0029C320[selection].count);
        fill=ammoCount/IntToFloat(D_L25_0029C320[selection].maximum);
        color=FastTweenColor(0x800000ff,0x8000ff00,fill);
        ammoStart=IntToFloat(450);
        ammoWidth=IntToFloat(386);
        ammoWidth-=IntToFloat(450);
        ammoColors[0]=0x800000ff; ammoColors[1]=color;
        ammoWidth*=fill;
        edge=ammoStart+ammoWidth;
        if(fill>0.0f) DrawScreenRectangle(450,8,(int)edge,19,1,ammoColors);
        {
        Rgba rect[4]={{0x70,0xc0,0xf0,0x55},{0x70,0xc0,0xf0,0x55},{0x70,0xc0,0xf0,0x55},{0x70,0xc0,0xf0,0x55}};
        Rgba rect1[4]={{0x00,0x2d,0x44,0x60},{0x00,0x2d,0x44,0x60},{0x00,0x2d,0x44,0x60},{0x00,0x2d,0x44,0x60}};
        Rgba rect2[4]={{0x80,0x80,0x80,0x80},{0x80,0x80,0x80,0x80},{0x80,0x80,0x80,0x80},{0x80,0x80,0x80,0x80}};
        DrawHudSpriteGradient(GetIconFrame(0xea97,1),21,7,30,30,rect1);
        DrawHudSpriteGradient(GetIconFrame(0xea97,0),21,7,30,30,rect);
        row=(char *)&D_L25_0029C320[FindLastUsedChainEntry(D_L25_001B0CF0)];
        DrawHudSpriteGradient(GetIconFrame(0xea97,*(short *)(row+0x1c)),21,7,30,30,rect2);
        DrawHudSpriteGradient(GetIconFrame(0xea97,1),462,9,30,30,rect1);
        row=(char *)&D_L25_0029C320[FindLastUsedChainEntry(7)];
        DrawHudSpriteGradient(GetIconFrame(0xea97,*(short *)(row+0x1c)),462,9,30,30,rect2);
        }
        Sprintf(text,D_L25_001B0D58,D_L25_0029C320[FindLastUsedChainEntry(D_L25_001B0CF0)].count,D_L25_0029C320[FindLastUsedChainEntry(D_L25_001B0CF0)].maximum);
        DrawTextSmallFont(67,5,0x80808080,text,128);
        SetCounterPlusOne(2);
        result=LookUpStepTable();
        if(result>=0) {
            D_L25_0029C320[FindLastUsedChainEntry(D_L25_001B0CF0)].active=0;
            D_L25_001B0CF0=result;
            D_L25_0029C320[FindLastUsedChainEntry(result)].active=1;
        }
        DrawScaledObjectUniform(D_L25_001B0CD8,iconX,iconY,0x80f0f0f0,1.0f,0.0f);
    }
    CallLoadedModuleHandler_L00443E18();
    {
    float four=4.0f, half2=0.5f;
    char *darkSprite, *lightSprite;
    int spriteY;
    float spriteX;
    darkSprite=FindTableEntryById(D_L25_001A904C+0x8710,186);
    state=FindTableEntryById(D_L25_001A904C+0x8710,187);   /* the second texture reuses state */
    lightSprite=FindTableEntryById(D_L25_001A904C+0x8710,188);
    spriteX=D_L25_001AC4E0+four;
    spriteY=label_y(darkSprite,D_L25_001AC4E4+four,D_L25_001B2904,half2,1);
    DrawScaledObjectUniform(darkSprite,spriteX,(float)spriteY,0x60442d00,0.8f,0.0f);
    spriteX=D_L25_001AC4E0+four;
    spriteY=label_y(state,D_L25_001AC4E4+four,D_L25_001B2904,half2,1);
    DrawScaledObjectUniform(state,spriteX,(float)spriteY,0x60241700,0.8f,0.0f);
    spriteX=D_L25_001AC4E0+four;
    spriteY=label_y(lightSprite,D_L25_001AC4E4+four,D_L25_001B2904,half2,1);
    DrawScaledObjectUniform(lightSprite,spriteX,(float)spriteY,0x55f0c070,0.8f,0.0f);
    }
    DrawObjectHudMarkers();
    return 1;
}
