#include "common.h"

/* A unit of its own so that the call to func_L02_003D1ED0 goes through its symbol: PAL has has
   that function as assembly at an address of its own, and a call within one object can only
   reach the object's own copy. */

typedef int TI128 __attribute__((mode(TI)));
extern void func_31E6A0(char *, int, int);
extern void func_31E3C0(char *, int, int, int);
extern void armed_enemy_release_held_object(char *, TI128 *);
extern void enemy_release_effect_record(char *);
extern void func_3FC1B0(char *, int);
extern void func_315348(char *, char *);
extern void func_2F1CC8(char *, int, int);
extern void func_316220(char *);

/* Rebuilds the actor's shared effect record after the sub-object has gone. */
void enemy_release_effect_record(char *self) {
    char *state = *(char **)(self + 0x68);

    if (*(char **)(state + 0x2E4) != 0) {
        TI128 pos = *(TI128 *)(*(char **)(state + 0x2E4) + 0x10);

        armed_enemy_release_held_object(self, &pos);
    }
    if (*(short *)(state + 0x2F6) == 1)
        func_3FC1B0(*(char **)(self + 0xB8), 0x9CA);
    *(short *)(state + 0x2F6) = 0;
    *(int *)(state + 0x2E0) = 0;
    if (*(unsigned char *)(state + 0x291) != 0) {
        *(unsigned char *)(state + 0x292) = 0;
        *(float *)(state + 0x2B0) = *(float *)(state + 0x2B4) = *(float *)(state + 0x2B8) = 1.0f;
        func_315348(self, state + 0x290);
        func_2F1CC8(state + 0x290, 0, 0x40);
    }
    func_31E3C0(self, 0, 0, 3);
    func_316220(self);
    func_31E6A0(self, 1, 0);
    *(unsigned char *)(self + 0x31) = 0;
    *(int *)(self + 0x98) = 0;
    *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) & 0xEFFF) | 0x47;
}
