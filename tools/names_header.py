"""Read the generated name table: include/names.h and the parts it includes (include/names/)."""
from pathlib import Path

PARTS = "names"


def part_files(header):
    """The generated parts next to this header."""
    folder = Path(header).parent / PARTS
    return sorted(folder.glob("*.h")) if folder.is_dir() else []


def is_generated(path, header):
    """Is this file the name table, or a part of it?"""
    return Path(path) == Path(header) or Path(path).parent == Path(header).parent / PARTS


def read(header):
    """All the name table's text, or an empty string if it is not there."""
    header = Path(header)
    if not header.exists():
        return ""
    return "\n".join(p.read_text(errors="replace") for p in [header, *part_files(header)])
