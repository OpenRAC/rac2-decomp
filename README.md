<p align="center">
  <img src="assets/rac2-logo.png" alt="RAC2 — Going Commando" width="480">
</p>

# Ratchet & Clank: Going Commando (PS2) Decompilation

[![Tool tests](https://github.com/OpenRAC/rac2-gc-decomp/actions/workflows/tests.yml/badge.svg)](https://github.com/OpenRAC/rac2-gc-decomp/actions/workflows/tests.yml)
[![Progress report](https://github.com/OpenRAC/rac2-gc-decomp/actions/workflows/progress.yml/badge.svg)](https://github.com/OpenRAC/rac2-gc-decomp/actions/workflows/progress.yml)
[![Code](https://decomp.dev/OpenRAC/rac2-gc-decomp.svg?mode=shield&label=Code&measure=matched_code_percent)](https://decomp.dev/OpenRAC/rac2-gc-decomp)

A work-in-progress **matching decompilation** of *Ratchet & Clank: Going Commando* (Insomniac Games, 2003) for the PlayStation 2 (`SCUS_972.68`, accepted target **USA v1.01**; USA v2.00 is an experimental route), part of the **[OpenRAC](https://openrac.dev)** initiative. The goal is C/C++ that compiles to a byte-identical copy of the retail executable and its 27 level overlays.

> [!NOTE]
> This repository contains **no game assets, retail executables, or disassembly**. You must provide your own legally obtained copy of the game. Read [`LEGAL.md`](LEGAL.md) first; `scripts/legal_check.py` enforces it in CI.

> [!NOTE]
> AI-assisted research and tooling under human direction. A matching claim needs a byte-for-byte comparison against the pinned executable; an AI answer is not evidence.

## Progress

<!-- generated-progress:start -->
Recorded validation on **10 October 2026**:

| Scope | Integrated C functions / placements | Matched C bytes |
| --- | ---: | ---: |
| Boot | 376 functions | 30,104 |
| 27 level overlays | 13,886 placements | 1,312,280 |
| Native overlay subset, included above | 9,490 placements | 1,072,344 |
| **Total C coverage** | **Boot + all 27 overlays** | **1,342,384 / 48,788,176 (2.7515%)** |
<!-- generated-progress:end -->

All proofs above are **USA v1.01**, the default region. USA v2.00 is a separate experimental route (`--region v2`): its disc, boot and 27 overlays are pinned ([`docs/REGIONS.md`](docs/REGIONS.md)), but its candidates and its heuristic unique-code estimate add no matching credit and do not replace the figures above.

![Matched code](progress/decompilation.svg)

<!-- unique-code-progress:start -->
| Metric | Matched C bytes | Total code bytes | Progress |
| --- | ---: | ---: | ---: |
| Conservative unique EE code (unsupported extents uncollapsed) | 481,344 | 44,400,168 | 1.0841% |
| Loaded code (boot + 27 overlays) | 1,342,384 | 48,788,176 | 2.7515% |

Structurally supported function extents cover 40,075,248 loaded EE bytes; 231,732 EE bytes remain unresolved. VU code excluded: 86,368 bytes.
Provisional representative partition: 37,641,816 bytes (certified: false); no global progress percentage is inferred from this partition.
Conservative global partition retains unknown extents and gaps without deduplication: 8,626,560 loaded EE bytes have unsupported boundaries. The total follows the stated grouping policy and is not a certified original-source size. Supported subset: 481,344 / 35,773,608 unique bytes.

Shared boot binding: 22,576 static edges in combined pinned reference images. Runtime code preservation is unproved. See [the binding and remaining-duplication audit](docs/BOOT-SHARED-CODE-VERIFICATION.md).
<!-- unique-code-progress:end -->

![Unique and loaded code](progress/unique-decompilation.svg)

## Quick Start (default: USA v1.01)

1. Clone and install: `git clone https://github.com/OpenRAC/rac2-gc-decomp && pip install -r requirements.txt`
2. Put `SCUS_972.68` from your own v1.01 disc in `baserom/` (hashes in `config/target.json`).
3. Check your setup: `python scripts/doctor.py --iso <your.iso>`
4. Prepare the reference (needs [Wrench](https://github.com/chaoticgd/wrench) `wrenchbuild`):
   `python scripts/setup.py --iso <your.iso> --runtime <private dir> --wrench <wrenchbuild>`
5. Pick a function: `python scripts/function_size_rank.py --region ntsc-u --category small --status todo --ascending`

**Experimental USA v2.00 route** (candidates only, no matching credit): add `--region v2` to the commands above, SHA-1 `4124a79c1e5a1ceb56f514df0dbbc11f072af56f`; see [`docs/V2-SETUP.md`](docs/V2-SETUP.md).

6. Fetch the legacy SN Systems toolchain and SDK yourself (community mirrors, **not** part of this repository and git-ignored; check their licences before use):
   ```bash
   git clone https://github.com/AngheloAlf/SN-Systems-ProDG_for_PS2_3.01 toolchain/sn-prodg-3.01
   git clone https://github.com/AngheloAlf/sce_ps2_sdk_24 toolchain/sn-prodg-24
   ```

Compiler and linker requirements are in [`toolchain/README.md`](toolchain/README.md); the full walkthrough is [`docs/START-HERE.md`](docs/START-HERE.md).

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md), [`docs/CONTINUE.md`](docs/CONTINUE.md) and the [campaign workflow](docs/CAMPAIGN-WORKFLOW.md). Claim work in [`docs/CONTRIBUTOR-RESERVATIONS.md`](docs/CONTRIBUTOR-RESERVATIONS.md) before starting. Write everything in English with scoped, detailed commit messages.

## Credits

- **GFI (Game Fuckery Inc.)** community: years of reverse engineering and research.
- **[RC2-Going-Decompiled](https://github.com/Promises/RC2-Going-Decompiled)** by Promises: v2.00 symbol names and the matching-build approach for `tools/ee/`.
- **[rac1-decomp](https://github.com/OpenRAC/rac1-decomp)** and **[rac3-uya-decomp](https://github.com/OpenRAC/rac3-uya-decomp)**: repository layout, compiler findings and engine research.
- **[Wrench](https://github.com/chaoticgd/wrench)** by chaoticgd: PS2 Ratchet & Clank formats and level extraction.

## License

MIT — see [LICENSE](LICENSE). It covers this repository's code, never the game, its assets or proprietary toolchains. *Ratchet & Clank* is a trademark of Sony Interactive Entertainment; this project is not affiliated with Sony or Insomniac Games. `ports/pal-functional/` keeps its own MIT notice in [its LICENSE](ports/pal-functional/LICENSE).
