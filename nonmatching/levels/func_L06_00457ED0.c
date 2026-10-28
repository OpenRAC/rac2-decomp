/* Nonmatching Notak group trigger: USA616/616 bytes, 0/1 placements. Eight
 * bounded trials: short-circuit source; explicit hit/second-group guards;
 * no second scheduling; no first scheduling; independently reordered field
 * writes; explicit entry lifetimes; signed group indices; -g. Guard and store
 * forms improved the correspondence, then tied. No flags retained.
 * Remaining differences: first group's nullable entry assignment/delay slot
 * steals the second group load; second group index/table operands use different
 * GPRs. All other control/body instructions in the retained form agree apart
 * from relocations. Reopen with original list iterator/view lifetime evidence.
 *
 * Canonical definitions verified: 2A9640 returns void* and takes pointer,u32,s32;
 * 2A7940 returns float; 2A7470 and458138 are void. Retail animation helper has
 * four GPR parameters and no stable result. Both qcopy transfers cover complete
 * aligned16-byte vectors at state460 and5B0, with default memory clobbers; no nc.
 * Group entries include their final high-bit-marked member before termination.
 * Trigger state spans8bytes; hit record is the complete64-byte collision record.
 * State field accesses reach5BF, object stride256; no local owner allocation.
 * Current qualified Notak update uses the same460/5B0 vectors and timer24C.
 * RAC1 current donor8bbc6b38 was searched for the field/timer family; no equivalent.
 */
#include "common.h"

typedef struct {
    int firstGroup, secondGroup;
} NotakGroupTriggerState;
typedef struct {
    char reserved00[0x20];
    unsigned char *other;
    char reserved24[0x1C];
} NotakTriggerHit;
extern unsigned short *D_L06_001FB3A0[];
extern unsigned char *D_L06_001B281C MACRO_ADDR;
extern void *func_002A9640(void *, unsigned int, int);
extern float func_002A7940(void);
extern void func_002A7470(unsigned char *, int, int, int);
extern void func_L06_00458138(char *);

/* Each group ends with its final index's high bit set. The final member is
 * processed before that sentinel is tested, matching the other Notak groups. */
void func_L06_00457ED0(unsigned char *object)
{
    NotakGroupTriggerState *trigger;
    NotakTriggerHit *hit;
    unsigned short *entry, *group;
    unsigned char *member, *state;
    if (object[0x20] == 0) {
        object[0x20] = 1;
        *(unsigned short *)(object + 0x34) |= 0x800;
    }
    trigger = *(NotakGroupTriggerState **)(object + 0x68);
    hit = func_002A9640(object, 0x10000, 0);
    if (!hit) {
        object[0xA8] = 255;
        return;
    }
    if (*(short *)(hit->other + 0xAA) != 0xFE5) {
        if (trigger->firstGroup != 0xFF && (group = D_L06_001FB3A0[trigger->firstGroup])) {
            entry = group;
            do {
                member = D_L06_001B281C + ((*entry & 0x7FFF) << 8);
                if (*(signed char *)(member + 0x20) >= 0 && *(short *)(member + 0xAA) == 0xBBA) {
                    state = *(unsigned char **)(member + 0x68);
                    if (*(float *)(state + 0x20) > 0.0f) {
                        *(float *)(state + 0x5A4) = func_002A7940();
                        qcopy(state + 0x5B0, state + 0x460);
                        *(short *)(state + 0x24C) = 270;
                        member[0x20] = 4;
                        func_002A7470(member, 6, 0, 10);
                        *(int *)(state + 0x5A0) = 0;
                        *(short *)(state + 0x492) = 0;
                        member[0x20] = 5;
                        member[0x95] = 1;
                    }
                }
            } while (*(short *)entry++ >= 0);
        }
        if (trigger->secondGroup == 0xFF || !(group = D_L06_001FB3A0[trigger->secondGroup])) {
            func_L06_00458138((char *)object);
            return;
        }
        entry = group;
        {
            do {
                member = D_L06_001B281C + ((*entry & 0x7FFF) << 8);
                if (*(signed char *)(member + 0x20) >= 0 && *(short *)(member + 0xAA) == 0xBBA) {
                    state = *(unsigned char **)(member + 0x68);
                    *(float *)(state + 0x5A4) = func_002A7940();
                    qcopy(state + 0x5B0, state + 0x460);
                    *(short *)(state + 0x24C) = 270;
                    member[0x20] = 4;
                    func_002A7470(member, 6, 0, 10);
                    member[0x20] = 5;
                    member[0x95] = 1;
                }
            } while (*(short *)entry++ >= 0);
        }
        func_L06_00458138((char *)object);
    }
    object[0xA8] = 255;
}
