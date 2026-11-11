#ifndef GADGETS_H
#define GADGETS_H

#include "common.h"

/*
 * RaC1 Gadget and Weapon Enum (reused by RaC1 Save-Import system in RaC2).
 * Recovered from Aug 8 2002 proto string mining (@creepnt 2026).
 */
typedef enum RaC1GadgetId {
    GADGET_BOMB_GLOVE       = 0,
    GADGET_PYROCITOR        = 1,
    GADGET_BLASTER          = 2,
    GADGET_GLOVE_OF_DOOM    = 3,
    GADGET_SUCK_CANNON      = 4,
    GADGET_SWINGSHOT        = 5,
    GADGET_HYDRODISPLACER   = 6,
    GADGET_SONIC_SUMMONER   = 7,
    GADGET_RYNO             = 8,
    GADGET_WALLOPER         = 9,
    GADGET_VISIBOMB         = 10,
    GADGET_DECOY_GLOVE      = 11,
    GADGET_TESLA_CLAW       = 12,
    GADGET_TAUNTER          = 13,
    GADGET_TRESPASSER       = 14,
    GADGET_METAL_DETECTOR   = 15,
    GADGET_MAGNEBOOTS       = 16,
    GADGET_GRIND_BOOTS      = 17,
    GADGET_HOVERBOARD       = 18,
    GADGET_HELI_PACK        = 19,
    GADGET_THRUSTER_PACK    = 20,
    GADGET_HYDRO_PACK       = 21,
    GADGET_O2_MASK          = 22,
    GADGET_PILOTS_HELMET    = 23,
    GADGET_MORPH_O_RAY      = 24,
    GADGET_CODEBOT          = 25,
    GADGET_HOLOGUISE        = 26,
    GADGET_PDA              = 27,
    GADGET_PERSUADER        = 28
} RaC1GadgetId;

/*
 * RaC2 Native Gadget and Weapon Identifiers.
 * Recovered from gadgets.cpp assertions in prototype builds.
 */
typedef enum RaC2GadgetId {
    GADGET_RC2_LANCER             = 0,
    GADGET_RC2_GRAVITY_BOMB       = 1,
    GADGET_RC2_CHOPPER            = 2,
    GADGET_RC2_BLITZ_GUN          = 3,
    GADGET_RC2_MINI_TURRET        = 4,
    GADGET_RC2_SEEKER_GUN         = 5,
    GADGET_RC2_PULSE_RIFLE        = 6,
    GADGET_RC2_MEGATURRET         = 7,
    GADGET_RC2_SPIDER_BOT         = 8,
    GADGET_RC2_TETRABOMB          = 9,
    GADGET_RC2_HOVERBIKE          = 10,
    GADGET_RC2_THERMAL_GOGGLES    = 11,
    GADGET_RC2_TRACTOR_BEAM       = 12,
    GADGET_RC2_LEVITATOR          = 13,
    GADGET_RC2_CHARGE_BOOTS       = 14,
    GADGET_RC2_ARMOR_1            = 15,
    GADGET_RC2_ARMOR_2            = 16,
    GADGET_RC2_ARMOR_3            = 17,
    GADGET_RC2_ARMOR_4            = 18,
    GADGET_RC2_SHEEPANATOR        = 19,
    GADGET_RC2_SNIPER_RIFLE       = 20,
    GADGET_RC2_HOMING_GRENADE     = 21,
    GADGET_RC2_HOVERBOMBLAUNCHER  = 22,
    GADGET_RC2_SWARMGUN           = 23,
    GADGET_RC2_MINITURRET_GLOVE   = 24,
    GADGET_RC2_MINIROCKET_GUN     = 25,
    GADGET_RC2_PLASMA_COIL        = 26,
    GADGET_RC2_LAVAGUN            = 27,
    GADGET_RC2_SYNTHENOID         = 28,
    GADGET_RC2_WHISTLER_LAUNCHER  = 29,
    GADGET_RC2_BOUNCER            = 30,
    GADGET_RC2_ZODIAC             = 31,
    GADGET_RC2_MAGNETIZER         = 32,
    GADGET_RC2_HOOK               = 33,
    GADGET_RC2_GLIDER             = 34,
    GADGET_RC2_DYNAMO             = 35,
    GADGET_RC2_SHIELD_CHARGER     = 36,
    TOTAL_RC2_GADGETS             = 37
} RaC2GadgetId;

#endif /* GADGETS_H */
