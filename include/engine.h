#ifndef ENGINE_H
#define ENGINE_H

#include "common.h"
struct Moby;

/*
 * Insomniac Engine Core Geometry Systems:
 * - tfrag: Terrain fragment geometry (static terrain rendering)
 * - tie:   Instanced environment structures
 * - shrub: Instanced foliage, grass, and decorative meshes
 * - moby:  Dynamic interactive entities (actors, projectiles, crates)
 */

typedef enum GeometryKind {
    GEOM_TFRAG = 0,
    GEOM_TIE   = 1,
    GEOM_SHRUB = 2,
    GEOM_MOBY  = 3
} GeometryKind;

/*
 * Game Modes and Movie Playback states.
 * Recovered from mode.cpp and loaders.cpp in prototype builds.
 */
typedef enum GameMode {
    GAME_MODE_NONE            = 0,
    GAME_MODE_DEBUG           = 1,
    GAME_MODE_NORMAL          = 2,
    GAME_MODE_MOVIE           = 3,
    GAME_MODE_SCENE           = 4,
    GAME_MODE_PAUSE           = 5,
    GAME_MODE_FREEZE          = 6,
    GAME_MODE_VENDOR          = 7,
    GAME_MODE_SPACE           = 8,
    GAME_MODE_PUZZLE          = 9,
    GAME_MODE_HOVERBIKE_PAUSE = 10,
    GAME_MODE_WEAPON_UPGRADE  = 11,
    GAME_MODE_CREDITS         = 12
} GameMode;

typedef enum MovieType {
    MOVIE_INFOBOT = 0,
    MOVIE_HELP    = 1,
    MOVIE_SPECIAL = 2,
    MOVIE_STORY   = 3
} MovieType;

/*
 * Collision System API:
 * Pill/capsule collision detection for Mobies.
 * Recovered from assertion strings in engine core (0x001E8890).
 */
s32 MB_CheckCollPill(struct Moby *moby);

/*
 * Camera collision primitive test:
 * Recovered from 0x001E7A50 (author initials RAR).
 */
s32 Camera_CollPrimTest(void *prim, void *grid);

/* Measured USA v1.01 memory views, not native host-pointer structures.
 * Addresses are 32-bit PS2 values; decode them explicitly in a PC port/debugger.
 * Field purposes not established by callers and the consumer retain offset names.
 * See docs/game/community-engine-reference.md, "Measured retail impact queue". */
typedef struct Rac2Impact32 {
    /* 0x00 */ f32 vector[4];
    /* 0x10 */ u32 sourceAddress;
    /* 0x14 */ u32 flags;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ s16 objectClass;
    /* 0x1C */ f32 strength;
    /* 0x20 */ u32 unk20;
    /* 0x24 */ u32 unk24;
} Rac2Impact32;                         /* payload: 0x28 bytes */

/* Only the prefix needed by the inspected collision paths. Its size is not
 * the size or stride of a complete moby. */
typedef struct Rac2MobyCollisionView32 {
    /* 0x00 */ u8 unk00[0x10];
    /* 0x10 */ f32 position[4];
    /* 0x20 */ u8 unk20[0x48];
    /* 0x68 */ u32 instanceDataAddress;
    /* 0x6C */ u8 unk6C[0x3C];
    /* 0xA8 */ u8 impactSlot;
    /* 0xA9 */ u8 unkA9;
    /* 0xAA */ s16 objectClass;
} Rac2MobyCollisionView32;              /* measured prefix: 0xAC bytes */

/* Catalogue symbol; QueueMobyImpact in names.h is a descriptive alias. */
void func_002A8E20(void *target, const Rac2Impact32 *impact);

/*
 * Moves *position towards target (src/game/002AA800.c). Under the EABI the
 * two pointers take $a0 and $a1, the floats $f12-$f15 and direction $a2,
 * whatever their order in the list; this order is the one retail's callers
 * set the registers up in (level 20 and 23 bodies only match with it).
 */
float func_002AA898(float *position, float target, float *velocity,
                    float acceleration, float damping, float limit, int direction);

#endif /* ENGINE_H */
