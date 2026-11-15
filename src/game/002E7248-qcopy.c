#include "names.h"
/* Shuts the scene down: runs the helpers, clears the resident flag and, when the scene record has no active entry, lifts the copy of its next record (third component adjusted) before the final transition. */
typedef int TI128 __attribute__((mode(TI)));
extern char D_00189E20[];
extern char D_00152C00[];
extern void func_002B7320(void);
extern void func_0026F728(void);
extern void func_0026F750(int);
extern void func_0026F798(void);
extern void func_0026F778(char *, void *, int, int);
extern void func_00272198(float);
extern void func_002B8518(void);
extern float func_00283B98(float, float);

/* Ends the scene and starts the closing transition. */
void func_002E7248(void) {
    char *data;
    char *scene;
    float liftedPoint[4] __attribute__((aligned(16)));

    music_Unpause();
    data = gHeroState;
    data[0x22B5] = 0;
    EmptyStubF728();
    scene = gHeroMoby_00152C00;
    if (*(short *)(scene + 0x2A) != 0) {
        EmptyStubF750(1);
        data[0x22B5] = 0;
        EmptyStubF728();
        EmptyStubF798();
        SetCameraTransitionFrames(8.0f);
        ClearPadPortState();
    } else {
        data = scene + 0x80;
        *(TI128 *)liftedPoint = *(TI128 *)data;
        liftedPoint[2] = FastAddRotations(liftedPoint[2], -2.3f);
        scene += 0x70;
        EmptyStubF778(scene, liftedPoint, 0, 1);
        EmptyStubF778(scene, data, 0, 0);
        SetCameraTransitionFrames(8.0f);
        ClearPadPortState();
    }
}
