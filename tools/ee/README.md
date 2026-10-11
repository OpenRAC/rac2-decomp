# tools/ee (imported helpers, not a build route)

These scripts were imported from Going Native / RC2-Going-Decompiled as reference material. They do **not**
replace the canonical gates in `scripts/` (`build.py`, `campaign.py`, the pinned byte checks) and are not a
supported way to build or prove anything in this repository.

Known limitations:

- `ps2eeas_dli.awk` is called by `asm_unit.sh` with `-v sites=` / `-v count=1`, which its own file-ordering
  logic does not read, so it prints nothing and `asm_unit.sh` rejects the unit.
- `build.sh` now exits non-zero when the rebuilt image differs, but it was written for another layout
  (modern GNU binutils, a different container) and is untested against this repository's targets.
- Nothing here is qualified against the campaign compiler profile.

Do not present these helpers as a build route until they are fixed and qualified.
These imported files retain their upstream GPL-2.0 licence in [LICENSE](LICENSE);
they are not relicensed under the repository root MIT notice. See [CREDITS.md](../../CREDITS.md).
