/* 1 November 2026 (closer a3): 1944/1944, 28 words, profile -O2 -G8 -ffunction-sections -frac2-hazard-labels -g
 * -frac2-zero-ti-por. From 94 with: no pointer locals for state + 0x10 / + 0x20 (PRE's reaching copies are the two
 * spilled slots 0x11C and 0x120, and s0 is reload's register for the first, inherited over the three calls), plain
 * locals for contacts/kind/triggered (the old stack struct was a stand-in for spilled pseudos), hoisted 5 now gets
 * $s6 once &rotation stops outranking it, D_0018C0B0 NOT_SDA, (idx + table)->field for retail's mult-then-index addu.
 * Left: (1) the 12-byte copy: retail's %hi is v1, so ptr gets a1 and reload's scratches v0/a0; local-alloc's fake_death
 * sends %hi off v0 only if a local in v0 follows the copy, and here the load of state + 0x24 waits on the copy while
 * the range load doesn't (a fixed scalar symbol against a frame store), so the range load sits in between. (2) the
 * range: retail stores it before 1.5's li.s, so 1.5 gets f0; here 1.5 goes first. (3) spill reloads a2/a3 for a1/a2. */
/* GPT-6.1 Sol high, task v1293, 29 October 2026.
 * Best check: 1944/1944 bytes, 0/27 USA v1.01 placements; first mismatch
 * +0xB0. Compile alone with game -O2 -G8 -ffunction-sections; declarations
 * follow below. The retail 0x190 frame is reproduced. No linked build or
 * runtime validation was performed; the original INCLUDE_ASM is restored.
 *
 * The incoming draft rechecked at 1944 bytes, 0/27, first mismatch +0xB8.
 * Independent diagnostic comparison found 334 non-relocation instruction
 * differences there versus 80 here (390 versus 95 when relocation opcode/
 * register bits are included). These counts ignore relocated values, are only
 * diagnostics, and do not imply a match or validated bindings.
 *
 * Separate search-loop variables, retail branch orientation, separate impact
 * notification calls, and a response-local struct recover the measured
 * contacts/kind/trigger/rotation/timer stack slots at +0x110 through +0x120.
 * A short-lived rotation pointer retains the initial three-call register.
 * The copied constant is three integer ignore-list entries, not float XYZ:
 * retail level 00 words are 0, 3604, 3684. The strength table has stride 0xE0
 * and a float at +0x74. All vector transfers use memory-clobbering qcopy.
 *
 * Eighteen checker invocations (one syntax correction) and two allocator
 * diagnostics: ordinary late scalar locals gave 1936 bytes/0x180 frame;
 * grouping response locals restored 1944/0x190. Scalar/array/builtin copies
 * did not recover the ignore-copy registers. An inline query initializer
 * produced 1952 bytes; early scale calculation hoisted FP work too far.
 * Remaining: ignore-list copy registers, query range/scale FP allocation,
 * point/best-index allocation, call setup and later stores/branches. Reopen
 * with an evidenced query initializer or allocator-lifetime improvement.
 */
#include "common.h"

#include "include_asm.h"

typedef int CollisionQuad __attribute__((mode(TI)));
typedef union { CollisionQuad q; float f[4]; } CollisionVector;
typedef struct { int ignored[3]; } CollisionShape;
typedef struct {
    CollisionVector previous, position, velocity;
    char *owner;
    CollisionShape *shape;
    int kind;
    float range, scale, radius;
    int flags, reserved;
    int result;
    int result_kind;
    int extra;
} CollisionQuery;
typedef struct {
    CollisionVector force;
    char *owner;
    int flags;
    unsigned char kind, enabled;
    short object_class;
    float strength;
    int count;
} CollisionImpact;
typedef union {
    struct { CollisionVector point, work, delta, difference, projection, perpendicular; } math;
    CollisionImpact impact;
} CollisionWorkspace;

extern CollisionShape D_L00_001B0FC8;
extern float D_L00_001B0FA0 __attribute__((sda));
extern float D_L00_001B0FAC __attribute__((sda));
extern float D_L00_001B0FBC __attribute__((sda));
extern float D_L00_001B0FB0 __attribute__((sda));
extern float D_L00_001B0FC0 __attribute__((sda));
extern int D_L00_001ADB2C __attribute__((sda));
extern int D_L00_001A8FF0, D_L00_001A8FF4;
extern char *D_0018C0B0 NOT_SDA;
extern char *D_L00_001C3280[];
extern unsigned char D_00139568[];
typedef struct {
    char pad00[0x74];
    float strength;
    char pad78[0x68];
} CollisionWeaponInfo;
extern CollisionWeaponInfo D_L00_00262570[];

extern void func_002AFFD8(char *, char *, int);
extern void func_00300190(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002FEE70(int, void *, int);
extern void func_002FE880(void *, float *, float);
extern int func_002FE9D0(CollisionQuery *);
extern int func_00300540(int);
extern void func_002ACDE8(void *, void *, void *);
extern int func_00277F48(void *, float, int, void *, int);
extern int func_002ABB78(char *);
extern int func_002AB1F0(unsigned char *);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_00282C48(float);
extern void func_002AB668(void *, int, float);
extern int func_002E5CF8(int, int, char *);
extern int func_00282978(void *);
extern void func_002A8E20(void *, CollisionImpact *);
extern void func_0032D758(void *, int, void *);
extern void func_0032C700(void *, int, int, int, int, int, int, int,
                         int, int, int, int, float, float);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern void func_002A9288(void *, float);

/* Resolve motion and contacts, select a nearby target, and apply the object's
 * impact response. The query and impact layouts reflect their measured fields. */
void func_L00_004096B0(char *object)
{
    CollisionVector direction, previous;
    CollisionShape shape[1];
    CollisionQuery query;
    CollisionWorkspace workspace;
    char *state = *(char **)(object + 0x68);
    char *position = object + 0x10;
    int contacts, contact_kind, triggered;
    float range, fade;

    func_002AFFD8(position, (char *)&direction, 1);
    func_00300190(position, position);
    if (*(unsigned char *)(object + 0x20) == 0) {
        float query_range;

        qcopy(&previous, position);
        func_00282CC0(position, position, state);
        func_002FEE70(*(int *)(state + 0x28), state, 0);
        func_002FE880(position, (float *)state, 0.0040555559f);
        shape[0] = D_L00_001B0FC8;
        query_range = D_L00_001B0FAC;
        if (*(int *)(state + 0x24) != 0)
            query_range = D_L00_001B0FBC;
        qcopy(&query.previous, &previous);
        qcopy(&query.position, position);
        qcopy(&query.velocity, state);
    query.shape = shape;
    query.radius = 1.5f;
    query.scale = (D_L00_001B0FA0 - 1.0f) + 1.0f;
    query.owner = object;
    query.kind = 3;
    query.range = query_range;
    query.flags = 0;
    query.reserved = 0;
    query.extra = 0;
    contacts = func_002FE9D0(&query);
        contact_kind = func_00300540(query.result_kind);
        qcopy(position, &query.position);
        qcopy(state, &query.velocity);
        func_002ACDE8(object + 0xC0, object + 0xC0, state + 0x10);
        func_002ACDE8(object + 0xD0, object + 0xD0, state + 0x10);
        func_002ACDE8(object + 0xE0, object + 0xE0, state + 0x10);
        if (contacts > 0) {
            int count, i, best;
            count = func_00277F48(position, 7.0f, 1, D_0018C0B0, 0);
            if (count != 0) {
                float closest = 10000.0f;
                best = -1;
                for (i = 0; i < count; i++) {
                    char *target = D_L00_001C3280[i];
                    char *description;
                    if (*(unsigned char *)(target + 0x31) == 0 || func_002ABB78(target) != 0)
                        continue;
                    description = (char *)func_002AB1F0((unsigned char *)target);
                    if (description != 0 && !(*(float *)description <= 0.0f) && target != 0 &&
                        *(char **)(target + 0x24) != 0 &&
                        *(short *)(*(char **)(target + 0x24) + 0x46) == 5) {
                        float distance = func_00282E48(target + 0x10, object + 0x10);
                        if (distance < closest) {
                            closest = distance;
                            best = i;
                        }
                    }
                }
                if (best >= 0) {
                    char *target = D_L00_001C3280[best];
                    char *description = (char *)func_002AB1F0((unsigned char *)target);
                    float length, projection;
                    qcopy(&workspace.math.point, target + 0x10);
                    if (D_L00_001A8FF0 != 0) {
                        func_00282D30(&workspace.math.work, target + 0xE0,
                                      *(float *)(description + 0x10));
                        func_00282CC0(&workspace.math.point, &workspace.math.point, &workspace.math.work);
                    } else
                        workspace.math.point.f[2] += *(float *)(description + 0x10);
                    projection = func_00282DB0(&direction, state);
                    func_00282D30(&workspace.math.work, &direction, projection);
                    func_00282CF0(&workspace.math.delta, state, &workspace.math.work);
                    length = func_00282DF0(&workspace.math.delta);
                    if (length != 0.0f) {
                        func_00282CF0(&workspace.math.difference, &workspace.math.point, object + 0x10);
                        projection = func_00282DB0(&workspace.math.difference, &direction);
                        func_00282D30(&workspace.math.projection, &direction, projection);
                        func_00282CF0(&workspace.math.perpendicular, &workspace.math.difference, &workspace.math.projection);
                        if (length < 0.06666667f)
                            length = 0.06666667f;
                        func_00282F20(&workspace.math.perpendicular, &workspace.math.perpendicular, length);
                        func_00282CC0(state, &workspace.math.perpendicular, &workspace.math.work);
                    }
                }
            }
            qcopy(&workspace.math.point, state);
            workspace.math.point.f[2] = 0.0f;
            func_00282DD8(&workspace.math.point, &workspace.math.point, &direction);
            func_00282F20(&workspace.math.point, &workspace.math.point, 1.0f);
            range = func_002A78D8(0.0f, 0.52359885f);
            if (func_00282C48(range) < 0.00001f) {
                func_002AB668(&workspace.math.work, (int)&direction, range);
                func_002ACDE8(&workspace.math.point, &workspace.math.point, &workspace.math.work);
            }
            range = func_002A7878(0.05235988646745682f, 0.10471977293491364f);
            func_002AB668(state + 0x10, (int)&workspace.math.point, range);
            func_002E5CF8(0, 0, object);
        }
        workspace.impact.owner = object;
        workspace.impact.flags = 0x830000;
        workspace.impact.strength = (D_00139568[0x25] + D_L00_00262570)->strength;
        workspace.impact.count = 1;
        qcopy(&workspace.impact.force, state);
        triggered = 0;
        func_00282F20(&workspace.impact.force, &workspace.impact.force, 1.0f);
        workspace.impact.kind = 3;
        workspace.impact.force.f[3] = 5627.9248046875f;
        workspace.impact.enabled = 1;
        workspace.impact.object_class = *(short *)(object + 0xAA);
        range = *(int *)(state + 0x24) != 0 ? 8.0f : 2.0f;
        if (func_00282978(state + 0x20) != 0 ||
            (contacts > 0 && (unsigned int)(contact_kind - 1) <= 1)) {
            triggered = 1;
        } else {
            if (*(short *)(state + 0x22) == 0) {
                int count, i;
                count = func_00277F48(object + 0x10, range, 1, D_0018C0B0, 0);
                for (i = 0; i < count; i++) {
                    char *target = D_L00_001C3280[i];
                    char *description = (char *)func_002AB1F0((unsigned char *)target);
                    int special = func_002ABB78(target);
                    if (special != 0 || (description != 0 && *(float *)description > 0.0f &&
                                         *(short *)(description + 6) == 0)) {
                        func_002A8E20(target, &workspace.impact);
                        triggered = 1;
                        if (special == 0) {
                            if (*(int *)(state + 0x24) != 0)
                                func_0032D758(target, 0x4C, *(void **)(object + 0xB8));
                            else
                                func_0032D758(target, 0x25, *(void **)(object + 0xB8));
                        }
                        break;
                    }
                }
            } else {
                (*(short *)(state + 0x22))--;
                if (*(short *)(state + 0x22) < 0)
                    *(short *)(state + 0x22) = 0;
            }
        }
        if (triggered) {
            float blast_range;
            func_002E5CF8(1, 0, object);
            blast_range = 0.6f;
            if (*(int *)(state + 0x24) != 0)
                blast_range = 2.4f;
            func_0032C700(object + 0x10, 0, 6, 5, 6, 8, 10, 0, 0, 0, 0, D_L00_001ADB2C,
                          blast_range, 20.0f);
            func_002FEE50(*(int *)(state + 0x28));
            func_0029F338(object);
            return;
        }
    }
    fade = D_L00_001B0FB0;
    if (*(int *)(state + 0x24) != 0)
        fade = D_L00_001B0FC0;
    if (D_L00_001A8FF0 == 0 && D_L00_001A8FF4 == 0)
        func_002A9288(object, fade);
}
