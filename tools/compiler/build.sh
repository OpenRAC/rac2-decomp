#!/bin/bash
# The game's C compiler: GNU EE 2.9-ee-991111b (cpp, cc1, as) rebuilt from its public source.
#
#   tools/compiler/build.sh [OUT]        # default build/compiler/tools
#
# Run it on 32-bit-capable x86-64 Linux (gcc -m32), e.g. in the rac2-linux container
# (docs/build/building.md). It downloads the two inputs to build/downloads/ and checks them,
# applies the patches in tools/compiler/patches/ (Lombyte's sce-991111b stack, MIT, with its
# retired 0034 and its earlier 0020), the 0057/0058 compiler profiles, the 0059/0061/0062 assembler options and the
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
git apply --whitespace=nowarn "$HERE"/patches/0062-*.patch       # opt-in SN absolute `la sym+addend`
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
python3 $T/convert_frag_memmove.py gas/config/tc-mips.c
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
python3 $T/keep_float_pun_source.py gcc
python3 $T/no_extra_increment_givs.py gcc
python3 $T/sticky_volatile_sets.py gcc
python3 $T/caller_reg_order.py gcc
python3 $T/delay_no_split_hi.py gcc
python3 $T/gcse_hash_111.py gcc
python3 $T/sched_store_offset.py gcc
python3 $T/sched_stack_offset.py gcc
python3 $T/allocno_live_length.py gcc
sha256sum --check --quiet <<'SUMS'
a7436602ef9e063c0eafef9888797527ea3fd6e2d35b041d3fed46fcb457f504  gcc/config/mips/mips.c
e25f1a54bfdcc6c96e1c8ba9c9b977f15738ca8554393920e6af33c2d3a3f7bc  gcc/config/mips/mips.h
790a54f4772853284ab43a7afc9f592913da8f012b46d43abf5f2a3660467eef  gcc/config/mips/mips.md
ac510ce81929bc41707be97fd43a1e23ce62815990e1cac0ee7d8b416b71e70b  gcc/toplev.c
4b210daa9030021109b5e28d88d9ef9f6cf879c09659c8586d7db9053f27438c  gcc/haifa-sched.c
7b58c94fbad9767bc95c7f444f1bb31a4bc1d557e87787fa6921c59031412a67  gcc/reorg.c
5f27c022987d2bf2330149f896c76787a08036afed6f3041b49b77c0cd99e822  gcc/flags.h
28391f37355e5a0324ac19a9451f8f0dfa42e8e9f25b0157939388924d35f632  gcc/gcse.c
efc2260dd9c22f76d0d343ae14c313833755995ebda0ceab098f99e009d3afe2  gcc/flow.c
3535b59f5a754e44fb67989b1c30ad8f8f4fab6c30f12ef4dff287f527a82306  gas/config/tc-mips.c
6d4c688bdf8517a1da1b35a04bb1e3b6137093a6224b3ed52666581e3a7bd557  gcc/reload1.c
94489f80e8769d277c3cfd7c73a3d5ee3f8ce0af790f61ef3c575b593b3b4099  gcc/loop.c
d210a06544c16ce97a326b878527df1ea6730074ce8507a55830615df2820242  gcc/cse.c
734dc911b2b3764dc532eb95e3ddc886a94f6c9289a9686080db5e99d2221cd8  gcc/resource.c
23fccc683e52141c78256e75795be2b6573cc2be5683247c86379d416f213729  gcc/expmed.c
60cc098fdef5da1d5d0597bd624c1b2d56661b39e3ffaca628dcd32bedca7f18  gcc/global.c
cf87807db5f932724aaf0433323592a5eaa4eccfe58936ca5e3d3d395ca90e45  gcc/alias.c
25c4bd0e51fcdbeb9d53ab1092adab542d9833576391c83da7f3fb53908fbb86  gcc/combine.c
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
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_keep_float_pun_source.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_no_extra_increment_givs.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sticky_volatile_sets.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_caller_reg_order.py"
python3 "$ROOT/tests/test_qcopy_rtl.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_dli_masks.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_hazard_labels.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_block_move_loop.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_block_move_quad.py"
echo "compiler in $OUT"
