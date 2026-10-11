"""Where private (game-derived) working data may live.

Outside the repository, or inside its git-ignored ``extracted/`` folder. Nothing under ``extracted/``
is ever tracked: ``.gitignore`` excludes it and ``scripts/legal_check.py`` rejects any tracked file there.
"""
from __future__ import annotations

import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EXTRACTED = ROOT / "extracted"


def inside_repository(path: Path) -> bool:
    resolved = path.resolve()
    return resolved == ROOT or ROOT in resolved.parents


def allowed(path: Path) -> bool:
    """True for a directory outside the repository, or one under the ignored ``extracted/`` folder."""
    resolved = path.resolve()
    if not inside_repository(resolved):
        return True
    if EXTRACTED not in resolved.parents:
        return False
    probe = resolved / ".private-probe"
    ignored = subprocess.run(["git", "-C", str(ROOT), "check-ignore", "-q", str(probe)], check=False).returncode == 0
    return ignored
