#include "include_asm.h"

#include "common.h"
extern char D_00189E20[];
extern char *D_L00_001C3280[];
extern int func_002E5CF8(int index, int mode, void *object);
extern void func_L00_002D3778(void *dst, void *src, float scale);
extern void func_PAL_L00_0038E960(void *position, int count);
/* Type id of an object's data record, or 0 when the object or record is missing. */
static __inline__ int object_type(char *object)
{
    char *data;
    return object != 0 && (data = *(char **)(object + 0x24)) != 0
        ? *(short *)(data + 0x46) : 0;
}

/* Play sound 1 once, then for each of the first count slot objects of type 5 or 9 emit effect 4 at its scaled position. */
void func_PAL_L00_002BA0B0(void *object, int count)
{
    float position[4] __attribute__((aligned(16)));
    char **slot;
    int type;
    int remaining;
    char *base;

    if (count != 0) {
        base = D_00189E20;
        if (*(short *)(base + 0xbfe) == 0) {
            func_002E5CF8(1, 0, object);
            *(short *)(base + 0xbfe) = 1;
        }
        if (count > 0) {
            remaining = count;
            slot = D_L00_001C3280;
            do {
                type = object_type(*slot);
                if (type == 5 || type == 9) {
                    qcopy(position, *slot + 0x10);
                    func_L00_002D3778(position, position, 0.5f);
                    func_PAL_L00_0038E960(position, 4);
                }
                remaining--;
                slot++;
            } while (remaining != 0);
        }
    }
}
