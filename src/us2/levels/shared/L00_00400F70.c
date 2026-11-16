#include "include_asm.h"

#include "common.h"
extern void moby_set_state(char *pickup, int mode, int value);
extern void func_L00_003FF7B8_1(char *pickup);
extern void glow_ring_effect_update(char *pickup);
extern float func_00282E80_3(char *pickup, char *table);
extern float func_00282C48_10(float value);
extern void value_set_entry_by_index(int pickup, int value);
extern void help_unlock_entry(int pickup);
extern int moby_handle_request_slot_state(int pickup);
extern void func_0029F338_4(char *pickup);
extern char D_00189EA0_2[];
extern unsigned char g_action_flag __attribute__((sda));

/* two-phase update on a record: phase 0 marks a byte with 255 and either runs a shared two-call teardown when a global latch byte is set and a sub-vars field is non-zero, or plays a mode/value pair plus a call; phase 1 runs a setup call and two float queries against a stored table and, when both are below 2.0, plays three fixed calls and either tears down or writes 120 into a sub-vars field */
void charge_boots_pickup_update_us2(char *pickup)
{
    int *vars = *(int **)(pickup + 104);
    unsigned char phase = *(unsigned char *)(pickup + 32);

    switch (phase) {
    case 0:
        *(unsigned char *)(pickup + 48) = 255;
        if (g_action_flag != 0 && vars[17] != 0) {
            func_0029F338_4((char *)vars[17]);
            func_0029F338_4(pickup);
            return;
        } else {
            moby_set_state(pickup, 1, -1);
            func_L00_003FF7B8_1(pickup);
        }
        break;
    case 1:
        glow_ring_effect_update(pickup);
        if (func_00282E80_3(pickup + 16, D_00189EA0_2) < 2.0f) {
            if (func_00282C48_10(*(float *)(pickup + 24) - *(float *)(D_00189EA0_2 + 8)) < 2.0f) {
                value_set_entry_by_index(4658, -1);
                help_unlock_entry(54);
                moby_handle_request_slot_state(54);
                if (vars[17] != 0) {
                    func_0029F338_4((char *)vars[17]);
                    func_0029F338_4(pickup);
                    return;
                }
                vars[16] = 120;
            }
        }
        break;
    }
}

