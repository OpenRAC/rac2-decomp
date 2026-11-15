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

extern int D_L15_001B1530 __attribute__((sda));
extern int D_L15_001B1534 __attribute__((sda));
extern int D_L15_001B15C4 __attribute__((sda));
extern StageSetup D_L15_00221E10;
extern StageRecord D_L15_0029FD80[];
extern int table_find_last_used_entry(int);
extern void hero_set_state_value_b(int);
extern void table_reset_working_values(void);
extern void level_clear_object_records(void);

/* Resets the Gorn stage counters and restores the selected record's value. */
void ResetGornStageCounters(void)
{
    StageSetup *stage = &D_L15_00221E10;
    int recordIndex;

    D_L15_001B1530 = -2;
    D_L15_001B15C4 = 1;
    stage->timer = 1;
    stage->limit = 100;
    D_L15_001B1534 = 0;
    stage->count = 0;
    recordIndex = table_find_last_used_entry(6);
    stage->scale = 8.0f;
    D_L15_0029FD80[recordIndex].words[5] = D_L15_0029FD80[recordIndex].words[4];
    hero_set_state_value_b(0);
    table_reset_working_values();
    level_clear_object_records();
}

