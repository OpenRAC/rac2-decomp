# Continue the decompilation

If this is your first contribution, use [CONTRIBUTOR-QUICKSTART.md](CONTRIBUTOR-QUICKSTART.md)
first. Its fork/PR route is separate from an owner-authorized ongoing campaign.
Tool acquisition and setup levels are described in [toolchain/README.md](../toolchain/README.md).

Open this repository's local checkout on branch `RAC2`. A short request to
continue matching decompilation is sufficient when the repository instructions
and the private machine environment are available. No long pasted prompt is
required. The accepted campaign, default region and every proof are USA v1.01 (`config/target.json`). USA v2.00 (`--region v2`, `config/regions/ntsc-u-v2/`) is a separate, experimental route: its results are exploratory candidates and add no matching credit.

## Experimental: short request on USA v2.00: "decompile N small functions"

The v1.01 campaign commands below stay the default and have no v2.00 catalogues. For v2.00 follow this loop; stop and report the first missing prerequisite
(ISO, `baserom/SCUS_972.68`, ProDG 2.0 files, compiler chain, Podman container) instead of substituting another route.

1. `python scripts/doctor.py --region v2 --iso <iso>` and the setup in [V2-SETUP.md](V2-SETUP.md) (steps 1-5). Verify the chain's five
   source hashes (`tools/linux/build-compiler.sh`) and start the `rac2-gnu` container.
2. Pick targets: `python scripts/function_size_rank.py --category small --status todo --ascending --limit 40`. Skip calls into VU0/COP2,
   `syscall`, and in-place `cvt.w.s $f12,$f12` words (handwritten; see `trials/usa-v2/README.md`). Read the words with `rabbitizer`.
3. Reserve the lot in [CONTRIBUTOR-RESERVATIONS.md](CONTRIBUTOR-RESERVATIONS.md) and wait for acknowledgement.
4. For each function write `trials/usa-v2/<Name>.c`, then
   `python scripts/try_function.py trials/usa-v2/<Name>.c --address <addr> --size <n> --mask-relocs --flags "-O2 -G0 -ffunction-sections"`.
   Iterate the C shape and try `-G8`. Record only a full `MATCH` with `--record`, and put near misses in `trials/usa-v2/README.md`.
5. `python scripts/v2_report.py report --output build/decomp/report.json`, `python scripts/legal_check.py`, the unit tests, then a
   detailed commit and a draft PR per [PR-DESCRIPTIONS.md](PR-DESCRIPTIONS.md). Matches are candidates: say so; add no credit claim.

Never copy code from GPL projects (Going Native) into the tree; use them for names and ideas only.

## Read only the current entry points

1. Read `AGENTS.md`, then this page and the relevant section of
   [CAMPAIGN-WORKFLOW.md](CAMPAIGN-WORKFLOW.md).
2. If present, read `.local/ENVIRONMENT.md`. This ignored file supplies a pointer
   to the machine's private tool paths and compact current resumption. Keep
   those details private. On a fresh machine, use `scripts/doctor.py` and
   [START-HERE.md](START-HERE.md) to establish the required environment.
3. Fetch the intended remote, check the branch and local changes, and preserve
   unpublished work. Read current proof metadata instead of repeating an
   unchanged reconstruction merely to recover its count.
4. Run `campaign.py status`, `queue` and the selected `packet` using the private
   runtime binding. Choose the current task and its explicit reopening condition.
   Do not restart parked source permutations or historical jobs.
5. Use [shared reservations](CONTRIBUTOR-RESERVATIONS.md) before starting the
   selected small lot, and inspect the [nonmatching shelf](../nonmatching/README.md)
   for retained work. Fresh ownership checks precede compiler trials; an expired
   or uncertain claim stops admission. Reservation is not matching evidence.

Use the [official campaign tools](CAMPAIGN-TOOLS.md) to inspect a recorded trial
with `campaign.py diff` and finalize a completed validated batch with
`campaign.py finalize`. Neither command starts a matching search or authorizes
publication to another repository.

Read compiler, native-overlay and source-layout documentation when a concrete
technical question requires it. Archive files are evidence, not startup instructions.
When a task concerns shared copies, use the
[normalized family workflow](NORMALIZED-FAMILY-WORKFLOW.md) for candidate discovery
and reviewed binding controls. It retains exact acceptance and the one register;
its signatures never reopen a parked source trial or add matching credit.
Verify a stale environment pointer and update its private source as soon as it
changes; do not repeatedly rediscover an already documented tool.

## Pick a small function

With your own `baserom/SCUS_972.68` in place, rank the retail functions by size and
list unmatched ones (output stays local; only addresses and sizes are printed):

```bash
python scripts/function_size_rank.py --category small --status todo --ascending --limit 20
```

Boundaries are heuristic; confirm in Ghidra, then claim the lot in
[CONTRIBUTOR-RESERVATIONS.md](CONTRIBUTOR-RESERVATIONS.md). `scripts/legal_check.py`
runs in CI and rejects game bytes, assets or disassembly.

## Mission and ownership

An explicit continuation request starts matching work. The long-term goal is
complete byte-matching decompilation, followed by a native runtime and launcher.
Intermediate percentages are milestones. A status question, successful push or
failed target does not end an active campaign; preserve refusals and proceed to
another authorized target. An explicit stop, a completed requested objective or
a concrete external prerequisite can end the current run. A documentation-only
request does not resume decompilation.

Keep one owner writing the public checkout. Independent assistants may analyze
and review in read-only mode or private scratch areas. Save the compact private
resumption before long reads or interruption, including the current request,
authorizations, active operations and next action. The task register owns target
decisions; the resumption supplies operational continuity and evidence pointers.

## Publish a coherent lot

Follow the user's repository/branch authorization; project documentation does
not create authorization for other repositories or services. Qualify complete
symbols and current source units, then run all affected full-image gates with
frozen inputs. Retain partial results privately and add no credit for them.
Refresh source inventory, register views and the README bar when their inputs
change. Use detailed English commits, explicit staging and a normal push, then
verify the remote SHA and CI. Never force-push or include private runtime data.

For LP's authenticated primary-maintainer publication path, pass
`--owner-local` to `campaign.py finalize`. It keeps the complete matching and
freshness gates while selecting the bounded report/finalizer/policy tests and
running isolated test-case shards on multiple workers. The exhaustive default remains
available for protected queue validation; do not invoke it accidentally as a
routine owner-local prepublication test.

Integrate an eligible reviewed PR through the [merge queue](MERGE-QUEUE.md).
It checks the temporary combined commit against the latest `RAC2`; an older
topic base alone does not require another manual merge. If shared C, catalogue
or proof inputs conflict or become stale, follow the contributor branch-update
procedure and refresh the affected evidence before rejoining the queue. Do not
use an administrator override to skip queue or integrity checks.

An example short request:

> Continue matching decompilation on branch RAC2. Read AGENTS.md, docs/CONTINUE.md
> and the private environment pointer, then use the current register queue.
> Preserve previous refusals and push each validated lot with detailed English commits.
