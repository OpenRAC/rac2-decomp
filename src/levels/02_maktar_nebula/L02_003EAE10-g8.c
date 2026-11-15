#include "include_asm.h"
#include "names.h"

/* func_L02_003EAE10 is a unit of its own: it reads $gp data (hence -G8) and needs the opt-in
   clear profile (-frac2-zero-ti-barrier, docs/build/compiler-notes.md): with it, the load of the
   state's +0x3C float follows the 16-byte clear at once, as retail has it. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int TI128 __attribute__((mode(TI)));

extern u16 *g_entity_group_lists[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));

extern void euler_rotation_basis(float *, float *);
extern void matrix_from_basis_rows(float *, float *);
extern void FastVecSub(float *, float *, float *);
extern void matrix_mul_vec3(float *, float *, float *);
extern float math_fabs(float);

/* Checks that no other waiting platform of the group sits farther along its
   swing than this one. */
int swing_platform_is_leading(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float angles[4];
    float rotation[12];
    float inverse[16];
    float offset[4];
    float otherOffset[4];
    float limit;
    u16 *listEntry;
    u8 *entity;

    if (*(u8 *)(actor + 0x21) == 0xFF)
        return 1;
    *(TI128 *)angles = 0;
    angles[2] = *(float *)(state + 0x3C);
    euler_rotation_basis(rotation, angles);
    matrix_from_basis_rows(inverse, rotation);
    FastVecSub(offset, (float *)(state + 0x30), (float *)(actor + 0x10));
    matrix_mul_vec3(offset, offset, inverse);
    limit = math_fabs(offset[1]);
    for (listEntry = g_entity_group_lists[*(u8 *)(actor + 0x21)];
         *(u8 *)(actor + 0x21) != 0xFF && *(u8 *)(actor + 0x21) <= D_L02_001B35B8 && listEntry != 0 &&
         ((listEntry != 0 && (s16)listEntry[-1] >= 0) || listEntry == g_entity_group_lists[*(u8 *)(actor + 0x21)]);
         listEntry++) {
        entity = D_L02_001B359C_1[0] + ((*listEntry & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity != (u8 *)actor && *(short *)(entity + 0xAA) == 0xAB0 /* moby class 2736 */ && entity[0x20] == 3) {
            FastVecSub(otherOffset, (float *)(*(char **)(entity + 0x68) + 0x30), (float *)(entity + 0x10));
            matrix_mul_vec3(otherOffset, otherOffset, inverse);
            if (limit < math_fabs(otherOffset[1]))
                return 0;
        }
    }
    return 1;
}
