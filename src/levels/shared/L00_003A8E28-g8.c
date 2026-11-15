#include "include_asm.h"
#include "common.h"

/* Small-data sibling of L00_003A8E28.c: the body below reaches the level's
   globals through $gp (the file gets -G8 by its name, see config/cflags.txt). */

extern char D_L00_0023BB78[];

extern unsigned char D_L00_001AF810 __attribute__((sda));

extern unsigned char D_L00_001AF811 __attribute__((sda));

extern void func_2EDE88();

typedef int TI128 __attribute__((mode(TI)));

extern float D_L00_001AF7A4 __attribute__((sda));

extern void matrix_mul_vec3(void *, void *, void *);

extern void FastVecAdd(void *, void *, void *);

/* Builds the local vector {scale, 0, 0, 1}, transforms its copy, then adds the object position. */
void moby_transform_offset_to_world(char *moby, char *out)
{
    float rotated[4];
    float offset[4];
    TI128 zero = 0;

    *(TI128 *)offset = zero;
    offset[0] = D_L00_001AF7A4;
    offset[3] = 1.0f;
    *(TI128 *)rotated = *(TI128 *)offset;
    matrix_mul_vec3(rotated, rotated, moby + 0xC0);
    FastVecAdd(out, rotated, moby + 0x10);
}

/* Resets the two slot cursors, then releases the 256-entry slot table. */
void trail_reset_slots(void)
{
    D_L00_001AF811 = 0;
    D_L00_001AF810 = 0;
    func_2EDE88(D_L00_0023BB78, 0x1C00);
}

typedef int Qword __attribute__((mode(TI)));

typedef struct {
    Qword pos;
    Qword a;
    Qword b;
    Qword c;
    Qword d;
    short flag;
    short count;
    float t;
    float u;
    float rate;
} TrailSlot;

typedef struct {
    char pad0[0x18];
    short index;
    short id;
} TrailSource;

typedef struct {
    char pad0[0x10];
    Qword pos;
    char pad20[0x48];
    TrailSource *source;
} TrailActor;

extern float D_L00_001AF760 __attribute__((sda));
extern float D_L00_001AF798 __attribute__((sda));
extern float D_L00_001AF774 __attribute__((sda));
extern char *level_get_slot_body(int, int);
extern int *level_get_slot_header(int, int);
extern int ref_L00_003A9000_00(void *);
extern void func_2EE3D0(void *, void *, float);
extern void func_2EE108(void *, void *, void *);

/* Moves one trail slot along with its owner and keeps its two spin timers wrapping. */
int trail_update_slot(TrailActor *self)
{
    TrailSource *source = self->source;
    char *base = level_get_slot_body(MOBY_CLASS_PULSE_RIFLE, source->id);
    char *data = base + *level_get_slot_header(MOBY_CLASS_PULSE_RIFLE, source->id);
    TrailSlot *slots = (TrailSlot *)data;
    Qword rot[1];

    if (slots[source->index].flag == 0)
        return 0;
    if (ref_L00_003A9000_00(&slots[source->index].count)) {
        slots[source->index].flag = 0;
        return 0;
    }
    qcopy_nc(&slots[source->index].b, &self->pos);
    slots[source->index].t += D_L00_001AF760;
    if (slots[source->index].t >= 4.0f)
        slots[source->index].t -= 4.0f;
    slots[source->index].u += D_L00_001AF798;
    if (slots[source->index].u >= 4.0f)
        slots[source->index].u -= 4.0f;
    func_2EE3D0(rot, source, D_L00_001AF774 * 0.016666668f);
    func_2EE108(&slots[source->index], &slots[source->index], rot);
    func_2EE108(&slots[source->index].a, &slots[source->index].a, rot);
    return 1;
}

extern short D_L00_001AF82C __attribute__((sda));
extern unsigned char D_L00_001AF830 __attribute__((sda));
extern int g_frame_l00_counter MACRO_ADDR;
/* One 28-byte entry of the slot table (layout as in L00_003B0CE8-g8.c): used holds the frame it was taken. */
typedef struct { unsigned char pad0[0xC]; int used; unsigned char pad10[4]; unsigned char id[8]; } SlotEntry1270;
/* The hero record: its position at 0x80, the pad buttons word at 0x1230 and the hero moby at 0x2290. */
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x11A0];
    int buttons;
    char pad1234[0x105C];
    char *moby;
} HeroL00;
extern HeroL00 g_hero_state;
extern int D_00138320 NOT_SDA;
extern float D_L00_001AF838[4];
extern float D_L00_001AF848[4];
extern void node_free_slot(int);
extern char *RecordHeroTrailNode(void *);
extern int func_001163B0(void);
extern int part_spawn_debris_two_mode(void *,int,int,int,int,int,void *,float,float);
extern void ref_L00_003B1270_0(int,int,int,void *,int);

/* Releases slot-table entries taken 480 or more frames ago, steps the moby's state 0, 1, 2, and in
   state 2 spawns a particle at the hero when the hero's button word has a bit of D_00138320 set
   (recording it in a new slot when func_L00_003B0DA0 gives one); then hands both slot cursors to
   ref_L00_003B1270_0. */
/* Per-frame update for the Fireboot Weapon moby: spawns trail particles at the hero while the button is held. */
void fireboot_weapon_update(char *moby)
{
    int stop = 0, result;
    short random;
    short random2;
    unsigned char slot;
    char *entry;

    while (!stop && D_L00_001AF811 != D_L00_001AF810) {
        if (g_frame_l00_counter - ((SlotEntry1270 *)D_L00_0023BB78)[D_L00_001AF811].used < 480)
            stop = 1;
        else
            node_free_slot(D_L00_001AF811);
    }
    switch ((unsigned char)moby[0x20]) {
    case 0:
        moby[0x20] = 1;
        break;
    case 1:
        moby[0x20] = 2;
        break;
    case 2:
        if (D_00138320 & g_hero_state.buttons) {
            entry = RecordHeroTrailNode(g_hero_state.position);
            if (entry) {
                slot = D_L00_001AF810 - 1;
                random = D_L00_001AF82C + (func_001163B0() & 7);
                result = part_spawn_debris_two_mode(g_hero_state.position, slot, 0, random, 1, (unsigned char)(D_L00_001AF830 + (func_001163B0() & 3)), moby, 1, 1);
                *(int *)(entry + 0x10) = result;
            } else {
                random2 = D_L00_001AF82C + (func_001163B0() & 7);
                part_spawn_debris_two_mode(g_hero_state.position, 0, 1, random2, 1, (unsigned char)(D_L00_001AF830 + (func_001163B0() & 3)), moby, 1, 1);
            }
        }
        break;
    }
    ref_L00_003B1270_0(0x41, 0x41, 0x80000000, D_L00_001AF838, D_L00_001AF810);
    ref_L00_003B1270_0(0x40, 0x40, 0x80F0F0F0, D_L00_001AF838, D_L00_001AF810);
    ref_L00_003B1270_0(0x41, 0x51, 0x80000000, D_L00_001AF848, D_L00_001AF811);
    ref_L00_003B1270_0(0x40, 0x50, 0x80F0F0F0, D_L00_001AF848, D_L00_001AF811);
}

/* Moby index list: entry 0 is the count, entries 1..count index the 256-byte moby array. */
extern short ref_L00_003ADEA0_0[];
/* Base of the moby array. */
extern char *ref_L00_003ADEA0_1 MACRO_ADDR;
/* Frame counter: an absolute macro load in ordinary flow, a $gp load in a delay slot. */
extern int ref_L00_003ADEA0_2 MACRO_ADDR;
/* Per-row links drawn by func_L00_003ADA30: up to eight mobys and a null terminator. */
extern char *ref_L00_003ADEA0_3[10][9];
typedef struct { char pad[0x18]; char *hit; int count; float point[4]; } CollisionADEA0;
extern CollisionADEA0 ref_L00_003ADEA0_4;
extern void math_trap_always(void);
extern float fast_vec_dist(void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void part_spawn_sparks_between_mobys(void *, void *);
extern void anim_start_blended(void *, int, int, int);
extern int PlayMobySound(int, int, void *);
extern void gfx_add_draw_callback_first(void *, void *);
extern void DrawMobyLinkQuads(char *);

/* Once per frame, links each listed active moby to every other active moby of class 0x81F within
   12 units and in line of sight (up to eight, in the moby's row of ref_L00_003ADEA0_3), registers
   func_L00_003ADA30 to draw the links, and when a flagged moby of another class (not the hero's)
   blocks a link, marks whichever end of it is nearer to that moby and records the blocker. */
void UpdateMobyLinks(void)
{
    int i, j, n, row;
    char *moby, *other, *vars, *hit;

    for (i = 1; i <= ref_L00_003ADEA0_0[0]; i++) {
        moby = ref_L00_003ADEA0_1 + (ref_L00_003ADEA0_0[i] << 8);
        {
            char *first = *(char **)(moby + 0x68);

            if (*(int *)(first + 0x7C) == ref_L00_003ADEA0_2)
                return;
            *(int *)(first + 0x7C) = ref_L00_003ADEA0_2;
            *(short *)(first + 0x4A) = i - 1;
        }
        if (i >= 11)
            math_trap_always();
        row = i - 1;
        if (*(unsigned char *)(moby + 0x20) != 6)
            continue;
        n = 0;
        for (j = 1; j <= ref_L00_003ADEA0_0[0]; j++) {
            other = ref_L00_003ADEA0_1 + (ref_L00_003ADEA0_0[j] << 8);
            if (*(unsigned char *)(other + 0x20) != 6 || other == moby || *(short *)(other + 0xAA) != 0x81F /* moby class 2079 */)
                continue;
            if (!(fast_vec_dist(moby + 0x10, other + 0x10) < 12.0f))
                continue;
            if (*(int *)(*(char **)(other + 0x68) + 0x7C) == ref_L00_003ADEA0_2)
                continue;
            if (CollLine(other + 0x10, moby + 0x10, 2, 0, 0))
                continue;
            part_spawn_sparks_between_mobys(moby, other);
            if (n >= 8)
                math_trap_always();
            ref_L00_003ADEA0_3[row][n++] = other;
            ref_L00_003ADEA0_3[row][n] = 0;
            if (!CollLine(moby + 0x10, other + 0x10, 0, moby, 0))
                continue;
            hit = ref_L00_003ADEA0_4.hit;
            if (!hit || *(short *)(hit + 0xAA) == *(short *)(moby + 0xAA) || hit == g_hero_state.moby
                || !(*(unsigned short *)(hit + 0x34) & 0x1000))
                continue;
            if (fast_vec_dist(hit + 0x10, moby + 0x10) < fast_vec_dist(hit + 0x10, other + 0x10))
                other = moby;
            *(unsigned char *)(other + 0x20) |= 8;
            vars = *(char **)(other + 0x68);
            anim_start_blended(other, 1, 0, 3);
            PlayMobySound(0, 0, other);
            *(char **)(vars + 0x54) = hit;
            *(int *)(vars + 0x58) = 600;
            *(short *)(vars + 0x52) = 1;
            *(short *)(vars + 0x48) = 7;
            *(int *)(vars + 0x40) = 0;
        }
        if (n)
            gfx_add_draw_callback_first(DrawMobyLinkQuads, moby);
    }
}
