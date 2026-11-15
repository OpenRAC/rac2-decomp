#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[0x21C];
    short f21C;                        
    unsigned char pad21E[0x186C - 0x21E];
    float f186C;                       
    unsigned char pad1870[0x1FE0 - 0x1870];
    float glow[3][4];                  
    float v2010[4];                    
    float v2020[4];                    
    unsigned char pad2030[0x2080 - 0x2030];
    float queue[8][4];                 
    unsigned int queueColor[8];        
    float queueSize[8];                
    float queueFade[8];                
    short queueCount;                  
    unsigned char pad2162[0x22B4 - 0x2162];
    unsigned char mode;                
    unsigned char pad22B5[0x24FC - 0x22B5];
    short f24FC;                       
    short pad24FE;
    short f2500;                       
    unsigned char pad2502[0x2508 - 0x2502];
    unsigned int f2508;                
    unsigned char pad250C[0x2520 - 0x250C];
    short f2520;                       
    short pad2522;
    unsigned int f2524;                
} Hero_L00_002A7A50;
extern Hero_L00_002A7A50 g_hero_state;
extern int D_L00_001A8F00 MACRO_ADDR;
extern unsigned char D_001A7A40[] __attribute__((sda));
extern void gfx_l00_draw_billboard_quad(void *, unsigned int, float, float);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern void gfx_set_clear_color_packet(int, int, int, int);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern int hero_slot_item_id(int);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern float ApproachValue(float *, float, float);

void func_PAL_L00_002A7938(void)
{
    int index, alpha;
    float value, divisor, size, step, peak;
    unsigned int color;

    if (D_L00_001A8F00 == 2 || D_L00_001A8F00 == 6) {
        for (index = 0; index < g_hero_state.queueCount; index++)
            gfx_l00_draw_billboard_quad(g_hero_state.queue[index], g_hero_state.queueColor[index],
                              g_hero_state.queueSize[index], g_hero_state.queueFade[index]);
        return;
    }
    if (g_hero_state.f21C) {
        value = IntToFloat(g_hero_state.f21C);
        divisor = IntToFloat(15);
        value = value * 3.1415927f;
        value = math_fast_sin_or_cos_b(value / divisor);
        alpha = FloatToInt((value * 0.5f + 0.5f) * 80.0f);
        gfx_set_clear_color_packet(0xAA, 0, 0, alpha);
        VU1_addGSregister(0x47, 0x5360B);
    }
    if (g_hero_state.mode == 3) {
        unsigned int tint = g_hero_state.f2508;
        float (*glow)[4] = g_hero_state.glow;
        int remaining = 2;
        while (remaining >= 0) {
            gfx_l00_draw_billboard_quad(*glow, tint, 0.2f, 0.08f);
            glow++;
            remaining--;
        }
    } else if (g_hero_state.mode == 0) {
        if ((hero_slot_item_id(3) == 3 || hero_slot_item_id(3) == 2) && !g_hero_state.f24FC) {
            if (g_hero_state.f2500) {
                peak = 1.0f;
                if (peak < g_hero_state.v2020[0]) peak = g_hero_state.v2020[0];
                if (peak < g_hero_state.v2020[1]) peak = g_hero_state.v2020[1];
                if (peak < g_hero_state.v2020[2]) peak = g_hero_state.v2020[2];
                FastTweenColor(0xC0000028U, 0x28, peak);
            }
            gfx_l00_draw_billboard_quad(g_hero_state.v2010, 0xC0000028U, 0.05700000002980232f, 0.08f);
        }
        for (index = 0; index < g_hero_state.queueCount; index++)
            gfx_l00_draw_billboard_quad(g_hero_state.queue[index], g_hero_state.queueColor[index],
                              g_hero_state.queueSize[index], g_hero_state.queueFade[index]);
    } else if (g_hero_state.mode == 2) {
        gfx_l00_draw_billboard_quad(g_hero_state.v2010, 0x300000C0U, 0.25f, 0.08f);
    } else if (g_hero_state.mode == 1) {
        size = g_hero_state.f2520 ? 0.101500004529953f : 0.07f;
        if (D_001A7A40[3]) {
            g_hero_state.v2010[2] -= 0.01f;
            size *= 1.7f;
        } else {
            g_hero_state.v2010[2] -= 0.02f;
        }
        ApproachValue(&g_hero_state.f186C, size, 0.0036000002f);
        gfx_l00_draw_billboard_quad(g_hero_state.v2010, g_hero_state.f2524, g_hero_state.f186C, 0.08f);
    }
}

