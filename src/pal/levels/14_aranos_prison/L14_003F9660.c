#include "include_asm.h"
#include "common.h"

extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern int func_002ACBC8(void *, int);
extern void func_002B4090(void *, void *, float, float, float);
extern int func_00288E18(int, int);
extern int func_00288D58(void);
extern int func_00287FF8(int, int);
extern void func_L08_0030A8F8(int);
extern char D_00189EA0[];
extern char D_L14_001A8F20[] __attribute__((sda));
extern char *D_L14_001B259C_direct __asm__("D_L14_001B259C") __attribute__((sda));

/* Help-message (subtitle) history: how often each message was shown, when, and in which levels. */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
typedef struct {
    char pad[4];
    unsigned char level;
    char rest[0xDB];
} PrisonGadget;
typedef struct {
    int zone[4];
    int row;
    int hintZone;
    int count;
    int pad1C;
    int target;
    char *moby;
    int active;
} PrisonHelpState;
extern SubtitleHistory D_0018C958[];
extern unsigned char D_00139568[];
extern unsigned char D_00139630;
extern u8 D_0019B2E8[];
extern PrisonGadget D_L14_002686F0[];
extern int D_L14_001A8F00 __attribute__((sda));
extern short D_L14_001B22E0[] __attribute__((sda));
extern unsigned int D_001A7390 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));

/* True once the gadget in slot 10 has reached level MAX. */
static inline int prisonGadgetUpgraded(int max)
{
    int level = (D_L14_002686F0 + D_00139568[10])->level;
    return level >= max;
}

/* Shows help message MSG unless its history entry IDX says it was shown in the last 18 seconds. */
static inline void prisonHelpTimed(int msg, int idx)
{
    if (((int)D_001A7390 * 5 + 2) / 6 - D_0018C958[idx].time > 900 || !D_0018C958[idx].time)
        func_00288E18(msg, idx);
    else if (D_0018C958[idx].time < ((int)D_001A7390 * 5 + 2) / 6)
        D_0018C958[idx].time = ((int)D_001A7390 * 5 + 2) / 6;
}

/* The first time only records history entry IDX as seen in this level; later times show MSG. */
static inline void prisonHelp(int msg, int idx)
{
    if (D_0018C958[idx].count) {
        prisonHelpTimed(msg, idx);
    } else {
        D_0018C958[idx].count++;
        if (D_0018C958[idx].time < ((int)D_001A7390 * 5 + 2) / 6)
            D_0018C958[idx].time = ((int)D_001A7390 * 5 + 2) / 6;
        D_0018C958[idx].levels = (D_0018C958[idx].levels | (1u << D_001A79F0)) | 0x80000000u;
    }
}

/* func_PAL_L14_003F9660, the PAL copy of func_L14_003F4F98: the same C, where the help timers
   run on the 50 Hz scale and the gadget level comes from func_00288D58. */
void func_PAL_L14_003F9660(char *obj)
{
    PrisonHelpState *st = *(PrisonHelpState **)(obj + 0x68);
    float vel[4] __attribute__((aligned(16)));
    int max = func_00288D58() ? 5 : 2;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(short *)(obj + 0x96) = 0;
        *(unsigned char *)(obj + 0x30) = 0xFF;
        if (st->target >= 0)
            st->moby = D_L14_001B259C_direct + (st->target << 8);
        else
            st->moby = 0;
        if (!prisonGadgetUpgraded(max)) {
            if (st->moby)
                st->active = 1;
            else
                st->active = 0;
        } else {
            if (st->moby) {
                *(unsigned short *)(st->moby + 0x34) |= 1;
                st->moby[0x31] = 0;
            }
            st->active = 0;
        }
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (func_002B3868(obj))
            st->count = 0;
        if (func_002ACBC8(D_00189EA0, st->zone[0])) {
            if (!prisonGadgetUpgraded(max))
                func_002A7750(obj, 2, -1);
        }
        if (st->active) {
            qcopy(vel, D_L14_001A8F20);
            vel[1] -= 0.1f;
            func_002B4090(st->moby, vel, 0.05f, 0.0f, 0.0f);
        }
        break;
    case 2:
        if (func_002B3868(obj))
            st->count = 0;
        if (D_L14_001A8F00 != 2 && st->count >= 6) {
            func_00287FF8(10, max);
            func_L08_0030A8F8(2);
            if (st->moby) {
                *(unsigned short *)(st->moby + 0x34) |= 1;
                st->moby[0x31] = 0;
            }
            st->active = 0;
            func_002A7750(obj, 1, -1);
        }
        break;
    }

    if (func_002ACBC8(D_00189EA0, st->zone[1]) && !(D_00139630 & 2))
        prisonHelpTimed(0xA2C, 131);
    if (func_002ACBC8(D_00189EA0, st->zone[2])) {
        prisonHelp(0xA09, 96);
        D_0018C958[97].count = 0xFFFF;
    }
    if (func_002ACBC8(D_00189EA0, st->zone[3]) && D_L14_001B22E0[2])
        prisonHelp(0xA0A, 97);
    if (func_002ACBC8(D_00189EA0, st->hintZone) && !(D_0019B2E8[st->row + D_001A79F0 * 16] & 0x80) &&
        D_0018C958[94].count < 2)
        prisonHelp(0xA07, 94);
    st->count++;
}
