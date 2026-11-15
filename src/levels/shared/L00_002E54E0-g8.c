#include "names.h"
/* Clamp the value to [1024, 4096], publish it scaled and quantised, then rerun the engine.
   The first float is an incomplete array so the address is the split %hi/%lo form that the
   retail computes early; the two int words are sda arrays (assembler macro form, never
   $gp), and the small-data float's address differs by program, hence the ref_ name. */
extern float D_001BD364[];
extern int D_001B1EB4[] __attribute__((sda));
extern int D_001B255C[] __attribute__((sda));
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
    D_001BD364[0] = value * 1024.0f;
    D_001B1EB4[0] = quantized;
    D_001B255C[0] = quantized;
    ref_L00_002E54E0_00 = (value - 64.0f) * 1024.0f;
    UpdateViewContext();
}
