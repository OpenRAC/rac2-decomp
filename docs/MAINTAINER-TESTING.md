# Primary maintainer local validation route

The repository owner can use locally validated work without repeating remote
heavy or focused tool tests, and merge directly through the owner-only ruleset
exemptions. Other contributors keep the existing full checks, review and merge
queue. Matching credit and local byte-exact acceptance gates are unchanged.

| Contribution | Local preparation | PR tool tests | Merge-group tool tests | Main tool tests |
| --- | --- | --- | --- | --- |
| Other contributors | Existing full-suite workflow | Full | Full, always | Existing full or authenticated exact-queue reuse route |
| Authenticated primary maintainer | Explicit relevant local tests and applicable matching gates | Local trust; no remote tool tests | Full if a merge group is used | Local trust when the owner is the exact push sender |

The PR selector runs from the protected base commit and authenticates the current
PR through GitHub's API: owner ID `191315338`, login `llesieur99`, head/base
repository ID `1400228215` (`OpenRAC/rac2-gc-decomp`), open PR, base branch `RAC2`,
and exact valid head/base SHAs matching the event. Labels, PR text, Git author
names, and fork branch names cannot grant this route. An older base selector
can still apply the older route during rollout.

For a main push, GitHub's event must identify the same repository and immutable
sender ID/login, `refs/heads/RAC2`, and valid `after` equal to `GITHUB_SHA`. The
owner can merge another contributor's locally validated PR; that contributor's
PR checks remain full. The owner push decision does not wait for PR association
or require a previous queue run. Other push senders retain the existing full or
verified exact-SHA queue reuse behavior. Unknown events, invalid identities,
API errors and stale PR heads cannot grant local trust.

## Local preparation and direct merge

Use the repository environment and actual affected maintained test modules,
including tests for dependency changes. For example:

```sh
python scripts/maintainer_tests.py --test test_progress_modules --test test_decomp_report_cli
```

The maintained local command authenticates the owner and runs the explicit
modules. This is focused local validation, not a full-suite receipt. Changes to
C, declarations, placements, compiler or other hashed matching inputs still
require their fresh source/object/integration/reference gates. Documentation or
presentation changes with unchanged matching inputs do not require a game build.

The existing campaign finalizer remains available with repeated
`--maintainer-test` selections and its mandatory focused policy/finalizer tests.
Its historical plan fields do not themselves prove that a remote queue ran.
The owner-only direct merge command is documented in `docs/MERGE-QUEUE.md`.
The local route relies on the owner's judgement that the applicable tests and
matching gates were completed; GitHub does not automatically verify that claim.

## CI publication and provenance

On owner PRs, the shared validation records mode `local` and explicit local
validation trust. It runs neither remote discovery nor focused tool tests.
The required `tests` and `SCUS_972.68 Progress` consumers still fail if policy or
shared validation is missing, failed, cancelled or skipped. They confirm routing
and publication, not remote tool-test execution on this route.

On owner main pushes, `ci_export.py --mode local` rechecks the event identity,
exact checkout SHA, and clean tracked worktree/index. It validates current source
hashes/rendered compilation units, existing physical proof metadata/display,
committed catalogue/input/chunk/family hashes, and equality between the unique
summary's physical totals and current physical proof. It groups the same physical
report and copies committed unique summary and reuse metadata. It does not run
remote tool tests, fresh unique/reuse classification, queue reuse, or objdiff.
Stale metadata fails this local publication route without a hidden full-suite
fallback.

The original public artifact names remain available. The physical report keeps
its original grouping and totals. On the local route only, the unique objdiff
view contains a single aggregate from committed conservative unique byte
metrics, with no per-class regeneration or claimed matched-function count.
The exact committed summary and reuse-family bytes accompany it. Full, manual
and merge-group exports retain the original granular unique report.

`SCUS_972.68_local-provenance` records the exact commit, immutable actor,
tracked-input and output hashes, mode `local`, local validation trust, absence of
automatic local verification, absence of remote full tests and absence of fresh
unique/reuse classification. It is a local report publication receipt and is
never a `verified-ci-full-export` or a fabricated merge-queue receipt.

The merge-group workflow keeps literal unconditional complete discovery and
full exports. Manual `workflow_dispatch` always runs full validation. Non-owner
PRs remain full. The existing non-owner main fallback and exact-queue artifact
verification remain in place; their reviewed workflow/exporter hashes must be
updated whenever those literal bytes change. Workflow token permissions remain
read-only. Actual external decomp.dev ingestion must be verified separately.
