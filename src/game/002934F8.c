#include "common.h"
/* Relocate a packed asset block and optionally compact its packet headers. */
typedef unsigned char U8;
typedef unsigned int Q128 __attribute__((mode(TI)));
extern void func_0026FEB8(const char *, ...);
extern void func_00282B50(void *destination, void *source, int bytes);
extern void func_002932B8(void *entries, void *textures, U8 *map, int count);
extern const char ref_002934F8_00[];
extern U8 ref_002934F8_01[];
extern int ref_002934F8_02[];
extern Q128 ref_002934F8_03[];

void func_002934F8(U8 *block, void *textures, U8 *map, int index)
{
    int compressed = block[0xB] != 0;
    int count;
    if (compressed) {
        int size;
        func_0026FEB8(ref_002934F8_00, index);
        size = *(int *)(block + 0x2C);
        if (size > 0x3FC00) size = 0x3FC00;
        block[0xB] = 0;
        block[0x2C] = 0;
        *(short *)(block + 0x2E) = 0;
        block[0x2D] = size >> 10;
        ref_002934F8_02[ref_002934F8_01[index]] = size;
    }
    count = block[4] + block[5] + block[6];
    if (block[0x2C]) { U8 *q = block + block[0x2C] * 16; count += q[1]; }
    if (*(int *)block) {
        int i;
        U8 *entry;
        *(U8 **)block = block + *(int *)block;
        i = 0;
        entry = *(U8 **)block;
        for (; i < count; ++i, entry += 16) {
            U8 *data = (U8 *)(*(int *)(entry + 8) + (int)block);
            int first_two, all_three;
            *(U8 **)(entry + 8) = data;
            *(int *)entry += (int)block;
            first_two = block[4] + block[5];
            all_three = first_two + block[6];
            if (compressed && (i < first_two || i >= all_three)) {
                int j;
                for (j = 0; j < 8; j++)
                    ((unsigned short *)data)[j] = ((unsigned short *)data)[j * 2];
                *(unsigned short *)(data + 0xE) = 0;
                *(unsigned short *)(data + 0xC) = *(unsigned short *)(data + 0x18) - 16;
                func_00282B50((unsigned short *)data + j, data + 32, (entry[0xC] - 2) * 16);
            }
        }
    }
    if (*(int *)(block + 0x10)) *(U8 **)(block + 0x10) = block + *(int *)(block + 0x10);
    if (*(int *)(block + 0x14)) *(U8 **)(block + 0x14) = block + *(int *)(block + 0x14);
    if (*(int *)(block + 0x18)) *(U8 **)(block + 0x18) = block + *(int *)(block + 0x18);
    if (*(int *)(block + 0x1C)) {
        int n, i;
        *(U8 **)(block + 0x1C) = block + *(int *)(block + 0x1C);
        n = **(int **)(block + 0x1C);
        for (i = 0; i < n; ++i)
            (*(int **)(block + 0x1C))[i + 1] += (int)block;
    }
    if (*(int *)(block + 0x20)) {
        U8 *entry;
        *(U8 **)(block + 0x20) = block + *(int *)(block + 0x20);
        entry = *(U8 **)(block + 0x20);
        do {
            U8 *cursor = entry;
            *(int *)(entry + 0xC) += (int)block;
            if (*cursor != 255) {
                do {
                    *cursor = map[*cursor];
                    ++cursor;
                } while (*cursor != 255);
            }
            if (*(int *)(entry + 0xC) < 0) break;
            entry += 16;
        } while (1);
    }
    if (*(int *)(block + 0x28)) *(U8 **)(block + 0x28) = block + *(int *)(block + 0x28);
    {
    int i = 0;
    if (block[0xC]) {
        int *parts = (int *)(block + 0x48);
        do {
            int *slot = parts + i;
            if (*slot) {
                U8 *part = block + *slot;
                int j;
                int *q;
                *(U8 **)slot = part;
                if (*(int *)(part + 0x14)) *(U8 **)(part + 0x14) = part + *(int *)(part + 0x14);
                for (j = 0; j < part[0x10]; ++j) {
                    int *q2 = (int *)(part + 0x1C) + j;
                    *q2 = (int)block + *q2;
                }
            }
            i++;
        } while (i < block[0xC]);
    }
    }
    if (index >= 0) qcopy(&ref_002934F8_03[ref_002934F8_01[index]], map);
    if (*(void **)block)
        func_002932B8(*(void **)block, textures, map, count);
}
