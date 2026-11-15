#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad[0x284];
    char *target;
    int timer;
} HeroD740;
extern char *g_moby_l04_pool __attribute__((sda));
extern char *D_L04_001B25CC[] __attribute__((sda));
extern char g_hero_position[], g_sound_state[];
extern HeroD740 D_L04_001B9540;
extern u8 D_0019B2E8[];
extern char *g_hero_moby;
extern int g_current_map_index __attribute__((sda));
extern int moby_count_group_not_in_state(int, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int IsPointInCuboid(void *, int);
extern void cam_lock_entry(int);
extern int cam_is_trigger_ready(int);
extern void moby_mark_table_entry_flagged(unsigned int);
extern void level_capture_checkpoint_state(void *, void *);
extern int snd_start_in_slot(int, int, void *);
extern void moby_set_flag_bit(void *, int);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void snd_stop_voice(int);


