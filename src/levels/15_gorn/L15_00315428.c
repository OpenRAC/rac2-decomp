#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;

extern u32 g_moby_list_address_table[];
extern char *moby_get_motion_data(void *);
extern char *D_L15_001B261C_base[] __asm__("D_L15_001B261C") __attribute__((sda));

/* func_L15_00315428 is defined in L15_00315428-effects-g8.c. */

extern void *func_803804E8(int a0);

/* Stores the second argument into the record the lookup returned. */
void moby_set_record_callback(int id, void *value)
{
    void *record = func_803804E8(id);

    if (record != 0) {
        *(void **)((char *)record + 0x158) = value;
    }
}

/* Counts list entries with an active object, a linked cursor and positive value. */
s32 CountActiveLinkedListObjects(char *list) {
    u16 *cursor;
    char *objectBase;
    char *entry;
    char *vars;
    u32 listAddr;
    s32 info;
    s32 count = 0;
    float threshold;

    listAddr = g_moby_list_address_table[(u8)list[0x21]];
    if (listAddr == 0)
        return 0;
    cursor = (u16 *)listAddr;
    threshold = 0.0f;
    do {
        objectBase = D_L15_001B261C_base[0];
        entry = (char *)(((*cursor & 0x7FFF) << 8) + (u32)objectBase);
        if ((*(u16 *)(entry + 0x34) & 0x20) != 0) {
            vars = *(char **)(entry + 0x68);
            info = moby_get_motion_data(entry);
            if (*(s32 *)vars != 0 && *(s32 *)(info + 0x110) != 0 &&
                threshold < *(float *)(*(s32 *)vars))
                count++;
        }
    } while (*(s16 *)cursor++ >= 0);
    return count;
}




/* func_L15_0041F2F8 is in L15_00315428-f7-g8.c. */

/* func_L15_0042DCE0 is defined in L15_0042DCE0-g8.c. */

/* func_L15_0042E1B0 is defined in L15_0042E1B0-g8.c. */

/* func_L15_0042EFE0 is defined in L15_0042EFE0-g8.c. */

/* func_L15_0042FD40: attempt kept in drafts (148 bytes, +0x4 differs). */
/* func_L15_0042FD40 is defined in L15_00315428-g8.c (this unit has no $gp access for it). */

/* func_L15_0042FFB8 is defined in L15_00315428-g8.c (it reaches a global through $gp). */

/* func_L15_00430168 lives in L15_00430168-g8.c. */

/* func_L15_00430590 is defined in L15_00430590-g8.c. */


/* func_L15_00430B30 is defined in L15_00430B30-g8.c. */


/* func_L15_00430DF0 is defined in L15_00430DF0-g8.c. */

/* func_L15_00431590 is defined in L15_00431590-g8.c. */

/* func_L15_00432008: attempt kept in drafts (176 bytes, 4 instructions over). */
/* func_L15_00432008 is defined in L15_00315428-g8.c (this unit has no $gp access for it). */

/* func_L15_004320B0 is matched in its own unit, src/levels/shared/L15_004320B0-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

extern unsigned char g_gorn_armed_data[];

extern void RebuildExpiredChannelCurves(void *id);
extern void func_802FFC98(void *id, void *value);
extern int func_803068A0(void *id);
extern void func_80329048(void *id);

/* Per-frame update of this moby (class 4522): runs the level update once it is armed. */
void gorn_armed_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x20) == 1) {
        RebuildExpiredChannelCurves(moby);
        func_802FFC98(g_gorn_armed_data, moby);
        if (func_803068A0(vars + 0x54) != 0) {
            func_80329048(moby);
        }
    }
}

/* func_L15_00432210 is defined in L15_00432210-g8.c. */
