/* near-miss: func_L03_003E18D8 (03_endako, 284 bytes). w2: 288/284 B; all but the order of the byte/float stores before the final call: the t2 byte store to +0x77 sits in the jal delay slot in retail, but here sched hoists one of the two t2 stores, and the 0xFF constant is built twice (v0 and v1) instead of once. */

extern char *func_0029EFD0(int);
extern void func_002A0F48(char *);

char *func_L03_003E18D8(int a0, void *a1, void *a2, void *a3, float f12, float f13, float f14,
                        unsigned char t0, unsigned char t1, unsigned char t2)
{
    char *obj = func_0029EFD0(0xB1B);
    char *st;
    int ff = 0xFF;

    if (obj != 0) {
        qcopy(obj + 0x10, a1);
        *(unsigned char *)(obj + 0x30) = ff;
        *(float *)(obj + 0x2C) = 0.015f;
        *(int *)(obj + 0xB8) = a0;
        *(unsigned short *)(obj + 0x32) = ff;
        obj[0x20] = 0;
        st = *(char **)(obj + 0x68);
        qcopy(st, a2);
        qcopy(st + 0x10, a3);
        *(float *)(st + 0x64) = f14;
        *(int *)(st + 0x70) = 0x10E;
        st[0x75] = t0;
        st[0x76] = t1;
        st[0x77] = t2;
        *(float *)(st + 0x68) = f13;
        *(float *)(st + 0x6C) = f12;
        st[0x78] = t2;
        func_002A0F48(obj);
    }
    return obj;
}
