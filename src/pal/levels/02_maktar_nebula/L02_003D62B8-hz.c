/* func_PAL_L02_003D62B8, the PAL copy of func_L02_003D2248: the same C, where
   0.0055555556900799274f becomes 0.008f; 0.10333333909511566f becomes 0.124000005f;
   0.0034906589426100254f becomes 0.005026549f; 0.41887909173965454f becomes 0.5026549f; 0xA
   becomes 0x8. */
#include "common.h"

extern void func_31E6A0(char *, int, int);

extern void func_31E3C0(char *, int, int, int);

extern void func_332710(float, float, float, float);

extern void func_316150(char *, int, int, int);

extern void func_316180(char *, int *, int *, int *);

extern void armed_enemy_spawn_held_object(char *self);
void armed_enemy_setup_pal(char *self, int delay) {
    char *state = *(char **)(self + 0x68);

    *(short *)(state + 0x2F6) = 0;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    func_332710(0.008f, 0.124000005f, 0.005026549f,
                0.5026549f);
    func_31E6A0(self, 3, 1);
    if (*(unsigned char *)(self + 0x43) != 0)
        func_31E3C0(self, 0, 0, 0x8);
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
    *(unsigned char *)(state + 0x6A) = 0;
    *(unsigned char *)(state + 0x2E) = 1;
    *(unsigned char *)(self + 0x7F) = 0;
    *(unsigned char *)(self + 0x31) = 1;
    *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) | 0x1000) & 0xFFB8;
    armed_enemy_spawn_held_object(self);
    *(short *)(state + 0x2FC) = delay;
    *(short *)(state + 0x88) = 0;
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_316150(self, *(unsigned char *)(state + 0x54), *(unsigned char *)(state + 0x55),
                    *(unsigned char *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
    if (*(char **)(state + 0x2E4) != 0) {
        int a, b, c;

        func_316180(self, &a, &b, &c);
        func_316150(*(char **)(state + 0x2E4), a, b, c);
    }
}
