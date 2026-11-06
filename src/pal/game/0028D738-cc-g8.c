/* func_PAL_0028D738, the PAL copy of func_0028CCE0: the same C, where rename func_002A9588 becomes func_PAL_002A9FA0. */
#include "common.h"

extern void func_00287E60(void);
extern float func_00282C10(float);
extern float func_00283248(float, float);
extern int func_PAL_002A9FA0(int, int, int, int, int);
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

void func_PAL_0028D738(Selector *object)
{
    float x, y, magnitude, angle;
    int old, choice;
    unsigned char *fade = object->fade;
    func_00287E60();
    object->timeout = 150;
    object->timer = 24;
    D_00138180.mode = 2;
    x = D_00138180.x;
    y = D_00138180.y;
    magnitude = func_00282C10(x * x + y * y);
    if (magnitude != 0.0f) {
        x /= magnitude;
        y /= magnitude;
    }
    angle = func_00283248(x, y);
    if ((object->state >> 24) == 0 && D_001B189C) {
        if (D_00138180.pressed & 0xF000) goto reset_selection;
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
                a = angle + 3.1415927f + 3.1415927f + 1.5707964f + 3.1415927f / (float)D_001B18D0;
                a = a * 0.15915494f * (float)D_001B18D0;
                object->selected = (int)a % D_001B18D0;
            }
        } else if (D_00138180.pressed & 0xF000) {
            choice = old;
            if (D_00138180.pressed & 0x1000) {
                choice = choice == -1 ? D_001A8DB0[4] : D_001B18D4[D_001A8D48][choice * 7 + 4];
            }
            if (D_00138180.pressed & 0x4000) {
                choice = choice == -1 ? D_001A8DB0[5] : D_001B18D4[D_001A8D48][choice * 7 + 5];
            }
            if (D_00138180.pressed & 0x8000) {
                choice = choice == -1 ? D_001A8DB0[2] : D_001B18D4[D_001A8D48][choice * 7 + 2];
            }
            if (D_00138180.pressed & 0x2000) {
                choice = choice == -1 ? D_001A8DB0[3] : D_001B18D4[D_001A8D48][choice * 7 + 3];
            }
            object->selected = choice;
        }
    }
    if (object->selected != old) {
        func_PAL_002A9FA0(0, 0, 1, 0, 1);
        fade[1] = 0;
        func_002E5E58(3, 0, 0);
    } else if (fade[1] < 8) ++fade[1];
    if (!(D_00138180.held & 0x10)) {
        if (D_00138180.released & 0x10) {
            int current = object->selected;
            if (current == -1) D_00189E20.choice = 0;
            else D_00189E20.choice = D_001B18D4[D_001A8D48][current * 7 + 6];
        }
        if (D_001A7BB3) func_00287E18();
        if (*fade) --*fade;
    } else if (*fade < 8) ++*fade;
    if (D_00189E20.choice == 6 && !D_001B18A0)
        D_00189E20.choice = 0;
    if (D_00189E20.choice == 7 && !D_001B18A4)
        D_00189E20.choice = 0;
    if (D_00189E20.choice == 5 && !D_001B18A2)
        D_00189E20.choice = 0;
    if (!*fade) {
        D_001B1900 = object->selected;
        D_001B18FC = object->state;
        func_0028B5D0(object->handle);
        object->timer = -6;
        D_001B18F8 = D_001B1598;
    }
}
