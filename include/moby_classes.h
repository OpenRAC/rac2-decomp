/*
 * Moby class ids (oClass, the s16 at moby +0xAA) that have a label in
 * docs/game/moby-dispatch.tsv (class_label, from community model lists).
 * Generated from that table; a label several ids share gets _2, _3 ... in id order.
 * Classes with no label keep their number in code, with a "moby class N" comment.
 */
#ifndef MOBY_CLASSES_H
#define MOBY_CLASSES_H

#define MOBY_CLASS_MEGACORP_VENDOR                      0xB /* Megacorp Vendor */
#define MOBY_CLASS_BOLT                                 0xD /* Bolt */
#define MOBY_CLASS_BOLT_2                               0xE /* Bolt */
#define MOBY_CLASS_BOLT_3                               0xF /* Bolt */
#define MOBY_CLASS_BOLT_4                               0x10 /* Bolt */
#define MOBY_CLASS_BOLT_5                               0x11 /* Bolt */
#define MOBY_CLASS_BOLT_6                               0x12 /* Bolt */
#define MOBY_CLASS_BOLT_7                               0x13 /* Bolt */
#define MOBY_CLASS_CLANK                                0x57 /* Clank */
#define MOBY_CLASS_VISIBOMB_GUN                         0xA3 /* Visibomb Gun */
#define MOBY_CLASS_VISIBOMB_MISSILE                     0xAC /* Visibomb Missile */
#define MOBY_CLASS_TESLA_CLAW                           0xB1 /* Tesla Claw */
#define MOBY_CLASS_WALLOPER                             0xB4 /* Walloper */
#define MOBY_CLASS_TRACTOR_BEAM                         0xBC /* Tractor Beam */
#define MOBY_CLASS_BOMB_GLOVE                           0xC0 /* Bomb Glove */
#define MOBY_CLASS_DECOY                                0xCB /* Decoy */
#define MOBY_CLASS_SWINGSHOT                            0xD0 /* Swingshot */
#define MOBY_CLASS_SWINGSHOT_HOOK                       0xD1 /* Swingshot Hook */
#define MOBY_CLASS_CRATE                                0x1F4 /* Crate */
#define MOBY_CLASS_NANOTECH_CRATE                       0x1F5 /* Nanotech Crate */
#define MOBY_CLASS_EXPLOSIVE_CRATE                      0x1F9 /* Explosive Crate */
#define MOBY_CLASS_AMMO_CRATE                           0x1FF /* Ammo Crate */
#define MOBY_CLASS_PURPLE_NANOTECH_CRATE                0x200 /* Purple Nanotech Crate */
#define MOBY_CLASS_DECOY_GLOVE                          0x232 /* Decoy Glove */
#define MOBY_CLASS_HELIPACK                             0x25F /* Helipack */
#define MOBY_CLASS_SWINGSHOT_NODE                       0x2F6 /* Swingshot Node */
#define MOBY_CLASS_SWINGSHOT_NODE_2                     0x323 /* Swingshot Node */
#define MOBY_CLASS_SPAWN_POINT                          0x325 /* Spawn Point */
#define MOBY_CLASS_TAXI                                 0x330 /* Taxi */
#define MOBY_CLASS_PLATINUM_BOLT                        0x46E /* Platinum Bolt */
#define MOBY_CLASS_TELEPORTER                           0x46F /* Teleporter */
#define MOBY_CLASS_MEGACORP_VENDOR_LOGO                 0x477 /* Megacorp Vendor Logo */
#define MOBY_CLASS_EXPLOSION_EFFECT                     0x4A8 /* Explosion Effect */
#define MOBY_CLASS_LAVA_GUN                             0x5C9 /* Lava Gun */
#define MOBY_CLASS_PLASMA_STORM                         0x5CA /* Plasma Storm */
#define MOBY_CLASS_PULSE_RIFLE                          0x5CB /* Pulse Rifle */
#define MOBY_CLASS_SEEKER_GUN                           0x5CE /* Seeker Gun */
#define MOBY_CLASS_MINIROCKET_TUBE                      0x5CF /* Minirocket Tube */
#define MOBY_CLASS_BLITZ_GUN                            0x5D1 /* Blitz Gun */
#define MOBY_CLASS_LANCER                               0x5D2 /* Lancer */
#define MOBY_CLASS_HOVERBOMB_PROJECTILE                 0x5D8 /* Hoverbomb Projectile */
#define MOBY_CLASS_SEEKER_PROJECTILE                    0x5D9 /* Seeker Projectile */
#define MOBY_CLASS_FIREBOOT_WEAPON                      0x820 /* Fireboot Weapon */
#define MOBY_CLASS_DYNAMO                               0x825 /* Dynamo */
#define MOBY_CLASS_ELECTROLYZER                         0x870 /* Electrolyzer */
#define MOBY_CLASS_CHOPPER                              0x879 /* Chopper */
#define MOBY_CLASS_LEVITATOR_PAD                        0x8E2 /* Levitator Pad */
#define MOBY_CLASS_ENEMY_HOVERBIKE_RACER                0x8EF /* Enemy Hoverbike Racer */
#define MOBY_CLASS_WATERFALL                            0x8F6 /* Waterfall */
#define MOBY_CLASS_WATERFALL_FROZEN                     0x8F7 /* Waterfall (frozen) */
#define MOBY_CLASS_WATERFALL_FROZEN_2                   0x8F8 /* Waterfall (frozen) */
#define MOBY_CLASS_WATERFALL_FROZEN_3                   0x8F9 /* Waterfall (frozen) */
#define MOBY_CLASS_GLIDER                               0x905 /* Glider */
#define MOBY_CLASS_SPIDERBOT_GLOVE                      0x907 /* Spiderbot Glove */
#define MOBY_CLASS_WATER                                0x908 /* Water */
#define MOBY_CLASS_SEESAW_BEAM                          0x90D /* Seesaw Beam */
#define MOBY_CLASS_BRIDGEBOT                            0x940 /* Bridgebot */
#define MOBY_CLASS_EXPLOSIVE_CRATE_2                    0x94C /* Explosive Crate */
#define MOBY_CLASS_HYPNOMATIC                           0x950 /* Hypnomatic */
#define MOBY_CLASS_GADGEBOT                             0x964 /* Gadgebot */
#define MOBY_CLASS_DESERT_CRYSTAL_SHELL                 0x96A /* Desert Crystal Shell */
#define MOBY_CLASS_CRYSTAL_SHELL_SHARD                  0x96D /* Crystal Shell Shard */
#define MOBY_CLASS_CRYSTAL_SHELL_SHARD_2                0x96E /* Crystal Shell Shard */
#define MOBY_CLASS_CRYSTAL_SHELL_SHARD_3                0x96F /* Crystal Shell Shard */
#define MOBY_CLASS_FAN                                  0x979 /* Fan */
#define MOBY_CLASS_ELEVATOR_FACTORY                     0x982 /* Elevator Factory */
#define MOBY_CLASS_ELEVATOR_RES                         0x983 /* Elevator - Res */
#define MOBY_CLASS_TUBE_START                           0x985 /* Tube Start */
#define MOBY_CLASS_GLIDER_PAD                           0x988 /* Glider Pad */
#define MOBY_CLASS_ANT_RING                             0x994 /* Ant Ring */
#define MOBY_CLASS_ANT_BRIDGE                           0x995 /* Ant Bridge */
#define MOBY_CLASS_RARITANIUM                           0x99A /* Raritanium */
#define MOBY_CLASS_BLUE_SWINGSHOT_TARGET                0x99D /* Blue Swingshot Target */
#define MOBY_CLASS_MUTANT_SWAMP_BEAST                   0x9A2 /* Mutant Swamp Beast */
#define MOBY_CLASS_FACTORY_DOOR                         0x9A3 /* Factory Door */
#define MOBY_CLASS_FACTORY_BOT_DOOR                     0x9A4 /* Factory Bot Door */
#define MOBY_CLASS_RES_BOT_DOOR                         0x9A6 /* Res Bot Door */
#define MOBY_CLASS_TRASH_CAN                            0x9B1 /* Trash Can */
#define MOBY_CLASS_SCENERY_SHIP                         0x9B7 /* Scenery Ship */
#define MOBY_CLASS_SPITTING_DUNE_CRAWLER                0x9C6 /* Spitting Dune Crawler */
#define MOBY_CLASS_CHAINBLADE                           0x9F8 /* Chainblade */
#define MOBY_CLASS_B2_BRAWLER_LEGS                      0xA44 /* B2 Brawler Legs */
#define MOBY_CLASS_MUTANT_FIREFLY                       0xA49 /* Mutant Firefly */
#define MOBY_CLASS_B2_BRAWLER_HEAD                      0xA4B /* B2 Brawler Head */
#define MOBY_CLASS_MEGACORP_CHICKENBOT                  0xA4E /* Megacorp Chickenbot */
#define MOBY_CLASS_SWAMP_MONSTER_II                     0xA54 /* Swamp Monster II */
#define MOBY_CLASS_MINI_NUKE                            0xA5A /* Mini-Nuke */
#define MOBY_CLASS_HOVERBOMB_GUN                        0xA5B /* Hoverbomb Gun */
#define MOBY_CLASS_SHIELD_CHARGER                       0xA5C /* Shield Charger */
#define MOBY_CLASS_SHEEPINATOR                          0xA5D /* Sheepinator */
#define MOBY_CLASS_MEGATURRET_GLOVE                     0xA65 /* Megaturret Glove */
#define MOBY_CLASS_RYNO_II                              0xA67 /* RYNO II */
#define MOBY_CLASS_HOVERBIKE_RACE_BOMB                  0xA77 /* Hoverbike Race Bomb */
#define MOBY_CLASS_SWAMP_MONSTER_I_ARM                  0xA8D /* Swamp Monster I Arm */
#define MOBY_CLASS_SWAMP_MONSTER_I_EYE                  0xA8E /* Swamp Monster I Eye */
#define MOBY_CLASS_SLOT_MACHINE                         0xA9C /* Slot Machine */
#define MOBY_CLASS_ELEVATOR                             0xAAA /* Elevator */
#define MOBY_CLASS_HOVERBIKE_RACE_ITEM_BOX              0xAB8 /* Hoverbike Race Item Box */
#define MOBY_CLASS_BLITZ_CANNON                         0xAF1 /* Blitz Cannon */
#define MOBY_CLASS_MULTI_STAR                           0xAF6 /* Multi-Star */
#define MOBY_CLASS_KILONOID                             0xB02 /* Kilonoid */
#define MOBY_CLASS_INFILTRATOR_BALL                     0xB28 /* Infiltrator Ball */
#define MOBY_CLASS_INFILTRATOR_LOCK                     0xB29 /* Infiltrator Lock */
#define MOBY_CLASS_MUTANT_MUCKDWELLER                   0xB2B /* Mutant Muckdweller */
#define MOBY_CLASS_ENEMY_HOVERBIKE                      0xB2D /* Enemy Hoverbike */
#define MOBY_CLASS_ARACHNOID                            0xB3A /* Arachnoid */
#define MOBY_CLASS_SPIDER_BOT                           0xB58 /* Spider Bot */
#define MOBY_CLASS_PROTOPET                             0xB69 /* Protopet */
#define MOBY_CLASS_DESER_RIDER_JOBA                     0xB7C /* Deser Rider (Joba) */
#define MOBY_CLASS_GRULCH                               0xB88 /* Grulch */
#define MOBY_CLASS_SPACE_TOURIST                        0xBB8 /* Space Tourist */
#define MOBY_CLASS_MEGACORP_ROBOT_GUARD                 0xBBF /* Megacorp Robot Guard */
#define MOBY_CLASS_TWO_HEADED_SMOLGIAN_SNAPPER          0xBCB /* Two-headed Smolgian snapper */
#define MOBY_CLASS_VAPORIZER                            0xC04 /* Vaporizer */
#define MOBY_CLASS_HEAVY_LANCER                         0xC05 /* Heavy Lancer */
#define MOBY_CLASS_MINI_NUKE_PROJECTILE                 0xC07 /* Mini Nuke Projectile */
#define MOBY_CLASS_SPAWNER                              0xC1A /* Spawner */
#define MOBY_CLASS_TURRET                               0xC20 /* Turret */
#define MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER 0xC3B /* Megacorp Security Robot - Flamethrower */
#define MOBY_CLASS_PX6_BLADEBALL                        0xC3E /* PX6 BladeBall */
#define MOBY_CLASS_PLASMA_COIL                          0xC4A /* Plasma Coil */
#define MOBY_CLASS_METEOR_GUN                           0xC59 /* Meteor Gun */
#define MOBY_CLASS_MINITURRET_GLOVE                     0xC5A /* Miniturret Glove */
#define MOBY_CLASS_TELEPORTER_2                         0xC60 /* Teleporter */
#define MOBY_CLASS_SYNTHENOID                           0xCB2 /* Synthenoid */
#define MOBY_CLASS_MEGACORP_HOVER_TANK                  0xCBC /* Megacorp Hover Tank */
#define MOBY_CLASS_AMMO                                 0xCDB /* Ammo */
#define MOBY_CLASS_GRAVITY_BOMB                         0xCE3 /* Gravity Bomb */
#define MOBY_CLASS_HK_22                                0xCEE /* HK-22 */
#define MOBY_CLASS_JOBA_TRIBESMAN                       0xCF5 /* Joba Tribesman */
#define MOBY_CLASS_JOBIAN_SAUR_BEAST                    0xD07 /* Jobian Saur-Beast */
#define MOBY_CLASS_MEGACORP_TROOPER_TORSO               0xD0E /* Megacorp Trooper Torso */
#define MOBY_CLASS_MEGACORP_TROOPER_LEGS                0xD0F /* Megacorp Trooper Legs */
#define MOBY_CLASS_UNKNOWN_THIEFS_WEAPON                0xD45 /* Unknown Thief's Weapon */
#define MOBY_CLASS_TRAIN_WITH_RAIL                      0xD5C /* Train with Rail */
#define MOBY_CLASS_TRAIN                                0xD9B /* Train */
#define MOBY_CLASS_SLIM_COGNITO_BUTTON                  0xDDC /* Slim Cognito Button */
#define MOBY_CLASS_SLIM_COGNITO_SHIP                    0xE0D /* Slim Cognito Ship */
#define MOBY_CLASS_BOUNCER                              0xE14 /* Bouncer */
#define MOBY_CLASS_TETRABOMB_GUN                        0xE2F /* Tetrabomb Gun */
#define MOBY_CLASS_THE_MYSTIC                           0xE3E /* The Mystic */
#define MOBY_CLASS_GLIDER_2                             0xE5B /* Glider */
#define MOBY_CLASS_CHARGE_BOOTS                         0xE70 /* Charge Boots */
#define MOBY_CLASS_TURRET_SPIDER_BOT                    0xE79 /* Turret Spider Bot */
#define MOBY_CLASS_TANKBOT_GLOVE                        0xE7A /* Tankbot Glove */
#define MOBY_CLASS_SHEEP                                0xE7D /* Sheep */
#define MOBY_CLASS_GIANT_CLANK_PAD                      0xE80 /* Giant Clank Pad */
#define MOBY_CLASS_SHADY_SALESMAN                       0xE95 /* Shady Salesman */
#define MOBY_CLASS_HEAVY_BOUNCER                        0xE9E /* Heavy Bouncer */
#define MOBY_CLASS_BLACK_SHEEPINATOR                    0xEAD /* Black Sheepinator */
#define MOBY_CLASS_DARK_SHEEP                           0xEB0 /* Dark Sheep */
#define MOBY_CLASS_ZODIAC                               0xEC8 /* Zodiac */
#define MOBY_CLASS_CLANK_ZAPPER                         0xED8 /* Clank Zapper */
#define MOBY_CLASS_RECEIVER_BOT                         0xEE1 /* Receiver Bot */
#define MOBY_CLASS_MINING_VEHICLE                       0xEEF /* Mining Vehicle */
#define MOBY_CLASS_EXTERMIBOT_LEGS                      0xF0A /* Extermibot Legs */
#define MOBY_CLASS_EXTERMIBOT_TORSO                     0xF0B /* Extermibot Torso */
#define MOBY_CLASS_ARCTIC_LEVIATHAN                     0xF57 /* Arctic Leviathan */
#define MOBY_CLASS_MOTHERSHIP_BOSS_PART                 0xF7F /* Mothership Boss Part */
#define MOBY_CLASS_SPACE_TOURIST_2                      0xF91 /* Space Tourist */
#define MOBY_CLASS_TV_SCREENS                           0xFA0 /* TV Screens */
#define MOBY_CLASS_THERMANATOR                          0xFB0 /* Thermanator */
#define MOBY_CLASS_THERM_WATER                          0xFB2 /* Therm Water */
#define MOBY_CLASS_MUTANT_TEST_SQUIRREL                 0xFB4 /* Mutant Test-Squirrel */
#define MOBY_CLASS_GADGETRON_HOUND_OF_CUDDLY_DEATH      0xFB6 /* Gadgetron Hound of Cuddly Death */
#define MOBY_CLASS_ELEVATOR_DAM                         0xFD8 /* Elevator Dam */
#define MOBY_CLASS_SECRET_DOOR                          0xFD9 /* Secret Door */
#define MOBY_CLASS_MEGACORP_SWEEPER_BOT                 0xFF3 /* Megacorp Sweeper Bot */
#define MOBY_CLASS_TRIBESMAN                            0xFF8 /* Tribesman */
#define MOBY_CLASS_MEGACORP_RIVET_BOT                   0xFFC /* Megacorp Rivet Bot */
#define MOBY_CLASS_MEGACORP_LASER_BOT                   0xFFD /* Megacorp Laser Bot */
#define MOBY_CLASS_MUTANT_SANDFLY                       0xFFF /* Mutant Sandfly */
#define MOBY_CLASS_DESERT_DUNE_MONSTER                  0x1002 /* Desert Dune Monster */
#define MOBY_CLASS_MEGAROCKET_CANNON                    0x1004 /* Megarocket Cannon */
#define MOBY_CLASS_YETI                                 0x10D0 /* Y.E.T.I. */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT                 0x10D4 /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_2               0x10D5 /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_3               0x10D6 /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_4               0x10D7 /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_5               0x10D8 /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_6               0x10D9 /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_7               0x10DA /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_8               0x10DB /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_9               0x10DC /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_10              0x10DD /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_11              0x10DE /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_12              0x10DF /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_13              0x10E0 /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_14              0x10E1 /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_15              0x10E3 /* Spaceship Attachment */
#define MOBY_CLASS_SPACESHIP_ATTACHMENT_16              0x10E5 /* Spaceship Attachment */
#define MOBY_CLASS_JOBA_BIRD                            0x1105 /* Joba Bird */
#define MOBY_CLASS_TESLA_BARRIER                        0x1192 /* Tesla Barrier */
#define MOBY_CLASS_NANOTECH_UPGRADE                     0x11C4 /* Nanotech Upgrade */
#define MOBY_CLASS_ARENA_CROWD                          0x126E /* Arena Crowd */
#define MOBY_CLASS_LAMP                                 0x12FA /* Lamp */
#define MOBY_CLASS_MINITURRET                           0x1366 /* Miniturret */
#define MOBY_CLASS_MEGATURRET                           0x1367 /* Megaturret */

#endif /* MOBY_CLASSES_H */
