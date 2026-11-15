#include "include_asm.h"

#include "common.h"

/* func_US2_L04_0040CF60, the v2.00 copy of func_L04_0040BA68: the same C, where the 0x840
   pad test is skipped on the frame that opens the selection (accept). */

/* Field accesses at byte offsets, written as members of an unnamed struct. */
#define S32_AT(p,o) (((struct { char pad[o]; int v; } *)(p))->v)
#define PTR_AT(p,o) (((struct { char pad[o]; char *v; } *)(p))->v)
#define U16_AT(p,o) (((struct { char pad[o]; unsigned short v; } *)(p))->v)

extern int D_L04_001B0978 __attribute__((sda)), g_selected_race_index __attribute__((sda)), g_current_race_index __attribute__((sda));
/* The flag at +0x14 is element 5, as in L04_00412308-g8.c; the offset form keeps
   retail's two-word $at store, which never takes a call's delay slot. */
extern int D_L04_001A8ED0[] MACRO_ADDR;
extern char g_hero_state[] NOT_SDA, g_pad_state[] NOT_SDA;
extern char *g_moby_l04_pool, *D_L04_001B08F4 __attribute__((sda));
/* Five 64-byte entries; a set bit 28 in flags lets the entry be chosen. The
   entries are members of one object, so the row address adds base first. */
typedef struct { int head; int flags; char rest[56]; } SelectEntry;
extern struct { SelectEntry entry[5]; } g_race_challenge_table NOT_SDA;
extern void snd_send_cmd22(int), snd_send_cmd23(int);
extern int snd_Pump(void);
extern void music_Pause(int), music_Unpause(void);
extern void racer_reset_state(char *, int);
extern int func_US2_L04_002E7F28(int,int);
extern void racer_release_sound_handles(char *, char *), racer_release_link_state(char *,char *);
extern int snd_play_from_global_bank(int,int,void *);
extern int race_get_course_win_count(int);
/* Five-entry selection: pad bits 0x8000/0x2000 move D_L04_001B0904 with wraparound;
   0x840 takes the entry if its flag is set or func_L04_0040A1D0 of the previous entry
   is positive (sound 4, else 5), and 0x10 ends through func_L04_0040AC30. loop.c
   reverses the count-up slot loop, so its counter is set after the hoisted -1. */
void func_US2_L04_0040CF60(char *m, char *p)
{
    int done = 0;
    int accept = 1;
    int *slot, i;
    char *obj, *extra, *child, *base;
    if (!D_L04_001B0978) {
        accept = 0;
        D_L04_001A8ED0[5] = 1;
        snd_send_cmd22(0x5d); music_Pause(0); snd_Pump();
        D_L04_001A8ED0[0] = 1;
        racer_reset_state(m,0);
        g_selected_race_index = g_current_race_index;
        D_L04_001B0978 = 1;
    }
    if (S32_AT(g_hero_state,0x2294) != 0x31) func_US2_L04_002E7F28(0x31,1);
    U16_AT(m,0x34) |= 0x41;
    if (S32_AT(p,0x1dc) != -1) {
        obj = g_moby_l04_pool + (S32_AT(p,0x1dc) << 8);
        extra = D_L04_001B08F4;
        U16_AT(obj,0x34) |= 0x41;
        if (extra) U16_AT(extra,0x34) |= 0x41;
    }
    base=g_moby_l04_pool;
    slot=(int *)(p+0x1e4);
    for (i=0;i<21;i++) {
        if (slot[i] != -1) {
            obj=base+(slot[i]<<8);
            U16_AT(obj,0x34)|=0x41;
            child=PTR_AT(PTR_AT(obj,0x68),0x8c);
            if (child) U16_AT(child,0x34)|=0x41;
        }
    }
    racer_release_sound_handles(m,p);
    S32_AT(g_hero_state,0x24a0)=26;
    g_hero_state[0x22b5]=1;
    S32_AT(PTR_AT(g_hero_state,0x2290),0x98)=0;
    if (S32_AT(g_pad_state,0x1c4)&0x8000) {
        snd_play_from_global_bank(3,0,0);
        g_selected_race_index=g_selected_race_index-1;
        if (g_selected_race_index < 0) g_selected_race_index=4;
    } else if (S32_AT(g_pad_state,0x1c4)&0x2000) {
        snd_play_from_global_bank(3,0,0);
        g_selected_race_index=g_selected_race_index+1;
        if (g_selected_race_index >= 5) g_selected_race_index=0;
    }
    if (accept && (S32_AT(g_pad_state,0x1c4)&0x840)) {
        if ((g_race_challenge_table.entry[g_selected_race_index].flags&0x10000000) || (g_selected_race_index>0 && race_get_course_win_count(g_selected_race_index-1)>0)) {
            snd_play_from_global_bank(4,0,0); done=1;
            g_current_race_index=g_selected_race_index;
            m[0xbc]=2;
        } else snd_play_from_global_bank(5,0,0);
    } else if (S32_AT(g_pad_state,0x1c4)&0x10) {
        snd_play_from_global_bank(4,0,0);done=1;
        racer_release_link_state(m,p);
        S32_AT(p,0x320)=-1;m[0x20]=4;
    }
    if (done) {
        snd_send_cmd23(0x5d);music_Unpause();snd_Pump();
        D_L04_001A8ED0[5]=0;D_L04_001A8ED0[0]=0;D_L04_001B0978=0;
    }
}
