/* Build object-relative transforms for grouped instances and optional joint attachments. */
#include "common.h"
typedef int V4TI_F36d8a248 __attribute__((mode(TI)));
typedef union { float f[4]; V4TI_F36d8a248 q; } B1320Vec;
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_0029FC20(void *, int, void *);
extern void func_002833F0(void *, void *);
extern void func_00283678(void *, void *);
extern void func_00283738(void *, void *, void *);
extern int func_L00_00323338(void *, void *, int, void *, void *, void *, void *);
extern int func_002A7820(int, int);
extern int D_L00_001B1EB8;
extern short *D_L00_001FA920[];
extern char *D_L00_001B1E9C;
extern int D_L00_001A9018;
extern short **D_L00_001A9014 __attribute__((sda));
extern char *D_L00_001B251C;
extern int D_L00_001A9020 __attribute__((sda));
extern short **D_L00_001A901C;
extern char *D_L00_001B2400;
typedef struct {
    char transform[48];
    float position[4];
    void *offset;
    void *attachment;
    short index;
    unsigned char end, joint, type, copy_matrix, period, phase;
} B1320Entry;
void func_L00_00323448(char *object, B1320Entry *entries, int capacity,
                     int moby_group, int tie_group, int shrub_group,
                     int period, char *attachment)
{
    char joints[40][64] __attribute__((aligned(16)));
    char inverse[48] __attribute__((aligned(16)));
    union { char matrix[48]; B1320Vec vectors[3]; } work;
    char transpose[64] __attribute__((aligned(16)));
    int count, i, joint_count, phase;
    if (capacity <= 0) { entries->end = 0; return; }
    if (moby_group == -1 && tie_group == -1 && shrub_group == -1) {
        entries->end = 0; return;
    }
    joint_count = 0;
    if (attachment) {
        char *p = *(char **)(*(char **)(attachment + 0x24) + 0x1C);
        if (p) joint_count = *(int *)p;
        if (!joint_count || joint_count > 40) return;
        for (i = 0; i < joint_count; ++i) func_0029FC20(attachment, i, joints[i]);
        attachment[0x31] = 0;
        *(unsigned short *)(attachment + 0x34) |= 1;
    }
    euler_rotation_basis(work.matrix, object + 0xF0);
    matrix_from_basis_rows(transpose, work.matrix);
    copy_matrix3x4(inverse, transpose);
    qcopy(work.matrix, object + 0x10);
    count = 0;
    if (moby_group != -1 && moby_group < D_L00_001B1EB8 && D_L00_001FA920[moby_group]) {
        char *moby_item;
        short *moby_ids = D_L00_001FA920[moby_group];
        do {
            int id = *moby_ids & 0x7FFF;
            moby_item = D_L00_001B1E9C + id * 256;
            if (count >= capacity) goto finish;
            entries[count].index = id;
            entries[count].end = 2;
            entries[count].type = 0;
            entries[count].offset = 0;
            if (attachment) {
                entries[count].attachment = attachment;
                if (entries[count].joint == 255) {
                    work.vectors[1].q = *(V4TI_F36d8a248 *)(moby_item + 0x10);
                    work.vectors[2].q = *(V4TI_F36d8a248 *)(moby_item + 0xC0);
                    entries[count].joint = func_L00_00323338(attachment, joints, joint_count, &work.vectors[1], &work.vectors[2], work.matrix, inverse);
                }
            }
            FastVecSub(entries[count].position, moby_item + 0x10, work.matrix);
            matrix_mul_vec3((char *)entries[count].position, (char *)entries[count].position, inverse);
            if (!*(int *)(moby_item + 0x24)) euler_rotation_basis(moby_item + 0xC0, moby_item + 0xF0);
            multiply_matrix3x3(&entries[count], inverse, moby_item + 0xC0);
            *(unsigned short *)(moby_item + 0x34) |= 0x104;
            ++count;
        } while (*moby_ids++ >= 0);
    }
    if (tie_group != -1) {
        phase = 0;
        if (period > 0) phase = func_002A7820(0, period);
        if (tie_group < D_L00_001A9018 && D_L00_001A9014[tie_group]) {
            char *tie_item;
            short *tie_ids = D_L00_001A9014[tie_group];
            do {
                int id = *tie_ids & 0x7FFF;
                tie_item = D_L00_001B251C + id * 64;
                if (count >= capacity) goto finish;
                entries[count].type = 1;
                entries[count].index = id;
                entries[count].end = 2;
                entries[count].offset = 0;
                if (attachment) {
                    entries[count].attachment = attachment;
                    if (entries[count].joint == 255) {
                        work.vectors[1].q = *(V4TI_F36d8a248 *)(tie_item + 0x30);
                        work.vectors[2].q = *(V4TI_F36d8a248 *)(tie_item);
                        entries[count].joint = func_L00_00323338(attachment, joints, joint_count, &work.vectors[1], &work.vectors[2], work.matrix, inverse);
                    }
                }
                if (period <= 0) {
                    if (period < 0) entries[count].period = 255;
                    else entries[count].period = 0;
                } else {
                    entries[count].period = period + 1;
                    entries[count].phase = phase;
                    phase = (phase + 1) % entries[count].period;
                }
                FastVecSub(entries[count].position, tie_item + 0x30, work.matrix);
                matrix_mul_vec3((char *)entries[count].position, (char *)entries[count].position, inverse);
                multiply_matrix3x3(&entries[count], inverse, tie_item);
                ++count;
            } while (*tie_ids++ >= 0);
        }
    }
    if (shrub_group != -1 && shrub_group < D_L00_001A9020 && D_L00_001A901C[shrub_group]) {
        char *shrub_item;
        short *shrub_ids = D_L00_001A901C[shrub_group];
        do {
            int id = *shrub_ids & 0x7FFF;
            shrub_item = D_L00_001B2400 + id * 64;
            if (count >= capacity) goto finish;
            entries[count].type = 2;
            entries[count].end = 2;
            entries[count].offset = 0;
            entries[count].index = id;
            FastVecSub(entries[count].position, shrub_item + 0x30, work.matrix);
            matrix_mul_vec3((char *)entries[count].position, (char *)entries[count].position, inverse);
            multiply_matrix3x3(&entries[count], inverse, shrub_item);
            ++count;
        } while (*shrub_ids++ >= 0);
    }
finish:
    if (count) entries[count - 1].end = 1;
    else entries->end = 0;
}
