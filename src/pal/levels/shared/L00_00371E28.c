#include "include_asm.h"
#include "names.h"

extern unsigned int g_save_menu_flags __attribute__((sda));
extern int ref_L00_001A8F00_00 __attribute__((sda));
typedef struct L00_0036FA68_Object {
    unsigned char pad00[0x64];
    void (*field64)(struct L00_0036FA68_Object *);
} L00_0036FA68_Object;
extern L00_0036FA68_Object *ref_L00_001AC0C0_00 __attribute__((sda));
extern void SetBackgroundColor(int a, int b, int c);
extern int request_begin_slot(int a, int b, int c, int d, int e);
extern void game_reset_frame_counters(void);
extern void UpdateSoundVoices(void);
extern void part_update_all(void);
extern void level_count_active_records(void);
extern unsigned int ref_L00_0036FA68_00(void);
extern void game_update_idle_frame_counters(void);
extern void subtitle_update_state_machine(void);

/* Runs the level's tick chain once: the three-argument engine reset, a gate on the resident
 * word and the boot flag, then the subsystem updates and the resident object's callback. */
void func_PAL_L00_00372508(void)
{
    L00_0036FA68_Object *object;

    SetBackgroundColor(0, 0, 0);
    if (ref_L00_001A8F00_00 == 0 && (g_save_menu_flags & 1)) {
        if (request_begin_slot(4, 1, 1, 0, 0) == 0)
            return;
    }
    if (ref_L00_0036FA68_00() != 0)
        return;
    game_reset_frame_counters();
    UpdateSoundVoices();
    part_update_all();
    level_count_active_records();
    object = ref_L00_001AC0C0_00;
    object->field64(object);
    game_update_idle_frame_counters();
    subtitle_update_state_machine();
}


