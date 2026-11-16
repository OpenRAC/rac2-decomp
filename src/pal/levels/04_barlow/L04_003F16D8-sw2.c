#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad[0x284];
    char *target;
    int timer;
} HeroD740;
extern char *g_moby_l04_pool __attribute__((sda));
extern char *g_linked_record_table[] __attribute__((sda));
extern char g_hero_position[], g_sound_state[];
extern HeroD740 g_hero_l04_state;
extern u8 g_moby_group_flags[];
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
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern void snd_stop_voice(int);


