"""One producer for current CI metadata checks and public report artifacts.

Source mode is limited pre-queue metadata validation, never a full-suite receipt.
Local mode trusts the owner's committed local reports and publishes metadata,
without a remote tool-suite or fresh unique/reuse classification receipt.
Full mode keeps the actual expensive checks once. Legal-reference raw gates
remain the maintained local workflow's responsibility.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import sysconfig
import importlib.metadata
import re
import tempfile

ROOT = Path(__file__).resolve().parents[1]
FILES = {
    "report.json": "build/decomp/report.json",
    "source-modules.json": "build/decomp/source-modules.json",
    "source-inventory.json": "progress/source-inventory.json",
    "unique-report.json": "build/decomp/unique-report.json",
    "unique-summary.json": "build/decomp/unique-summary.json",
    "code-reuse-report.json": "progress/code-reuse-report.json",
    "code-reuse-families.json.gz": "progress/code-reuse-families.json.gz",
    "objdiff-validation.json": "build/decomp/objdiff-validation.json",
    "unique-objdiff-validation.json": "build/decomp/unique-objdiff-validation.json",
}
CHECKS = ["source-layout-full", "physical-proofs", "unique", "reuse", "objdiff-physical", "objdiff-unique"]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def contained(repo, relative):
    path = repo / relative
    if path.is_symlink() or not path.resolve().is_relative_to(repo.resolve()) or path.resolve() == repo.resolve():
        raise ValueError("CI input/output leaves repository")
    return path


def checkout_guard(repo):
    expected = os.environ.get("GITHUB_SHA", "")
    if not re.fullmatch(r"[0-9a-f]{40}", expected):
        raise ValueError("Exact announced CI commit is missing")
    head = subprocess.check_output(["git", "-C", str(repo), "rev-parse", "--verify", "HEAD"]).decode().strip()
    if head != expected:
        raise ValueError("CI checkout differs from announced commit")
    for args in (("diff", "--quiet", "HEAD", "--"), ("diff", "--quiet", "--cached", "HEAD", "--")):
        result = subprocess.run(["git", "-C", str(repo), *args], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        if result.returncode != 0:
            raise ValueError("CI tracked worktree or index changed")


def inputs(repo):
    checkout_guard(repo)
    names = subprocess.check_output(["git", "-C", str(repo), "ls-files", "-z"]).decode().split("\0")
    if not any(names):
        raise ValueError("Tracked CI input closure is empty")
    return {name: sha(contained(repo, name).read_bytes()) for name in sorted(names) if name}


def tools(objdiff):
    result = {"python-executable": sha(Path(sys.executable).read_bytes()),
              "objdiff-cli": sha(Path(objdiff).read_bytes())}
    stdlib = Path(sysconfig.get_path("stdlib"))
    for path in sorted(stdlib.rglob("*")):
        relative = path.relative_to(stdlib)
        if "site-packages" not in relative.parts and path.is_file() and path.suffix in (".py", ".so", ".pyd"):
            result["stdlib/" + relative.as_posix()] = sha(path.read_bytes())
    library = sysconfig.get_config_var("LDLIBRARY")
    if library:
        path = Path(sys.base_prefix) / "lib" / library
        if path.is_file():
            result["python-library"] = sha(path.read_bytes())
    package = importlib.metadata.distribution("rabbitizer")
    if package.version != "1.16.2":
        raise ValueError("Decoder version differs")
    for relative in package.files or []:
        path = Path(package.locate_file(relative))
        if path.is_file() and path.suffix in (".py", ".so", ".pyd"):
            result["rabbitizer/" + str(relative).replace("\\", "/")] = sha(path.read_bytes())
    if not any(k.startswith("rabbitizer/") for k in result):
        raise ValueError("Decoder byte closure is missing")
    return result


def source_metadata(repo):
    """Read current pinned source and render exact recipes, without family scan."""
    import source_layout as layout
    manifest_path = repo / "config/source-layout.json"
    raw = manifest_path.read_bytes()
    manifest = json.loads(raw)
    if (Path(layout.__file__).resolve() != (repo / "scripts/source_layout.py").resolve()
            or manifest["generator_sha256"] != sha((repo / "scripts/source_layout.py").read_bytes())):
        raise ValueError("Source generator freshness changed")
    for relative, expected in manifest["input_sha256"].items():
        if sha(contained(repo, relative).read_bytes()) != expected:
            raise ValueError("Pinned source input changed")
    boot, native, required = layout.load_inputs(repo)
    smalldata = layout.load_smalldata(repo, required)
    from boot_sdk_unit import admitted_units, load_catalog
    sdk = [load_catalog(repo, unit) for unit in admitted_units(repo)]
    expected_sources = {"candidates/boot.c"} | {c["source"] for _, c in native + smalldata} | {c["source"] for c in sdk}
    if any(manifest["input_sha256"].get(name) != value for name, value in required.items()):
        raise ValueError("Current catalogue is absent from source input closure")
    generated, _ = layout.render(repo, manifest, enforce_hashes=True)
    if set(generated) != expected_sources or any(data != contained(repo, name).read_bytes() for name, data in generated.items()):
        raise ValueError("Actual standalone source differs from current recipes")
    inventory = {"schema": 1, "kind": "authored-source-inventory", "source_layout_sha256": sha(raw),
                 "metrics": manifest["metrics"], "integration_credit_added": 0}
    encoded = (json.dumps(inventory, indent=2, sort_keys=True) + "\n").encode()
    if encoded != (repo / "progress/source-inventory.json").read_bytes():
        raise ValueError("Source inventory metadata differs")
    return {"byte_identical_units": len(generated), "scope": "current hashes/render; no fresh family classification"}


def command(repo, *args):
    subprocess.run(args, cwd=repo, check=True)


def physical_display(repo, physical):
    import readme_progress as display
    read = lambda path: json.loads((repo / path).read_bytes())
    levels = [read("progress/levels/" + row["level"] + ".json") for row in read("config/overlays.json")["levels"]]
    native = [f for proof in levels for f in proof["functions"] if f.get("origin") in ("level-native", "level-smalldata")]
    svg = display.render(int(physical["measures"]["matchedCode"]), int(physical["measures"]["totalCode"])).encode()
    text = (repo / "README.md").read_text(encoding="utf8")
    table = display.render_table(physical, native, read("progress/report.json")["verified_at"])
    if svg != (repo / "progress/decompilation.svg").read_bytes() or display.update_readme(text, table) != text:
        raise ValueError("Physical display differs from current validated report")


def unique_and_reuse(repo, output):
    # Shared maintained API inputs: unique.generate runs exactly once, and
    # code_reuse.generate receives that validated primary rather than rerunning it.
    import unique_code_report as uq
    import code_reuse_report as reuse
    path = repo / "config/function-catalog/catalog.json"
    catalog, raw = uq.read_catalog(path)
    credit = uq.load_current_credit(repo, catalog)
    primary = uq.generate(catalog, credit, uq.current_boot_binding(repo, catalog))
    primary["catalog_sha256"] = uq.digest(raw)
    summary = {k: v for k, v in primary.items() if k != "groups"}
    summary_bytes = uq.encoded(summary)
    if summary_bytes != (repo / "progress/unique-code-report.json").read_bytes():
        raise ValueError("Current unique serialization differs")
    (output / "unique-summary.json").write_bytes(summary_bytes)
    (output / "unique-report.json").write_bytes(uq.encoded(uq.objdiff(primary)))
    wide = reuse.wide_groups(repo)
    report, details = reuse.generate(catalog, credit, primary, wide)
    authored, authored_details = reuse.authored_subset(repo, credit)
    report.update(authored_C_reuse_subset=authored, catalog_sha256=reuse.digest(raw),
                  input_sha256=reuse.snapshot(repo, path, catalog),
                  wide_group_reference=reuse.wide_reference(wide))
    families = reuse.compressed(reuse.encoded(reuse.families_payload(details, authored_details, wide)))
    report["families_sha256"] = reuse.digest(families)
    if (reuse.encoded(report) != (repo / "progress/code-reuse-report.json").read_bytes()
            or families != (repo / "progress/code-reuse-families.json.gz").read_bytes()):
        raise ValueError("Current reusable-code serialization differs")


def local_reports(repo, before, event):
    """Publish current committed local snapshots; never mint full queue proof."""
    from maintainer_test_policy import owner_local_push
    if not owner_local_push(os.environ.get("GITHUB_EVENT_NAME"), event, os.environ.get("GITHUB_SHA")):
        raise ValueError("Local publication requires the exact primary maintainer push")
    source = source_metadata(repo)
    from progress_module_report import verified_report
    physical = verified_report(repo)
    physical_display(repo, physical)
    read = lambda relative: json.loads(contained(repo, relative).read_bytes())
    summary = read("progress/unique-code-report.json")
    reuse = read("progress/code-reuse-report.json")
    catalog_path = "config/function-catalog/catalog.json"
    catalog = read(catalog_path)
    catalog_sha = before.get(catalog_path)
    if (summary.get("catalog_sha256") != catalog_sha or reuse.get("catalog_sha256") != catalog_sha
            or reuse.get("primary_reference", {}).get("metrics") != summary.get("metrics")):
        raise ValueError("Local report catalogue or primary metrics changed")
    pins = {row["path"]: row["sha256"] for row in catalog["input_pins"]}
    for snapshot in (pins, reuse["input_sha256"]):
        for relative, expected in snapshot.items():
            if before.get(relative) != expected:
                raise ValueError("Local report input snapshot changed")
    for row in catalog.get("function_chunks", []):
        relative = (Path(catalog_path).parent / row["path"]).as_posix()
        if before.get(relative) != row["sha256"]:
            raise ValueError("Local catalogue chunk changed")
    if before.get("progress/code-reuse-families.json.gz") != reuse.get("families_sha256"):
        raise ValueError("Local reusable-code family snapshot changed")
    metrics = summary["metrics"]
    excluded_vu = summary["coverage"]["excluded_vu_bytes"]
    if type(excluded_vu) is not int or excluded_vu < 0:
        raise ValueError("Local unique VU exclusion is invalid")
    if (metrics["physical_total_bytes"] + excluded_vu != int(physical["measures"]["totalCode"])
            or metrics["physical_matched_bytes"] != int(physical["measures"]["matchedCode"])):
        raise ValueError("Local unique summary differs from current physical proof")
    total, matched = metrics["unique_total_bytes"], metrics["unique_matched_bytes"]
    if type(total) is not int or type(matched) is not int or not 0 <= matched <= total:
        raise ValueError("Local unique aggregate is invalid")
    from progress_modules import group_report
    from decomp_report import measures
    grouped, modules = group_report(physical, repo)
    aggregate = measures(total, 0, 1, matched, 0)
    unique = {"version": 2, "measures": aggregate,
              "units": [{"name": "committed-local-unique-summary", "measures": aggregate,
                         "metadata": {"complete": False, "autoGenerated": True, "progressCategories": ["unique"]}}],
              "categories": [{"id": "unique", "name": "Committed conservative unique EE summary", "measures": aggregate}]}
    output = repo / "build/decomp"
    output.mkdir(parents=True, exist_ok=True)
    for name, value in (("report.json", grouped), ("source-modules.json", modules), ("unique-report.json", unique)):
        (output / name).write_bytes((json.dumps(value, indent=2) + "\n").encode())
    (output / "unique-summary.json").write_bytes(contained(repo, "progress/unique-code-report.json").read_bytes())
    if inputs(repo) != before:
        raise ValueError("Local report inputs changed during publication")
    names = {name: path for name, path in FILES.items() if "objdiff-validation" not in name}
    provenance = {"schema": 1, "kind": "owner-local-report-publication", "mode": "local",
                  "commit_sha": os.environ["GITHUB_SHA"],
                  "repository": {key: event["repository"][key] for key in ("id", "full_name")},
                  "actor": {key: event["sender"][key] for key in ("id", "login")},
                  "local_validation_trusted": True, "local_validation_automatically_verified": False,
                  "remote_full_validation": False, "fresh_unique_reuse_classification": False,
                  "unique_view": "aggregate from committed summary; no per-class regeneration",
                  "source": source, "inputs": before,
                  "outputs": {name: sha(contained(repo, path).read_bytes()) for name, path in names.items()}}
    (output / "local-provenance.json").write_bytes((json.dumps(provenance, sort_keys=True) + "\n").encode())
    return {"mode": "local", "local_validation_trusted": True, "full_validation": False,
            "fresh_unique_reuse_classification": False, "provenance": str(output / "local-provenance.json")}


def produce(repo, mode, objdiff=None, event=None):
    before = inputs(repo)
    if mode == "local":
        return local_reports(repo, before, event or {})
    source = source_metadata(repo)
    from progress_module_report import verified_report
    physical = verified_report(repo)  # Original generate + validate_object_proof once.
    physical_display(repo, physical)
    with tempfile.TemporaryDirectory(prefix="rac2-ci-views-", dir=os.environ.get("RUNNER_TEMP")) as directory:
        runtime = Path(directory).resolve()
        canonical = repo.resolve()
        if runtime == canonical or runtime.is_relative_to(canonical) or canonical.is_relative_to(runtime):
            raise ValueError("Campaign runtime must remain outside the repository")
        command(repo, sys.executable, "scripts/campaign.py", "--runtime", str(runtime), "views", "--check")
    if mode == "source":
        if inputs(repo) != before:
            raise ValueError("Source metadata changed during precheck")
        return {"mode": "source", "source": source, "physical": physical["measures"],
                "full_validation": False, "artifacts_published": False}
    if mode != "full" or objdiff is None:
        raise ValueError("Full export requires pinned objdiff")
    if sha(Path(objdiff).read_bytes()) != "c8290281e82114bcc1a06ff73061110d3902a177822e750337de2537188e358f":
        raise ValueError("Objdiff executable pin differs")
    tool_pins = tools(objdiff)
    import source_layout as layout
    layout.verify(repo, repo)  # Full family/source check, not source-mode shortcut.
    from progress_modules import group_report
    grouped, summary = group_report(physical, repo)
    output = repo / "build/decomp"
    output.mkdir(parents=True, exist_ok=True)
    for name, value in (("report.json", grouped), ("source-modules.json", summary)):
        (output / name).write_bytes((json.dumps(value, indent=2) + "\n").encode())
    command(repo, str(objdiff), "report", "changes", str(output / "report.json"), str(output / "report.json"),
            "-o", str(output / "objdiff-validation.json"))
    unique_and_reuse(repo, output)
    command(repo, sys.executable, "scripts/readme_unique_progress.py", "--catalogue-report", "progress/unique-code-report.json",
            "--physical-report", "build/decomp/report.json", "--check")
    from decomp_report import measures
    (output / "empty.json").write_bytes(json.dumps({"version": 2, "measures": measures(0, 0, 0),
                                                  "units": [], "categories": []}).encode())
    command(repo, str(objdiff), "report", "changes", str(output / "empty.json"), str(output / "unique-report.json"),
            "-o", str(output / "unique-objdiff-validation.json"))
    if inputs(repo) != before or tools(objdiff) != tool_pins:
        raise ValueError("CI inputs changed during full export")
    receipt = {"schema": 1, "kind": "verified-ci-full-export", "mode": "full", "checks": CHECKS,
               "commit_sha": os.environ["GITHUB_SHA"], "event": os.environ["GITHUB_EVENT_NAME"],
               "run_id": int(os.environ["GITHUB_RUN_ID"]), "run_attempt": int(os.environ["GITHUB_RUN_ATTEMPT"]),
               "repository": "OpenRAC/rac2-gc-decomp", "repository_id": 1400228215,
               "workflow_path": ".github/workflows/tests.yml", "workflow_sha256": before[".github/workflows/tests.yml"],
               "exporter_sha256": before["scripts/ci_export.py"], "inputs": before,
               "tools": tool_pins,
               "outputs": {name: sha(contained(repo, path).read_bytes()) for name, path in FILES.items()}}
    bundle = output / "verified-export"
    bundle.mkdir(exist_ok=True)
    for name, path in FILES.items():
        (bundle / name).write_bytes(contained(repo, path).read_bytes())
    (bundle / "receipt.json").write_bytes((json.dumps(receipt, sort_keys=True) + "\n").encode())
    return {"mode": "full", "checks": CHECKS, "full_validation": True, "bundle": str(bundle)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--mode", choices=("source", "full", "local"), required=True)
    parser.add_argument("--objdiff", type=Path)
    parser.add_argument("--event", type=Path)
    args = parser.parse_args()
    try:
        event = json.loads(args.event.read_bytes()) if args.event else None
        print(json.dumps(produce(ROOT, args.mode, args.objdiff, event), sort_keys=True))
    except Exception:
        print("CI export failed: validation", flush=True)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
