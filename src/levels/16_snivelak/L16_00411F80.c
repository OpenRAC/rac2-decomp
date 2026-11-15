/*
 * A unit of its own because the moby pool and count are single-instruction macro loads of plain
 * scalars here (MACRO_ADDR), while L16_00403900.c declares the pool as an array. A fixed scalar
 * read does not alias the struct-member stores to part->flags, so loop.c hoists those reads out
 * of the later walks. The $gp form in retail is only the assembler's delay-slot macro load.
 */
#include "common.h"

typedef struct GroupPartModel {
    u8 pad00[0x10];
    void *bound;
} GroupPartModel;

typedef struct GroupPart {
    u8 pad00[0x24];
    GroupPartModel *model;
    u8 pad28[0xC];
    u16 flags;
    u8 pad36[0x12];
    float alpha;
    u8 pad4C[0x4C];
    void *bound;
} GroupPart;

extern u16 *D_L16_001FB660[];
extern u8 *D_L16_001B2B1C MACRO_ADDR;
extern s32 D_L16_001B2B38 MACRO_ADDR;
extern u8 D_001395B8[];

#define GROUP(off) (*(s32 *)(state + (off)))
#define GROUP_HAS_ENTRY(entry, off)                                       \
    ((GROUP(off) & 255) != 255 && GROUP(off) <= D_L16_001B2B38 &&         \
     (entry) != 0 &&                                                      \
     (((entry) != 0 && (s16)(entry)[-1] >= 0) ||                          \
      (entry) == D_L16_001FB660[GROUP(off)]))
#define GROUP_MOBY(index) ((GroupPart *)(D_L16_001B2B1C + (((index) & 0x7fff) << 8)))
#define CHILD(off) ((GroupPart *)*(u8 **)(state + (off)))

/* Turns this moby, its three linked parts and its three moby groups on or off. */
void SetMobyAndGroupsEnabled(u8 *self, s32 enable)
{
    GroupPart *moby = (GroupPart *)self;
    u8 *state = *(u8 **)(self + 0x68);
    GroupPart *part;

    if (enable) {
        {
            u16 *entry = D_L16_001FB660[GROUP(0x184)];

            while (GROUP_HAS_ENTRY(entry, 0x184)) {
                part = GROUP_MOBY(*entry++);
                if (!part) break;
                part->flags = (part->flags & 0xffbe) | 0x1000;
                {
                    void *bound = part->model->bound;

                    part->flags &= 0xfffd;
                    part->bound = bound;
                }
            }
        }
        {
            u16 *entry = D_L16_001FB660[GROUP(0x17c)];

            while (GROUP_HAS_ENTRY(entry, 0x17c)) {
                part = GROUP_MOBY(*entry);
                if (!part) break;
                part->flags = (part->flags & 0xffbe) | 0x1000;
                part->bound = part->model->bound;
                entry++;
            }
        }
        {
            u16 *entry = D_L16_001FB660[GROUP(0x180)];

            while (GROUP_HAS_ENTRY(entry, 0x180)) {
                part = GROUP_MOBY(*entry);
                if (!part) break;
                part->flags = (part->flags & 0xffbe) | 0x1000;
                part->bound = part->model->bound;
                entry++;
            }
        }
        moby->flags = (moby->flags & 0xffbe) | 0x1000;
        moby->bound = moby->model->bound;
        if (CHILD(0x1f0)) {
            CHILD(0x1f0)->flags &= 0xffbe;
            CHILD(0x1f0)->flags |= 0x1000;
            CHILD(0x1f0)->bound = CHILD(0x1f0)->model->bound;
        }
        if (CHILD(0x238)) {
            CHILD(0x238)->flags &= 0xffbe;
            CHILD(0x238)->flags |= 0x1000;
            CHILD(0x238)->bound = CHILD(0x238)->model->bound;
        }
        if (CHILD(0x23c)) {
            CHILD(0x23c)->flags &= 0xffbe;
            CHILD(0x23c)->flags |= 0x1000;
            CHILD(0x23c)->bound = CHILD(0x23c)->model->bound;
        }
    } else {
        {
            u16 *entry = D_L16_001FB660[GROUP(0x184)];

            while (GROUP_HAS_ENTRY(entry, 0x184)) {
                part = GROUP_MOBY(*entry++);
                if (!part) break;
                part->bound = 0;
                part->flags = (part->flags & 0xefff) | 0x43;
            }
        }
        {
            u16 *entry = D_L16_001FB660[GROUP(0x17c)];

            while (GROUP_HAS_ENTRY(entry, 0x17c)) {
                part = GROUP_MOBY(*entry);
                if (!part) break;
                part->bound = 0;
                part->flags = (part->flags | 0x41) & 0xefff;
                entry++;
            }
        }
        {
            u16 *entry = D_L16_001FB660[GROUP(0x180)];

            while (GROUP_HAS_ENTRY(entry, 0x180)) {
                part = GROUP_MOBY(*entry);
                if (!part) break;
                part->bound = 0;
                part->flags = (part->flags | 0x41) & 0xefff;
                entry++;
            }
        }
        if (!D_001395B8[0x83]) {
            moby->bound = 0;
            moby->flags = (moby->flags | 0x41) & 0xefff;
            if (CHILD(0x1f0)) {
                CHILD(0x1f0)->flags |= 0x41;
                CHILD(0x1f0)->flags &= 0xefff;
                CHILD(0x1f0)->bound = 0;
            }
            if (CHILD(0x238)) {
                CHILD(0x238)->flags |= 0x41;
                CHILD(0x238)->flags &= 0xefff;
                CHILD(0x238)->bound = 0;
            }
            if (CHILD(0x23c)) {
                CHILD(0x23c)->flags |= 0x41;
                CHILD(0x23c)->flags &= 0xefff;
                CHILD(0x23c)->bound = 0;
            }
            moby->alpha = 0.0f;
            if (CHILD(0x1f0)) CHILD(0x1f0)->alpha = 0.0f;
        }
    }
}
