# USA v2.00 on Linux: reproduce the setup and help decompile

Everything below was run end to end on Fedora x86-64 with Podman. You need your **own** USA v2.00 disc image
(`SCUS_972.68`, SHA-256 `eda31b45…` in [`config/regions/ntsc-u-v2/target.json`](../config/regions/ntsc-u-v2/target.json))
and you must follow [`LEGAL.md`](../LEGAL.md). Keep every tool, ISO and build output **outside Git**
(`~/rac2-private/` below); `scripts/legal_check.py` runs in CI.

## 1. Environment

```bash
git clone https://github.com/OpenRAC/rac2-gc-decomp && cd rac2-gc-decomp
python3 -m venv ~/rac2-private/venv && ~/rac2-private/venv/bin/pip install -r requirements.txt
mkdir -p baserom && 7z x -obaserom "<your v2.00 iso>" SCUS_972.68      # or copy it from your disc
python scripts/doctor.py --region v2 --iso "<your v2.00 iso>"          # disc and boot must match the pins
python scripts/function_size_rank.py --category small --status todo --ascending --limit 20
```

## 2. Prepare the reference (Wrench)

Download `wrenchbuild` from the [official releases](https://github.com/chaoticgd/wrench/releases), then:

```bash
~/rac2-private/venv/bin/python scripts/setup.py --region v2 --iso "<iso>" --runtime ~/rac2-private/runtime \
  --sevenzip /usr/bin/7z --wrench <path>/wrenchbuild
```

It verifies the disc and extracts the boot and the 27 overlays (all pinned in `config/regions/ntsc-u-v2/`).

## 3. Assembly round trip (SN ProDG 2.0 + wibo)

Third-party community mirrors; not part of this repository, check their licences. Place the files in
`toolchain/sn-prodg-2.0/ee/bin/` (git-ignored) or any private directory:

- `ps2eeas.exe` from `AngheloAlf/SN-Systems-ProDG_for_PS2_2.0` (`usr/local/sce/ee/gcc/ee/bin/`), saved as `Ps2EeAs.exe`
  (SHA-256 must be `c839dd63…`), and its `ld.exe` (`80f3724a…`). The ProDG 3.01 and SDK 2.4 assemblers do **not** reproduce v2.00.
- [wibo](https://github.com/decompals/wibo) (`wibo-x86_64`) to run the Windows tools on Linux.

```bash
export RAC2_EXE_RUNNER=<path>/wibo-x86_64
~/rac2-private/venv/bin/python scripts/build.py --region v2 --manifest <runtime>/runs/<run>/manifest.json \
  --toolchain <dir containing ee/bin> --all-levels --jobs 8
```

Expected: the boot and all 27 overlays report `All PT_LOAD bytes and metadata match`.

## 4. Build the compiler (GNU EE 2.9-ee-991111b)

```bash
tools/linux/build-compiler.sh ~/rac2-private/compiler       # ~2 minutes, needs podman or docker
```

All inputs are public and SHA-256 checked. The script applies only published transformers (`tools/linux/rac2_recipe.py`)
and prints the five source hashes; all must equal the checkpoint table in [`COMPILER-NOTES.md`](COMPILER-NOTES.md)
(`mips.c 4a6a1ae1…`, `mips.h 87d59c06…`, `mips.md 9720897d…`, `toplev.c 38d52727…`, `tc-mips.c b22dfff8…`).
They do on Ubuntu 24.04 and 26.04 (`UBUNTU=26.04 tools/linux/build-compiler.sh …`). The `cc1`/`cpp`/`as` **binary** hashes
depend on the build host and do not equal the documented ones, so record your own in any proof.
Behavioural check: compiling `candidates/boot.c` gives bytes identical to the recorded v1.01 proofs for all 210
relocation-free functions (the other 99 need a link to compare).

## 5. Try a function

```bash
podman run -d --init --name rac2-gnu --userns=keep-id --security-opt label=disable -v $HOME:$HOME \
  --tmpfs /rac2tmp:exec,mode=1777 rac2-linux:24.04 sleep infinity
export PYTHONPATH=$PWD/tools/linux RAC2_LINUX_RUNNER="podman exec rac2-gnu bash -c" \
  RAC2_WSL_TOOLS=$HOME/rac2-private/compiler/tools RAC2_WSL_TMP=/rac2tmp
python scripts/try_function.py trials/usa-v2/IntToFloat.c --address 0x284690 --size 16     # prints MATCH
```

Write your function in `trials/usa-v2/`, compare, then iterate on the C shape (see the notes in
[`trials/usa-v2/README.md`](../trials/usa-v2/README.md)). Leaf functions compare exactly; calls and globals carry relocations.

## 6. decomp.dev report

`python scripts/function_size_rank.py` and `python scripts/v2_report.py catalog --reference <reference dir>` refresh the committed
structure-only catalogue (`config/regions/ntsc-u-v2/catalog.json`). After a function matches, add `--record` to
`scripts/try_function.py` to store its proof in `progress/v2/matches.json`, then
`python scripts/v2_report.py report --output build/decomp/report.json` builds the objdiff report CI uploads to decomp.dev.
Totals are a heuristic estimate (about 5.27 MB): boot extents are inferred and level code is normalised chunks with relocation fields and immediates erased, so different constants can collapse into one body. They are not comparable to the official loaded-byte or conservative unique-code figures and are never a denominator. Matches recorded here are exploratory candidates and earn no credit in the report.

## 7. Contribute

Claim a small lot in [`CONTRIBUTOR-RESERVATIONS.md`](CONTRIBUTOR-RESERVATIONS.md) first, open a draft PR against `RAC2`
as described in [`CONTRIBUTOR-QUICKSTART.md`](CONTRIBUTOR-QUICKSTART.md), and keep matching claims honest:
a function counts only after the campaign byte gates pass.
`python scripts/measure_unique.py --reference <runtime>/runs/<run>/reference` estimates unique v2.00 code (about 5.25 MB, heuristic; see section 6).

## 9. Deduplicated v1.01 estimate (accepted target)

The accepted v1.01 target counts 48.8 MB of loaded code because the engine is repeated in each of the 27 overlays.
`python scripts/unique_estimate.py catalog --reference <v1.01 reference> --elf <reference>/boot.elf` (private input, then commit
`config/estimates/ntsc-u.json`) and `python scripts/unique_estimate.py report --output build/decomp/unique-estimate-report.json`
build a separate decomp.dev report in which each distinct body counts once (relocation fields masked by a register-tracking heuristic).
Credit comes only from accepted proofs of identical digest and extent, so it adds nothing to the official figures. CI uploads it as
`SCUS_972.68_unique_estimate`; the maintainer's `SCUS_972.68_report` is unchanged.
