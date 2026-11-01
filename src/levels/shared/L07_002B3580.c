#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038F3D8(void *);
extern void func_L00_0038E880(void *, void *, void *);
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L00_001AC850 __attribute__((sda));
extern int D_L00_001B2630 __attribute__((sda)), D_L00_001B2638 __attribute__((sda));
extern Collision D_L00_001BF200;
extern Material D_L00_00262570[];
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0038F178(void *);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void func_002FD1B8(int, int, int, float, float, float, float);
extern void func_00282C88(void *);
extern char *func_00312D58(void *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002BFB38(void *, void *, int, int);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);

extern char D_L07_001FDEC0[];
extern void func_338D68();

typedef int DriveVector __attribute__((mode(TI)));
typedef struct PlayerDriveView {
    unsigned char pad0[0x20]; float basis[16];
    unsigned char pad60[0x98 - 0x60]; float rotation;
    unsigned char pad9C[0xF0 - 0x9C]; DriveVector velocity;
    unsigned char pad100[0x160 - 0x100]; DriveVector pendingResult;
    float distance, planarDistance;
    unsigned char pad178[0x190 - 0x178]; DriveVector direction; float heading;
    float yawRate, yawError;
    unsigned char pad1AC[4]; float speed, targetSpeed; int frame;
    unsigned char pad1BC[0x348 - 0x1BC]; short request, contact;
    unsigned char pad34C[0x454 - 0x34C]; float recoverySpeed;
    unsigned char pad458[0x470 - 0x458]; DriveVector localDirection, targetDirection;
    float pad490, acceleration;
    unsigned char pad498[6]; unsigned char allowAction;
    unsigned char pad49F[0x4AE - 0x49F]; short actionFrame;
    unsigned char pad4B0[12]; float lateralSpeed, inputHeading, targetHeading;
    unsigned char pad4C8[12]; int transition; float inputSpeed, strafeSpeed;
    unsigned char pad4E0[16]; DriveVector jumpDirection;
    unsigned char pad500[0x20]; float recoveryRate; short special;
    unsigned char pad526[7]; unsigned char useCurrentSpeed;
    unsigned char pad52E[0xA60 - 0x52E]; DriveVector pending;
    unsigned char padA70[0x14]; float pendingDamping;
    unsigned char padA88[0xC38 - 0xA88]; float plane;
    unsigned char padC3C[0x1440 - 0xC3C]; DriveVector savedDirection;
    unsigned char pad1450[4]; short overrideDirection;
    unsigned char pad1456[2]; float savedHeading;
    unsigned char pad145C[0x2294 - 0x145C]; int state;
    unsigned char pad2298[4]; int mode;
    unsigned char pad22A0[0x22C3 - 0x22A0]; unsigned char axisMode;
    unsigned char pad22C4[0x24B8 - 0x22C4]; float animationSpeed;
} PlayerDriveView;
extern PlayerDriveView D_00189E20;
/* Resident subview at the velocity vector; targetSpeed is 0xC4 bytes later. */
typedef struct DriveVelocityView {
    DriveVector velocity;
    unsigned char pad10[0xC4 - 0x10]; float targetSpeed;
} DriveVelocityView;
extern DriveVelocityView D_00189F10;
extern int D_L07_001A8FF0 MACRO_ADDR;
extern float D_L07_001A7DC0 MACRO_ADDR;
/* The settings prefix ends at the observed direction vector. */
typedef struct DriveSettings {
    unsigned char pad0[0x158]; float heading;
    unsigned char pad15C[0x370 - 0x15C]; DriveVector direction;
} DriveSettings;
extern DriveSettings D_L07_001B90C0;
extern void func_L00_002B54F8(float, float);
extern void func_L00_002B41B8(float, float);
extern void func_L00_002B3EF8(int, float, float, float);
extern void func_L01_002B6948(float);
extern void func_L00_002D3798(DriveVector *, DriveVector *, float);
extern void func_L00_002D3B58(DriveVector *, DriveVector *, float);
extern void func_L00_002D3BD8(void *, const void *, float);
extern float func_L00_002D3A58(char *);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA898(float *, float *, int, float, float, float, float);
extern float func_00283BE0(float, float);
extern void func_L00_002AA0F0(float, float, float);
extern float func_00282DB0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283C80(float, float);
extern void func_00282CC0(void *, void *, void *);


/* Update directional movement, including the state-44 yaw spring.
 * Shares the resident views and locomotion arms with func_L01_002B7360. */
void func_L07_002B5738(void)
{
    union { DriveVector q; float f[4]; } local;
    float smoothed;
    float oldHeading;
    int state = D_00189E20.state;

    if (state == 10) {
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(&D_00189E20.pendingResult, &D_00189E20.pending);
        D_00189E20.targetSpeed = D_00189E20.planarDistance;
    } else if (state == 16) {
        float speed;
        PlayerDriveView *hero = &D_00189E20;
        if (D_00189E20.frame > 54) {
            func_002AA2E8((float *)(&D_00189E20.recoveryRate), 0.0069444445f, 0.0019444445f);
        }
        if (D_00189E20.frame <= 54) speed = D_00189E20.recoverySpeed;
        else speed = 0.058333337f;
        hero->speed = speed;
        func_L00_002B41B8(0.012222223f, 0.0125f);
        func_L00_002D3BD8(&D_00189F10.velocity, &D_00189F10.velocity, 0.0f);
        func_L00_002D3798((DriveVector *)(&D_00189F10.velocity), (DriveVector *)(&D_00189F10.velocity), D_00189F10.targetSpeed);
    } else if (state == 27) {
        if (D_00189E20.frame > 40) {
            func_L00_002B3EF8(0, 0.04f, 0.2f, 0.250163913f);
            func_L01_002B6948(0.0055555557f);
        }
        if (13.0f <= D_00189E20.plane && D_00189E20.plane <= 30.0f) {
            if (27.0f < D_00189E20.plane)
                func_002AA2E8((float *)(&D_00189E20.lateralSpeed), 0.0f, 0.0022222223f);
            else func_002AA2E8((float *)(&D_00189E20.lateralSpeed), 0.033333335f, 0.0022222223f);
        }
        local.f[0] = D_00189E20.lateralSpeed;
        local.f[1] = 0.0f;
        local.f[2] = func_00282DB0(&D_00189E20.velocity, &D_00189E20.basis);
        func_00283098(&D_00189E20.velocity, &local, &D_00189E20);
    } else if (state == 11) {
        D_00189E20.heading = D_00189E20.targetHeading;
        qcopy(&D_00189E20.direction, &D_00189E20.targetDirection);
        func_L00_002B3EF8(0, 0.04f, 0.2f, 0.11635530f);
        if (D_00189E20.transition != 3) D_00189E20.targetSpeed = D_00189E20.inputSpeed;
        else D_00189E20.targetSpeed = 0.0f;
        if (D_00189E20.useCurrentSpeed != 0) {
            float rate = D_00189E20.animationSpeed * 0.083333336f;
            if (rate < 0.033333335f) rate = 0.033333335f;
            func_002AA2E8((float *)(&D_00189E20.strafeSpeed), rate, 0.010277778f);
            D_00189E20.targetSpeed = D_00189E20.planarDistance;
        } else {
            if (D_00189E20.allowAction != 0 && D_00189E20.actionFrame <= 11)
                func_002AA2E8((float *)(&D_00189E20.strafeSpeed), 0.0f, 0.0022222223f);
            else func_002AA2E8((float *)(&D_00189E20.strafeSpeed), 0.07f, 0.0022222223f);
        }
        if (D_00189E20.axisMode == 0) {
            ((float *)&D_00189E20.velocity)[0] = func_00283180(D_00189E20.inputHeading);
            ((float *)&D_00189E20.velocity)[0] *= D_00189E20.strafeSpeed;
            ((float *)&D_00189E20.velocity)[1] = func_00283198(D_00189E20.inputHeading);
            ((float *)&D_00189E20.velocity)[1] *= D_00189E20.strafeSpeed;
        } else {
            func_L00_002D3BD8(&local, &D_00189E20.localDirection, D_00189E20.strafeSpeed);
            func_L00_002D3B58(&local.q, &local.q, 0.0f);
            func_L00_002D3BD8(&D_00189E20.velocity, &D_00189E20.velocity, 0.0f);
            func_00282CC0(&D_00189E20.velocity, &D_00189E20.velocity, &local);
        }
        if (D_00189E20.axisMode == 0 && D_00189E20.useCurrentSpeed == 0) {
            float angle = func_00283C80(D_00189E20.targetHeading, D_00189E20.inputHeading);
            float cosine = func_00283198(angle);
            float amount = D_00189E20.inputSpeed * cosine;
            float component = func_00283180(D_00189E20.targetHeading);
            ((float *)&D_00189E20.velocity)[0] += component * amount;
            component = func_00283198(D_00189E20.targetHeading);
            ((float *)&D_00189E20.velocity)[1] += component * amount;
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(&D_00189E20.pendingResult, &D_00189E20.pending);
    } else if (state == 17) {
        D_00189E20.heading = ((float *)&D_00189E20.jumpDirection)[3];
        qcopy(&D_00189E20.direction, &D_00189E20.jumpDirection);
        if (D_00189E20.frame > 9) func_L00_002B3EF8(-1, 0.042f, 0.2f, 0.19780402f);
        if (D_00189E20.frame > 8) {
            if (D_00189E20.request == 0) {
                ((float *)&D_00189E20.velocity)[0] = func_00283180(D_00189E20.heading);
                ((float *)&D_00189E20.velocity)[0] *= 0.08166667f;
                ((float *)&D_00189E20.velocity)[1] = func_00283198(D_00189E20.heading);
                ((float *)&D_00189E20.velocity)[1] *= 0.08166667f;
            } else {
                func_L00_002D3BD8(&D_00189E20.velocity, &D_00189E20.velocity, 0.0f);
                func_00282F20(&local, &D_00189E20.direction, 0.08166667f);
                func_00282CC0(&D_00189E20.velocity, &D_00189E20.velocity, &local);
            }
        }
        D_00189E20.targetSpeed = D_00189E20.planarDistance;
    } else if (state == 129 && D_L07_001A8FF0 == 0) {
        func_L00_002B3EF8(0, 0.04f, 0.2f, D_00189E20.acceleration);
        D_00189E20.targetSpeed = 0.0f;
    } else {
        if (D_00189E20.state == 44) {
            float angle = D_00189E20.rotation;
            float delta;
            D_00189E20.yawError = func_002AA898(&angle, &D_00189E20.yawRate, 0,
                D_00189E20.heading, 0.017999999225139618f, 0.2f, 0.12217307090759277f);
            delta = func_00283BE0(angle, D_00189E20.rotation);
            func_L00_002AA0F0(0.0f, 0.0f, delta);
        } else {
            oldHeading = D_00189E20.heading;
            qcopy(&local, &D_00189E20.direction);
            if (D_00189E20.overrideDirection != 0) {
                D_00189E20.heading = D_L07_001B90C0.heading;
                qcopy(&D_00189E20.direction, &D_L07_001B90C0.direction);
            }
            func_L00_002B3EF8(0, 0.04f, 0.2f, D_00189E20.acceleration);
            if (D_00189E20.overrideDirection != 0) {
                D_00189E20.savedHeading = oldHeading;
                qcopy(&D_00189E20.savedDirection, &local);
                D_00189E20.heading = oldHeading;
                qcopy(&D_00189E20.direction, &D_00189E20.savedDirection);
            }
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(&D_00189E20.pendingResult, &D_00189E20.pending);
        {
            float damping = 0.0055555557f;
            if (D_00189E20.speed < D_L07_001A7DC0 * 0.00333333365f) {
                if (D_00189E20.mode == 2) {
                    float rate = D_00189E20.pendingDamping;
                    smoothed = func_L00_002D3A58((char *)&D_00189E20.velocity);
                    func_002AA2E8(&smoothed, 0.0f, rate);
                    func_L00_002D3BD8(&D_00189E20.velocity, &D_00189E20.velocity, smoothed);
                    return;
                }
                if (D_00189E20.contact != 0) damping = 0.00305555575f;
                else if (D_00189E20.special != 0) damping = 0.00055555557f;
                else damping = 0.0022222223f;
            }
            func_L01_002B6948(damping);
        }
    }
}

/* func_L07_00321D68 is in its qualified quadword-copy unit. */


int func_L07_00338D20(int a0)
{
    char *p;

    if (a0 == -1)
        return -1;
    p = *(char **)(D_L07_001FDEC0 + a0 * 4);
    if (p == 0)
        return -1;
    func_338D68(p);
    return 0;
}

INCLUDE_ASM("asm/levels", func_L07_0034AEC8);

void func_L07_003844C0(unsigned char *obj) {
    struct {
        Vec old, velocity, normal;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
        Vec position, spread;
    } frame;
    char *ctx = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, ctx, position);
    func_002FEE70(*(int *)(ctx + 0x1C), ctx, 0);
    func_00300190(position, position);
    func_00300248(ctx, ctx);
    func_002FE880(position, ctx, 0.0030555557f);
    func_L00_0038F178(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L00_00262570 + D_00139568[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        if (!func_00278E78() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            func_002FD1B8(D_L00_001B2630, D_L00_001B2638, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L00_001BF200.point.f[2];
            effect = func_00312D58(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = func_002A7940();
                speed = func_002A7878(0.0f, 0.050000004f);
                frame.spread.f[0] = func_00283180(angle) * speed;
                frame.spread.f[1] = func_00283198(angle) * speed;
                frame.spread.f[2] = func_002A7878(0.050000004f, 0.10833334f);
                lifetime = func_002A7820(90, 120);
                func_002BFB38(&frame.position, spread, func_002A77E0(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &D_L00_001BF200;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &D_L00_001BF200;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                func_00283028(&frame.velocity, ctx, &reread->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
                func_00282F20(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                func_00283028(&frame.velocity, ctx, &collision->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
                func_00282F20(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (obj[0xBC]) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
    }
}


void func_L07_003848D8(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, position, ctx);
    func_002AFFD8(position, &frame.surface, 0);
    func_00282D30(&frame.surface, &frame.surface, 0.0003055556f);
    func_L00_0038F3D8(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L00_00262570)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L00_001BF200;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L00_001BF200;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            func_00283028(&frame.velocity, ctx, &reread->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L00_001BF200;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            func_00283028(&frame.velocity, ctx, &collision->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
        else
            func_L00_0038E880(obj, &frame.velocity, &frame.normal);
    }
}



extern unsigned short *D_L07_001FAD60[];

extern unsigned char *D_L07_001B22DC[] __attribute__((sda));

extern int D_L07_001B22F8[] __attribute__((sda));

/* Returns the first entity of the group's id list whose state byte is 1, or 0. */
unsigned char *func_L07_003F6B88(int group) {
    unsigned short *p;
    unsigned char *e;

    for (p = D_L07_001FAD60[group];
         (unsigned char)group != 0xFF && group <= D_L07_001B22F8[0] && p != 0 &&
         ((short)p[-1] >= 0 || p == D_L07_001FAD60[group]);
         p++) {
        e = D_L07_001B22DC[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 1)
            return e;
    }
    return 0;
}

/* func_L07_003F6F00 is defined in L07_002B3580-g8.c (it reads five tuning words through $gp). */



/* func_L07_00416510 is defined in L07_00416510-g8.c. */
