"""Operator queue admission must be pinned and must never bypass GitHub rules."""
import copy
import importlib.util
import json
from pathlib import Path
import sys
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
spec = importlib.util.spec_from_file_location("merge_queue", Path(__file__).resolve().parents[1] / "scripts/merge_queue.py")
queue = importlib.util.module_from_spec(spec)
spec.loader.exec_module(queue)


class EnqueueTests(unittest.TestCase):
    def setUp(self):
        self.head = "a" * 40
        self.pr = {"number": 77, "state": "open", "draft": False, "node_id": "PR_test",
                   "head": {"sha": self.head}, "base": {"ref": "RAC2", "repo": {"full_name": queue.REPOSITORY}}}
        self.reply = {"data": {"enqueuePullRequest": {"mergeQueueEntry": {
            "id": "MQE_test", "position": 1, "pullRequest": {"number": 77, "headRefOid": self.head}}}}}

    def test_native_admission_pins_head_and_does_not_jump(self):
        with patch.object(queue, "gh_api", side_effect=[self.pr, self.reply]) as api:
            self.assertEqual(queue.enqueue(77, self.head)["position"], 1)
        self.assertEqual(api.call_args_list[1].args[:2], ("POST", "graphql"))
        self.assertEqual(api.call_args_list[1].args[2]["variables"], {"pr": "PR_test", "head": self.head})
        self.assertIn("expectedHeadOid:$head,jump:false", api.call_args_list[1].args[2]["query"])
        self.assertNotIn("mergePullRequest", api.call_args_list[1].args[2]["query"])

    def test_changed_head_stops_before_mutation(self):
        self.pr["head"]["sha"] = "b" * 40
        with patch.object(queue, "gh_api", return_value=self.pr) as api:
            with self.assertRaises(ValueError):
                queue.enqueue(77, self.head)
            self.assertEqual(api.call_count, 1)

    def test_foreign_closed_and_draft_prs_are_refused(self):
        for change in ("closed", "draft", "branch", "repository"):
            pr = copy.deepcopy(self.pr)
            if change == "closed":
                pr["state"] = "closed"
            elif change == "draft":
                pr["draft"] = True
            elif change == "branch":
                pr["base"]["ref"] = "other"
            else:
                pr["base"]["repo"]["full_name"] = "other/repo"
            with self.subTest(change=change), patch.object(queue, "gh_api", return_value=pr) as api:
                with self.assertRaises(ValueError):
                    queue.enqueue(77, self.head)
                self.assertEqual(api.call_count, 1)

    def test_refused_or_racing_mutation_has_no_merge_fallback(self):
        with patch.object(queue, "gh_api", side_effect=[self.pr, ValueError("Head changed")]) as api:
            with self.assertRaises(ValueError):
                queue.enqueue(77, self.head)
            self.assertEqual(api.call_count, 2)

    def test_mismatched_acknowledgement_is_not_success(self):
        self.reply["data"]["enqueuePullRequest"]["mergeQueueEntry"]["pullRequest"]["headRefOid"] = "b" * 40
        with patch.object(queue, "gh_api", side_effect=[self.pr, self.reply]):
            with self.assertRaises(ValueError):
                queue.enqueue(77, self.head)

    def test_invalid_arguments_do_not_call_api(self):
        with patch.object(queue, "gh_api") as api:
            for number, head in [(0, self.head), (77, "RAC2"), (True, self.head)]:
                with self.assertRaises(ValueError):
                    queue.enqueue(number, head)
            api.assert_not_called()

    def test_graphql_uses_structured_stdin_and_no_shell(self):
        completed = type("Result", (), {"returncode": 0, "stdout": json.dumps(self.reply)})()
        with patch.object(queue.subprocess, "run", return_value=completed) as run:
            queue.gh_api("POST", "graphql", {"query": queue.MUTATION, "variables": {"head": self.head}})
        self.assertEqual(run.call_args.args[0], ["gh", "api", "--method", "POST", "graphql", "--input", "-"])
        self.assertNotIn("shell", run.call_args.kwargs)
        self.assertEqual(json.loads(run.call_args.kwargs["input"])["variables"]["head"], self.head)


class OwnerLocalTests(unittest.TestCase):
    def setUp(self):
        self.head = "a" * 40
        self.actor = {"id": 29800182, "login": "ThorpenCodes"}
        self.permission = {"user": self.actor, "permission": "write"}
        self.pr = {"number": 77, "state": "open", "draft": False, "head": {"sha": self.head},
                   "base": {"ref": "RAC2", "repo": {"full_name": queue.REPOSITORY, "id": 1400228215}}}
        self.reply = {"merged": True, "sha": "b" * 40}

    def test_primary_keeps_existing_three_calls(self):
        actor = {"id": 191315338, "login": "llesieur99"}
        with patch.object(queue, "gh_api", side_effect=[actor, self.pr, self.reply]) as api:
            self.assertTrue(queue.merge_owner_local(77, self.head)["merged"])
        self.assertEqual(api.call_count, 3)

    def test_named_writer_merges_only_pinned_head_after_permission_check(self):
        with patch.object(queue, "gh_api", side_effect=[self.actor, self.permission, self.pr, self.reply]) as api:
            result = queue.merge_owner_local(77, self.head)
        self.assertFalse(result["local_tests_verified_by_github"])
        self.assertEqual(api.call_args_list[1].args,
                         ("GET", "repos/OpenRAC/rac2-gc-decomp/collaborators/ThorpenCodes/permission"))
        self.assertEqual(api.call_args_list[-1].args,
                         ("PUT", "repos/OpenRAC/rac2-gc-decomp/pulls/77/merge", {"sha": self.head, "merge_method": "merge"}))

    def test_named_read_only_user_cannot_attempt_merge(self):
        self.permission["permission"] = "read"
        with patch.object(queue, "gh_api", side_effect=[self.actor, self.permission]) as api, self.assertRaises(ValueError):
            queue.merge_owner_local(77, self.head)
        self.assertEqual(api.call_count, 2)

    def test_spoofed_identity_cannot_lookup_pr_or_merge(self):
        self.actor["id"] = 7
        with patch.object(queue, "gh_api", return_value=self.actor) as api, self.assertRaises(ValueError):
            queue.merge_owner_local(77, self.head)
        api.assert_called_once_with("GET", "user")

    def test_changed_head_refuses_mutation_after_role_check(self):
        self.pr["head"]["sha"] = "c" * 40
        with patch.object(queue, "gh_api", side_effect=[self.actor, self.permission, self.pr]) as api, self.assertRaises(ValueError):
            queue.merge_owner_local(77, self.head)
        self.assertEqual(api.call_count, 3)

    def test_github_ruleset_or_token_refusal_has_no_queue_fallback(self):
        with patch.object(queue, "gh_api", side_effect=[self.actor, self.permission, self.pr, ValueError("GitHub refused")]) as api, \
                self.assertRaisesRegex(ValueError, "GitHub refused"):
            queue.merge_owner_local(77, self.head)
        self.assertEqual(api.call_count, 4)


if __name__ == "__main__":
    unittest.main()
