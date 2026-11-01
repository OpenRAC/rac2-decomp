#include "include_asm.h"

#include "common.h"
typedef struct {
    float x, y, z, w;
} UpdateVec;
typedef struct {
    UpdateVec start, end, velocity;
    void *object;
    void *ignore;
    int ignoreCount;
    float radius, friction, bounce;
    int flags, mask, response, surface, gravity;
    float maxTurn;
} UpdateQuery;
typedef union {
    UpdateQuery query;
    struct {
        UpdateVec angles, adjusted, transform[4];
    } attachment;
} UpdateWorkspace;
typedef struct {
    char pad[0x18];
    char *hit;
    int count;
    UpdateVec point, extra, normal;
} UpdateCollision;
extern char D_001B2830[] MACRO_ADDR;
extern UpdateCollision D_001BAF80;
extern char D_001BAFC0[];
extern char D_00189E20[];
extern char *D_001B5390 __attribute__((nosda));
extern int D_001A8CFC[] MACRO_ADDR;
extern int D_0018C0B4 __attribute__((nosda));
extern int D_00138324 __attribute__((nosda));
extern int D_001A8BB0 __attribute__((sda));
extern float D_001B0958 __attribute__((sda));
extern char *D_001B0960 __attribute__((sda));
extern int D_001B0964 __attribute__((sda));
extern float D_001B096C __attribute__((sda));
extern float D_001B0970 __attribute__((sda));
extern int D_001B2840[] MACRO_ADDR;
extern int update_timer SDATA(D_001B2840);
extern int D_001B2844[] MACRO_ADDR;
extern int update_collision SDATA(D_001B2844);
extern int D_001B2848[] MACRO_ADDR;
extern int update_water SDATA(D_001B2848);
extern int D_001B2858[] MACRO_ADDR;
extern int update_handle SDATA(D_001B2858);
extern char *D_001AD7EC[] MACRO_ADDR;
extern float D_002373F0[][2];
extern void func_002B00B0(void *, void *, int);
extern void func_002FE8D8(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern void func_00282F20(void *, void *, float);
extern void func_002B0CE0(int, int, int);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern void func_US2_0029C548(int, void (*)(void *));
extern void func_0032F3D0(void *);
extern void func_00335840(void);
extern void func_003317E0(void);
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_US2_0026F750(int, int);
extern void func_00335798(void *, void *, void *);
extern void func_002A7470(void *, int, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_US2_00330BE8(void *), func_003309A0(void *), func_0032FEA8(void *);
extern void func_00330BC0(void *), func_00331718(void);
extern int func_00282948(void *);
extern int func_002FE9D0(UpdateQuery *);
extern int func_00300540(int);
extern void func_00282C88(void *);
extern float func_00282DF0(void *);
extern char *func_0032DA58(void *, void *, void *, float);
extern void func_00330CA0(void *);
extern void func_002FEE50(int), func_002FED28(int), func_0029F338(void *);
extern void func_00283658(void *, void *), func_002AB6D8(void *, void *);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002833F0(void *, void *), func_US2_003303C0(void *);
extern void func_0027D098(void (*)(void *), void *);
extern void func_00330E48(void *);
extern void func_002A9288(void *, float);
#define I(p, n) (*(int *)((char *)(p) + (n)))
#define F(p, n) (*(float *)((char *)(p) + (n)))
#define P(p, n) (*(char **)((char *)(p) + (n)))
#define STATE(p) (*(unsigned char *)((p) + 0x20))

/* Advances launch, grounded movement, falling and teardown states of a timed actor. */
void func_US2_0032F944(char *obj)
{
    /* The query and attachment transform use the same workspace in separate phases. */
    struct {
        UpdateVec previous, ahead, behind;
        UpdateWorkspace workspace;
        UpdateVec rotation;
    } scratch;
    char *vars = P(obj, 0x68);
    int i, hit, action;
    float (*particles)[2];
    char *hero;

    if (STATE(obj) >= 2)
    func_002B00B0(obj, D_001B2830, 1);
    else
    func_002FE8D8(obj + 0x10, D_001B2830);
    func_00282D30(D_001B2830, D_001B2830, -1.0f);
    func_00282D30(&scratch.ahead, obj + 0xE0, D_001B096C);
    func_00282CC0(&scratch.ahead, obj + 0x10, &scratch.ahead);
    func_00282D30(&scratch.behind, obj + 0xE0, -1.0f);
    func_00282CC0(&scratch.behind, obj + 0x10, &scratch.behind);
    if (func_002761F8(&scratch.ahead, &scratch.behind, 2, obj, 0)) {
        if (func_00278E78() == 2) {
            func_00282D30(D_001B2830, D_001BAFC0, 0.0009765625f);
            func_00282F20(D_001B2830, D_001B2830, -1.0f);
            D_001B2844[0] = 1;
        } else {
            update_collision = 0;
        }
        if (func_00278E78() == 6)
        update_water = 1;
        else
        update_water = 0;
    } else {
        update_collision = 0;
        D_001B2848[0] = 0;
    }
    func_002B0CE0(6, 0, 1);
    switch (STATE(obj)) {
    case 0:
        STATE(obj) = 1;
        I(vars, 0x58) = 0;
        F(obj, 0x2C) = 0.00025f;
        I(obj, 0x98) = 0;
        particles = D_002373F0;
        for (i = 97; i >= 0; i--) {
            (*particles)[0] = func_002A7940();
            (*particles)[1] = func_002A78D8(720.0f, 2160.0f) * 0.00029088825f;
            particles++;
        }
        update_timer = 1800;
        if (D_001A8CFC[0])
            func_US2_0029C548(0, func_0032F3D0);
        /* fall through */
    case 1:
        hero = D_00189E20;
        action = I(hero, 0x2294);
        if (action == 98 || D_001A8BB0 == 2 || action == 111 || action == 100 ||
            action == 99 || action == 23 || action == 24 || action == 129 || action == 39) {
            func_00335840();
            STATE(obj) = 7;
            func_003317E0();
            I(vars, 0x60) = 0;
            break;
        }
        F(obj, 0x2C) += 0.01f;
        if (F(obj, 0x2C) > 0.023f)
            F(obj, 0x2C) = 0.023f;
        qcopy(&scratch.previous, obj + 0x10);
        func_00282CC0(obj + 0x10, obj + 0x10, vars);
        func_002FEE70(D_001B2858[0], vars, 0);
        func_00300190(obj + 0x10, obj + 0x10);
        func_00300248(vars, vars);
        func_002FE880(obj + 0x10, vars, 0.0030555557f);
        if (func_002761F8(&scratch.previous, obj + 0x10, 0, obj, 0)) {
            UpdateCollision *collision = &D_001BAF80;
            char *other = collision->hit;
            if (other && (other == P(hero, 0x2290) || *(short *)(other + 0xAA) == 0x907))
                break;
            qcopy(obj + 0x10, &collision->point);
            func_002B0CE0(6, 0, 1);
            func_US2_0026F750(28, 1);
            func_00335798(obj + 0x10, obj + 0xF0, obj);
            STATE(obj) = 2;
            func_002A7470(obj, 1, 0, 10);
            I(obj, 0x48) = 0;
        }
        break;
    case 2:
        STATE(obj) = 3;
        func_002E5CF8(2, 0, obj);
        if (D_0018C0B4 != 28 || D_001A8BB0 == 2) {
            func_00335840();
            STATE(obj) = 9;
            I(vars, 0x60) = 0;
        }
        break;
    case 3:
        func_US2_00330BE8(obj);
        func_003309A0(obj);
        func_0032FEA8(obj);
        func_00330BC0(obj);
        func_00331718();
        if (func_00282948(D_001B2840)) {
            STATE(obj) = 9;
            I(vars, 0x60) = 10;
        }
        if (D_00138324 & 32) {
            STATE(obj) = 9;
            I(vars, 0x60) = 10;
        }
        if (D_0018C0B4 != 28 || D_001A8BB0 == 2) {
            func_00335840();
            STATE(obj) = 9;
            I(vars, 0x60) = 0;
        }
        break;
    case 4:
        qcopy(&scratch.previous, obj + 0x10);
        func_00282CC0(obj + 0x10, obj + 0x10, vars);
        func_002FE880(obj + 0x10, vars, 0.0061111115f);
        func_00300190(obj + 0x10, obj + 0x10);
        func_00300248(vars, vars);
        qcopy(&scratch.workspace.query.start, &scratch.previous);
        qcopy(&scratch.workspace.query.end, obj + 0x10);
        qcopy(&scratch.workspace.query.velocity, vars);
        scratch.workspace.query.radius = 0.2f;
        scratch.workspace.query.friction = 0.85f;
        scratch.workspace.query.bounce = 0.75f;
        scratch.workspace.query.response = 1;
        scratch.workspace.query.object = obj;
        scratch.workspace.query.ignore = 0;
        scratch.workspace.query.ignoreCount = 0;
        scratch.workspace.query.flags = 0;
        scratch.workspace.query.mask = 0;
        scratch.workspace.query.gravity = 0;
        hit = func_002FE9D0(&scratch.workspace.query);
        qcopy(obj + 0x10, &scratch.workspace.query.end);
        qcopy(vars, &scratch.workspace.query.velocity);
        if (hit == 2) {
            if (func_00300540(scratch.workspace.query.surface) || scratch.workspace.query.surface == 12) {
                STATE(obj) = 9;
                I(vars, 0x60) = 10;
            } else {
                STATE(obj) = 2;
                func_00282C88(vars);
            }
        } else if (func_00282DF0(vars) > 0.4f) {
            STATE(obj) = 9;
            I(vars, 0x60) = 10;
        }
        break;
    case 9:
        STATE(obj) = 5;
        func_003317E0();
        /* fall through */
    case 5:
        if (func_00282948(vars + 0x60)) {
            func_002E5CF8(1, 0, obj);
            func_00282F20(&scratch.rotation, obj + 0xC0, 1.0f);
            func_0032DA58(obj, obj + 0x10, &scratch.rotation, F(obj, 0x18));
            STATE(obj) = 6;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            if (D_0018C0B4 != 28 || D_001A8BB0 == 2) {
                func_00335840();
                I(vars, 0x60) = 0;
            } else
                I(vars, 0x60) = D_001B0964;
            I(vars, 0x64) = 0;
        }
        break;
    case 6:
        func_00330CA0(obj);
        F(vars, 0x64) += D_001B0958 * 0.016666668f;
        if (func_00282948(vars + 0x60) && !I(vars, 0x68))
            STATE(obj) = 8;
        break;
    case 7:
        if (func_00282948(vars + 0x60))
            STATE(obj) = 8;
        break;
    case 8:
        if (D_0018C0B4 == 28)
            func_US2_0026F750(0, 1);
        if (*(short *)(D_001B5390 + 0x86) == 27)
            func_00335840();
        func_002FEE50(update_handle);
        func_002FED28(I(vars, 0x6C));
        func_002FED28(I(vars, 0x70));
        func_002FED28(I(vars, 0x74));
        D_001B0960 = 0;
        func_US2_0029C548(0, 0);
        func_0029F338(obj);
        return;
    }
    if (STATE(obj) >= 2 && D_001AD7EC[0]) {
        func_00283658(scratch.workspace.attachment.transform, obj + 0xC0);
        func_002AB6D8(scratch.workspace.attachment.transform, &scratch.workspace.attachment.angles);
        func_002AD0E0(obj, D_001AD7EC[0], obj + 0x10,
                     &scratch.workspace.attachment.angles, obj + 0x10,
                     &scratch.workspace.attachment.adjusted);
        func_002833F0(obj + 0xC0, &scratch.workspace.attachment.adjusted);
    }
    if ((unsigned int)(STATE(obj) - 2) < 2)
        func_US2_003303C0(obj);
    func_0027D098(func_00330E48, obj);
    func_002A9288(obj, D_001B0970);
}
