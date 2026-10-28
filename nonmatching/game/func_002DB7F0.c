/* func_002DB7F0 - 404 bytes, 28 places (src/game/002D5E98.c): draws a menu
   (entries at menu+0x34, selection at +0x38, height at +0x24), one line per
   entry with its value text, the selected one highlighted.  Returns 2.

   Near miss: right size, 7 lines after masking relocations, all register
   choice: retail counts the entries in $a0 with the pointer in $v1 and loads
   the height into $v1 for the divide; here the count is $a1 and the pointer
   $a0.  Retail also builds the first call's 0x2004B before `sd $s3`.

   Tried: four forms of the counting loop, the declaration order, the first
   callee returning int, its second argument unsigned. */

#include "include_asm.h"

extern void func_002FC560(int, int);
extern void func_0027C540(int);
extern void func_0027C660(void);
extern signed char *func_00288FB8(int);
extern void func_0027F538(int, int, long, signed char *, int);
extern void func_0027F980(int, int, long long, signed char *, int);

typedef struct { int text; unsigned char **kind; int pad[4]; } Item2DB7F0;

int func_002DB7F0(char *menu)
{
    int count;
    Item2DB7F0 *p;
    int step;
    int y;
    int i;
    Item2DB7F0 *entry;
    int style;

    func_002FC560(0x47, 0x2004B);
    func_0027C540(0);
    count = 0;
    p = *(Item2DB7F0 **)(menu + 0x34);
    while (p->text != 0) {
        count++;
        p++;
    }
    step = *(int *)(menu + 0x24) / (count + 1);
    y = step - 8;
    i = 0;
    if ((*(Item2DB7F0 **)(menu + 0x34))->text != 0) {
        do {
            entry = *(Item2DB7F0 **)(menu + 0x34) + i;
            style = i == *(int *)(menu + 0x38) ? 0x8020FFFF : 0x80FFA888;
            func_0027F538(0xC, y, style, func_00288FB8(entry->text), -1);
            i++;
            entry = (Item2DB7F0 *)((char *)entry + **(unsigned char **)&entry->kind * 4);
            func_0027F980(*(int *)(menu + 0x20) - 0xC, y, 0x80FFA888LL,
                          func_00288FB8(((int *)entry)[2]), -1);
            y += step;
        } while ((*(Item2DB7F0 **)(menu + 0x34))[i].text != 0);
    }
    func_0027C660();
    return 2;
}
