#include "common.h"

extern void *CreateMoby(int id);
extern float IntToFloat(int value);
extern void func_002A0F48(void *moby);

/* Creates one waterfall piece of the given class at the parent waterfall's position and copies the parent's settings into it. */
void *waterfall_spawn_piece(void *parent, int class_id, short rotation_speed, int is_open, int link_index, unsigned char min_alpha,
                        unsigned char rotates) {
    unsigned char *parent_bytes = (unsigned char *)parent;
    unsigned char *child = (unsigned char *)CreateMoby(class_id);
    unsigned char *child_vars;

    if (child) {
        child[0x30] = parent_bytes[0x30];
        *(unsigned short *)(child + 0x32) = *(unsigned short *)(parent_bytes + 0x32);
        child[0x31] = 1;
        qcopy(child + 0x10, parent_bytes + 0x10);
        qcopy(child + 0xF0, parent_bytes + 0xF0);
        *(float *)(child + 0xF8) = *(float *)(parent_bytes + 0xF8);
        *(int *)(child + 0xF0) = 0;
        *(int *)(child + 0xF4) = 0;
        child_vars = (unsigned char *)*(unsigned int *)(child + 0x68);
        *(unsigned short *)(child_vars + 0x4) = rotation_speed;
        child_vars[0x1C] = is_open;
        *(float *)(child_vars + 0x8) = IntToFloat(is_open);
        child_vars[0x1D] = rotates;
        *(int *)child_vars = link_index;
        child_vars[0x1E] = min_alpha;
        *(unsigned short *)(child_vars + 0x6) = 0;
        func_002A0F48(child);
        child[0x20] = 0;
    }
    return child;
}
