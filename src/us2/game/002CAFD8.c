#include "include_asm.h"

/* func_US2_002CAFD8, v2.00's own: resets the view's field of view and fog, updates the
   view context, then resets the active camera. */
extern void func_0027AB40(void);
extern void func_002C9C90(void);
extern void func_00279D18(void);

/* Partial view of the shared screen/render state. */
typedef struct {
    char pad[0xB0];
    float fB0;
    char gapB4[0x164];
    float f218, f21C;
    char gap220[8];
    float f228, f22C;
} ScreenState;
extern ScreenState D_001B9040;

void func_US2_002CAFD8(void) {
    ScreenState *view = &D_001B9040;

    view->f218 = 0.0f;
    view->f21C = 524288.0f;
    view->f228 = 255.0f;
    view->f22C = 0.0f;
    view->fB0 = 0.62f;
    func_0027AB40();
    func_002C9C90();
    func_00279D18();
}

INCLUDE_ASM("asm/us2/game", func_US2_002CB038);
