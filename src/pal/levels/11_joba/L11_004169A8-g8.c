/* func_PAL_L11_004169A8, the PAL copy of func_L11_00411D40: the same C, where the frame-based
 * delays, rates and speeds take their 50 Hz values and the barrel's fire test becomes
 * func_PAL_002AF6C0. -frac2-gcse-unsplit-edges gives the mount branches their shared address setup.
 */
#include "common.h"
typedef int TurretQuad __attribute__((mode(TI)));
typedef union { f32 f[4]; TurretQuad q; } TurretVec __attribute__((aligned(16)));
typedef struct {
 u8 pad0[0x10]; TurretVec unused; u8 pad20[0x20];
 s16 unk40, mount_delay; f32 pitch; s32 unk48, unk4C;
 u8 pad50[2]; s16 dismount_delay, barrel; u8 pad56[6];
 f32 rest_z, yaw_speed, pitch_speed; s32 beam, beam_frames;
 u8 matrix[0x40]; f32 aim[4]; u8 padC0[0x30]; s32 sound;
} TurretVars;
typedef struct { f32 size; u8 pad4[12]; f32 pos[3], alpha; } TurretBeam;
typedef struct {
 u8 pad0[0x80]; TurretVec pos, rot; u8 padA0[0x50]; u8 velocity[0xA0];
 u8 pad190[0x1ac]; u8 *ground; u8 pad340[0x1c70]; f32 stick_x, stick_y;
 u8 pad1FB8[0x2d8]; u8 *moby; s32 state; s32 pad2298, mode;
} TurretHero;
extern TurretHero D_00189E20 __attribute__((nosda));
extern struct { u8 pad0[0x6c]; void *owner; u8 slots[0]; } D_00188660 __attribute__((nosda));
extern s32 D_L11_001CAE40 __attribute__((nosda));
extern s32 D_L11_001A7BA4[] __attribute__((sda));
extern s32 D_L11_001A8FB4 SDATA(D_L11_001A8FB4);
extern s32 D_L11_001A8FB4_block[] __asm__("D_L11_001A8FB4") __attribute__((sda));
extern struct { u8 pad[0x1a0]; s32 held, pressed; } D_00138180 __attribute__((nosda));
extern f32 D_L11_001B0C90 __attribute__((sda)), D_L11_001B0C94 __attribute__((sda));
extern TurretVec D_L11_001B0CA0 SDATA(D_L11_001B0CA0);
extern TurretBeam D_L11_001C8A40[];
extern struct { u8 pad[0x160]; f32 unk160; s32 pad164, unk168, unk16C; f32 unk170; s32 pad174, unk178; } D_L11_001BA780;
extern s32 func_00282978(void *);
extern void func_0029FCC0(void *, s32, void *);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282A88(void *, s32);
extern void func_003355A8(s32);
extern s32 func_L11_002D8EF8(s32, s32);
extern void func_002A7470(void *, s32, s32, s32);
extern void func_00335438(void *, void *, s32, s32, s32);
extern f32 func_00282E48(void *, void *);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00283248(f32, f32);
extern void func_00283098(void *, void *, void *);
extern s32 func_L00_002FCF18(void *, f32, f32, f32, f32, f32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void func_00291450(s32);
extern f32 func_00282E20(void *);
extern void func_00282D90(void *, void *, f32);
extern void func_002E59F8(s32);
extern void func_002AEC48(void *, void *, s32, f32, f32);
extern s32 func_PAL_002AF6C0(void *, f32);
extern void func_002AF000(void *, f32, f32, f32);
extern void func_L11_00450328(void *, void *, void *, s32, f32);
extern f32 func_002A7878(f32, f32);
extern f32 func_00282DF0(void *);
extern void func_00282F20(void *, void *, f32);
extern s32 func_002A7820(s32, s32);
extern void func_L04_00358AE8(void *, void *, s32, s32, f32);
extern void func_002A0F48(void *);
extern void func_L11_004885A0(void);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_00273318(void *, s32, s32, s32, s32, s32, f32, f32, f32);

typedef struct {
 u8 pad0[0x10]; f32 pos[4]; u8 state; u8 pad21[0x13]; u16 flags;
 u8 pad36[0xc]; u8 seq, prev_seq; u8 pad44[4]; f32 speed;
 u8 pad4C[0x14]; u8 anim_flags; u8 pad61[7]; u8 *pvars;
 u8 pad6C[0x50]; u8 command; u8 padBD[3]; u8 matrix[0x30]; f32 rot[4];
} TurretMoby;

void func_PAL_L11_004169A8(TurretMoby *moby) {
    TurretVec seat;
    TurretVec offset;
    TurretVec tmp;
    TurretVec shot;
    TurretVec muzzle;
    TurretVec dir;
    TurretVec rnd;
    TurretVars *vars;
    TurretBeam *beam;
    float len;
    float stick_y;
    float yaw;
    int n;
    int i;
    int invert;

    vars = (TurretVars *)moby->pvars;
    if (D_L11_001CAE40 || moby->state == 6) return;
    moby->flags &= ~4;
    func_0029FCC0(moby, 3, &seat);
    seat.f[2] += 0.4f;
    if (moby->state >= 4) {
        if (func_00282978(&vars->mount_delay) != 0 && moby->command == 1 &&
            D_00189E20.mode != 0x14 && D_00189E20.mode != 7 && D_00189E20.state != 0x39 && D_L11_001A8FB4 == 0) {
            qcopy_nc(&D_00189E20.pos, &seat);
            qcopy_nc(&D_00189E20.rot, moby->rot);
            offset.f[0] = func_00283180(D_00189E20.rot.f[2]) * -0.4f;
            offset.f[1] = func_00283198(D_00189E20.rot.f[2]) * -0.4f;
            offset.f[2] = 0.0f;
            func_00282CC0(&D_00189E20.pos, &D_00189E20.pos, &offset);
            func_00282A88(&D_00189E20.velocity, 0xA0);
            if (D_00138180.pressed & 0x10) {
                func_003355A8(0);
                func_L11_002D8EF8(0, 1);
                moby->command = 2;
                moby->state = 4;
                moby->speed = 1.0f;
                func_002A7470(moby, 0, 0, 1);
            } else {
                if (moby->state != 5) {
                    vars->dismount_delay = 2;
                    func_00335438(D_00189E20.moby + 0x10, D_00189E20.moby + 0xf0, 0, 0, 0);
                    if (moby->prev_seq != 4) {
                        func_002A7470(moby, 4, 0, 4);
                    }
                }
                moby->state = 5;
                moby->speed = 2.0f;
            }
        } else if (moby->command == 2) {
            if (func_00282E48(&seat, D_00189E20.moby + 0x10) > 1.2f || D_00189E20.ground != moby) {
                moby->command = 0;
                vars->mount_delay = 50;
            }
        } else if (D_00189E20.mode != 0x14 && D_00189E20.mode != 7 &&
                   D_00189E20.state != 0x39 && D_00189E20.ground == moby &&
                   func_00282E48(&seat, D_00189E20.moby + 0x10) < 1.2f && vars->mount_delay == 0 && D_L11_001A8FB4_block[0] == 0) {
            moby->command = 1;
            func_L11_002D8EF8(0x31, 1);
        }
    }
    switch (moby->state) {
    case 0:
        moby->state = 4;
        vars->rest_z = moby->pos[2];
        vars->pitch = 0.0f;
        moby->rot[2] = 0.0f;
        vars->beam = -1;
        vars->mount_delay = 0;
        vars->unk48 = 0;
        vars->unk4C = 0;
        vars->unk40 = 0;
        D_00188660.owner = moby;
        return;
    case 4:
        if (func_00282E80(moby->pos, &D_00189E20.pos) < 4.0f) {
            moby->pos[2] += ((vars->rest_z - 1.0f) - moby->pos[2]) * 0.11f;
            if (D_00189E20.ground != moby) {
                yaw = func_00283B98(vars->yaw_speed,
                func_00283B98(func_00283BE0(
                    func_00283248(D_00189E20.pos.f[0] - moby->pos[0], D_00189E20.pos.f[1] - moby->pos[1]),
                    moby->rot[2]), 3.14159298f) * 0.01f) * 0.9f;
                vars->yaw_speed = yaw;
                moby->rot[2] = func_00283B98(moby->rot[2], yaw);
            } else vars->yaw_speed = 0.0f;
            func_00283098(&tmp, &D_L11_001B0CA0, moby->matrix);
            func_00282CC0(&tmp, &tmp, &seat);
            if (vars->beam == -1) {
                vars->beam_frames = 0;
                vars->beam = func_L00_002FCF18(&tmp, 0.4f, 0.0f, 4.0f, 4.0f, 4.0f);
                func_002E5CF8(2, 0, moby);
            } else {
                beam = &D_L11_001C8A40[vars->beam];
                beam->pos[0] = tmp.f[0];
                beam->pos[1] = tmp.f[1];
                beam->pos[2] = tmp.f[2];
                n = ++vars->beam_frames;
                if (n > 40 || !(n & 4)) {
                    beam->size = 4.0f;
                    beam->alpha = 0.4f;
                } else if (n >= 25 && (n & 0xA) == 0xA) {
                    beam->size = 4.0f;
                    beam->alpha = 0.4f;
                } else {
                    beam->alpha = 0.0f;
                }
            }
        } else {
            if (moby->pos[2] < vars->rest_z) {
                moby->pos[2] += 0.020000001f;
            } else {
                moby->pos[2] = vars->rest_z;
            }
            if (D_00189E20.ground != moby && vars->beam != -1) {
                func_002E5CF8(0, 0, moby);
                func_00291450(vars->beam);
                vars->beam = -1;
            }
        }
        break;
    case 5:
        D_00188660.owner = moby;
        if (moby->pos[2] < vars->rest_z) {
            moby->pos[2] += 0.020000001f;
        } else {
            moby->pos[2] = vars->rest_z;
        }
        tmp.f[0] = D_00189E20.stick_x;
        invert = -1;
        if (D_L11_001A7BA4[0]) invert = 1;
        stick_y = -D_00189E20.stick_y * invert;
        tmp.f[1] = stick_y;
        len = func_00282E20(&tmp);
        if (len > 1.0f) {
            func_00282D90(&tmp, &tmp, len);
        }
        vars->yaw_speed += -tmp.f[0] * 0.0012566373f;
        if (tmp.f[0] == 0.0f) vars->yaw_speed = 0.0f;
        if (vars->yaw_speed != 0.0f) {
            u8 *slot = (u8 *)&D_00188660 + vars->sound * 0x70;
            if (*(u8 **)(slot + 0x88) != moby || !slot[0x74])
                vars->sound = func_002E5CF8(3, 4, moby);
        } else {
            if (vars->sound != -1) {
                u8 *slot = (u8 *)&D_00188660 + vars->sound * 0x70;
                if (*(u8 **)(slot + 0x88) == moby && slot[0x74])
                    func_002E59F8(vars->sound);
            }
            vars->sound = -1;
        }
        vars->pitch_speed += -tmp.f[1] * 0.00045378567f;
        if (tmp.f[1] == 0.0f) vars->pitch_speed = 0.0f;
        moby->rot[2] = func_00283B98(moby->rot[2], vars->yaw_speed);
        vars->pitch = func_00283B98(vars->pitch, vars->pitch_speed);
        if (vars->pitch < -0.52359885f) {
            vars->pitch = -0.52359885f;
            vars->pitch_speed = 0.0f;
        } else if (vars->pitch > 0.52359885f) {
            vars->pitch = 0.52359885f;
            vars->pitch_speed = 0.0f;
        }
        vars->yaw_speed *= 0.97f;
        vars->pitch_speed *= 0.97f;
        vars->aim[1] = -vars->pitch;
        func_002AEC48(moby, vars->matrix, 2, 0.0432f, 0.43200004f);
        if (D_00138180.held & 0x20) {
            if (D_00138180.pressed & 0x20) {
                func_002A7470(moby, vars->barrel == 0 ? 3 : 2, 0, 1);
            } else if (moby->seq == 2) {
                if (func_PAL_002AF6C0(moby, 1.1666667f)) {
                    func_002AF000(&shot, 1.2f, moby->rot[2], vars->pitch);
                    func_0029FCC0(moby, 0, &muzzle);
                    func_L11_00450328(moby, &shot, &muzzle, 0, 6.0f);
                    func_002E5CF8(1, 0, moby);
                    D_L11_001BA780.unk160 = 0.03f;
                    D_L11_001BA780.unk168 = 8;
                    D_L11_001BA780.unk170 = 0.03f;
                    D_L11_001BA780.unk178 = 6;
                    D_L11_001BA780.unk16C = 0;
                    vars->barrel = 0;
                    for (i = 0; i < 5; i++) {
                        rnd.q = 0;
                        rnd.f[0] = func_002A7878(-1.0f, 1.0f);
                        rnd.f[1] = func_002A7878(-1.0f, 1.0f);
                        rnd.f[2] = func_002A7878(-1.0f, 1.0f);
                        dir.q = rnd.q;
                        func_00282F20(&dir, &dir, func_00282DF0(&shot) * 0.5799999f);
                        func_00282CC0(&dir, &shot, &dir);
                        func_00282F20(&dir, &dir, func_002A7878(0.060000002f, 0.120000005f));
                        func_L04_00358AE8(&muzzle, &dir, 0x5F2F4F6F, func_002A7820(4, 8), 50000.0f);
                    }
                    func_00282F20(&shot, &shot, 0.010000001f);
                    func_L04_00358AE8(&muzzle, &shot, 0x2F4F7F7F, func_002A7820(3, 6), 500000.0f);
                } else if (moby->anim_flags & 2) {
                    func_002A7470(moby, 3, 0, 1);
                }
            } else if (moby->seq == 3) {
                if (func_PAL_002AF6C0(moby, 1.1666667f)) {
                    func_002AF000(&shot, 1.2f, moby->rot[2], vars->pitch);
                    func_0029FCC0(moby, 1, &muzzle);
                    func_L11_00450328(moby, &shot, &muzzle, 0, 6.0f);
                    func_002E5CF8(1, 0, moby);
                    D_L11_001BA780.unk160 = 0.03f;
                    D_L11_001BA780.unk168 = 8;
                    D_L11_001BA780.unk170 = 0.03f;
                    D_L11_001BA780.unk178 = 6;
                    D_L11_001BA780.unk16C = 0;
                    vars->barrel = 1;
                    for (i = 0; i < 5; i++) {
                        rnd.q = 0;
                        rnd.f[0] = func_002A7878(-1.0f, 1.0f);
                        rnd.f[1] = func_002A7878(-1.0f, 1.0f);
                        rnd.f[2] = func_002A7878(-1.0f, 1.0f);
                        dir.q = rnd.q;
                        func_00282F20(&dir, &dir, func_00282DF0(&shot) * 0.5799999f);
                        func_00282CC0(&dir, &shot, &dir);
                        func_00282F20(&dir, &dir, func_002A7878(0.060000002f, 0.120000005f));
                        func_L04_00358AE8(&muzzle, &dir, 0x5F2F4F6F, func_002A7820(4, 8), 50000.0f);
                    }
                    func_00282F20(&shot, &shot, 0.010000001f);
                    func_L04_00358AE8(&muzzle, &shot, 0x2F4F7F7F, func_002A7820(3, 6), 500000.0f);
                } else if (moby->anim_flags & 2) {
                    func_002A7470(moby, 2, 0, 1);
                }
            }
        } else if (moby->prev_seq != 4 && (moby->anim_flags & 2)) {
            func_002A7470(moby, 4, 0, 1);
        }
        if (func_00282978(&vars->dismount_delay) != 0) {
            func_002A0F48(moby);
            moby->flags |= 4;
            func_L11_004885A0();
            func_0029FCC0(moby, 2, &tmp);
            func_002AF000(&shot, D_L11_001B0C90, moby->rot[2], vars->pitch);
            shot.f[2] += D_L11_001B0C94;
            func_00282CC0(&muzzle, &tmp, &shot);
            func_00335370(&muzzle);
            dir.f[0] = 0.0f;
            dir.f[1] = -vars->pitch;
            dir.f[2] = moby->rot[2];
            func_003353C8(&dir);
        }
        func_00273318(moby, 0xFF0F0FFF, 0, 0xD, -1, 4, 1.0f, 0.0f, 90.0f);
        break;
    }
}
