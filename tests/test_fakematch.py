"""tools/fakematch.py: FAKEMATCH comments are found per function, and only the allowed functions may have them."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("fakematch", ROOT / "tools/fakematch.py")
fakematch = importlib.util.module_from_spec(spec)
spec.loader.exec_module(fakematch)

SOURCE = """\
void func_L17_003E8A58(int *state)
{
    /* FAKEMATCH: volatile keeps the store before the load. */
    *(volatile int *)state = 0;
}

/* FAKEMATCH: the dead arm keeps a value live. */
void func_002CC6B0(void)
{
}

void func_00100000(void)
{
    int x; /* FAKEMATCH: not allowed here */
}
"""


class FakematchTests(unittest.TestCase):
    def test_sites_are_attributed_to_their_function(self):
        rows = fakematch.rows_of("src/x.c", SOURCE)
        self.assertEqual([r[1] for r in rows], ["func_L17_003E8A58", "func_002CC6B0", "func_00100000"])
        self.assertEqual(rows[0][2], "volatile keeps the store before the load")

    def test_only_allowed_functions_pass(self):
        errors = fakematch.problems(fakematch.rows_of("src/x.c", SOURCE))
        self.assertEqual(len(errors), 1)
        self.assertIn("func_00100000", errors[0])

    def test_helper_in_an_allowed_unit_passes(self):
        rows = [("src/u.c", "helper", "keeps a value live")]
        self.assertEqual(fakematch.problems(rows, {"src/u.c": {"helper", "func_002CC6B0"}}), [])
        self.assertEqual(len(fakematch.problems(rows, {"src/u.c": {"helper", "func_00100000"}})), 1)

    def test_release_own_functions_pass_in_their_release_tree(self):
        ok = [("src/pal/game/u.c", "func_PAL_0034F068", "r"), ("src/us2/levels/u.c", "func_US2_L03_003C8620", "r")]
        self.assertEqual(fakematch.problems(ok), [])
        self.assertEqual(fakematch.problems([("src/pal/u.c", "helper", "r")], {"src/pal/u.c": {"helper", "func_PAL_00100000"}}), [])
        bad = [("src/game/u.c", "func_PAL_0034F068", "r"), ("src/pal/game/u.c", "func_00100000", "r")]
        self.assertEqual(len(fakematch.problems(bad)), 2)

    def test_render_is_sorted_with_header(self):
        text = fakematch.render([("b.c", "f", "r"), ("a.c", "g", "s")])
        self.assertTrue(text.startswith("# Code that matches retail"))
        self.assertLess(text.index("a.c"), text.index("b.c"))

    def test_repository_table_agrees(self):
        self.assertEqual(fakematch.check(), [])


if __name__ == "__main__":
    unittest.main()
