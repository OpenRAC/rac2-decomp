/* func_PAL_L09_003FCF28, the PAL copy of func_L09_003F8598: the same C, where the frame count stored at 0x2E0 is scaled for 50 Hz. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int D_L09_001B2878 __attribute__((sda));

/* An absolute view of the canonical pool pointer; its extent stays unknown. */
extern unsigned char *D_L09_001B285C_base[] __asm__("D_L09_001B285C") __attribute__((sda));

extern unsigned short *D_L09_001FB560[];

extern unsigned char *D_L09_001FE6C0[];

extern int D_L09_001B0F58 __attribute__((sda));

extern float func_00282E80(void *, void *);

extern int func_L09_003F72A8(unsigned char *);

extern int func_L09_003F71C8(unsigned char *, int);

void func_PAL_L09_003FCF28(unsigned char *object) {
    unsigned char *source_data = *(unsigned char **)(object + 0x68);
    TI128 position;
    unsigned short *list;
    unsigned char *candidate;
    unsigned char *pool;
    unsigned char *candidate_data;
    unsigned char *best;
    unsigned char *best_data;
    int frame;
    int target_index;
    float best_distance;
    float distance;
    int group;

    target_index = *(int *)(source_data + 0x2C0);
    if (target_index == -1)
        return;
    qcopy(&position, D_L09_001FE6C0[target_index] + 0x10);
    list = D_L09_001FB560[object[0x21]];
    best = 0;
    best_distance = 100000.0f;
    for (;
         object[0x21] != 0xFF && object[0x21] <= D_L09_001B2878 && list != 0 &&
         ((list != 0 && (short)list[-1] >= 0) || list == D_L09_001FB560[object[0x21]]);
         list++) {
        pool = D_L09_001B285C_base[0];
        candidate = pool + ((*list & 0x7FFF) << 8);
        if (candidate == 0)
            break;
        candidate_data = *(unsigned char **)(candidate + 0x68);
        distance = func_00282E80(candidate + 0x10, &position);
        if (candidate_data == 0)
            continue;
        if ((candidate_data[0x302] & 1) == 0)
            continue;
        if (*(int *)(source_data + 0x420) != -1) {
            group = func_L09_003F72A8(object) + 1;
            if (group != *(int *)(candidate_data + 0x420))
                continue;
            if (func_L09_003F71C8(candidate, group) >= *(int *)(candidate_data + 0x42C))
                continue;
        }
        if (*(int *)(source_data + 0x424) != 0 && *(int *)(source_data + 0x424) != *(int *)(candidate_data + 0x424))
            continue;
        if (distance < best_distance) {
            best_distance = distance;
            best = candidate;
        }
    }
    if (best != 0) {
        best_data = *(unsigned char **)(best + 0x68);
        frame = D_L09_001B0F58;
        *(int *)(best_data + 0x2B0) = *(int *)(source_data + 0x2B0);
        *(int *)(best_data + 0x2B4) = *(int *)(source_data + 0x2B4);
        *(int *)(best_data + 0x2B8) = *(int *)(source_data + 0x2B8);
        *(int *)(best_data + 0x2BC) = *(int *)(source_data + 0x2BC);
        *(int *)(best_data + 0x2C0) = *(int *)(source_data + 0x2C0);
        *(int *)(best_data + 0x2D0) = *(int *)(source_data + 0x2D0);
        *(int *)(best_data + 0x2D4) = *(int *)(source_data + 0x2D4);
        *(unsigned short *)(best_data + 0x2E0) = ((s32)(frame) * 5 + 2) / 6;
        *(int *)(best_data + 0x2DC) = *(int *)(source_data + 0x2C0);
        best_data[0x2EA] = 1;
        best_data[0x302] = (best_data[0x302] | 2) & 0xFE;
        best_data[0x303] = source_data[0x303];
        *(unsigned short *)(best + 0x34) = *(unsigned short *)(best + 0x34) & 0xFFFD;
        best_data[0x31D] = 1;
        best_data[0x31C] = 1;
    }
}
