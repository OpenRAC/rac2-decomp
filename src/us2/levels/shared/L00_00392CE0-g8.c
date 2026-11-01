#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;
typedef struct TetherState TetherState;
typedef struct {
    u8 pad00[0x10];
    Vector position;
    u8 pad20[4];
    struct { u8 pad00[0x46]; s16 kind; } *owner;
    u8 pad28[0xC];
    u16 flags;
    u8 pad36[0x32];
    TetherState *state;
    u8 pad6C[0x3E];
    s16 objectClass;
    u8 padAC[0x10];
    u8 hit;
    u8 padBD[3];
    Vector right, up, forward;
    float pitch, yaw, roll;
} Moby;
struct TetherState {
    int unknown00;
    float speed;
    int unknown08[2];
    int timer;
    Moby *attached;
    float inputX, inputY;
    int unknown20;
    Moby *leftFin, *rightFin;
    int sound;
    int unknown30[5];
    float hover;
    float targetSpeed;
    int camera;
};
typedef struct {
    Vector direction;
    Moby *owner;
    u32 flags;
    u8 kind, response;
    u16 objectClass;
    float power;
    int mode;
} DamageRecord;
typedef struct {
    int unknown00[6];
    Moby *hit;
    int mesh;
    Vector position, unknown30, normal, edgeStart, edgeEnd, tail;
} CollisionResult;
typedef struct { u8 pad00[0x70]; float power; u8 pad74[0x6C]; } LevelClass;
extern u32 D_00138180[];
extern u8 D_00189E20[], D_00188660[], D_00139568[];
extern int D_L00_001B1A4C, D_L00_001B1BE8, D_L00_001ADB2C, D_L00_001A8FF0;
extern int D_L00_001B1994 __attribute__((sda)), D_001A7428 __attribute__((sda));
extern float D_L00_001AF0E0 __attribute__((sda)), D_L00_001AF0E4 __attribute__((sda)), D_L00_001AF0E8 __attribute__((sda));
extern float D_L00_001AF0EC __attribute__((sda)), D_L00_001AF0F0 __attribute__((sda));
extern CollisionResult D_L00_001BF200;
extern Vector D_L00_001B8FF0;
extern LevelClass D_L00_00262570[];
extern int D_L00_001C3280[];
extern void func_L00_002F46C8(void);
extern int func_002B0CE0(int, void *, int);
extern void func_L00_00391310(Moby *, TetherState *), func_L00_00390F28(Moby *, int), func_L00_00391398(Moby *, TetherState *);
extern void func_US2_L00_00429510(Moby *, Moby *);
extern int func_00283CF0(float), func_002E5F40(int, int);
extern float func_00282C48(float), func_00283BE0(float, float), func_002A89A8(void *, int, float), func_002AA2E8(float *, float, float), func_00283248(float, float);
extern void func_002AB668(void *, void *, float), func_002ACDE8(void *, void *, void *), func_002FEE70(int, void *, void *), func_002A9288(Moby *, float);
extern void func_00282D30(void *, void *, float), func_002AF000(float *, float, float, float), func_00282CC0(void *, void *, void *), func_00300190(void *, void *);
extern void func_00283898(void *, int, float), func_00282F70(void *, void *, float);
extern int func_L00_00380058(Vector *), func_002761F8(void *, void *, int, Moby *, DamageRecord *);
extern void func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float), func_00283028(void *, void *, void *), func_002E59F8(int);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int func_00277F48(float, void *, int, Moby *, int);
extern void func_002A9850(void *, Vector *, int *, int, int, int, int, int, float, float, float);
extern void func_002ACB48(float *, float), func_L00_003914E0(Moby *, int), func_002AFFD8(Vector *, Vector *, int), func_00282DD8(void *, void *, void *);
extern float ref_US2_L00_00392CE0_01;

/* Updates the flying tether's steering, sweep collision, impact burst and attached pieces. */
void func_US2_L00_00392CE0(Moby *actor) {
    Vector previous, blast, blastNormal, velocity, contactEdge, scratch;
    DamageRecord damage;
    TetherState *state = actor->state;
    Moby *mount, *ignore;
    u8 *sound;
    float desiredSpeed, angle, turn, height, roll, yaw;
    Vector *fin;
    int timer, playerHit = 0, i, hits;
    blast.quad = 0; blastNormal.quad = 0;
    blast.f[2] = 0.13333334f; blastNormal.f[2] = 1;
    D_L00_001B1A4C = 1; D_L00_001B1994 = 1;
    func_L00_002F46C8(); D_L00_001B1BE8 = 1; func_002B0CE0(6, 0, 1);
    timer = --state->timer;
    if (timer < -99 || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x16 || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x39 || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x6F ||
        ((Hero *)D_00189E20)->i[0x229C / 4] == 2 || ((Hero *)D_00189E20)->i[0x229C / 4] == 4 || ((Hero *)D_00189E20)->i[0x229C / 4] == 3 || ((Hero *)D_00189E20)->i[0x229C / 4] > 12 ||
        ((Hero *)D_00189E20)->i[0x229C / 4] == 7 || ((Hero *)D_00189E20)->i[0x229C / 4] == 10 || ((Hero *)D_00189E20)->i[0x229C / 4] == 16 || ((Hero *)D_00189E20)->i[0x229C / 4] == 5 ||
        ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x62 || ref_US2_L00_00392CE0_01 > 0.0f || !((Hero *)D_00189E20)->i[0x340 / 4] ||
        ((mount = ((Hero *)D_00189E20)->ptr[0x33C / 4]) && (mount->objectClass == 0x13E || mount->objectClass == 0x46F)) || D_001A7428) {
        func_L00_00391310(actor, state); return;
    }
    if (timer < 0) {
        if (D_L00_001ADB2C) { func_L00_00391310(actor, state); ((Hero *)D_00189E20)->h[0x1E0 / 2] = 12; return; }
        if (state->attached) func_US2_L00_00429510(state->attached, actor);
        func_L00_00390F28(actor, 0); func_L00_00391398(actor, state); return;
    }
    desiredSpeed = D_L00_001AF0E4 * 0.016666668f;
    if (D_00138180[0x1A0 / 4] & 0x40) desiredSpeed = D_L00_001AF0E8 * 0.016666668f;
    state->targetSpeed += (desiredSpeed - state->targetSpeed) * D_L00_001AF0EC;
    state->speed += (state->targetSpeed - state->speed) * D_L00_001AF0F0;
    if (state->speed > D_L00_001AF0E8 * 0.016666668f) state->speed = D_L00_001AF0E8 * 0.016666668f;
    func_002E5F40(state->sound, func_00283CF0((state->targetSpeed - (D_L00_001AF0E4 * 0.016666668f) /
                      (D_L00_001AF0E8 * 0.016666668f - D_L00_001AF0E4 * 0.016666668f)) * D_L00_001AF0E0));
    if ((u32)(state->timer - 1) < 0xBB2) {
        float stickX = ((Hero *)D_00189E20)->f[0x1FB0 / 4], stickY = ((Hero *)D_00189E20)->f[0x1FB4 / 4];
        state->inputX += (stickX - state->inputX) * 0.1f;
        state->inputY += (stickY - state->inputY) * 0.1f;
        if (D_L00_001A8FF0) {
            actor->pitch = (state->inputX - actor->pitch) * 0.06f;
            actor->yaw = state->inputY * 0.012271847f;
            actor->roll = state->inputX * 0.012271847f;
            if (func_00282C48(actor->roll) > 0.00001f) {
                func_002AB668(&scratch, &actor->forward, -actor->roll);
                func_002ACDE8(&actor->right, &actor->right, &scratch); func_002ACDE8(&actor->up, &actor->up, &scratch);
            }
            if (func_00282C48(actor->yaw) > 0.00001f) {
                func_002AB668(&scratch, &actor->up, -actor->yaw);
                func_002ACDE8(&actor->right, &actor->right, &scratch); func_002ACDE8(&actor->forward, &actor->forward, &scratch);
            }
            if (func_00282C48(actor->pitch) > 0.00001f) {
                func_002AB668(&scratch, &actor->right, actor->pitch);
                func_002ACDE8(&actor->up, &actor->up, &scratch); func_002ACDE8(&actor->forward, &actor->forward, &scratch);
            }
            func_002FEE70(state->camera, &actor->right, 0);
        } else {
            actor->pitch += (state->inputX - actor->pitch) * 0.06f;
            angle = func_00283BE0(actor->yaw, state->inputY * 0.012271847f);
            actor->yaw = angle;
            if (angle >= 1.5707964f) actor->yaw = 1.5697963f;
            else if (angle <= -1.5707964f) actor->yaw = -1.5697963f;
            actor->roll = func_00283BE0(actor->roll, state->inputX * 0.012271847f);
            func_002A9288(actor, 0.2f);
        }
    }
    if (D_L00_001A8FF0) func_00282D30(&velocity, &actor->right, state->speed);
    else func_002AF000(velocity.f, state->speed, actor->roll, -actor->yaw);
    qcopy(&previous, &actor->position);
    func_00282CC0(&actor->position, &actor->position, velocity.f); func_00300190(&actor->position, &actor->position);
    if (state->timer >= 0xB7D) {
        height = func_002A89A8(&actor->position, 0, 0.5f) + state->hover;
        if (actor->position.f[2] < height && (!D_L00_001BF200.hit ||
            (D_L00_001BF200.hit->owner && D_L00_001BF200.hit->owner->kind == 5))) {
            turn = func_00283248(state->speed, func_002AA2E8(&actor->position.f[2], height, 0.10000001f));
            if (turn > 0.026179943f) turn = 0.026179943f;
            actor->yaw -= turn;
        }
    }
    if (actor->position.f[0] < 4.5f || actor->position.f[0] > 1018.5f || actor->position.f[1] < 4.5f ||
        actor->position.f[1] > 1018.5f || actor->position.f[2] < 4.5f || actor->position.f[2] > 1018.5f) {
        func_L00_00391310(actor, state); return;
    }
    func_L00_00391398(actor, state);
    func_00283898(&state->leftFin->position, 1,
                  -(state->inputY * 0.5f + func_00282C48(state->inputX * 0.33333334f) + (state->inputX - actor->pitch) * 1.1f) * 0.7f);
    fin = &state->rightFin->position;
    roll = (state->inputY * 0.5f + func_00282C48(state->inputX * 0.33333334f));
    func_00283898(fin, 1, ((state->inputX - actor->pitch) * 1.1f - roll) * 0.7f);
    damage.flags = 0x830000; damage.direction.quad = velocity.quad; damage.owner = actor;
    damage.mode = 1; damage.power = (D_L00_00262570 + D_00139568[0xE])->power;
    func_00282F70(&damage.direction, &damage.direction, 1);
    damage.kind = 3; damage.direction.f[3] = 5627.925f;
    damage.objectClass = actor->objectClass; damage.direction.f[2] = 1; damage.response = 2;
    ignore = actor;
    if (state->timer > 0xB90) ignore = ((Hero *)D_00189E20)->ptr[0x2290 / 4];
    if (func_L00_00380058(&actor->position)) {
        actor->hit = 2;
        qcopy(&contactEdge, &D_L00_001B8FF0);
        scratch.quad = 0; scratch.f[2] = 1; scratch.f[3] = 1;
        func_00283028(&blast, &velocity, &scratch); func_00282F20(&blast, &blast, 0.033333335f);
        func_00282F20(&blastNormal, &scratch, 1);
        if (state->sound != -1) {
            sound = D_00188660 + state->sound * 0x70;
            if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) func_002E59F8(state->sound);
        }
        state->sound = -1;
    } else if (func_002761F8(&previous, &actor->position, 0, ignore, &damage)) {
        CollisionResult *col = &D_L00_001BF200;
        Moby *hit = col->hit;
        if (hit) {
            if (hit == ((Hero *)D_00189E20)->ptr[0x2290 / 4]) playerHit = 1;
            actor->hit = 2;
            qcopy(&actor->position, &col->position);
            func_00282CF0(&contactEdge, &col->edgeStart, &col->edgeEnd);
            func_00282F20(&contactEdge, &contactEdge, 1);
            func_00283028(&blast, &velocity, &col->normal); func_00282F20(&blast, &blast, 0.033333335f);
            func_00282F20(&blastNormal, &col->normal, 1);
            if (state->sound != -1) {
                sound = D_00188660 + state->sound * 0x70;
                if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) func_002E59F8(state->sound);
            }
            state->sound = -1;
        } else if (col->mesh > 0) {
            actor->hit = 1; qcopy(&actor->position, &col->position);
            func_00282CF0(&contactEdge, &col->edgeStart, &col->edgeEnd);
            func_00282F20(&contactEdge, &contactEdge, 1);
            func_00283028(&blast, &velocity, &col->normal); func_00282F20(&blast, &blast, 0.033333335f);
            func_00282F20(&blastNormal, &col->normal, 1);
            if (state->sound != -1) {
                sound = D_00188660 + state->sound * 0x70;
                if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) func_002E59F8(state->sound);
            }
            state->sound = -1;
        }
    } else if (!state->timer) { func_L00_00391310(actor, state); return; }
after_rebound:
    if (state->timer < 0xB7C && (D_00138180[0x1A4 / 4] & 0x20)) {
        actor->hit = 1;
        if (state->sound != -1) {
            sound = D_00188660 + state->sound * 0x70;
            if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) func_002E59F8(state->sound);
        }
        state->sound = -1;
    }
    if (actor->hit) {
        if (!playerHit) {
            func_002ABBB8(actor, &blast, 0, 0, 0, 10, 3, 16, 4, 2, 0, 1, 1, 20, 1, 1, -1, 0, 0x810001);
            hits = func_00277F48(4, &actor->position, 16, actor, 0);
            scratch.quad = actor->position.quad;
            func_002A9850(actor, &scratch, D_L00_001C3280, hits, 0, 0x830000, 3, 2,
                          (D_L00_00262570 + D_00139568[0xE])->power, 1, 1);
        }
        actor->flags |= 1; state->speed = 0.02f;
        state->inputX *= 0.01f;
        if (state->timer >= 0xB9B) state->timer = -100;
        else state->timer = -1;
        qcopy(&scratch, &actor->position);
        for (i = 4; i >= 0; --i) {
            qcopy(&actor->position, &scratch); func_002ACB48(actor->position.f, 1.5f); func_L00_003914E0(actor, 1);
            qcopy(&actor->position, &scratch);
        }
        velocity.f[0] = 0; actor->hit = 0;
    }
    if (state->attached) func_US2_L00_00429510(state->attached, actor);
    if (!D_L00_001A8FF0) return;
    func_002AFFD8(&actor->position, &actor->forward, 1);
    func_00282DD8(&scratch, &actor->right, &actor->forward); func_00282F20(&actor->up, &scratch, 1);
    func_00282DD8(&actor->forward, &actor->up, &actor->right);
    actor->right.f[3] = actor->up.f[3] = actor->forward.f[3] = 0;
}
