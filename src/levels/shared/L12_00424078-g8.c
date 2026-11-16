#include "common.h"

/* func_L12_00424078 is a unit of its own: -g (config/cflags.txt) gives the line label that
   puts retail's two-nop floor in front of each div.s (docs/build/compiler-notes.md, "Division/root
   scheduling and padding"), and -G8 reads the frame counter through $gp. */

extern u8 *g_moby_list_start[3] __attribute__((sda)); /* entity base, read bare (lui/lw) */
extern s16 *g_moby_l12_group_lists[];
extern int g_frame_l12_counter __attribute__((sda));
extern char g_str_pulsing_light_debug_a[], g_str_pulsing_light_debug_b[];
extern void STUB_printf(void *, int);
extern void func_L12_0031E1D0(void *, int, int);
extern int moby_count_group_not_in_state(int, int);
extern float IntToFloat(int);
extern int PulseColor(int, int, float);

/* State 0 packs two colours from the byte values in words 0-3 and 4-7 into words 10 and 11
 * and counts the target ids in words 12-15 (up to four, ended by -1) into word 9; state 1,
 * once func_002A8508 reports two or more for its group (+0x21), sets the colour (+0x78) of each
 * group member whose +0x31 flag is set; states 1 and 2 set it on the counted targets. The colour
 * comes from func_L01_0031BC68 with words 10 and 11 and a phase angle of D_L12_001B29C8 modulo
 * the period in word 8. */
/* Makes a group of lights pulse between two colours once the group is switched on. */
void pulsing_light_group_update(u8 *obj) {
    int *vars = *(int **)(obj + 0x68);
    int i;
    int n;
    int first;
    int second;
    s16 *ids;
    u8 *member;
    int period;
    float phase;

    switch (obj[0x20]) {
    case 0:
        n = 0;
        first = vars[3] << 24; first |= vars[2] << 16; first |= vars[1] << 8; first |= vars[0];
        vars[10] = first;
        second = vars[7] << 24; second |= vars[6] << 16; second |= vars[5] << 8; second |= vars[4];
        vars[11] = second;
        vars[9] = 0;
        if (vars[12] != -1) {
            vars[9] = 1;
            do {
                if (++n >= 4) break;
                if (vars[12 + n] == -1) break;
                vars[9]++;
            } while (1);
        }
        if (vars[9]) {
            STUB_printf(g_str_pulsing_light_debug_a, *(s16 *)(obj + 0xB2));
            func_L12_0031E1D0(obj, 2, -1);
        } else {
            STUB_printf(g_str_pulsing_light_debug_b, *(s16 *)(obj + 0xB2));
            func_L12_0031E1D0(obj, 1, -1);
        }
        break;
    case 1:
        if (moby_count_group_not_in_state(obj[0x21], -1) >= 2) {
            ids = g_moby_l12_group_lists[obj[0x21]];
            do {
                member = g_moby_list_start[0] + ((*(u16 *)ids & 0x7FFF) << 8);
                if (member[0x31]) {
                    period = vars[8];
                    phase = IntToFloat(g_frame_l12_counter % period) * 6.2831855f / IntToFloat(period) - 3.1415927f;
                    *(int *)(member + 0x78) = PulseColor(vars[10], vars[11], phase);
                }
            } while (*ids++ >= 0);
        }
    case 2:
        for (i = 0; i < vars[9]; i++) {
            u8 *target = g_moby_list_start[0] + (vars[12 + i] << 8);
            if (target[0x31]) {
                period = vars[8];
                phase = IntToFloat(g_frame_l12_counter % period) * 6.2831855f / IntToFloat(period) - 3.1415927f;
                *(int *)(target + 0x78) = PulseColor(vars[10], vars[11], phase);
            }
        }
        break;
    }
}
