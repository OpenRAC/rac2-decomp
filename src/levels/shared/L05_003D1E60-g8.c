#include "include_asm.h"
#include "common.h"

extern float g_effect_slot_state __attribute__((sda));
extern char *g_spawned_effect_mobys[] MACRO_ADDR;
extern int g_spawned_effect_times[] MACRO_ADDR;
extern int g_glow_effect_blends[] MACRO_ADDR;
extern int g_feltzin_mission_index MACRO_ADDR;
extern void moby_mark_spawned(void *object);
extern unsigned char *CreateMoby(int type);

/* Spawns a 0x986 object into the first free one of five slots, passing VALUE and its slot in its
   state. The slot table is reset on first use (count -1); when all five are taken and EVICT is
   set, the slot whose spawn frame is oldest is freed first. */
/* Spawns an explosion in the first free of five slots and frees the oldest one if all are used
   and asked to. */
unsigned char *func_L05_003D1E60(void *position, int value, int evict)
{
    int i;
    int selected;
    int age;
    int oldest;
    int now;
    unsigned char *object;
    char *state;

    if (g_effect_slot_state == -1.0f) {
        for (i = 4; i >= 0; i--)
            g_spawned_effect_mobys[i] = 0;
        g_effect_slot_state = 0.0f;
    }
    if (g_effect_slot_state >= 5.0f) {
        if (evict) {
            now = g_feltzin_mission_index;
            oldest = 0;
            selected = -1;
            for (i = 0; i < 5; i++) {
                age = now - g_spawned_effect_times[i];
                if (age > oldest) {
                    oldest = age;
                    selected = i;
                }
            }
            if (selected >= 0) {
                moby_mark_spawned(g_spawned_effect_mobys[selected]);
                g_spawned_effect_mobys[selected] = 0;
                g_glow_effect_blends[selected] = 0;
                g_effect_slot_state -= 1.0f;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    for (i = 0; i < 5 && g_spawned_effect_mobys[i] != 0; i++) {}
    object = CreateMoby(0x986);
    if (object) {
        state = *(char **)(object + 0x68);
        object[0x30] = 255;
        object[0x20] = 0;
        *(int *)(state + 8) = value;
        *(int *)state = i;
        qcopy(object + 0x10, position);
        g_spawned_effect_mobys[i] = (char *)object;
        g_spawned_effect_times[i] = g_feltzin_mission_index;
        g_effect_slot_state += 1.0f;
    }
    return object;
}
