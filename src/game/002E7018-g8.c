#include "include_asm.h"
#include "names.h"

/* Small data: the three tables the function reaches through $gp. Their addresses
   differ from program to program, so they carry no level address and are named
   after the function's own place in level 00. */
extern unsigned int ref_L00_00361F20_00 __attribute__((sda));
extern unsigned int ref_L00_00361F20_01 __attribute__((sda));
extern unsigned int ref_L00_00361F20_02 __attribute__((sda));

extern int g_current_map_index;
extern unsigned long long D_001B2160;
extern float D_00261EC0[];

extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void mem_fast_helper_c(unsigned char *, unsigned char *, int);
extern void FastVecScale(unsigned char *, unsigned char *, float);
extern void FastVecAdd(unsigned char *, unsigned char *, unsigned char *);
extern void draw_world_quad(unsigned char *, int, int);

/* Builds the four quads of one draw call: the scale comes from the resident
   mode word indexing a float table, every quad carries the grey 0x80808080,
   and the block copied out of small data also carries the four render packet
   words. */
void gfx_draw_overlay_quads(void)
{
    unsigned char verts[4][16];
    int colors[4];
    unsigned char buf[0x40];
    unsigned long long packet;
    unsigned int mode;
    float scale = 1.0f;
    int i;

    VU1_addGSregister(0x47, 0x31801);

    packet = D_001B2160;

    *(unsigned long long *)(buf + 0x20) = 0;
    *(unsigned long long *)(buf + 0x28) = packet;
    *(unsigned long long *)(buf + 0x30) = 0xFF9000000260ULL;
    *(unsigned long long *)(buf + 0x38) = 0x8000000044ULL;
    mem_fast_helper_c(buf, (unsigned char *)&ref_L00_00361F20_00, 0x20);

    mode = g_current_map_index;
    if (mode < 0x13) {
        scale = D_00261EC0[mode];
    }

    for (i = 0; i < 4; i++) {
        colors[i] = 0x80808080;
        FastVecScale(verts[i], (unsigned char *)&ref_L00_00361F20_01 + i * 16, scale);
        FastVecAdd(verts[i], verts[i], (unsigned char *)&ref_L00_00361F20_02);
    }

    draw_world_quad(verts[0], 0, 0);
    VU1_addGSregister(0x47, 0x5360B);
}

/* The state word this function reads and the word it writes back live in the
   program's own memory, so they carry no level address. */
extern int ref_L00_00365F50_00 __attribute__((sda));
extern int ref_L00_00365F50_01;

/* The flag words the selection state keeps. */
typedef struct {
    unsigned int f00;
    unsigned char pad00[0x14];
    unsigned int f18;
    unsigned int f1c;
    unsigned char pad01[0x88];
    unsigned int fa8;
    unsigned int fac;
    unsigned int fb0;
} SelectionFlags;

extern SelectionFlags D_00139768;
extern char D_001A63A8_3[];
extern int PlayBonusReelWithGameLoop(int);
extern int mpeg_play_movie_by_id(int);

/* Acts on the state the program names: raises the flag bits that belong to
   that state in the resident state block, then has the two state machines
   take it (each one stops the rest when it answers that it is busy). The
   selector's pending byte is cleared on the way in and set on the way out,
   and the program is told the selection ended in state 6. */
void scene_start_sequence_for_state(void)
{
    int stateId = ref_L00_00365F50_00;

    D_001A63A8_3[7] = 0;

    if (stateId == 0xA9) {
        D_00139768.f00 |= 2;
        D_00139768.fa8 |= 0x600;
        if (PlayBonusReelWithGameLoop(0xA9)) goto done;
        if (mpeg_play_movie_by_id(1)) goto done;
        PlayBonusReelWithGameLoop(0xAA);
    } else if (stateId == 0x17) {
        mpeg_play_movie_by_id(0x17);
    } else if (stateId == 0xAB) {
        D_00139768.fa8 |= 0x800;
        D_00139768.f18 = (D_00139768.f18 & 0xFEFFFFFF) | 0x1000000;
        D_00139768.fac |= 0x1000;
        if (PlayBonusReelWithGameLoop(0xAB)) goto done;
        if (mpeg_play_movie_by_id(0x18)) goto done;
        PlayBonusReelWithGameLoop(0xAC);
    } else if (stateId == 0xAD) {
        D_00139768.f18 = (D_00139768.f18 & 0xFDFFFFFF) | 0x2000000;
        D_00139768.fac |= 0x6000;
        if (PlayBonusReelWithGameLoop(0xAD)) goto done;
        if (mpeg_play_movie_by_id(0x19)) goto done;
        PlayBonusReelWithGameLoop(0xAE);
    } else if (stateId == 0x1A) {
        mpeg_play_movie_by_id(0x1A);
    } else if (stateId == 0x1B) {
        mpeg_play_movie_by_id(0x1B);
    } else if (stateId == 0xAF) {
        D_00139768.fac |= 0x8000;
        D_00139768.f1c = (D_00139768.f1c & 0xEFFFFFFF) | 0x10000000;
        D_00139768.fb0 = (D_00139768.fb0 & 0xFFFEFFFF) | 0x10000;
        if (PlayBonusReelWithGameLoop(0xAF)) goto done;
        if (mpeg_play_movie_by_id(0x1C)) goto done;
        PlayBonusReelWithGameLoop(0xB0);
    }
done:
    D_001A63A8_3[7] = 1;
    { int six = 6; ref_L00_00365F50_01 = six; }
}

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct PartList2EB598 {
    u8 pad00[6];
    u8 flag;
    u8 pad07[5];
    u8 used;
    u8 pad0D[0x3B];
    u32 entries[1];
};

struct Moby2EB598 {
    u8 pad00[0x24];
    struct PartList2EB598 *parts;
    u8 pad28[0x0A];
    u16 unk32;
    u16 unk34;
    u8 pad36[2];
    u64 color;
    u8 pad40[2];
    u8 idx;
    u8 slot;
    u8 pad44[0x1E];
    u8 flag72;
    u8 flag73;
    u8 pad64[4];
    u32 model;
    u8 pad6C[0x2C];
    u32 unk94;
    u8 pad9C[0x0E];
    short class_id;
};

struct ModelRec2EB598 {
    u16 flags;
    u8 pad02[2];
    u32 part_count;
    u16 pad08;
    u8 pad0A[2];
    u16 num_parts;
    u8 pad0E[2];
    u32 end_off;
    int part_off[1];
};

struct State2EB598 {
    u8 pad00[0x38];
    u32 unk38;
    u8 pad3C[4];
    u16 unk40;
    u8 pad42[2];
    short num_parts;
    u8 pad46[2];
    u16 unk48;
    u8 pad4A[2];
    u32 unk4C;
    u32 unk50;
    u32 unk54;
    u8 pad58[0x10];
    u32 unk68;
    struct ModelRec2EB598 *rec;
    u32 unk70;
    u8 pad74[0x118];
    struct Moby2EB598 *slots[1];
};

extern struct State2EB598 g_scene_playback_state;
extern struct Moby2EB598 *ref_L00_002EB598_00 __attribute__((sda));

extern void FlushCache(int);
extern int fast_decompress(int, int);
extern struct Moby2EB598 *CreateMoby(int);
extern void moby_init_instance(struct Moby2EB598 *, int);

/* Creates a moby for every part of a model record and links the parts to the model data. */
void moby_spawn_model_parts(void)
{
    struct ModelRec2EB598 *rec;
    struct Moby2EB598 *mob;
    int *partOffsets;
    int *partData;
    int i;
    int k;
    int idx;
    int id;
    int off;
    int endp;
    int tableOffset;

    FlushCache(0);
    fast_decompress(g_scene_playback_state.unk70, (int)g_scene_playback_state.rec);
    FlushCache(0);

    rec = g_scene_playback_state.rec;
    g_scene_playback_state.unk38 = 0;
    partOffsets = rec->part_off;
    g_scene_playback_state.unk40 = rec->flags;
    tableOffset = rec->part_count;
    g_scene_playback_state.unk48 = rec->pad08;
    g_scene_playback_state.num_parts = rec->num_parts;
    g_scene_playback_state.unk68 = (u32)rec + rec->end_off;
    if (tableOffset < 0x400) {
        g_scene_playback_state.unk4C = 0;
    } else {
        g_scene_playback_state.unk4C = (u32)rec + tableOffset;
    }

    for (i = 0; i < g_scene_playback_state.num_parts; i++) {
        off = *partOffsets++;
        partData = (int *)((u8 *)rec + off);
        id = partData[0];
        partData = (int *)((u8 *)partData + 0xC);
        endp = (int)rec + partData[0];
        partData = (int *)((u8 *)partData + 4);
        if (id == 0x215 /* moby class 533 */) {
            id = 0xD54 /* moby class 3412 */;
        }
        mob = g_scene_playback_state.slots[i];
        if (mob == 0) {
            if (id == 0) {
                mob = ref_L00_002EB598_00;
                moby_init_instance(mob, 0);
            } else {
                mob = CreateMoby(id);
            }
            mob->unk32 = 0x1FF;
            mob->unk34 |= 6;
            mob->flag72 = 0xFF;
            mob->color = 0x20202000000000ULL;
            mob->unk94 = 0;
            if (mob->parts->flag) {
                if (mob->class_id == 0xD54 /* moby class 3412 */) {
                    mob->flag73 = 0;
                } else {
                    mob->flag73 = 8;
                }
            }
            idx = mob->parts->used;
            mob->parts->used = idx + 1;
            mob->idx = idx;
            mob->slot = idx;
            g_scene_playback_state.slots[i] = mob;
            if (mob->class_id == 0xD54 /* moby class 3412 */) {
                g_scene_playback_state.unk54 = (u32)mob;
            }
        }
        mob->model = endp;
        mob->parts->entries[mob->idx] = (u32)partData;
        for (k = 0; k < ((u8 *)partData)[0x10]; k++) {
            int *w = (int *)((u8 *)partData + 0x1C);

            w[k] = (int)partData + w[k];
        }
    }
}
