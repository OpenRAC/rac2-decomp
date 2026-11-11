# Engine Symbols, Subsystems, and Assertions from Prototype Builds

**Measured November 2026 from preserved pre-release builds** (specifically the September 2003
cluster: `Sep 04` NTSC preview, `Sep 07` NTSC review, `Sep 09` PAL review).

This document catalogs the recovered source filenames, subsystem architectures, internal
enumerations, global object layouts, and assertion messages discovered in preserved public
Going Commando pre-release builds.

---

## 1. Sourcing Boundary & Policy Compliance

Per `AGENTS.md` and `docs/policy/SOURCING.md`:
- **Evidence standard:** Prototype builds may be cited by name, but are never evidence for
  a match. A function is only matched when `tools/build.py all --strict` produces byte-identical
  retail output for USA v1.01 (`SCUS_972.68`).
- **What is permitted to be included:**
  1. **Source filenames & modularity:** Mapping unnamed address-based files (`src/game/00288D88.c`,
     `src/game/002D5E98.c`) to their original module names (`hud.cpp`, `menu.cpp`, `vendor.cpp`).
  2. **Readable symbol aliases:** Adding recovered function, variable, and struct aliases to
     `include/names.h` and shared headers.
  3. **Accurate types and enums:** Replacing generic integers or magic hex numbers with the
     engine's actual enumeration names (`GAME_MODE_*`, `GADGET_*`, `CS_*`) in `include/` headers.
- **What is NOT permitted:**
  - Committing disc images, extracted ELFs, or proprietary tools to git (`baserom/`, `build/`,
    `toolchain/`, and `work/` are ignored).
  - Introducing artificial compiler barriers or fake code that diverges from retail bytes.

---

## 2. Recovered Source File Paths and Hierarchy

Unlike the stripped retail boot executable, the September 2003 preview builds retain dozens of
unstripped assertion paths revealing Insomniac's original repository hierarchy:

### Core Engine & System
| Path in Build | Description / Primary Role |
| :--- | :--- |
| `globals.cpp` | Global subsystem state and engine initializers |
| `db_core.cpp` | Debug core dispatch and profiling hooks |
| `framebuf.cpp` | GS framebuffer management, vram sizing, and resolution logging |
| `freeze.cpp` | In-game pause / debug freeze state machine |
| `loaders.cpp` | Disc WAD streaming, level chunk loading, texture parsing |
| `tables.cpp` | Static tables, configuration maps, and game progression parameters |
| `mode.cpp` | Global game mode transitions and mode stack (`modeStackIndex`) |
| `mcstate.cpp` | Memory Card state machine and transaction handling |
| `save.cpp` | Save game serialization, Moby instance persistence, and slot management |

### Audio
| Path in Build | Description / Primary Role |
| :--- | :--- |
| `music.cpp` | Interactive level and cutscene music streaming |
| `/usr/local/989snd/ee/989snd.c` | Sony 989 Sound System library integration |

### Rendering & Hardware Pipeline
| Path in Build | Description / Primary Role |
| :--- | :--- |
| `vuchain.cpp` | VU1 microprogram DMA chain builder and DMAC channel 1 dispatcher |

### Gameplay Subsystems
| Path in Build | Description / Primary Role |
| :--- | :--- |
| `herob.cpp` | Ratchet movement, input processing, and physics state (`Hero.pMoby`) |
| `mobyfunc.cpp` | Moby manipulation, anim buffer dispatch, and shadow rendering |
| `mobyutil.cpp` | Moby group tracking, challenge XP allocation, and distance scaling |
| `update.cpp` | Master frame update loop (hero, moby, particle, camera, sound) |
| `npc.cpp` | Non-player character dialogue and parameter parsing |
| `mission.cpp` | Planet mission state and objective transitions (`MSTATE_DONE`) |
| `gadgets.cpp`, `gadgets.h` | Weapon and gadget inventory, ammo, and upgrade logic |
| `vendor.cpp` | Megacorp vendor and Slim Cognito shop interfaces |
| `space.cpp` | Space level scene management and audio bank loading |
| `spacecombat.cpp` | Space ship dogfighting, squad leader AI, and ship gadgets |

### Moby Update Implementations (`update/`)
The engine delegates class-specific updates to individual translation units in `update/`:
- `update/moby2078.cpp` (Class 2078)
- `update/moby2080.cpp` (Class 2080)
- `update/moby2662.cpp` (Class 2662)
- `update/moby2715.cpp` (Class 2715)
- `update/moby2862.cpp` (Class 2862)
- `update/moby3078.cpp` (Class 3078)
- `update/moby3301.cpp` (Class 3301)
- `update/moby4016.cpp` (Class 4016)

### GUI and HUD (`gui/`)
- `gui/behaviors.cpp` — Interactive menu behaviors and slot mapping
- `gui/graphicObjects.cpp` — 2D UI render primitives and text alignment
- `gui/mathUtil.cpp` — Coordinate scaling and easing math (`t >= 0.0f && t <= 1.0f`)
- `gui/memoryManagement.cpp` — Dedicated GUI allocator and heap tracking
- `gui/rc2Hud.cpp` — Going Commando HUD widget renderer (brackets, timelines)
- `hud.cpp` — In-game HUD moby allocation and bank rendering
- `menu.cpp` — Quick-select wheel and main pause menus
- `pause.cpp` — Pause menu state, challenge transitions, and planet info
- `map.cpp` — Full-screen planet map, fog-of-war, and mask rendering

---

## 3. Verified Engine Enumerations and Constants

### Game Modes (`GAME_MODE_*`)
Found in `mode.cpp`:
```c
enum GameMode {
    GAME_MODE_NONE             = 0,
    GAME_MODE_DEBUG            = 1,
    GAME_MODE_NORMAL           = 2,
    GAME_MODE_MOVIE            = 3,
    GAME_MODE_SCENE            = 4,
    GAME_MODE_PAUSE            = 5,
    GAME_MODE_FREEZE           = 6,
    GAME_MODE_VENDOR           = 7,
    GAME_MODE_SPACE            = 8,
    GAME_MODE_PUZZLE           = 9,
    GAME_MODE_HOVERBIKE_PAUSE  = 10,
    GAME_MODE_WEAPON_UPGRADE   = 11,
    GAME_MODE_CREDITS          = 12,
};
```

### Movie Playback Types (`MOVIE_*`)
```c
enum MovieType {
    MOVIE_INFOBOT  = 0,
    MOVIE_HELP     = 1,
    MOVIE_SPECIAL  = 2,
    MOVIE_STORY    = 3,
};
```

### Card Save States (`CS_*`)
Found in `mcstate.cpp`:
```c
enum CardSaveState {
    CS_INIT,
    CS_GOOD_SAVE,
    CS_WARNING,
    CS_NOCARD,
    CS_WAIT_FOR_CARD,
    CS_UNFORMATTED,
    CS_PROMPT_FORMAT,
    CS_FORMAT_PENDING,
    CS_FORMATTING,
    CS_FORMATTED,
    CS_CHECK_SAVE,
    CS_CHECKING_SAVE,
    CS_NOSAVE,
    CS_PROMPT_CREATE_SAVE,
    CS_CREATE_SAVE_PENDING,
    CS_CREATING_SAVE,
    CS_NEWCARD,
    CS_FORMAT_FAILED,
    CS_CREATE_FAILED,
    CS_NO_ROOM,
    CS_LOAD_FAILED,
    CS_SAVE_FAILED,
    CS_SAVING,
    CS_PROMPT_BEGIN_UNFORMATTED,
    CS_PROMPT_BEGIN_NOSAVE,
    CS_EOL,
};
```

### Weapons & Gadgets (`gadgets.h`)
The complete internal gadget identifiers:
```c
enum GadgetId {
    GADGET_UNDEFINED = 0,
    GADGET_CORE_PACK,
    GADGET_HELI_PACK,
    GADGET_ROCKET_PACK,
    GADGET_HYDRO_PACK,
    GADGET_SONIC_SUMMONER,
    GADGET_O2_MASK,
    GADGET_PILOT_HELMET,
    GADGET_WRENCH,
    GADGET_SUCK_CANNON,
    GADGET_BOMB_GLOVE,
    GADGET_DEVASTATOR,
    GADGET_GRAPPLING_HOOK,
    GADGET_VISIBOMB_GUN,
    GADGET_TAUNTER,
    GADGET_BOLT_GUN,
    GADGET_PYROCITOR,
    GADGET_MINE_GLOVE,
    GADGET_WALLOPER,
    GADGET_TESLA_CLAW,
    GADGET_GLOVE_OF_DOOM,
    GADGET_MORPHA_RAY,
    GADGET_HYDRODISPLACER,
    GADGET_RYNO,
    GADGET_DEFENSE_DROIDS,
    GADGET_INFLATO_RATCHET,
    GADGET_TRESPASSER,
    GADGET_METAL_DETECTOR,
    GADGET_MAGNE_BOOTS,
    GADGET_GRIND_BOOTS,
    GADGET_HOVERBOARD,
    GADGET_HOLO_GUISE,
    GADGET_PDA,
    GADGET_MAPOMATIC,
    GADGET_BOLT_GRABBER,
    GADGET_PERSUADER,
    GADGET_HOVER_ROCKETS,
    TOTAL_GADGETS,
};
```

Additional gadget identifiers and equipment categories listed in `gadgets.h`:
`RATCHET_HP`, `BOLTS`, `ENEMY`, `ARMOR`, `ENEMY_BOLTS`, `ENEMY_XP`, `MAJORBOLTS`, `MINORBOLTS`,
`OTHERBOLTS`, `MAJORXP`, `MINORXP`, `SHEEPANATOR`, `CHOPPER`, `SNIPER_RIFLE`, `HOMING_GRENADE`,
`HOVERBOMBLAUNCHER`, `SWARMGUN`, `MINITURRET_GLOVE`, `GRAVITY_BOMB`, `BLITZ_GUN`,
`MINIROCKET_GUN`, `PLASMA_COIL`, `LAVAGUN`, `LANCER`, `SYNTHENOID`, `SPIDERBOT`,
`WHISTLER_LAUNCHER`, `BOUNCER`, `ZODIAC`, `MAGNETIZER`, `HOOK`, `GLIDER`, `FIRETRAIL`,
`DYNAMO`, `SHIELD_CHARGER`.

---

## 4. Global Structures and Named Singletons

The assertions provide verified names for several of the game's core global subsystems:

| Prototype Name | Decompiled Symbol (Retail) | Evidence & Context |
| :--- | :--- | :--- |
| `Hero.pMoby` | `D_001A8C88` / `D_00189EA0` | `herob.cpp`: `Hero.pMoby != NULL` |
| `Hud.header` | `D_001B23A0` group | `loaders.cpp`: `Hud.header->bank_handle[2] >= 0` |
| `Map.level` | `D_001A72DC` | `mission.cpp`: `Map.level >= 0 && Map.level < MAX_LEVELS` |
| `Music.off` / `Music.loading` | `D_001A79F0` group | `music.cpp`: `!Music.off`, `Music.loading` |
| `Pause.loading` | `D_001F2840` group | `pause.cpp`: `Pause.loading == 0` |
| `Vendor.gadget_count` | `D_0025A058` group | `vendor.cpp`: `Vendor.gadget_count > 0` |
| `Settings.PalMode` | PAL mode flag | `freeze.cpp`: `Settings.PalMode == false` |
| `MobyInstances` | `D_001A8A70` / moby heap base | `save.cpp`: `pMoby >= MobyInstances && pMoby < MobyInstancePermEnd` |
| `MobyGroupCnt` | Group table length | `spacecombat.cpp`: `pMoby->group < MobyGroupCnt` |
| `RC2PowerUpLevel` | Weapon evolution array | `gadgets.cpp`: `RC2PowerUpLevel[i] == i` |

---

## 5. Memory Map Layout and Heap Categories

The `*** MEMORY MAP ***` diagnostic printout in `loaders.cpp` defines the exact engine
categories used during level chunk initialization:

1. `os` — Core PlayStation 2 kernel memory and stack
2. `code mem` — Executable program text and resident engine code
3. `tfrag geom` — Terrain fragment geometry packets
4. `occlusion` — Static occlusion culling tables
5. `sky` — Sky dome vertex buffers and textures
6. `collision` — Octree spatial collision meshes
7. `shared vram` — Shared GS VRAM texture allocations
8. `particle vram` — Particle texture memory
9. `effects vram` — Screen-space visual effect buffers
10. `mobys` — Moby class definition templates
11. `ties` — Static object model instances
12. `shrubs` — Instanced vegetation geometry
13. `ratchet seqs` — Hero animation sequence curves
14. `help messages` — Localized tutorial and help strings
15. `tie insts` — Instanced static object instances
16. `shrub insts` — Shrub instance matrices
17. `moby insts` — Dynamic actor instance buffers (`MobyInstances`)
18. `moby pvars` — Moby private variable heaps
19. `misc insts` — Miscellaneous level props
20. `part insts` — Active particle system instances
21. `vu chain bufs` — Vector unit DMA double-buffers
22. `tie cache` — Static tie transform cache
23. `hud` — Heads-Up Display textures and sprite geometry
24. `gui` — Pause/vendor menus and map buffers

---

## 6. Community Patcher and Protection Analysis

The preserved archive `Ratchet & Clank - Going Commando (Sep 4, 2003 prototype).7z` includes
a tool named `RC2_LateDebug_Patcher.exe`:
- **Function:** PE32 console utility created by community researcher "Louis".
- **Purpose:** Disables the WIBU-BOX copy protection dongle check (`cdrom0:\WIBU.IRX;1` / `wibu_ee: RPC collision!`)
  which prevented unpatched preview builds from running on retail debug stations or emulators without
  the physical hardware security dongle connected to the PS2 USB port.
- **Decompilation impact:** The decompilation targets retail USA v1.01 (`SCUS_972.68`), which had
  all development dongle checks removed before gold master manufacturing.

---

## 7. Actionable Improvements for the Decompilation

1. **Header Updates (`include/`):**
   - Add `include/gadgets.h` with `enum GadgetId` matching `GADGET_*` to replace magic IDs across
     weapons and inventory modules.
   - Add `enum GameMode` to `include/mode.h` matching `GAME_MODE_*`.
   - Add `enum CardSaveState` to `include/save.h` matching `CS_*`.
2. **Naming Updates (`include/names.h`):**
   - Add readable aliases for `Hero.pMoby`, `MobyInstances`, `MobyGroupCnt`, and `RC2PowerUpLevel`.
   - Rename functions corresponding to known assertion boundaries (e.g., `MobyUpdate`, `SaveGame`,
     `InitMusic`, `ParsePermGsRam`).
3. **Module Splitting Guidance:**
   - Units currently labeled by address (e.g. `src/game/002D5E98.c`) correspond to distinct
     original modules (`menu.cpp`, `vendor.cpp`, `pause.cpp`). Splitting them into `-g8.c` or
     semantic sub-units aligned with these original names will improve readability and maintainability.
