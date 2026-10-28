/* functional: medium. snd_SendCommandSync written from the retail assembly: same reads, writes and calls in the same order (stage the payload in D_001A70C0, wait for the sound server, send the command over RPC into the D_001A7080 reply, drain, return its second word); the staging copy and waits sit in static helpers. */
extern int D_001A7480 __attribute__((sda));
extern int D_001A74F8 __attribute__((sda));
extern int D_001A74C0 __attribute__((sda));
extern int D_001A74C4 __attribute__((sda));
extern int *D_001A74A0[] __attribute__((sda));
extern char D_001A7040[];
extern int D_001A7080[];
extern unsigned char D_001A70C0[];
extern char D_001A7578[];
extern void func_00132028(void);
extern void func_0011AEA0(int);
extern void func_001322B8(void *, int);
extern int func_0011D810(void *);
extern void func_00115D48(void *);
extern void func_0011D620(void *, int, int, void *, int, void *, int, int, int);
extern int func_00132220(void);
extern void func_00133108(void *);

static void snd_stage_and_pump(int size, unsigned char *payload) {
    int i;
    unsigned char *dst = D_001A70C0;

    for (i = 0; i < size; i++) {
        unsigned char b = payload[i];
        dst[i] = b;
    }
    while (D_001A7480 != 0) {
        func_00132028();
        func_0011AEA0(0);
    }
    func_001322B8(D_001A7080, 1);
    while (func_0011D810(D_001A7040) != 0) {
        if (D_001A74F8 == 0) {
            func_00115D48(D_001A7578);
        }
        func_00132028();
        func_0011AEA0(0);
    }
}

static void snd_drain(void) {
    while (func_00132220() == 0) {
    }
}

int func_00132C48(int cmd, int size, unsigned char *payload) {
    int ret;
    int *entry;

    snd_stage_and_pump(size, payload);
    if (size != 0) {
        func_0011D620(D_001A7040, cmd, 1, D_001A70C0, size, D_001A7080, 0xC, 0, 0);
    } else {
        func_0011D620(D_001A7040, cmd, 1, (void *)0, 0, D_001A7080, 0xC, 0, 0);
    }
    snd_drain();
    ret = D_001A7080[1];
    entry = D_001A74A0[D_001A74C0];
    if (*entry != 0 && D_001A74C4 == 0) {
        func_00133108(entry);
    }
    return ret;
}
