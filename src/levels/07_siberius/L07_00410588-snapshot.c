#include "common.h"
typedef int SibQuad __attribute__((mode(TI)));

typedef struct {
    u8 prefix[0x30];
    SibQuad position;
    u8 middle[0x30];
    SibQuad rotation;
} SibRecord128;

extern SibRecord128 *g_shooter_mount_table __attribute__((sda));
extern u8 *g_joint_record_table __attribute__((sda));
extern u8 g_ship_joint_tag;
extern void euler_rotation_basis(void *, void *);
extern void BuildObjectAttachmentTransforms(void *, void *, int, int, int, int, int, int);

/* Briefly moves the object to its saved start position to build its attached joint pointers, then puts its real position back. */
void ship_build_joint_pointers(u8 *moby)
{
    SibQuad saved[2];
    u8 *vars = *(u8 **)(moby + 0x68);
    SibRecord128 *records;
    int index;
    u8 *joint_out;
    u8 *end;
    int count;
    u8 *cursor;
    u8 tag;
    qcopy(&saved[0], moby + 0x10);
    qcopy(&saved[1], moby + 0xF0);
    index = *(int *)(vars + 0xC8);
    records = g_shooter_mount_table;
    qcopy(moby + 0x10, &records[index].position);
    qcopy(moby + 0xF0, &records[index].rotation);
    euler_rotation_basis(moby + 0xC0, moby + 0xF0);
    BuildObjectAttachmentTransforms(moby, vars + 0x1B0, 0x40, -1, *(int *)(vars + 0xCC), -1, 7, 0);
    cursor = vars;
    tag = g_ship_joint_tag;
    end = cursor + 0x1400;
    count = 0;
    joint_out = cursor + 0x15B0;
    do {
        s16 id = *(s16 *)(cursor + 0x1F8);
        u8 *table = g_joint_record_table;
        if (table[(id << 5) + 0x1D] == tag) {
            *(u8 **)(cursor + 0x1F0) = joint_out;
            count++;
            cursor[0x1FE] = 0;
            joint_out += 0x20;
        }
        cursor += 0x50;
        if (count >= 8)
            break;
    } while ((s32)cursor < (s32)end);
    qcopy(moby + 0x10, &saved[0]);
    qcopy(moby + 0xF0, &saved[1]);
    euler_rotation_basis(moby + 0xC0, moby + 0xF0);
}
