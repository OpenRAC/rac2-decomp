#include "include_asm.h"
#include "names.h"

/* func_US2_002CAFD8, v2.00's own: resets the view's field of view and fog, updates the
   view context, then resets the active camera. */
extern void UpdateViewContext(void);
extern void cam_reset_active_position(void);
extern void gfx_build_view_matrices(void);

/* Partial view of the shared screen/render state. */
typedef struct {
    char pad[0xB0];
    float fB0;
    char gapB4[0x164];
    float f218, f21C;
    char gap220[8];
    float f228, f22C;
} ScreenState;
extern ScreenState g_view_params;

void func_US2_002CAFD8(void) {
    ScreenState *view = &g_view_params;

    view->f218 = 0.0f;
    view->f21C = 524288.0f;
    view->f228 = 255.0f;
    view->f22C = 0.0f;
    view->fB0 = 0.62f;
    UpdateViewContext();
    cam_reset_active_position();
    gfx_build_view_matrices();
}

