/* functional: high. Near-miss draft; same reads, writes and calls in the same order, only the byte layout differs. */

typedef unsigned char u8;

typedef struct { char pad0[0xC]; int kind; char pad1[4]; int handle; char pad2[0xC8]; } Entry_002AD860;

extern u8 D_00139568[];
extern Entry_002AD860 D_00239BA0[];
extern int D_0018C0E8[];
extern short D_001A63AC;

extern int func_00294630(int);
extern void func_00294420(int);

/* Marks entry a0's slot as taken, starting the entry's handle when it was idle.
   Returns 1 when the slot was taken, 0 when it is blocked. */
int func_002AD860(int a0)
{
    u8 *p = D_00139568 + a0;
    Entry_002AD860 *e = &D_00239BA0[*p];
    int ret = 0;

    if (e->kind == 0) {
        if (func_00294630(e->handle) == 0) {
            if (D_001A63AC != 0)
                return ret;
        }
        D_0018C0E8[0] = a0;
        if (func_00294630(D_00239BA0[*p].handle) == 0)
            func_00294420(D_00239BA0[*p].handle);
        ret = 1;
    } else {
        int kind = e->kind;

        if (kind == 3) {
            ret = 1;
            D_0018C0E8[3] = a0;
        } else if (kind == 2) {
            ret = 1;
            D_0018C0E8[2] = a0;
        } else if (kind == 1) {
            ret = 1;
            D_0018C0E8[1] = a0;
        }
    }
    return ret;
}
