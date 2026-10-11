"""Producer API contracts and workflow dependency guards, synthetic inputs only."""
import json
from pathlib import Path
import re
import sys
import tempfile
import types
import unittest
import os
from unittest.mock import Mock, patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import ci_export as export
import code_reuse_report as reuse_module
import maintainer_test_policy as policy

WIDE = {"schema": 1, "policy": "measured-wide-relation", "mask": "synthetic", "frontier": "synthetic",
        "controls": {}, "counts": {"groups": 0, "retained_groups": 0, "families": 0, "placements": 0},
        "groups": []}


class ExportTests(unittest.TestCase):
    def setUp(self):
        private = Path(__file__).resolve().parents[2]
        self.tmp = tempfile.TemporaryDirectory(dir=private)
        self.addCleanup(self.tmp.cleanup)
        self.repo = Path(self.tmp.name)
        (self.repo / "progress").mkdir()
        (self.repo / "config/function-catalog").mkdir(parents=True)
        (self.repo / "build/decomp").mkdir(parents=True)

    def test_source_route_validates_physical_once_and_never_heavy_exports(self):
        physical = {"measures": {"matchedCode": 12}}
        module = types.SimpleNamespace(verified_report=Mock(return_value=physical))
        with patch.dict(sys.modules, {"progress_module_report": module}), \
             patch.object(export, "inputs", return_value={"source": "a" * 64}), \
             patch.object(export, "source_metadata", return_value={"byte_identical_units": 1}) as source, \
             patch.object(export, "physical_display") as display, patch.object(export, "command") as command, \
             patch.object(export, "unique_and_reuse") as heavy:
            result = export.produce(self.repo, "source")
        self.assertEqual(module.verified_report.call_count, 1)
        self.assertEqual(source.call_count, 1)
        display.assert_called_once_with(self.repo, physical)
        heavy.assert_not_called()
        self.assertEqual(command.call_count, 1)  # Real registry view check, no unique/objdiff commands.
        self.assertEqual(command.call_args.args[1], sys.executable)
        args = command.call_args.args
        runtime = Path(args[args.index("--runtime") + 1])
        self.assertFalse(runtime.is_relative_to(self.repo.resolve()))
        self.assertFalse(result["full_validation"])
        self.assertFalse(result["artifacts_published"])

    def test_changed_input_during_source_precheck_refuses(self):
        module = types.SimpleNamespace(verified_report=Mock(return_value={"measures": {}}))
        with patch.dict(sys.modules, {"progress_module_report": module}), \
             patch.object(export, "inputs", side_effect=[{"a": "1"}, {"a": "2"}]), \
             patch.object(export, "source_metadata"), patch.object(export, "physical_display"), \
             patch.object(export, "command"), self.assertRaises(ValueError):
            export.produce(self.repo, "source")

    def fixture_analyses(self):
        encoded = lambda value: (json.dumps(value, sort_keys=True, separators=(",", ":")) + "\n").encode()
        primary = {"groups": [], "scope": "qualified", "measures": {"matchedCode": 12}}
        catalog, raw, credit = {"catalogue": "actual"}, b"catalogue", {("boot", 16, 12): "a" * 64}
        uq = types.SimpleNamespace(read_catalog=Mock(return_value=(catalog, raw)), load_current_credit=Mock(return_value=credit),
             current_boot_binding=Mock(return_value="binding"), generate=Mock(return_value=primary), digest=export.sha,
             encoded=encoded, objdiff=Mock(return_value={"version": 2}))
        reuse = types.SimpleNamespace(generate=Mock(return_value=({"metrics": {}}, [{"family": "proved"}])),
             authored_subset=Mock(return_value=({"count": 1}, [{"source": "src/example.c"}])),
             wide_groups=Mock(return_value=WIDE), wide_reference=reuse_module.wide_reference,
             families_payload=reuse_module.families_payload, compressed=reuse_module.compressed,
             digest=export.sha, snapshot=Mock(return_value={"source": "b" * 64}), encoded=encoded, POLICY="maintained-policy")
        summary = dict(primary, catalog_sha256=export.sha(raw))
        summary.pop("groups")
        (self.repo / "progress/unique-code-report.json").write_bytes(encoded(summary))
        families = reuse_module.compressed(encoded(reuse_module.families_payload(
            [{"family": "proved"}], [{"source": "src/example.c"}], WIDE)))
        report = {"metrics": {}, "authored_C_reuse_subset": {"count": 1}, "catalog_sha256": export.sha(raw),
                  "input_sha256": {"source": "b" * 64}, "wide_group_reference": reuse_module.wide_reference(WIDE),
                  "families_sha256": export.sha(families)}
        (self.repo / "progress/code-reuse-report.json").write_bytes(encoded(report))
        (self.repo / "progress/code-reuse-families.json.gz").write_bytes(families)
        return uq, reuse, catalog, credit, primary

    def test_unique_computed_once_and_reuse_receives_exact_same_qualified_primary(self):
        uq, reuse, catalog, credit, primary = self.fixture_analyses()
        with patch.dict(sys.modules, {"unique_code_report": uq, "code_reuse_report": reuse}):
            export.unique_and_reuse(self.repo, self.repo / "build/decomp")
        uq.generate.assert_called_once_with(catalog, credit, "binding")
        reuse.generate.assert_called_once_with(catalog, credit, primary, WIDE)
        reuse.wide_groups.assert_called_once_with(self.repo)
        self.assertTrue((self.repo / "build/decomp/unique-report.json").exists())

    def test_changed_measured_wide_relation_is_inside_the_compared_serialization(self):
        uq, reuse, *_ = self.fixture_analyses()
        reuse.wide_groups.return_value = dict(WIDE, policy="changed-wide-relation")
        with patch.dict(sys.modules, {"unique_code_report": uq, "code_reuse_report": reuse}), \
             self.assertRaisesRegex(ValueError, "reusable-code serialization differs"):
            export.unique_and_reuse(self.repo, self.repo / "build/decomp")

    def test_stale_summary_or_families_serialization_refuses(self):
        for name in ("unique-code-report.json", "code-reuse-report.json", "code-reuse-families.json.gz"):
            with self.subTest(name=name):
                uq, reuse, *_ = self.fixture_analyses()
                (self.repo / "progress" / name).write_bytes(b"changed metadata")
                with patch.dict(sys.modules, {"unique_code_report": uq, "code_reuse_report": reuse}), self.assertRaises(ValueError):
                    export.unique_and_reuse(self.repo, self.repo / "build/decomp")

    def test_workflow_has_one_producer_literal_full_queue_and_failure_dependent_required_jobs(self):
        text = (Path(__file__).resolve().parents[1] / ".github/workflows/tests.yml").read_text()
        self.assertEqual(text.count("run: python -m unittest discover -s tests -v"), 1)
        self.assertEqual(text.count("run: python scripts/ci_export.py --mode full"), 1)
        self.assertIn("if: github.event_name == 'merge_group' || needs.policy.outputs.mode == 'full'", text)
        self.assertIn("ref: ${{ github.event.pull_request.base.sha || github.sha }}", text)
        self.assertNotIn("statuses: write", text)
        self.assertNotIn("actions: write", text)
        for key in ("tests", "progress"):
            section = re.split(r"(?m)^  [a-z_]+:\s*$", text.split("\n  " + key + ":\n", 1)[1], 1)[0]
            self.assertIn("needs: [policy, validation]", section)
            self.assertIn("if: always()", section)
            self.assertIn('test "$POLICY_RESULT" = success', section)
            self.assertIn('test "$VALIDATION_RESULT" = success', section)
        self.assertIn("name: SCUS_972.68 Progress", text)
        self.assertEqual(policy.FULL_JOB, "validation")

    def test_manual_dispatch_preserves_full_validation_only(self):
        text = (Path(__file__).resolve().parents[1] / ".github/workflows/tests.yml").read_text()
        self.assertIn("\n  workflow_dispatch:\n", text)
        self.assertIn("workflow_dispatch:full)", text)
        self.assertNotIn("workflow_dispatch:targeted", text)
        self.assertNotIn("workflow_dispatch:reuse", text)
        api = Mock()
        result = policy.select("workflow_dispatch", {"repository": {"id": policy.REPOSITORY_ID,
                               "full_name": policy.REPOSITORY}}, "a" * 40, api)
        self.assertEqual(result["mode"], "full")
        api.get.assert_not_called()

    def local_fixture(self):
        metrics = {"physical_total_bytes": 100, "physical_matched_bytes": 12,
                   "unique_total_bytes": 80, "unique_matched_bytes": 10}
        encode = lambda value: (json.dumps(value, sort_keys=True) + "\n").encode()
        catalog = {"input_pins": [{"path": "src/example.c", "sha256": "a" * 64}],
                   "function_chunks": [{"path": "chunk.gz", "sha256": "b" * 64}]}
        catalog_raw = encode(catalog)
        summary = {"metrics": metrics, "catalog_sha256": export.sha(catalog_raw), "coverage": {"excluded_vu_bytes": 0}}
        families = b"committed-family-snapshot"
        reuse = {"primary_reference": {"metrics": metrics}, "catalog_sha256": export.sha(catalog_raw),
                 "input_sha256": {"src/example.c": "a" * 64}, "families_sha256": export.sha(families)}
        payloads = {"config/function-catalog/catalog.json": catalog_raw,
                    "progress/unique-code-report.json": encode(summary),
                    "progress/code-reuse-report.json": encode(reuse),
                    "progress/code-reuse-families.json.gz": families,
                    "progress/source-inventory.json": b"{}\n"}
        for relative, data in payloads.items():
            (self.repo / relative).write_bytes(data)
        before = {relative: export.sha(data) for relative, data in payloads.items()}
        before.update({"src/example.c": "a" * 64, "config/function-catalog/chunk.gz": "b" * 64})
        event = {"repository": {"id": policy.REPOSITORY_ID, "full_name": policy.REPOSITORY},
                 "sender": {"id": policy.MAINTAINER_ID, "login": policy.MAINTAINER_LOGIN},
                 "ref": "refs/heads/RAC2", "after": "a" * 40}
        modules = {"progress_module_report": types.SimpleNamespace(verified_report=Mock(return_value={
                       "measures": {"totalCode": "100", "matchedCode": "12"}})),
                   "progress_modules": types.SimpleNamespace(group_report=Mock(return_value=({"version": 2}, {}))),
                   "decomp_report": types.SimpleNamespace(measures=lambda total, data, units, matched, complete:
                       {"totalCode": str(total), "matchedCode": str(matched), "totalUnits": units, "completeUnits": complete})}
        return before, event, modules

    def test_local_publication_trusts_committed_snapshots_without_full_receipt_or_heavy_scan(self):
        before, event, modules = self.local_fixture()
        original_summary = (self.repo / "progress/unique-code-report.json").read_bytes()
        with patch.dict(sys.modules, modules), patch.object(export, "inputs", return_value=before), \
             patch.object(export, "source_metadata", return_value={"byte_identical_units": 1}), \
             patch.object(export, "physical_display"), patch.object(export, "unique_and_reuse") as heavy, \
             patch.object(export, "command") as command, patch.object(export, "tools") as tools, \
             patch.dict(os.environ, {"GITHUB_EVENT_NAME": "push", "GITHUB_SHA": "a" * 40}):
            result = export.produce(self.repo, "local", event=event)
        heavy.assert_not_called(); command.assert_not_called(); tools.assert_not_called()
        self.assertFalse(result["full_validation"])
        self.assertTrue(result["local_validation_trusted"])
        self.assertEqual((self.repo / "build/decomp/unique-summary.json").read_bytes(), original_summary)
        provenance = json.loads((self.repo / "build/decomp/local-provenance.json").read_bytes())
        self.assertEqual(provenance["kind"], "owner-local-report-publication")
        self.assertFalse(provenance["remote_full_validation"])
        self.assertFalse(provenance["local_validation_automatically_verified"])
        self.assertFalse((self.repo / "build/decomp/verified-export/receipt.json").exists())
        unique = json.loads((self.repo / "build/decomp/unique-report.json").read_bytes())
        self.assertEqual(unique["measures"]["matchedCode"], "10")
        self.assertEqual(unique["measures"]["completeUnits"], 0)

    def test_local_wide_receipt_pin_is_checked_without_rebuilding_relation(self):
        before, event, modules = self.local_fixture()
        receipt = reuse_module.WIDE_RECEIPT
        data = reuse_module.wide_bytes(WIDE)
        (self.repo / receipt).write_bytes(data)
        before[receipt] = export.sha(data)
        report_path = self.repo / "progress/code-reuse-report.json"
        report = json.loads(report_path.read_bytes())
        report["input_sha256"][receipt] = before[receipt]
        report["wide_group_reference"] = reuse_module.wide_reference(WIDE)
        report_path.write_text(json.dumps(report), encoding="utf8")
        before["progress/code-reuse-report.json"] = export.sha(report_path.read_bytes())
        with patch.dict(sys.modules, modules), patch.object(export, "inputs", return_value=before), \
             patch.object(export, "source_metadata", return_value={}), patch.object(export, "physical_display"), \
             patch.object(export, "unique_and_reuse") as heavy, \
             patch.object(reuse_module, "wide_groups") as rebuild, \
             patch.dict(os.environ, {"GITHUB_EVENT_NAME": "push", "GITHUB_SHA": "a" * 40}):
            result = export.produce(self.repo, "local", event=event)
            self.assertFalse(result["fresh_unique_reuse_classification"])
            before[receipt] = "c" * 64
            with self.assertRaisesRegex(ValueError, "input snapshot changed"):
                export.produce(self.repo, "local", event=event)
        heavy.assert_not_called()
        rebuild.assert_not_called()
        provenance = json.loads((self.repo / "build/decomp/local-provenance.json").read_bytes())
        self.assertEqual(provenance["inputs"][receipt], export.sha(data))
        self.assertFalse(provenance["fresh_unique_reuse_classification"])

    def test_local_stale_pins_catalogue_families_or_physical_metrics_fail(self):
        for kind in ("input", "catalogue", "families", "chunk", "physical", "drift"):
            with self.subTest(kind=kind):
                before, event, modules = self.local_fixture()
                if kind == "input": before["src/example.c"] = "c" * 64
                elif kind == "catalogue": before["config/function-catalog/catalog.json"] = "c" * 64
                elif kind == "families": before["progress/code-reuse-families.json.gz"] = "c" * 64
                elif kind == "chunk": before["config/function-catalog/chunk.gz"] = "c" * 64
                elif kind == "physical": modules["progress_module_report"].verified_report.return_value["measures"]["matchedCode"] = "13"
                after = dict(before); after["drift"] = "changed"
                with patch.dict(sys.modules, modules), \
                     patch.object(export, "inputs", side_effect=[before, after if kind == "drift" else before]), \
                     patch.object(export, "source_metadata"), patch.object(export, "physical_display"), \
                     patch.dict(os.environ, {"GITHUB_EVENT_NAME": "push", "GITHUB_SHA": "a" * 40}), \
                     self.assertRaises(ValueError):
                    export.produce(self.repo, "local", event=event)

    def test_local_publication_rechecks_push_identity_and_rejects_pr_manual_queue(self):
        before, event, modules = self.local_fixture()
        for event_name in ("pull_request", "workflow_dispatch", "merge_group", "push"):
            with self.subTest(event_name=event_name):
                if event_name == "push": event["sender"]["id"] = 1
                with patch.object(export, "inputs", return_value=before), \
                     patch.object(export, "source_metadata") as source, \
                     patch.dict(os.environ, {"GITHUB_EVENT_NAME": event_name, "GITHUB_SHA": "a" * 40}), \
                     self.assertRaises(ValueError):
                    export.produce(self.repo, "local", event=event)
                source.assert_not_called()

    def test_local_workflow_skips_remote_tests_and_preserves_publisher_artifact_names(self):
        text = (Path(__file__).resolve().parents[1] / ".github/workflows/tests.yml").read_text()
        self.assertNotIn("run: python scripts/maintainer_tests.py", text)
        self.assertNotIn("pull_request:targeted", text)
        self.assertIn("pull_request:local|push:full|push:local|push:reuse", text)
        self.assertIn('run: python scripts/ci_export.py --mode local --event "$GITHUB_EVENT_PATH"', text)
        for artifact in ("SCUS_972.68_report", "SCUS_972.68_source-modules", "SCUS_972.68_authored_source",
                         "SCUS_972.68-unique_report", "SCUS_972.68_unique-metrics", "SCUS_972.68_code-reuse"):
            self.assertIn("name: " + artifact, text)

    def test_checkout_guard_requires_exact_head_and_both_index_worktree_clean(self):
        sha = "a" * 40
        with patch.dict("os.environ", {"GITHUB_SHA": sha}), \
             patch.object(export.subprocess, "check_output", return_value=(sha + "\n").encode()), \
             patch.object(export.subprocess, "run", return_value=types.SimpleNamespace(returncode=0)) as run:
            export.checkout_guard(self.repo)
            self.assertEqual(run.call_count, 2)
            self.assertIn("--cached", run.call_args_list[1].args[0])
        for codes in ((1, 0), (0, 1), (0, 128)):
            with patch.dict("os.environ", {"GITHUB_SHA": sha}), \
                 patch.object(export.subprocess, "check_output", return_value=sha.encode()), \
                 patch.object(export.subprocess, "run", side_effect=[types.SimpleNamespace(returncode=c) for c in codes]), \
                 self.assertRaises(ValueError):
                export.checkout_guard(self.repo)

    def test_wrong_head_or_missing_context_cannot_export(self):
        for expected, head in (("", "a" * 40), ("not-a-sha", "a" * 40), ("a" * 40, "b" * 40)):
            with patch.dict("os.environ", {"GITHUB_SHA": expected}), \
                 patch.object(export.subprocess, "check_output", return_value=head.encode()), \
                 self.assertRaises(ValueError):
                export.checkout_guard(self.repo)

    def test_dirty_post_suite_tree_refuses_before_physical_validation(self):
        with patch.object(export, "checkout_guard", side_effect=ValueError("post-suite dirty")), \
             patch.object(export, "source_metadata") as source, self.assertRaises(ValueError):
            export.produce(self.repo, "source")
        source.assert_not_called()

    def test_inside_repository_runner_temp_is_refused_before_views_execution(self):
        module = types.SimpleNamespace(verified_report=Mock(return_value={"measures": {}}))
        with patch.dict(sys.modules, {"progress_module_report": module}), \
             patch.dict(os.environ, {"RUNNER_TEMP": str(self.repo)}), \
             patch.object(export, "inputs", return_value={"source": "a" * 64}), \
             patch.object(export, "source_metadata"), patch.object(export, "physical_display"), \
             patch.object(export, "command") as command, self.assertRaisesRegex(ValueError, "outside"):
            export.produce(self.repo, "source")
        command.assert_not_called()

    def test_full_route_uses_external_views_runtime_and_same_interpreter(self):
        physical = {"measures": {}}
        modules = {"progress_module_report": types.SimpleNamespace(verified_report=Mock(return_value=physical)),
                   "source_layout": types.SimpleNamespace(verify=Mock()),
                   "progress_modules": types.SimpleNamespace(group_report=Mock(return_value=({"version": 2}, {}))),
                   "decomp_report": types.SimpleNamespace(measures=lambda *args: {})}
        for relative in export.FILES.values():
            path = self.repo / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(b"{}\n")
        binary = self.repo / "objdiff"
        binary.write_bytes(b"qualified-test-binary")
        original_sha = export.sha
        def digest(body):
            return "c8290281e82114bcc1a06ff73061110d3902a177822e750337de2537188e358f" if body == b"qualified-test-binary" else original_sha(body)
        frozen = {".github/workflows/tests.yml": "b" * 64, "scripts/ci_export.py": "c" * 64}
        with patch.dict(sys.modules, modules), patch.object(export, "inputs", return_value=frozen), \
             patch.object(export, "source_metadata"), patch.object(export, "physical_display"), \
             patch.object(export, "tools", return_value={"qualified": "d" * 64}), patch.object(export, "sha", side_effect=digest), \
             patch.object(export, "unique_and_reuse") as analysis, patch.object(export, "command") as command, \
             patch.dict(os.environ, {"GITHUB_SHA": "a" * 40, "GITHUB_EVENT_NAME": "merge_group",
                                    "GITHUB_RUN_ID": "50", "GITHUB_RUN_ATTEMPT": "1"}):
            result = export.produce(self.repo, "full", binary)
        self.assertTrue(result["full_validation"])
        analysis.assert_called_once()
        modules["source_layout"].verify.assert_called_once_with(self.repo, self.repo)
        calls = [value.args for value in command.call_args_list]
        runtime = Path(calls[0][calls[0].index("--runtime") + 1])
        self.assertFalse(runtime.is_relative_to(self.repo.resolve()))
        python_calls = [args for args in calls if args[1] != str(binary)]
        self.assertEqual(len(python_calls), 2)
        self.assertTrue(all(args[1] == sys.executable for args in python_calls))


if __name__ == "__main__": unittest.main()
