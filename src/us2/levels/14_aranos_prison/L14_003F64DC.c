#include "include_asm.h"
#include "common.h"

/* func_US2_L14_003F64DC, the USA v2.00 copy of func_L14_003F4F98: the same C, where the gadget
   level limit 2 becomes limit = func_00288D58() ? 5 : 2, and the two-armed func_00287FF8 call
   becomes func_00287FF8(10, limit). */

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

/* True once the gadget in slot 10 has been upgraded. */
static inline int prisonGadgetUpgraded(int limit)
{
    int level = (D_L14_002686F0 + D_00139568[10])->level;

    return level >= limit;
}

/* Shows help message MSG unless its history entry IDX says it was shown in the last 18 seconds. */
static inline void prisonHelpTimed(int msg, int idx)
{
    if (D_001A7390 - D_0018C958[idx].time > 1080 || !D_0018C958[idx].time)
        func_00288E18(msg, idx);
    else if (D_0018C958[idx].time < D_001A7390)
        D_0018C958[idx].time = D_001A7390;
}

/* The first time only records history entry IDX as seen in this level; later times show MSG. */
static inline void prisonHelp(int msg, int idx)
{
    if (D_0018C958[idx].count) {
        prisonHelpTimed(msg, idx);
    } else {
        D_0018C958[idx].count++;
        if (D_0018C958[idx].time < D_001A7390)
            D_0018C958[idx].time = D_001A7390;
        D_0018C958[idx].levels = (D_0018C958[idx].levels | (1u << D_001A79F0)) | 0x80000000u;
    }
}

/* Drives the prison's help prompts: links the target moby, plays the hints at the trigger zones
   and records which help messages were already shown. */
void func_US2_L14_003F64DC(char *obj)
{
    PrisonHelpState *st = *(PrisonHelpState **)(obj + 0x68);
    float vel[4] __attribute__((aligned(16)));
    int limit = 2;

    if (func_00288D58())
        limit = 5;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(short *)(obj + 0x96) = 0;
        *(unsigned char *)(obj + 0x30) = 0xFF;
        if (st->target >= 0)
            st->moby = D_L14_001B259C_direct + (st->target << 8);
        else
            st->moby = 0;
        if (!prisonGadgetUpgraded(limit)) {
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
            if (!prisonGadgetUpgraded(limit))
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
            func_00287FF8(10, limit);
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
