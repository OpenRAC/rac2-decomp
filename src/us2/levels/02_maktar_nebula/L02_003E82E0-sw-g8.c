#include "include_asm.h"

#include "common.h"
extern float D_L02_001B0A18[] __attribute__((sda));
typedef union { u8 b[0x200]; u32 w[0x80]; } GameFlags;
extern u8 D_001395B8[];
#define FLAG (((GameFlags *)D_001395B8)->b[0x8F])
extern int D_L02_001B0938[] __attribute__((sda));
extern char D_L02_001B0978[], D_L02_001B09A8[];
extern char D_00188660[];
typedef union { u8 b[0x2600]; f32 f[0x980]; } Hero;
extern u8 D_00189E20[];
extern char D_L02_001A8F20[] __attribute__((sda));
extern int D_L02_001AEC78, D_001A79F8;
extern void func_L00_002E6CF0(void (*)(char *), void *);
extern void func_L02_003E7B58(char *);
extern void func_002A7750(void *, int, int);
extern float func_002A7878(float, float);
extern int func_002A77E0(int), func_002B3868(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_L00_0030C710(int);
extern int func_0026FEB8(char *, ...);
extern int func_US2_002AF9C8(char *, float);
extern int func_002E5CF8(int, int, void *);
extern void func_L02_003E75A8(void *), func_US2_L02_003E8D50(void *), func_002E59F8(int);
extern void func_002A7398(void *, int, int);
extern void func_L02_003E7370(void *);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_002A8BD0(void *, void *, int, float);
extern int func_00277F48(void *, int, void *, void *, float);
extern char *func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern char *func_L02_003CEBB8(int);
extern void func_L02_003CED70(void *, void *, void *);
extern float func_00283248(float, float);
extern void func_0029F338(void *);
extern char *func_002A9640(void *, int, int);
extern void func_L02_003E79F8(void *);
typedef struct { char pad[0x18]; u8 kind; u8 flags; short sourceClass; char tail[0x14]; } Hit003E6D70;
typedef struct { char pad[0xAA]; short classId; } SlotActor003E6D70;
typedef struct {
    char pad0[0x20]; float health; short count; char pad26[10];
    float multiplier; char pad34[0x2C]; float reel[3];
    char pad6c[0x38]; int destroyed;
} SlotState003E6D70;

/* Updates the slot-machine actor. State 0 sets it up and rolls the three reel rates; 2 counts the
   spin (past the 36th, moving 40 of weight 1's share to weight 5) and waits for its animation; 3
   and 4 hand over to their own updates; 5 destroys it, with a blast and two prizes when the word at
   +0xA4 is set. Every state but 5 then takes a hit: a hard one from a class other than 0 and 0x47
   destroys it, and in state 1 one from class 0x47 spends ten bolts and starts a spin. */
void func_US2_L02_003E82E0(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float point[4];
    Hit003E6D70 hit;
    float prizePoint[4];
    char *contact, *other;
    int i, index;
    float *rate;
    float zero;
    SlotState003E6D70 *setup = (SlotState003E6D70 *)state;
    if (*(unsigned char *)(actor + 0x31)) func_L00_002E6CF0(func_L02_003E7B58, actor);
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
    func_002A7750(actor, 1, -1);
    setup->health = 3.0f;
    setup->count = 3;
    setup->multiplier = 1.0f;
    zero = 0.0f;
    setup->destroyed = 0;
    setup->reel[2] = zero;
    setup->reel[1] = zero;
    setup->reel[0] = zero;
    rate = (float *)(state + 0x84);
    for (i = 2; i >= 0; i--) *rate++ = func_002A7878(D_L02_001B0A18[0], D_L02_001B0A18[1]) * 0.016666668f;
    if (func_002A77E0(2)) *(unsigned short *)(actor + 0x34) |= 0x8000;
    else *(unsigned short *)(actor + 0x34) &= 0x7FFF;
    *(unsigned short *)(actor + 0x34) |= 0x4000;
        break;
    case 2:
    if (func_002B3868(actor)) {
        if (*(unsigned char *)(actor + 0x43) != 1) func_002A7470(actor, 1, 0, 1);
        func_L00_0030C710(0xF0);
        if (FLAG < 0x7F) FLAG++;
        if (FLAG > 0x24 && D_L02_001B0938[5] < 30) {
            D_L02_001B0938[5] += 40;
            D_L02_001B0938[1] -= 40;
            func_0026FEB8(D_L02_001B0978);
        }
        func_0026FEB8(D_L02_001B09A8, FLAG);
    }
    if (*(unsigned char *)(actor + 0x43) == 1) {
        if (*(unsigned char *)(actor + 0x60) & 2) {
            *(unsigned short *)(actor + 0x96) = 0;
            func_002A7470(actor, 0, 0, 1);
            func_002A7750(actor, 3, -1);
        } else if (func_US2_002AF9C8(actor, 10.0f)) {
            char *slot = D_00188660 + *(int *)(state + 0x54) * 0x70;
            if (*(char **)(slot + 0x88) != actor || *(unsigned char *)(slot + 0x74) == 0)
                *(int *)(state + 0x54) = func_002E5CF8(1, 4, actor);
        }
    }
        break;
    case 3:
    func_L02_003E75A8(actor);
        break;
    case 4:
    if (func_002B3868(actor)) {
        char *slot;
        index = *(int *)(state + 0x54);
        *(int *)(state + 0x50) = 60;
        if (index != -1) {
            slot = D_00188660 + index * 0x70;
            if (*(char **)(slot + 0x88) == actor && *(unsigned char *)(slot + 0x74)) func_002E59F8(index);
        }
        *(int *)(state + 0x54) = -1;
    }
    func_US2_L02_003E8D50(actor);
        break;
    case 5:
    {
        char *slot;
        index = *(int *)(state + 0x54);
        if (index != -1) {
            slot = D_00188660 + index * 0x70;
            if (*(char **)(slot + 0x88) == actor && *(unsigned char *)(slot + 0x74)) func_002E59F8(index);
        }
    }
    *(int *)(state + 0x54) = -1;
    func_002A7398(actor, 0, 0);
    func_002E5CF8(0, 0, actor);
    func_L02_003E7370(actor);
    *(unsigned short *)(actor + 0x34) = (*(unsigned short *)(actor + 0x34) & 0xBFFF) | 2;
    if (*(int *)(state + 0xA4)) {
        func_L01_0031A278(actor, point, 0.0f, 0.0f, 1.5f);
        func_002A8BD0(&hit, actor, 0x810001, 2.0f);
        hit.kind = 2;
        hit.flags = 1;
        hit.sourceClass = ((SlotActor003E6D70 *)actor)->classId;
        func_00277F48(point, 16, actor, &hit, 4.0f);
        func_0032C700(actor + 0x10, 1, 25, 20, 20, 20, 45, 0, 1, 1, 0, 0, 1.5f, 20.0f);
        if (*(int *)(state + 0x58)) {
            for (i = 0; i < 2; i++) {
                char *prize = func_L02_003CEBB8(*(int *)(state + 0x58));
                if (prize) {
                    func_L01_0031A278(actor, prizePoint, 0.5f, (float)i * 0.9f - 0.45f, 0.0f);
                    func_L02_003CED70(prize, prizePoint, D_L02_001A8F20);
                    *(float *)(prize + 0xF8) = func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(float *)(prize + 0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - *(float *)(prize + 0x14));
                }
            }
        }
    }
    func_0029F338(actor);
    return;
    case 1:
        break;
    }
    contact = func_002A9640(actor, 0x10000, 0);
    if (!contact) return;
    other = *(char **)(contact + 0x20);
    if (other && *(short *)(other + 0xAA) != 0 && *(short *)(other + 0xAA) != 0x47 && *(float *)(contact + 0x2C) > 2.0f) {
        D_L02_001AEC78--;
        func_002A7750(actor, 5, -1);
    } else if (*(unsigned char *)(actor + 0x20) == 1 && other && *(short *)(other + 0xAA) == 0x47 && D_001A79F8 > 9) {
        D_001A79F8 -= 10;
        func_L02_003E79F8(actor);
        func_002A7750(actor, 2, -1);
    }
    *(unsigned char *)(actor + 0xA8) = 0xFF;
}
