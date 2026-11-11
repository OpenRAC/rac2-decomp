# Prototype builds — which one to use, and for what

**Measured November 2026 against the pinned retail boot** (`SCUS_972.68`, USA v1.01,
2 618 684 bytes, sha256 `36d5814d…`, `config/target.json`).

All six known 2003 prototype builds were obtained and measured. This document records what
each one is good for, and how the builds relate to the retail program.

## What was measured

| Build | Serial | Boot size | SHA256 (first 8) | Level archives |
| --- | --- | ---: | --- | --- |
| **6 Aug 2003** (NTSC preview) | `SCUS_972.68` | 1 541 852 | `5342b8e9` | 51 files on disc |
| **8 Aug 2003** (PAL preview) | `SCES_516.07` | 1 541 852 | `26228247` | 96 files on disc |
| **18 Aug 2003** (NTSC alpha) | `SCUS_972.68` | 1 542 156 | `a594cf3d` | 51 files on disc |
| **4 Sep 2003** (NTSC preview) | `SCUS_972.68` | 3 489 116 | `ec323260` | 97 files on disc |
| **7 Sep 2003** (NTSC review) | `SCUS_972.68` | 3 497 308 | `9fb9c47b` | 97 files on disc |
| **9 Sep 2003** (PAL review) | `SCES_516.07` | 3 505 500 | `2f0b590f` | 97 files on disc |

**No build carries symbols.** All six boot executables have zero `.symtab`, `.strtab`, or
DWARF `.debug_*` sections.

### Build groupings

1. **The August cluster (Aug 6, Aug 8, Aug 18):**
   - Entry point: `0x001318E8` across all three.
   - Section count: 68 sections.
   - Boot binary size: ~1.54 MB.
   - **Aug 6 and Aug 8 differ by only 15 bytes in `.text`** (a single 16-byte patch block at offset `0x153D78` returning early from a display initialization routine).
   - Aug 18 adds 304 bytes (+0x130) to the binary, retaining the exact same entry point and segment order.
   - Debug strings are heavily stripped in this cluster, matching retail string density.

2. **The September cluster (Sep 4, Sep 7, Sep 9):**
   - Entry point: `0x001344B8` across all three.
   - Section count: 72 sections.
   - Boot binary size: ~3.49–3.50 MB.
   - The September builds incorporate unstripped debug assertions, diagnostic menus, memory-map reporting, and developer source filename strings (see `docs/research/prototype-engine-symbols.md`).
   - The 7 and 9 September boots are the same code with minor region asset differences (8 192 bytes of data differ between the NTSC review and PAL review images).

## Distance to the retail

Identical bytes over the common window of each section, prototype vs retail USA v1.01:

| Section | 6 Aug | 8 Aug | 18 Aug | 4 Sep | 7 Sep | 9 Sep |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| `core.text` | **26.5 %** | **26.5 %** | **26.5 %** | 12.1 % | 12.1 % | 12.1 % |
| `core.data` | **93.8 %** | **93.8 %** | **92.7 %** | 91.4 % | 91.4 % | 91.4 % |
| `core.rdata` | **88.7 %** | **88.7 %** | **88.6 %** | 22.4 % | 22.4 % | 22.4 % |
| `.data` (resident) | 59.8 % | 59.8 % | 59.8 % | **64.0 %** | **64.0 %** | **64.0 %** |

The September builds add roughly 11 400 bytes to `core.text` over the August size
(125 008 → 136 440, against 125 264 in retail), and that insertion shifts everything
after it, which is why twice as much code stops matching byte-for-byte. **For byte-crossing
toward retail, the August cluster is the better code anchor by a factor of two.**

## A working data bridge

Using the 178 assert messages localized in the retail boot as anchors, and finding the
same strings in the September boots, the deltas cluster instead of scattering:

| Sections (retail ← prototype) | Anchors | Dominant delta |
| --- | ---: | --- |
| `core.data` ← `core.data` | 4 | **−0x2B80** (4/4) |
| `core.rdata` ← `core.rdata` | 85 | **−0x32F0** (83/85) |
| other section pairs | — | scattered — no global correspondence |

An independent anchor family agrees on the first one: the 64-byte display block at retail
`0x00138040` sits at prototype `0x0013abc0`, which is exactly `+0x2B80`. So within
`core.data` and within the string block of `core.rdata`, a prototype address maps to the
retail by a constant that can be *computed*, not guessed. Outside those regions it does
not, and nothing is named from a projection.

## Which build to reach for

| Need | Build |
| --- | --- |
| Anchors for byte-crossing toward the retail | **Aug 6 / Aug 8 / Aug 18** (closest code and data) |
| Recovered source filenames, assertions, and enums | **Sep 4 / Sep 7 / Sep 9** (contains 40+ module paths and hundreds of assertions) |
| Level archives and level content | Any August or September build — both use the same level table and section format |
| Engine module split & subsystem architecture | Any — the two-module shape (CORE + FRONTEND) is consistent across all six |
| What community research tooling (`rc2_aug8_research`) targets | **Aug 6 / Aug 8** — boot offset, size, and patch sites align with these images |

## Limits

- **Sourcing policy:** Per `AGENTS.md`, prototype builds may be cited naming the build,
  never as the evidence for a match. Retail USA v1.01 byte identity is the sole evidence.
- "Closest" means identical bytes over the common window of a section. It is a
  proxy for usefulness as an anchor, not a statement about which build is more similar in
  behaviour.
- No proprietary binaries, disc images, extracted executables, or tools are committed to the
  repository (`baserom/`, `build/`, `toolchain/`, and `work/` remain ignored).
