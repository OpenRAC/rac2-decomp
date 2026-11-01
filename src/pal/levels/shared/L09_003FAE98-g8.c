#include "include_asm.h"

typedef struct {
    char pad[0x30];
    float f30;
    float f34;
    char pad2[8];
} PhaseEntry;
extern PhaseEntry *ref_L09_003F65E0_00;
extern PhaseEntry *ref_L09_003F65E0_01 __attribute__((sda));

void func_PAL_L09_003FAE98(char *object) {
    char *state = *(char **)(object + 0x68);

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(unsigned char *)(object + 0x20) = 1;
        break;
    case 1:
        if (*(float *)(state + 4) > 0.0f) {
            ref_L09_003F65E0_00[*(int *)state].f30 += *(float *)(state + 4) * (0.020000001f);
            while (ref_L09_003F65E0_00[*(int *)state].f30 > 1.0f)
                ref_L09_003F65E0_00[*(int *)state].f30 -= 1.0f;
            while (ref_L09_003F65E0_00[*(int *)state].f30 < -1.0f)
                ref_L09_003F65E0_00[*(int *)state].f30 += 1.0f;
        }
        if (*(float *)(state + 8) > 0.0f) {
            ref_L09_003F65E0_01[*(int *)state].f34 += *(float *)(state + 8) * (0.020000001f);
            while (ref_L09_003F65E0_01[*(int *)state].f34 > 1.0f)
                ref_L09_003F65E0_01[*(int *)state].f34 -= 1.0f;
            while (ref_L09_003F65E0_00[*(int *)state].f34 < 1.0f)
                ref_L09_003F65E0_00[*(int *)state].f34 += 1.0f;
        }
        break;
    }
}
