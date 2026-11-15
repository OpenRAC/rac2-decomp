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
extern void func_L00_00428000(Moby *, Moby *);
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
/* Updates the flying tether's steering, sweep collision, impact burst and attached pieces. */
/* Per-frame update of the Visibomb Missile moby. */
void func_L00_003918C8(Moby *actor) {
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
    StartTimedObjectOnce(); D_L00_001B1BE8 = 1; ForceClaimNotice(6, 0, 1);
    timer = --state->timer;
    if (timer < -99 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x16 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x39 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x6F ||
        ((Hero *)gHeroState)->i[0x229C / 4] == 2 || ((Hero *)gHeroState)->i[0x229C / 4] == 4 || ((Hero *)gHeroState)->i[0x229C / 4] == 3 || ((Hero *)gHeroState)->i[0x229C / 4] > 12 ||
        ((Hero *)gHeroState)->i[0x229C / 4] == 7 || ((Hero *)gHeroState)->i[0x229C / 4] == 10 || ((Hero *)gHeroState)->i[0x229C / 4] == 16 || ((Hero *)gHeroState)->i[0x229C / 4] == 5 ||
        ((Hero *)gHeroState)->i[0x2294 / 4] == 0x62 || !((Hero *)gHeroState)->i[0x340 / 4] ||
        ((mount = ((Hero *)gHeroState)->ptr[0x33C / 4]) && (mount->objectClass == 0x13E /* moby class 318 */ || mount->objectClass == 0x46F /* Teleporter */)) || D_001A7428) {
        ReleaseTether(actor, state); return;
    }
    if (timer < 0) {
        if (D_L00_001ADB2C) { ReleaseTether(actor, state); ((Hero *)gHeroState)->h[0x1E0 / 2] = 12; return; }
        if (state->attached) UpdateCameraFollowTarget(state->attached, actor);
        RestoreLevelLighting(actor, 0); AttachTetherPieceToParent(actor, state); return;
    }
    desiredSpeed = D_L00_001AF0E4 * 0.016666668f;
    if (gPadState[0x1A0 / 4] & 0x40) desiredSpeed = D_L00_001AF0E8 * 0.016666668f;
    state->targetSpeed += (desiredSpeed - state->targetSpeed) * D_L00_001AF0EC;
    state->speed += (state->targetSpeed - state->speed) * D_L00_001AF0F0;
    if (state->speed > D_L00_001AF0E8 * 0.016666668f) state->speed = D_L00_001AF0E8 * 0.016666668f;
    SetVoicePitchBend(state->sound, FloatToInt((state->targetSpeed - (D_L00_001AF0E4 * 0.016666668f) /
                      (D_L00_001AF0E8 * 0.016666668f - D_L00_001AF0E4 * 0.016666668f)) * D_L00_001AF0E0));
    if ((u32)(state->timer - 1) < 0xBB2) {
        float stickX = ((Hero *)gHeroState)->f[0x1FB0 / 4], stickY = ((Hero *)gHeroState)->f[0x1FB4 / 4];
        state->inputX += (stickX - state->inputX) * 0.1f;
        state->inputY += (stickY - state->inputY) * 0.1f;
        if (D_L00_001A8FF0) {
            actor->pitch = (state->inputX - actor->pitch) * 0.06f;
            actor->yaw = state->inputY * 0.012271847f;
            actor->roll = state->inputX * 0.012271847f;
            if (FloatAbs(actor->roll) > 0.00001f) {
                BuildAxisAngleQuaternion(&scratch, &actor->forward, -actor->roll);
                RotateVectorByQuaternion(&actor->right, &actor->right, &scratch); RotateVectorByQuaternion(&actor->up, &actor->up, &scratch);
            }
            if (FloatAbs(actor->yaw) > 0.00001f) {
                BuildAxisAngleQuaternion(&scratch, &actor->up, -actor->yaw);
                RotateVectorByQuaternion(&actor->right, &actor->right, &scratch); RotateVectorByQuaternion(&actor->forward, &actor->forward, &scratch);
            }
            if (FloatAbs(actor->pitch) > 0.00001f) {
                BuildAxisAngleQuaternion(&scratch, &actor->right, actor->pitch);
                RotateVectorByQuaternion(&actor->up, &actor->up, &scratch); RotateVectorByQuaternion(&actor->forward, &actor->forward, &scratch);
            }
            SteerEffectDirection(state->camera, &actor->right, 0);
        } else {
            actor->pitch += (state->inputX - actor->pitch) * 0.06f;
            angle = fast_subtract_rotations(actor->yaw, state->inputY * 0.012271847f);
            actor->yaw = angle;
            if (angle >= 1.5707964f) actor->yaw = 1.5697963f;
            else if (angle <= -1.5707964f) actor->yaw = -1.5697963f;
            actor->roll = fast_subtract_rotations(actor->roll, state->inputX * 0.012271847f);
            QueueGroundShadow(actor, 0.2f);
        }
    }
    if (D_L00_001A8FF0) FastVecScale(&velocity, &actor->right, state->speed);
    else BuildSphericalOffset(velocity.f, state->speed, actor->roll, -actor->yaw);
    qcopy(&previous, &actor->position);
    FastVecAdd(&actor->position, &actor->position, velocity.f); TransformVectorOrCopy(&actor->position, &actor->position);
    if (state->timer >= 0xB7D) {
        height = ProbeGroundHeightBelow(&actor->position, 0, 0.5f) + state->hover;
        if (actor->position.f[2] < height && (!gCollisionResult.hit ||
            (gCollisionResult.hit->owner && gCollisionResult.hit->owner->kind == 5))) {
            turn = FastMatrixHelperA(state->speed, ApproachValue(&actor->position.f[2], height, 0.10000001f));
            if (turn > 0.026179943f) turn = 0.026179943f;
            actor->yaw -= turn;
        }
    }
    if (actor->position.f[0] < 4.5f || actor->position.f[0] > 1018.5f || actor->position.f[1] < 4.5f ||
        actor->position.f[1] > 1018.5f || actor->position.f[2] < 4.5f || actor->position.f[2] > 1018.5f) {
        ReleaseTether(actor, state); return;
    }
    AttachTetherPieceToParent(actor, state);
    build_axis_rotation_quaternion(&state->leftFin->position, 1,
                  -(state->inputY * 0.5f + FloatAbs(state->inputX * 0.33333334f) + (state->inputX - actor->pitch) * 1.1f) * 0.7f);
    fin = &state->rightFin->position;
    roll = (state->inputY * 0.5f + FloatAbs(state->inputX * 0.33333334f));
    build_axis_rotation_quaternion(fin, 1, ((state->inputX - actor->pitch) * 1.1f - roll) * 0.7f);
    damage.flags = 0x830000; damage.direction.quad = velocity.quad; damage.owner = actor;
    damage.mode = 1; damage.power = (gWeaponTable_L00 + gItemSlotToRecord[0xE])->power;
    FastVectorNormalizeHelper(&damage.direction, &damage.direction, 1);
    damage.kind = 3; damage.direction.f[3] = 5627.925f;
    damage.objectClass = actor->objectClass; damage.direction.f[2] = 1; damage.response = 2;
    ignore = actor;
    if (state->timer > 0xB90) ignore = ((Hero *)gHeroState)->ptr[0x2290 / 4];
    if (FindAcceptingTableObject(&actor->position)) {
        actor->hit = 2;
        qcopy(&contactEdge, &D_L00_001B8FF0);
        scratch.quad = 0; scratch.f[2] = 1; scratch.f[3] = 1;
        FastVectorNormalize(&blast, &velocity, &scratch); vec_scale_to_length(&blast, &blast, 0.033333335f);
        vec_scale_to_length(&blastNormal, &scratch, 1);
        if (state->sound != -1) {
            sound = gSoundState + state->sound * 0x70;
            if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) StopSoundVoice(state->sound);
        }
        state->sound = -1;
    } else if (CollLine(&previous, &actor->position, 0, ignore, &damage)) {
        CollisionResult *col = &gCollisionResult;
        Moby *hit = col->hit;
        if (hit) {
            if (hit == ((Hero *)gHeroState)->ptr[0x2290 / 4]) playerHit = 1;
            actor->hit = 2;
            qcopy(&actor->position, &col->position);
            FastVecSub(&contactEdge, &col->edgeStart, &col->edgeEnd);
            vec_scale_to_length(&contactEdge, &contactEdge, 1);
            FastVectorNormalize(&blast, &velocity, &col->normal); vec_scale_to_length(&blast, &blast, 0.033333335f);
            vec_scale_to_length(&blastNormal, &col->normal, 1);
            if (state->sound != -1) {
                sound = gSoundState + state->sound * 0x70;
                if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) StopSoundVoice(state->sound);
            }
            state->sound = -1;
        } else if (col->mesh > 0) {
            actor->hit = 1; qcopy(&actor->position, &col->position);
            FastVecSub(&contactEdge, &col->edgeStart, &col->edgeEnd);
            vec_scale_to_length(&contactEdge, &contactEdge, 1);
            FastVectorNormalize(&blast, &velocity, &col->normal); vec_scale_to_length(&blast, &blast, 0.033333335f);
            vec_scale_to_length(&blastNormal, &col->normal, 1);
            if (state->sound != -1) {
                sound = gSoundState + state->sound * 0x70;
                if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) StopSoundVoice(state->sound);
            }
            state->sound = -1;
        }
    } else if (!state->timer) { ReleaseTether(actor, state); return; }
after_rebound:
    if (state->timer < 0xB7C && (gPadState[0x1A4 / 4] & 0x20)) {
        actor->hit = 1;
        if (state->sound != -1) {
            sound = gSoundState + state->sound * 0x70;
            if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) StopSoundVoice(state->sound);
        }
        state->sound = -1;
    }
    if (actor->hit) {
        if (!playerHit) {
            SpawnExplosionEffects(actor, &blast, 0, 0, 0, 10, 3, 16, 4, 2, 0, 1, 1, 20, 1, 1, -1, 0, 0x810001);
            hits = ProcessCollisionHit(4, &actor->position, 16, actor, 0);
            scratch.quad = actor->position.quad;
            QueueKnockbackForNodes(actor, &scratch, gAreaHitTargets, hits, 0, 0x830000, 3, 2,
                          (gWeaponTable_L00 + gItemSlotToRecord[0xE])->power, 1, 1);
        }
        actor->flags |= 1; state->speed = 0.02f;
        state->inputX *= 0.01f;
        if (state->timer >= 0xB9B) state->timer = -100;
        else state->timer = -1;
        qcopy(&scratch, &actor->position);
        for (i = 4; i >= 0; --i) {
            qcopy(&actor->position, &scratch); AddRandomOffsetToVector(actor->position.f, 1.5f); SpawnTetherImpactEffects(actor, 1);
            qcopy(&actor->position, &scratch);
        }
        velocity.f[0] = 0; actor->hit = 0;
    }
    if (state->attached) UpdateCameraFollowTarget(state->attached, actor);
    if (!D_L00_001A8FF0) return;
    ComputeViewDirection(&actor->position, &actor->forward, 1);
    FastVecCross(&scratch, &actor->right, &actor->forward); vec_scale_to_length(&actor->up, &scratch, 1);
    FastVecCross(&actor->forward, &actor->up, &actor->right);
    actor->right.f[3] = actor->up.f[3] = actor->forward.f[3] = 0;
}
