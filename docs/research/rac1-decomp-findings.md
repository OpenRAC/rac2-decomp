# Findings from rac1-decomp

[rac1-decomp](https://github.com/OpenRAC/rac1-decomp) is a matching decompilation
of the first game, PAL v2.00 `SCES_509.16`, at 22.6% of its code (2,974 of 5,109
functions) on 5 October 2026. Several of its measured results concern compiler,
library and SDK code that the engine's later games share. This page summarises
them for RAC2 with links to the original records.

Everything below was measured on **RAC1's** executable. None of it is a RAC2
match, adds RAC2 credit or relaxes this repository's acceptance rules. A RAC2
use still needs its own catalogue, fresh objects and complete loaded-byte gates.

## 1. Library code: compile the real source first

RAC1's retail `core_text` links GCC's runtime library. rac1-decomp rebuilds it
from GCC's own sources rather than decompiling it
([`src/libgcc/README.md`](https://github.com/OpenRAC/rac1-decomp/blob/cb22f0b0d3a171d1fd4b6851b86fe214a22c9822/src/libgcc/README.md),
[`docs/DECOMP_PROGRESS.md`](https://github.com/OpenRAC/rac1-decomp/blob/cb22f0b0d3a171d1fd4b6851b86fe214a22c9822/docs/DECOMP_PROGRESS.md),
"libgcc is 2.9-ee").

- **Compiler.** Sony's **gcc 2.9-ee-991111**, the lineage of this repository's
  current GNU EE profile, not the SN 2.95.3 that built RAC1's game code.
- **Sources.** At commit `cb22f0b0d3a171d1fd4b6851b86fe214a22c9822`,
  `libgcc2.c` and `longlong.h` come from GCC trunk `31cf01446d`
  (1999-09-09). GCC 2.95.3's `fp-bit.c` has two marked changes: shared
  `__thenan_df` storage and the `NO_DENORMALS` backport from trunk
  `2672543458` (2000-03-16). The build also selects
  `FLOAT_BIT_ORDER_MISMATCH` and the GOFAST names.
- **Result.** fp-bit (`_fpadd_parts`, `__adddf3`, `__subdf3`, `__muldf3`,
  `__divdf3`, `__fpcmp_parts_d`, `__cmpdf2`, `__floatsidf`, `__fixdfsi`, ...)
  and libgcc2's `__divdi3`, `__muldi3`, `__floatdidf` and `__fixunsdfdi` match
  RAC1 byte for byte, relocations included, with no post-processing. Across
  0x11DFE8-0x1206A0, 2,478 words compare equal.
  That whole-image total includes the remaining assembly stubs and linker
  fill; it is not a claim that every byte in the region comes from C.
- **Build through the driver, not `cc1`.** The driver passes the target
  predefines (`__mips__`, `__R5900__`, ...) from which `longlong.h` selects its
  MIPS multiply and divide primitives. Called through `cc1` directly,
  `__divdi3` came out 0x50 bytes too long.
- **One object per `L_*` module**, as in `libgcc.a`. Each object's 8-byte
  `.text` alignment reproduces retail's gaps between modules. Linker fill
  between some modules is `0xCDCDCDCD`, which splat had split out as tiny
  "functions". Each division module owns a static `__clz_tab`.
- **Still open in RAC1.** `__moddi3`, `__udivdi3` and `__umoddi3` remain
  assembly stubs. Retail reserves additional unused stack space: 0x20,
  0x10 and 0x20 bytes respectively. The source and flag trials recorded
  upstream did not resolve those frame differences.
- **How it was found.** A family of near-misses shared one "known residual".
  Compiling one member with every available EE `cc1` showed that only 2.9-ee
  produced retail's prologue. A family-wide residual can point to a different
  compiler or to library code rather than a missing source lever.

In RAC2, the stopped boot helpers `FUN_00123400` (144 bytes) and
`FUN_001234F0` (64 bytes) follow the integrated `FUN_00123268` (44 bytes) with
the sizes and order of RAC1's `__unpack_f`, `fptodp` and `__make_dp`. That is a
correspondence hypothesis, proposed separately as campaign evidence. RAC2 has
not established whether its boot links the same modules, revision or flags.

## 2. SDK archives as a source of names

The EE SDK archives (`libmc.a`, `libdbc.a`, `libpad2.a`, `libmpeg.a`, ...)
matched RAC1 retail members byte for byte with relocations masked. Their
`.symtab`/`.mdebug` give real function and static-data names, for example
`sceMcInit`, `sceMcOpen`, `sceMcRead` and `sceMcSync` in `libmc.o`. In this
repository such names are naming research only and add no credit.
rac1-decomp took the archives from a community mirror of the SDK; RAC2's
toolchain policy does not accept unverified SDK sources, so any use needs an
archive whose provenance meets that policy.

## 3. Compiler behaviour measured on RAC1

These explain differences RAC2 has also recorded. RAC1's source and evidenced
assembler/linker compatibility methods are now permitted under `AGENTS.md`.
RAC2 currently uses qualified source-level compiler/assembler models and direct
object-section placement. A pass from another toolchain still needs local
evidence and independent controls; never rewrite compiler-authored operations
just to close an unexplained difference. The measurements below retain their
original date and toolchain scope.

- **Two SN GCC 2.95.3 sub-builds behave differently.** v1.14 (in the
  `sce_ps2_sdk_24` kit) lays out callee-saved slots like RAC1 retail; v1.36
  (`ee-gcc2953` in ProDG 3.01) uses a mirrored layout. No command-line flag
  changes either. This matches the `sd`/`sq` difference in
  [compiler-notes.md](../build/compiler-notes.md), which compared the ProDG 3.01 kit.
- **GCC 2.95.3 has no sibling-call optimisation**: `-foptimize-sibling-calls` is
  rejected and `-O3` does not help. RAC1's bare `j target` tail calls came from
  post-processing. Sony's 2.9-ee performs tail calls natively, also in eight
  RAC1 functions where retail did not.
- **Small data.** RAC1's game code uses `-G2`: float constants stay inline and
  small globals are reached through `$gp`. `-G0` never uses `$gp`; `-G4` and
  above pool floats into `.lit4`. Placement follows an extern's declared size.
- **Short-loop erratum.** SN's `ps2eeas` pads every backward branch whose loop
  is shorter than six instructions with nops. The 2.9-ee driver's own `as.exe`
  pads call-free short loops; the standalone GNU `ee-as` of the same version
  pads none. RAC2's [rac1-to-rac2.md](rac1-to-rac2.md) records the same
  hazard-nop behaviour for the ProDG 3.01 assembler.

## 4. Candidate-generation aids

rac1-decomp uses these to propose candidates. These observations do not
permit source permutations on parked RAC2 targets: the concrete reopening
evidence required by `AGENTS.md` and `docs/contributing/matching-blockers.md` still applies.

- **m2c with generated context** for a first C sketch. Its output is never
  matching as emitted and mis-decodes branch-likely conditions.
- **[decomp-permuter](https://github.com/simonlindholm/decomp-permuter)**
  ([`docs/PERMUTER.md`](https://github.com/OpenRAC/rac1-decomp/blob/cb22f0b0d3a171d1fd4b6851b86fe214a22c9822/docs/PERMUTER.md)).
  Effective on store-order and small register-allocation near-misses: one RAC1
  function reached an exact candidate at iteration 105, under two minutes, by
  reordering two stores. Less effective on control-flow shapes such as loop
  reversal or branch inversion. A hit is a lead, not a proof.
- **Exhaustive reordering** of a few marked statements (rac1's
  `tools/permute.py`) covers every ordering of up to about eight lines.

## 5. Names carried from RAC1 functions with equal fingerprints

Measured 2026-11-09 from the two catalogues alone, with no game data: this
repository's `config/levels/functions.tsv` at master `674fcc9ef` and
rac1-decomp's `config/overlays/functions.tsv` and `config/names.tsv` at
`f911d6e4b971`. Both catalogues fingerprint a function the same way: the hash of
its words with only the address fields masked (jump targets, address halves,
`$gp` offsets and large offsets on other registers). Equal fingerprints mean the
two functions are the same code apart from addresses. They do not prove that a
masked address reaches the same routine or datum, so each name below also needed
one of three supports.

105 functions took their RAC1 counterpart's name in `include/names.h`
(35 under "recovered", 70 under "descriptive", following the tier
rac1-decomp records for the name). A function was taken only when:

- it is longer than 16 bytes;
- its fingerprint belongs to one RAC2 function and to RAC1 functions that all
  carry one name, of tier `recovered` or `descriptive` (not `candidate`);
- it had no alias yet, and the name occurs nowhere else in `src/`, `include/`,
  `nonmatching/` or `ports/`, so the macro cannot rewrite another identifier;
- the name does not embed a RAC1 address; and
- one support holds:
  - **no address fields**: its matched C calls nothing and names no global, so
    nothing was masked and the code is identical word for word;
  - **neighbours in the same order**: at least two other fingerprint pairs lie
    within 0x1000 bytes of it in RAC2 with RAC1 counterparts at the same
    displacement, to within 0x400 bytes, so the link order agrees; or
  - **100 bytes or more** of equal code under a fingerprint unique in both games.

Left out: 154 functions whose fingerprint several RAC2 functions share (the RAC1
name cannot tell them apart), 29 of 16 bytes or less, 22 whose RAC1 name is
already an identifier here, 16 that already had an alias, 16 with none of the
three supports and 4 whose name embeds a RAC1 address. The boot catalogue has no
fingerprints, so functions listed only there were not compared. These are
aliases only: no function is renamed and no bytes change.

| RAC2 function | Bytes | RAC1 function | Name | RAC1 tier | Support |
| --- | ---: | --- | --- | --- | --- |
| `func_0026FEB8` | 56 | `func_001E9730` | `STUB_printf` | recovered | no address fields |
| `func_0027B948` | 120 | `func_001F3D00` | `ResetGsRegistersPr` | recovered | 100 bytes or more |
| `func_0027E920` | 260 | `func_L02_0020BF88` | `AppendDisplayListEntry` | descriptive | 100 bytes or more |
| `func_0027F128` | 80 | `func_001F65B0` | `measure_text_width` | descriptive | no address fields |
| `func_002802E0` | 56 | `func_001F7648` | `FontSetWindow` | recovered | no address fields |
| `func_00280A70` | 192 | `func_001F7DD8` | `lerp_clip_vertex` | descriptive | neighbours in the same order |
| `func_00280B30` | 96 | `func_001F7E98` | `closest_point_on_segment` | descriptive | neighbours in the same order |
| `func_00281154` | 128 | `func_001F84AC` | `writeSetupBlock` | recovered | neighbours in the same order |
| `func_002811D4` | 64 | `func_001F852C` | `writeGSHeader` | recovered | neighbours in the same order |
| `func_00281214` | 1532 | `func_001F856C` | `ScisAndRender` | recovered | neighbours in the same order |
| `func_00282BE0` | 40 | `func_001F9B20` | `is_vector_outside_clip` | descriptive | neighbours in the same order |
| `func_00282C10` | 32 | `func_001F9B50` | `square_root` | descriptive | neighbours in the same order |
| `func_00282C30` | 24 | `func_001F9B70` | `subtract_integer_with_clamp` | descriptive | neighbours in the same order |
| `func_00282CD8` | 24 | `func_L00_001FF240` | `add_vectors` | descriptive | neighbours in the same order |
| `func_00282D08` | 40 | `func_001F9C08` | `lerp_vector` | descriptive | neighbours in the same order |
| `func_00282D48` | 24 | `func_L00_001FF2C8` | `scale_vector_xyz_in_place` | descriptive | neighbours in the same order |
| `func_00282D60` | 24 | `func_001F9C48` | `scale_vector` | descriptive | neighbours in the same order |
| `func_00282D78` | 24 | `func_001F9C60` | `multiply_vector_components` | descriptive | neighbours in the same order |
| `func_00282D90` | 32 | `func_L00_001FF328` | `divide_vector_xyz` | descriptive | neighbours in the same order |
| `func_00282DB0` | 40 | `func_001F9C78` | `FastVecDot` | recovered | neighbours in the same order |
| `func_00282DD8` | 24 | `func_001F9CA0` | `FastVecCross` | recovered | neighbours in the same order |
| `func_00282DF0` | 48 | `func_001F9CB8` | `FastVecLength` | recovered | neighbours in the same order |
| `func_00282E48` | 56 | `func_001F9D10` | `fast_vec_dist` | descriptive | neighbours in the same order |
| `func_00282E80` | 48 | `func_001F9D48` | `vec_distance_xy` | descriptive | neighbours in the same order |
| `func_002830C0` | 48 | `func_001F9EE8` | `transform_vector` | descriptive | neighbours in the same order |
| `func_002830F0` | 24 | `func_001F9F18` | `FastVectorFromPackedChars` | recovered | neighbours in the same order |
| `func_00283108` | 40 | `func_001F9F30` | `FastVectorToPackedChars` | recovered | neighbours in the same order |
| `func_00283150` | 48 | `func_001F9F60` | `FastCountChars` | recovered | neighbours in the same order |
| `func_00283360` | 40 | `func_001FA168` | `set_identity_rotation_rows` | descriptive | neighbours in the same order |
| `func_00283388` | 48 | `func_001FA190` | `set_identity_matrix` | descriptive | neighbours in the same order |
| `func_002833B8` | 56 | `func_001FA1C0` | `set_scale_matrix` | descriptive | neighbours in the same order |
| `func_002833F0` | 32 | `func_001FA1F8` | `euler_rotation_basis` | descriptive | neighbours in the same order |
| `func_00283410` | 32 | `func_001FA218` | `euler_to_matrix` | descriptive | neighbours in the same order |
| `func_00283658` | 32 | `func_001FA460` | `copy_matrix_rotation` | descriptive | neighbours in the same order |
| `func_00283678` | 32 | `func_001FA480` | `copy_matrix3x4` | descriptive | neighbours in the same order |
| `func_00283698` | 80 | `func_001FA4A0` | `matrix_from_basis_rows` | descriptive | neighbours in the same order |
| `func_00283738` | 80 | `func_001FA4F0` | `multiply_matrix3x3` | descriptive | neighbours in the same order |
| `func_00283788` | 72 | `func_001FA540` | `multiply_matrix` | descriptive | neighbours in the same order |
| `func_002837D0` | 64 | `func_001FA588` | `multiply_quaternions` | descriptive | neighbours in the same order |
| `func_00283898` | 192 | `func_L00_001FFED8` | `build_axis_rotation_quaternion` | descriptive | neighbours in the same order |
| `func_00283958` | 120 | `func_001FA648` | `quaternion_to_rotation_basis` | descriptive | neighbours in the same order |
| `func_00283D00` | 56 | `func_L00_00200210` | `fast_fmod` | descriptive | neighbours in the same order |
| `func_00284E18` | 40 | `func_001FB448` | `SetBackgroundColor` | recovered | neighbours in the same order |
| `func_00284FC0` | 108 | `func_001FB598` | `PutDrawBufferSmall` | recovered | neighbours in the same order |
| `func_00288F48` | 108 | `func_001FE4D0` | `Help_FindIndex` | recovered | 100 bytes or more |
| `func_0028B338` | 148 | `func_L00_00235FF8` | `select_moby_context` | descriptive | neighbours in the same order |
| `func_0028B6C8` | 116 | `func_001FFDA0` | `set_animation_parameter` | descriptive | neighbours in the same order |
| `func_0028B740` | 104 | `func_L00_00236400` | `hud_screen_position` | descriptive | no address fields |
| `func_00293260` | 88 | `func_00203B18` | `relocate_asset_entry_pointers` | descriptive | no address fields |
| `func_00294D80` | 196 | `func_00205660` | `register_8bit_texture` | descriptive | 100 bytes or more |
| `func_00295BE8` | 100 | `func_00205C08` | `compose_bitmap_from_mask` | descriptive | no address fields |
| `func_00297550` | 280 | `func_00207090` | `decode_map_rle_row` | descriptive | no address fields |
| `func_0029AE78` | 56 | `func_0020BAD8` | `memcard_GetDataSize` | recovered | no address fields |
| `func_0029CF58` | 32 | `func_0020C210` | `DmaToSpr` | recovered | neighbours in the same order |
| `func_0029CF78` | 56 | `func_0020C230` | `DmaToSprSync` | recovered | neighbours in the same order |
| `func_0029D4D0` | 720 | `func_0020C468` | `fast_decompress` | descriptive | neighbours in the same order |
| `func_0029D7A0` | 32 | `func_0020C738` | `fast_decompress_spr_dma_start` | descriptive | neighbours in the same order |
| `func_0029F390` | 188 | `func_0020D6D0` | `update_moby_animation_state` | descriptive | neighbours in the same order |
| `func_0029FEE0` | 216 | `func_0020DD48` | `PatchMobyGifs` | recovered | neighbours in the same order |
| `func_002A0488` | 48 | `func_L00_00251328` | `set_moby_color` | descriptive | neighbours in the same order |
| `func_002A04B8` | 48 | `func_L00_00251358` | `get_moby_color` | descriptive | neighbours in the same order |
| `func_002A3DB8` | 340 | `func_00211548` | `get_moby_joint_matrices_batch` | descriptive | 100 bytes or more |
| `func_002A3F10` | 356 | `func_002116A0` | `get_moby_joint_matrices` | descriptive | 100 bytes or more |
| `func_002A4AD8` | 688 | `func_00212258` | `upload_used_moby_textures` | descriptive | 100 bytes or more |
| `func_002A4D88` | 224 | `func_00212578` | `MobyAnimProc` | recovered | 100 bytes or more |
| `func_002A7AA8` | 56 | `func_L00_00258E58` | `cubic_hermite_scalar` | descriptive | no address fields |
| `func_002A8AF0` | 204 | `func_L00_0025A778` | `point_in_path_xy` | descriptive | no address fields |
| `func_002A8C00` | 36 | `func_L00_0025A8C0` | `make_hit_descriptor` | descriptive | no address fields |
| `func_002AAF40` | 92 | `func_L00_0025D0E0` | `swap_color_channel_words` | descriptive | no address fields |
| `func_002B72E8` | 52 | `func_00216EF0` | `music_Pause` | recovered | neighbours in the same order |
| `func_002B7320` | 28 | `func_00216F28` | `music_Unpause` | recovered | neighbours in the same order |
| `func_002B7340` | 64 | `func_L00_002666C8` | `music_set_active_track_value` | descriptive | neighbours in the same order |
| `func_002B7DF8` | 48 | `func_00217830` | `music_channel_ready_callback` | descriptive | no address fields |
| `func_002B8048` | 108 | `func_00217A60` | `music_remaining_time_callback` | descriptive | neighbours in the same order |
| `func_002B8888` | 100 | `func_00218188` | `ClearPadInput` | recovered | no address fields |
| `func_002DE810` | 64 | `func_00227A30` | `pack_image_descriptor` | descriptive | no address fields |
| `func_002E0408` | 332 | `func_00229098` | `build_shadow_sphere_outline` | descriptive | neighbours in the same order |
| `func_002E10B8` | 260 | `func_00229D48` | `patch_shrub_gifs` | descriptive | neighbours in the same order |
| `func_002E2988` | 684 | `func_0022B648` | `BuildShrubTextureDma` | recovered | 100 bytes or more |
| `func_002E425C` | 296 | `func_0022D6B4` | `sky_queue_texture_upload` | descriptive | neighbours in the same order |
| `func_002E60E8` | 44 | `func_0022F0F0` | `voice_update_callback` | descriptive | no address fields |
| `func_002EF310` | 156 | `func_00234620` | `PatchTfragGifs` | recovered | 100 bytes or more |
| `func_002FC410` | 76 | `func_00234B48` | `VU1_addDataRef` | recovered | neighbours in the same order |
| `func_002FC518` | 72 | `func_00234C50` | `vu1_add_vif_code` | descriptive | neighbours in the same order |
| `func_002FCF90` | 52 | `func_00235290` | `append_dma_tag` | descriptive | neighbours in the same order |
| `func_0034FA30` | 180 | `func_0023C1F8` | `audioDecEndPut` | recovered | no address fields |
| `func_00350590` | 24 | `func_0023CD10` | `readBufCreate` | recovered | no address fields |
| `func_003505E0` | 68 | `func_0023CD60` | `readBufEndPut` | recovered | no address fields |
| `func_00350628` | 72 | `func_0023CDA8` | `readBufBeginGet` | recovered | no address fields |
| `func_00350670` | 36 | `func_0023CDF0` | `readBufEndGet` | recovered | no address fields |
| `func_00350878` | 36 | `func_0023CFF0` | `scTag2` | recovered | no address fields |
| `func_00351310` | 340 | `func_0023DA88` | `viBufModifyPts` | recovered | neighbours in the same order |
| `func_00351FA0` | 32 | `func_0023E710` | `voBufDecCount` | recovered | no address fields |
| `func_L00_002EE660` | 72 | `func_L00_001FF718` | `pack_vector_s16` | descriptive | neighbours in the same order |
| `func_L00_00310838` | 116 | `func_L00_0024FFE8` | `offset_moby_class_point_pairs` | descriptive | no address fields |
| `func_L00_0035F7E8` | 112 | `func_L00_0028F230` | `resolve_lookup_record` | descriptive | neighbours in the same order |
| `func_L00_00424A08` | 60 | `func_L00_002E9900` | `follow_camera_set_distance` | descriptive | neighbours in the same order |
| `func_L00_00424A50` | 52 | `func_L00_002E9968` | `follow_camera_set_height` | descriptive | neighbours in the same order |
| `func_L00_00424B48` | 36 | `func_L00_002E9A18` | `set_follow_camera_orbit_clamp_mode` | descriptive | neighbours in the same order |
| `func_L02_00364D3C` | 208 | `func_0022D1DC` | `_ssp_load_tex` | recovered | 100 bytes or more |
| `func_L03_002D84F0` | 104 | `func_L02_001FC308` | `register_camera_update_callback` | descriptive | 100 bytes or more |
| `func_L04_0032F1D8` | 360 | `func_L01_00262BC0` | `ripple_heights_to_scratchpad` | descriptive | neighbours in the same order |
| `func_L04_0032F340` | 128 | `func_L01_00262D28` | `ripple_lerp_buffers` | descriptive | neighbours in the same order |
| `func_L04_0032F994` | 656 | `func_L01_00263338` | `ripple_emit_sub_block` | descriptive | neighbours in the same order |
| `func_L04_0033CB88` | 120 | `func_L01_0026E8E0` | `MoveCtl_Init` | descriptive | no address fields |
