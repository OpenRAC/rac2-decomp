#include "common.h"

/* func_L10_00425888: clamps the four 32-bit values at D_L10_001B1390 to 127 and copies their
   low bytes into the block at D_L10_001395B8 (+0x66..+0x69).
   Built -G8.  Retail reads the first word through $gp everywhere (sda) and the other three
   as absolute macro loads at the first word + 4/8/12.  The offset form is also why those
   three loads never fill a delay slot: this cc1 gives a symbol+offset memory operand length 2
   (simple_memory_operand accepts only a bare small-data symbol), so each clamp's branch slot
   takes the 127 from the fall-through, as in retail, and the last branch steals the bare
   $gp load of the first word from its target.  Two names for the one block: the sda scalar
   and the absolute macro form of the same address (D_L10_001B1390_4). */
extern s32 g_mission_completion_counts __attribute__((sda));
extern s32 D_L10_001B1390_4[] MACRO_ADDR;
extern u8 g_mission_save_block[];

void mission_store_completion_counts(void) {
    if (g_mission_completion_counts > 0x7F) g_mission_completion_counts = 0x7F;
    if (D_L10_001B1390_4[1] > 0x7F) D_L10_001B1390_4[1] = 0x7F;
    if (D_L10_001B1390_4[2] > 0x7F) D_L10_001B1390_4[2] = 0x7F;
    if (D_L10_001B1390_4[3] > 0x7F) D_L10_001B1390_4[3] = 0x7F;

    g_mission_save_block[0x66] = g_mission_completion_counts;
    g_mission_save_block[0x67] = D_L10_001B1390_4[1];
    g_mission_save_block[0x68] = D_L10_001B1390_4[2];
    g_mission_save_block[0x69] = D_L10_001B1390_4[3];
}
