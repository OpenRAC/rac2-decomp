/* functional: high. Written from the assembly, including the jump table at 0x26C530 (cases 0, 1, 2, 4 and 7 do something, 3, 5, 6 and 8 or more return 0); case 7 reads other without a null check, as retail does. */
#include "common.h"

extern void *D_0026E900[][5];       /* per-kind dispatch records (20 bytes each) */
extern char *D_001B1504;            /* table of 32-byte entries */
extern char *D_001B1380;            /* table of 32-byte entries */
extern char D_00189EA0[];           /* argument of func_002ACBC8 */
extern char D_00189E20[];           /* a block of globals, read at +0x630, +0x640 and +0x24A0 */
extern int func_002ACBC8(void *, int);

/* TestCameraTakeover: whether the camera object obj (live byte at 124) is to be taken over
   given the current one `other`. A hook in the object's kind record may decide (-1 for no, 1 for
   yes); otherwise the object's mode word at +116 chooses: 0, 1 and 2 compare priorities
   (byte 124) when other has no hold (+126 is zero), 4 asks func_002ACBC8 about the entry's
   target, and 7 checks the object's state against the globals. */
int func_00270838(char *obj, char *other)
{
    unsigned int mode;
    int (*hook)(char *, char *);
    char *ent;

    if (*(unsigned char *)(obj + 124) == 0) {
        return 0;
    }
    hook = (int (*)(char *, char *))D_0026E900[*(short *)(obj + 140)][1];
    if (hook != 0) {
        int r = hook(obj, other);

        if (r == -1) {
            return 0;
        }
        if (r == 1) {
            return 1;
        }
    }

    mode = *(unsigned int *)(obj + 116);
    if (mode >= 8) {
        return 0;
    }
    switch (mode) {
    case 1:
    case 2:
        if (*(unsigned char *)(obj + 125) == 0) {
            return 0;
        }
        /* fall through */
    case 0:
        if (other == 0) {
            return 1;
        }
        if (*(short *)(other + 126) != 0) {
            return 1;
        }
        return *(unsigned char *)(other + 124) < *(unsigned char *)(obj + 124);
    case 4: {
        int target;

        ent = D_001B1504 + *(short *)(obj + 132) * 32;
        target = *(int *)(*(char **)(ent + 28) + 12);
        if (other != 0 && *(short *)(other + 126) == 0) {
            if (!(*(unsigned char *)(other + 124) < *(unsigned char *)(obj + 124))) {
                return 0;
            }
        }
        return func_002ACBC8(D_00189EA0, target) != 0;
    }
    case 7: {
        int slot = *(short *)(obj + 134);
        int v;

        if (slot != *(int *)(D_00189E20 + 9376)) {
            return 0;
        }
        if (*(short *)(other + 126) == 0) {
            if (!(*(unsigned char *)(other + 124) < *(unsigned char *)(obj + 124))) {
                return 0;
            }
        }
        if (slot != 3) {
            return 1;
        }
        ent = D_001B1504 + *(short *)(obj + 132) * 32;
        v = *(int *)(*(char **)(ent + 28) + 36);
        if (v < 0) {
            return 1;
        }
        if (*(int *)(D_00189E20 + 1584) != *(int *)(D_001B1380 + v * 32 + 16)) {
            return 0;
        }
        return *(int *)(D_00189E20 + 1600) == 0;
    }
    default:
        return 0;
    }
}
