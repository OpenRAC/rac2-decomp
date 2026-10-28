# Functional C

C that behaves like the retail function without matching its bytes. It is for
the native port only: the matching build never reads it, `src/` never holds it,
and the progress report never counts it.

- One file per function (or per small group), named after the function.
- List each in [`../functional.tsv`](../functional.tsv) as `name<TAB>file`.
  `tests/check_repository.py` requires every listed function to still be
  `INCLUDE_ASM` in `src/` and its file to exist here.
- When a function matches, put the match in `src/` and delete its row and file.
- OpenRAC reads the table through `port/game/rac2-ntsc/hostgen.json`
  ("candidates"); how to write and verify this C is in OpenRAC's
  `docs/port/BACKFILL.md`.
