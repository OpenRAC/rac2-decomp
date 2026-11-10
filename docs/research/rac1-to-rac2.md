# RAC1 to RAC2: preparation decisions

Measured on 2026-10-01 against the pinned USA v1.01 image.

The earlier project-45 GC extraction from 2026-09-19 was rechecked using a fresh
archive extraction and a fresh Wrench unpack. Its 27 ELF signatures established
extraction, not reconstruction. RAC2 now has its own profile and byte gates.

| Property | RAC2 measurement | Consequence |
| --- | --- | --- |
| Disc | 3,828,350,976 bytes; all five configured hashes match | Refuse other editions before unpacking |
| Boot | 2,618,684-byte MIPS ELF; entry `0x00131AE8` | Pin the executable independently of RAC1 |
| GP | `0x001AEFF0` from `.reginfo` | Do not reuse RAC1 GP `0x00166C00` |
| PT_LOAD | 2; total 2,521,763 file-backed bytes | Compare both, not just the largest |
| Secondary load | address `0x01800000`, 88,931 bytes | Preserve auxiliary data and its odd-sized ending |
| Section names | `mc1.data` occurs twice | Distinguish generated names with file offsets |
| Level executables | 27 with distinct pinned SHA-256 identities | Use program identity plus level, address and size |

The first ProDG 3.01 reconstruction of `core.text` was 116 bytes larger than the
same assembly built with ProDG 2.0. The later assembler inserted hazard NOPs in
short loops even with `.set noreorder`. ProDG 2.0 is therefore the instrument used
for this **assembly reconstruction**. This does not qualify its C compiler, or
invalidate the later assembler for future compiler-generated RAC2 candidates.

The gap between the two loads is not runtime memory. It terminates the preceding
splat segment and is excluded from the link. Splat data disassembly omitted the
final three bytes of the secondary load; emitting them into an assembler data
section caused alignment to add a fourth byte. The linker instead emits the three
data bytes at that section's end. Every byte and every load extent still passes
the full comparison; no candidate executable is trimmed to fit an oracle.

Local build reports record instrument hashes and dependency versions. Each run
starts from newly generated assembly and objects. The acceptance gate checks
fresh output, entry point, all PT_LOAD contents, addresses, sizes, memory extents
and flags. Metadata outside loaded memory can differ, so a matching reconstruction
is not a byte-identical ELF container and is not decompiled C/C++.

Pending qualification: compiler identity and flags, GP-relative relocation policy,
stack-frame conventions, reviewed function boundaries and padding/delay slots.
No RAC1 function name, address or optimization profile has been promoted into a
RAC2 match. No native gameplay has been claimed.
