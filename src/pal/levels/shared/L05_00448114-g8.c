#include "include_asm.h"

#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
extern int g_ship_state __attribute__((sda));
extern int g_ship_crash_recovery_time __attribute__((sda));
extern int g_ship_transition_timer __attribute__((sda));
extern int g_ship_fade_level_a MACRO_ADDR, g_ship_fade_level_b MACRO_ADDR;
typedef struct { char pad[0x20]; int model; } Entry;
typedef struct { char pad[0x1C]; Entry *entry; } ModelSlot;
typedef struct { char data[256]; } ModelRecord;
extern ModelSlot *g_path_l05_entry_table MACRO_ADDR;
extern ModelRecord *g_feltzin_target_mobys MACRO_ADDR;
extern char g_ship_record_position[] __attribute__((aligned(16))) MACRO_ADDR;
extern char g_ship_saved_euler[] __attribute__((aligned(16))) MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern unsigned char *func_L05_003D1E60(void *,int,int);
extern void ship_update_record_transform(void *,float);
extern void mat_get_euler_angles(void *,void *);

/* Starts the recorded-path transition for the ship: saves its position and orientation and sets the timer (PAL: 50 Hz). */
void ship_start_record_playback_pal(char *obj)
{
    Quadword matrix[4];
    Entry *entry;
    float scale;
    if (g_ship_state != 6) {
        ModelSlot *slots = g_path_l05_entry_table;
        ModelRecord *models = g_feltzin_target_mobys;
        {
            int index = *(short *)(obj + 0x84);

            g_ship_state = 6;
            entry = slots[index].entry;
        }
        g_ship_fade_level_a = 0;
        {
            int index = entry->model;

            g_ship_fade_level_b = 0;
            func_L05_003D1E60(models[index].data + 0x10, 0, 1);
        }
        qcopy(g_ship_record_position, obj + 0x30);
        scale = 1.0f;
        if (g_current_map_index == 20) scale = 2.0f;
        ship_update_record_transform(obj, scale);
        g_ship_transition_timer = ((s32)(g_ship_crash_recovery_time) * 5 + 2) / 6;
        qcopy(&matrix[0], obj);
        qcopy(&matrix[1], obj + 0x10);
        qcopy(&matrix[2], obj + 0x20);
        qzero(&matrix[3]);
        ((float *)matrix)[3] = ((float *)matrix)[7] = ((float *)matrix)[11] = 0.0f;
        ((float *)matrix)[15] = 1.0f;
        mat_get_euler_angles(matrix, g_ship_saved_euler);
    }
}
