"""Exercise the C forwarders without relying on ambient EE floating registers."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
SOURCES = (
    ROOT / "src/game/0029B658-rc2.c",
    ROOT / "src/us2/game/0029C448-rc2.c",
    ROOT / "src/pal/game/0029BFF0-rc2.c",
)
HEADER = "#include <stdint.h>\ntypedef int32_t s32;\n"
HARNESS = r"""
#include <stdint.h>
typedef void (*Forwarder)(int32_t, int32_t, float, float, float, float);
void func_0029B658(int32_t, int32_t, float, float, float, float);
void func_US2_0029C448(int32_t, int32_t, float, float, float, float);
void func_PAL_0029BFF0(int32_t, int32_t, float, float, float, float);
int32_t D_001A8CFC;
static int calls;
static uintptr_t context;
static unsigned int alpha, color;
static float bounds[4];

void func_003384C0(char *object, unsigned int a, unsigned int c,
                   float top, float bottom, float left, float right)
{
    ++calls;
    context = (uintptr_t)object;
    alpha = a;
    color = c;
    bounds[0] = top;
    bounds[1] = bottom;
    bounds[2] = left;
    bounds[3] = right;
}

int main(void)
{
    Forwarder forwarders[] = {
        func_0029B658, func_US2_0029C448, func_PAL_0029BFF0
    };
    int i;
    for (i = 0; i < 3; ++i) {
        D_001A8CFC = 0;
        calls = 0;
        forwarders[i](-7, (int32_t)0xF0ABCDEFU, -12.5f, 43.25f, -3.75f, 91.5f);
        if (calls != 0)
            return 10 + i;
        D_001A8CFC = 0x100000;
        forwarders[i](-7, (int32_t)0xF0ABCDEFU, -12.5f, 43.25f, -3.75f, 91.5f);
        if (calls != 1 || context != 0x136F28U)
            return 20 + i;
        if (alpha != (unsigned int)-7 || color != 0xF0ABCDEFU)
            return 30 + i;
        if (bounds[0] != -12.5f || bounds[1] != 43.25f ||
            bounds[2] != -3.75f || bounds[3] != 91.5f)
            return 40 + i;
    }
    return 0;
}
"""


def compile_and_run(compiler, directory, sources):
    directory = Path(directory)
    (directory / "common.h").write_text(HEADER, encoding="utf-8")
    (directory / "include_asm.h").write_text("", encoding="utf-8")
    harness = directory / "contract.c"
    harness.write_text(HARNESS, encoding="utf-8")
    executable = directory / "contract"
    subprocess.run(
        [compiler, "-m32", "-std=c99", "-O2", "-I", str(directory),
         *map(str, sources), str(harness), "-o", str(executable)],
        check=True, capture_output=True, text=True, timeout=30,
    )
    return subprocess.run([str(executable)], capture_output=True, text=True, timeout=30)


class RectangleForwardingTests(unittest.TestCase):
    def test_all_regions_forward_context_flags_and_four_floats(self):
        compiler = shutil.which("cc") or shutil.which("gcc")
        if not compiler:
            self.skipTest("A native 32-bit C compiler is required")
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            probe = directory / "probe"
            result = subprocess.run(
                [compiler, "-m32", "-x", "c", "-", "-o", str(probe)],
                input="int main(void) { return sizeof(void *) != 4; }\n",
                capture_output=True, text=True, timeout=30,
            )
            if result.returncode:
                self.skipTest("The native compiler lacks a 32-bit C runtime")
            try:
                result = subprocess.run([str(probe)], capture_output=True, timeout=30)
            except OSError:
                self.skipTest("The host cannot execute 32-bit test programs")
            self.assertEqual(result.returncode, 0)
            result = compile_and_run(compiler, directory, SOURCES)
            self.assertEqual(
                result.returncode, 0,
                "Rectangle forwarders lost their context, flags or FP arguments "
                f"(contract exit {result.returncode}): {result.stderr}",
            )


if __name__ == "__main__":
    unittest.main()
