#include "common.h"

extern int math_random_int_below(int);
extern void moby_mark_spawned(char *);
extern void moby_set_state(char *, int, int);
extern float D_L00_001B19D0;
extern char D_L00_001B8FF0[];
extern int cam_moby_update(char *);
extern int subtract_integer_with_clamp(int);
extern float math_fabs(float);
extern float FastVecDot(char *, char *);
extern int FastTweenColor(unsigned int, int, float);
extern void set_moby_color(char *, int, int, int);

/* Fades the glow object in and out: opens it when its trigger fires, retires it after two ticks of its counter, and keeps its colour pulsing. */
/* Per-frame update of the moby of class 358. */
void glow_fade_update(char *obj)
{
    char *rig = *(char **)(obj + 0x68);
    float shade;
    unsigned int base;
    int color, green, blue;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (cam_moby_update(obj) != 0 || (D_L00_001B19D0 > 0.8f && math_random_int_below(10) == 0)) {
            moby_set_state(obj, 1, -1);
            *(u16 *)(obj + 0x34) |= 0x2800;
        }
        break;
    case 1:
        cam_moby_update(obj);
        if (*(u8 *)(obj + 0x23) < 2) {
            moby_mark_spawned(obj);
            return;
        }
        *(u8 *)(obj + 0x23) -= 2;
        break;
    }
    shade = math_fabs(FastVecDot(obj + 0xC0, D_L00_001B8FF0));
    shade = shade * (shade * shade * shade * shade);
    if (*(u16 *)(obj + 0x96) != 0) {
        shade = (float)(10 - subtract_integer_with_clamp(*(u16 *)(obj + 0x96) - 10)) * 0.1f;
        *(u16 *)(obj + 0x96) = *(u16 *)(obj + 0x96) - 1;
    } else if (math_random_int_below(0x2D) == 0) {
        *(u16 *)(obj + 0x96) = 0x14;
    }
    base = *(unsigned int *)(rig + 0x50);
    if ((base >> 24) != 0)
        shade = shade * 0.8f;
    color = FastTweenColor(base, -1, shade);
    blue = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    set_moby_color(obj, color & 0xFF, green, blue);
}
