# toolchain/

Local tools that cannot be distributed. Never committed (see `.gitignore`).

- `sn-prodg-2.0/ee/bin/Ps2EeAs.exe`: SN ProDG 2.0's assembler (SHA-256 `c839dd63…`).
- `sn-prodg-2.0/ee/bin/ld.exe`: the SN ProDG 3.01 linker (SHA-256 `80f3724a…`).

The compilers are not here: `tools/compiler/` rebuilds them from public source into
`build/compiler/`. See [docs/build/building.md](../docs/build/building.md).
