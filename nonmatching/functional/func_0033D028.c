/* functional: high. Written from the assembly; same reads, writes and calls in the same order. The two float constants at D_001ADE58/D_001ADE60 are $gp-relative in retail (-G8 unit), here plain globals; no byte match attempted beyond that (needs a -G8 split of the unit). */
extern void func_0033AE28(char *);
extern void func_0033B018(char *, float, float);
extern void func_00335E38(char *, float, float, float, float);
extern void func_00336B98(char *, int);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_002E4860(void);
extern void func_00132938(int);
extern unsigned int D_00138340;
extern int D_001A7B98;
extern int D_001A7B9C;
extern int D_001A7BA0;
extern float D_001ADE58;
extern float D_001ADE5C;
extern float D_001ADE60;
extern float D_001ADE64;

int func_0033D028(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    float zero = 0.0f;
    int v;

    func_0033AE28(p);
    q = *(float **)(a0 + 0x33C);
    func_0033B018(p, q[0], q[1]);
    q = *(float **)(a0 + 0x33C);
    func_00335E38(a0 + 0x2AC, q[0] + D_001ADE58, q[1] + D_001ADE5C, zero, zero);
    q = *(float **)(a0 + 0x33C);
    func_00335E38(a0 + 0x2F4, q[0] + D_001ADE60, q[1] + D_001ADE64, zero, zero);
    if (a1 & 0x1000) {
        func_002E5E58(3, 0, 0);
        *(int *)(a0 + 0x2A8) = (*(int *)(a0 + 0x2A8) + 2) % 3;
    } else if (a1 & 0x4000) {
        func_002E5E58(3, 0, 0);
        *(int *)(a0 + 0x2A8) = (*(int *)(a0 + 0x2A8) + 1) % 3;
    } else {
        v = D_00138340;
        if (v & 0x8000) {
            int sel = *(int *)(a0 + 0x2A8);
            if (sel == 0) {
                v = D_001A7BA0 - 3;
                D_001A7BA0 = v > -1 ? v : 0;
            } else if (sel == 1) {
                v = D_001A7B9C - 3;
                D_001A7B9C = v > -1 ? v : 0;
            }
        } else if (v & 0x2000) {
            int sel = *(int *)(a0 + 0x2A8);
            if (sel == 0) {
                v = D_001A7BA0 + 3;
                D_001A7BA0 = v < 0x401 ? v : 0x400;
            } else if (sel == 1) {
                v = D_001A7B9C + 3;
                D_001A7B9C = v < 0x401 ? v : 0x400;
            }
        } else if (a1 & 0x40) {
            if (*(int *)(a0 + 0x2A8) == 2) {
                func_002E5E58(4, 0, 0);
                D_001A7B98 = D_001A7B98 == 0;
                func_00132938(D_001A7B98 ^ 1);
            } else {
                func_002E5E58(5, 0, 0);
            }
        }
    }
    func_00336B98(a0 + 0x2F4, D_001A7B9C);
    func_00336B98(a0 + 0x2AC, D_001A7BA0);
    func_002E4860();
    return (a1 >> 6) & 1;
}
