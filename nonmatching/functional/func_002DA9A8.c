/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, v0920, 2026-10-29. Near miss.
 * USA v1.01: 876/876 bytes, 0/28 places, first mismatch +0x158.
 * Profile: -O2 -G0 -ffunction-sections. Eight instructions differ:
 * second text call: menu height/context height loads and y-store/-1 setup;
 * third text call: four context stores (y store moves ahead of bottom/left/x).
 * Named signed coordinates and measured height, pointer text-window
 * ABI, aggregate initialization and the WIP owner/index shape match the rest.
 * Split/direct/widened height arithmetic tie. Grouped coordinate decrements tie
 * with ordinary field decrements; reordered groups change register allocation.
 * Disabling sched1 or sched2 worsens other blocks. No linked build run.
 * Declarations needed by this draft follow. Recover the text-context source
 * representation or scheduling profile; no volatile casts/barriers were used.
 */
#include "common.h"
typedef struct { int pad[8]; int width,height; int pad28[3]; unsigned int flags; int pad38[3]; int mode; int tex[2]; int choice[2]; int active; } DrawMenu;
typedef struct { s16 x0,x1,y0,y1,x,y,w,h,line; u16 flags; s16 extra0,extra1; } TextBox;
typedef struct { int pad0[2]; int state; char padc[0x150]; int stage; int pad160; int status; } DrawState;
extern DrawState D_001393E0;
extern s16 D_001A6480[];
extern u8 D_001395B8[];
typedef struct { char pad[0x14]; u8 *owner; char pad18[0x120]; int messageFlag,message; char pad140[0x24]; int age; } DrawRoot;
extern DrawRoot D_001F2840;
extern u8 D_001A7AF8[],D_00139588[];

extern int func_002B49C8(int),func_00288FB8(int);
extern void func_0027C540(int),func_0027C660(void);
extern void *func_00115484(void *,int,unsigned int);
extern void func_00280200(TextBox *,long,u8 *,int);
extern u64 func_00294C40(int);
extern void func_0027E018(int,int,int,int,int,int,int,int,u64,u64);
int func_002DA9A8(DrawMenu *menu)
{

    u64 packet;
    int message,texture,height,index,type;
    unsigned int selection;
    u8 *text,*row,*owner;
    if (menu->active<0 || func_002B49C8(6)) return 0;
    if (menu->mode<2) {
        if (!(menu->flags&0x100)) return 1;
        if (D_001393E0.state!=2) return 2;
        if (D_001393E0.stage<3 && D_001393E0.status<0 && D_001F2840.age>10) return 2;
        func_0027C540(0);
        message=0x2e00;if (D_001F2840.messageFlag) message=D_001F2840.message;
        text=(u8 *)func_00288FB8(message);
        {
        TextBox draw={1,menu->height+1,1,menu->width+1,menu->width>>1,5,0,0,16,5};
        func_00280200(&draw,0x80000000L,text,-1);
        height=menu->height; height-=draw.h;draw.y=height>>1;draw.flags^=4;
        func_00280200(&draw,0x80000000L,text,-1);
        draw.x0--;draw.x1--;draw.y0--;draw.y1--;draw.x--;draw.y--;
        func_00280200(&draw,0x80ffa888L,text,-1);
        }
        func_0027C660();return 2;
    }
    if (menu->flags&4) {
        owner=*(u8 **)(D_001F2840.owner+0xe8);
        selection=(menu->mode<4)^1;
        index=menu->choice[selection];
        row=*(u8 **)(owner+0x48)+index*10;
        type=*(s16 *)(row+4);
        if (!*(s16 *)(row+4)) { s16 id=*(s16 *)(row+6);if (!D_001A7AF8[id]) return 1;}
        if (*(s16 *)(row+4)==1) {if (!D_001395B8[*(s16 *)(row+6)]) return 1;}
    }
    func_0027C540(0);if (menu->mode<4) texture=menu->tex[0];else texture=menu->tex[1];packet=func_00294C40(texture);
    if (*(u32 *)((u8 *)menu+0x10)&8) func_0027E018(*(int *)((u8 *)menu+0x18),*(int *)((u8 *)menu+0x1c),menu->width,menu->height,0,0,*(int *)((u8 *)menu+0x38),*(int *)((u8 *)menu+0x3c),0x80808080ULL,packet);
    else func_0027E018(0,0,D_001A6480[0xb0],D_001A6480[0xb1],0,0,*(int *)((u8 *)menu+0x38),*(int *)((u8 *)menu+0x3c),0x80808080ULL,packet);
    func_0027C660();return 16;
}
