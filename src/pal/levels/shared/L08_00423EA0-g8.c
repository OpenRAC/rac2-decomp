#include "common.h"

/* func_PAL_L08_00423EA0, the PAL copy of func_L08_0041EBF8: the same hover-vehicle update, where
   the per-frame float steps and timers are scaled for 50 Hz. D_L08_001B1B64 is read as a word here,
   since the scale needs its whole value. Same profile as the template's unit (config/cflags.txt). */

typedef struct VehicleVars VehicleVars;

/* The vehicle moby: only the fields this update touches. */
typedef struct VehicleMoby {
    u8 pad00[0x10];
    float pos[4];             /* 0x10 */
    u8 state;                 /* 0x20 */
    u8 pad21[3];
    u8 *pClass;               /* 0x24 */
    u8 pad28[4];
    float f2c;                /* 0x2c */
    u8 pad30;
    u8 drawn;                 /* 0x31 */
    u8 pad32[2];
    u16 modeBits;             /* 0x34 */
    u8 pad36[0x0c];
    u8 seqA;                  /* 0x42 */
    u8 seqB;                  /* 0x43 */
    u8 pad44[0x1c];
    u8 f60;                   /* 0x60 */
    u8 pad61[7];
    VehicleVars *pVars;       /* 0x68 */
    u8 pad6c[3];
    u8 f6f;                   /* 0x6f */
    u8 pad70[0x28];
    s32 collData;             /* 0x98 */
    s32 f9c;                  /* 0x9c */
    u8 padA0[8];
    u8 impact;                /* 0xa8 */
    u8 padA9[0x17];
    float mtx[3][4];          /* 0xc0 */
    float rot[4];             /* 0xf0 */
} VehicleMoby;

/* Its instance data (moby + 0x68). */
struct VehicleVars {
    float vel[4];             /* 0x00 */
    u8 pad10[0x10];
    float roll;               /* 0x20 */
    float pitch;              /* 0x24 */
    float yaw;                /* 0x28 */
    u8 pad2c[4];
    float home[4];            /* 0x30 */
    u8 pad40[8];
    float bobPhase;           /* 0x48 */
    float bobOffset;          /* 0x4c */
    float sway[2];            /* 0x50 */
    float lastZ;              /* 0x58 */
    float throttle;           /* 0x5c */
    float health;             /* 0x60 */
    u8 pad64[4];
    float f68;                /* 0x68 */
    u8 *f6c;                  /* 0x6c */
    u8 pad70[4];
    void *f74;                /* 0x74 */
    float power;              /* 0x78 */
    s16 timer7c;              /* 0x7c */
    u8 pad7e[0x0a];
    s16 timer88;              /* 0x88 */
    u8 mode8a;                /* 0x8a */
    u8 hitCooldown;           /* 0x8b */
    s16 f8c;                  /* 0x8c */
    u8 pad8e[2];
    u8 flash[7];              /* 0x90 */
    u8 flashRGB[3];           /* 0x97 */
    u8 pad9a[6];
    u8 *lastHit;              /* 0xa0 */
    s32 fa4;                  /* 0xa4 */
    s32 fa8;                  /* 0xa8 */
    u8 padac[4];
    struct {
        u8 hdr[0x10];
        float mtx[3][4];
    } rotor[3];               /* 0xb0 */
    float angle[3];           /* 0x170 */
    float f17c;               /* 0x17c */
    float rate[3];            /* 0x180 */
    s32 sound;                /* 0x18c */
    s32 f190;                 /* 0x190 */
    s32 f194;                 /* 0x194 */
    u8 pad198[4];
    s32 f19c;                 /* 0x19c */
    u8 pad1a0[4];
    s32 fx1a4;                /* 0x1a4 */
    s32 fx1a8;                /* 0x1a8 */
    s32 fx1ac;                /* 0x1ac */
    s32 fx1b0;                /* 0x1b0 */
    s32 fx1b4;                /* 0x1b4 */
    u8 pad1b8[8];
    float trail[4];           /* 0x1c0 */
};

typedef struct {
    u8 pad00[0x80];
    float position[4];
    float rotation[4];
    u8 padA0[0x2d0 - 0xa0];
    float cameraPosition[4];
    u8 pad2E0[0x33c - 0x2e0];
    u8 *attachment;
    s32 available;
    u8 pad344[0x1830 - 0x344];
    VehicleMoby *vehicle;
    u8 pad1834[8];
    float health;
    float maxHealth;
    u8 pad1844[4];
    s32 healthBar;
    u8 pad184C[0x2290 - 0x184c];
    VehicleMoby *moby;
    s32 animationState;
    u8 pad2298[4];
    s32 movementState;
    u8 pad22A0[0x22b5 - 0x22a0];
    u8 vehicleControl;
    u8 pad22B6[0x24cc - 0x22b6];
    s32 healthAvailable;
} VehiclePlayerState;
extern VehiclePlayerState D_00189E20_14;
extern s32 D_L08_001A8F00;
extern float D_L08_001B19B4 __attribute__((sda));
extern s32 D_L08_001B1B64 __attribute__((sda));
extern s32 func_002829A8(u8 *);
extern u8 *func_002A9640(u8 *, s32, s32);
extern void func_PAL_002AC290(u8 *, u8 *);
extern void func_PAL_002AC3C0(u8 *, u8 *);
extern void func_L08_00328BB0(s32, s32, s32, s32);

extern float D_L08_001B18D0 __attribute__((sda));
extern float D_L08_001B18D8 __attribute__((sda));
extern float D_L08_001B18E0 __attribute__((sda));
extern float D_L08_001B18E4 __attribute__((sda));
extern float D_L08_001B18E8 __attribute__((sda));
extern float D_L08_001B18EC __attribute__((sda));
extern float D_L08_001B18F0 __attribute__((sda));
extern float D_L08_001B18F4 __attribute__((sda));
extern float D_L08_001B18F8 __attribute__((sda));
extern float D_L08_001B18FC __attribute__((sda));
extern float D_L08_001B1900 __attribute__((sda));
extern float D_L08_001B1904 __attribute__((sda));
extern float D_L08_001B1908 __attribute__((sda));
extern float D_L08_001B190C __attribute__((sda));
extern float D_L08_001B1910 __attribute__((sda));
extern float D_L08_001B1914 __attribute__((sda));
extern s32 D_L08_001B1918 __attribute__((sda));
extern s32 D_L08_001B191C __attribute__((sda));
extern float D_L08_001B1920 __attribute__((sda));
extern float D_L08_001B1924 __attribute__((sda));
extern float D_L08_001B1928 __attribute__((sda));
extern float D_L08_001B192C __attribute__((sda));
extern float D_L08_001B1930 __attribute__((sda));
extern float D_L08_001B1934 __attribute__((sda));
extern float D_L08_001B1938 __attribute__((sda));
extern float D_L08_001B193C __attribute__((sda));
extern float D_L08_001B1940 __attribute__((sda));
extern float D_L08_001B1948 __attribute__((sda));
extern float D_L08_001B194C __attribute__((sda));
extern float D_L08_001B1950 __attribute__((sda));
extern float D_L08_001B1954 __attribute__((sda));
extern float D_L08_001B1958 __attribute__((sda));
extern float D_L08_001B19B8 __attribute__((sda));
extern float D_L08_001B19BC __attribute__((sda));
extern float D_L08_001B19C0 __attribute__((sda));
extern float D_L08_001B19C4 __attribute__((sda));
extern float D_L08_001B19C8 __attribute__((sda));
extern float D_L08_001B19CC __attribute__((sda));
extern float D_L08_001B19D0 __attribute__((sda));
extern float D_L08_001B19D4 __attribute__((sda));
extern float D_L08_001B19D8 __attribute__((sda));
extern float D_L08_001B19E4 __attribute__((sda));
extern float D_L08_001B1A14 __attribute__((sda));
extern float D_L08_001B1A18 __attribute__((sda));
extern float D_L08_001B1A1C __attribute__((sda));
extern float D_L08_001B1A20 __attribute__((sda));
extern float D_L08_001B1A24 __attribute__((sda));
extern float D_L08_001B1A28 __attribute__((sda));
extern float D_L08_001B1A30 __attribute__((sda));
extern s32 D_L08_001B1A44 __attribute__((sda));
extern s32 D_L08_001B1A48 __attribute__((sda));
extern s32 D_L08_001B1A78 __attribute__((sda));
extern float D_L08_001B1B1C __attribute__((sda));
extern float D_L08_001B1B20 __attribute__((sda));
extern float D_L08_001B1B24 __attribute__((sda));
extern s32 D_L08_001B1B28 __attribute__((sda));
extern float D_L08_001B1B2C __attribute__((sda));
extern float D_L08_001B1B30 __attribute__((sda));
extern float D_L08_001B1B34 __attribute__((sda));
extern float D_L08_001B1B38 __attribute__((sda));
extern float D_L08_001B1B3C __attribute__((sda));
extern s32 D_L08_001B1B40 __attribute__((sda));
extern float D_L08_001B1B44 __attribute__((sda));
extern float D_L08_001B1B48 __attribute__((sda));
extern float D_L08_001B1B4C __attribute__((sda));
extern float D_L08_001B1B50 __attribute__((sda));
extern float D_L08_001B1B54 __attribute__((sda));
extern s32 D_L08_001B1B58 __attribute__((sda));
extern float D_L08_001B1B5C __attribute__((sda));
extern float D_L08_001B1B60 __attribute__((sda));
extern float D_L08_001B1B7C __attribute__((sda));
extern float D_L08_001B1B80 __attribute__((sda));
extern s32 D_001A79F0;
extern s32 D_00138180[];
extern u8 D_00188660[];
typedef struct {
    u8 pad00[0x74];
    u8 active;
    u8 pad75[0x13];
    struct VehicleMoby *owner;
} EffectSlot;
typedef struct {
    u8 pad00[0x18];
    struct VehicleMoby *moby;
    u8 pad1C[4];
    float lowest[4];
    float point[4];
    float normal[4];
} CollisionResult;
extern CollisionResult D_L08_001BFF40;
typedef struct {
    u8 pad000[0x160];
    float amount;
    u8 pad164[4];
    s32 timer;
    s32 phase;
} ShakeState;
extern ShakeState D_L08_001B99C0;
extern u8 D_L08_001B9B00[];
extern float D_L08_001B031C[] __attribute__((sda));
extern void ref_L08_0041EBF8_00(void);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void func_0029F978(void *, s32, void *);
extern float func_002A0558(void *, void *);
extern s32 func_002B0C28(s32, s32, s32);
extern s32 func_PAL_L08_0031ACF8(s32, void *, s32);
extern void func_L01_00323310(s32, s32);
extern void func_PAL_L08_002D3078(s32, s32);
extern void func_PAL_L00_002D2668(s32, s32, float);
extern void func_002E59F8(s32);
extern s32 func_002E5DA0(s32, s32, void *, s32);
extern s32 func_00282978(void *);
extern void func_L08_0041E4F8(void *);
extern s32 func_002A77E0(s32);
extern void func_L08_0041E630(float *, float *, float *, float *, float *);
extern float func_00282DF0(void *);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282C48(float);
extern float func_L08_003277C0(s32, float);
extern void func_00283898(void *, s32, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_002A89A8(void *, s32, float);
extern s32 func_00278E78(void);
extern void func_002AB6D8(void *, void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_0029FCC0(void *, s32, void *);
extern s32 func_00278870(void *, float);
extern s32 func_00277258(void *, s32, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_PAL_L08_004239F0(void *, void *, s32, float, float, float, float, float, float);
extern void func_002A8C00(void *, void *, s32, void *, float);
extern void func_00277F48(void *, s32, void *, void *, float);
extern void func_PAL_L08_00423D30(void *);
extern void func_PAL_002AC718(void *, void *, void *, float, float, s32, s32, s32, float, float, float, float,
                          s32, float, s32, s32, s32, s32, s32);
extern void func_002AEF28(void *, void *, void *, float, float, float);
extern float func_00283CE0(s32);
extern s32 func_00283CF0(float);
extern void *func_L08_00435600(void *, void *);
extern void func_L08_004356A0(void *, void *);
extern void func_0029F338(void *);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_PAL_L08_0033B2D0(void *, s32, s32, void *, float, float);
extern void func_L08_00339220(void *, void *, s32, s32, float);
extern void func_00282948(void *);
#define PLAYER D_00189E20_14
#define HIT D_L08_001BFF40
/* An effect record (0x70 bytes) still owned by this moby and active. */
#define EFFECT(i) ((EffectSlot *)(D_00188660 + (i) * 0x70))
#define EFFECT_LIVE(i) (EFFECT(i)->owner == moby && EFFECT(i)->active)

/* Update the rideable hovering vehicle and its player-control state. */
void func_PAL_L08_00423EA0(VehicleMoby *moby)
{
    VehicleVars *p = moby->pVars;
    s32 fresh;
    float inputTurn, inputThrottle, inputPitch, inputBrake, inputStrafe;
    /* basis: the ground-aligned matrix (rows x, y, normal, zero translation); its rows
     * are reused below as the probe point, its offset and the contact normal. */
    float forward[4], thrust[4], nextPos[4], basis[4][4], angles[4], scratch[16];

    if (D_L08_001A8F00 == 2 || PLAYER.animationState == 97) {
        moby->drawn = 0;
        moby->modeBits |= 1;
        return;
    }
    moby->drawn = 1;
    moby->modeBits &= 0xfffe;
    if (func_002829A8(&p->hitCooldown))
        p->lastHit = 0;
    if (moby->state) {
        u8 *hit, *target;
        moby->pos[2] = p->lastZ;
        hit = func_002A9640(moby, 1, 0);
        if (hit && (target = *(u8 **)(hit + 0x20))) {
            s32 kind = *(s16 *)(target + 0xaa);
            if (kind != 0xeef && kind != 0x942 && kind != 0xfff &&
                (target != p->lastHit || !p->hitCooldown)) {
                p->flashRGB[0] = 0xd2;
                p->flashRGB[1] = 0xd2;
                p->flashRGB[2] = 0xd2;
                func_PAL_002AC290(moby, p->flash);
                p->health -= *(float *)(hit + 0x2c);
                PLAYER.health = p->health;
                if (p->health <= 0.0f)
                    moby->state = 5;
                p->lastHit = *(u8 **)(hit + 0x20);
                p->hitCooldown = (D_L08_001B1B64 * 5 + 2) / 6;
            }
        }
        moby->impact = 0xff;
    } else {
        p->lastZ = moby->pos[2];
    }
    func_PAL_002AC3C0(moby, p->flash);
    moby->f2c = *(float *)(moby->pClass + 0x24) * D_L08_001B19B4;
    if (PLAYER.vehicle == moby && moby->state)
        PLAYER.healthBar = (s32)(PLAYER.health / PLAYER.maxHealth * 200.0f);
    else
        PLAYER.healthBar = 200;
    fresh = 0;
    if (p->sound != -1)
        func_L08_00328BB0(p->sound, -1, -1, 1);
    switch (moby->state) {
    case 0:
        if (moby->seqB)
            func_PAL_002A7E68(moby, 0, 0, 10);
        if (!p->rotor[0].hdr[1]) {
            s32 j;
            for (j = 0; j < 3; j++)
                func_0029F978(moby, j + 2, &p->rotor[j]);
        }
        p->fa4 = 0;
        p->fa8 = 255;
        qcopy(p->home, moby->pos);
        qzero(p->vel);
        switch (D_001A79F0) {
        case 8:
            PLAYER.maxHealth = D_L08_001B19D4;
            break;
        case 19:
            PLAYER.maxHealth = D_L08_001B19D8;
            break;
        default:
            PLAYER.maxHealth = D_L08_001B19D0;
            break;
        }
        p->health = PLAYER.maxHealth;
        PLAYER.health = p->health;
        p->f74 = 0;
        moby->state = 1;
        p->fx1a4 = -1;
        p->power = 0.0f;
        p->fx1ac = 0;
        p->fx1b0 = 0;
        break;
    case 1:
        if (PLAYER.animationState != 28 && PLAYER.animationState != 22 &&
            PLAYER.animationState != 57 && PLAYER.animationState != 111 &&
            PLAYER.movementState != 2 && PLAYER.movementState != 4 &&
            PLAYER.movementState != 3 && PLAYER.movementState < 13 &&
            PLAYER.movementState != 7 && PLAYER.movementState != 10 &&
            PLAYER.movementState != 16 && PLAYER.movementState != 5 &&
            PLAYER.animationState != 98 && PLAYER.healthAvailable > 0 &&
            D_L08_001A8F00 == 0 && PLAYER.available &&
            (!PLAYER.attachment || (*(s16 *)(PLAYER.attachment + 0xaa) != 0x13e &&
                                    *(s16 *)(PLAYER.attachment + 0xaa) != 0x46f)) &&
            func_002A0558(moby, PLAYER.moby) < D_L08_001B18E0 &&
            PLAYER.animationState != 49) {
            s32 ready = func_002B0C28(7, 0x12ea, 1) != 0;
            if ((D_00138180[0x69] & 16) && ready) {
                p->f190 = 0;
                fresh = 1;
                func_PAL_L08_0031ACF8(0, ref_L08_0041EBF8_00, 1);
                func_L01_00323310(p->f194, p->f19c);
                func_PAL_L08_002D3078(49, 0);
                func_PAL_L00_002D2668(D_L08_001B1918, 0, 15.0f);
                qcopy(PLAYER.rotation, moby->rot);
                qcopy(PLAYER.position, moby->pos);
                PLAYER.vehicle = moby;
                moby->state = 3;
                if (p->fx1b4 != -1 && EFFECT_LIVE(p->fx1b4))
                    func_002E59F8(p->fx1b4);
                p->fx1b4 = -1;
                PLAYER.moby->f9c = -1;
                PLAYER.vehicleControl = 1;
            }
        }
        if (!EFFECT_LIVE(p->fx1b4))
            p->fx1b4 = func_002E5DA0(9, 4, moby, 0x85c);
        /* Activation continues through the control/movement path this frame. */
    case 3:
        moby->collData = 0;
        func_00282978(&p->timer7c);
        inputStrafe = inputBrake = inputPitch = inputThrottle = inputTurn = 0.0f;
        if (moby->state == 3) {
            PLAYER.vehicleControl = 1;
            if (D_00138180[0x68] & 0x80) {
                if ((moby->seqA < 1 || moby->seqA > 3) && moby->seqB != 1 && moby->seqB != 2 &&
                    moby->seqB != 3) {
                    if (moby->seqB != 1)
                        func_PAL_002A7E68(moby, 1, 0, 10);
                } else if (moby->f60 & 2) {
                    if (moby->seqA == 1) {
                        if (moby->seqB != 2)
                            func_PAL_002A7E68(moby, 2, 0, 10);
                    } else if (moby->seqB == 3 || moby->seqB == 0) {
                        if (moby->seqB != 1)
                            func_PAL_002A7E68(moby, 1, 0, 10);
                    }
                }
                p->power -= D_L08_001B1A14 * 1.2f;
                if (!func_002A77E0(9) || (D_00138180[0x69] & 0x80))
                    func_L08_0041E4F8(moby);
            } else {
                if (moby->f60 & 2) {
                    if ((moby->seqA >= 1 && moby->seqA <= 2) ||
                        moby->seqB == 1 || moby->seqB == 2) {
                        if (moby->seqB != 3)
                            func_PAL_002A7E68(moby, 3, 0, 10);
                    } else if (moby->seqB) {
                        func_PAL_002A7E68(moby, 0, 0, 10);
                    }
                }
                p->power += D_L08_001B1A18 * 1.2f;
            }
            if (D_L08_001B191C != D_L08_001B1918 && D_L08_001B1918 != -1)
                func_PAL_L00_002D2668(D_L08_001B1918, 0, 15.0f);
            func_L08_0041E630(&inputTurn, &inputThrottle, &inputPitch, &inputBrake, &inputStrafe);
            inputTurn *= p->power;
        } else {
            p->power -= D_L08_001B1A14 * 1.2f;
            if (moby->f60 & 2) {
                if ((moby->seqA >= 1 && moby->seqA <= 2) ||
                    moby->seqB == 1 || moby->seqB == 2) {
                    if (moby->seqB != 3)
                        func_PAL_002A7E68(moby, 3, 0, 2);
                } else if (moby->seqB) {
                    func_PAL_002A7E68(moby, 0, 0, 2);
                }
            }
        }
        if (p->power > 1.0f)
            p->power = 1.0f;
        else if (p->power < 0.0f)
            p->power = 0.0f;
        {
            float sign = 1.0f;
            float hoverHeight, rate, speed, speedMax, steer, turn, turnRad, bank;
            float turnFactor, damping, push, acceleration, spin, strength, height;
            float *angle, *rates;
            s32 special, grounded, collision;

            inputThrottle *= p->power;
            inputBrake += 1.0f - p->power;
            inputStrafe *= p->power;
            hoverHeight = D_L08_001B190C * p->power + D_L08_001B1A1C * (1.0f - p->power);
            if (moby->state == 3)
                hoverHeight = D_L08_001B190C * p->power + D_L08_001B1A20 * (1.0f - p->power);
            p->throttle = inputThrottle;
            inputPitch *= 0.017453294f;
            inputPitch *= D_L08_001B1948;
            speed = func_00282DF0(p) * p->power;
            speedMax = D_L08_001B1908 * 0.020000001f;
            rate = D_L08_001B1950 * 0.020000001f;
            steer = (speed < rate ? speed : rate) / rate * D_L08_001B194C + (1.0f - D_L08_001B194C) +
                    D_L08_001B1A24 * (1.0f - p->power);
            turn = inputTurn * steer * 0.0003490659f;
            p->yaw = func_00283B98(p->yaw, D_L08_001B18F8 * turn);
            turnRad = inputTurn * 0.017453294f;
            bank = D_L08_001B1930 * turnRad;
            bank *= p->power;
            bank *= D_L08_001B193C * inputThrottle + (1.0f - D_L08_001B193C);
            bank -= moby->rot[0];
            bank *= D_L08_001B192C;
            p->roll += bank;
            forward[0] = func_00283180(p->yaw);
            forward[1] = func_00283198(p->yaw);
            forward[2] = 0.0f;
            if (inputThrottle < 0.0f)
                inputThrottle *= D_L08_001B1934;
            if (inputThrottle < 0.0f)
                sign = -1.0f;
            turnFactor = func_00282C48(inputTurn), damping = func_L08_003277C0(2, (speedMax - speed) / speedMax);
            push = inputThrottle + D_L08_001B1938 * turnFactor * sign;
            push *= 0.00040000002f;
            push *= D_L08_001B1904;
            acceleration = push * damping;
            spin = p->power * 0.0003490659f;
            p->rate[0] = spin * D_L08_001B18D0;
            strength = D_L08_001B18D8 * 0.0003490659f;
            rates = p->rate;
            angle = p->angle;
            {
                s32 k;
                for (k = 1; k < 3; k++) {
                    float t = speed / speedMax + inputThrottle;
                    float x;
                    if (!(k & 1))
                        x = t - inputTurn;
                    else
                        x = t + inputTurn;
                    x = x * strength * 0.5f;
                    if (k & 1)
                        x = -x;
                    p->rate[k] = x;
                }
            }
            {
                s32 k;
                for (k = 0; k < 3; k++) {
                    angle[k] = func_00283B98(angle[k], rates[k]);
                    func_00283898(p->rotor[k].mtx, k == 0 ? 2 : 0, angle[k]);
                }
            }
            func_00282CC0(nextPos, moby->pos, p->vel);
            height = func_002A89A8(nextPos, 0, 0.5f);
            special = 0;
            if (func_00278E78() == 1 || func_00278E78() == 11)
                special = 1;
            if (moby->pos[2] < height + hoverHeight + 0.3f && special)
                moby->state = 5;
            grounded = 1;
            p->vel[2] -= D_L08_001B1920 * 0.00040000002f;
            if (height != 0.0f) {
                func_00282F20(basis[2], HIT.normal, 1.0f);
                func_00282DD8(basis[1], moby->mtx, basis[2]);
                func_00282DD8(basis[0], basis[1], basis[2]);
                qzero_nc(basis[3]);
                func_002AB6D8(basis, angles);
                {
                    float tilt = inputPitch * 0.5f;
                    p->pitch = func_00283B98(p->pitch,
                        func_00283BE0(func_00283B98(-angles[1], tilt * (D_L08_001B1A28 * (p->power + 1.0f))),
                                      p->pitch) * D_L08_001B1940);
                }
                if (nextPos[2] < height + hoverHeight + 0.2f) {
                    grounded = 0;
                    if (nextPos[2] + 0.1f < height || special) {
                        nextPos[2] = height;
                        func_00282D30(p, p, D_L08_001B1928);
                    }
                    p->vel[2] += ((height + hoverHeight - nextPos[2]) * D_L08_001B1910 - p->vel[2]) *
                                 D_L08_001B1910;
                    if (inputBrake > 0.0f) {
                        float brake = 1.0f - D_L08_001B1954 * inputBrake;
                        p->vel[0] *= brake;
                        p->vel[1] *= brake;
                    }
                    func_00282D30(p, p, D_L08_001B18FC);
                    func_00283698(scratch, moby->mtx);
                    func_002830C0(p, p, scratch);
                    p->vel[1] *= D_L08_001B1900;
                    func_00283098(p, p, moby->mtx);
                }
                func_00282F20(thrust, moby->mtx, acceleration);
                if (p->pitch < -0.78539824f) {
                    if (thrust[2] > 0.0f)
                        thrust[2] = 0.0f;
                    func_00282F20(thrust, thrust, acceleration);
                } else {
                    float climb = D_L08_001B1920 * 0.000100000005f;
                    if (thrust[2] > climb)
                        thrust[2] = climb;
                    func_00282F20(thrust, thrust, acceleration);
                }
                {
                    float side = inputStrafe * 0.00040000002f;
                    func_00282F20(scratch, moby->mtx[1], D_L08_001B1A30 * side * p->power);
                }
                func_00282CC0(thrust, thrust, scratch);
                func_00282CC0(p, p, thrust);
            }
            qcopy(moby->pos, nextPos);
            func_0029FCC0(moby, 0, basis[0]);
            basis[0][2] += D_L08_001B1914 - D_L08_001B1A1C;
            func_00282CF0(basis[1], moby->pos, basis[0]);
            moby->collData = 0;
            collision = func_00278870(basis[0], D_L08_001B1914);
            if (!collision) {
                if (D_001A79F0 == 19) {
                    s32 saved = PLAYER.moby->collData;
                    PLAYER.moby->collData = 0;
                    collision = func_00277258(basis[0], 0, moby, D_L08_001B1914);
                    PLAYER.moby->collData = saved;
                } else {
                    collision = func_00277258(basis[0], 2, moby, D_L08_001B1914);
                }
            }
            moby->collData = *(s32 *)(moby->pClass + 0x10);
            if (collision) {
                if (func_00278E78() == 1 || func_00278E78() == 11)
                    moby->state = 5;
                if (HIT.moby != PLAYER.moby) {
                    float give = 1.0f;
                    if (grounded) {
                        HIT.point[0] -= basis[0][0];
                        HIT.point[1] -= basis[0][1];
                        if (HIT.point[0] < 0.060000002f)
                            HIT.point[0] *= p->power;
                        if (HIT.point[1] < 0.060000002f)
                            HIT.point[1] *= p->power;
                        HIT.point[0] += basis[0][0];
                        HIT.point[1] += basis[0][1];
                    } else {
                        give = p->power;
                    }
                    func_00282CC0(moby->pos, HIT.point, basis[1]);
                    func_00282DD8(basis[3], HIT.normal, p);
                    func_00282DD8(basis[2], basis[3], HIT.normal);
                    func_00282F20(basis[2], basis[2], 1.0f);
                    func_00282F20(p, basis[2], func_00282DB0(p, basis[2]) * give);
                    func_00282D30(p, p, D_L08_001B1924);
                    if (moby->pos[2] < p->f17c)
                        moby->state = 5;
                }
            }
        }
        if (moby->state == 3) {
            if (moby->pos[2] < HIT.lowest[2])
                HIT.lowest[2] = moby->pos[2];
            if (p->power < 0.98f && (D_00138180[0x68] & 0x80)) {
                if (p->fx1a8 == 0) {
                    if (!p->fx1ac)
                        func_002E5DA0(1, 0, moby, 0x85c);
                    p->fx1a8 = 2;
                    p->fx1ac = 12;
                } else if (p->fx1a8 == 2) {
                    if (!EFFECT_LIVE(p->fx1a4)) {
                        p->fx1a4 = func_002E5DA0(2, 4, moby, 0x85c);
                        if (p->fx1b4 != -1 && EFFECT_LIVE(p->fx1b4))
                            func_002E59F8(p->fx1b4);
                        p->fx1b4 = -1;
                    }
                }
                if (p->f68 < D_L08_001B031C[0]) {
                    func_PAL_L08_004239F0(moby, HIT.lowest, D_L08_001B1B40,
                        D_L08_001B1B38, D_L08_001B1B3C, D_L08_001B1B34,
                        D_L08_001B1B34, D_L08_001B1B44, D_L08_001B1B48);
                    if (!func_002A77E0(11)) {
                        D_L08_001B99C0.amount = (1.0f - p->power) * 0.05f;
                        D_L08_001B99C0.timer = 12;
                        D_L08_001B99C0.phase = 0;
                    }
                } else {
                    func_PAL_L08_004239F0(moby, HIT.lowest, D_L08_001B1B58,
                        D_L08_001B1B50, D_L08_001B1B54, D_L08_001B1B4C,
                        D_L08_001B1B4C, D_L08_001B1B5C, D_L08_001B1B60);
                }
                if (p->fx1b4 != -1 && EFFECT_LIVE(p->fx1b4))
                    func_002E59F8(p->fx1b4);
                p->fx1b4 = -1;
            } else if (p->fx1a8 == 2) {
                if (p->fx1a4 != -1 && EFFECT_LIVE(p->fx1a4))
                    func_002E59F8(p->fx1a4);
                p->fx1a4 = -1;
                if (p->fx1ac == 0)
                    func_002E5DA0(4, 0, moby, 0x85c);
                p->fx1a8 = 0;
                p->fx1ac = 12;
            } else if (!EFFECT_LIVE(p->fx1b4)) {
                p->fx1b4 = func_002E5DA0(9, 4, moby, 0x85c);
            }
            func_PAL_L08_004239F0(moby, HIT.lowest, D_L08_001B1B28,
                D_L08_001B1B20, D_L08_001B1B24, D_L08_001B1B1C,
                D_L08_001B1B2C, D_L08_001B1B30, 1.0f);
        }
        func_0029FCC0(moby, 0, basis[0]);
        basis[0][2] += D_L08_001B19C8;
        {
            float reach = D_L08_001B19B8;
            switch (D_001A79F0) {
            case 8:
                reach = D_L08_001B19BC;
                break;
            case 19:
                reach = D_L08_001B19C0;
                break;
            }
            func_002A8C00(basis[2], moby, 0x10000, p, reach);
        }
        func_00277F48(basis[0], 0, moby, basis[2], D_L08_001B1958);
        if (func_00282DF0(p) > D_L08_001B19CC * 0.020000001f) {
            func_0029FCC0(moby, 1, scratch);
            func_00277F48(scratch, 0, moby, basis[2], D_L08_001B19C4);
        }
        if (!fresh && PLAYER.vehicle == moby && (D_00138180[0x69] & 16)) {
            func_PAL_L08_00423D30(moby);
            moby->state = 1;
            if (!EFFECT_LIVE(p->fx1b4))
                p->fx1b4 = func_002E5DA0(9, 4, moby, 0x85c);
        }
        break;
    case 2:
    case 4:
    case 6:
        break;
    case 5:
        func_PAL_L08_00423D30(moby);
        func_0029FCC0(moby, 0, forward);
        func_PAL_002AC718(moby, p, forward, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f,
                      1, 1, -1, 0, 0x810001);
        qcopy(moby->pos, p->home);
        moby->state = 0;
        break;
    }
    p->lastZ = moby->pos[2];
    {
        float step = p->power * 0.0003490659f;
        p->bobPhase = func_00283B98(p->bobPhase, D_L08_001B18E8 * step);
    }
    p->bobOffset = func_00283198(p->bobPhase) * D_L08_001B18E4 * p->power;
    moby->pos[2] += p->bobOffset * p->power;
    {
        float k = p->power * 0.0003490659f;
        func_002AEF28(moby, &p->sway[0], &p->sway[1], D_L08_001B18EC * 0.017453294f,
                      D_L08_001B18F0 * k, D_L08_001B18F4 * k);
    }
    moby->rot[2] = p->yaw;
    moby->rot[0] = func_00283B98(moby->rot[0], p->roll);
    moby->rot[1] = func_00283B98(moby->rot[1], p->pitch);
    if (moby->state == 3) {
        if (D_001A79F0 == 8 || D_001A79F0 == 19) {
            switch (p->mode8a) {
            case 0:
                if (p->f68 < D_L08_001B031C[0]) {
                    p->mode8a = 1;
                    p->timer88 = 0;
                }
                break;
            case 1:
                (p->timer88)++;
                if (p->timer88 > (D_L08_001B1A78 * 5 + 2) / 6)
                    p->timer88 = (D_L08_001B1A78 * 5 + 2) / 6;
                if (p->f68 > D_L08_001B031C[0])
                    p->mode8a = 3;
                else if (p->timer88 >= (D_L08_001B1A78 * 5 + 2) / 6)
                    p->mode8a = 2;
                break;
            case 2:
                if (p->f68 > D_L08_001B031C[0])
                    p->mode8a = 3;
                break;
            case 3:
                func_00282978(&p->timer88);
                if (p->f68 < D_L08_001B031C[0])
                    p->mode8a = 1;
                else if (p->timer88 == 0)
                    p->mode8a = 0;
                break;
            }
            if (p->mode8a && p->f6c) {
                u8 *other = *(u8 **)(p->f6c + 0x68);
                float num = func_00283CE0(*(s32 *)(other + 4));
                p->f8c =
                    func_00283CF0(D_L08_001B19E4 * num / ((func_00283CE0(*(s32 *)other) * 60.0f * 5 + 2) / 6));
            } else {
                p->f8c = 0x200;
            }
            if (p->f6c) {
                if (!p->f74)
                    p->f74 = func_L08_00435600(moby, p->f6c + 0x10);
                else
                    func_L08_004356A0(p->f74, p->f6c + 0x10);
            } else if (p->f74) {
                func_0029F338(p->f74);
                p->f74 = 0;
            }
        }
        func_00282F20(forward, moby->mtx, -0.5f);
        if (forward[2] < 0.0f)
            forward[2] = 0.0f;
        forward[2] += 1.5f;
        func_00282CC0(PLAYER.position, forward, moby->pos);
        qcopy(PLAYER.cameraPosition, PLAYER.position);
        PLAYER.cameraPosition[2] = moby->pos[2];
        qcopy(PLAYER.rotation, moby->rot);
    }
    moby->collData = *(s32 *)(moby->pClass + 0x10);
    if (moby->drawn && func_00282E48(moby->pos, D_L08_001B9B00) < 64.0f) {
        func_002A93B0(moby);
        moby->f6f = 60;
    }
    if (p->sound != -1)
        func_L08_00328BB0(p->sound, -1, 0, 0);
    if (p->throttle != 0.0f) {
        if (!EFFECT_LIVE(p->fx1a4)) {
            p->fx1a4 = func_002E5DA0(0, 4, moby, 0x85c);
            func_PAL_L08_0033B2D0(moby, p->fx1a4, 0, p->trail, D_L08_001B1B7C, D_L08_001B1B80);
        } else {
            func_00282CF0(forward, moby->pos, p->trail);
            forward[2] = 0.0f;
            func_L08_00339220(moby, p->trail, D_L08_001B1A44, D_L08_001B1A48, func_00282DF0(forward));
            if (p->fx1b4 != -1 && EFFECT_LIVE(p->fx1b4))
                func_002E59F8(p->fx1b4);
            p->fx1b4 = -1;
        }
    } else if (p->fx1a8 != 2) {
        if (p->fx1a4 != -1 && EFFECT_LIVE(p->fx1a4))
            func_002E59F8(p->fx1a4);
        p->fx1a4 = -1;
    }
    func_00282948(&p->fx1ac);
}
