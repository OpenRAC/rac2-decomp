# Contributing

## Matching a function

1. Set up the build once ([docs/build/building.md](docs/build/building.md)) and run `tools/build.py all`.
2. Pick a function from `config/boot/functions.tsv` or `config/levels/functions.tsv`. A level
   function's row lists all its places; one definition serves them all.
3. Find its `INCLUDE_ASM` line in `src/` (`grep -rn func_XXXXXXXX src`) and replace it with
   its C, in place. Name what it uses by what it is: other functions by their catalogue names,
   the boot's resident data `D_XXXXXXXX`, a level's data `D_LNN_XXXXXXXX` (its address in level
   NN). Never write a level address as a number: a level function is linked into every level
   that has it, each with its own addresses.
4. `tools/check.py func_XXXXXXXX` compiles its file and tries it at each of its places in a few
   seconds; `--diff` shows the instructions beside the retail ones.
5. `tools/build.py` the programs that have it (`boot`, `level 4`, or `all`). It places the
   function everywhere the catalogue says and prints `OK` per program, or why a place does
   not match. A function counts once its C links into a program that equals the retail one.
6. Leave `progress/report.json` alone: a maintainer regenerates it on
   `master` after merging, so pull requests do not conflict on them (AGENTS.md, "The progress report").

Close but not matching: put it in `nonmatching/` with a line in its README.

## Tracking

- **Reservations.** Before you start, reserve the functions, files or levels you will work on
  in [issue #152](https://github.com/OpenRAC/rac2-decomp/issues/152): one comment per
  contributor, edited in place, at most 500 unfinished functions. Read the other comments
  first and do not overlap them. Release what you finish or drop. [AGENTS.md](AGENTS.md) has
  the exact rules.
- **What is left.** `python3 tools/todo.py` lists the functions still to match by size
  (`--min`, `--max`, `--kind boot|shared|level`, `--limit`). Before you start one, look for it
  in [`nonmatching/README.md`](nonmatching/README.md): an earlier near miss and its notes may
  be there.
- **Near misses.** C that does not match goes into `nonmatching/` with a row in its README,
  and the function keeps its `INCLUDE_ASM` marker in `src/`.
- **The progress report.** `progress/report.json` is generated. Only a
  maintainer refreshes it, on `master`, after merging. Leave it out of your pull request;
  if you ran `tools/progress.py`, undo it with
  `git checkout origin/master -- progress/report.json`.
  `python3 tools/progress.py --check` passes while the report is behind and prints how many
  new functions wait for the refresh.
- **Before a pull request**, all must pass:
  ```sh
  python3 tools/build.py all --strict          # and with --version pal, --version us2
  python3 -m unittest discover -s tests
  python3 tests/check_repository.py
  python3 tools/progress.py --check
  ```
  A function that matches in v1.01 but not in another release stays assembly there:
  `tools/carry.py --version pal --demote` ([`docs/build/versions.md`](docs/build/versions.md)).

## Improving shared knowledge

Every contributor can edit any entry in [`docs/contributing/matching-blockers.md`](docs/contributing/matching-blockers.md)
using a fork/topic branch and a normal PR, even when another person wrote the original note.
Maintainers review the merge; they are not the sole authors. A coding AI edits this Markdown
file in the same checkout, with no separate wiki clone or browser automation.

Read existing findings before another trial. Add new measurements or correct a superseded
conclusion in the relevant entry, with the profile, applicable release, result, remaining
difference and PR/commit link. Preserve useful dated history and distinguish local candidates
from merged fixes. Discuss uncertain findings in the relevant code or documentation PR;
issue #157 is retired and kept only as historical provenance. Reservations stay in issue #152.

## Sending your work

Branch from `master`, commit, push the branch and open a pull request to `master`. In the pull
request, give the commands you ran and what they printed (`tools/build.py all --strict`,
`tools/progress.py`, the tests). CI runs the tests and the repository check; a maintainer merges.
Never push to `master` and never force-push a shared branch. AGENTS.md has the full rules and docs/agents/agent-workflow.md says which model takes which functions, for
people as much as for agents.

Use `--strict` for the final build before pushing: it fails if any C function falls back
to assembly, even when the resulting program equals retail. Ordinary builds keep that
fallback available while experimenting. Compiler and assembler changes automatically
invalidate the affected cached C objects.

## Rules

- **Sources.** Use the retail programs of your own disc, SDK library *binaries*, open-source code
  under its licence, public decompilations and tools, and public hardware documentation. Never
  use Sony's SDK source, samples or headers, or leaked or NDA material of any kind (leaked
  builds, symbol dumps from them, leaked source), not even as a reference. Publicly distributed
  prototype discs may be cited, naming the build, never as the evidence for a match. OpenRAC's
  docs/policy/SOURCING.md is the full policy.
- Follow RAC1's source practices: meaningful C may call the reviewed shared EE helpers
  `qcopy`, `qcopy_nc` and `qzero` in `include/common.h`. Public runtime-library target
  primitives may retain their original assembly with upstream provenance and licence.
  No ad-hoc instruction sequences in game functions, register pins, artificial barriers,
  fake dependencies or false interfaces. Flags are per file (`config/cflags.txt`), never
  per function. These exceptions still require exact linked validation; see `AGENTS.md`.
- The build may model measured retail assembler/linker behavior, following RAC1:
  macro expansion, hardware padding and data-section placement need independent
  controls and strict linked validation. Never patch compiler-authored operations,
  values or register assignments to manufacture a match.
- Never commit game data, extracted assembly, disc images or proprietary tools: `baserom/`,
  `toolchain/` and `build/` stay local.
- Conventional commit subjects (`feat(src):`, `fix(tools):`, `docs:` ...), with a body that
  says what changed and how it was checked.
- `python -m unittest discover -s tests`, `python tests/check_repository.py` and
  `python tools/progress.py --check` pass (CI runs
  them; it cannot build, having no game data).
