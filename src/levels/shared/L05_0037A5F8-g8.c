/* func_L05_0037A5F8: the HUD markers drawn over level objects (in levels 05, 10, 15, 25).
 * Own unit for -frac2-zero-ti-por (the rotation clear keeps its por + sq to 0($sp)). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float D_L05_001AC4E0 __attribute__((sda));
extern float D_L05_001AC4E4 __attribute__((sda));
extern float D_L05_001AC4E8 __attribute__((sda));
extern float D_L05_001AC4EC __attribute__((sda));
extern int D_L05_001AC4F0 __attribute__((sda));
extern int D_L05_001AC4F4 __attribute__((sda));
extern float D_L05_001AC4F8 __attribute__((sda));
extern int D_L05_001AC4FC __attribute__((sda));
extern float D_L05_001B2D84[] MACRO_ADDR;
extern u8 *D_L05_00225DD0[] NOT_SDA;
extern u16 *D_L05_001FB220[];
extern u8 *D_L05_001B251C[] MACRO_ADDR;
typedef struct { float position[4]; u8 pad[0x220]; float view[12]; } L05HudCamera;
extern L05HudCamera D_L05_001B96C0;
extern u64 func_0027C878(int);
extern void func_L05_003008C0(float,float,float,float,int,int,int,int,u64,u64);
extern int func_L00_004272A0(void);
extern s32 func_002ED688(u8 *);
extern float func_00282E48(void *,void *);
extern void func_002833F0(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002836E8(void *,void *);
extern void func_00283098(void *,void *,void *);
extern float func_002A7798(float);
extern int func_00283CF0(float);
extern int D_L05_001B2D80;
/* The HUD label idiom, as in src/levels/15_gorn/L15_00431590-g8.c. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L05_001B2D80;
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

/* label_y with the rounded result as its own handle. Its display-mode and result tests
 * have no effect (dead-test rounding helper, allowed by owner ruling of 7 November 2026,
 * precedent src/game/002D2188-g8.c); they set retail's block and register layout at entry. */
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L05_001B2D80;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_L05_0037A5F8(void)
{
    float offset[4],rotation[4],rotate[12],view[12];
    float distance,x,y,scale,radius;
    u64 texture,color,color2;
    u8 *object,*state;
    u16 *list,*nextList;
    int i,alpha,c,ty;
    u8 *entry;
    y = (float)hud_coord(D_L05_001AC4E4, D_L05_001B2D84[0], 0.5f);
    texture = func_0027C878(D_L05_001AC4FC);
    func_L05_003008C0(D_L05_001AC4E0,y,D_L05_001AC4E8,D_L05_001AC4EC,0,0,D_L05_001AC4F0,D_L05_001AC4F4,0x80808080ULL,texture);
    for (i=0;i<func_L00_004272A0();i++) {
        entry = D_L05_00225DD0[i];
        nextList = D_L05_001FB220[entry[0x21]];
        if (!nextList) continue;
        list = nextList;
        do {
            object = D_L05_001B251C[0]+((*list&0x7FFF)<<8);
            state = (u8 *)func_002ED688(object);
            if (*(int *)(state+0x110) && *(int *)(state+0x14C)) {
                distance = func_00282E48(D_L05_001B96C0.position,object+0x10);
                if (distance <= 128.0f) {
                    radius = D_L05_001AC4F8;
                    radius *= 0.0078125f;
                    *(Quad *)rotation = 0;
                    rotation[2] = 1.5707964f;
                    scale = distance*radius;
                    func_002833F0(rotate,rotation);
                    func_00282CF0(offset,object+0x10,D_L05_001B96C0.position);
                    func_00282F20(offset,offset,scale);
                    func_002836E8(view,D_L05_001B96C0.view);
                    func_00283098(offset,offset,view);
                    func_00283098(offset,offset,rotate);
                    alpha = func_00283CF0(func_002A7798(1.0f-distance*0.0078125f)*128.0f);
                    distance = offset[2]*0.125f+D_L05_001AC4E8*0.5f;
                    if (*(int *)(state+0x158)) { alpha=128; distance=D_L05_001AC4E8*0.5f; }
                    if (distance > D_L05_001AC4E8+D_L05_001AC4E8) distance=D_L05_001AC4E8+D_L05_001AC4E8;
                    else if (distance < 0.0f) distance=0.0f;
                    x = offset[0]+D_L05_001AC4E0;
                    ty = label_y((void *)alpha, D_L05_001AC4E4-offset[1], D_L05_001B2D84[0], 0.5f, 1);
                    y = (float)ty;
                    c = *(s32 *)(state+0x150);
                    c |= alpha<<24;
                    color = c;
                    texture = func_0027C878(D_L05_001AC4FC);
                    func_L05_003008C0(x,y,distance,distance,0,0,D_L05_001AC4F0,D_L05_001AC4F4,color,texture);
                } else if (*(int *)(state+0x158)) {
                    *(Quad *)rotation = 0;
                    rotation[2] = 1.5707964f;
                    y = D_L05_001AC4F8;
                    func_002833F0(rotate,rotation);
                    func_00282CF0(offset,object+0x10,D_L05_001B96C0.position);
                    func_00282F20(offset,offset,y);
                    func_002836E8(view,D_L05_001B96C0.view);
                    func_00283098(offset,offset,view);
                    func_00283098(offset,offset,rotate);
                    alpha=128;
                    distance = D_L05_001AC4E8;
                    if (distance > D_L05_001AC4E8+D_L05_001AC4E8) distance=D_L05_001AC4E8+D_L05_001AC4E8;
                    else if (distance < 0.0f) distance=0.0f;
                    x = offset[0]+D_L05_001AC4E0;
                    ty = label_y(state, D_L05_001AC4E4-offset[1], D_L05_001B2D84[0], 0.5f, 1);
                    y = (float)ty;
                    c = *(s32 *)(state+0x150);
                    c |= alpha<<24;
                    color2 = c;
                    texture = func_0027C878(D_L05_001AC4FC);
                    func_L05_003008C0(x,y,distance,distance,0,0,D_L05_001AC4F0,D_L05_001AC4F4,color2,texture);
                }
            }
        } while ((s16)*list++ >= 0);
    }
}
