/* func_PAL_L00_00402D4C, the PAL copy of func_L00_003FE4C8: the same C, with the
 * timers scaled to 50 Hz, and the same function as func_PAL_L02_0042DE18. */
#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char D_00189E20[];
extern unsigned char D_00138180[];

extern u8 D_00139581[];
extern int D_L00_001A8F00;
extern int D_L00_001B2BE8;
extern float D_L00_001B0BF0[4] __attribute__((sda));
extern int D_L00_001B0C00 __attribute__((sda));
extern int D_L00_001B0C04 __attribute__((sda));
extern int D_L00_001B0C08 __attribute__((sda));
extern int D_L00_001B0C0C __attribute__((sda));
typedef struct { char pad00[0x54]; float rate; char pad58[0xE0 - 0x58]; } AimEntry;
extern AimEntry D_L00_00262570[];
extern void func_L00_003FE8D0(char *);
extern void func_PAL_L00_002C4480(int, int);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_00282978(s16 *);
extern int func_00282948(int *);
extern void func_002829D8(float *);
extern void func_PAL_L00_002AF6C0(void);
extern void func_PAL_L00_002AF458(void);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_L00_002D4040(int);
extern int func_L00_002D3F30(int, int);
/* The caller deliberately supplies a sixth GPR word (4) in the call slot;
 * retail overwrites it before consumption. Original return/unused-formal
 * intent remains unqualified, but the observed call prefix is preserved. */
extern void func_00273318(float, float, float, void *, u32, void *, int, int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_PAL_L00_00403200(char *, void *, int, void *);
extern void func_PAL_L00_004033A8(char *, void *, void *, int);

/* Coordinate the multi-object interaction and its repeat/cooldown timers. */

typedef struct { float timer; s16 delay; s16 repeat; int index; int pad0C; char *list[0]; } BeamState;

void func_PAL_L00_00402D4C(unsigned char *object) {
    float origin[4];
    float destination[4];
    AimEntry *entry;
    BeamState *state = *(BeamState **)(object + 0x68);
    char **list;
    char *member;
    u32 color;
    int allowed;
    int any;
    int count;
    int index;
    int i;
    int phase;

    func_L00_003FE8D0(object);
    if (((Hero *)D_00189E20)->i[2213] == 1) func_PAL_L00_002C4480(29, 1);
    if (((Hero *)D_00189E20)->ptr[1300] != 0) ((Hero *)D_00189E20)->ptr[766] = ((Hero *)D_00189E20)->ptr[1300];
    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        func_002A75E0(object, 1, 0, 5, 0);
    if (state->repeat != 0 && func_00282978(&state->repeat)) func_PAL_L00_002AF6C0();
    func_00283098(origin, D_L00_001B0BF0, object + 0xC0);
    func_00282CC0(origin, origin, object + 0x10);
    func_002829D8(&state->timer);
    allowed = 1;
    if (((Hero *)D_00189E20)->i[2213] == 29) {
        if (!func_00282948(&((Hero *)D_00189E20)->i[2381])) allowed = 0;
        else {
            if (state->timer > 0.0f || !func_L00_002D4040(-1) || object[0x20] != 1)
                color = 0x600000FF;
            else color = 0x600FFF0F;
            func_00273318(1.0f, 0.0f, 90.0f, object, color, 0, 31, -1, 4);
        }
    } else ((Hero *)D_00189E20)->i[2381] = 33;
    phase = (u8)object[0x20];
    if (phase == 1) {
        if (D_L00_001A8F00 != 0 || !allowed || state->timer != 0.0f || ((Hero *)D_00189E20)->b[8892] != 0 ||
            (u8)object[0x42] > 1 || !(((Hero *)D_00138180)->u[104] & ((Hero *)D_00189E20)->u[1164]) || ((Hero *)D_00189E20)->i[1168] < 19) return;
        if (func_L00_002D4040(-1)) {
            func_L00_002D3F30(-1, 1);
            D_L00_001B2BE8 = phase;
            if (((Hero *)D_00189E20)->i[2213] != 29) func_002A75E0(object, 2, 0, 2, 0);
            func_002E5CF8(0, 0, object);
            func_PAL_L00_002AF458();
            object[0x20] = 2;
            state->delay = ((s32)D_L00_001B0C00 * 5 + 2) / 6;
            state->repeat = ((s32)D_L00_001B0C08 * 5 + 2) / 6;
            state->index = 0;
        } else if ((((Hero *)D_00138180)->u[105] & ((Hero *)D_00189E20)->u[1164]) || D_L00_001B2BE8 == 1) {
            func_002E5CF8(1, 0, object);
            D_L00_001B2BE8 = 0;
        }
        entry = D_L00_00262570 + D_00139581[0];
        state->timer = 1.0f / entry->rate;
    } else if (phase == 2) {
        if (!func_00282978(&state->delay)) return;
        func_PAL_L00_00403200(object, destination, state->index, origin);
        func_PAL_L00_004033A8(object, origin, destination, state->index);
        index = state->index + 1;
        state->index = index;
        if (index >= D_L00_001B0C0C) object[0x20] = 3;
        else state->delay = ((s32)D_L00_001B0C04 * 5 + 2) / 6;
    } else {
        any = 0;
        count = D_L00_001B0C0C;
        for (i = 0; i < count; i++) {
            list = state->list + i;
            member = *list;
            if (member != 0) {
                any = 1;
                if ((*(s16 *)(member + 0xAA) != 0x5D8 || (u8)member[0x20] == 0xFE ||
                     (u8)member[0x20] == 0xFD) && !(((Hero *)D_00138180)->u[104] & ((Hero *)D_00189E20)->u[1164])) *list = 0;
            }
        }
        if (!any) object[0x20] = 1;
    }
}
