# Code style

Short rules for C in `src/` and `include/`, carried from rac1-decomp's
`docs/contributing/style.md`. If a rule would change the compiled bytes, the bytes win. Leave a
short comment that says why.

## Names

| What | Style | Example |
|---|---|---|
| Function | `snake_case`, system first | `hero_set_move_state`, `yeti_update` |
| Copy of a function in one level | system, then level | `hero_l04_update_state_machine` |
| Global | `g_` + `snake_case` | `g_active_yeti_count` |
| File-local data | `s_` + `snake_case` | `s_fade_timer` |
| Local variable, parameter | `snake_case` | `path_point`, `moby` |
| Type | `PascalCase` | `HeroMotion` |
| Moby private data | class name + `Vars` | `YetiVars` |
| Enum value, macro | `UPPER_CASE`, with a shared prefix | `MOBY_CLASS_YETI` |
| Unknown field | offset | `unk_24` |
| Unknown function, data | address | `func_002A77E0`, `D_001A8CFC` |

- Readable names are macros over address names. Add them to `config/names_local.tsv`, not to
  `include/names.h` ([names.md](names.md)).
- Never respell recovered names (tier `recovered` in `config/names.tsv`) or library names
  (`memcpy`, `sceSifSendCmd`).
- A name says what the thing is. No numbers from the disc: not `moby_4966_update`.

## Moby classes

`include/moby_classes.h` names the class ids that have a label in
`docs/game/moby-dispatch.tsv`: write `MOBY_CLASS_MINITURRET`, not `0x1366`. A class with no
label keeps its number with `/* moby class 4710 */`.

## Comments

Every function gets one or two short sentences in simple English: what it does, and why the C
has this shape if that is not clear.

```c
/* Spawns a Yeti at the next free spawn point. */
```

Do: use names ("Spawns a Yeti"); say what a number means when it has no name yet
(`/* 0x1C: frames left */`).

Do not: use IDs when a name is known (`/* class 0x10D0 */`); use `func_`, `D_` or `+0x` when a
name or field exists; leave worker notes ("matches now", "regalloc"); repeat what the code says.

Keep matching notes and provenance notes (carried code, licence credit) unchanged.

## Markers

| Marker | Meaning |
|---|---|
| `/* FAKEMATCH: <reason> */` | The code matches, but it is not what the authors wrote. Tracked in `config/fakematch.tsv`. |
| `INCLUDE_ASM` | Not matched in C yet. |
| `ASM_FUNC` | Original assembly. It stays assembly. |

## Format

4 spaces, K&R braces, 120 columns. No tabs and no trailing spaces in new code.
