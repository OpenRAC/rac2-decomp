#include "names.h"
typedef struct {
    short id, animation;
    float scale;
} StartupEntry;
typedef struct { StartupEntry entries[13]; } StartupTable;
typedef struct {
    unsigned char pad00[0x30];
    int state;
    unsigned char pad34[0x10];
    short count;
    unsigned char pad46[0x146];
    unsigned char *objects[0];
} StartupContext;

extern StartupTable g_startup_table;
extern unsigned char g_unlocked_item_flags __attribute__((section(".sdata")));
extern StartupContext g_tutorial_probe_context;
extern unsigned char g_startup_anim_slots[];
extern float g_startup_anim_param __attribute__((section(".sdata")));
extern int g_current_map_index __attribute__((section(".sdata")));
extern void func_L00_00311238(void *, int, void *);

/* Starts the configured startup animation for eligible objects in the level. */
void anim_start_startup_animations(void)
{
    StartupTable table;
    int i;
    if (g_unlocked_item_flags) {
        table = g_startup_table;
        for (i = 0; i < g_tutorial_probe_context.count; i++) {
            unsigned char *object = g_tutorial_probe_context.objects[i];
            int j;
            if (*(int *)(object + 0x54))
                continue;
            for (j = 0; table.entries[j].id; j++) {
                if (*(short *)(object + 0xaa) == table.entries[j].id) {
                    float scale = table.entries[j].scale;
                    int k;
                    for (k = 0; k < 7; k++) {
                        if (!g_startup_anim_slots[k * 64 + 1])
                            break;
                    }
                    if (k < 7) {
                        unsigned char *slot = g_startup_anim_slots + k * 64;
                        func_L00_00311238(object, table.entries[j].animation, slot);
                        *(float *)(slot + 0x20) = scale;
                        *(float *)(slot + 0x24) = scale;
                        *(float *)(slot + 0x28) = scale;
                    }
                }
            }
        }
        if (g_current_map_index == 6 && g_tutorial_probe_context.state == 1)
            g_startup_anim_param = -0.25f;
    }
}
