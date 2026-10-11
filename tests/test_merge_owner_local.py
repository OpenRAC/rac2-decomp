import copy
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import merge_queue


class OwnerLocalMergeTests(unittest.TestCase):
    def setUp(self):
        self.head = "a" * 40
        self.actor = {"id": 191315338, "login": "llesieur99"}
        self.pr = {"number": 1, "state": "open", "draft": False,
                   "base": {"ref": "RAC2", "repo": {"id": 1400228215, "full_name": merge_queue.REPOSITORY}},
                   "head": {"sha": self.head}}
        self.calls = []

    def api(self, method, endpoint, payload=None):
        self.calls.append((method, endpoint, payload))
        if endpoint == "user": return self.actor
        if method == "GET": return self.pr
        return {"merged": True, "sha": "b" * 40}

    def test_exact_owner_head_merges_with_expected_sha(self):
        with patch.object(merge_queue, "gh_api", self.api):
            result = merge_queue.merge_owner_local(1, self.head)
        self.assertTrue(result["merged"])
        self.assertFalse(result["local_tests_verified_by_github"])
        self.assertEqual(self.calls[-1], ("PUT", "repos/" + merge_queue.REPOSITORY + "/pulls/1/merge",
                                        {"sha": self.head, "merge_method": "merge"}))

    def test_wrong_actor_never_mutates(self):
        for actor in ({"id": 1, "login": "llesieur99"}, {"id": 191315338, "login": "other"}):
            self.actor = actor
            with patch.object(merge_queue, "gh_api", self.api), self.assertRaises(ValueError):
                merge_queue.merge_owner_local(1, self.head)
        self.assertFalse(any(method == "PUT" for method, _, _ in self.calls))

    def test_changed_head_draft_or_wrong_base_never_mutates(self):
        original = copy.deepcopy(self.pr)
        for change in ("head", "draft", "repo", "branch"):
            self.pr = copy.deepcopy(original)
            if change == "head": self.pr["head"]["sha"] = "c" * 40
            if change == "draft": self.pr["draft"] = True
            if change == "repo": self.pr["base"]["repo"]["id"] = 1
            if change == "branch": self.pr["base"]["ref"] = "other"
            with patch.object(merge_queue, "gh_api", self.api), self.assertRaises(ValueError):
                merge_queue.merge_owner_local(1, self.head)
        self.assertFalse(any(method == "PUT" for method, _, _ in self.calls))

    def test_refused_merge_is_not_reported_success(self):
        with patch.object(merge_queue, "gh_api", side_effect=[self.actor, self.pr, {"merged": False}]), self.assertRaises(ValueError):
            merge_queue.merge_owner_local(1, self.head)

    def test_invalid_pin_never_calls_github(self):
        with patch.object(merge_queue, "gh_api") as api, self.assertRaises(ValueError):
            merge_queue.merge_owner_local(1, "bad")
        api.assert_not_called()
