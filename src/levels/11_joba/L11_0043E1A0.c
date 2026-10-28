#include "include_asm.h"
#include "common.h"







/* Dispatches an indexed polygon query through the already integrated helper. */
typedef struct { s32 field00; u8 remainder[12]; } JobaPolygonHeaderView;

extern JobaPolygonHeaderView *D_L11_001FF580[];

extern s32 func_002A8AF0(f32 *point, f32 *vertices, s32 count);

/* Consumes one positive counter selected by the measured class identifier. */
typedef struct {
    u8 prefix[0xe0];
    s32 fielde0, fielde4, fielde8, fieldec, fieldf0, fieldf4;
} JobaClassCounterView;


/* bumps the 0xFFFF-saturated counter, then starts the state's timer and reports the object */
extern u8 D_L11_004465F8[];
extern void func_300150(void *);
extern void func_2F8AD0(void *, void *);
extern void func_31F338(void);

void func_L11_00440160(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    u16 *counter = (u16 *)(obj + 0x96);
    if (*counter <= 0xFFFE) {
        *counter = *counter + 1;
    }
    func_300150(state + 0x190);
    func_2F8AD0(D_L11_004465F8, obj);
    func_31F338();
}

/* clears the state's six-word block and its counters, then restarts the object */
extern void func_32C9E0();

void func_L11_004401C0(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 i;
    s32 *p = (s32 *)(state + 0x134);
    *(s16 *)(state + 0x1F0) = -1;
    *(s16 *)(state + 0x1E8) = 0;
    *(s16 *)(state + 0x1F2) = -1;
    for (i = 5; i >= 0; i--) {
        *p = 0;
        p--;
    }
    *(s32 *)(state + 0x18C) = 0;
    *(s32 *)(state + 0x180) = 0;
    func_32C9E0(obj, 1, -1);
    *(float *)(state + 0x1BC) = 1.0f;
    *(s32 *)(state + 0x170) = 0;
}

/* func_L11_00440238 lives in L11_00440238-g8.c (its source unit has the retail small-data view). */
INCLUDE_ASM("asm/levels", func_L11_00440360);

/* func_L11_00440790 lives in L11_00440238-g8.c (its source unit has the retail small-data view). */

/* Finds the class entry the identifier names and hands it to that class's handler. */
extern u8 *D_L11_001FC420[];

extern u8 *D_L11_001B359C __attribute__((section(".sdata")));

extern void func_L11_003F2F38(u8 *);

extern void func_L11_00439950(u8 *);

INCLUDE_ASM("asm/levels", func_L11_00440868);

/* func_L11_00440970 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* Hands a target point to the first free class-0xD37 moby (state 1) in this moby's
   group: records the caller as its owner, places it at the target facing -pi/2, sets
   its heading toward the target from the caller and starts it; 0 when the group is
   empty or has no free member. */
typedef struct {
    u8 pad0[0x10];
    float pos[4];
    u8 state;
    u8 pad21[0x89];
    short oclass;
    u8 padAC[0xC];
    void *owner;
    u8 padBC[4];
    float rot[12];
    float fF0;
    float fF4;
    float fF8;
} GroupMoby440B28;
typedef struct {
    u8 pad0[0xC0];
    int group;
} GroupVars440B28;
extern char *D_001B359C __attribute__((sda));
extern unsigned short *D_001FC420[];
extern float func_00283248(float, float);
extern void func_002833F0(void *, void *);
extern void func_L11_00436910(void *, int, int);

int func_L11_00440B28(u8 *object, float *target)
{
    GroupMoby440B28 *member;
    unsigned short *list;
    unsigned short *p;
    int group;
    float dx;

    group = ((GroupVars440B28 *)*(u8 **)(object + 0x68))->group;
    if (group == 0xFF)
        return 0;
    list = D_001FC420[group];
    if (list == 0)
        return 0;
    p = list;
    do {
        member = (GroupMoby440B28 *)(D_001B359C + (*p & 0x7FFF) * 0x100);
        if (member != 0 && member->state != 0xFE && member->state != 0xFD &&
            member->oclass == 0xD37 && member->state == 1) {
            member->owner = object;
            qcopy(member->pos, target);
            member->fF0 = 0.0f;
            member->fF4 = -1.5707965f;
            dx = target[0] - ((float *)func_L11_004417E8(object))[0];
            member->fF8 = func_00283248(dx, target[1] - ((float *)func_L11_004417E8(object))[1]);
            func_002833F0(member->rot, &member->fF0);
            func_L11_00436910(member, 0, 1);
            return 1;
        }
    } while ((short)*p++ >= 0);
    return 0;
}

/* Returns the state's 0x200 halfword. */
s16 func_L11_00440C80(u8 *obj) {
    return *(s16 *)(*(u8 **)(obj + 0x68) + 0x200);
}

INCLUDE_ASM("asm/levels", func_L11_00440C90);

/* func_L11_00440E18 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* Walks the state's 0x120 slots in order and renews each live entry through the two shared helpers. */
extern s32 func_417238(s32);

extern void func_4172E8(s32);

void func_L11_00441090(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 i;
    for (i = 0; i <= *(s32 *)(state + 0x18C); i++) {
        s32 *slot = (s32 *)(state + 0x120 + i * 4);
        if (slot[0] == 0) {
            continue;
        }
        if (func_417238(slot[0]) == 0) {
            continue;
        }
        func_4172E8(slot[0]);
    }
}

/* Clears the state's 0x120 slot table once every live entry has been accepted. */
extern s32 func_417270(s32);

void func_L11_00441108(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 i;
    s32 accepted = 1;
    for (i = 0; i <= *(s32 *)(state + 0x18C); i++) {
        s32 *slot = (s32 *)(state + 0x120 + i * 4);
        if (slot[0] == 0) {
            continue;
        }
        if (func_417270(slot[0]) != 0) {
            continue;
        }
        accepted = 0;
        break;
    }
    if (accepted != 0) {
        s32 j;
        for (j = 0; j <= *(s32 *)(state + 0x18C); j++) {
            *(s32 *)(state + 0x120 + j * 4) = 0;
        }
        *(s32 *)(state + 0x18C) = 0;
    }
}

/* hands every entry of the class list to its measured handler */
extern u8 *D_L11_001FC420[];

extern u8 *D_L11_001B359C;

extern void func_L11_00449878(u8 *);

extern void func_L11_0044C4F0(u8 *);

extern void func_L11_00452DF8(u8 *);

extern void func_L11_00454DD8(u8 *);

extern void func_L11_00456540(u8 *);

extern void func_L11_00436A78(u8 *);

extern void func_L11_00439BF0(u8 *);

extern void func_L11_0043AB28(u8 *);

extern void func_L11_003F3098(u8 *);

/* The class table base read through an incomplete `sda` array: cc1 emits the one-instruction
   load, which the assembler expands absolute (`lui $r` / `lw $r,%lo($r)`) and which is not
   hoisted out of the loop, as retail has it (docs/COMPILER-NOTES.md). */
extern u8 *D_L11_001B359C_base[] __asm__("D_L11_001B359C") __attribute__((sda));

void func_L11_004411C8(u8 *obj)
{
    s32 index = *(s32 *)(*(u8 **)(obj + 0x68) + 0xC0);
    u16 *p;
    u8 *list;
    u8 *entry;

    if (index == 0xFF)
        return;
    list = D_L11_001FC420[index];
    if (list == 0)
        return;
    p = (u16 *)list;
    do {
        entry = D_L11_001B359C_base[0] + ((*p & 0x7FFF) << 8);
        switch (*(s16 *)(entry + 0xAA)) {
        case 0xD98:
            func_L11_00449878(entry);
            break;
        case 0xDCF:
            func_L11_0044C4F0(entry);
            break;
        case 0xDF4:
            func_L11_00452DF8(entry);
            break;
        case 0xDF7:
            func_L11_00454DD8(entry);
            break;
        case 0xDF9:
            func_L11_00456540(entry);
            break;
        case 0xD37:
            func_L11_00436A78(entry);
            break;
        case 0xD4A:
            func_L11_00439BF0(entry);
            break;
        case 0xD4B:
            func_L11_0043AB28(entry);
            break;
        case 0xB3A:
            func_L11_003F3098(entry);
            break;
        }
    } while (*(s16 *)p++ >= 0);
}

/* func_L11_00441350 lives below, after the id-list macros it uses. */


/* arms the one-shot flag block when it is idle and the state agrees */
typedef struct { u8 pad[0x284]; s32 field284; s32 field288; } JobaFlagBlockView;

extern JobaFlagBlockView D_L11_001BA780;

void func_L11_004417A8(u8 *object, s32 value) {
    u8 *state = *(u8 **)(object + 0x68);
    if (D_L11_001BA780.field284 == *(s32 *)(state + 0x184)) {
        D_L11_001BA780.field284 = 0;
    }
    if (value != 0 && D_L11_001BA780.field284 == 0) {
        D_L11_001BA780.field284 = value;
        D_L11_001BA780.field288 = 0;
    }
    *(s32 *)(state + 0x184) = value;
}

/* returns the 128-byte entry selected by the state index, at its 0x30-byte payload */
extern u8 *D_L11_001B368C __attribute__((sda));

u8 *func_L11_004417E8(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    return D_L11_001B368C + (*(s32 *)(state + 0x168) << 7) + 0x30;
}

/* returns zero for a missing state polygon index or dispatches its point query to the integrated crossing-parity helper */
s32 func_L11_00441808(u8 *object, f32 *point) {
    u8 *state = *(u8 **)(object + 0x68);
    s32 index = *(s32 *)(state + 0x164);
    JobaPolygonHeaderView *header;
    s32 result;
    if (index == -1) {
        result = 0;
    } else {
        header = D_L11_001FF580[index];
        result = func_002A8AF0(point, (f32 *)(header + 1), header->field00);
    }
    return result;
}

/* Returns the state's 0xC0 word. */
s32 func_L11_00441858(u8 *obj) {
    return *(s32 *)(*(u8 **)(obj + 0x68) + 0xC0);
}

/* consumes one positive signed state counter selected by a measured class identifier and reports success */
s32 func_L11_00441868(u8 *object, s32 class_id) {
    JobaClassCounterView *state = *(JobaClassCounterView **)(object + 0x68);
    switch (class_id) {
        case 0xd98:
            if (state->fielde0 > 0) { state->fielde0--; return 1; }
            break;
        case 0xdcf:
            if (state->fielde4 > 0) { state->fielde4--; return 1; }
            break;
        case 0xdf4:
            if (state->fielde8 > 0) { state->fielde8--; return 1; }
            break;
        case 0xdf7:
            if (state->fieldec > 0) { state->fieldec--; return 1; }
            break;
        case 0xdf9:
            if (state->fieldf0 > 0) { state->fieldf0--; return 1; }
            break;
        case 0xd37:
            if (state->fieldf4 > 0) { state->fieldf4--; return 1; }
            break;
    }
    return 0;
}

/* increments one signed state counter selected by a measured class identifier */
/* Increments the state counter selected by the measured class identifier. */
void func_L11_00441978(u8 *object, s32 class_id) {
    JobaClassCounterView *state = *(JobaClassCounterView **)(object + 0x68);
    switch (class_id) {
        case 0xd98: state->fielde0++; break;
        case 0xdcf: state->fielde4++; break;
        case 0xdf4: state->fielde8++; break;
        case 0xdf7: state->fieldec++; break;
        case 0xdf9: state->fieldf0++; break;
        case 0xd37: state->fieldf4++; break;
    }
}

/* Each group word of the object's state names an id list in D_L11_001FC420: halfwords whose low
   15 bits index the 256-byte records of D_L11_001B359C, the last one with its sign bit set. A
   walk stops when the group word (re-read after every callback) is 0xFF or above the limit
   kept at D_L11_001B35B8. */
extern s32 D_L11_001B35B8[] __attribute__((sda));

#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = (u16 *)D_L11_001FC420[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L11_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L11_001FC420[GROUP(off)]); \
         p++)

extern s16 func_L02_004024A0(u8 *);
extern void func_L02_004024B0(u8 *);
extern void func_L02_004024C0(u8 *);

/* Counts the entities of the object's group (state word 0xC8) for which func_L02_004024A0
   holds, then sets (func_L02_004024B0) or clears (func_L02_004024C0) entities until the count
   equals the second argument. */
void func_L11_00441A58(u8 *object, s32 count) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *p;
    u8 *e;
    s32 n = 0;

    FOR_EACH_ID(p, 0xC8) {
        e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (func_L02_004024A0(e))
            n++;
    }
    if (n < count) {
        FOR_EACH_ID(p, 0xC8) {
            e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (!func_L02_004024A0(e)) {
                func_L02_004024B0(e);
                n++;
                if (n >= count)
                    break;
            }
        }
    } else if (n > count) {
        FOR_EACH_ID(p, 0xC8) {
            e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (func_L02_004024A0(e)) {
                func_L02_004024C0(e);
                n--;
                if (n <= count)
                    break;
            }
        }
    }
}

extern s32 func_L02_003D7300(u8 *);
extern void func_L02_003D7310(u8 *);
extern void func_L02_003D7320(u8 *);

/* Counts the entities of the object's group (state word 0xCC) for which func_L02_003D7300
   holds, then sets (func_L02_003D7310) or clears (func_L02_003D7320) entities until the count
   equals the second argument. */
void func_L11_00441D08(u8 *object, s32 count) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *p;
    u8 *e;
    s32 n = 0;

    FOR_EACH_ID(p, 0xCC) {
        e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (func_L02_003D7300(e))
            n++;
    }
    if (n < count) {
        FOR_EACH_ID(p, 0xCC) {
            e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (!func_L02_003D7300(e)) {
                func_L02_003D7310(e);
                n++;
                if (n >= count)
                    break;
            }
        }
    } else if (n > count) {
        FOR_EACH_ID(p, 0xCC) {
            e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (func_L02_003D7300(e)) {
                func_L02_003D7320(e);
                n--;
                if (n <= count)
                    break;
            }
        }
    }
}

extern float func_L02_002F21C0(void *, void *);
extern char D_00189EA0[];

/* Over the entities of the object's group (state word 0xC0): first resets the "armed" halfword
   (1 -> 0) of the state of every entity of the four measured classes and reports its class to
   func_L11_00441978. Then, twice: picks the entity of those classes (state byte not 0xFE or 0xFD
   and at least 4, halfword not 1) that func_L02_002F21C0 puts nearest to D_00189EA0, and arms
   its halfword when func_L11_00441868 consumes the class's counter. */
void func_L11_00441350(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *p;
    u8 *e;
    u8 *best;
    f32 best_d;
    f32 d;
    s32 i;
    s32 v;

    FOR_EACH_ID(p, 0xC0) {
        e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        switch (*(s16 *)(e + 0xAA)) {
        case 0xD98:
            if (*(s16 *)(*(u8 **)(e + 0x68) + 0x366) == 1) {
                *(s16 *)(*(u8 **)(e + 0x68) + 0x366) = 0;
                func_L11_00441978(object, *(s16 *)(e + 0xAA));
            }
            break;
        case 0xDCF:
            if (*(s16 *)(*(u8 **)(e + 0x68) + 0x4CA) == 1) {
                *(s16 *)(*(u8 **)(e + 0x68) + 0x4CA) = 0;
                func_L11_00441978(object, *(s16 *)(e + 0xAA));
            }
            break;
        case 0xDF9:
            if (*(s16 *)(*(u8 **)(e + 0x68) + 0x256) == 1) {
                *(s16 *)(*(u8 **)(e + 0x68) + 0x256) = 0;
                func_L11_00441978(object, *(s16 *)(e + 0xAA));
            }
            break;
        case 0xD37:
            if (*(s16 *)(*(u8 **)(e + 0x68) + 0x282) == 1) {
                *(s16 *)(*(u8 **)(e + 0x68) + 0x282) = 0;
                func_L11_00441978(object, *(s16 *)(e + 0xAA));
            }
            break;
        }
    }

    for (i = 0; i < 2; i++) {
        best = 0;
        best_d = 10000.0f;
        FOR_EACH_ID(p, 0xC0) {
            e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            v = -1;
            switch (*(s16 *)(e + 0xAA)) {
            case 0xD98:
                v = *(s16 *)(*(u8 **)(e + 0x68) + 0x366);
                break;
            case 0xDCF:
                v = *(s16 *)(*(u8 **)(e + 0x68) + 0x4CA);
                break;
            case 0xDF9:
                v = *(s16 *)(*(u8 **)(e + 0x68) + 0x256);
                break;
            case 0xD37:
                v = *(s16 *)(*(u8 **)(e + 0x68) + 0x282);
                break;
            }
            /* Retail tests the entity again after the switch and reads its class a second time as
               an unsigned halfword: both are needed for the same words. */
            if (e == 0)
                continue;
            if (e[0x20] == 0xFE)
                continue;
            if (e[0x20] == 0xFD)
                continue;
            if ((s16)*(u16 *)(e + 0xAA) != 0xD98 && (s16)*(u16 *)(e + 0xAA) != 0xDCF &&
                (s16)*(u16 *)(e + 0xAA) != 0xDF9 && (s16)*(u16 *)(e + 0xAA) != 0xD37)
                continue;
            if (v == 1)
                continue;
            if (e[0x20] < 4)
                continue;
            if (best == 0) {
                best = e;
                best_d = func_L02_002F21C0(best + 0x10, D_00189EA0);
            } else {
                d = func_L02_002F21C0(e + 0x10, D_00189EA0);
                if (d < best_d) {
                    best = e;
                    best_d = d;
                }
            }
        }
        if (best != 0) {
            switch (*(s16 *)(best + 0xAA)) {
            case 0xD98:
                if (func_L11_00441868(object, 0xD98))
                    *(s16 *)(*(u8 **)(best + 0x68) + 0x366) = 1;
                break;
            case 0xDCF:
                if (func_L11_00441868(object, 0xDCF))
                    *(s16 *)(*(u8 **)(best + 0x68) + 0x4CA) = 1;
                break;
            case 0xDF9:
                if (func_L11_00441868(object, 0xDF9))
                    *(s16 *)(*(u8 **)(best + 0x68) + 0x256) = 1;
                break;
            case 0xD37:
                if (func_L11_00441868(object, 0xD37))
                    *(s16 *)(*(u8 **)(best + 0x68) + 0x282) = 1;
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/levels", func_L11_00441FB8);

extern s32 func_L11_00441FB8(u8 *, u8 *, s32);
extern void func_L02_003FC248(u8 *, s32, s32);
extern void func_L11_00449970(u8 *, s32, s32);
extern s32 func_L11_0043A800(u8 *);
extern void func_L01_003E9CF8(u8 *, s32, void (*)(u8 *));
extern void func_L00_002B30E8(void);
extern u8 D_00189E20[];

/* Hands every entity of the object's group (state word 0xC0) that the shared test func_L11_00441FB8
   accepts, and whose state byte is not 0xFE, 0xFD or below 3, to the handler of its class (the
   halfword at +0xAA); then runs the test once more on the entity D_00189E20 holds at +0x2290. */
void func_L11_00442170(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *p;
    u8 *e;
    u8 *player;

    FOR_EACH_ID(p, 0xC0) {
        e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 0xFE)
            continue;
        if (e[0x20] == 0xFD)
            continue;
        if (e[0x20] < 3)
            continue;
        if (func_L11_00441FB8(object, e, 0) == 0)
            continue;
        switch (*(s16 *)(e + 0xAA)) {
        case 0xD98:
            func_L11_00449970(e, 0, 0);
            break;
        case 0xDCF:
            func_L02_003FC248(e, 0, -1);
            func_L11_0044C4F0(e);
            break;
        case 0xDF4:
            func_L02_003FC248(e, 0, -1);
            func_L11_00452DF8(e);
            break;
        case 0xDF7:
            func_L02_003FC248(e, 0, -1);
            func_L11_00454DD8(e);
            break;
        case 0xDF9:
            func_L02_003FC248(e, 0, -1);
            func_L01_003E9CF8(e, 0, func_L11_00456540);
            break;
        case 0xD37:
            func_L02_003FC248(e, 0, -1);
            func_L11_00436A78(e);
            break;
        case 0xD4B:
            if (func_L11_0043A800(e))
                func_L11_0043AB28(e);
            break;
        }
    }
    player = D_00189E20;
    if (func_L11_00441FB8(object, *(u8 **)(player + 0x2290), 1))
        func_L00_002B30E8();
}

INCLUDE_ASM("asm/levels", func_L11_004423F8);

INCLUDE_ASM("asm/levels", func_L11_004425C8);

/* func_L11_00442B60 is defined in its dedicated source unit. */

extern void func_L02_003A6F78(u8 *);

/* Runs func_L02_003A6F78 on every entity of the object's two groups (state words 0x178 and
   0x174); an empty group, or a group word of 0xFF, ends the function. */
void func_L11_00442C80(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *p;
    u16 *q;
    u8 *e;

    if (GROUP(0x178) == 0xFF)
        return;
    q = (u16 *)D_L11_001FC420[GROUP(0x178)];
    if (q == 0)
        return;
    for (p = q; (GROUP(0x178) & 0xFF) != 0xFF && GROUP(0x178) <= D_L11_001B35B8[0] && p != 0 &&
                ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L11_001FC420[GROUP(0x178)]);
         p++) {
        e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        func_L02_003A6F78(e);
    }
    if (GROUP(0x174) == 0xFF)
        return;
    q = (u16 *)D_L11_001FC420[GROUP(0x174)];
    if (q == 0)
        return;
    for (p = q; (GROUP(0x174) & 0xFF) != 0xFF && GROUP(0x174) <= D_L11_001B35B8[0] && p != 0 &&
                ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L11_001FC420[GROUP(0x174)]);
         p++) {
        e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        func_L02_003A6F78(e);
    }
}

/* func_L11_00442E38 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* func_L11_00443380 and func_L11_004433D8 live in the sibling small-data unit
   (L11_0043E1A0-g8.c): they reach the level's globals through $gp. */

INCLUDE_ASM("asm/levels", func_L11_00443498);

INCLUDE_ASM("asm/levels", func_L11_00443940);

/* maps the class index to its measured identifier */
extern u32 D_L11_002BB0E0[];

/* The level's own jump table: the address of each case body. */
extern void *jtbl_002BB0E0[13];

s32 func_L11_00443CE0(s32 a) {
    static void * volatile tab[] = {
        &&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7,
        &&c8, &&c9, &&c10, &&c11, &&c12
    };

    if ((u32)a >= 13) {
        goto def;
    }
    goto *jtbl_002BB0E0[a];
c0:
    return 0x2F66;
c1:
    return 0x2F67;
c2:
    return 0x2F68;
c3:
    return 0x2F69;
c4:
    return 0x2F6A;
c5:
    return 0x2F6B;
c6:
    return 0x2F6C;
c7:
    return 0x2F6D;
c8:
    return 0x2F70;
c9:
    return 0x2F71;
c10:
    return 0x3243;
c11:
    return 0x3244;
c12:
    return 0x3245;
def:
    return 0x2F66;
}

INCLUDE_ASM("asm/levels", func_L11_00443D78);

INCLUDE_ASM("asm/levels", func_L11_00444400);

INCLUDE_ASM("asm/levels", func_L11_004456A0);

/* func_L11_00445990 is defined in L11_00445990-g8.c ($gp accesses). */

/* func_L11_00445B30 is defined in L11_00445B30-g-g8.c. */

/* Claims the shared call slot for the state entry the identifier names. */
typedef struct {
    u8 pad0[0x24];
    s32 field24;
    s32 field28;
    u8 pad2[0x3C];
    s32 field68;
} JobaCallSlotView;

extern u8 D_001A63A8[];

/* Claims the shared call slot for the state entry the caller's class identifier
   selects, unless the slot is already busy or waiting. */

s32 func_L11_00445D28(u8 *obj, s32 idx) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 v;

    if ((u32)idx >= 0x27) {
        return 0;
    }
    if (idx < 0x14) {
        s32 *p = (s32 *)((u8 *)state + idx * 4);
        v = p[0x84];
    } else {
        s32 *p = (s32 *)((u8 *)state + (idx - 0x14) * 4);
        v = p[0x98];
    }
    {
        JobaCallSlotView *slot = (JobaCallSlotView *)D_001A63A8;

        if (slot->field68 != 0) {
            goto fail;
        }
        if (slot->field24 != -1) {
            goto fail;
        }
        slot->field24 = (v & 0x3FFF) + 0x7D0;
        slot->field28 = 0;
        {
            s16 *p = (s16 *)((u8 *)state + idx * 2 + 0x2A0);
            *p = 1;
        }
    }
    return 1;
fail:
    return 0;
}
/* func_L11_00445DF8 is defined in L11_00445DF8-g8.c ($gp accesses). */

INCLUDE_ASM("asm/levels", func_L11_00446020);

/* hands the state's 0x1C4 field to the shared helper, after the caller's argument */
extern int func_L00_003206B8(void *, int);

int func_L11_004461C0(u8 *object, u8 *arg) {
    u8 *state = *(u8 **)(object + 0x68);
    return func_L00_003206B8(arg, *(int *)(state + 0x1C4));
}

INCLUDE_ASM("asm/levels", func_L11_004461E8);
