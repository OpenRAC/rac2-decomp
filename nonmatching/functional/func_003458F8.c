/* functional: medium. Only one captured call, so the pad branches are read from the assembly, not exercised. Menu cursor handler: pad bits 0x1000 up, 0x4000 down, 0x8000 left, 0x2000 right (each plays sound 3 and moves the column at +0x48C / row at +0x490 with the retail wrap rules), 0x40 select; then looks up the 10-byte entry at 0x259CE0 for (col + row*3), stores its id at +0x494 and, when the id is flagged, copies a short from the 0xE0-byte table into the gp-relative word; written as the same branches and writes in the same order, only codegen differs. */
extern void func_002E5E58(int a, int b, int c);
extern char D_00259CE0[];
extern unsigned char D_001A7AF8[];
extern unsigned char D_00139568[];
extern char D_00239BA0[];
extern int D_001F2880;
extern int D_001ADB10 __attribute__((sda));

void func_003458F8(char *self, int buttons) {
    int x, y, id;
    int *px = (int *)(self + 0x48C);
    int *py = (int *)(self + 0x490);
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        y = *py - 1;
        *py = y;
        if (y < 0) {
            *py = 0;
            *(int *)(self + 0x498) = 1;
        }
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        y = *py;
        if (y == 0) {
            if (*px == 0) {
                *py = 1;
                *px = 1;
            } else {
                *py = 1;
            }
        } else if (y == 1) {
            *(int *)(self + 0x498) = 3;
            x = *px;
            *py = 0;
            *px = x - 1;
        }
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        x = *px - 1;
        *px = x;
        if (*py == 0) {
            *px = (x > -1) ? x : 2;
        } else {
            *px = (x > 0) ? x : 2;
        }
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        x = *px + 1;
        *px = x;
        if (*py == 0) {
            *px = (x > 2) ? 0 : x;
        } else {
            *px = (x > 2) ? 1 : x;
        }
    } else if (buttons & 0x40) {
        int sel = *(short *)(D_00259CE0 + (*px + *py * 3) * 10 + 6);
        if (sel != 0 && D_001A7AF8[sel] != 0) {
            func_002E5E58(4, 0, 0);
            D_001F2880 = sel;
            *(int *)(self + 0x494) = sel;
            return;
        }
        func_002E5E58(5, 0, 0);
    }
    id = *(short *)(D_00259CE0 + (*px + *py * 3) * 10 + 6);
    *(int *)(self + 0x494) = id;
    if (id != 0 && D_001A7AF8[id] != 0) {
        D_001ADB10 = *(short *)(D_00239BA0 + D_00139568[id] * 0xE0 + 6);
    }
}
