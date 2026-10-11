"""Run explicitly targeted local tests or select bounded maintainer PR tests.

This is a focused check, never a full-suite or matching-gate receipt. The
protected merge queue still runs unittest discovery over every test module.
"""
import argparse
import ast
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import unittest

from maintainer_test_policy import identity, REPOSITORY


def authenticate(repo):
    """Use GitHub's immutable authenticated user ID, not local Git names."""
    remote = subprocess.check_output(["git", "-C", str(repo), "remote", "get-url", "origin"], text=True).strip()
    if remote not in {"https://github.com/" + REPOSITORY + ".git", "https://github.com/" + REPOSITORY,
                      "git@github.com:" + REPOSITORY + ".git"}:
        raise ValueError("Maintainer testing requires the maintained GitHub repository")
    result = subprocess.run(["gh", "api", "--hostname", "github.com", "user"], capture_output=True, text=True)
    if result.returncode or not identity(json.loads(result.stdout)):
        raise ValueError("Maintainer testing requires the authenticated primary maintainer")
    user = json.loads(result.stdout)
    return {"id": user["id"], "login": user["login"]}


def validate_modules(repo, modules):
    values = sorted(set(modules))
    if not values:
        raise ValueError("Specify at least one test module")
    for name in values:
        if not re.fullmatch(r"test_[a-z0-9_]+", name) or not (repo / "tests" / (name + ".py")).is_file():
            raise ValueError("Unknown maintained test module: " + name)
    return values


def check_changed_python(repo, paths):
    """Syntax-only owner precheck; never import executable contributors here."""
    checked = []
    for relative in sorted(set(paths)):
        if not relative.endswith(".py"):
            continue
        path = repo / relative
        if path.is_absolute() and not path.resolve().is_relative_to(repo.resolve()):
            raise ValueError("Changed Python path escapes the repository")
        if path.is_file():
            ast.parse(path.read_bytes(), filename=relative)
            checked.append(relative)
    return checked


def select_modules(repo, paths):
    """Owner PR precheck: smoke + directly changed test modules + syntax.

    This deliberately does not infer transitive coverage or run a heavy suite
    for an orphan executable. It is limited pre-queue feedback; every queued
    contribution still runs unconditional full discovery in the workflow.
    """
    check_changed_python(repo, paths)
    selected = {"test_maintainer_test_policy", "test_maintainer_tests", "test_decomp_report_cli"}
    for relative in paths:
        if Path(relative).parent == Path("tests") and relative.endswith(".py"):
            name = Path(relative).stem
            if name.startswith("test_") and (repo / "tests" / (name + ".py")).is_file():
                selected.add(name)
    return validate_modules(repo, selected)


def run_modules(repo, modules):
    sys.path.insert(0, str(repo / "scripts"))
    sys.path.insert(0, str(repo / "tests"))
    if modules is None:
        print("Unmapped executable change: running the complete suite.", flush=True)
        suite = unittest.defaultTestLoader.discover(str(repo / "tests"))
    else:
        print("Targeted test modules: " + ", ".join(modules), flush=True)
        suite = unittest.defaultTestLoader.loadTestsFromNames(modules)
    if not suite.countTestCases():
        print("No tests were selected; refusing a successful test receipt.", flush=True)
        return 1
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    return 0 if result.wasSuccessful() else 1


def _flatten_tests(suite):
    for item in suite:
        if isinstance(item, unittest.TestSuite):
            yield from _flatten_tests(item)
        else:
            yield item


def test_ids(repo, modules):
    repo = Path(repo).resolve()
    for path in (repo / "scripts", repo / "tests"):
        value = str(path)
        if value not in sys.path:
            sys.path.insert(0, value)
    suite = unittest.defaultTestLoader.loadTestsFromNames(modules)
    return [test.id() for test in _flatten_tests(suite)]


def run_test_ids(repo, identifiers):
    repo = Path(repo).resolve()
    for path in (repo / "scripts", repo / "tests"):
        value = str(path)
        if value not in sys.path:
            sys.path.insert(0, value)
    suite = unittest.defaultTestLoader.loadTestsFromNames(identifiers)
    if not suite.countTestCases():
        print("No tests were selected; refusing a successful test receipt.", flush=True)
        return 1
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    return 0 if result.wasSuccessful() else 1


def run_modules_parallel(repo, modules, jobs=0):
    """Shard maintained test cases across isolated worker processes."""
    repo = Path(repo).resolve()
    modules = validate_modules(repo, modules)
    requested = jobs or min(4, os.cpu_count() or 1)
    if type(requested) is not int or requested < 1:
        raise ValueError("Maintainer test jobs must be a positive integer or zero for automatic selection")
    identifiers = test_ids(repo, modules)
    if not identifiers:
        print("No tests were selected; refusing a successful test receipt.", flush=True)
        return 1
    workers = min(requested, len(identifiers))
    if workers == 1:
        return run_test_ids(repo, identifiers)
    code = ("import sys;from pathlib import Path;sys.path[:0]=['scripts','tests'];"
            "from maintainer_tests import run_test_ids;"
            "sys.exit(run_test_ids(Path.cwd(),sys.argv[1:]))")
    shards = [identifiers[index::workers] for index in range(workers)]

    def execute(index):
        return subprocess.run([sys.executable, "-c", code, *shards[index]], cwd=repo,
                              capture_output=True, text=True)

    print(f"Parallel targeted tests: {len(identifiers)} cases from {len(modules)} modules, "
          f"{workers} workers", flush=True)
    failed = []
    with ThreadPoolExecutor(max_workers=workers) as pool:
        futures = {pool.submit(execute, index): index for index in range(workers)}
        for future in as_completed(futures):
            index = futures[future]
            result = future.result()
            print(f"\n===== worker {index + 1}/{workers}: {len(shards[index])} cases "
                  f"(exit {result.returncode}) =====", flush=True)
            if result.stdout:
                print(result.stdout, end="" if result.stdout.endswith("\n") else "\n", flush=True)
            if result.stderr:
                print(result.stderr, end="" if result.stderr.endswith("\n") else "\n", file=sys.stderr, flush=True)
            if result.returncode:
                failed.append(index + 1)
    if failed:
        print("Failed targeted workers: " + ", ".join(map(str, sorted(failed))), file=sys.stderr, flush=True)
        return 1
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, default=Path(__file__).resolve().parents[1])
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--test", action="append", help="Maintained test module; repeat for a local focused check")
    group.add_argument("--ci-base", help="Verified protected-base SHA supplied by the CI policy")
    args = parser.parse_args(argv)
    repo = args.repo.resolve()
    if args.test:
        authenticate(repo)
        modules = validate_modules(repo, args.test)
    else:
        if not re.fullmatch(r"[0-9a-f]{40}", args.ci_base):
            parser.error("CI base must be an exact commit SHA")
        paths = subprocess.check_output(["git", "-C", str(repo), "diff", "--name-only", "-z",
                                         args.ci_base, "HEAD"], text=True).split("\0")
        modules = select_modules(repo, [p for p in paths if p])
    return run_modules(repo, modules)


if __name__ == "__main__":
    raise SystemExit(main())
