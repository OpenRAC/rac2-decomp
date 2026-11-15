#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned int u32;

typedef unsigned char u8;

typedef unsigned short u16;

typedef short s16;

typedef float f32;

/* Small-data controls: the four measured globals the level's script hooks share. */
extern s32 D_L11_001B1530 __attribute__((sda));

extern s32 D_L11_001B1540 __attribute__((sda));

extern s32 D_L11_001B1550 __attribute__((sda));

extern s32 D_L11_001B1560 __attribute__((sda));

extern void func_3004A8(void *);

extern void func_4882F0(void *, void *, s32, s32, s32);

extern void func_488268(s32, s32);

extern void func_4881A8(void *);

extern void func_488200(void *);

extern u32 D_L11_001B32E8[1];

extern u8 D_L11_001BA8C0[];

extern u8 *D_L11_001B359C[3] __attribute__((sda));

extern u8 *D_L11_001FC420[];

extern float func_282E48(void *, void *);

extern void func_32C9E0();

extern void func_440C90(u8 *);

/* One class record of the measured class table: six halfwords, then the two flag
   bytes at 0x14 and 0x15.  The record is 26 bytes long. */
typedef struct {
    s16 half[6];
    u8 pad0[8];
    u8 flag14;
    u8 flag15;
    u8 pad1[4];
} JobaClassRecordView;

typedef struct {
    s32 count;
    JobaClassRecordView *records;
} JobaClassTableView;

/* The class table itself: an array of pointers to the per-class entries. */
extern u32 D_L11_001B14F8 __attribute__((sda));

/* Checks the state's six counters against the class record and reports whether the
   class may still be used. */
/* Tells whether the current wave is finished: all fighters of the wave were used and none are left alive. */
s32 func_L11_00442710(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 index = *(s16 *)(state + 0x1F0);
    s32 cls = *(s16 *)(state + 0x1F2);
    JobaClassTableView *entry = ((JobaClassTableView **)&gArenaChallengeTable)[index];
    JobaClassRecordView *rec = &entry->records[cls];
    u32 *counters = (u32 *)(state + 0x100);
    s32 same = 1;
    s32 i;
    s32 result;
    for (i = 0; i < 6; i++) {
        same &= (counters[i] == (u32)rec->half[i]);
    }
    if (rec->flag14 != 0) {
        same &= *(u32 *)(state + 0x118);
    }
    if (rec->flag15 != 0) {
        same &= *(u32 *)(state + 0x11C);
    }
    result = 0;
    if (*(u32 *)(state + 0x140) == 0) {
        if (same != 0) {
            result = 1;
        }
    }
    return result;
}

/* The group count and the entity table's base, as the walks below reach them: the count through
   $gp, the base as a bare symbol (a three-word `sda` array keeps the `lui`/`lw` pair). */
extern s32 D_L11_001B35B8 __attribute__((sda));

extern u8 *D_L11_001B359C_abs[3] __attribute__((sda));

extern char D_00189EA0[];

extern s32 func_L11_00442B60(u8 *);

extern s32 func_L02_003D77B8(u8 *);

extern float func_00282E80(void *, void *);

#define GROUP(off) (*(s32 *)(state + (off)))

/* Claims the slot at the state's count (+0x18C) in its 0x120 table: an empty slot is taken as it
   is, a filled one only when func_L02_003D77B8 refuses its entity and the count is still below
   the class record's limit (byte 0x16), which then advances. The slot gets the first entity of the
   group's id list (state word 0xC4) that func_L11_00442B60 and func_L02_003D77B8 both accept;
   when the slot is still empty after that walk, the first entity that func_L02_003D77B8 accepts
   and that lies more than 30.0 from D_00189EA0 takes it. The table address is formed at each use
   (retail does), which lets GCSE hoist it ahead of the first walk. */
/* Picks the next fighter that will lead the current squad. */
void func_L11_00440E18(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    JobaClassTableView *entry = ((JobaClassTableView **)&gArenaChallengeTable)[*(s16 *)(state + 0x1F0)];
    JobaClassRecordView *rec = &entry->records[*(s16 *)(state + 0x1F2)];
    u8 *slot = *(u8 **)(state + (*(s32 *)(state + 0x18C) << 2) + 0x120);
    s32 ok = 0;
    u16 *listStart;
    u8 **slots;
    u16 *cursor;
    u8 *member;

    if (slot != 0) {
        if (HasFreeChildSlotInState2(slot) == 0 && *(s32 *)(state + 0x18C) < *((u8 *)rec + 0x16) - 1) {
            ok = 1;
            *(s32 *)(state + 0x18C) = *(s32 *)(state + 0x18C) + 1;
        }
    } else {
        ok = 1;
    }
    if (ok) {
        if (GROUP(0xC4) == 0xFF)
            return;
        listStart = (u16 *)gGroupIdLists[GROUP(0xC4)];
        if (listStart == 0)
            return;
        for (cursor = listStart; (GROUP(0xC4) & 0xFF) != 0xFF && GROUP(0xC4) <= D_L11_001B35B8 && cursor != 0 &&
                    ((cursor != 0 && (s16)cursor[-1] >= 0) || cursor == (u16 *)gGroupIdLists[GROUP(0xC4)]);
             cursor++) {
            member = D_L11_001B359C_abs[0] + ((*cursor & 0x7FFF) << 8);
            if (member == 0)
                break;
            if (IsEntityFarAndInDirection(member)) {
                if (HasFreeChildSlotInState2(member)) {
                    slots = (u8 **)(state + 0x120);
                    *(u8 **)((u8 *)slots + (GROUP(0x18C) << 2)) = member;
                    break;
                }
            }
        }
        slots = (u8 **)(state + 0x120);
        if (*(u8 **)((u8 *)slots + (GROUP(0x18C) << 2)) == 0) {
            for (cursor = (u16 *)gGroupIdLists[GROUP(0xC4)];
                 (GROUP(0xC4) & 0xFF) != 0xFF && GROUP(0xC4) <= D_L11_001B35B8 && cursor != 0 &&
                 ((cursor != 0 && (s16)cursor[-1] >= 0) || cursor == (u16 *)gGroupIdLists[GROUP(0xC4)]);
                 cursor++) {
                member = D_L11_001B359C_abs[0] + ((*cursor & 0x7FFF) << 8);
                if (member == 0)
                    break;
                if (HasFreeChildSlotInState2(member)) {
                    if (vec_distance_xy(member + 0x10, gHeroPosition) > 30.0f) {
                        slots = (u8 **)(state + 0x120);
                        *(u8 **)((u8 *)slots + (GROUP(0x18C) << 2)) = member;
                        return;
                    }
                }
            }
        }
    }
}

/* The four angle and length constants the script reads through $gp. */
extern f32 D_L11_001B15AC __attribute__((sda));

extern f32 D_L11_001B15B0 __attribute__((sda));

extern f32 D_L11_001B15B4 __attribute__((sda));

extern f32 D_L11_001B15B8 __attribute__((sda));

extern float func_00283B98(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern float func_002A7878(float, float);

extern void func_00282CC0(u8 *, u8 *, u8 *);

extern void func_002833F0(u8 *, u8 *);

extern u8 *func_L11_004417E8(u8 *);

extern void func_L11_00436910(char *, int, int);

extern void func_L11_004496A0(char *, int, int);

extern void func_L11_0044C328(char *, int, int);

extern void func_L11_00452C58(char *, int, int);

extern void func_L11_00454C78(char *, int, int);

/* arms the script bridge over the measured buffers and starts it on the shared slot */
/* Starts the short intro script that moves the camera. */
void func_L11_00443380(void) {
    s32 buffer[4];
    func_3004A8(buffer);
    func_4882F0(&D_L11_001B1550, &D_L11_001B1560, 1, 0, 0);
    func_488268(2, 0x168);
    func_4881A8(&D_L11_001B1530);
    func_488200(&D_L11_001B1540);
}

/* Turns the script's angle around the actor and hands the result to the level's
   helpers when the angle is small enough. */
/* Keeps the intro script going and changes the arena state once the camera has turned far enough. */
void func_L11_004433D8(u8 *obj) {
    s32 objState;

    D_L11_001B32E8[0] = 1;
    if (func_282E48(D_L11_001BA8C0, &D_L11_001B1530) < 0.01f) {
        objState = obj[0x20];
        if (objState == 4) {
            func_32C9E0(obj, 7, -1);
        } else if (objState == 5) {
            func_32C9E0(obj, 6, -1);
        }
        func_488268(1, 0);
        func_4881A8(&D_L11_001B1530);
        func_488200(&D_L11_001B1540);
    }
}

/* Turns the script's angle around the actor, hands the result to the level's helpers
   and counts the class the script's identifier names. */
/* Places a fighter in the arena, turns it toward the middle and starts it. It also counts the fighter as used. */
s32 func_L11_00440970(u8 *object, u8 *fighter) {
    u8 *state = *(u8 **)(object + 0x68);
    f32 turnStep = D_L11_001B15B4;
    f32 value;

    value = FastAddRotations(*(f32 *)(state + 0x19C), turnStep);
    *(f32 *)(state + 0x19C) = value;
    value = FastSinOrCosA(value);
    *(f32 *)(fighter + 0x10) = D_L11_001B15B8 * value;
    value = FastSinOrCosB(*(f32 *)(state + 0x19C));
    *(f32 *)(fighter + 0x14) = D_L11_001B15B8 * value;
    FastVecAdd(fighter + 0x10, fighter + 0x10, GetArenaCenterPoint(object));
    *(f32 *)(fighter + 0x18) = RandomFloatRange(D_L11_001B15AC, D_L11_001B15B0);
    *(f32 *)(fighter + 0xF4) = -1.570796489715576171875f;
    *(s32 *)(fighter + 0xF0) = 0;
    *(f32 *)(fighter + 0xF8) = *(f32 *)(state + 0x19C);
    euler_rotation_basis(fighter + 0xC0, fighter + 0xF0);
    switch (*(s16 *)(fighter + 0xAA)) {
    case 0xD98 /* Joba security robot */:
        InitSecurityRobot(fighter, 0, 1);
        *(s32 *)(state + 0x100) += 1;
        break;
    case 0xDCF /* Joba smasher robot */:
        InitSmasherRobot(fighter, 0, 1);
        *(s32 *)(state + 0x104) += 1;
        break;
    case 0xDF4 /* moby class 3572 */:
        InitFlamethrowerRobot(fighter, 0, 1);
        *(s32 *)(state + 0x108) += 1;
        break;
    case 0xDF7 /* moby class 3575 */:
        InitJobaDroneState(fighter, 0, 1);
        *(s32 *)(state + 0x10C) += 1;
        break;
    case 0xD37 /* moby class 3383 */:
        InitEnemyState(fighter, 0, 1);
        *(s32 *)(state + 0x114) += 1;
        break;
    }
    return 1;
}

/* The group count once more, read bare (`lui`/`lw`) in these walks, under a second name: the
   scalar above is read through $gp. */
extern s32 D_L11_001B35B8_1[] __attribute__((sda));
extern f32 D_L11_001B1614 __attribute__((sda));
extern f32 D_L11_001B1618 __attribute__((sda));
extern s32 func_00312B58(u8 *);
extern s32 func_L02_00416800(u8 *);
extern s32 func_002A77E0(s32);
extern void func_L02_00416720(u8 *, u8 *, f32, f32);

/* Leaves the function when the group is 0xFF or empty; the braces it opens close in END_IDS. */
#define FOR_EACH_ID(p, off) \
    if (GROUP(off) == 0xFF) \
        return; \
    { u16 *q = (u16 *)gGroupIdLists[GROUP(off)]; \
    if (q == 0) \
        return; \
    for (p = q; (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L11_001B35B8_1[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)gGroupIdLists[GROUP(off)]); \
         p++)
#define END_IDS }
/* One half: collect the entities of group OFF for which func_00312B58 holds (counting the
   others in m), then, up to 1000 passes over the group at state word 0x17C while m is below
   the record's limit, hand one collected entity at a time to func_L02_00416720 with an entity
   of that group. */
#define HALF(limit, off) \
    { \
        s32 n, m, i, k; \
        if (*(s16 *)(rec + (limit)) != 0) { \
            m = 0; \
            n = 0; \
            for (k = 15; k >= 0; k--) \
                buf[k] = 0; \
            FOR_EACH_ID(p, off) { \
                e = gMobyTable_L11[0] + ((*p & 0x7FFF) << 8); \
                if (e == 0) \
                    break; \
                if (IsMobyInState6(e) == 0) { \
                    m++; \
                } else { \
                    buf[n] = e; \
                    n++; \
                } \
            } END_IDS \
            if (n != 0) { \
                for (i = 0; i < 1000 && m < *(s16 *)(rec + (limit)); i++) { \
                    FOR_EACH_ID(p, 0x17C) { \
                        e = gMobyTable_L11[0] + ((*p & 0x7FFF) << 8); \
                        if (e == 0) \
                            break; \
                        if (n <= 0) \
                            break; \
                        if (IsStateOneWithClearedVars(e) != 0 && RandomIntBelow(6) == 0) { \
                            n--; \
                            BindCapturedObjectToMoby(e, buf[n], D_L11_001B1614 * 0.016666668f, \
                                              D_L11_001B1618 * 2.908882452175021e-4f); \
                            m++; \
                            break; \
                        } \
                    } END_IDS \
                } \
            } \
        } \
    }

/* For each of the object's two groups (state words 0x178 and 0x174), gathers the entities
   func_00312B58 accepts and counts the ones it refuses; then, while that count is below the
   limit of the class record the state names (the halfword at 0x10, at 0x12 for the second
   group), hands the gathered entities, last first, to func_L02_00416720 together with entities
   of the group at state word 0x17C. */
/* Hands waiting fighters to their spawn points until enough of each group are in the arena. */
void func_L11_00442E38(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    JobaClassTableView *entry =
        ((JobaClassTableView **)&gArenaChallengeTable)[*(s16 *)(state + 0x1F0)];
    u8 *rec = (u8 *)&entry->records[*(s16 *)(state + 0x1F2)];
    u8 *buf[16];
    u16 *p;
    u8 *e;

    HALF(0x10, 0x178)
    HALF(0x12, 0x174)
}

extern const f32 D_L11_001B15BC __attribute__((sda));
extern const f32 D_L11_001B15C0 __attribute__((sda));
extern const f32 D_L11_001B15C4 __attribute__((sda));
extern const f32 D_L11_001B15C8 __attribute__((sda));
extern const f32 D_L11_001B15CC __attribute__((sda));
extern const f32 D_L11_001B15D0 __attribute__((sda));
extern const f32 D_L11_001B15D4 __attribute__((sda));
extern const f32 D_L11_001B15D8 __attribute__((sda));
extern const f32 D_L11_001B15DC __attribute__((sda));
extern const f32 D_L11_001B15E0 __attribute__((sda));
extern const f32 D_L11_001B15E4 __attribute__((sda));
extern const f32 D_L11_001B15E8 __attribute__((sda));
extern const f32 D_L11_001B15EC __attribute__((sda));
extern const f32 D_L11_001B15F0 __attribute__((sda));
extern const f32 D_L11_001B15F4 __attribute__((sda));
extern u8 D_00189E20[];
extern void *func_L00_002D70A0(s32);
extern void func_L00_002D7140(void *);
extern void func_L00_00424F58(void *, f32, f32);

/* The object state's guide vector (state +0x170), allocated while the mode byte is 8 or 9:
   it is set from one of five read-only small-data vectors chosen by the target's class. */
#define GUIDE (*(f32 **)(s + 0x170))
#define SET_GUIDE(x, y, z) (GUIDE[0] = (x), GUIDE[1] = (y), GUIDE[2] = (z))

/* Sets the point the camera guide follows, depending on which kind of boss is fighting. */
void func_L11_004423F8(u8 *obj) {
    u8 *s = *(u8 **)(obj + 0x68);

    if (obj[0x20] == 8 || obj[0x20] == 9) {
        if (GUIDE == 0) {
            GUIDE = AllocCameraOverrideSlot(5);
        } else if (*(void **)(s + 0x180) != 0) {
            if (*(u8 **)(s + 0x184) == 0) {
                SET_GUIDE(D_L11_001B15BC, D_L11_001B15C0, D_L11_001B15C4);
                return;
            }
            if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xD4A /* moby class 3402 */)
                SET_GUIDE(D_L11_001B15D4, D_L11_001B15D8, D_L11_001B15DC);
            if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xD4B /* moby class 3403 */)
                SET_GUIDE(D_L11_001B15EC, D_L11_001B15F0, D_L11_001B15F4);
            else if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xB3A /* Arachnoid */)
                SET_GUIDE(D_L11_001B15E0, D_L11_001B15E4, D_L11_001B15E8);
        } else if (obj[0x20] == 9) {
            u8 *player = gHeroState;
            SET_GUIDE(D_L11_001B15C8, D_L11_001B15CC, D_L11_001B15D0);
            if (*(f32 *)(player + 0x88) > ((f32 *)GetArenaCenterPoint(obj))[2] + 16.0f) {
                if (*(u16 *)(obj + 0x96) < 500)
                    SetCameraStrengthAndSteerToTarget(GetArenaCenterPoint(obj), 0.17453295f, 0.0f);
                else
                    SetCameraStrengthAndSteerToTarget(GetArenaCenterPoint(obj), 0.008726647f, 0.0f);
            }
        } else {
            SET_GUIDE(D_L11_001B15BC, D_L11_001B15C0, D_L11_001B15C4);
        }
    } else {
        EndCameraOverride(GUIDE);
        GUIDE = 0;
    }
}

#undef SET_GUIDE
#undef GUIDE
