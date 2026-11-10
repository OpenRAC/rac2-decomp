# decomp-permuter

For near misses whose instructions are right but whose registers or order are not, OpenRAC's
[`tools/permuter`](https://github.com/OpenRAC/OpenRAC/tree/master/tools/permuter) runs [decomp-permuter](https://github.com/simonlindholm/decomp-permuter)
for this project. Its `rac2/ntsc` profile compiles each candidate with the game's own C chain (the
SN `cpp`, `cc1` and `as` of `build/compiler/tools`, in a container of the Linux image, with the
file's flags from `tools/build.py`) and counts a score 0 only when `tools/check.py` says every place
matches. From an OpenRAC checkout:

```sh
OPENRAC_SOURCE_RAC2_NTSC=<this checkout> python3 tools/permuter run rac2/ntsc func_X --c nonmatching/.../func_X.c
```

Results are hints: rewrite the useful change by hand and check it with `tools/check.py` and the
build, as for any match. Its README lists what is not covered yet (files built with the SDK
compiler or with `-Wa,` options).
