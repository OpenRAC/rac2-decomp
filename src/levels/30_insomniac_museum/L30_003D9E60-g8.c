#include "common.h"
typedef struct {
    float vertices[16];
    u32 colors[4];
    float uv[8];
    u64 regs[4];
} MuseumPacket;
extern int g_flicker_sprite_frame[] __attribute__((sda));
extern float g_flicker_uv_table[8] __attribute__((sda));
extern struct { char pad[0x158]; short texture; } g_screen_adjust_offsets;
extern int g_vram_fb_offset;
extern int func_002F4BA8(int);
extern void gfx_l30_draw_facing_sprite(void *,void *,float,float);
/* Draws a flickering sprite at the object's position, with texture coordinates that change over time. */
void gfx_draw_flicker_sprite(char *object) {
    MuseumPacket p;
    int frame=g_flicker_sprite_frame[0] >> 1;
    int a,b;
    p.uv[0]=g_flicker_uv_table[frame&7];
    p.uv[1]=g_flicker_uv_table[(frame+=2)&7];
    p.uv[2]=g_flicker_uv_table[(frame+=3)&7];
    p.uv[3]=1.0f-g_flicker_uv_table[(frame+=1)&7];
    p.uv[4]=1.0f-g_flicker_uv_table[(frame+=1)&7];
    p.uv[5]=g_flicker_uv_table[(frame+=2)&7];
    p.uv[6]=1.0f-g_flicker_uv_table[(frame+=1)&7];
    p.uv[7]=1.0f-g_flicker_uv_table[(frame+=1)&7];
    p.colors[3]=p.colors[2]=p.colors[1]=p.colors[0]=0x60808080;
    a=func_002F4BA8(g_screen_adjust_offsets.texture);
    b=func_002F4BA8(0x200);
    p.regs[1]=((s64)g_vram_fb_offset>>8);
    p.regs[1] |= ((s64)(g_screen_adjust_offsets.texture>>6)<<14);
    p.regs[1] |= ((s64)a<<26);
    p.regs[1] |= ((s64)b<<30);
    p.regs[2]=0x60;
    p.regs[3]=0x4000000048LL;
    p.regs[0]=0;
    gfx_l30_draw_facing_sprite(object+0x10,&p,6.0f,0.08f);
}
