/* func_PAL_L02_00401980, the PAL copy of func_L02_003FD228: the same C. */

/* Four bytes: cc1 then emits the address as a single `la`, which gas expands to an adjacent
   lui/addiu pair (an array of unknown size is split by cc1 itself). */
typedef struct {
    char pad0[0x80];
    char pos[8];
    float f88;
    char pad1[0x2236];
    unsigned char b22C2;
    char pad2[0x22D];
    unsigned char b24F0;
} L02_003F5710_Hero;

extern L02_003F5710_Hero D_00189E20;

/* Watches the hero block's height (+0x88) against 420.0 and the copy of it the actor kept at
   +0x98. Crossing it downwards clears the byte at +0x24F0 and the global flag; crossing it upwards
   sets both when the flag is clear and the hero is within 150.0 of D_L02_001B3210, and clears
   both when the flag is set and the hero is farther away. While the flag is set the hero's byte
   at +0x22C2 is raised, and the first time the actor's word at +0xDC is set and handed its two
   words at +0x1C and +0x20. The height is then kept at +0x98.

   The flag is a plain extern int: the assembler decides each access at its use, a gp-relative one
   inside a delay slot and the absolute lui/lw pair elsewhere, as retail has them. */
extern char *D_L02_001B1190[] __attribute__((sda));

/* Whether the pair of table entries the object names still agree with its own four words. */
/* func_L02_003FCBF0 is defined in L02_003FCBF0-g8.c. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef float f32;

extern char *D_L02_001B1190[2] __attribute__((sda));
extern unsigned char *D_L02_001B359C[3] __attribute__((sda));
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern u32 D_L02_001FC060[];
extern f32 D_L02_001B1258 __attribute__((sda));
extern f32 D_L02_001B125C __attribute__((sda));
extern s32 func_00312B58(char *);
extern s32 func_L02_00416800(char *);
extern s32 func_002A77E0(s32);
extern void func_L02_00416720(char *, char *, f32, f32);

#define GROUP(off) (*(s32 *)(state + (off)))
/* Leaves the function when the group is 0xFF or empty; the braces it opens close in END_IDS. */
#define FOR_EACH_ID(p, off) \
    if (GROUP(off) == 0xFF) \
        return; \
    { u16 *q = (u16 *)D_L02_001FC060[GROUP(off)]; \
    if (q == 0) \
        return; \
    for (p = q; (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L02_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[GROUP(off)]); \
         p++)
#define END_IDS }
/* One half: collect the entities of group OFF for which func_00312B58 holds (counting the
   others in m), then, up to 1000 passes over group 0xCC while m is below the record's limit,
   hand one collected entity at a time to func_L02_00416720 with an entity of 0xCC. */
#define HALF(limit, off) \
    { \
        s32 n, m, i, k; \
        if (*(s16 *)(rec + (limit)) != 0) { \
            m = 0; \
            n = 0; \
            for (k = 15; k >= 0; k--) \
                buf[k] = 0; \
            FOR_EACH_ID(p, off) { \
                e = (char *)D_L02_001B359C[0] + ((*p & 0x7FFF) << 8); \
                if (e == 0) \
                    break; \
                if (func_00312B58(e) == 0) { \
                    m++; \
                } else { \
                    buf[n] = e; \
                    n++; \
                } \
            } END_IDS \
            if (n != 0) { \
                for (i = 0; i < 1000 && m < *(s16 *)(rec + (limit)); i++) { \
                    FOR_EACH_ID(p, 0xCC) { \
                        e = (char *)D_L02_001B359C[0] + ((*p & 0x7FFF) << 8); \
                        if (e == 0) \
                            break; \
                        if (n <= 0) \
                            break; \
                        if (func_L02_00416800(e) != 0 && func_002A77E0(6) == 0) { \
                            n--; \
                            func_L02_00416720(e, buf[n], D_L02_001B1258 * 0.020000001f, \
                                              D_L02_001B125C * 0.0003490659f); \
                            m++; \
                            break; \
                        } \
                    } END_IDS \
                } \
            } \
        } \
    }

void func_PAL_L02_00401980(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    char *rec = *(char **)(D_L02_001B1190[*(s16 *)(state + 0x120)] + 4)
                + *(s16 *)(state + 0x122) * 0x14;
    char *buf[16];
    u16 *p;
    char *e;

    HALF(0xC, 0xC8)
    HALF(0xE, 0xC4)
}

/* Fills the slot of the list at +0xA8 that the counter at +0xD8 names. It goes on when that slot is
   empty, or when func_L02_003D77B8 returns 0 for the entity in it and the counter is below the
   table record's limit (byte +0x12 less one: the counter is then stepped). The entity group the
   object names (+0x44) is walked: the first entity for which func_L02_003FD000 and
   func_L02_003D77B8 both return non-zero goes into the slot; if the slot is still empty, the
   first one with func_L02_003D77B8 non-zero that is more than 30.0 away from D_00189EA0. */
extern unsigned char D_001395B8[0x100];

/* D_001A7A0C, written as the second word of an 8-byte object: cc1 then counts the store as two
   instructions and keeps it out of func_L02_003FCDF8's delay slot, and the assembler gives the
   absolute `lui $at ; sw`. */
extern int func_L02_003F9B70(int);

extern int func_L02_00400650(char *, int);

/* With a1 == 0 and no count yet for func_L02_003F9B70(0), plays the hero's scene 7 with its
   word at +0x22C8 kept; otherwise picks the scene from a1 (6, 0xB or a random one), adds the
   two scores and starts func_L00_0030C7F8(0x168). Then counts the entry. The unit is built with
   -frac2-gcse-unsplit-edges and -frac2-keep-block-order (config/cflags.txt): the high half of
   D_001395B8 is computed in the entry block, and the switch keeps its `b default` with the
   default body last, as in retail. `+= 1` keeps the counter's address out of the call. */
/* Two passes, over the two 16-byte vectors at D_L02_001B1730 in turn.  Each combines the vector
   with the object's vectors at +0xC0 and +0x10 (func_00283098, func_00282CC0) into v0, builds v1
   as a vector whose z is -func_002A7878(D_L02_001B1750, D_L02_001B1754) / 60, combines it with
   A1, and hands v0 and v1 twice to func_002BAE50 with colour words and a pick of func_002A7820:
   first with one of two sets chosen by bit 0 of D_L02_001B30C8, then with a third set. */
extern s32 func_L02_00400650(char *, s32);

/* Picks the message to ask for after the entity the object is attending to (state word 0xD0),
   for its kinds 0x9F8 and 0xA44: while D_0018C2EC is not positive, one of two at random (0x10 or
   0x11, 0x16 or 0x17), dropped when the state's flag for it is set; then 0x12 (0x18) when the
   entity's float at +0x20 is below its half-word at +0x24 scaled by D_L02_001B1534, unless the
   state's half-word at 0x1F4 (0x200) is set, and 0x13 (0x19) when that float is not above zero,
   unless the half-word at 0x1F6 (0x202) is set.  A positive pick is handed to func_L02_00400650. */
extern u8 D_001395B8[];
typedef struct {
    char pad0[4];
    u8 f4;
    char pad1[0xDB];
} L02_003FF9A0_Rec;

extern L02_003FF9A0_Rec D_L02_00264A70[];

extern s32 func_L02_003F9B70(s32);
/* Calls func_L00_002C42E0(0x6F, 1) unless D_0018C0B4 already is 0x6F.  When the input test
   func_L00_0032EF10(0x40, 0x3C, 0) holds, the object changes state to 7 and its selection (state
   half-word 0x118) moves to the next entry of the table at D_L02_001B1190 that is usable: the flag
   of D_001395B8 at the index func_L02_003F9B70 gives for the entry's word at +8 is set, entries from
   12 on also pass func_00288D58, and entries 7 and 8 need the byte at +4 of the record of
   D_L02_00264A70 that D_00139568[0x1E] (0x2A) names.  The pick is kept in the state and in
   D_001395B8[0x3C].  Otherwise, when func_L00_0032EF10(0x10, 0x3C, 0) holds, func_L02_003FCA80
   runs; if neither test holds the callback func_L02_003FF6E8 is registered for the object. */
/* Picks an idle message for the object. Nothing happens while the message system at D_001A63A8
   is busy (+0x68 set, +0x24 not -1) or while the countdown at +0xE4 of the state runs. A float
   (+0xE8, plus a2) and a count (+0xEC, plus a1) accumulate; when the float passes D_L02_001B1520
   or the count D_L02_001B1524, the messages 0x1D..0x22 not played yet (the half-words at
   +0x1D0 + id * 2; 0x1D only while +0xD0 is zero) become candidates and both restart. When
   func_00282948 reports the timer at +0x100 idle, both restart and the timer is set to 300. The
   messages 0x1A..0x1C join when a3 is above D_L02_001B1528, 0x23 when the hero block's int at
   +0x24CC is under D_001A7A00 * D_L02_001B152C and 0x24 when it is not positive. One candidate,
   picked at random, is started through func_L02_00400650 and the countdown is set to
   D_L02_001B1530 plus a random share of it.

   Each loop points lp at the list before it fills it. Set in two places, lp has no base the
   alias analysis knows (alias.c's record_set), so the stores of the second loop may reach the
   globals and the loads of D_001A7A00 and D_L02_001B152C stay below that loop, as in retail;
   with one lp, or with list[n++] in the loops, gcse's PRE hoists them above it. The thresholds
   are const (retail reads them ahead of the stores to the state); the hero block's address and
   the ids 0x23/0x24 each have a variable of their own, as retail rebuilds the address from its
   high half and loads each id next to its store. */
/* In state 8 the actor's 0xC0 object is created through func_L00_002D70A0(5) when missing,
   otherwise it gets one of three float triples: by the class (+0xAA, 0x9F8 or 0xA44) of the
   0xD0 object, or the default one when there is none. In any other state the object is
   released through func_L00_002D7140 and the slot cleared.
   Each branch writes its own triple; the y and z stores (re-reading 0xC0) come out as one tail
   through cross-jumping after reload, which is why z keeps its own register ($f2). The stores
   are struct fields so the sda loads are not ordered behind them. */
