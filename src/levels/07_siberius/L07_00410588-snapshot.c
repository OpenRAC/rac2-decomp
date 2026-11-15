#include "common.h"
typedef int SibQuad __attribute__((mode(TI)));

typedef struct {
    u8 prefix[0x30];
    SibQuad position;
    u8 middle[0x30];
    SibQuad rotation;
} SibRecord128;

extern SibRecord128 *D_L07_001B23CC __attribute__((sda));
extern u8 *D_L07_001B2954 __attribute__((sda));
extern u8 D_L07_00227E7F;
extern void func_002833F0(void *, void *);
extern void func_L00_00323448(void *, void *, int, int, int, int, int, int);

void func_L07_00410588(u8 *self)
{
    SibQuad saved[2];
    u8 *state = *(u8 **)(self + 0x68);
    SibRecord128 *records;
    int index;
    u8 *out;
    u8 *end;
    int count;
    u8 *cursor;
    u8 tag;
    qcopy(&saved[0], self + 0x10);
    qcopy(&saved[1], self + 0xF0);
    index = *(int *)(state + 0xC8);
    records = D_L07_001B23CC;
    qcopy(self + 0x10, &records[index].position);
    qcopy(self + 0xF0, &records[index].rotation);
    euler_rotation_basis(self + 0xC0, self + 0xF0);
    BuildObjectAttachmentTransforms(self, state + 0x1B0, 0x40, -1, *(int *)(state + 0xCC), -1, 7, 0);
    cursor = state;
    tag = D_L07_00227E7F;
    end = cursor + 0x1400;
    count = 0;
    out = cursor + 0x15B0;
    do {
        s16 id = *(s16 *)(cursor + 0x1F8);
        u8 *table = D_L07_001B2954;
        if (table[(id << 5) + 0x1D] == tag) {
            *(u8 **)(cursor + 0x1F0) = out;
            count++;
            cursor[0x1FE] = 0;
            out += 0x20;
        }
        cursor += 0x50;
        if (count >= 8)
            break;
    } while ((s32)cursor < (s32)end);
    qcopy(self + 0x10, &saved[0]);
    qcopy(self + 0xF0, &saved[1]);
    euler_rotation_basis(self + 0xC0, self + 0xF0);
}
