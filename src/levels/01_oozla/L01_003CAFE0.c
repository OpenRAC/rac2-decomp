#include "include_asm.h"
#include "common.h"


/* Quadword copies and clears, the spelling that reaches lq/sq. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282948(void *a0);

extern void func_00282978(void *a0);

extern void func_0029F338(void *a0);

extern u32 D_L01_001BF918[];

extern u32 g_pHeroMoby[];

extern s32 func_3120A8(void *a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5,
                      u32 a6, f32 f12, f32 f13);

extern s32 func_355780(u32 a0, u32 a1, void *a2);

extern void func_002A7750(void *a0, s32 a1, s32 a2);
extern u8 *D_L01_001B255C_sda[] __attribute__((sda));
extern u8 *D_L01_001FE180[];

extern u8 *D_L01_001B255C __attribute__((sda));

extern u32 D_L01_001FFE80[];

/* func_L01_003CEDA0: scalar `sda` declarations under -G0 give retail's absolute accesses and
   its $gp loads in delay slots. */
extern u8 D_001A7B1C __attribute__((sda));
extern u8 D_0018C958[];
extern u8 D_L01_001BF6C0[];
extern u8 *D_L01_001B264C __attribute__((sda));
extern int D_L01_001A8F40 __attribute__((sda));
extern int D_L01_001A900C __attribute__((sda));
extern float D_L01_001B1FA0 __attribute__((sda));
extern u32 D_001A7390 __attribute__((sda));
extern float func_00283B98(float, float);
extern int func_002ACBC8(void *, int);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern void func_L01_003CEB00(void *);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_00288308(int);
extern void func_002AD860(int);
extern void func_002B0A18(int, int);
extern void func_0029B3E0(int, int);
extern void func_L00_00429020(int);
extern void func_00288E18(int, int);

/* func_L01_003CAFE0 is in L01_003CAFE0-ctx-g16.c. */


/* func_L01_003CB668 is in L01_003CB668-g16.c. */

/* func_L01_003CBCD8 is in L01_003CBCD8-qcopy.c. */

/* Frees the object at 0xD8 of the object at 0x68 and clears its 0xDC flag. */
void func_L01_003CBFA8(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (a0[0x21] != 0xFF && *(u8 *)(p + 0xDC) != 0)
        func_00282948(*(void **)(p + 0xD8));
    *(u8 *)(p + 0xDC) = 0;
}

/* func_L01_003CBFF0 is defined in a sibling -g8.c unit. */

/* Releases the sub-objects at 0xC0, 0xBC, 0xC4 and 0x26, first bumping the counter at 0x96. */
void func_L01_003CC210(u8 *a0)
{
    u8 *p = a0;
    u8 *q = *(u8 **)(p + 0x68);

    if (*(s32 *)(q + 0x74) == 0)
        func_00282948(q + 0xC0);
    if (*(u16 *)(p + 0x96) < 0xFFFE)
        *(u16 *)(p + 0x96) = *(u16 *)(p + 0x96) + 1;
    func_00282948(q + 0xBC);
    func_00282948(q + 0xC4);
    func_00282978(q + 0x26);
}

/* func_L01_003CC280 is defined in L01_003CC280-g8.c. */

/* Registers the object with the 0x04000009 descriptor and arms its 0x00 flag once. */
void func_L01_003CC898(u8 *a0, u32 a1, u32 a2, u8 a3, u8 *a4)
{
    u8 *s0 = a0;
    u8 *s1 = a4;

    if (func_3120A8(s0, a1, a2, 0x04000009, 0, 1, 1, (f32)a3, 1.0f) == 0)
        return;
    if (D_L01_001BF918[0] != g_pHeroMoby[0])
        return;
    if (*s1 == 0)
        return;
    func_355780(3, 0, s0);
    *s1 = 1;
}


extern void func_L01_00323310(s32 a0, s32 a1);
extern void func_002A7470(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_L01_00337A60(void *a0, void *a1, void *a2, s32 a3);

/* While the owner's kind (+0x95) is 6, serves the two entities whose ids lie at +0xA0 and +0xA4. */
s32 func_L01_003CDB40(u8 *a0)
{
    u8 *s0;
    u8 *s1;
    u8 *s2;
    s32 *ids;
    s32 i;
    u8 *tbl;
    s32 v;

    s0 = *(u8 **)(a0 + 0x68);
    if (a0[0x95] == 6)
        return 0;
    ids = (s32 *)(s0 + 0xA0);
    for (i = 0; i < 2; i++) {
        if (ids[i] == -1)
            continue;
        s1 = D_L01_001B255C_sda[0] + (ids[i] << 8);
        s2 = *(u8 **)(s1 + 0x68);
        if (a0[0x95] == 4 && *(s32 *)(s2 + 0x74) == 1)
            func_L01_00323310(*(s32 *)(s0 + 0xD0), *(s32 *)(s0 + 0xD8));
        if (s1[0x95] == 8)
            continue;
        v = *(s32 *)(s2 + 0xC0);
        if (v < *(s32 *)(s0 + 0xBC))
            v = *(s32 *)(s0 + 0xBC);
        *(s32 *)(s0 + 0xBC) = v;
        *(s32 *)(s2 + 0xC0) = v;
        if (*(f32 *)(s0 + 0x20) <= 0.0f) {
            if (a0[0x43] != 5)
                func_002A7470(a0, 5, 0, 10);
            *(f32 *)(s0 + 0x20) = 0.0f;
            *(f32 *)(s2 + 0x20) = 0.0f;
            if (s1[0x43] != 4 && s1[0x42] != 4)
                func_002A7470(s1, 4, 0, 10);
            s1[0x95] = 8;
            func_002A7750(a0, 0, 6);
        }
        qcopy(s0 + 0x80, s2 + 0x60);
        tbl = D_L01_001FE180[*(s32 *)(s0 + 0xA8)];
        func_L01_00337A60(s0 + 0x70, s2 + 0x60, tbl + 0x10, *(s32 *)tbl);
    }
    return *(s32 *)(s0 + 0xBC);
}

/* Sends the timer string and steps the 0x2E/0x28/0x2A state fields of the owner. */
extern s32 func_00283CF0(f32 a0);
extern void func_L01_003377C8(void *a0);
extern void func_002A7398(void *a0, s32 a1, s32 a2);

/* Seeds the state block (random timers, the saved position, its mode bytes), lets the table
   entry it names inherit the object's float at +0x18, then starts either the flagged (0xAC)
   or the plain animation. */
void func_L01_003CDD00(u8 *a0)
{
    u8 *s0 = *(u8 **)(a0 + 0x68);

    *(u8 *)(s0 + 0x48) = func_00283CF0(30.0f);
    *(u8 *)(s0 + 0x4A) = func_00283CF0(24.0f);
    *(f32 *)(a0 + 0x2C) = *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24);
    qcopy(s0 + 0x60, a0 + 0x10);
    *(u8 *)(s0 + 0x28) = 3;
    *(u8 *)(s0 + 0x2E) = 3;
    *(f32 *)(s0 + 0x30) = 3.0f;
    *(u32 *)(s0 + 0xB4) = 0;
    *(s32 *)(s0 + 0xC0) = -1;
    *(u8 *)(s0 + 0x2A) = 8;
    if (*(s32 *)(s0 + 0xCC) != -1) {
        u8 *e = (u8 *)((*(s32 *)(s0 + 0xCC) << 8) + (s32)D_L01_001B255C_sda[0]);

        if (*(u8 *)(e + 0x20) != 0xFE) {
            if (*(u8 *)(e + 0x20) != 0xFD)
                *(f32 *)(e + 0x18) = *(f32 *)(a0 + 0x18);
        }
    }
    if (*(s32 *)(s0 + 0xA8) != -1)
        func_L01_003377C8(D_L01_001FE180[*(s32 *)(s0 + 0xA8)]);
    if (*(u32 *)(s0 + 0xAC) != 0) {
        *(u16 *)(a0 + 0x34) &= 0xEFFF;
        func_002A7398(a0, 0, 0);
        *(u32 *)(a0 + 0x48) = 0;
        func_002A7750(a0, 0, 4);
        return;
    }
    *(u16 *)(a0 + 0x34) |= 0x1000;
    func_002A7398(a0, 1, 0);
    func_002A7750(a0, 0, 1);
}

/* Releases the three sub-objects at 0xBC, 0xB4 and 0x26, first bumping the counter at 0x96. */
void func_L01_003CDE58(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (*(u16 *)(a0 + 0x96) < 0xFFFE)
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
    func_00282948(p + 0xBC);
    func_00282948(p + 0xB4);
    func_00282978(p + 0x26);
}

/* The group count and the entity base, read as bare symbols (`sda` arrays of unknown size: the
   assembler makes the loads $gp ones in a branch delay slot); the base takes a second name
   because D_L01_001B255C is declared above with its pointer type. */
extern s32 D_L01_001B2578[] __attribute__((sda));
extern u16 *D_L01_001FB020[];
extern u8 D_00189EA0[];

extern void *func_002A9640(void *, s32, s32);
extern f32 func_002A96A0(void *, void *);
extern u8 *func_002AB1F0(u8 *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern f32 func_00283CE0(s32);
extern void func_L01_002F14E8(s32, s32, f32);

/* While the owner's kind (+0x95) is 5 or 6 and its timer (+0x20) is positive, finds the entity
   func_002A9640 names (only when the state's halfword at +0x26 is below 1) and its distance
   f20 from func_002A96A0; when that is positive, walks the id list of the owner's group and
   sets the effect record each entity hands out (func_002AB1F0: class-dependent 60 or 0 at +6,
   the distance taken off its float at +0), otherwise takes the distance off the timer. Then
   it runs the timer out (releasing the entity at +0xCC and switching to state 5), or, below it,
   enters state 4 for a distance of 1.0 or more and scales the vector at +0x90. At the end the
   shared update runs and the timer ratio is handed to func_L01_002F14E8. The function keeps
   the second `p != 0` guard of the walk; func_L01_003CDB40 returns a word, and the retail
   copy of the 0.2 limit holds one ulp more than 0.2f. */
void func_L01_003CDEA8(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    u8 *ent;
    u8 *s0;
    u8 *e;
    u8 *r;
    u16 *p;
    f32 f20;
    f32 w;
    s32 s4;
    u16 cls;

    if (a0[0x95] >= 5 && a0[0x95] <= 6 && 0.0f < *(f32 *)(state + 0x20)) {
        ent = func_002A9640(a0, 0x10000, 0);
        s0 = ent;
        if (*(short *)(state + 0x26) >= 1)
            s0 = 0;
        f20 = func_002A96A0(a0, s0);
        if (s0 != 0 && 0.0f < f20) {
            if (a0[0x21] != 0xFF && *(s32 *)(state + 0xA0) != -1) {
                cls = *(u16 *)(*(u8 **)(s0 + 0x20) + 0xAA);
                s4 = (cls == 0xCE4 || cls == 0xCE5) ? 60 : 0;
                for (p = D_L01_001FB020[a0[0x21]];
                     a0[0x21] != 0xFF && a0[0x21] <= D_L01_001B2578[0] && p != 0 &&
                     ((p != 0 && (short)p[-1] >= 0) || p == D_L01_001FB020[a0[0x21]]);
                     p++) {
                    e = D_L01_001B255C_sda[0] + ((*p & 0x7FFF) << 8);
                    if (e == 0)
                        break;
                    r = func_002AB1F0(e);
                    if (r != 0) {
                        *(u16 *)(r + 6) = s4;
                        *(f32 *)r = *(f32 *)r - f20;
                        r[0x17] = state[0x37];
                        *(s32 *)(r + 0x18) = *(s32 *)(state + 0x38);
                        *(u16 *)(r + 0x1C) = *(u16 *)(state + 0x3C);
                    }
                    e[0xA8] = 0xFF;
                }
            } else {
                *(f32 *)(state + 0x20) = *(f32 *)(state + 0x20) - f20;
            }
        }
        a0[0xA8] = 0xFF;
        if (*(f32 *)(state + 0x20) < 0.0f) {
            if (*(s32 *)(state + 0xCC) != -1)
                func_0029F338(D_L01_001B255C_sda[0] + (*(s32 *)(state + 0xCC) << 8));
            *(s32 *)(state + 0xCC) = -1;
            if (a0[0x43] != 5)
                func_002A7470(a0, 5, 0, 10);
            *(f32 *)(state + 0x20) = 0.0f;
            func_002A7750(a0, 0, 6);
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) & 0xEFFF;
        } else {
            if (1.0f <= f20) {
                *(s32 *)(state + 0xBC) = 0xF0;
                if (a0[0x43] != 4)
                    func_002A7470(a0, 4, 0, 3);
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) & 0xEFFF;
                func_002A7750(a0, 0, 6);
            }
            if (0.1f < f20) {
                func_00282CF0(state + 0x90, a0 + 0x10, D_00189EA0);
                w = (f20 + f20 + 3.0f) * 0.016666668f;
                if (0.20000002f < w)
                    w = 0.20000002f;
                func_00282F20(state + 0x90, state + 0x90, w);
                *(s32 *)(state + 0x98) = 0;
            }
        }
    } else {
        a0[0xA8] = 0xFF;
    }
    func_L01_003CDB40(a0);
    if (a0[0x95] >= 5 && a0[0x95] <= 6)
        func_L01_002F14E8(1, 0, *(f32 *)(state + 0x20) / func_00283CE0(*(short *)(state + 0x24)));
}


/* func_L01_003CE868 is defined in L01_003CE868-g8.c. */

/* Three states on the byte at +0x20: 0 raises the moby by 0.75 and sets its scale to 1.5 times
   the class value (or frees it while D_001A7B1C is set); 1 turns it (+0xF8) and, once the point
   D_00189EA0 lies in the cuboid its vars name at +4, queues movie 0x26 (QueueMovie) and enters
   state 2; 2 bumps the counter at +0x96, waits for func_002F5D10, then runs the level calls for
   the entry its vars name at +8, flags the object named at +0xC once, steps the subtitle history
   timer of entry 16 (TryQueueSubtitleSelection 0x9B9 after 180 frames) and frees the moby.
   The timer's three loads keep their retail order only when the frame counter is read last. */
void func_L01_003CEDA0(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68), *q;
    int mode;

    switch (a0[0x20]) {
    case 0:
        if (D_001A7B1C) {
            func_0029F338(a0);
            break;
        }
        *(float *)(a0 + 0x18) += 0.75f;
        *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * 1.5f;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        *(float *)(a0 + 0xF8) = func_00283B98(*(float *)(a0 + 0xF8), 0.078539826f);
        if (func_002ACBC8(D_00189EA0, *(int *)(p + 4))) {
            p = D_L01_001BF6C0;
            if (func_00288AA0(p, 0x26)) {
                func_00288BE8(p);
                func_002A7750(a0, 2, -1);
            }
        }
        if (a0[0x31])
            func_L01_003CEB00(a0);
        break;
    case 2:
        mode = D_L01_001A8F40;
        (*(u16 *)(a0 + 0x96))++;
        if (mode == 2) {
            a0[0x31] = 0;
            *(u16 *)(a0 + 0x34) |= 1;
        }
        if (func_002F5D10())
            break;
        q = D_L01_001B264C + (*(int *)(p + 8) << 7);
        D_L01_001A900C = 0;
        D_L01_001B1FA0 = 0;
        func_L00_002B9D60(q + 0x30, q + 0x70, 0x6F, 1);
        func_00288308(0x24);
        func_002AD860(0x24);
        func_002B0A18(0x1225, -1);
        func_0029B3E0(0, -1);
        if (*(int *)(p + 12) != -1) {
            p = *(u8 **)(D_L01_001B255C + (*(int *)(p + 12) << 8) + 0x68);
            if (!*(int *)(p + 0x3C)) {
                func_L00_00429020(*(int *)(p + 0x38));
                *(int *)(p + 0x3C) = 1;
            }
            p = D_0018C958;
            if (!*(u16 *)(p + 0xC0)) {
                u16 elapsed = *(u16 *)(p + 0xC2);
                u32 start = *(u32 *)(p + 0xC4);
                u32 now = D_001A7390;

                if (start + elapsed >= now - 2) {
                    *(u16 *)(p + 0xC2) = ++elapsed;
                    if (elapsed >= 180) {
                        func_00288E18(0x9B9, 0x10);
                        *(u16 *)(p + 0xC2) = 0;
                    }
                } else {
                    if (start < now)
                        *(u32 *)(p + 0xC4) = now;
                    *(u16 *)(p + 0xC2) = 0;
                }
            }
        }
        func_0029F338(a0);
        break;
    }
}

/* func_L01_003D1A48 lives in L01_003D1A48-g8.c. */

/* func_L01_003D1F40 is defined in L01_003D1F40-g8.c. */

/* func_L01_003D25B8 is defined in a sibling -g8.c unit. */

/* func_L01_003D26C0 is in L01_003D26C0-g8.c. */

/* func_L01_003D2890 is in L01_003CAFE0-launch.c. */

/* func_L01_003D2E50 is in L01_003D2E50.c. */

/* func_L01_003D68C0 is defined in a sibling -g8.c unit. */

/* func_L01_003D8358 lives in L01_003D8358-g8.c. */

/* func_L01_003D8830 is in L01_003CAFE0-burst.c. */

/* func_L01_003D8AD0 is defined in a sibling -g8.c unit. */

/* func_L01_003D8C00 is defined in L01_003D8C00-qcopy-barrier.c. */

/* func_L01_003D8E80 is defined in L01_003CAFE0-g8.c. */


/* func_L01_003D98E0 is defined in L01_003D98E0-g8.c. */

/* func_L01_003DA300 is in L01_003DA300-g8.c. */

/* func_L01_003DA3F0 is defined in L01_003DA3F0-g8.c. */
