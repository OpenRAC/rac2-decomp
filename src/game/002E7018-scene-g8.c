#include "common.h"

/* The loading-scene state: the variant drawn at random and a counter. */
typedef struct { char pad[0x64]; int variant; int counter; } SceneState;
extern SceneState D_00152C00;
/* The scene context cleared here: two workspace addresses and the resident chunk table. */
typedef struct { char pad[0x6C]; int unk6C; int unk70; char *chunks[70]; } SceneContext;
extern SceneContext D_001B8840;
/* The scene arena cursor (RAC1 current_vu_chain), read and written as an absolute word. */
extern int D_001B22B0 MACRO_ADDR;
extern void func_00294070(int);

/* The loaded level archive and its header, after RAC1 space.c initialize_level_runtime. */
typedef struct { int pad0; int data_offset; char pad[0x48]; int scenes[5]; } SceneHeader;
typedef struct { int offset; int size; } SceneChunk;
typedef struct { char pad[0xC]; int unkC; int unk10; int unk14; SceneHeader *header; } SceneArchive;
extern SceneArchive D_001BAEC0;
extern int func_001163B0(void);
extern unsigned int ref_L00_003646F8_00 __attribute__((sda));
extern unsigned int ref_L00_003646F8_01 __attribute__((sda));
extern void func_00282A60(void *, int, int);
extern char D_001B1390[] MACRO_ADDR;
extern char D_001B13D0[] MACRO_ADDR;

/* Draws one of four loading-scene variants, clears the scene context, moves the
   scene arena cursor down by 0x60000 and lists the variant's archive chunks (at most
   70, up to the first empty one). The header is read only after the cursor is
   stored: that source order is what gives retail's allocation and schedule. */
/* Sets up a loading scene: picks one of four scenes at random and lists the data chunks it needs. */
void func_002EA968(void) {
    SceneHeader *header;
    int data_base;
    SceneChunk *scene_chunk;
    int k;
    int workspace_offset;

    gHeroMoby_00152C00.variant = (Rand() >> 16) & 3;
    gHeroMoby_00152C00.counter = 0;
    qcopy(&ref_L00_003646F8_00, &ref_L00_003646F8_01);
    ClearMemory(&gScenePlaybackState, 0, 0x1D0);
    ClearMemory(D_001B1390, 0, 0x40);
    ClearMemory(D_001B13D0, 0, 0x40);
    workspace_offset = D_001B22B0 - 0x60000;
    gScenePlaybackState.unk6C = D_001BAEC0.unkC + workspace_offset;
    gScenePlaybackState.unk70 = D_001BAEC0.unk10 + workspace_offset;
    D_001B22B0 = workspace_offset;
    header = D_001BAEC0.header;
    data_base = (int)header + header->data_offset;
    scene_chunk = (SceneChunk *)(data_base + header->scenes[gHeroMoby_00152C00.variant]);
    for (k = 0; k < 70 && scene_chunk->size != 0; k++) {
        {
            int chunk_offset = scene_chunk->offset + 0x800;
            gScenePlaybackState.chunks[k] = (char *)(data_base + header->scenes[gHeroMoby_00152C00.variant] + chunk_offset);
        }
        scene_chunk++;
    }
    SelectSegmentAndUpdateWorld(0);
}
