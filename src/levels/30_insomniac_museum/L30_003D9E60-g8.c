#include "common.h"
typedef struct {
    float vertices[16];
    u32 colors[4];
    float uv[8];
    u64 regs[4];
} MuseumPacket;
extern int D_L30_001B2758[] __attribute__((sda));
extern float D_L30_001B0990[8] __attribute__((sda));
extern struct { char pad[0x158]; short texture; } g_screen_adjust_offsets;
extern int D_001A72D8;
extern int func_002F4BA8(int);
extern void gfx_l30_draw_facing_sprite(void *,void *,float,float);
/* Draws a flickering sprite at the object's position, with texture coordinates that change over time. */
void gfx_draw_flicker_sprite(char *object) {
    MuseumPacket p;
    int frame=D_L30_001B2758[0] >> 1;
    int a,b;
    p.uv[0]=D_L30_001B0990[frame&7];
    p.uv[1]=D_L30_001B0990[(frame+=2)&7];
    p.uv[2]=D_L30_001B0990[(frame+=3)&7];
    p.uv[3]=1.0f-D_L30_001B0990[(frame+=1)&7];
    p.uv[4]=1.0f-D_L30_001B0990[(frame+=1)&7];
    p.uv[5]=D_L30_001B0990[(frame+=2)&7];
    p.uv[6]=1.0f-D_L30_001B0990[(frame+=1)&7];
    p.uv[7]=1.0f-D_L30_001B0990[(frame+=1)&7];
    p.colors[3]=p.colors[2]=p.colors[1]=p.colors[0]=0x60808080;
    a=func_002F4BA8(g_screen_adjust_offsets.texture);
    b=func_002F4BA8(0x200);
    p.regs[1]=((s64)D_001A72D8>>8);
    p.regs[1] |= ((s64)(g_screen_adjust_offsets.texture>>6)<<14);
    p.regs[1] |= ((s64)a<<26);
    p.regs[1] |= ((s64)b<<30);
    p.regs[2]=0x60;
    p.regs[3]=0x4000000048LL;
    p.regs[0]=0;
    gfx_l30_draw_facing_sprite(object+0x10,&p,6.0f,0.08f);
}
