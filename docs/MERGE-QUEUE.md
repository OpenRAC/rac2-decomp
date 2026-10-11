# RAC2 merge queue

The [primary maintainer test route](MAINTAINER-TESTING.md) can avoid redundant
local/PR/main tool-suite runs for the authenticated primary maintainer. Every
merge group still runs the complete suite; other contributors retain the existing
workflow. Progress publication and matching gates are unchanged.

Maintainers activate the queue only after its workflows and trusted validator
are integrated into protected `RAC2`.

The merge queue tests an approved contribution against the current `RAC2`
branch before integrating it. When another PR merges first, a queued PR does
not need a topic-branch update merely because its base is older. GitHub prepares
a temporary combined commit and reruns the required checks on that commit.

## Submit and integrate

1. Author and validate your contribution against a current upstream base. Keep
   the actual validated base and proof provenance in the required PR description.
2. Obtain the required review and pass the PR checks. Maintainers use the merge
   queue action on GitHub, or `python scripts/merge_queue.py <number>
   --expected-head <sha>` when the PR is eligible. The maintained command pins
   the reviewed head and calls native queue admission directly; it does not
   enable classic auto-merge or fall back to a direct merge. Do not use an
   administrator override.
3. The queue runs `tests`, `SCUS_972.68 Progress`, and `PR description` on its
   temporary combined commit. A successful group merges automatically in order.
4. If the queue removes a failed contribution, inspect the failing run. Correct
   the contribution and its evidence, then submit it to the queue again.

The configured policy uses merge commits, one build at a time, one PR per group,
and `ALLGREEN` validation. Every group must pass; a green later contribution
cannot excuse an earlier failure. Required checks have a 60-minute response
timeout. Reviews remain required outside the configured review exemptions.
The existing review exemption uses GitHub's explicit `exempt` mode so queue
admission honors it. Named local-route accounts need separately configured
PR-only review/check/queue exemptions for a direct merge. Repository write access
alone cannot grant them. Integrity restrictions have no bypass actors: deletion,
non-fast-forward updates and unresolved discussions remain protected. Ordinary
queue submissions still run their required checks. Reservations remain required.

## Proofs and conflicts

The queue does not resolve conflicting source edits or regenerate byte-matching
proofs. Function reservations prevent duplicate ownership but do not prevent
conflicts in shared compilation units, catalogues, registers or generated reports.
If combined C or proof inputs change, follow the branch-update procedure and
refresh the affected complete-symbol and full-image evidence with your verified
private environment. Do not hand-edit hashes, counts or gate results to make a
queue check pass. Documentation-only changes do not require a game rebuild.

The description's validated base remains the base actually used by the author.
Queue checks are an additional combined-commit validation, not a claim that CI
reconstructed the game or independently established an ABI.

## Trusted description checks

Normal PR metadata is checked by the protected `pull_request_target` workflow,
which reports a commit status on the exact contribution head. Queue descriptions
use a separate read-only job named `PR description`. It loads the validator from
protected `RAC2` and uses read-only REST metadata to bind the live queue reference
and its two-parent merge commit to the current target and exactly one open PR.
It checks the active single-entry queue policy and validates current PR bodies
and changed-file lists as data. Missing or changed identities, malformed events
and unavailable API evidence fail the group.

The queue job has no status-writing permission and never executes contributor
Python with its API token. GitHub Actions reports its job result on the temporary
commit. Workflow changes still require code review; the format check is not a
technical approval of a contribution.

See GitHub's [merge queue guide](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/configuring-pull-request-merges/managing-a-merge-queue).

## Explicit local-validation exception

LP's approved accounts, `llesieur99` (immutable user ID 191315338) and
`ThorpenCodes` (immutable user ID 29800182), may explicitly request an exact-head
merge after completed local validation without waiting for remote full tests
or the native queue. The shared `scripts/local_validation_policy.py` allowlist
requires both ID and login. Thorpen must also have a current GitHub-verified
write, maintain or admin repository role:

```sh
python scripts/merge_queue.py <PR> --expected-head <SHA> --owner-local
```

This is an explicit local-validation assertion, not a GitHub proof of local
test results. The command refuses unnamed accounts, read-only delegated users,
changed heads and unavailable or inconsistent permission metadata. The automatic
CI policy remains primary-only: Thorpen's PR/push events do not automatically
select local trust. Bare `--maintainer-test` remains primary-only too.

Repository write access, token authorization and ruleset bypass are distinct.
The direct REST merge requires a token authorized for this repository (for a
fine-grained token, Contents write) and the account's configured PR-only
review/check/queue exemptions where applicable. The command grants no permissions,
changes no ruleset, and never uses an administrator override or queue fallback
after GitHub refuses it. Discussion resolution remains enforced.

See GitHub's [collaborator permission endpoint](https://docs.github.com/en/rest/collaborators/collaborators#get-repository-permissions-for-a-user)
and [merge endpoint](https://docs.github.com/en/rest/pulls/pulls#merge-a-pull-request).

Deletion, non-fast-forward restrictions and other contributorsâ€™ required
checks and queue remain enforced. Source matching acceptance stays byte-exact.
