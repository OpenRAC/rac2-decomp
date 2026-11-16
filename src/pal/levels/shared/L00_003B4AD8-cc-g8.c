#include "names.h"
/* func_PAL_L00_003B4AD8, the PAL copy of func_L00_003B1270: the same C, where the 480-frame slot age
   becomes 400, D_L00_001AF82C and D_L00_001AF830 are read as ints, and both spawn values take the
   50 Hz scale. */
#include "common.h"

extern unsigned char g_trail_slot_head __attribute__((sda));

extern unsigned char g_trail_slot_tail __attribute__((sda));

extern char g_effect_path_node_table[];

extern int g_fireboot_debris_count_base __attribute__((sda));
extern int g_fireboot_debris_kind_base __attribute__((sda));
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
extern int g_pad_pressed_flags NOT_SDA;
extern float g_fireboot_trail_params_a[4];
extern float g_fireboot_trail_params_b[4];
extern void node_free_slot(int);
extern char *RecordHeroTrailNode(void *);
extern int func_001163B0(void);
extern void *part_spawn_debris_two_mode(void *,int,int,int,int,int,void *,float,float);
extern void ref_L00_003B1270_0(int,int,int,void *,int);

/* Releases slot-table entries taken 400 or more frames ago, steps the moby's state 0, 1, 2, and in
   state 2 spawns a particle at the hero when the hero's button word has a bit of D_00138320 set
   (recording it in a new slot when func_L00_003B0DA0 gives one); then hands both slot cursors to
   ref_L00_003B1270_0. */
void fireboot_weapon_update_pal(char *m)
{
    int stop = 0, result;
    short random;
    short random2;
    unsigned char slot;
    char *entry;

    while (!stop && g_trail_slot_tail != g_trail_slot_head) {
        if (g_frame_l00_counter - ((SlotEntry1270 *)g_effect_path_node_table)[g_trail_slot_tail].used < 400)
            stop = 1;
        else
            node_free_slot(g_trail_slot_tail);
    }
    switch ((unsigned char)m[0x20]) {
    case 0:
        m[0x20] = 1;
        break;
    case 1:
        m[0x20] = 2;
        break;
    case 2:
        if (g_pad_pressed_flags & g_hero_state.buttons) {
            entry = RecordHeroTrailNode(g_hero_state.position);
            if (entry) {
                slot = g_trail_slot_head - 1;
                random = ((s32)(g_fireboot_debris_count_base + (func_001163B0() & 7)) * 5 + 2) / 6;
                result = part_spawn_debris_two_mode(g_hero_state.position, slot, 0, random, 1, (unsigned char)(((s32)(g_fireboot_debris_kind_base + (func_001163B0() & 3)) * 5 + 2) / 6), m, 1, 1);
                *(int *)(entry + 0x10) = result;
            } else {
                random2 = ((s32)(g_fireboot_debris_count_base + (func_001163B0() & 7)) * 5 + 2) / 6;
                part_spawn_debris_two_mode(g_hero_state.position, 0, 1, random2, 1, (unsigned char)(((s32)(g_fireboot_debris_kind_base + (func_001163B0() & 3)) * 5 + 2) / 6), m, 1, 1);
            }
        }
        break;
    }
    ref_L00_003B1270_0(0x41, 0x41, 0x80000000, g_fireboot_trail_params_a, g_trail_slot_head);
    ref_L00_003B1270_0(0x40, 0x40, 0x80F0F0F0, g_fireboot_trail_params_a, g_trail_slot_head);
    ref_L00_003B1270_0(0x41, 0x51, 0x80000000, g_fireboot_trail_params_b, g_trail_slot_tail);
    ref_L00_003B1270_0(0x40, 0x50, 0x80F0F0F0, g_fireboot_trail_params_b, g_trail_slot_tail);
}
