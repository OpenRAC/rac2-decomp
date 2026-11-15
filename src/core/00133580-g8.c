#include "common.h"

extern int D_001A748C __attribute__((sda));
extern int D_001A7498 __attribute__((sda));
extern unsigned int D_001A7100 NOT_SDA;
extern char D_001A713F NOT_SDA;
extern void func_0011B500(void *, void *);
extern int func_00124B88(int);
extern int func_00132028(void);

/* snd_CheckLoadInProgress: poll the shared loader status, pumping when asked
 * to wait. The fallback preserves the caller's sceCdSync mode argument. */
int func_00133580(int arg0) {
    char *end;
    int busy;

    if (D_001A748C == 0)
        return func_00124B88(arg0);

    end = &D_001A713F;
    func_0011B500(&D_001A7100, end);
    busy = D_001A7100 < 1;
    D_001A7498 = busy;
    if (busy == 1)
        return 0;
    if (arg0 == 1)
        return 1;
    while (D_001A7498 == 0) {
        snd_Pump();
        func_0011B500(&D_001A7100, end);
        busy = D_001A7100 < 1;
        D_001A7498 = busy;
    }
    return 0;
}

