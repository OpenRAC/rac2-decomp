#include "common.h"
#include "structs.h"

extern int r1_D_001313E8;

extern void r1_func_00118C90(int);

extern char r1_D_00132590[];

extern int r1_func_0011B4C8();

extern int cd_scmd_check_ready(int);

extern int r1_D_00131440;

extern int sceCdSyncS(int);

extern int r1_D_001313F0;

extern void r1_func_0011A6C8();

extern int r1_D_001313D0;

extern char r1_D_00152FF0[];

extern int r1_func_0011B6B8(void *);

extern char r1_D_00153000[];

extern char r1_D_00132E08[];

/* rac1-decomp src/core/001208E8.c: func_00120E98 */
/*
 * sceCdNcmdDiskReady, sibling of r1_func_00121930 (and of the r1_func_0011CBC8
 * pair): open the service, run one r1_func_0011B4C8 RPC, then release the
 * lock and hand back the reply. The reply is read back through the
 * uncached mirror of the DMA buffer (| 0x20000000), which is why the
 * address is spelled as an integer or.
 *
 * The RPC failure path comes first (release, return 0), then the success
 * path, as retail lays them out. Under 2.9-ee that is the form that keeps
 * the early guard's `return 0` and the failure arm's `return 0` apart
 * (retail keeps two separate zeroings); the success-first spelling that
 * 2.95.3 needed is cross-jumped by 2.9-ee into one tail (SIZE 144/152).
 * The two compilers merge the tails in mirror-image layouts, so the
 * layout alone does not tell them apart; the prebuilt libcdvd.a, which
 * this matches, is 2.9-ee's.
 */
/* Asks the CD drive if the disc is ready and returns the reply. */
int sceCdDiskReady(void) {
    int result;

    if (cd_scmd_check_ready(2) == 0) {
        return 0;
    }
    if (r1_func_0011B4C8(r1_D_00132590, 0xE, 0, 0, 0, &r1_D_00131440, 4, 0, 0) < 0) {
        r1_func_00118C90(r1_D_001313E8);
        return 0;
    }
    result = *(int *)((unsigned int)&r1_D_00131440 | 0x20000000);
    r1_func_00118C90(r1_D_001313E8);
    return result;
}

/* rac1-decomp src/core/001208E8.c: func_00120F30 */
/* sceCdSyncS */
/* Waits for the last CD system command to finish, or only checks if it is still running. */
int sceCdSyncS(int poll_only) {
    if (poll_only == 0) {
        if (r1_D_001313D0 > 0) {
            r1_func_0011A6C8(r1_D_00152FF0);
        }
        while (r1_D_001313F0 != 0 || r1_func_0011B6B8(r1_D_00132590) != 0) {
            cd_sleep_with_alarm(0x3C);
        }
        return 0;
    }
    if (r1_D_001313F0 != 0 || r1_func_0011B6B8(r1_D_00132590) != 0) {
        return 1;
    }
    return 0;
}

/* rac1-decomp src/core/001208E8.c: func_00120FD0 */
/* sceCdSync */
/* Waits for the last CD read command to finish, or only checks if it is still running. */
int sceCdSync(int poll_only) {
    if (poll_only == 0) {
        if (r1_D_001313D0 > 0) {
            r1_func_0011A6C8(r1_D_00153000);
        }
        while (r1_func_0011B6B8(r1_D_00132E08) != 0) {
            cd_sleep_with_alarm(0x3C);
        }
        return 0;
    }
    return r1_func_0011B6B8(r1_D_00132E08);
}
