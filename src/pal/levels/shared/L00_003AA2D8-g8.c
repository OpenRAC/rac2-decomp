/* func_PAL_L00_003AA2D8, the PAL copy of func_L00_003A6C30: the same C, with the frame timers
 * (D_L00_001AF6C0 to D_L00_001AF6CC, read whole here, and D_001A7390) scaled to 50 Hz,
 * the frame constants 10, 9 and 40 at 8, 7 and 33, and the 1/60 step at 1/50.
 * The null-candidate arm keeps two stores of the timer: the extra reference puts state in $s2.
 * Built with -g like its template.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;
struct Rac2Native_5f824a0e369ccf7b_src_record { u8 b0,b1,b2,b3; u16 s4,s6,s8,s10,s12; u8 e,f; };
typedef struct { char prefix[0x50]; float speed, rate; char middle[0x18]; float damage; char tail[0x6C]; } WeaponEntry;
typedef struct { float radius, spread, power, reserved; float position[4]; } MuzzleLight;

extern char D_00189E20[];
extern int D_00138180[];
extern u8 D_00139568[];
extern Statistics D_0018C750[];
extern u32 D_001A7390;
extern u32 D_001A79F0;
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L00_00294980[], D_L00_00294A00[];
extern int D_L00_001A8F00;
extern float D_L00_001B2868;
extern float D_L00_001B286C;
extern float D_L00_001B2870;
extern int D_L00_001B2874;
extern int D_L00_001AF6C0 __attribute__((sda));
extern int D_L00_001AF6C4 __attribute__((sda));
extern int D_L00_001AF6C8 __attribute__((sda));
extern int D_L00_001AF6CC __attribute__((sda));
extern float D_L00_001B8DC0[4];
extern char *D_L00_001C3280[];
extern WeaponEntry D_L00_00262570[];
extern MuzzleLight D_L00_001C6F40[];

extern void func_PAL_L00_003AB208(char *);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern int func_002829D8(void *);
extern float *func_002AB1F0(char *);
extern int func_002ABB78(char *);
extern void func_002AF000(void *, float, float, float);
extern char *func_L00_00324D18(void *, void *, float, float, float, float, float, int);
extern int func_L00_002D4040(int);
extern int func_L00_002D3F30(int, int);
extern void func_00273318(void *, float, u32, void *, int, float, int, float, int);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern float func_00283CE0(int);
extern void func_002A75E0(void *, int, int, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_L00_002C4480(int, int);
extern void func_PAL_L00_003AAFC8(char *);
extern void func_PAL_L00_003E8BE8(char *);
extern void func_PAL_L00_002AF458(void);
extern void func_PAL_L00_002AF6C0(void);
extern int func_00291308(void *, int, float, float);
extern int func_002E5DA0(int, int, char *, int);
extern int func_002E5CF8(int, int, char *);
extern int func_L00_002D6998(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern int func_L00_002D6978(int);
extern void func_PAL_L00_003E6400(void *, char *, char *, float);
extern void func_PAL_L00_00423E08(void *, char *, char *);
extern int func_00277F48(float, void *, int, void *, int);
extern void func_002A8E20(void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_PAL_L00_003E74D8(void *, int, int);
extern void func_L00_002D6B70(int);
extern void func_00291450(int);
extern void func_00283098(void *, void *, void *);

#define TYPE(m) (*(short *)((m) + 0xAA))

void func_PAL_L00_003AA2D8(char *moby)
{
    Vector muzzle, targetPosition, playerPoint, offset, direction;
    char damage[0x30] __attribute__((aligned(16)));
    Vector center;
    char *state = *(char **)(moby + 0x68);
    char *target = 0;
    float previousRange, horizontal, vertical;
    int specialMode = ((Hero *)D_00189E20)->i[0x1244 / 4] == 3;

    if (D_L00_001A8F00 == 8)
        return;
    if (*(u8 *)(moby + 0x20) == 0) {
        *(u8 *)(moby + 0x20) = 2;
        func_PAL_L00_003AB208(moby);
    }
    horizontal = D_L00_001B2868;
    previousRange = D_L00_001B286C;
    if (TYPE(moby) == 0x5D2)
        D_L00_001B286C = 20.0f;
    else
        D_L00_001B286C = 30.0f;
    if (TYPE(moby) == 0x5D2)
        func_0029FCC0(moby, 0, muzzle);
    else {
        func_00282D30(muzzle, moby + 0xD0, -1.3f);
        func_00282CC0(muzzle, muzzle, moby + 0x10);
    }
    {
        float *dst = (float *)(state + 0x14);
        dst[0] = muzzle[0];
        dst[1] = muzzle[1];
        dst[2] = muzzle[2];
    }
    func_00282D30(playerPoint, (char *)((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0xE0, 0.75f);
    func_00282CC0(playerPoint, &((Hero *)D_00189E20)->f[0x80 / 4], playerPoint);
    vertical = D_L00_001B2870;
    D_L00_001B2868 = D_L00_001B2870 = 0.1047197655f;
    *(int *)(state + 0x2C) = 0;
    func_00282978(state + 6);
    {
        char *locked = *(char **)state;
        if (locked) {
            float *component;
            target = locked;
            component = func_002AB1F0(target);
            if (component) {
                func_00282D30(offset, target + 0xE0, component[4]);
                func_00282CC0(targetPosition, target + 0x10, offset);
            } else {
                qcopy(targetPosition, target + 0x10);
            }
            if (!locked || *(u8 *)(locked + 0x20) == 0xFE || *(u8 *)(locked + 0x20) == 0xFD
                || (component && *component <= 0.0f && !func_002ABB78(locked))
                || !*(u8 *)(locked + 0x31) || ((Hero *)D_00189E20)->h[0x24EC / 2]) {
                target = 0;
                *(short *)(state + 4) = -1;
                *(int *)state = 0;
                *(int *)(state + 8) = 0;
            } else {
                ((Hero *)D_00189E20)->ptr[0xBF8 / 4] = locked;
            }
        }
    }
    if (!((Hero *)D_00189E20)->i[0x1500 / 4] && *(u8 *)(moby + 0x20) == 1 && !((Hero *)D_00189E20)->h[0x24EC / 2] && *(short *)(state + 6) == 0) {
        char *candidate;
        func_002AF000(offset, 1.0f, ((Hero *)D_00189E20)->f[0x778 / 4], ((Hero *)D_00189E20)->f[0x774 / 4]);
        candidate = func_L00_00324D18(playerPoint, offset, vertical, horizontal, previousRange, 0.7853982449f, 0.6108652949f, 1);
        if (candidate) {
            if (candidate == *(char **)(state + 0x30)) {
                if (func_00282948(state + 0x34)) {
                    float *component;
                    target = candidate;
                    *(char **)state = target;
                    *(short *)(state + 4) = *(short *)(target + 0xAA);
                    *(int *)(state + 8) = 0;
                    *(short *)(state + 6) = ((s32)(TYPE(moby) == 0x5D2 ? D_L00_001AF6C0 : D_L00_001AF6C8) * 5 + 2) / 6;
                    component = func_002AB1F0(candidate);
                    if (component) {
                        *(float *)(state + 8) = component[4];
                        func_00282D30(direction, *(char **)state + 0xE0, component[4]);
                        func_00282CC0(targetPosition, *(char **)state + 0x10, direction);
                    } else {
                        qcopy(targetPosition, *(char **)state + 0x10);
                    }
                }
            } else {
                *(int *)(state + 0x34) = ((s32)(TYPE(moby) == 0x5D2 ? D_L00_001AF6C4 : D_L00_001AF6CC) * 5 + 2) / 6;
            }
        } else {
            *(int *)state = 0;
            *(short *)(state + 4) = -1;
            *(int *)(state + 8) = 0;
            target = 0;
            if (TYPE(moby) == 0x5D2)
                *(int *)(state + 0x34) = ((s32)D_L00_001AF6C4 * 5 + 2) / 6;
            else
                *(int *)(state + 0x34) = ((s32)D_L00_001AF6CC * 5 + 2) / 6;
        }
        *(char **)(state + 0x30) = candidate;
    } else if (((Hero *)D_00189E20)->i[0x1500 / 4]) {
        *(int *)state = 0;
    }
    if (((Hero *)D_00189E20)->i[0x2294 / 4] == 29 || ((Hero *)D_00189E20)->i[0x1500 / 4]) {
        func_00273318(moby, 1.0f, *(float *)(state + 0xC) > 0.0f && func_L00_002D4040(-1) ? 0x600000FF : 0x600FFF0F, 0, 0x26, 0.0f, -1, 90.0f, 4);
    }
    if (*(char **)state) {
        float distance = func_00282E48(D_L00_001B8DC0, targetPosition);
        func_00273318(moby, func_00282C48(0.9f - distance * 0.006666667f * 0.65f), 0xFF0FFF0F, targetPosition, 0x26, 0.0f, -1, 90.0f, 4);
    }
    if (*(int *)(state + 0x28) > 0
        && (*(int *)(state + 0x28) > 6 || !(D_00138180[0x1A0 / 4] & ((Hero *)D_00189E20)->i[0x1230 / 4]) || !func_L00_002D4040(-1)))
        (*(int *)(state + 0x28))--;
    if (*(u8 *)(moby + 0x42) == *(u8 *)(moby + 0x43) && (*(u8 *)(moby + 0x60) & 2))
        func_002A75E0(moby, 1, 0, 2, 0);
    switch (*(u8 *)(moby + 0x20)) {
    case 1: {
        int ready;
        if (((Hero *)D_00189E20)->i[0x2294 / 4] == 1)
            func_PAL_L00_002C4480(29, 1);
        ready = 1;
        if (((Hero *)D_00189E20)->i[0x2294 / 4] == 29)
        {
            ready = 0;
            if (func_00282948(&((Hero *)D_00189E20)->i[0x2534 / 4]))
                ready = 1;
        }
        else
            ((Hero *)D_00189E20)->i[0x2534 / 4] = 33;
        if (func_002829D8(state + 0xC) && !((Hero *)D_00189E20)->b[0x22BC] && (D_00138180[0x1A0 / 4] & ((Hero *)D_00189E20)->i[0x1230 / 4]) && ready) {
            if (func_L00_002D3F30(-1, 1)) {
                int count, i;
                D_L00_001B2874 = 1;
                if (D_0018C750[33].count < 0xFFFF)
                    D_0018C750[33].count++;
                if (((s32)D_001A7390 * 5 + 2) / 6 > D_0018C750[33].maximum)
                    D_0018C750[33].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
                D_0018C750[33].levels = (D_0018C750[33].levels | (1u << D_001A79F0)) | 0x80000000u;
                if (TYPE(moby) == 0x5D2)
                    func_PAL_L00_003AAFC8(moby);
                else
                    func_PAL_L00_003E8BE8(moby);
                if (*(short *)(state + 0x10) == 0) {
                    func_PAL_L00_002AF458();
                    *(short *)(state + 0x10) = 1;
                }
                if (*(u8 *)(moby + 0x43) != 2)
                    func_PAL_002A7E68(moby, 2, 0, 0);
                if (*(int *)(state + 0x24) == -1)
                    *(int *)(state + 0x24) = func_00291308(moby + 0x10, 0, 4.0f, 0.0f);
                *(int *)(state + 0x28) = 8;
                func_002E5DA0(0, 0, moby, TYPE(moby));
                if (TYPE(moby) == 0x5D2)
                    func_L00_002D6998(D_L00_00294980);
                else if (*(int *)(state + 0x3C) < 0)
                    *(int *)(state + 0x3C) = func_L00_002D6998(D_L00_00294A00);
                if (TYPE(moby) == 0x5D2)
                    func_PAL_L00_003E6400(muzzle, moby, target, previousRange);
                else
                    func_PAL_L00_00423E08(muzzle, moby, target);
                {
                    WeaponEntry *entry = D_00139568[0x1E] + D_L00_00262570;
                    *(float *)(state + 0xC) = 1.0f / entry->rate;
                }
                count = func_00277F48(0.5f, muzzle, 0, moby, 0);
                for (i = 0; i < count; i++) {
                    float *component;
                    if (D_L00_001C3280[i] == ((Hero *)D_00189E20)->ptr[0x2290 / 4])
                        continue;
                    component = func_002AB1F0(D_L00_001C3280[i]);
                    if (!component)
                        continue;
                    *(int *)(damage + 0x14) = 0x10000;
                    *(int *)(damage + 0x20) = 1;
                    *(char **)(damage + 0x10) = moby;
                    *(float *)(damage + 0x1C) = (D_00139568[0x1E] + D_L00_00262570)->damage;
                    func_00282CF0(offset, D_L00_001C3280[i] + 0x10, muzzle);
                    func_00282F20(offset, offset, (D_00139568[0x1E] + D_L00_00262570)->speed * 0.020000001f);
                    qcopy(damage, offset);
                    func_00282F20(damage, damage, 1.0f);
                    *(float *)(damage + 0xC) = 5627.9248046875f;
                    *(short *)(damage + 0x1A) = TYPE(moby);
                    *(u8 *)(damage + 0x18) = 1;
                    *(u8 *)(damage + 0x19) = 1;
                    func_002A8E20(D_L00_001C3280[i], damage);
                    func_002AFFD8(D_L00_001C3280[i] + 0x10, direction, 1);
                    func_00282D30(direction, direction, component[4]);
                    func_00282CC0(center, direction, D_L00_001C3280[i] + 0x10);
                    func_PAL_L00_003E74D8(center, 0x19, 1);
                }
            } else {
                if ((D_00138180[0x1A4 / 4] & ((Hero *)D_00189E20)->i[0x1230 / 4]) || D_L00_001B2874 == 1) {
                    func_002E5CF8(1, 0, moby);
                    D_L00_001B2874 = 0;
                }
                {
                    WeaponEntry *entry = D_00139568[0x1E] + D_L00_00262570;
                    *(float *)(state + 0xC) = 1.0f / entry->rate;
                }
            }
        }
        if (!((D_00138180[0x1A0 / 4] & ((Hero *)D_00189E20)->i[0x1230 / 4]) && func_L00_002D4040(-1) && ((Hero *)D_00189E20)->b[0x22B8])) {
            if (*(int *)(state + 0x3C) >= 0) {
                func_L00_002D6B70(*(int *)(state + 0x3C));
                *(int *)(state + 0x3C) = -1;
            }
        }
        if (*(int *)(state + 0x3C) > 0 && !func_L00_002D6978(*(int *)(state + 0x3C) - 1))
            *(int *)(state + 0x3C) = -1;
        if (!((D_00138180[0x1A0 / 4] & ((Hero *)D_00189E20)->i[0x1230 / 4]) && func_L00_002D4040(-1))
            && !(((Hero *)D_00189E20)->i[0x1D8 / 4] < 8 && ((Hero *)D_00189E20)->b[0x22B8])) {
            func_PAL_L00_002AF6C0();
            *(short *)(state + 0x10) = 0;
        }
        break;
    }
    case 2:
        func_PAL_L00_002AF6C0();
        if (func_002829D8(state + 0xC))
            *(u8 *)(moby + 0x20) = 1;
        break;
    }
    if (*(int *)(state + 0x24) != -1) {
        if (specialMode || *(int *)(state + 0x28) <= 0) {
            func_00291450(*(int *)(state + 0x24));
            *(int *)(state + 0x24) = -1;
        } else {
            float ratio;
            qzero_nc(offset);
            offset[0] = 2.0f;
            offset[2] = 2.0f;
            func_00283098(offset, offset, &((Hero *)D_00189E20)->f[0x730 / 4]);
            (*(int *)(state + 0x24) + D_L00_001C6F40)->position[0] = ((Hero *)D_00189E20)->f[0x80 / 4] + offset[0];
            (*(int *)(state + 0x24) + D_L00_001C6F40)->position[1] = ((Hero *)D_00189E20)->f[0x84 / 4] + offset[1];
            (*(int *)(state + 0x24) + D_L00_001C6F40)->position[2] = ((Hero *)D_00189E20)->f[0x88 / 4] + offset[2];
            (*(int *)(state + 0x24) + D_L00_001C6F40)->position[3] = 4.0f;
            {
                float b;
                ratio = func_00283CE0(*(int *)(state + 0x28));
                b = func_00283CE0(8);
                ratio /= b;
                /* Both weapons light the muzzle the same way. */
                if (TYPE(moby) == 0x5D2) {
                    (*(int *)(state + 0x24) + D_L00_001C6F40)->radius = ratio;
                    (*(int *)(state + 0x24) + D_L00_001C6F40)->spread = ratio * 0.5f;
                    (*(int *)(state + 0x24) + D_L00_001C6F40)->power = (*(int *)(state + 0x24) + D_L00_001C6F40)->spread;
                } else {
                    (*(int *)(state + 0x24) + D_L00_001C6F40)->radius = ratio;
                    (*(int *)(state + 0x24) + D_L00_001C6F40)->spread = ratio * 0.5f;
                    (*(int *)(state + 0x24) + D_L00_001C6F40)->power = (*(int *)(state + 0x24) + D_L00_001C6F40)->spread;
                }
            }
        }
    }
}
