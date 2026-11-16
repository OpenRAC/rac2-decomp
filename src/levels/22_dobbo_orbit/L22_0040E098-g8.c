#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned int u32;

typedef int s32;

typedef int TI128 __attribute__((mode(TI)));

extern float g_scroll_effect_size __attribute__((sda));

extern u32 g_scroll_effect_id_a __attribute__((sda));

extern u32 g_scroll_effect_id_b __attribute__((sda));

extern u32 g_scroll_effect_id_c __attribute__((sda));

extern u32 g_scroll_burst_type_a __attribute__((sda));

extern s32 g_scroll_burst_count_a __attribute__((sda));

extern u32 g_scroll_burst_type_b __attribute__((sda));

extern s32 g_scroll_burst_count_b __attribute__((sda));

extern u32 g_scroll_burst_type_c __attribute__((sda));

extern s32 g_scroll_burst_count_c __attribute__((sda));

extern float func_002F3BC8(void *);

extern float func_0031FDE8(void);

extern void func_002F2BB8(void *, s32, u32, s32, float, float, float);

extern void func_002F2990(void *, void *, s32, u32, s32, s32, float, float, float);

/* scrolls the effect's phase, spawns three particles around it, and once the phase passes the
   limit emits three more through the shared emitter with the local direction {0, 0, 0, 1} */
void part_update_scrolling_effect(u8 *obj) {
    float direction[4];
    u8 *vars = *(u8 **)(obj + 0x68);
    float phase;
    float phase_step;
    float size;

    *(TI128 *)direction = 0;
    direction[3] = 1.0f;
    phase = *(float *)(vars + 0x14) - 0.1f;
    *(float *)(vars + 0x14) = phase;
    if (phase <= -8.0f) {
        *(float *)(vars + 0x14) = phase + 8.0f;
    }
    phase_step = func_002F3BC8(vars);
    size = g_scroll_effect_size * 0.2f;
    *(float *)(vars + 0x18) = *(float *)(vars + 0x18) + phase_step;
    func_002F2BB8(obj + 0x10, 0x31, g_scroll_effect_id_a, 1, size, 0.0f, func_0031FDE8());
    func_002F2BB8(obj + 0x10, 0x31, g_scroll_effect_id_b, 1, g_scroll_effect_size * 0.1f, 0.0f, func_0031FDE8());
    func_002F2BB8(obj + 0x10, 0x2F, g_scroll_effect_id_c, 1, g_scroll_effect_size * 0.05f, 0.0f, func_0031FDE8());
    if (*(float *)(vars + 0x18) > 1.0f) {
        func_002F2990(obj, direction, 1, g_scroll_burst_type_a, g_scroll_burst_count_a, 0x17, g_scroll_effect_size * 0.02f,
                          g_scroll_effect_size * 0.4f, *(float *)(vars + 0x14));
        func_002F2990(obj, direction, 1, g_scroll_burst_type_b, g_scroll_burst_count_b, 0x17, g_scroll_effect_size * 0.07f,
                          g_scroll_effect_size * 0.4f, *(float *)(vars + 0x14));
        func_002F2990(obj, direction, 1, g_scroll_burst_type_c, g_scroll_burst_count_c, 0x17, g_scroll_effect_size * 0.07f,
                          g_scroll_effect_size * 0.4f, *(float *)(vars + 0x14));
    }
}
