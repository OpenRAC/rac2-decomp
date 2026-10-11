#!/usr/bin/env bash
# Build the GNU EE 2.9-ee-991111b chain (cc1, cpp, as) from public sources in a Podman/Docker container.
# Usage: tools/linux/build-compiler.sh <work-dir>      (outputs <work-dir>/tools/{cc1,cpp,as})
# Inputs are fetched from public hosts and SHA-256 checked. Needs: podman or docker, git, curl, gh optional.
# Builds on Ubuntu 24.04; the five source hashes must equal docs/COMPILER-NOTES.md. Binary hashes also depend
# on the build host (documented on 26.04). Recipe and image: github.com/OpenRAC/OpenRAC games/rac2/ntsc/host.
set -euo pipefail
WORK=$(mkdir -p "$1" && cd "$1" && pwd)
REPO=$(cd "$(dirname "$0")/../.." && pwd)
ENGINE=${CONTAINER_ENGINE:-$(command -v podman || command -v docker)}
LOMBYTE_COMMIT=c260794
D=$WORK/openrac/build/rac2/downloads
get() { curl -fsSL -o "$2" "$1"; echo "$3  $2" | sha256sum -c --quiet; }

[[ -d $WORK/openrac/.git ]] || git clone -q --depth 1 https://github.com/OpenRAC/OpenRAC "$WORK/openrac"
mkdir -p "$D/lombyte-$LOMBYTE_COMMIT"
get "https://web.archive.org/web/20060518234647id_/http://ps2dev.sourceforge.net:80/downloads/ee/gnu-ee-binutils-gcc-1.1.tar.gz" \
    "$D/gnu-ee-binutils-gcc-1.1.tar.gz" 1f518043e252d6eda726386971d52eda26541ab936ea73a9783d73712b595f92
get https://ftp.gnu.org/gnu/bison/bison-1.28.tar.gz "$D/bison-1.28.tar.gz" \
    c5d3e4858e17cb440cee9de7837f07277bcfb03507e9d2f0c506cab5efe36c3a

# The OpenRAC clone lacks patch 0034; take the whole stack from the pinned Lombyte commit instead.
P=$WORK/openrac/games/rac1/ntsc/patches/sce-991111b
BASE=https://raw.githubusercontent.com/mateuszklysz/Lombyte/$LOMBYTE_COMMIT/patches/sce-991111b
for n in $(curl -fsSL "https://api.github.com/repos/mateuszklysz/Lombyte/contents/patches/sce-991111b?ref=$LOMBYTE_COMMIT" \
           | grep -o '"name": *"[^"]*\.patch"' | cut -d'"' -f4); do curl -fsSL -o "$P/$n" "$BASE/$n"; done
get "$BASE/0020-gas-absolute-unknown-symbol.patch" "$D/lombyte-$LOMBYTE_COMMIT/0020-gas-absolute-unknown-symbol.patch" \
    4a1726ac272b83648eea77e07e3fb13c4440a378cb3e69831c71f596838392dc

# Use this repository's recipe (published transformers only; reproduces the qualified source hashes).
cp "$REPO/tools/linux/rac2_recipe.py" "$WORK/openrac/games/rac2/ntsc/host/rac2_recipe.py"
H=$WORK/openrac/games/rac2/ntsc/host
sed -i 's|^RAC2=.*|RAC2=${RAC2_SCRIPTS:-$OPENRAC/games/rac2/ntsc/scripts/compiler}|' "$H/build-chain.sh"

UBUNTU=${UBUNTU:-24.04}   # docs/COMPILER-NOTES.md hashes were made on 26.04
sed "s/ubuntu:24.04/ubuntu:$UBUNTU/" "$H/linux-amd64.Dockerfile" > "$WORK/Dockerfile"
"$ENGINE" build -q -t rac2-linux:$UBUNTU -f "$WORK/Dockerfile" "$H" >/dev/null
mkdir -p "$WORK/chain"
"$ENGINE" run --rm --userns=keep-id --security-opt label=disable \
  -v "$WORK:$WORK" -v "$REPO/scripts/compiler:$REPO/scripts/compiler:ro" \
  -e RAC2_SCRIPTS="$REPO/scripts/compiler" -e PATCH_0020="$D/lombyte-$LOMBYTE_COMMIT/0020-gas-absolute-unknown-symbol.patch" \
  rac2-linux:$UBUNTU bash "$H/build-chain.sh" "$WORK/chain"
mkdir -p "$WORK/tools" && cp "$WORK"/chain/tools/{cc1,cpp,as} "$WORK/tools/"
echo "source hashes:"; cat "$WORK/chain/source-hashes.txt"
sha256sum "$WORK"/chain/source/gcc/toplev.c | sed "s|$WORK/chain/||"
echo "compare with the checkpoints in docs/COMPILER-NOTES.md; compiler tools are in $WORK/tools"
