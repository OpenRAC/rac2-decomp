#include "common.h"
#include "structs.h"

extern int func_00124B88(int);

extern int r1_D_001313E8;

extern void r1_func_00118C90(int);

typedef struct {
    char pad[0x24];
    void *serve;
} SifRpcClientData;

extern int r1_func_00120B28(void);

extern int r1_func_00118CC0(int);

extern int r1_func_00118BF0(int, void *);

extern void r1_func_0011AE20(int);

extern int r1_func_0011B2F8(void *, unsigned int, int);

extern void r1_func_0011A6C8();

extern int r1_D_001313DC;

extern int r1_D_001313D0;

extern int r1_D_001313F8;

extern int r1_D_00159850;

extern char r1_D_00159858[];

extern char r1_D_00152FB0[];

extern char r1_D_00152FD8[];

extern char r1_D_00132590[];

extern int r1_D_001363AC;

extern int r1_func_00124780(void);

extern int r1_func_0011AC70(int);

extern void r1_func_0011C820();

extern int r1_D_00136390;

extern int r1_D_00136398;

extern void r1_func_0011AB20(int, void *);

extern int r1_D_00141850;

extern char r1_D_00141858[];

extern int r1_func_00124C28(int);

extern void r1_func_0011AC40(int);

extern void r1_func_0011CF78(int);

extern int r1_D_001363C8;

extern int r1_func_0011D450(void *, unsigned int, int);

extern char r1_D_0013B228[];

extern char r1_D_0013B250[];

extern char r1_D_00137DC8[];

/* rac1-decomp src/core/001208E8.c: func_00121040 */
/* _sceCd_ncmd_prechk (libcdvd.a cdvd000.o): take the command semaphore,
   record the command, bind the 0x80000593 server once and retry until it
   answers. The two wait loops are written out separately, as retail keeps
   both copies. */
int func_00124C98(int arg0) {
    int i;
    volatile int *sem = &r1_D_001363AC;

    r1_func_00124780();
    if (*sem != r1_func_0011AC70(*sem)) {
        if (r1_D_00136390 > 0) {
            r1_func_0011C820(r1_D_0013B228, arg0, r1_D_00136398);
        }
        return 0;
    }
    r1_D_00136398 = arg0;
    r1_func_0011AB20(r1_D_00141850, r1_D_00141858);
    if (r1_func_00124C28(1) != 0) {
        r1_func_0011AC40(*sem);
        return 0;
    }
    r1_func_0011CF78(0);
    if (r1_D_001363C8 >= 0) {
        return 1;
    }
    while (1) {
        if (r1_func_0011D450(r1_D_00137DC8, 0x80000593, 0) < 0) {
            if (r1_D_00136390 > 0) {
                r1_func_0011C820(r1_D_0013B250);
            }
            for (i = 0x100000; i != -1; i--)
                ;
        } else {
            if (((SifRpcClientData *)r1_D_00137DC8)->serve != 0) {
                break;
            }
            for (i = 0x100000; i != -1; i--)
                ;
        }
    }
    r1_D_001363C8 = 0;
    return 1;
}


extern int r1_func_0011AB10(void);

extern void r1_func_0011CEC8(void *, int);

extern int r1_func_0011D620(void *, unsigned int, int, void *, int, void *, int, void *, int);

extern void r1_func_00124818(void);

extern int r1_func_001248F8(void);

extern int r1_D_001363D0;

extern volatile int r1_D_001363A4;

extern volatile int r1_D_001363B4;

extern int r1_D_001363B8;

extern int r1_D_001363BC;

extern int r1_D_001363C0;

extern int r1_D_001363C4;

extern int r1_D_001363CC;

extern volatile int r1_D_001363A0;

extern volatile int r1_D_001363A8;

extern volatile int r1_D_001363AC_v __asm__("r1_D_001363AC");

extern int r1_D_00141A68;

extern int r1_D_00141AC0;

extern char r1_D_00137580[];

extern char r1_D_0013B268[];

extern char r1_D_0013B288[];

/* sceCdInit (libcdvd cdvd000.o): reset the RPC bind states, bind the
   0x80000592 init server (retrying until it answers), send init_mode and
   read the IOP reply. The store to 63B4 is volatile and the store of the
   thread id plain: with the copy of GetThreadId's result folded into its
   store, sched1 leaves retail's register allocation in the init block.
   Making any one other init store volatile instead (e.g. 63C8) gives the
   same bytes. */
int func_00124E08(int init_mode) {
    int ret;
    int r;
    int i;
    int stat;
    int a;
    int b;
    int owner;
    char *rbuf;

    if (r1_func_00124C28(1) != 0) {
        return 0;
    }
    r1_func_0011CF78(0);
    owner = r1_func_0011AB10();
    r1_D_001363A4 = 1;
    r1_D_00141850 = owner;
    r1_D_001363C0 = -1;
    r1_D_001363B8 = -1;
    r1_D_001363C8 = -1;
    r1_D_001363C4 = -1;
    r1_D_001363CC = -1;
    r1_D_001363BC = -1;
    r1_D_001363B4 = 0;
    r1_D_001363D0++;
    while (1) {
        r = r1_func_0011D450(&r1_D_00141A68, 0x80000592, 0);
        if (r < 0) {
            if (r1_D_00136390 > 0) {
                r1_func_0011C820(r1_D_0013B268, r, r1_D_001363D0);
            }
            for (i = 0x100000; i != -1; i--) {
            }
            continue;
        }
        if (((SifRpcClientData *)&r1_D_00141A68)->serve != 0) {
            r1_D_00141AC0 = init_mode;
            r1_D_001363CC = 0;
            r1_func_0011CEC8(&r1_D_00141AC0, 4);
            rbuf = r1_D_00137580;
            if (r1_func_0011D620(&r1_D_00141A68, 0, 0, &r1_D_00141AC0, 4, rbuf, 0x10, 0, 0) < 0) {
                r1_D_001363A4 = 0;
                return 0;
            }
            break;
        }
        for (i = 0x100000; i != -1; i--) {
        }
    }
    a = *(int *)((unsigned int)(rbuf + 4) | 0x20000000);
    b = *(int *)((unsigned int)(rbuf + 8) | 0x20000000);
    stat = *(int *)((unsigned int)(rbuf + 0xC) | 0x20000000);
    ret = 1;
    if (stat == 0xFF) {
    } else if (stat == 0xFE) {
        r1_D_00136390 = ret;
    } else {
        if (a / 256 < 2 || b / 256 < 2) {
            ret = 2;
        }
    }
    r1_D_001363A4 = 0;
    switch (init_mode) {
    case 5:
        if (r1_D_00136390 > 0) {
            r1_func_0011C820(r1_D_0013B288);
        }
        r1_func_00124818();
        r1_D_001363A8 = -1;
        r1_D_001363AC_v = -1;
        r1_D_001363A0 = -1;
        break;
    case 0:
    case 1:
    default:
        r1_func_00124780();
        r1_func_001248F8();
        break;
    }
    return ret;
}











struct sceSifRpcData_r001250E8 {
    void *paddr; /* 0x0: packet in flight; released by _request_end */
    u32 pid; /* 0x4 */
    s32 tid; /* 0x8: semaphore signalled by _request_end when >= 0 */
    u32 mode; /* 0xC */
};

struct sceSifClientData_r001250E8 {
    struct sceSifRpcData_r001250E8 rpcd; /* 0x0 */
    u32 command; /* 0x10 */
    void *buff; /* 0x14 */
    void *cbuff; /* 0x18 */
    void (*func)(void *); /* 0x1C: end function, called with para when the call completes */
    void *para; /* 0x20 */
    void *serve; /* 0x24: server bound by sceSifBindRpc; 0 until bound */
};

extern s32 r1_D_001313D0_21490[] __asm__("r1_D_001313D0");

extern volatile s32 r1_D_001313EC_21490[] __asm__("r1_D_001313EC");

extern s32 r1_D_00131404[];

extern struct sceSifClientData_r001250E8 r1_D_00159A90;

extern s32 r1_D_00159AD0[];

extern u8 r1_D_001325C0_21490[] __asm__("r1_D_001325C0");

extern u8 r1_D_00153080[];

extern u8 r1_D_00153090[];

extern u8 r1_D_001530B0[];

extern s32 r1_func_00118CC0();


extern void r1_func_00120B28_21490() __asm__("r1_func_00120B28");

extern s32 r1_func_00120FD0();

extern s32 r1_func_0011B2F8();

extern void r1_func_0011AE20();





extern int r1_func_00120FD0();

/* rac1-decomp src/core/001208E8.c: func_00121490 */
/* libcdvd disk-ready query (the sceCdDiskReady pattern): take the S-command semaphore, bind the 0x8000059A server once, send mode and return the server's status word. Mode 8 reports -1 on failure, every other mode 6.
   Adapted from Lombyte (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/textbin/fun_00121190.c, FUN_00121190. */
s32 func_001250E8(s32 mode) {
    s32 response;
    s32 spin;

    if (r1_D_001313D0_21490[0] > 0) {
        r1_func_0011A6C8(r1_D_00153080);
    }
    r1_func_00120B28_21490();
    if (r1_D_001313EC_21490[0] != r1_func_00118CC0(r1_D_001313EC_21490[0])) {
        return 6;
    }
    if (r1_func_00120FD0(1) != 0) {
        r1_func_00118C90(r1_D_001313EC_21490[0]);
        if (mode == 8) {
            return -1;
        }
        return 6;
    }
    r1_func_0011AE20(0);
    if (r1_D_00131404[0] < 0) {
        for (;;) {
            if (r1_func_0011B2F8(&r1_D_00159A90, 0x8000059A, 0) < 0) {
                if (r1_D_001313D0_21490[0] > 0) {
                    r1_func_0011A6C8(r1_D_00153090);
                }
                for (spin = 0x100000; spin != -1; spin--) {
                }
                continue;
            }
            if (r1_D_00159A90.serve != 0) {
                r1_D_00131404[0] = 0;
                break;
            }
            for (spin = 0x100000; spin != -1; spin--) {
            }
        }
    }
    r1_D_00159AD0[0] = mode;
    r1_func_0011AD70(r1_D_00159AD0, 4);
    if (r1_func_0011B4C8(&r1_D_00159A90, 0, 0, r1_D_00159AD0, 4, r1_D_001325C0_21490, 4, 0, 0) < 0) {
        r1_func_00118C90(r1_D_001313EC_21490[0]);
        if (mode == 8) {
            return -1;
        }
        return 6;
    }
    if (r1_D_001313D0_21490[0] > 0) {
        r1_func_0011A6C8(r1_D_001530B0);
    }
    response = *(s32 *)((u32)r1_D_001325C0_21490 | 0x20000000);
    r1_func_00118C90(r1_D_001313EC_21490[0]);
    return response;
}

extern int r1_func_00121040();

extern void r1_func_0011AD70();

extern void r1_func_0011AD70(void *, int);

extern int r1_D_00132A00;

extern int r1_func_00121040(int);

extern int r1_D_001313EC;

extern int r1_D_001313EC;


extern void r1_func_00118C90();

extern int r1_func_0011B4C8();

extern s32 r1_func_0011B4C8();

extern int r1_D_001325C0;

extern char r1_D_00132E08[];

/* rac1-decomp src/core/001208E8.c: func_00121688 */
/* sceCdMmode */
int func_001252E0(int arg0) {
    int *p = &r1_D_00132A00;
    int r;

    if (r1_func_00121040(0x22) == 0) {
        return 0;
    }
    r1_D_00132A00 = arg0;
    r1_func_0011AD70(p, 4);
    if (r1_func_0011B4C8(r1_D_00132E08, 0x22, 0, p, 4, &r1_D_001325C0, 4, 0, 0) < 0) {
        r1_func_00118C90(r1_D_001313EC);
        return 0;
    }
    r = *(int *)((unsigned int)&r1_D_001325C0 | 0x20000000);
    r1_func_00118C90(r1_D_001313EC);
    return r;
}

