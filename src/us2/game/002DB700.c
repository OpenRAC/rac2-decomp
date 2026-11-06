#include "include_asm.h"


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
extern short D_001A63AC;
extern int D_0025E0B0;
extern StreamReads2DAD18 D_0014B540;
extern int func_002B7B18(int, int, int);

int func_US2_002DBA70(Handles_2DCB28 *object)
{
    switch (object->state) {
    case 0:
        if (object->first != 0) {
            if (D_001A63AC != 0)
                break;
            {
                StreamReads2DAD18 *reads = &D_0014B540;
                int offset = reads->offset;

                if (func_002B7B18(object->first,
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
                StreamReads2DAD18 *reads = &D_0014B540;
                int offset = reads->offset;

                if (func_002B7B18(object->second,
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
