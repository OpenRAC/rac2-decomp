#include "common.h"
extern char g_hero_state[];
extern void moby_transform_joint_point(void *, int, void *);
extern void copy_matrix3x4(void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern int anim_copy_entry_data(void *, int, int, void *);
extern void mem_copy_aligned(void *, void *, int);
extern void func_002A0F48(void *);
extern char g_carry_anim_buffer[];

typedef struct { char pad[0x48]; char *animations[1]; } AnimationTable_b0847;

/* Plays the companion's carried-pose animation and keeps it attached to the hero's hand while the hero holds it, blending between animation frames. */
void companion_update_carry_anim(void) {
    char matrix[64] __attribute__((aligned(16)));
    char *hero = g_hero_state;
    char *companion = *(char **)(hero + 0xC18);
    companion[0x6F] = 0;
    if ((*(u16 *)(*(char **)(hero + 0x2290) + 0x34) ^ 1) & 1) {
        moby_transform_joint_point(*(void **)(hero + 0x2290), 5, matrix);
        qcopy(companion + 0x10, matrix + 0x30);
        copy_matrix3x4(companion + 0xC0, matrix);
        mat_get_euler_angles(matrix, companion + 0xF0);
        *(u16 *)(companion + 0x34) &= 0xFFBE;
        if (*(u8 *)(companion + 0x43) != 0x7A) {
            char *buf = g_carry_anim_buffer;
            companion[0x40] = 1;
            companion[0x42] = 0x7A;
            companion[0x43] = 0x7A;
            *(void **)(companion + 0x58) = anim_copy_entry_data(companion, 0x7A, 1, buf);
            *(void **)(companion + 0x5C) = anim_copy_entry_data(companion, *(u8 *)(companion + 0x43), *(u8 *)(companion + 0x41), buf + 0x600);
        } else if (*(u8 *)(companion + 0x42) == *(u8 *)(companion + 0x43)) {
            *(float *)(companion + 0x44) += *(float *)(companion + 0x48) * *(float *)(companion + 0x4C);
        } else {
            *(float *)(companion + 0x44) += *(float *)(companion + 0x4C);
        }
        if (*(float *)(companion + 0x44) >= 1.0f) {
            char *buf = g_carry_anim_buffer;
            companion[0x40] = companion[0x41];
            *(void **)(companion + 0x58) = buf;
            mem_copy_aligned(buf, buf + 0x600, 0x600);
            ++*(u8 *)(companion + 0x41);
            if (*(u8 *)(companion + 0x41) >= *(u8 *)((*(AnimationTable_b0847 **)(companion + 0x24))->animations[*(u8 *)(companion + 0x43)] + 0x10))
                companion[0x41] = 0;
            *(void **)(companion + 0x5C) = anim_copy_entry_data(companion, *(u8 *)(companion + 0x43), *(u8 *)(companion + 0x41), buf + 0x600);
            *(float *)(companion + 0x44) = (*(float *)(companion + 0x44) - 1.0f) / *(float *)(companion + 0x4C);
            *(float *)(companion + 0x4C) = **(float **)(companion + 0x58);
            *(float *)(companion + 0x44) *= *(float *)(companion + 0x4C);
        }
        func_002A0F48(companion);
    } else {
        *(u16 *)(companion + 0x34) |= 0x41;
    }
}
