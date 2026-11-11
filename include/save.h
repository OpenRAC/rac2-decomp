#ifndef SAVE_H
#define SAVE_H

#include "common.h"

/*
 * Insomniac Save Game IFF (Interchange File Format) Chunk IDs.
 *
 * Recovered from save file analysis (chaoticgd, creepnt 2024-2026)
 * and cross-referenced with PS2 memory card save streams:
 *   - NTSC-U: BASCUS-97199 (RaC1), BASCUS-97268 (RaC2)
 *   - PAL:    BESCES-50916 (RaC1), BESCES-51607 (RaC2)
 */

typedef enum SaveGameBlockId {
    SAVE_BLOCK_LEVEL                    = 0,     /* Current / last level ID (int) */
    SAVE_BLOCK_BOLT_COUNT               = 1,     /* Total bolt count (int) */
    SAVE_BLOCK_GAME_COMPLETES           = 2,     /* Playthrough / challenge mode count */
    SAVE_BLOCK_ELAPSED_TIME             = 3,     /* In-game elapsed time */
    SAVE_BLOCK_LAST_SAVE_TIME           = 4,     /* Timestamp (sceCdCLOCK) */
    SAVE_BLOCK_GLOBAL_FLAGS             = 5,     /* Global progression bit flags */
    SAVE_BLOCK_CHEATS_ACTIVATED         = 7,     /* Active cheats bitmask */
    SAVE_BLOCK_SKILL_POINTS             = 8,     /* Skill points unlocked */
    SAVE_BLOCK_AMMO                     = 9,     /* Current ammo table */
    SAVE_BLOCK_UNLOCKS                  = 10,    /* Weapon / Gadget unlock bitmask */
    SAVE_BLOCK_PURCHASABLE_VENDOR_ITEMS = 12,    /* Vendor purchase availability */
    SAVE_BLOCK_GALACTIC_MAP             = 14,    /* Visited planet coordinates */
    SAVE_BLOCK_HELP_MESSAGES            = 16,    /* Help prompt flags */
    SAVE_BLOCK_CAMERA_UP_DOWN_MODE      = 25,    /* Invert pitch setting */
    SAVE_BLOCK_CAMERA_LEFT_RIGHT_MODE   = 26,    /* Invert yaw setting */
    SAVE_BLOCK_CAMERA_ROTATION_SPEED    = 27,    /* Camera sensitivity */
    SAVE_BLOCK_CHEATS_EVER_ACTIVATED    = 37,    /* Permanent cheat taint flag */
    SAVE_BLOCK_TOTAL_PLAY_TIME          = 1003,  /* Lifetime playtime */
    SAVE_BLOCK_TOTAL_DEATHS             = 1005   /* Lifetime death counter */
} SaveGameBlockId;

/*
 * Ratchet & Clank saves on the card: the Barlow Gadgetron vendor's free weapons.
 *
 * The vendor's card check (func_002FAE68) runs the card state machine's states 24-27
 * (func_00298F00): it opens BASCUS-97199RATCHET/save0.bin to save4.bin, then the
 * BESCES-50916RATCHET and BISCPS-15037RATCHET ones, reads 0x2800 bytes of each and checks the
 * save (func_0029AF58). Block 10 of a RaC1 save is a byte per RaC1 item id; a nonzero byte for
 * one of five weapons sets a bit of the flags word D_001A7A00[8] (0x001A7A20), and any good save
 * sets RAC1_SAVE_FOUND. func_002FADB0 then makes the vendor's items for the set bits free
 * (func_002FAD68 with RaC2 items 12 Bomb Glove, 53
 * Walloper, 17 Decoy Glove, 14 Visibomb Gun, 18 Tesla Claw, in bit order) and clears RAC1_SAVE_FOUND.
 */
#define RAC1_SAVE_UNLOCK_BOMB_GLOVE     (1 << 0)  /* RaC1 item 0x0A: Bomb Glove */
#define RAC1_SAVE_UNLOCK_WALLOPER       (1 << 1)  /* RaC1 item 0x12: Walloper */
#define RAC1_SAVE_UNLOCK_DECOY_GLOVE    (1 << 2)  /* RaC1 item 0x19: Decoy Glove */
#define RAC1_SAVE_UNLOCK_VISIBOMB       (1 << 3)  /* RaC1 item 0x0D: Visibomb Gun */
#define RAC1_SAVE_UNLOCK_TESLA_CLAW     (1 << 4)  /* RaC1 item 0x13: Tesla Claw */
#define RAC1_SAVE_FOUND                 (1 << 7)  /* a RaC1 save was read */

#endif /* SAVE_H */
