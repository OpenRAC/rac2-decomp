#include "common.h"

extern void func_00287E60(void);
extern float func_00282C10(float);
extern float func_00283248(float, float);
extern int func_002A9588(int, int, int, int, int);
extern int func_002E5E58(int, int, void *);
extern void func_00287E18(void);
extern int func_0028B5D0(int);
typedef struct { char pad0[0x148]; float x, y; char pad150[0x70]; int held, pressed, released, mode; } RadialInput;
extern RadialInput D_00138180;
typedef struct { char pad0[0x24E4]; int choice; } RadialState;
extern RadialState D_00189E20;
extern short D_001B189C, D_001B18A0, D_001B18A2, D_001B18A4;
extern int D_001B18D0 __attribute__((sda));
extern int D_001A8D48;
extern int **D_001B18D4;
extern int D_001A8DB0[] __attribute__((sda));
extern unsigned char D_001A7BB3;
extern int D_001B18FC, D_001B18F8, D_001B1598;
extern int D_001B1900 __attribute__((sda));
typedef struct { char pad[0x64]; int handle; char pad68[4]; int timer; unsigned char fade[4]; int selected, state, timeout; } Selector;

/* Reads the stick and buttons for the radial weapon menu and updates which slot is selected. Closes the menu when the button is let go. */
void func_0028CCE0(Selector *object)
{
    float x, y, magnitude, angle;
    int old, choice;
    unsigned char *fade = object->fade;
    SetStateWordToThree();
    object->timeout = 180;
    object->timer = 24;
    gPadState.mode = 2;
    x = gPadState.x;
    y = gPadState.y;
    magnitude = square_root(x * x + y * y);
    if (magnitude != 0.0f) {
        x /= magnitude;
        y /= magnitude;
    }
    angle = FastMatrixHelperA(x, y);
    if ((object->state >> 24) == 0 && D_001B189C) {
        if (gPadState.pressed & 0xF000) goto reset_selection;
        if (magnitude < 0.5f) goto reset_selection;
        --object->state;
        if (object->state == -1) {
reset_selection:
            object->selected = -1;
            object->state = 0x10000FF;
        }
    }
    old = object->selected;
    if ((object->state >> 24) == 1) {
        if (magnitude > 0.0f) {
            if (magnitude > 0.9f) {
                float a;
                a = angle + 3.1415927f + 3.1415927f + 1.5707964f + 3.1415927f / (float)gRadialSlotCount;
                a = a * 0.15915494f * (float)gRadialSlotCount;
                object->selected = (int)a % gRadialSlotCount;
            }
        } else if (gPadState.pressed & 0xF000) {
            choice = old;
            if (gPadState.pressed & 0x1000) {
                choice = choice == -1 ? D_001A8DB0[4] : gRadialMenuPages[gRadialMenuPageIndex][choice * 7 + 4];
            }
            if (gPadState.pressed & 0x4000) {
                choice = choice == -1 ? D_001A8DB0[5] : gRadialMenuPages[gRadialMenuPageIndex][choice * 7 + 5];
            }
            if (gPadState.pressed & 0x8000) {
                choice = choice == -1 ? D_001A8DB0[2] : gRadialMenuPages[gRadialMenuPageIndex][choice * 7 + 2];
            }
            if (gPadState.pressed & 0x2000) {
                choice = choice == -1 ? D_001A8DB0[3] : gRadialMenuPages[gRadialMenuPageIndex][choice * 7 + 3];
            }
            object->selected = choice;
        }
    }
    if (object->selected != old) {
        PingPongBlendValues(0, 0, 1, 0, 1);
        fade[1] = 0;
        PlaySoundFromGlobalBank(3, 0, 0);
    } else if (fade[1] < 8) ++fade[1];
    if (!(gPadState.held & 0x10)) {
        if (gPadState.released & 0x10) {
            int current = object->selected;
            if (current == -1) gHeroState.choice = 0;
            else gHeroState.choice = gRadialMenuPages[gRadialMenuPageIndex][current * 7 + 6];
        }
        if (D_001A7BB3) AdvanceMenuStateOnMode7();
        if (*fade) --*fade;
    } else if (*fade < 8) ++*fade;
    if (gHeroState.choice == 6 && !D_001B18A0)
        gHeroState.choice = 0;
    if (gHeroState.choice == 7 && !D_001B18A4)
        gHeroState.choice = 0;
    if (gHeroState.choice == 5 && !D_001B18A2)
        gHeroState.choice = 0;
    if (!*fade) {
        D_001B1900 = object->selected;
        D_001B18FC = object->state;
        CloseHudElementByKey(object->handle);
        object->timer = -6;
        D_001B18F8 = D_001B1598;
    }
}
