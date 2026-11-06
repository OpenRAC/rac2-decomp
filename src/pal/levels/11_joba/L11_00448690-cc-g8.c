/* func_PAL_L11_00448690, the PAL copy of func_L11_00442E38: the same C. */

typedef int s32;

typedef unsigned int u32;

typedef unsigned char u8;

typedef unsigned short u16;

typedef short s16;

typedef float f32;

/* Small-data controls: the four measured globals the level's script hooks share. */
extern u8 *D_L11_001B359C[3] __attribute__((sda));

extern u8 *D_L11_001FC420[];

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
/* The group count and the entity table's base, as the walks below reach them: the count through
   $gp, the base as a bare symbol (a three-word `sda` array keeps the `lui`/`lw` pair). */
#define GROUP(off) (*(s32 *)(state + (off)))

/* Claims the slot at the state's count (+0x18C) in its 0x120 table: an empty slot is taken as it
   is, a filled one only when func_L02_003D77B8 refuses its entity and the count is still below
   the class record's limit (byte 0x16), which then advances. The slot gets the first entity of the
   group's id list (state word 0xC4) that func_L11_00442B60 and func_L02_003D77B8 both accept;
   when the slot is still empty after that walk, the first entity that func_L02_003D77B8 accepts
   and that lies more than 30.0 from D_00189EA0 takes it. The table address is formed at each use
   (retail does), which lets GCSE hoist it ahead of the first walk. */
/* The four angle and length constants the script reads through $gp. */
/* arms the script bridge over the measured buffers and starts it on the shared slot */
/* Turns the script's angle around the actor and hands the result to the level's
   helpers when the angle is small enough. */
/* Turns the script's angle around the actor, hands the result to the level's helpers
   and counts the class the script's identifier names. */
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
    { u16 *q = (u16 *)D_L11_001FC420[GROUP(off)]; \
    if (q == 0) \
        return; \
    for (p = q; (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L11_001B35B8_1[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L11_001FC420[GROUP(off)]); \
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
                e = D_L11_001B359C[0] + ((*p & 0x7FFF) << 8); \
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
                    FOR_EACH_ID(p, 0x17C) { \
                        e = D_L11_001B359C[0] + ((*p & 0x7FFF) << 8); \
                        if (e == 0) \
                            break; \
                        if (n <= 0) \
                            break; \
                        if (func_L02_00416800(e) != 0 && func_002A77E0(6) == 0) { \
                            n--; \
                            func_L02_00416720(e, buf[n], D_L11_001B1614 * 0.020000001f, \
                                              D_L11_001B1618 * 0.0003490659f); \
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
void func_PAL_L11_00448690(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    JobaClassTableView *entry =
        ((JobaClassTableView **)&D_L11_001B14F8)[*(s16 *)(state + 0x1F0)];
    u8 *rec = (u8 *)&entry->records[*(s16 *)(state + 0x1F2)];
    u8 *buf[16];
    u16 *p;
    u8 *e;

    HALF(0x10, 0x178)
    HALF(0x12, 0x174)
}

/* The object state's guide vector (state +0x170), allocated while the mode byte is 8 or 9:
   it is set from one of five read-only small-data vectors chosen by the target's class. */
#define GUIDE (*(f32 **)(s + 0x170))
#define SET_GUIDE(x, y, z) (GUIDE[0] = (x), GUIDE[1] = (y), GUIDE[2] = (z))

#undef SET_GUIDE
#undef GUIDE
