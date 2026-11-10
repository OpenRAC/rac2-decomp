#include "include_asm.h"
#include "common.h"

extern void func_002F0538(int);

extern void func_002E7D48(int, int, int, int);

extern unsigned int D_L00_001B18D4;

extern short D_L00_001B267E;

extern void func_002E5C40(void);

void func_L00_0037F790(void)
{
    func_002F0538(0);
    func_002E7D48(0, 0, 0, 0x80);
    if (D_L00_001B267E != 0)
        D_L00_001B18D4 = 0x100FF;
    else
        D_L00_001B18D4 = 0x70;
    func_002E5C40();
}

typedef int Quad __attribute__((mode(TI)));
extern int func_001163B0(void);
extern void func_001163A0(int);
extern float func_002A78D8(float,float);
extern float func_002A7878(float,float);
extern int func_00283D38(int,int,float);
extern int func_002A77E0(int);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void *func_002C3150(void *,void *,int,int,float,int,int);
extern int D_L00_001AEE48 __attribute__((sda));
extern int D_L00_001AEE50[2];
extern float D_L00_001AEE58 __attribute__((sda));
extern float D_L00_001AEE5C;
extern float D_L00_001AEE60[2];
extern char D_L00_001B8DC0[];
extern char D_L00_001A8F20[] MACRO_ADDR;

void func_L00_00385040(char *object)
{
    union { Quad q; float f[4]; } vectors[2];
    char *state=*(char **)(object+0x68);
    int saved=func_001163B0();
    int i=0;
    func_001163A0(*(int *)(state+0x68));
    while(i<D_L00_001AEE48) {
        float speed,blend;
        int color;
        unsigned char random;
        vectors[1].q=0;
        vectors[1].f[0]=20.0f;
        i++;
        vectors[1].f[1]=func_002A78D8(0.0f,D_L00_001AEE58);
        vectors[1].f[2]=func_002A78D8(0.0f,D_L00_001AEE5C);
        vectors[0].q=vectors[1].q;
        func_00283098(&vectors[0],&vectors[0],D_L00_001B8DC0 + 0x230);
        func_00282CC0(&vectors[0],&vectors[0],D_L00_001B8DC0);
        speed=func_002A7878(D_L00_001AEE60[0],D_L00_001AEE60[1]);
        blend=func_002A7878(0.0f,1.0f);
        color=func_00283D38(D_L00_001AEE50[0],D_L00_001AEE50[1],blend);
        random=func_002A77E0(255);
        func_002C3150(&vectors[0],D_L00_001A8F20,color,2,speed,random,0);
    }
    func_001163A0(saved);
}

extern int func_00115DA8(char *buffer, char *format, ...);

extern void func_L00_002E95C0(int x, int y, unsigned long colour, char *text, int length);

extern char D_L00_001AEEC0[];

extern char D_L00_001AEED0[];

/* A six-word block of x/y pairs and a three-word block of colours. Retail reads
 * element 0 of each through $gp and the other elements as absolute macro loads at
 * an offset from the block, which keeps them out of the call delay slots
 * (docs/build/compiler-notes.md, "reorg: which global loads may fill a slot"). */
extern int D_L00_001AEE98[] MACRO_ADDR;

extern int D_L00_001AEE98_gp SDATA(D_L00_001AEE98);

extern int D_L00_001AEEB0[] MACRO_ADDR;

extern int D_L00_001AEEB0_gp SDATA(D_L00_001AEEB0);

/* Draws "Score: %d" (data+0x60), "Level: %d" (data+0x70 plus one) and "Score: %d"
 * (data+0x64) from the object's data (object+0x68), each at its own position and
 * colour. */
void func_L00_003852A0(void *object)
{
    char buffer[0x100];
    char *state = *(char **)((char *)object + 0x68);

    func_00115DA8(buffer, D_L00_001AEEC0, *(int *)(state + 0x60));
    func_L00_002E95C0(D_L00_001AEE98_gp, D_L00_001AEE98[1], D_L00_001AEEB0[2], buffer, -1);
    func_00115DA8(buffer, D_L00_001AEED0, *(int *)(state + 0x70) + 1);
    func_L00_002E95C0(D_L00_001AEE98[2], D_L00_001AEE98[3], D_L00_001AEEB0[1], buffer, -1);
    func_00115DA8(buffer, D_L00_001AEEC0, *(int *)(state + 0x64));
    func_L00_002E95C0(D_L00_001AEE98[4], D_L00_001AEE98[5], D_L00_001AEEB0_gp, buffer, -1);
}


/* 128-bit stack vectors reach lq/sq only through TImode. */
typedef int FlareQuad __attribute__((mode(TI)));
typedef union { FlareQuad bits; float f[4]; } FlareVec;
typedef struct { char pad[0x20]; unsigned char flags; } FlareTarget;

extern float func_00282E48(void *, void *);
extern float func_00283CE0(int);
extern void func_00279BD8(void *, void *);
extern unsigned long func_0027C878(int);
extern float func_00282C48(float);
extern int func_00283CF0(float);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027E018(int, int, int, int, int, int, int, int,
                         unsigned long, unsigned long);

typedef struct {
    FlareTarget *target;
    int active;
    float intensity;
    int pad;
    short alpha[16];
    short texture[16];
    unsigned int color[16];
    float offset[16];
    float scale[16];
} FlareState;
extern FlareState D_L00_001B90C0;
extern int D_001A7348[] __attribute__((sda));
/* Effect texture base (.bss, set by func_L00_00382AE8); read as retail's tied lui/lw. */
extern int D_L00_001B273C[] __attribute__((sda));
/* Base sprite size, 64. */
extern int D_L00_001AED00[];

/* Projects the flare target to the screen and draws its 14 sprites along the line
   through the screen centre, faded by distance and by how far off-centre it is
   (RAC1 draw_lens_flare; func_L08_003F7A48 draws 12). Both table bases are read
   through pointers set before the loop: reload rematerializes them inside it. */
void func_L00_00382F28(char *object)
{
    char *work = *(char **)(object + 0x68);
    FlareVec screen;
    float center[4], delta[4], offset[4], location[4];
    float distance, fade, horizontal, vertical;
    unsigned long texture;
    int color;
    int i, size, left, top;
    int *baseSize;
    int *texBase;

    if (D_L00_001B90C0.active != 1 || (D_L00_001B90C0.target->flags & 0x80)) {
        D_L00_001B90C0.active = 0;
        return;
    }
    if (D_L00_001B90C0.intensity <= 0.0f)
        return;
    distance = func_00282E48(D_L00_001B8DC0, work);
    baseSize = D_L00_001AED00;
    center[0] = func_00283CE0(D_001A7348[0]);
    center[1] = func_00283CE0(D_001A7348[1]);
    func_00279BD8(&screen, work);
    screen.f[0] = (screen.f[0] - func_00283CE0(D_001A7348[2])) * 0.0625f;
    screen.f[1] = (screen.f[1] - func_00283CE0(D_001A7348[3])) * 0.0625f;
    delta[0] = center[0] - screen.f[0];
    delta[1] = center[1] - screen.f[1];
    for (i = 0, texBase = D_L00_001B273C; i < 14; ++i) {
        texture = func_0027C878(*texBase + D_L00_001B90C0.texture[i]);
        offset[0] = delta[0] * D_L00_001B90C0.offset[i];
        offset[1] = delta[1] * D_L00_001B90C0.offset[i];
        location[0] = center[0] + offset[0];
        location[1] = center[1] + offset[1];
        fade = distance - 5.0f;
        if (fade > 1.0f)
            fade = 1.0f;
        else if (fade < 0.0f)
            fade = 0.0f;
        horizontal = func_00282C48(delta[0]) / center[0] * -5.0f + 5.5f;
        if (horizontal > 1.0f)
            horizontal = 1.0f;
        else if (horizontal < 0.0f)
            horizontal = 0.0f;
        vertical = func_00282C48(delta[1]) / center[1] * -5.0f + 5.5f;
        if (vertical > 1.0f)
            vertical = 1.0f;
        else if (vertical < 0.0f)
            vertical = 0.0f;
        fade *= horizontal * vertical * D_L00_001B90C0.intensity;
        color = (int)(((unsigned int)func_00283CF0(fade * D_L00_001B90C0.alpha[i]) << 24)
                      | (D_L00_001B90C0.color[i] & 0xFFFFFF));
        size = func_00283CF0(*baseSize * D_L00_001B90C0.scale[i]);
        func_002FC560(66, 0x8000000048ULL);
        left = func_00283CF0(location[0] - (float)(size >> 1));
        top = func_00283CF0(location[1] - (float)(size >> 1));
        func_0027E018(left, top, size, size, 0, 0, 64, 64, color, texture);
    }
    D_L00_001B90C0.intensity = 0.0f;
}
