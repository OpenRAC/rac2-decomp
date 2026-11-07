#!/bin/bash
# The game's C compiler: GNU EE 2.9-ee-991111b (cpp, cc1, as) rebuilt from its public source.
#
#   tools/compiler/build.sh [OUT]        # default build/compiler/tools
#
# Run it on 32-bit-capable x86-64 Linux (gcc -m32), e.g. in the rac2-linux container
# (docs/BUILDING.md). It downloads the two inputs to build/downloads/ and checks them,
# applies the patches in tools/compiler/patches/ (Lombyte's sce-991111b stack, MIT, with its
# retired 0034 and its earlier 0020), the 0057/0058 compiler profiles, the 0059/0061 assembler options and the
# transformers in tools/compiler/transformers/,
# refuses to build unless the patched sources hash as listed below, and builds.
#
# The binaries' hashes depend on the build host; the sources' do not. A compiler from these
# sources compiles every matched function in src/ to the retail bytes (tools/build.py).
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
HERE=$ROOT/tools/compiler
OUT=$(mkdir -p "${1:-$ROOT/build/compiler/tools}" && cd "${1:-$ROOT/build/compiler/tools}" && pwd)
DL=$ROOT/build/downloads
W=${WORK:-/tmp/rac2-compiler}
J=$(nproc)
mkdir -p "$DL" "$W"

fetch() {  # fetch FILE SHA256 URL
  [ -f "$DL/$1" ] || curl -fL --retry 3 -o "$DL/$1" "$3"
  echo "$2  $DL/$1" | sha256sum --check --quiet
}
fetch gnu-ee-binutils-gcc-1.1.tar.gz 1f518043e252d6eda726386971d52eda26541ab936ea73a9783d73712b595f92 \
  "https://web.archive.org/web/20060518234647id_/http://ps2dev.sourceforge.net:80/downloads/ee/gnu-ee-binutils-gcc-1.1.tar.gz"
fetch bison-1.28.tar.gz c5d3e4858e17cb440cee9de7837f07277bcfb03507e9d2f0c506cab5efe36c3a \
  https://ftp.gnu.org/gnu/bison/bison-1.28.tar.gz

# The source tree.
rm -rf "$W/src" && tar xzf "$DL/gnu-ee-binutils-gcc-1.1.tar.gz" -C "$W" && mv "$W/gnu-ee-binutils-gcc" "$W/src"
cd "$W/src"
export GIT_CEILING_DIRECTORIES=$W
for p in 0000 0001 0015 0016 0019 0020 0021 0022 0025 0026 0027 0028 0029 0030 0031 0032 0033 0034 \
         0036 0037 0044 0045 0046 0047 0048 0049 0050 0051 0052 0053 0054 0055 0056 0057; do
  git apply --whitespace=nowarn "$HERE"/patches/$p-*.patch
done
patch -R -p1 -s < "$HERE"/patches/0001-r5900-quad-saves.patch   # the retail saves in 8-byte slots
git apply --whitespace=nowarn "$HERE"/patches/0058-*.patch       # the opt-in -mastra-quad-saves switch
git apply --whitespace=nowarn "$HERE"/patches/0059-*.patch       # per-object sign-bit seed selection
git apply --whitespace=nowarn "$HERE"/patches/0060-*.patch       # leading-ones dli: lui-anchored first field
git apply --whitespace=nowarn "$HERE"/patches/0061-*.patch       # opt-in SN positive unsigned32-mask seed
T=$HERE/transformers
python3 $T/neutralise_timode_anchor.py gcc/config/mips/mips.c
python3 $T/enable_loop_padding.py gcc/config/mips/mips.h
python3 $T/ti_one_gpr.py gcc/config/mips/mips.h
python3 $T/count_trap_length.py gcc/config/mips/mips.c
python3 $T/count_block_move_length.py gcc/config/mips/mips.c
python3 $T/block_move_quad.py gcc/config/mips/mips.c
python3 $T/ascending_save_order.py gcc/config/mips/mips.c
python3 $T/reorder_save_blocks.py gcc/config/mips/mips.c
python3 $T/u4_mtc1_helper.py gas/config/tc-mips.c
python3 $T/restrict_mtc1_exemption.py gas/config/tc-mips.c
python3 $T/fold_zero_ti_store.py gcc
python3 $T/fold_zero_ti_return_value.py gcc
python3 $T/u3_frame_order_on.py gcc/config/mips/mips.c
python3 $T/disable_frame_order_default.py gcc/config/mips/mips.c
python3 $T/pad_div_erratum_nops.py gas/config/tc-mips.c
python3 $T/neutralise_div_dslot.py gcc
python3 $T/pad_div_erratum_branch.py gas/config/tc-mips.c >/dev/null
python3 $T/r5900_mfc1_interlock.py gas/config/tc-mips.c
python3 $T/swap_branch_slots.py gas/config/tc-mips.c
python3 $T/inline_li_d.py gas/config/tc-mips.c
python3 $T/tidy_condjump_fallthru.py gcc/flow.c
python3 $T/zero_ti_store_barrier.py gcc/haifa-sched.c
python3 $T/gcse_unsplit_edges.py gcc/gcse.c
python3 $T/keep_block_order.py gcc/flow.c
python3 $T/qcopy_pattern.py gcc
python3 $T/hazard_labels.py .
python3 $T/qcopy_barrier.py gcc
python3 $T/no_annulled_wide_stores.py gcc/reorg.c
python3 $T/zero_ti_por.py gcc
python3 $T/no_null_pointer_checks.py gcc
python3 $T/gcse_store_kills_loads.py gcc/gcse.c
python3 $T/reload_reg_used_guard.py gcc/reload1.c
python3 $T/trap_delay_barrier.py gcc/reorg.c
python3 $T/trap_redundant_barrier.py gcc/reorg.c
python3 $T/count_asm_words.py gcc/config/mips/mips.c
python3 $T/no_recombine_givs.py gcc/loop.c
python3 $T/narrow_saves_below.py gcc
python3 $T/keep_block_zero_copy.py gcc
python3 $T/sticky_volatile_refs.py gcc
python3 $T/frame_pointer_liveness.py gcc
python3 $T/wide_saves_below.py gcc
python3 $T/mult_add_no_flatten.py gcc
python3 $T/no_static_chain_base.py gcc
sha256sum --check --quiet <<'SUMS'
c949997ebc1ed001fc7d905723c8e9348f5c364db2b61bc4e84b9729b6a67f07  gcc/config/mips/mips.c
e25f1a54bfdcc6c96e1c8ba9c9b977f15738ca8554393920e6af33c2d3a3f7bc  gcc/config/mips/mips.h
790a54f4772853284ab43a7afc9f592913da8f012b46d43abf5f2a3660467eef  gcc/config/mips/mips.md
a4a8ff5c6251d11a326cb57ff904eb625cb430179681988ebaf9a6a943fc2a06  gcc/toplev.c
fa211f12b39de727c033f57a16ab627572547901d9cf8d2a7aa2e5dd77949e9e  gcc/haifa-sched.c
656c2b9546b5c38d96cfe25b02620cce02b625f5637ecad6386f0a4d89f3e0fe  gcc/reorg.c
2dbb0a9b85c135e82f7cbca95c85e5e0429f0fd5428fb6f092ad1cd99b4a3e12  gcc/flags.h
feb3bd29dd08e1d1b1db78861d580c55f161a55e63cedd368e873c48bc36982d  gcc/gcse.c
efc2260dd9c22f76d0d343ae14c313833755995ebda0ceab098f99e009d3afe2  gcc/flow.c
17c1a41578b92c102dea8c189e1e7372e637662e690d5226c87a4122a32d1225  gas/config/tc-mips.c
6d4c688bdf8517a1da1b35a04bb1e3b6137093a6224b3ed52666581e3a7bd557  gcc/reload1.c
2f6ffa23d379d620ec38db4e527b2cbd5583865195cd8b364aa2c1ce07433faf  gcc/loop.c
a2dd997196a573b94aef15338115cfdb1c2a7e29f3dc1857597695f1a0bf9b20  gcc/cse.c
8e2768736759358567dc26fe0379d8fbe8b6f5bc3d9dc35adeb573cb99eac63f  gcc/resource.c
23fccc683e52141c78256e75795be2b6573cc2be5683247c86379d416f213729  gcc/expmed.c
cf87807db5f932724aaf0433323592a5eaa4eccfe58936ca5e3d3d395ca90e45  gcc/alias.c
SUMS

# bison 1.28: the 1999 grammars need its skeleton.
if [ ! -x "$W/bison/bin/bison" ]; then
  rm -rf "$W/bison-1.28" && tar xzf "$DL/bison-1.28.tar.gz" -C "$W"
  (cd "$W/bison-1.28" && CC="gcc -std=gnu89" CFLAGS="-O2 -fcommon" ./configure --prefix="$W/bison" \
     && make -j$J && make install) > "$W/bison.log" 2>&1
fi
export BISON_SIMPLE=$W/bison/share/bison.simple BISON_HAIRY=$W/bison/share/bison.hairy

F="-O2 -fno-strict-aliasing -fcommon -std=gnu89 -D_GNU_SOURCE"
rm -rf "$W/build" && mkdir "$W/build" && cd "$W/build"
printf 'obstack.o gcc.o mkstemp.o: override CFLAGS = -g\n' > host-flags.mk
export CC="gcc -m32" CFLAGS="$F"
{
  bash "$W/src/configure" --target=mips64r5900-sf-elf --host=i686-linux-gnu --build=i686-linux-gnu \
       --disable-nls --enable-languages=c --without-headers --prefix="$W/install"
  make -j$J all-libiberty
  # The 1999 Makefile lacks flow.o -> insn-flags.h: generate the headers first.
  make -C gcc -f Makefile -f "$W/build/host-flags.mk" LANGUAGES=c "CC=gcc -m32" "CFLAGS=$F" \
       BISON="$W/bison/bin/bison" insn-flags.h insn-codes.h insn-config.h
  make -C gcc -f Makefile -f "$W/build/host-flags.mk" -j$J LANGUAGES=c "CC=gcc -m32" "CFLAGS=$F" \
       BISON="$W/bison/bin/bison" cc1 cpp xgcc
  make -j$J all-gas
} > "$W/build.log" 2>&1 || { tail -30 "$W/build.log"; exit 1; }
cp gcc/cc1 gcc/cpp "$OUT/" && cp gas/as-new "$OUT/as"
# the compiler's own headers (stdarg.h and the va-*.h it includes), as the
# SDK recipe installs them: an authored unit that includes <stdarg.h>
# (a varargs body) needs them on the preprocessor's path.
mkdir -p "$OUT/include" && cp "$W/src/gcc/ginclude/"*.h "$OUT/include/"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_zero_ti_store.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_gcse_unsplit_edges.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_keep_block_order.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_gcse_store_kills_loads.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_trap_delay_barrier.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_trap_redundant_barrier.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_swap_branch_slots.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_div_label_after_call.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_div_gp_fragments.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_count_asm_words.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_symbolic_loop_words.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_no_recombine_givs.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_qcopy.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_qcopy_barrier.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_no_annulled_wide_stores.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_zero_ti_por.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_ti_one_gpr.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_mtc1_exemption.py"
RAC2_GCC_SOURCE="$W/src/gcc/reload1.c" RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_reload_reg_used_guard.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_no_null_pointer_checks.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_narrow_saves_below.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_keep_block_zero_copy.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sticky_volatile_refs.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_frame_pointer_liveness.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_wide_saves_below.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_mult_add_no_flatten.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_no_static_chain_base.py"
python3 "$ROOT/tests/test_qcopy_rtl.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_dli_masks.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_hazard_labels.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_block_move_loop.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_block_move_quad.py"
echo "compiler in $OUT"
