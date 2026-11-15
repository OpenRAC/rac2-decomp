#include "include_asm.h"
#include "names.h"

typedef unsigned int undefined4;
extern undefined4 release_menu_stream_buffer(undefined4);
typedef struct {
    char reserved[0x44];
    int state;
    unsigned int first, second;
    int index, pending;
} Handles_2DCB28;
extern void snd_pump_music_and_disc_read(int);

int func_PAL_002DAFF0(Handles_2DCB28 *object) {
    object->first = release_menu_stream_buffer(object->first);
    object->second = release_menu_stream_buffer(object->second);
    object->index = -1;
    object->pending = -1;
    object->state = -1;
    snd_pump_music_and_disc_read(1);
    return 0;
}



/* func_PAL_002DBA38, the PAL copy of func_002DAD18: the same C, where the D_001A7BB4 % 5 index
   becomes D_0025E0B0, the value PAL's func_PAL_002D5C20 stores through the table D_PAL_001ABB58.
   The stream block D_0014B540 seen as its two tables of five {start, length} reads. */
typedef struct { int start, length; } StreamRead2DAD18;
typedef struct {
    char pad0[0x36C];
    int offset;
    char pad370[0xDD0 - 0x370];
    StreamRead2DAD18 first[5];
    StreamRead2DAD18 second[5];
} StreamReads2DAD18;
extern short D_001A63AC;
extern int D_0025E0B0;
extern StreamReads2DAD18 g_copy_setup_data;
extern int load_start_disc_read(int, int, int);

int func_PAL_002DBA38(Handles_2DCB28 *object)
{
    switch (object->state) {
    case 0:
        if (object->first != 0) {
            if (D_001A63AC != 0)
                break;
            {
                StreamReads2DAD18 *reads = &g_copy_setup_data;
                int offset = reads->offset;

                if (load_start_disc_read(object->first,
                                  reads->first[D_0025E0B0].start + offset,
                                  reads->first[D_0025E0B0].length) != 0)
                    object->state++;
                else
                    object->state = -1;
            }
        }
        break;
    case 1:
        if (D_001A63AC != 0)
            break;
        object->state = 2;
        break;
    case 2:
        if (object->second != 0) {
            if (D_001A63AC != 0)
                break;
            {
                StreamReads2DAD18 *reads = &g_copy_setup_data;
                int offset = reads->offset;

                if (load_start_disc_read(object->second,
                                  reads->second[D_0025E0B0].start + offset,
                                  reads->second[D_0025E0B0].length) != 0)
                    object->state++;
                else
                    object->state = -1;
            }
        }
        break;
    case 3:
        if (D_001A63AC != 0)
            break;
        object->state = 4;
        break;
    }
    return 0;
}
