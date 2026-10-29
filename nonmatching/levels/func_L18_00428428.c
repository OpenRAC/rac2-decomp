/* Complete C near miss; not linked and no matching credit.
 * Default -O2 -G8 -ffunction-sections: 624/676 bytes, USA and USA2 0/3 each;
 * PAL has no catalogue row. Seven bounded checks including final extent proof.
 * Class-parameter float copies and literal/address lifetimes remain different.
 * Fine block-order and GCSE-edge controls tie; GCSE/no-expensive/forward-CSE
 * controls also tie. No register pins, volatile, fake dependencies or padding.
 * The 36 bytes of query fields include a real aligned vector, giving a natural
 * complete 48-byte record. The sphere query copies 40 bytes (two lq and one ld),
 * all within that record. Its exclusive velocity alternative shares the union.
 * Shot origin and velocity are complete aligned vectors. All true callee
 * return types are preserved: the projectile creator returns an actor pointer,
 * the collision helpers return int, the effect helper is void.
 * Reopen with grounded class-parameter and constant lifetime evidence.
 */
#include "common.h"

typedef struct { float v[4]; } __attribute__((aligned(16))) ShotVector;
typedef struct {
    ShotVector direction;
    u8 *owner;
    u32 flags;
    u8 kind, subtype;
    u16 classId;
    float damage;
    int enabled;
} ShotQuery;

typedef union { ShotQuery query; ShotVector velocity; } ShotWorkspace;
typedef char ShotQueryExtent[(sizeof(ShotQuery) == 0x30) ? 1 : -1];
extern float D_L18_001B1280 __attribute__((sda));
extern float D_L18_001B1284 __attribute__((sda));
extern float D_L18_001B1288 __attribute__((sda));
extern float D_L18_001B128C __attribute__((sda));
extern float D_L18_001B12C0 __attribute__((sda));
extern const char D_L18_001B1338[];
extern u8 D_L18_001A8F20[];
extern void func_0026FEB8(const char *, ...);
extern void func_0029FCC0(char *, int, char *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern int func_L18_004283F0(u8 *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int func_00277F48(void *, float, int, void *, void *);
extern void func_00282F20(void *, const void *, float);
extern float func_00282E80(const void *, const void *);
extern u8 *func_L18_0043FFF8(void *, void *, void *, int, int, float, float, float);

u8 *func_L18_00428428(u8 *actor, int joint)
{
    ShotVector position;
    ShotWorkspace workspace;
    u8 *state = *(u8 **)(actor + 0x68);
    float rate = D_L18_001B1280;
    float speed = D_L18_001B1288;
    int kind;

    switch (*(s16 *)(actor + 0xAA)) {
    case 0xEC0:
        func_0026FEB8(D_L18_001B1338, 0xEC0);
        break;
    case 0xED4:
        rate = D_L18_001B1284;
        speed = D_L18_001B128C;
        break;
    case 0xEE1:
        break;
    default:
        break;
    }
    func_0029FCC0((char *)actor, joint + 2, (char *)&position);
    if (func_002A8C28(actor, &position, actor[0xBC] ? 1 : 0x10000,
                      1, 3, 0, 0.35f, (float)state[0x34], D_L18_001B12C0)) {
        workspace.query.owner = actor;
        workspace.query.flags = 0x810001;
        workspace.query.enabled = 1;
        workspace.query.damage = (float)state[0x34];
        qzero(&workspace.query.direction);
        workspace.query.kind = 2;
        workspace.query.subtype = 3;
        workspace.query.classId = *(u16 *)(actor + 0xAA);
        workspace.query.direction.v[2] = D_L18_001B12C0;
        workspace.query.direction.v[3] = 5627.9248046875f;
        kind = func_L18_004283F0(actor);
        func_002ABBB8(actor, D_L18_001A8F20, &position, 0.0f, 0.0f, 5, 2, 9,
                      0.0f, 0.0f, 9.0f, 1.1f, kind, 0.0f, 0, 1, -2, 0, 0x810001);
        func_00277F48(&position, 1.0f, 0x10, actor, &workspace.query);
        return 0;
    }
    speed *= 1.0f / 60.0f;
    func_00282F20(&workspace.velocity, actor + 0xC0, speed);
    if (actor[0xBC] == 0) {
        float time = func_00282E80(&position, state + 0x220) / speed;
        workspace.velocity.v[2] = (*(float *)(state + 0x228) - position.v[2]) / time;
    }
    return func_L18_0043FFF8(&position, actor, &workspace.velocity, 1, 3,
                             (float)state[0x34], rate, D_L18_001B12C0);
}
