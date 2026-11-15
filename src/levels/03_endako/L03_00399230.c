#include "common.h"

extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void func_324168(s32 a0, s32 a1);
extern void func_30D710(s32 a0, s32 a1);
extern void func_32C010();
extern void func_32C328(char *a0, char *a1, s32 a2);
extern void *func_31DD78(char *a0, s32 a1, s32 a2);
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern void func_311758(void *a0);
extern void part_emit_debris_burst(char *a0);
extern void func_31B920(char *a0, s32 a1, s32 a2);
extern f32  func_31BAE8(f32 a0, f32 a1);
extern f32  func_2F0000(f32 a0, f32 a1);
extern char D_L03_00188660[];
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern void func_2EEFE0(char *a0, char *a1, void *a2);
extern u8  *D_L03_001B2A1C;
extern f32  D_00189E20_19;
extern u8   D_001395BF;
extern void func_2BEE78(char *a0, char *a1, s32 a2, s32 a3);
extern void func_2B8300(s32 a0, s32 a1, char *a2);
extern void func_43B870(s32 a0);
extern void func_32F140(s32 a0, s32 a1);
extern char D_00189E20_11[];
extern u8   D_001395C0;
extern u8   D_001A7AFA;
extern u8   D_001A7B32;
extern u8   D_001A7AFB;
extern u8   D_001A7B33;
extern u8   D_001A7AFC;
extern u8   D_001A7B34;
extern void func_2B8510(s32 a0);
extern void func_313378(s32 a0);
extern void func_359FD0(char *a0, char *a1);
extern void func_30D710(s32 a0, s32 a1);
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ char position[0x10];
    /* 0x20 */ unsigned char state;
    /* 0x21 */ char pad21[0xB];
    /* 0x2C */ float scale;
    /* 0x30 */ unsigned char alpha;
    /* 0x31 */ char pad31;
    /* 0x32 */ unsigned short alpha2;
    /* 0x34 */ char pad34[0x34];
    /* 0x68 */ void *vars;
    /* 0x6C */ char pad6C[0x4C];
    /* 0xB8 */ int owner;
} L03SpawnObject;

typedef struct {
    /* 0x00 */ char a[0x10];
    /* 0x10 */ char b[0x10];
    /* 0x20 */ char pad20[0x44];
    /* 0x64 */ float v[3];
    /* 0x70 */ int kind;
    /* 0x74 */ char pad74;
    /* 0x75 */ unsigned char c;
    /* 0x76 */ unsigned char d;
    /* 0x77 */ unsigned char e;
    /* 0x78 */ unsigned char e2;
} L03SpawnState;




/* func_L03_003C6208 is defined in L03_003C6208-g8.c. */

/* func_L03_003C6A28 is defined in L03_00399230-6a28-g8.c. */

/* func_L03_003C6E50 is defined in L03_003C6E50-g8.c. */

/* func_L03_003C7018 is defined in L03_003C7018-menu.c. */

/* func_L03_003C72A8 is defined in L03_003C72A8-g8.c. */

/* Starts the console's remote view: clears its counters and moves it to state 2. */
void console_start_remote_view(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    *(u16 *)(vars + 0x106) = 0;
    *(s32 *)(vars + 0x100) = 0;
    *(u16 *)(moby + 0x34) |= 0x400;
    moby_set_state(moby, 2, -1);
    *(s32 *)(moby + 0x9C) = 0;
}

/* Marks the console as finished with its remote view. */
void console_end_remote_view(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    *(u16 *)(vars + 0x106) = 1;
    *(s32 *)(moby + 0x9C) = 1;
}

/* func_L03_003C7AA0 is matched in its own unit, src/levels/03_endako/L03_003C7AA0-qcopy.c (-frac2-qcopy). */

/* func_L03_003C7AC0 is matched in its own unit, src/levels/03_endako/L03_003C7AC0-g8.c (-G8). */

/* func_L03_003C7E20 is matched in its own unit, src/levels/03_endako/L03_003C7E20-g8.c (-G8). */

/* Builds the object's mode record: the private block gets the mode at +0xA0,
   the mode record is made from the caller's +0x10 and the object is released.
   The mode is kept in $v0 across the call, so the store lands in the call's
   delay slot. */
/* Stores a mode in the object, builds its mode record and then releases the object. */
void object_store_mode_release(char *moby, s32 mode)
{
    char buf[0x10];
    char *vars = *(char **)(moby + 0x68);

    *(s32 *)(vars + 0xA0) = mode;
    func_312898(mode, 2, buf);
    func_2EEFE0(vars + 0x90, moby + 0x10, buf);
    func_31B920(moby, 2, -1);
}

/* func_L03_003C8660 is matched in its own unit, src/levels/03_endako/L03_003C8660-qcopy.c (-frac2-qcopy). */

/* func_L03_003C8698 is defined in L03_003C8698.c. */

/* func_L03_003CA938 lives in the -G8 sibling L03_00399230-g8.c. */


/* func_L03_003CAD78 is defined in L03_003CAD78-g8.c. */

/* func_L03_003CB398 is defined in L03_003CB398-g8.c. */

/* func_L03_003CBC40 is defined in L03_003CBC40-g8.c. */

/* Picks the actor's next motion slot: case 0 draws a random turn rate, case 1
   re-checks the 0x70-stride table entry before refreshing the aim. */
/* Turns a spinning object toward a random heading and keeps its sound playing while it is active. */
void ant_ring_update(char *moby)
{
    char *self = moby;
    char *vars = *(char **)(self + 0x68);

    switch (*(u8 *)(self + 0x20)) {
    case 0:
        func_31B920(self, 1, -1);
        *(f32 *)(vars + 4) = func_31BAE8(60.0f, 90.0f) * 0.000290888245f;
        *(s32 *)(vars + 8) = -1;
        break;
    case 1: {
        s32 active = *(s32 *)vars;

        if (active != 0) {
            char *sound_slot = D_L03_00188660 + *(s32 *)(vars + 8) * 0x70;

            if (*(char **)(sound_slot + 0x88) != self || *(u8 *)(sound_slot + 0x74) == 0)
                *(s32 *)(vars + 8) = func_360A80(0, 4, self);
        }
        *(f32 *)(self + 0xF8) = func_2F0000(*(f32 *)(self + 0xF8),
            *(f32 *)(vars + 4));
        break;
    }
    }
}

/* func_L03_003CBE58 lives in the -G8 sibling L03_00399230-g8.c (it reads $gp-relative floats). */

/* func_L03_003CF0C0 is defined in L03_003CF0C0-g8.c. */

/* Tells whether the object is in state 2, 3 or 4. */
s32 actor_is_in_states_two_to_four(u8 *moby)
{
    return (u8)(moby[0x20] - 2) < 3;
}

/* func_L03_003CF7C8 is in L03_003CF7C8.c. */

/* Sets up an object on its first frame and then keeps updating its attached effect. */
void attached_effect_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(s32 *)(vars + 0x5C) |= 1;
        func_32C010(moby, vars + 0x60, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        func_32C328(moby, vars + 0x60, 0);
        break;
    }
}

/* func_L03_003D0300 is defined in L03_003D0300-g8.c. */

/* Waits until the object is hit or triggered, then runs its break routine and releases it. */
void break_on_hit_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(s32 *)(vars + 0x5C) |= 8;
        moby_set_state(moby, 1, -1);
        break;
    case 1: {
        char *hit = (char *)func_31DD78(moby, 0x10000, 0);
        s32 hit_moby;

        if (func_32AB10(moby) != 0
            || (hit != 0 && (hit_moby = *(s32 *)(hit + 0x20)) != 0
                && *(s16 *)(hit_moby + 0xAA) == 0xB1B /* moby class 2843 */)) {
            part_emit_debris_burst(moby);
            func_360A80(0, 0, moby);
            func_311758(moby);
        } else {
            *(u8 *)(moby + 0xA8) = 0xFF;
        }
        break;
    }
    }
}

/* func_L03_003D11E0 is in L03_003D11E0-g8.c. */

/* func_L03_003D1548 is in L03_003D1548-g8.c. */

/* func_L03_003D19C8 is in L03_003D19C8-g8.c. */


/* Ends a scripted scene: restores the linked object so it shows and can be hit again. */
void object_restore_linked_after_scene(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    func_324168(*(s32 *)(vars + 0x18), *(s32 *)(vars + 0x1C));
    func_30D710(0, -1);
    *(u16 *)(*(s32 *)(vars + 0x2C) + 0x34) |= 0x41;
    *(u16 *)(*(s32 *)(vars + 0x2C) + 0x34) &= ~0x1000;
    *(s32 *)(*(s32 *)(vars + 0x2C) + 0x98) = 0;
    *(u16 *)(*(s32 *)(vars + 0x2C) + 0x96) = 0;
}

/* func_L03_003D2018 is defined in L03_003D2018.c. */

extern u8 *D_L03_001B2A1C_tbl[] __asm__("D_L03_001B2A1C") __attribute__((sda));

/* Cleans up when the remote view ends: gives control back to the player and resets the camera. */
void console_remote_view_cleanup(char *moby)
{
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    char *hero;
    void *linked;

    func_2B8510(0);
    hero = D_00189E20_11;
    *(u16 *)(hero + 0x24FC) = 0;
    func_313378(*(u8 *)(self + 0xB0));
    D_001395C0 = 1;
    /* Resident bytes shared by all programs, written at their constant addresses
       (retail's lui $at,0x1A; sb form), as in 0033CB18.c. */
    *(u8 *)0x001A7B32 = 1;
    *(u8 *)0x001A7AFB = 1;
    *(u8 *)0x001A7B33 = 1;
    *(u8 *)0x001A7AFC = 1;
    *(u8 *)0x001A7B34 = 1;
    *(u8 *)0x001A7AFA = 1;
    func_2BEE78(self + 0x10, self + 0xF0, 0, 1);
    linked = *(void **)(vars + 0x2C);
    if (linked != 0) {
        func_311758(linked);
    }
    func_311758(D_L03_001B2A1C_tbl[0] + (*(s32 *)vars << 8));
    *(s32 *)(self + 0x78) = 0x80468CDC;
    func_32F140(*(s32 *)(vars + 0x24), -1);
    func_359FD0(hero + 0x80, hero + 0x90);
    func_30D710(0, -1);
}

/* func_L03_003D22C8 is defined in L03_00399230-g8.c. */

/* func_L03_003D2518 is defined in L03_003D2518.c. */


/* Spawns object class 0xB1B owned by `owner` and fills its 0x10E state record. */
extern void *CreateMoby(int);
extern void func_002A0F48(void *);

/* Spawns a kind-0xB1B object owned by OWNER at POSITION: opaque, a 0.015 rate, its state
   taking the two vectors, the three floats (in reverse order), a 0x10E word and the
   three bytes (the last twice). Returns the object, or 0. */
/* Creates a new object of one kind and fills in its start values. Returns it, or 0 if none could be made. */
u8 *object_spawn_and_init(char *owner, void *position, void *first, void *second,
                        u8 a, u8 b, u8 c, f32 x, f32 y, f32 z)
{
    u8 *object;
    u8 *state;

    object = CreateMoby(0xB1B /* moby class 2843 */);
    if (object != 0) {
        qcopy(object + 0x10, position);
        object[0x30] = *(u16 *)(object + 0x32) = 0xFF;
        *(f32 *)(object + 0x2C) = 0.015f;
        *(char **)(object + 0xB8) = owner;
        object[0x20] = 0;
        state = *(u8 **)(object + 0x68);
        qcopy(state, first);
        qcopy(state + 0x10, second);
        *(f32 *)(state + 0x64) = z;
        state[0x75] = a;
        state[0x76] = b;
        state[0x77] = c;
        state[0x78] = c;
        *(f32 *)(state + 0x68) = y;
        *(f32 *)(state + 0x6C) = x;
        *(s32 *)(state + 0x70) = 0x10E;
        func_002A0F48(object);
    }
    return object;
}

/* func_L03_003E1C88 is defined in L03_00399230-1c88-g8.c. */
