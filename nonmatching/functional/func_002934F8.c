/* functional: medium. The near-miss draft; same reads, writes, calls and result as retail (fcheck SAME on 2 of 2 captured calls); only register allocation or instruction order differs. */
/* Retained manual reconstruction, 2026-10-24.
 * Profile: -O2 -G0 -ffunction-sections.
 * Final measurements: us: 0/28 placements, exit1, 912 compiled bytes; us2:
 * 0/28 placements, exit1, 912 compiled bytes; pal: 0/28 placements, exit1,
 * 912 compiled bytes.
 * Remaining: Complete compressed-header compaction and all nested
 * relocations are retained. Separate loop and pointer lifetimes improved
 * the final source to 912/916 bytes. Operand order, loop header scheduling,
 * parts-array address hoisting and the final vector-copy allocation still
 * differ. qcopy/barrier and no-gcse were measured without a successful
 * match.
 * Reopen with: Independent original-header/part-table layout or compiler
 * live-range evidence that fixes the measured pointer lifetimes and
 * loop/address scheduling.
 * No byte-match or linked-build credit is claimed.
 */
/* Relocate a packed asset block and optionally compact its packet headers. */
typedef unsigned char U8;
typedef unsigned int Q128 __attribute__((mode(TI)));
extern void func_0026FEB8(const char *, ...);
extern void func_00282B50(void *destination, void *source, int bytes);
extern void func_002932B8(void *entries, void *textures, U8 *map, int count);
extern const char D_001B9240[];
extern U8 D_001CE4E0[];
extern int D_001D0E00[];
extern Q128 D_001D1580[];

void func_002934F8(U8 *block, void *textures, U8 *map, int index)
{
    int compressed = block[0xB] != 0;
    int count;
    if (compressed) {
        int size;
        func_0026FEB8(D_001B9240, index);
        size = *(int *)(block + 0x2C);
        if (size > 0x3FC00) size = 0x3FC00;
        block[0xB] = 0;
        block[0x2C] = 0;
        *(short *)(block + 0x2E) = 0;
        block[0x2D] = size >> 10;
        D_001D0E00[D_001CE4E0[index]] = size;
    }
    count = block[4] + block[5] + block[6];
    if (block[0x2C]) count += block[block[0x2C] * 16 + 1];
    if (*(int *)block) {
        int packet_index;
        U8 *entry;
        entry = block + *(int *)block;
        *(U8 **)block = entry;
        for (packet_index = 0; packet_index < count; ++packet_index, entry += 16) {
            U8 *data = block + *(int *)(entry + 8);
            int first_two, all_three;
            *(U8 **)(entry + 8) = data;
            *(int *)entry += (int)block;
            first_two = block[4] + block[5];
            all_three = first_two + block[6];
            if (compressed && (packet_index < first_two || packet_index >= all_three)) {
                int j;
                U8 *destination = data;
                U8 *source = data;
                for (j = 7; j >= 0; --j) {
                    *(unsigned short *)destination = *(unsigned short *)source;
                    destination += 2;
                    source += 4;
                }
                *(unsigned short *)(data + 0xE) = 0;
                *(unsigned short *)(data + 0xC) = *(unsigned short *)(data + 0x18) - 16;
                func_00282B50(data + 16, data + 32, (entry[0xC] - 2) * 16);
            }
        }
    }
    if (*(int *)(block + 0x10)) *(int *)(block + 0x10) += (int)block;
    if (*(int *)(block + 0x14)) *(int *)(block + 0x14) += (int)block;
    if (*(int *)(block + 0x18)) *(int *)(block + 0x18) += (int)block;
    if (*(int *)(block + 0x1C)) {
        int n, relocation_index;
        *(int *)(block + 0x1C) += (int)block;
        n = **(int **)(block + 0x1C);
        for (relocation_index = 0; relocation_index < n; ++relocation_index)
            (*(int **)(block + 0x1C))[relocation_index + 1] += (int)block;
    }
    if (*(int *)(block + 0x20)) {
        U8 *entry;
        *(int *)(block + 0x20) += (int)block;
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
    if (*(int *)(block + 0x28)) *(int *)(block + 0x28) += (int)block;
    {
    int part_index;
    int *parts = (int *)(block + 0x48);
    for (part_index = 0; part_index < block[0xC]; ++part_index) {
        U8 *part;
        int j;
        if (!parts[part_index]) continue;
        part = block + parts[part_index];
        ((U8 **)parts)[part_index] = part;
        if (*(int *)(part + 0x14)) *(int *)(part + 0x14) += (int)part;
        for (j = 0; j < part[0x10]; ++j)
            ((int *)(part + 0x1C))[j] += (int)block;
    }
    }
    if (index >= 0) D_001D1580[D_001CE4E0[index]] = *(Q128 *)map;
    if (*(void **)block)
        func_002932B8(*(void **)block, textures, map, count);
}
