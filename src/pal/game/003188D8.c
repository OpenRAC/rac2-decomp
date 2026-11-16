#include "include_asm.h"
#include "names.h"



void gfx_call_sync_helper(void);

/* Called when the enemy dies: wakes up its group mates (PAL build). */
void flyer_alert_group_on_death_pal(void)
{
  flyer_alert_group();
  return;
}


#include "common.h"
extern void moby_scale_owner_words_by_angles(float, float, char *, char *, float, char *);
extern void flyer_tick_timers(char *);
extern void gfx_update_color_fade_pal(char *, char *);
extern int FastDecTimer(void *);
extern void math_update_wrapped_angle_offset(char *, float, float, char *, float, char *);
extern void moby_scale_owner_words_by_angles(float, float, char *, char *, float, char *);
extern void gfx_update_color_fade_pal(char *, char *);
extern int FastDecTimer(void *);

/* Counts down the flying enemy's timers and steps its wrapped angle offsets (PAL: 50 Hz timings). */
void flyer_tick_timers_pal(char *object)
{
    char *data = *(char **)(object + 0x68);
    gfx_update_color_fade_pal(object, data + 0x50);
    FastDecTimer(data + 0x270);
    if (FastDecTimer(data + 0x272)) {
        math_update_wrapped_angle_offset(object, 0.1f, 0.10471977f, data + 0x27C, -1.0f, data + 0x280);
        moby_scale_owner_words_by_angles(0.13962635397911071777f, 0.031415932f, object, data + 0x284, 0.031415932f, data + 0x288);
    }
    if (*(unsigned short *)(object + 0x96) <= 65534)
        (*(unsigned short *)(object + 0x96))++;
}

