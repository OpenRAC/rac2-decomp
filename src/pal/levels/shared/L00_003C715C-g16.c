#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char D_00189E20[];
extern unsigned char D_00138180[];
#define H ((Hero *)D_00189E20)
#define PAD ((Hero *)D_00138180)

extern u8 D_00139581[];
extern int D_L00_001A8F00;
extern int D_L00_001B28EC;
extern float D_L00_001AFEF0[4] __attribute__((sda));
extern int D_L00_001AFF00 __attribute__((sda));
extern int D_L00_001AFF04 __attribute__((sda));
extern void func_L00_003C37A0(char *);
extern void func_PAL_L00_003C7548(char *, void *);
typedef struct { char pad00[0x54]; float rate; char pad58[0xE0 - 0x58]; } AimEntry;
extern AimEntry D_L00_00262570[];
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
extern void func_L00_003FE280(char *, char *);
extern s32 func_002AB1F0(u8 *);
extern void func_002FDF40(float, float, float, float, void *, void *, void *, void *);
extern int func_002FE5A0(float, void *, void *, void *, void *, void *, int *, int *);
extern void func_L00_003FE310(void *, void *, void *);
extern int func_L00_003FE2D0(int, int, int);
struct Rac2Native_5f824a0e369ccf7b_src_record;
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L00_0029F210;
extern int func_L00_002D6998(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern void func_L00_002D6B70(void);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L00_003FE490(void *);

/* func_PAL_L00_003C715C, the PAL copy of func_L00_003C3418: the same C, where 10, 40 and 23 frames
 * become 8, 33 and 19, and the two int timers are scaled to 50 Hz as they are stored.
 * Coordinate the multi-object interaction and its repeat/cooldown timers. */

typedef struct { char *target; int pad04; float timer; s16 delay; s16 repeat; } BeamState;

void func_PAL_L00_003C715C(unsigned char *object) {
    float origin[4];
    AimEntry *entry;
    BeamState *state = *(BeamState **)(object + 0x68);
    char *member;
    u32 color;
    int allowed;
    int phase;

    func_L00_003C37A0(object);
    if (H->i[2213] == 1) func_PAL_L00_002C4480(29, 1);
    if (H->ptr[1300] != 0) H->ptr[766] = H->ptr[1300];
    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        func_002A75E0(object, 1, 0, 8, 0);
    if (state->repeat != 0 && func_00282978(&state->repeat)) func_PAL_L00_002AF6C0();
    func_00283098(origin, D_L00_001AFEF0, object + 0xC0);
    func_00282CC0(origin, origin, object + 0x10);
    func_002829D8(&state->timer);
    allowed = 1;
    if (H->i[2213] == 29) {
        if (!func_00282948(&H->i[2381])) allowed = 0;
        else {
            if (state->timer > 0.0f || !func_L00_002D4040(-1) || object[0x20] != 1)
                color = 0x600000FF;
            else color = 0x600FFF0F;
            func_00273318(1.0f, 0.0f, 90.0f, object, color, 0, 31, -1, 4);
        }
    } else H->i[2381] = 33;
    phase = (u8)object[0x20];
    if (phase == 1) {
        if (D_L00_001A8F00 != 0 || state->timer != 0.0f || H->b[8892] != 0 ||
            (u8)object[0x42] > 1 || !(PAD->u[104] & H->u[1164]) || H->i[1168] < 19 || !allowed) return;
        if (func_L00_002D4040(-1)) {
            func_L00_002D3F30(-1, 1);
            D_L00_001B28EC = phase;
            func_002A75E0(object, 2, 4, 2, 0);
            func_002E5CF8(0, 0, object);
            func_PAL_L00_002AF458();
            object[0x20] = 2;
            state->delay = ((s32)(D_L00_001AFF00) * 5 + 2) / 6;
            state->repeat = ((s32)(D_L00_001AFF04) * 5 + 2) / 6;
        } else if ((PAD->u[105] & H->u[1164]) || D_L00_001B28EC == 1) {
            func_002E5CF8(1, 0, object);
            D_L00_001B28EC = 0;
        }
        entry = D_L00_00262570 + D_00139581[0];
        state->timer = 1.0f / entry->rate;
    } else if (phase == 2) {
        if (!func_00282978(&state->delay)) return;
        func_PAL_L00_003C7548(object, origin);
        object[0x20] = 3;
    } else {
        member = state->target;
        if ((member == 0 || *(s16 *)(member + 0xAA) != 0x5D8 || (u8)member[0x20] == 0xFE ||
             (u8)member[0x20] == 0xFD) && !(PAD->u[104] & H->u[1164])) {
            state->target = 0;
            object[0x20] = 1;
        }
    }
}
