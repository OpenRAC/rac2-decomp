"""Enqueue a pinned RAC2 PR through GitHub's native queue; never merge directly."""
import argparse
import json
import re
import subprocess
import sys

REPOSITORY = "OpenRAC/rac2-gc-decomp"
MUTATION = """mutation($pr:ID!,$head:GitObjectID!) {
  enqueuePullRequest(input:{pullRequestId:$pr,expectedHeadOid:$head,jump:false}) {
    mergeQueueEntry { id position pullRequest { number headRefOid } }
  }
}"""


def gh_api(method, endpoint, payload=None):
    command = ["gh", "api", "--method", method, endpoint]
    if payload is not None:
        command += ["--input", "-"]
    result = subprocess.run(command, input=json.dumps(payload) if payload is not None else None,
                            capture_output=True, text=True, timeout=90, check=False)
    if result.returncode:
        raise ValueError("GitHub refused queue admission; inspect reviews, checks, queue policy and authentication")
    response = json.loads(result.stdout)
    if isinstance(response, dict) and response.get("errors"):
        raise ValueError("GitHub refused queue admission; no direct-merge fallback")
    return response


def enqueue(number, expected_head):
    if type(number) is not int or number < 1 or not re.fullmatch(r"[0-9a-f]{40}", expected_head):
        raise ValueError("A positive PR number and its exact 40-character head SHA are required")
    pr = gh_api("GET", f"repos/{REPOSITORY}/pulls/{number}")
    if (pr["number"] != number or pr["state"] != "open" or pr["draft"] is not False
            or pr["base"]["ref"] != "RAC2" or pr["base"]["repo"]["full_name"] != REPOSITORY
            or pr["head"]["sha"] != expected_head or not isinstance(pr["node_id"], str)):
        raise ValueError("The current open RAC2 PR does not match the reviewed head")
    reply = gh_api("POST", "graphql", {"query": MUTATION,
                   "variables": {"pr": pr["node_id"], "head": expected_head}})
    entry = reply["data"]["enqueuePullRequest"]["mergeQueueEntry"]
    if (not isinstance(entry["id"], str) or not entry["id"]
            or type(entry["position"]) is not int or entry["position"] < 1
            or entry["pullRequest"]["number"] != number
            or entry["pullRequest"]["headRefOid"] != expected_head):
        raise ValueError("Queue admission was not acknowledged for this exact head; inspect before retrying")
    return {"queued": True, "pr": number, "head": expected_head, "position": entry["position"]}


def merge_owner_local(number, expected_head):
    """Explicit local-validation route; only the authenticated owner can use it."""
    if type(number) is not int or number < 1 or not re.fullmatch(r"[0-9a-f]{40}", expected_head):
        raise ValueError("A positive PR number and its exact 40-character head SHA are required")
    actor = gh_api("GET", "user")
    if actor.get("id") != 191315338 or actor.get("login") != "llesieur99":
        raise ValueError("The owner-local route requires the authenticated primary maintainer")
    pr = gh_api("GET", f"repos/{REPOSITORY}/pulls/{number}")
    if (pr["number"] != number or pr["state"] != "open" or pr["draft"] is not False
            or pr["base"]["ref"] != "RAC2" or pr["base"]["repo"]["full_name"] != REPOSITORY
            or pr["base"]["repo"]["id"] != 1400228215 or pr["head"]["sha"] != expected_head):
        raise ValueError("The current open RAC2 PR does not match the locally validated head")
    reply = gh_api("PUT", f"repos/{REPOSITORY}/pulls/{number}/merge",
                   {"sha": expected_head, "merge_method": "merge"})
    if reply.get("merged") is not True or not re.fullmatch(r"[0-9a-f]{40}", reply.get("sha", "")):
        raise ValueError("GitHub did not acknowledge the exact-head owner merge")
    return {"merged": True, "pr": number, "head": expected_head,
            "commit": reply["sha"], "validation": "owner-local", "local_tests_verified_by_github": False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("pr", type=int)
    parser.add_argument("--expected-head", required=True)
    parser.add_argument("--owner-local", action="store_true",
                        help="Owner only: merge this exact head after completed local validation")
    args = parser.parse_args()
    try:
        print(json.dumps(merge_owner_local(args.pr, args.expected_head) if args.owner_local
                         else enqueue(args.pr, args.expected_head)))
        return 0
    except (ValueError, KeyError, TypeError, OSError, subprocess.SubprocessError) as error:
        # Fixed local ValueErrors are safe; never print API payloads or credentials.
        print(str(error) if type(error) is ValueError else "Queue admission failed; inspect GitHub before retrying", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
