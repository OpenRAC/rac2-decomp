/* functional: high (fcheck covers 2 calls only). From the near miss (one redundant instruction off retail): same reads, writes and calls in the same order; options toggled at 0x1A7BA4/A8/B1 and mode mod 3 at 0x1A7BAC. */
typedef unsigned char u8;
typedef int s32;

extern void func_0033AE28(char *);
extern void func_0033B018(char *, float, float);
extern void func_002E5E58(int, int, int);
extern void func_0027AB40(void);

int func_0033C590(u8 *a0, s32 a1)
{
    u8 *p = a0 + 8;
    unsigned int *sfx = (unsigned int *)0x1A7BA4;
    unsigned int *music = (unsigned int *)0x1A7BA8;
    int *mode = (int *)0x1A7BAC;
    unsigned char *paused = (unsigned char *)0x1A7BB1;
    float *q;
    int v;

    func_0033AE28(p);
    q = *(float **)(a0 + 0x2AC);
    func_0033B018(p, q[0], q[1]);
    if (a1 & 0x1000) {
        func_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 0x2A8);
        *(int *)(a0 + 0x2A8) = (v + 3) % 4;
    } else if (a1 & 0x4000) {
        func_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 0x2A8);
        *(int *)(a0 + 0x2A8) = (v + 1) % 4;
    } else if (a1 & 0x40) {
        func_002E5E58(4, 0, 0);
        switch (*(int *)(a0 + 0x2A8)) {
        case 0:
            *sfx = *sfx < 1;
            break;
        case 1:
            *music = *music < 1;
            break;
        case 2:
            *mode = (*mode + 1) % 3;
            break;
        case 3:
            *paused = *paused < 1;
            func_0027AB40();
            break;
        }
    }
    return (a1 >> 6) & 1;
}
