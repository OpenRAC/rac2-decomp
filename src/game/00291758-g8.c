#include "include_asm.h"
#include "names.h"

extern int g_class_cache_count __attribute__((section(".sdata")));
extern int g_class_cache_next __attribute__((section(".sdata")));
extern unsigned char g_class_slot_lookup[];
extern short g_class_cache_ids[];
extern char *g_class_cache_objects[];
extern int g_class_cache_sizes[];
extern void moby_queue_class_update(int, int);
extern void tex_relocate_block(char *, int, int, int);

/* Registers a loaded object in the class cache tables, or only reserves a slot when no object is given. */
void load_register_class_cache_object(char *object, int mapBase, int mapEntries, int id)
{
    if (object == 0) {
        moby_queue_class_update(id, 1);
        g_class_slot_lookup[id] = *(unsigned char *)&g_class_cache_next;
        g_class_cache_next = g_class_cache_next + 1;
    } else {
        g_class_cache_ids[g_class_cache_count] = id;
        g_class_slot_lookup[id] = *(unsigned char *)&g_class_cache_count;
        g_class_cache_objects[g_class_cache_count] = object;
        g_class_cache_sizes[g_class_cache_count] = (unsigned char)object[0x2D] << 10;
        if ((unsigned char)object[0x2D] == 255)
            g_class_cache_sizes[g_class_cache_count] = 0x100000;
        moby_queue_class_update(id, 0);
        ++g_class_cache_count;
        tex_relocate_block(object, mapBase, mapEntries, id);
    }
}


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* The part list a moby hangs its parts from. */
struct PartList {
    u8 pad00[6];
    u8 flag;             /* 0x06 */
    u8 pad07[5];
    u8 used;             /* 0x0C */
    u8 pad0D[0x3B];
    u32 entries[1];      /* 0x48 */
};

/* What the render globals point at for the colour a new moby takes. */
struct ColorSrc {
    u8 pad00[0x38];
    u64 color;           /* 0x38 */
};

struct RenderGlobals {
    u8 pad00[0x2290];
    struct ColorSrc *color_src;    /* 0x2290 */
};

/* A moby: the engine's object. */
struct Moby {
    u8 pad00[0x24];
    struct PartList *parts;    /* 0x24 */
    u8 pad28[0x0A];
    u16 unk32;                /* 0x32 */
    u16 unk34;                /* 0x34 */
    u8 pad36[2];
    u64 color;                /* 0x38 */
    u8 pad40[2];
    u8 idx;                   /* 0x42 */
    u8 slot;                  /* 0x43 */
    u8 pad44[0x1E];
    u8 flag72;                /* 0x62 */
    u8 flag73;                /* 0x63 */
    u8 pad64[4];
    u32 model;                /* 0x68 */
    u8 pad6C[0x2C];
    u32 unk94;                /* 0x98 */
    u8 pad9C[0x0E];
    short class_id;           /* 0xAA */
};

/* The model record of a chunk: its parts, in the order the record lists them. */
struct ModelRec {
    u16 flags;        /* 0x00 */
    u8 pad02[2];
    u32 part_count;   /* 0x04 */
    u16 pad08;        /* 0x08 */
    u8 pad0A[2];
    u16 num_parts;    /* 0x0C */
    u8 pad0E[2];
    u32 end_off;      /* 0x10 */
    int part_off[1];  /* 0x14 */
};

/* The state of the world objects: the record in hand and the mobies built from it. */
struct TransferState {
    u8 pad00[0x38];
    u32 unk38;            /* 0x38 */
    u8 pad3C[4];
    u16 unk40;            /* 0x40 */
    u8 pad42[2];
    short num_parts;      /* 0x44 */
    u8 pad46[2];
    u16 unk48;            /* 0x48 */
    u8 pad4A[2];
    u32 unk4C;            /* 0x4C */
    u32 unk50;            /* 0x50 */
    u32 unk54;            /* 0x54 */
    u8 pad58[0x10];
    u32 unk68;            /* 0x68 */
    struct ModelRec *rec; /* 0x6C */
    u32 unk70;            /* 0x70 */
    u8 pad74[0x118];
    struct Moby *slots[1];/* 0x18C */
};

extern struct TransferState g_scene_playback_state;
extern struct RenderGlobals g_hero_state;
extern struct Moby *g_load_object_cursor __attribute__((sda));

extern void FlushCache(int);
extern int fast_decompress(int, int);
extern struct Moby *CreateMoby(int);
extern void moby_init_instance(struct Moby *, int);

/* The table of the two slots a load reserves. */
struct LoadSlots {
    char pad00[0x34];
    int slot[4];
};

extern struct LoadSlots g_load_slots;
extern int g_class_cache_slot __attribute__((sda));

/* Release the slot the object holds: remember its entry in the table of the two
   slots, then clear the object's own reference to it. */
void load_release_class_cache_slot(int *entry, int doRelease)
{
    if (doRelease != 0) {
        if (entry[1] >= 0) {
            g_load_slots.slot[entry[1]] = entry[0];
            if (entry[1] != g_class_cache_slot)
                goto out;
            g_class_cache_slot = entry[1] ^ 1;
        }
    }
out:
    *entry = -1;
}

/* UpdateWorldObjectAnimation: relocate the model record loaded for the current chunk and
   hook each of its parts to a moby, spawning one and initialising it the first time; each
   part's pointer table is made absolute. */
void load_relocate_world_object_parts(void)
{
    struct ModelRec *rec;
    struct Moby *moby;
    int *partOffsets;
    int *partData;
    int i;
    int k;
    int partIndex;
    int classId;
    int partOffset;
    int modelEnd;
    int partCount;

    FlushCache(0);
    fast_decompress(g_scene_playback_state.unk70, (int)g_scene_playback_state.rec);
    FlushCache(0);

    rec = g_scene_playback_state.rec;
    g_scene_playback_state.unk38 = 0;
    partOffsets = rec->part_off;
    g_scene_playback_state.unk40 = rec->flags;
    partCount = rec->part_count;
    g_scene_playback_state.unk48 = rec->pad08;
    g_scene_playback_state.num_parts = rec->num_parts;
    g_scene_playback_state.unk68 = (u32)rec + rec->end_off;
    if (partCount < 0x400) {
        g_scene_playback_state.unk4C = 0;
    } else {
        g_scene_playback_state.unk4C = (u32)rec + partCount;
    }

    for (i = 0; i < g_scene_playback_state.num_parts; i++) {
        partOffset = *partOffsets++;
        partData = (int *)((u8 *)rec + partOffset);
        classId = partData[0];
        partData = (int *)((u8 *)partData + 0xC);
        modelEnd = (int)rec + partData[0];
        partData = (int *)((u8 *)partData + 4);
        if (classId == 0x215 /* moby class 533 */ || classId == 0x10D1 /* moby class 4305 */) {
            classId = 0xD54 /* moby class 3412 */;
        }
        moby = g_scene_playback_state.slots[i];
        if (moby == 0) {
            if (classId == 0) {
                moby = g_load_object_cursor;
                moby_init_instance(moby, 0);
            } else {
                moby = CreateMoby(classId);
            }
            moby->unk32 = 0x1FF;
            moby->unk34 |= 6;
            moby->flag72 = 0xFF;
            moby->unk94 = 0;
            if (g_hero_state.color_src == 0) {
                moby->color = 0x38383800000000ULL;
            } else {
                moby->color = g_hero_state.color_src->color;
            }
            if (moby->parts->flag) {
                moby->flag73 = 0x18;
            }
            partIndex = moby->parts->used;
            moby->parts->used = partIndex + 1;
            moby->idx = partIndex;
            moby->slot = partIndex;
            g_scene_playback_state.slots[i] = moby;
            if (moby->class_id == 0xD54) {
                g_scene_playback_state.unk54 = (u32)moby;
            }
        }
        moby->model = modelEnd;
        moby->parts->entries[moby->idx] = (u32)partData;
        for (k = 0; k < ((u8 *)partData)[0x10]; k++) {
            int *w = (int *)((u8 *)partData + 0x1C);

            w[k] = (int)partData + w[k];
        }
    }
}
