# Distribution and source scope

This repository tracks authored source, tooling, structural identifiers and proof
metadata for Ratchet & Clank: Going Commando. Accepted matching coverage targets
USA v1.01; USA v2.00 remains an experimental route with zero credited candidates.

Game images, extracted executables, disassembly, textures, audio and other assets
remain private and are not publication inputs. Contributors supply their own
reference disc and permitted tools. Generated private outputs stay outside Git.
The local `legal_check.py` scan is a distribution hygiene check; it does not
establish licensing rights or technical matching proof.

The root [MIT licence](LICENSE) applies to original project work. Imported
reference helpers in [tools/ee/](tools/ee/README.md) retain their separate GPL-2.0
licence. [CREDITS.md](CREDITS.md) records provenance; attribution alone does not
relicense upstream work. The PAL functional port retains its own notice.
Source-specific SDK and compiler owners retain the provenance and limits in
[toolchain/README.md](toolchain/README.md); proprietary tools and runtime binaries
are supplied privately and are not distributed in this repository.

Only current complete-symbol and full-image byte/metadata gates establish
accepted C coverage. A masked comparison, assembly reconstruction, name hint,
heuristic family or exploratory report contributes no matching credit.
