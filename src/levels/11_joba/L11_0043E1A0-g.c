#include "include_asm.h"
#include "common.h"

#define S16(p,o) (*(short *)((p)+(o)))
#define U16(p,o) (*(unsigned short *)((p)+(o)))
#define I32(p,o) (*(int *)((p)+(o)))
#define F32(p,o) (*(float *)((p)+(o)))
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C __attribute__((section(".sdata")));
extern u8 D_00189E20[];
extern void func_L11_00445DF8(u8 *, int, float, float);
extern int func_L00_0035F5A0(int, int, int);
extern int func_00282978(short *);
/* Tallies the group's living members and their health, records the losses in
 * the four-slot history and stores their weighted sum at 0x14C. Built with -g:
 * the debug line layout gives retail's single nop before div.s. */
void func_L11_00440360(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    short *list;
    short *groupList;
    int active, i, slot, kind;
    float total, weights, energy, motion;
    u8 *member, *detail, *members;
    typedef struct { u8 pad[0x20]; float health; } MemberHealth;
    typedef struct { int value; int pad[3]; } HistInt;
    typedef struct { float value; int pad[3]; } HistFloat;
    struct HistoryFields { int count; float energy, motion; int pad; };
    struct StateHistory { u8 pad[0x50]; struct HistoryFields history[4]; };
    struct StateClassCount { u8 pad[0x200]; unsigned short count; };
    u8 *counts;
    u8 *energies;
    u8 *motions;
    u8 *player;
    if (I32(state,0xc0) == 255) return;
    groupList = (short *)D_L11_001FC420[I32(state,0xc0)];
    if (groupList == 0) return;
    list = groupList;
    if (object[0x20] == 9 && object[0xbc] == 0) return;
    ((struct StateClassCount *)state)->count = 0;
    active=0; total=0.0f;
    members=D_L11_001B359C;
    do {
        member = members + ((*list & 0x7fff) << 8);
        if (member != 0 && member[0x20] != 254 && member[0x20] != 253 && member[0x20] != 1) {
            kind = S16(member,0xaa);
            if (kind == 0xd98) {
                MemberHealth *hp = *(MemberHealth **)(member+0x68);
                total += hp->health;
                if (hp->health > 0.0f) active++;
            } else if (kind == 0xdcf) {
                MemberHealth *hp = *(MemberHealth **)(member+0x68);
                total += hp->health;
                if (hp->health > 0.0f) active++;
            } else if (kind == 0xdf4) {
                MemberHealth *hp = *(MemberHealth **)(member+0x68);
                total += hp->health;
                if (hp->health > 0.0f) active++;
            } else if (kind == 0xdf7) {
                MemberHealth *hp = *(MemberHealth **)(member+0x68);
                total += hp->health;
                if (hp->health > 0.0f) active++;
            } else if (kind == 0xdf9) {
                MemberHealth *hp = *(MemberHealth **)(member+0x68);
                total += hp->health;
                if (hp->health > 0.0f) active++;
            } else if (kind == 0xd37) {
                MemberHealth *hp = *(MemberHealth **)(member+0x68);
                total += hp->health;
                U16(state,0x200)++;
                if (hp->health > 0.0f) active++;
            } else if (kind == 0xd4a) {
                MemberHealth *hp = *(MemberHealth **)(member+0x68);
                active++;
                total += hp->health;
            } else if (kind == 0xd4b) {
                MemberHealth *hp = *(MemberHealth **)(member+0x68);
                total += hp->health;
                if (hp->health > 0.0f) active++;
            } else if (kind == 0xb3a) {
                MemberHealth *hp = *(MemberHealth **)(member+0x68);
                active++;
                total += hp->health;
            }
        }
    } while (*list++ >= 0);
    player = D_00189E20;
    func_L11_00445DF8(object, I32(state,0x140)-active, F32(state,0x144)-total,
        F32(state,0x148)-(float)I32(player,0x24cc));
    if (F32(state,0x148)-(float)I32(player,0x24cc) > 0.0f)
        func_L00_0035F5A0(0x17,0,0);
    if (active < I32(state,0x140))
        ((struct StateHistory *)state)->history[S16(state,0x1ec)].count += I32(state,0x140)-active;
    if (total < F32(state,0x144))
        ((struct StateHistory *)state)->history[S16(state,0x1ec)].energy += F32(state,0x144)-total;
    if ((float)I32(player,0x24cc) < F32(state,0x148))
        ((struct StateHistory *)state)->history[S16(state,0x1ec)].motion += F32(state,0x148)-(float)I32(player,0x24cc);
    F32(state,0x144) = total;
    I32(state,0x140) = active;
    F32(state,0x148) = (float)I32(player,0x24cc);
    weights=0.0f; energy=0.0f; motion=0.0f;
    for (i=4;i>0;i--) {
        float countTerm, energyTerm, motionTerm;
        float denominator = 5.0f-(float)i;
        float weight = 1.0f / denominator; energyTerm = weight*((struct StateHistory *)state)->history[(S16(state,0x1ec)+i)%4].energy;
        countTerm = weight*(float)((struct StateHistory *)state)->history[(S16(state,0x1ec)+i)%4].count;
        motionTerm = weight*((struct StateHistory *)state)->history[(S16(state,0x1ec)+i)%4].motion;
        energy += energyTerm;
        motion += motionTerm;
        weights += countTerm;
    }
    F32(state,0x14c) = energy*0.2f + weights + motion * -2.0f;
    if (func_00282978((short *)(state+0x1ee))) {
        S16(state,0x1ec) = (short)(U16(state,0x1ec)+1)%4;
        ((struct StateHistory *)state)->history[S16(state,0x1ec)].count=0;
        ((struct StateHistory *)state)->history[S16(state,0x1ec)].energy=0;
        ((struct StateHistory *)state)->history[S16(state,0x1ec)].motion=0;
        S16(state,0x1ee)=600;
    }
}
