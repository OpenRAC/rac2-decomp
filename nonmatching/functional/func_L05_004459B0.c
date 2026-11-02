/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* GPT-6.1 Sol high, task v0718, USA v1.01, default game -G0 profile.
 * Best check.py: 232/232 bytes, 0/4 places; four instruction
 * positions differ, starting at +0x94. The a1=self move follows the
 * instance-table load and index shift, while retail moves a1 first.
 * Typed 32/256/128-byte table entries recover all initial allocation.
 * Direct call comparison, a separate instance local and assigning the return
 * to a float tie. NOT_SDA for the instance table regresses to 240 bytes.
 * Reopen with evidence for the remaining call-setup scheduling difference.
 * All required declarations follow; not linked.
 */
#include "common.h"
typedef struct { char pad[0x1C]; char *entry; } ModelSlot;
typedef struct { char data[256]; } ModelRecord;
typedef struct { char data[128]; } InstanceRecord;
extern ModelSlot *D_L05_001B1EC4 MACRO_ADDR;
extern ModelRecord *D_L05_001B251C MACRO_ADDR;
extern InstanceRecord *D_L05_001B260C MACRO_ADDR;
extern int func_002ACBC8(void *, int);
extern float func_00282DB0(char *, char *);
int func_L05_004459B0(void *arg)
{
    char *self = arg;
    char *entry;
    char *p;
    char *tbl;
    int count;
    int id;
    int v;
    float best = 0.0f;

    entry = D_L05_001B1EC4[*(short *)(self + 0x84)].entry;
    p = entry + 0x24;
    tbl = D_L05_001B251C[*(int *)(entry + 0x20)].data;

    for (count = 0; count < 12; count++, p += 4) {
        v = *(int *)p;
        if (v < 0)
            continue;
        if (func_002ACBC8(self + 0x30, v) != 0) {
            id = *(int *)p;
        } else {
            if (func_002ACBC8(tbl + 0x10, *(int *)p) == 0)
                continue;
            id = *(int *)p;
        }
        if (func_00282DB0(D_L05_001B260C[id].data, self) > best)
            return 1;
    }
    return 0;
}
