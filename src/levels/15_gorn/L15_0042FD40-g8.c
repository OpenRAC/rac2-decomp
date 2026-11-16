#include "names.h"
typedef struct StageSetup {
    int initial;
    char pad04[0x10];
    int count;
    char pad18[0x10];
    int limit;
    int timer;
    float scale;
} StageSetup;

typedef struct StageRecord {
    int words[10];
} StageRecord;

extern int g_challenge_menu_choice __attribute__((sda));
extern int g_cutscene_l15_started_flag __attribute__((sda));
extern int g_gorn_enabled_flag __attribute__((sda));
extern StageSetup g_gorn_challenge_vars;
extern StageRecord g_weapon_l15_table[];
extern int table_find_last_used_entry(int);
extern void hero_set_state_value_b(int);
extern void table_reset_working_values(void);
extern void level_clear_object_records(void);

/* Resets the Gorn stage counters and restores the selected record's value. */
void ResetGornStageCounters(void)
{
    StageSetup *stage = &g_gorn_challenge_vars;
    int recordIndex;

    g_challenge_menu_choice = -2;
    g_gorn_enabled_flag = 1;
    stage->timer = 1;
    stage->limit = 100;
    g_cutscene_l15_started_flag = 0;
    stage->count = 0;
    recordIndex = table_find_last_used_entry(6);
    stage->scale = 8.0f;
    g_weapon_l15_table[recordIndex].words[5] = g_weapon_l15_table[recordIndex].words[4];
    hero_set_state_value_b(0);
    table_reset_working_values();
    level_clear_object_records();
}

