#include "names.h"
/* Clamp the value to [1024, 4096], publish it scaled and quantised, then rerun the engine.
   The first float is an incomplete array so the address is the split %hi/%lo form that the
   retail computes early; the two int words are sda arrays (assembler macro form, never
   $gp), and the small-data float's address differs by program, hence the ref_ name. */
extern float g_view_distance[];
extern int g_view_distance_quantized[] __attribute__((sda));
extern int g_moby_pool_base_copy[] __attribute__((sda));
extern float ref_L00_002E54E0_00 __attribute__((sda));
extern void UpdateViewContext(void);

/* Limits the value to a safe range, stores it in several engine settings, then refreshes the view. */
void gfx_set_clamped_view_distance(float value)
{
    int quantized;

    if (value < 1024.0f)
        value = 1024.0f;
    if (value > 4096.0f)
        value = 4096.0f;
    quantized = (int)value - 0x40;
    g_view_distance[0] = value * 1024.0f;
    g_view_distance_quantized[0] = quantized;
    g_moby_pool_base_copy[0] = quantized;
    ref_L00_002E54E0_00 = (value - 64.0f) * 1024.0f;
    UpdateViewContext();
}
