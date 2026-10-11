"""Explicit --owner-local authorization; independent of automatic CI selection.

Only LP's named users may assert completed local validation. A delegated user
also needs a current GitHub repository write role. GitHub enforces token scopes
and branch/ruleset restrictions when a merge is requested.
"""
REPOSITORY = "OpenRAC/rac2-gc-decomp"
REPOSITORY_ID = 1400228215
PRIMARY_ID = 191315338
LOCAL_USERS = {PRIMARY_ID: "llesieur99", 29800182: "ThorpenCodes"}
WRITE_PERMISSIONS = frozenset(("write", "maintain", "admin"))


def identity(user):
    return (isinstance(user, dict) and type(user.get("id")) is int
            and user.get("id") in LOCAL_USERS
            and user.get("login") == LOCAL_USERS[user["id"]])


def approve(user, permission_reader):
    """Validate authenticated identity and delegated user's effective role.

    The primary maintainer retains the existing trusted route. The reader must
    GET GitHub's collaborator permission endpoint for the exact repository and
    authenticated login. Absent, mismatched or insufficient evidence refuses
    the delegated route before any preparation or merge mutation.
    """
    if not identity(user):
        raise ValueError("The owner-local route requires an explicitly approved authenticated account")
    actor = {"id": user["id"], "login": user["login"]}
    if actor["id"] == PRIMARY_ID:
        return actor
    reply = permission_reader(f"repos/{REPOSITORY}/collaborators/{actor['login']}/permission")
    if (not isinstance(reply, dict) or not identity(reply.get("user"))
            or reply["user"]["id"] != actor["id"] or reply["user"]["login"] != actor["login"]
            or type(reply.get("permission")) is not str or reply["permission"] not in WRITE_PERMISSIONS):
        raise ValueError("Delegated owner-local validation requires a verified write, maintain or admin repository role")
    return actor
