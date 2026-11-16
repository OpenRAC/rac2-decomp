#include "include_asm.h"
#include "names.h"


/* func_US2_002DBA70, the USA v2.00 copy of func_002DAD18: the same C, where the D_001A7BB4 % 5 index
   becomes D_0025E0B0, the value func_US2_002D5C58 stores through the table D_US2_001ABAF0.
   The stream block D_0014B540 seen as its two tables of five {start, length} reads. */
typedef struct {
    char reserved[0x44];
    int state;
    unsigned int first, second;
    int index, pending;
} Handles_2DCB28;
typedef struct { int start, length; } StreamRead2DAD18;
typedef struct {
    char pad0[0x36C];
    int offset;
    char pad370[0xDD0 - 0x370];
    StreamRead2DAD18 first[5];
    StreamRead2DAD18 second[5];
} StreamReads2DAD18;
extern short g_sequence_active_flag;
extern int g_menu_selection_input_state;
extern StreamReads2DAD18 g_copy_setup_data;
extern int load_start_disc_read(int, int, int);

/* Starts the read of the first, then the second stream once the loader is idle: states 0 to 4, or -1 when a read is refused. */
int menu_stream_reads_update_us2(Handles_2DCB28 *handles)
{
    switch (handles->state) {
    case 0:
        if (handles->first != 0) {
            if (g_sequence_active_flag != 0)
                break;
            {
                StreamReads2DAD18 *reads = &g_copy_setup_data;
                int offset = reads->offset;

                if (load_start_disc_read(handles->first,
                                  reads->first[g_menu_selection_input_state].start + offset,
                                  reads->first[g_menu_selection_input_state].length) != 0)
                    handles->state++;
                else
                    handles->state = -1;
            }
        }
        break;
    case 1:
        if (g_sequence_active_flag != 0)
            break;
        handles->state = 2;
        break;
    case 2:
        if (handles->second != 0) {
            if (g_sequence_active_flag != 0)
                break;
            {
                StreamReads2DAD18 *reads = &g_copy_setup_data;
                int offset = reads->offset;

                if (load_start_disc_read(handles->second,
                                  reads->second[g_menu_selection_input_state].start + offset,
                                  reads->second[g_menu_selection_input_state].length) != 0)
                    handles->state++;
                else
                    handles->state = -1;
            }
        }
        break;
    case 3:
        if (g_sequence_active_flag != 0)
            break;
        handles->state = 4;
        break;
    }
    return 0;
}
