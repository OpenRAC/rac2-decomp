"""Source text with readable names turned back into address names.

C may define and use a symbol by its readable name (`void yeti_update(...)`);
include/names.h makes that a macro for the address name (`func_L19_0041B078`,
`D_L19_001B1D20`), so the object is the same. Tools that find definitions or
symbols by their address name read source through read_c() so they see the
address spelling either way. Line structure is kept: every replacement stays
on its line. Carried from rac1-decomp's tools/srcnames.py; rac2 maps data
names too.
"""
import re
from functools import lru_cache
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
import names_header  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
HEADER = ROOT / "include/names.h"
SYMBOL = r"(?:func|D)_(?:L\d\d_)?[0-9A-Fa-f]{8}"


@lru_cache(maxsize=1)
def _table():
    text = names_header.read(HEADER)
    names = dict(re.findall(rf"(?m)^#define\s+(\w+)\s+({SYMBOL})\s*$", text))
    if not names:
        return None, names
    # All keys above are whole \w+ tokens. Scanning tokens once avoids trying
    # thousands of alternatives at every word in every source file.
    token = re.compile(r"\b\w+\b")
    return token, names


def canon(text: str) -> str:
    """TEXT with every readable name replaced by its address name."""
    token, names = _table()
    if token is None:
        return text
    return token.sub(lambda m: names.get(m.group(0), m.group(0)), text)


def read_c(path, **kw) -> str:
    """PATH's text, as canon() gives it."""
    return canon(Path(path).read_text(**kw))
