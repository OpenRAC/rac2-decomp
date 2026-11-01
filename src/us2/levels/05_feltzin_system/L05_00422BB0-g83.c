#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; s32 i[4]; } Vec;
typedef struct {
    u8 pad00[0x10];
    Vec position;
    u8 pad20[0x10];
    u8 opacity;
    u8 pad31;
    s16 mode;
    u16 flags;
    u8 pad36[0x8A];
    Vec forward;
    Vec right;
    Vec up;
} GateMoby;
typedef struct { s32 count; s32 pad04[3]; Vec points[1]; } GatePath;
typedef struct { s32 count; u8 pad04[0x28]; s32 reset; u8 pad30[8]; s32 path; } FeltzinState;
extern s32 D_L05_001B1364 __attribute__((sda));
extern GateMoby *D_L05_001B13B4 __attribute__((sda));
extern GateMoby *D_L05_001B13B8 __attribute__((sda));
extern s32 D_L05_001B13BC __attribute__((sda));
extern f32 D_L05_001B13C0 __attribute__((sda));
extern f32 D_L05_001B13C4 __attribute__((sda));
extern s32 D_L05_001B13C8 __attribute__((sda));
extern s32 D_L05_001B13CC __attribute__((sda));
extern s32 D_L05_001B13D0 __attribute__((sda));
extern s32 D_L05_001B13E4 __attribute__((sda));
extern u8 D_L05_001B3550[] MACRO_ADDR;
extern FeltzinState D_L05_00221D10;
extern u8 D_L05_001B96C0[];
extern GatePath *D_L05_001FE380[];
extern u8 *D_L05_001B251C;
extern s32 D_001A79F0;
extern u8 D_0019B278[];
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F28(s32 a0);
extern void func_L05_00379F18(s32 a0);
extern void func_0029F338(void *moby);
extern u8 **func_L05_00379EB8(void);
extern s32 func_L00_004272A0(void);
extern void func_L05_0037B280(u8 *a0, s32 a1);
extern GateMoby *func_0029EFD0(s32 oclass);
extern u8 *func_L05_00379ED0(s32 a0);
extern s32 func_L00_0042B730(u8 *a0);
extern void func_US2_L05_00422530(u8 *actor, s32 mission);
extern void func_US2_L05_00422780(u8 *a0, s32 a1);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_00282DD8(void *dst, void *a, void *b);
extern void func_00282F20(void *dst, void *src, f32 scale);
extern f32 func_00282DB0(void *a, void *b);
extern f32 func_00282E48(void *a, void *b);
extern void func_L05_0037ADD8(f32 a0);
extern void func_002E5DA0(s32 a0, s32 a1, void *a2, s32 a3);
extern void func_L05_00424980(void *moby, s32 a1);
extern void func_L05_00424970(void *moby, u32 color);
extern s32 func_L05_0042C928(void *pos, s32 a1, s32 a2, s32 a3);

/* Mission 3 of the Feltzin dispatcher: gates (class 0x114A) are spawned along the selected path,
   two at a time, each facing along the path. When the player's or the second tracked position's
   dot product with the current gate's forward axis turns positive (and differs from last frame's),
   a pass within 1.25 units of the gate scores, otherwise the miss count rises and the next gate
   takes over. Twelve misses or func_L00_0042B730 fail the mission; once no gate is left, the
   reward is paid through func_US2_L05_00422530. */
void func_US2_L05_00422E88(u8 *actor)
{
    struct { Vec up, pos, toward, away; } v;
    u8 *state = *(u8 **)(actor + 0x68);
    GatePath *path;
    GateMoby *gate;
    u8 *player;
    u8 **objects;
    s32 found;
    s32 n;
    f32 dotPlayer, dotOther;

    v.up.q = 0;
    v.up.f[2] = 1.0f;
    if (!D_L05_001B1364) {
        D_L05_001B13B4 = 0;
        D_L05_001B13B8 = 0;
        D_L05_001B13C0 = -1.0f;
        D_L05_001B13C4 = -1.0f;
        D_L05_001B13C8 = 0;
        D_L05_001B13CC = 0;
        D_L05_001B13D0 = 0;
        D_L05_001B1364 = 1;
        *(s32 *)D_L05_001B3550 = 0;
        D_L05_00221D10.reset = 0;
        func_002B7320();
        if (D_L05_001B13BC) {
            func_0029F338((void *)D_L05_001B13BC);
        }
        func_L05_0037B210();
        D_L05_001B13BC = 0;
        func_L05_00379F28(1);
        D_L05_00221D10.path = *(s32 *)(state + 0x20);
        func_L05_00379F18(0);
        objects = func_L05_00379EB8();
        found = func_L00_004272A0();
        for (n = 0; n < found; n++) {
            if (*(s16 *)(objects[n] + 0xAA) == 0xF82) {
                func_L05_0037B280(objects[n], 1);
            }
        }
        path = D_L05_001FE380[*(s32 *)(state + 0x20)];
        while ((!D_L05_001B13B4 || !D_L05_001B13B8) && D_L05_001B13CC != path->count) {
            if (path->points[D_L05_001B13CC].f[3] != -1.0f) {
                gate = func_0029EFD0(0x114A);
                gate->opacity = 255;
                gate->mode = 0x1FF;
                gate->flags |= 0x100;
                if (!D_L05_001B13B4) {
                    D_L05_001B13B4 = gate;
                } else {
                    D_L05_001B13B8 = gate;
                }
                if (D_L05_001B13CC == path->count - 1) {
                    func_00282CF0(&gate->forward, &path->points[D_L05_001B13CC - 1],
                                  &path->points[D_L05_001B13CC]);
                    gate->forward.i[3] = 0;
                    func_00282F20(&gate->forward, &gate->forward, -1.0f);
                } else {
                    func_00282CF0(&gate->forward, &path->points[D_L05_001B13CC + 1],
                                  &path->points[D_L05_001B13CC]);
                    gate->forward.i[3] = 0;
                    func_00282F20(&gate->forward, &gate->forward, 1.0f);
                }
                func_00282DD8(&gate->right, &gate->forward, &v.up);
                func_00282F20(&gate->right, &gate->right, 1.0f);
                func_00282DD8(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, &path->points[D_L05_001B13CC]);
                gate->position.i[3] = 0;
            }
            D_L05_001B13CC++;
        }
    }
    if (!D_L05_001B13B4 && !D_L05_001B13B8 && !D_L05_001B13E4) {
        func_US2_L05_00422530(actor, 3);
        return;
    }
    if (func_L00_0042B730(func_L05_00379ED0(0xF82))) {
        D_L05_001B13E4 = 1;
        func_US2_L05_00422780(actor, 3);
        func_L05_0037B210();
    } else if (D_L05_001B13D0 >= 12) {
        D_L05_001B13E4 = 1;
        func_US2_L05_00422780(actor, 3);
        func_L05_0037B210();
    }
    if (D_L05_001B13E4) {
        return;
    }
    if (++*(s32 *)D_L05_001B3550 < 2) {
        return;
    }
    player = D_L05_001B251C + (*(s32 *)(state + 0x24) << 8);
    qcopy(&v.pos, D_L05_001B96C0);
    func_00282CF0(&v.away, &v.pos, &D_L05_001B13B4->position);
    func_00282F20(&v.away, &v.away, 1.0f);
    func_00282CF0(&v.toward, player + 0x10, &D_L05_001B13B4->position);
    func_00282F20(&v.toward, &v.toward, 1.0f);
    dotPlayer = func_00282DB0(&D_L05_001B13B4->forward, &v.toward);
    dotOther = func_00282DB0(&D_L05_001B13B4->forward, &v.away);
    if ((dotPlayer != D_L05_001B13C0 && dotPlayer > 0)
        || (dotOther != D_L05_001B13C4 && dotOther > 0)) {
        path = D_L05_001FE380[*(s32 *)(state + 0x20)];
        if (func_00282E48(&v.pos, &D_L05_001B13B4->position) <= 1.25f
            || func_00282E48(player + 0x10, &D_L05_001B13B4->position) <= 1.25f) {
            func_L05_0037ADD8(0.5f);
            func_002E5DA0(15, 0, actor, 0xFBF);
        } else {
            func_L05_0037ADD8(-0.75f);
            D_L05_001B13D0++;
        }
        func_0029F338((void *)D_L05_001B13B4);
        D_L05_001B13B4 = D_L05_001B13B8;
        D_L05_001B13B8 = 0;
        while (!D_L05_001B13B8 && D_L05_001B13CC != path->count) {
            if (path->points[D_L05_001B13CC].f[3] != -1.0f) {
                gate = func_0029EFD0(0x114A);
                gate->opacity = 255;
                gate->mode = 0x1FF;
                gate->flags |= 0x100;
                D_L05_001B13B8 = gate;
                if (D_L05_001B13CC == path->count - 1) {
                    func_00282CF0(&gate->forward, &path->points[D_L05_001B13CC - 1],
                                  &path->points[D_L05_001B13CC]);
                    gate->forward.i[3] = 0;
                    func_00282F20(&gate->forward, &gate->forward, -1.0f);
                } else {
                    func_00282CF0(&gate->forward, &path->points[D_L05_001B13CC + 1],
                                  &path->points[D_L05_001B13CC]);
                    gate->forward.i[3] = 0;
                    func_00282F20(&gate->forward, &gate->forward, 1.0f);
                }
                func_00282DD8(&gate->right, &gate->forward, &v.up);
                func_00282F20(&gate->right, &gate->right, 1.0f);
                func_00282DD8(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, &path->points[D_L05_001B13CC]);
                gate->position.i[3] = 0;
            }
            D_L05_001B13CC++;
        }
    }
    D_L05_001B13C0 = dotPlayer;
    D_L05_001B13C4 = dotOther;
    if (D_L05_001B13B4) {
        func_L05_00424980((void *)D_L05_001B13B4, 1);
        if (D_L05_001B13B8) {
            func_L05_00424970((void *)D_L05_001B13B4, 0x40008000);
        } else {
            func_L05_00424970((void *)D_L05_001B13B4, 0x4000C6FF);
        }
    }
    if (D_L05_001B13B8) {
        func_L05_00424980((void *)D_L05_001B13B8, 1);
        func_L05_00424970((void *)D_L05_001B13B8, 0x40808000);
    } else if (!D_L05_001B13D0 && !D_L05_001B13BC && !D_0019B278[D_001A79F0 * 4]) {
        D_L05_001B13BC = func_L05_0042C928(&D_L05_001B13B4->position, 0, -1, -1);
    }
}
