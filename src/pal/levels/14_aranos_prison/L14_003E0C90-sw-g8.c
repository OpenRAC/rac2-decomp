#include "include_asm.h"

#include "common.h"
extern char *D_L14_001B259C __attribute__((sda));
extern char D_00189EA0[];
extern unsigned char D_00188660[];
extern void func_002A7750(void *, int, int);
extern void func_00282CF0(void *dst, void *a, void *b);
extern float func_00282DF0(void *);
extern void func_00282DD8(void *dst, void *a, void *b);
extern int func_L14_003DE2D8(char *);
extern int func_002B3868(void *);
extern int func_002ACBC8(void *, int);
extern void func_L14_003DE488(char *);
extern int func_00282948(int *);
extern int func_L00_00324120(void *);
extern float func_00282E48(void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_L14_003DE360(char *, float);
extern void func_L14_003DE310(char *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* A two-position mover. State 0 stores its two end points (which one is the current
   position depends on word 0x70) and each linked entity's distance to them; state 1 waits on
   func_002ACBC8; states 3 and 4 re-arm the timer at 0x8C and, once func_L00_00324120 says so
   or the player has moved to the other side of the object, start the turn (states 5 and 6),
   which steps func_L14_003DE360 until the angle at 0x80 reaches 0 or pi/2 and then stops the
   object's sound. */
void func_PAL_L14_003E1E48(char *self)
{
    float pos[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float d1[4] __attribute__((aligned(16)));
    float d2[4] __attribute__((aligned(16)));
    char *st = *(char **)(self + 0x68);
    char **ent;
    float *dist;
    int i;
    float f;
    int side;
    unsigned char *sound;

    qcopy(pos, self + 0x10);
    qcopy(rot, self + 0xF0);

    switch ((unsigned char)self[0x20]) {
    case 0:
        *(unsigned short *)(self + 0x34) |= 0x100;
        *(float *)(st + 0x7C) = 0.0087266471f;
        *(int *)(st + 0x78) = -1;
        *(int *)(st + 0x5C) |= 1;
        if (*(int *)(st + 0x70) != 0) {
            qcopy(st + 0x90, self + 0x10);
            qcopy(st + 0xA0, st + 0x60);
            *(float *)(st + 0x80) = 1.5707964f;
            func_002A7750(self, 4, -1);
        } else {
            qcopy(st + 0xA0, self + 0x10);
            qcopy(st + 0x90, st + 0x60);
            *(float *)(st + 0x80) = 0.0f;
            func_002A7750(self, 3, -1);
        }
        qcopy(st + 0xB0, st + 0xA0);
        *(float *)(st + 0xB8) = *(float *)(st + 0x98);
        func_00282CF0(d1, st + 0xA0, st + 0xB0);
        *(float *)(st + 0x84) = func_00282DF0(d1);
        func_00282CF0(d2, st + 0x90, st + 0xB0);
        *(float *)(st + 0x88) = func_00282DF0(d2);
        func_00282DD8(st + 0xC0, d2, d1);
        ent = (char **)(st + 0xE0);
        dist = (float *)(st + 0xF0);
        /* The four linked-entity ids are the words at st+0xD0, just before the distances at
           st+0xF0, so each one is read eight words back from its distance. */
        for (i = 3; i >= 0; i--) {
            if (*(int *)(dist - 8) > 0) {
                *ent = D_L14_001B259C + (*(int *)(dist - 8) << 8);
                func_00282CF0(d1, *ent + 0x10, st + 0xB0);
                f = func_00282DF0(d1);
                if ((unsigned char)self[0x20] == 4) {
                    dist[0] = f;
                    dist[4] = *(float *)(st + 0x84) - *(float *)(st + 0x88) + f;
                } else {
                    dist[4] = f;
                    dist[0] = *(float *)(st + 0x88) - *(float *)(st + 0x84) + f;
                }
            } else {
                *ent = 0;
            }
            ent++;
            dist++;
        }
        if (func_L14_003DE2D8(self) != 0 && *(int *)(st + 0x74) >= 0) {
            func_002A7750(self, 1, -1);
        }
        break;
    case 1:
        func_002B3868(self);
        if (func_002ACBC8(D_00189EA0, *(int *)(st + 0x74)) != 0) {
            func_002A7750(self, 2, -1);
        }
        break;
    case 2:
        func_002A7750(self, 3, -1);
    case 3:
    case 4:
        if (func_002B3868(self) != 0) {
            func_L14_003DE488(self);
            *(int *)(st + 0x8C) = 83;
        }
        func_00282948((int *)(st + 0x8C));
        if (func_L00_00324120(self) == 0) {
            if (!(func_00282E48(D_00189EA0, self + 0x10) < 30.0f)) {
                break;
            }
            /* Which end the player is nearer; the object's own nearer end must differ. */
            side = func_00282E48(D_00189EA0, st + 0x90) > func_00282E48(D_00189EA0, st + 0xA0);
            if ((side ^ (func_00282E48(self + 0x10, st + 0x90) > func_00282E48(self + 0x10, st + 0xA0))) == 0) {
                break;
            }
        }
        if (func_L14_003DE2D8(self) == 0 && *(int *)(st + 0x8C) <= 0) {
            if ((unsigned char)self[0x20] == 4) {
                func_002A7750(self, 5, -1);
            } else {
                func_002A7750(self, 6, -1);
            }
        }
        break;
    case 5:
        if (func_002B3868(self) != 0) {
            *(int *)(st + 0x78) = func_002E5CF8(0, 4, self);
        }
        if (*(float *)(st + 0x80) > 0.0f) {
            func_L14_003DE360(self, -*(float *)(st + 0x7C));
        } else {
            if (*(int *)(st + 0x78) >= 0) {
                if (*(int *)(st + 0x78) != -1) {
                    sound = D_00188660 + *(int *)(st + 0x78) * 0x70;
                    if (*(char **)(sound + 0x88) == self && sound[0x74]) {
                        func_002E59F8(*(int *)(st + 0x78));
                    }
                }
                *(int *)(st + 0x78) = -1;
            }
            if (func_L00_00324120(self) == 0) {
                func_002A7750(self, 3, -1);
            }
        }
        break;
    case 6:
        if (func_002B3868(self) != 0) {
            *(int *)(st + 0x78) = func_002E5CF8(0, 4, self);
        }
        if (*(float *)(st + 0x80) < 1.5707964f) {
            func_L14_003DE360(self, *(float *)(st + 0x7C));
        } else {
            if (*(int *)(st + 0x78) >= 0) {
                if (*(int *)(st + 0x78) != -1) {
                    sound = D_00188660 + *(int *)(st + 0x78) * 0x70;
                    if (*(char **)(sound + 0x88) == self && sound[0x74]) {
                        func_002E59F8(*(int *)(st + 0x78));
                    }
                }
                *(int *)(st + 0x78) = -1;
            }
            if (func_L00_00324120(self) == 0) {
                func_002A7750(self, 4, -1);
            }
        }
        break;
    }
    func_L14_003DE310(self);
    func_00282CF0(delta, self + 0x10, pos);
    func_002AD6F0(st + 0x20, delta, rot, self + 0xF0);
}
