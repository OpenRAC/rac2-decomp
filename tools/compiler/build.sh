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
python3 $T/sched_arg_copy.py gcc
python3 $T/keep_user_copies.py gcc
python3 $T/la_funcref_weight.py gcc
python3 $T/fix_scratch_reuse.py gcc
python3 $T/sched_defer_const.py gcc
python3 $T/sched_global_yield.py gcc
python3 $T/sched_store_clobbered_first.py gcc
python3 $T/sched_clear_holds_store.py gcc
python3 $T/sched_call_addr_float.py gcc
python3 $T/la_float_vars_last.py gcc
python3 $T/reload_rotation.py gcc
python3 $T/cse_arg_rules.py gcc
python3 $T/sched2_barrier_hold.py gcc
python3 $T/l06_rules.py gcc
python3 $T/d1e8_rules.py gcc
python3 $T/d4948_rules.py gcc
python3 $T/l00_rules.py gcc
python3 $T/b44c0_rules.py gcc
python3 $T/d59c8_rules.py gcc
python3 $T/d78f0_rules.py gcc
python3 $T/la_fp_const_first.py gcc
python3 $T/gcse_hash_fp_112.py gcc
python3 $T/l04_ad28_rules.py gcc
python3 $T/cea0_rules.py gcc
python3 $T/cc6b0_rules.py gcc
python3 $T/l04_17308_rules.py gcc
python3 $T/l17_rules.py gcc
python3 $T/l05_42b2c0_rules.py gcc
python3 $T/gcse_hash_fp_59.py gcc
python3 $T/l11_dce0_rules.py gcc
python3 $T/sched2_order.py gcc
python3 $T/cd670_rules.py gcc
sha256sum --check --quiet <<'SUMS'
56ccede033f0d7041aeb573a89e79aeee2d635a18987403bee0a1e2d0370a44a  gcc/config/mips/mips.c
e8b9e0234097ac5c9865812717b2b666c90f535cb114ceb5c579e911e78c972a  gcc/config/mips/mips.h
790a54f4772853284ab43a7afc9f592913da8f012b46d43abf5f2a3660467eef  gcc/config/mips/mips.md
c01e6656316f7451e096fecfa70a06efa75cf01ec2225350b2800e045d111697  gcc/toplev.c
d187684f1c2dfcfcb168bd808752ab786b590ea1810daaadf53fe4f8383cfa25  gcc/haifa-sched.c
85ce08b12f1222054a9e7e009314ed0aafe48f8612af7ba0c9d2f878087d8ee6  gcc/reorg.c
b586b9b35f21061280f5d3a3d2c2c947de4d748090eeb73abb6e8826acaffbd0  gcc/flags.h
d141934f9b0181c58b79b05eba17074d7e773b06749e541c35ce43dc759bc114  gcc/gcse.c
ae0cc11c65f6ec520668b917bb5ef5052d52ee93964e8f06b5383be6b3e82a39  gcc/flow.c
72941ee59459c038850f9c330c32c623d1290fad4a54444f9dfd3cb008dfdb0c  gcc/emit-rtl.c
36132244008bfdfa284995132a7c33e522682486356cdaa38c99f2dca50b41be  gcc/jump.c
3535b59f5a754e44fb67989b1c30ad8f8f4fab6c30f12ef4dff287f527a82306  gas/config/tc-mips.c
c7286dea5cf785e9f6317f46d124692c3b6c405c0da6372fd6c5df5a7d6cb1f4  gcc/reload1.c
fef520171c0efbdd9066fed9caf5485df7821796eb73fdb9783e6fdbecdd44ab  gcc/loop.c
13587efab4dd4ff3a22bebb6ffa975a86fd1a46b9260e14786c93413cb0de1a6  gcc/cse.c
734dc911b2b3764dc532eb95e3ddc886a94f6c9289a9686080db5e99d2221cd8  gcc/resource.c
23fccc683e52141c78256e75795be2b6573cc2be5683247c86379d416f213729  gcc/expmed.c
06f9cb7a772a5af1b5e7c883030505ff623ef499ac76fb4ab8c143b1558e8ea1  gcc/global.c
c64b9016b3dd89b525f5fd0810acd3f7dcbde43b3d9d3fe4657ee486f36f0cbe  gcc/alias.c
25f59a6b97634b7d678db1939680e5c1d3a1675382a1d268c4ec4f7ce2b7b1a2  gcc/combine.c
6164df9c2636274d06479453593f16aa01454ae99c3136179053d2adaa650bc6  gcc/local-alloc.c
d7fca815635791e78130a1ab2f64a95139589f1c4b4862ec83facd1a0607aa23  gcc/final.c
a0ad1bf96073c9b6395a026769e17f4bdb4ce7b13edaa8d5666597edb2b60819  gcc/stmt.c
53b72984e05a65d7ad76844db9b1457ba8791a9d7959f32b9b375497e4e05a7b  gcc/regmove.c
0f87c4ba3a2fffe6ddb2c93c875b839354fe16441e6de3733b335ce7d96bc881  gcc/c-decl.c
d0b1373e522732ce4e20436d4424e1d12b716be14d9ef06155d66dd295635935  gcc/c-lex.c
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
  # The 1999 Makefile lacks flow.o -> insn-flags.h (and gcse.o -> tree-check.h, which
  # cea0_rules.py's tree.h include needs): generate the headers first.
  make -C gcc -f Makefile -f "$W/build/host-flags.mk" LANGUAGES=c "CC=gcc -m32" "CFLAGS=$F" \
       BISON="$W/bison/bin/bison" insn-flags.h insn-codes.h insn-config.h tree-check.h
  make -C gcc -f Makefile -f "$W/build/host-flags.mk" -j$J LANGUAGES=c "CC=gcc -m32" "CFLAGS=$F" \
       BISON="$W/bison/bin/bison" cc1 cpp xgcc
  make -j$J all-gas
} > "$W/build.log" 2>&1 || { tail -30 "$W/build.log"; exit 1; }
# A failed cc1 build must not leave the previous binaries in place unnoticed.
cp gcc/cc1 gcc/cpp "$OUT/" && cp gas/as-new "$OUT/as" || { tail -30 "$W/build.log"; exit 1; }
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
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_keep_user_copies.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_no_extra_increment_givs.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sticky_volatile_sets.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_caller_reg_order.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_la_funcref_weight.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_fix_scratch_reuse.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sched_defer_const.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sched_global_yield.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sched_store_clobbered_first.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sched_clear_holds_store.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sched_call_addr_float.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_la_float_vars_last.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_reload_rotation.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_cse_arg_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sched2_barrier_hold.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_l06_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_d1e8_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_d4948_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_l00_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_b44c0_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_d59c8_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_d78f0_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_la_fp_const_first.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_gcse_hash_fp_112.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_l04_ad28_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_cea0_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_cc6b0_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_l04_17308_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_l17_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_l05_42b2c0_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_gcse_hash_fp_59.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_l11_dce0_rules.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_sched2_order.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_cd670_rules.py"
python3 "$ROOT/tests/test_qcopy_rtl.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_dli_masks.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_hazard_labels.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_block_move_loop.py"
RAC2_COMPILER_ROOT="$OUT" python3 "$ROOT/tests/test_block_move_quad.py"
echo "compiler in $OUT"
