"""Run the Windows+WSL based RAC2 scripts on Linux without editing them.

Put this directory on PYTHONPATH. It changes only how child programs start:
  * ``*.exe`` is started through $RAC2_EXE_RUNNER (e.g. wibo);
  * ``wsl.exe -d D -e bash -lc SCRIPT`` runs SCRIPT through $RAC2_LINUX_RUNNER
    (e.g. ``podman exec rac2-gnu bash -c``), which must see the same paths;
  * ``wsl_chain.wsl_path`` returns the POSIX path unchanged.
Hashes and gates in the scripts are untouched; scripts/wsl_chain.py is hashed by
the level reviews and must not be edited.
"""
import importlib.abc
import importlib.machinery
import os
import shlex
import subprocess
import sys
from pathlib import Path

_POPEN = subprocess.Popen


def _rewrite(args):
    if isinstance(args, (str, bytes)) or not args:
        return args
    args = [os.fsdecode(a) for a in args]
    program = os.path.basename(args[0]).lower()
    if program == "wsl.exe":
        if len(args) != 7 or args[3:6] != ["-e", "bash", "-lc"]:
            raise ValueError(f"Unexpected WSL invocation: {args[:6]}")
        return shlex.split(os.environ.get("RAC2_LINUX_RUNNER", "bash -c")) + [args[6]]
    if program.endswith(".exe"):
        runner = os.environ.get("RAC2_EXE_RUNNER")
        return shlex.split(runner) + args if runner else args
    return args


class _Popen(_POPEN):
    def __init__(self, args, *a, **k):
        super().__init__(_rewrite(args), *a, **k)


subprocess.Popen = _Popen


class _Finder(importlib.abc.MetaPathFinder):
    def find_spec(self, name, path, target=None):
        if name != "wsl_chain":
            return None
        spec = importlib.machinery.PathFinder.find_spec(name, path)
        if spec is None or spec.loader is None:
            return spec
        run = spec.loader.exec_module

        def exec_module(module):
            run(module)
            module.wsl_path = lambda value: str(Path(value).resolve())

        spec.loader.exec_module = exec_module
        return spec


sys.meta_path.insert(0, _Finder())
