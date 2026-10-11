"""Explicit local trust is named, authenticated and separate from CI selection."""
import copy
from pathlib import Path
import sys
import unittest
from unittest.mock import Mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import local_validation_policy as local
import maintainer_test_policy as ci

PRIMARY = {"id": 191315338, "login": "llesieur99"}
DELEGATE = {"id": 29800182, "login": "ThorpenCodes"}


class LocalValidationPolicyTests(unittest.TestCase):
    def test_primary_retains_existing_authentication_without_extra_api(self):
        reader = Mock()
        self.assertEqual(local.approve(PRIMARY, reader), PRIMARY)
        reader.assert_not_called()

    def test_delegated_write_maintain_admin_require_live_permission_metadata(self):
        for permission in ("write", "maintain", "admin"):
            reader = Mock(return_value={"user": DELEGATE, "permission": permission})
            self.assertEqual(local.approve(DELEGATE, reader), DELEGATE)
            reader.assert_called_once_with(
                "repos/OpenRAC/rac2-gc-decomp/collaborators/ThorpenCodes/permission")

    def test_read_triage_unknown_roles_cannot_grant_local_route(self):
        for permission in ("read", "triage", "none", "push", None, True, []):
            with self.subTest(permission=permission), self.assertRaises(ValueError):
                local.approve(DELEGATE, Mock(return_value={"user": DELEGATE, "permission": permission}))

    def test_name_id_spoofs_and_unnamed_writers_are_refused_before_permission_lookup(self):
        for user in ({"id": 1, "login": "ThorpenCodes"}, {"id": 29800182, "login": "fake"},
                     {"id": "29800182", "login": "ThorpenCodes"}, {"id": 191315338.0, "login": "llesieur99"},
                     {"id": 7, "login": "AnotherWriter"}, None):
            reader = Mock()
            with self.subTest(user=user), self.assertRaises(ValueError):
                local.approve(user, reader)
            reader.assert_not_called()

    def test_permission_response_must_identify_same_authenticated_user(self):
        for user in (PRIMARY, {"id": 1, "login": "ThorpenCodes"},
                     {"id": 29800182, "login": "fake"}, None):
            with self.subTest(user=user), self.assertRaises(ValueError):
                local.approve(DELEGATE, Mock(return_value={"user": user, "permission": "admin"}))
        with self.assertRaises(ValueError):
            local.approve(DELEGATE, Mock(return_value={}))

    def test_permission_api_failure_is_not_a_fallback(self):
        with self.assertRaisesRegex(ValueError, "unavailable"):
            local.approve(DELEGATE, Mock(side_effect=ValueError("unavailable")))

    def test_automatic_ci_identity_stays_primary_only(self):
        self.assertTrue(ci.identity(PRIMARY))
        self.assertFalse(ci.identity(DELEGATE))
        event = {"repository": {"id": ci.REPOSITORY_ID, "full_name": ci.REPOSITORY},
                 "sender": copy.deepcopy(DELEGATE), "ref": "refs/heads/RAC2", "after": "a" * 40}
        self.assertFalse(ci.owner_local_push("push", event, "a" * 40))


if __name__ == "__main__":
    unittest.main()
