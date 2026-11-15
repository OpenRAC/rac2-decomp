#include "common.h"
#include "structs.h"
#include <stdarg.h>

extern int r1_D_0012FD9C;

extern int r1_D_0012FD9C NOT_SDA;

extern s32 r1_func_00118C90(s32);

extern int r1_func_001151B4();

extern char r1_D_0012FCEC[];

extern char r1_D_001580A8[];

extern int r1_D_0012FDA8;

extern s32 iop_file_buffers_equal(void);

extern void r1_func_001153FC(void *, int, int);

extern int r1_D_0012FD94;

/* rac1-decomp src/core/00119D88.c: func_0011BC70 */
/* A tail jump with the argument load in its delay slot (`lui / j /
   lw`), as 2.9-ee, which builds this SDK object, emits it. */
/* Releases the file system lock. */
void iop_file_unlock(void) {
    r1_func_00118C90(r1_D_0012FD9C);
}

ASM_FUNC("asm/core", func_0011DDD8);

extern int r1_func_0011D960(void);
extern void r1_func_0011D9A8(void);
extern int r1_func_0011D960(void);           /* DI */
extern void r1_func_0011D9A8(void);          /* EI */
extern int r1_func_0011D960(void);
extern void r1_func_0011D9A8(void);
extern int r1_func_00118CB0(int);      /* WaitSema */
typedef signed int s32_1B4C8;
extern s32_1B4C8 r1_func_00118CB0();
extern int r1_D_0012FDA0;
extern char r1_D_00157E80[];
extern s32 r1_D_0012FD98[];
extern u8 r1_D_00157600[];
struct RpcCb { void (*cb)(void *); void *data; };
extern struct RpcCb r1_D_00158100;
extern char r1_D_001580C0[];
extern char r1_D_00158080[];
extern char r1_D_001575C0[];
extern char *r1_D_00156940[];
extern char r1_D_001580A8[];
extern int r1_D_0012FD94;
extern void r1_func_0011B868();
extern void r1_func_0011BC80();
struct W4 { char b[4]; };
extern s32 r1_func_00118C90(s32);
extern void r1_func_0011AA38(int arg0, int arg1, int arg2);
extern void r1_func_0011AE20(int);
extern int r1_func_0011B2F8(void *, int, int);
extern s32 r1_func_0011B4C8(void *, s32, s32, void *, s32, void *, s32, void *, void *);
extern void r1_func_0011B710(void);

/* rac1-decomp src/core/00119D88.c: func_0011DE08 */
/* Starts up the file system link to the IOP: waits for the file server, clears the file table and sets up the reply buffers. */
s32 iop_file_init_client(void) {
    s32 result, i;
    char *slot;
    struct W4 versionWord;
    s32 *q;

    struct RpcCb *rq = &r1_D_00158100;
    r1_func_0011AE20(0);
    r1_D_00158100.cb = 0;
    rq->data = 0;
    result = r1_func_0011D960();
    r1_func_0011AA38(0x80000011, (int)r1_func_0011B868, (int)r1_D_001580C0);
    r1_func_0011AA38(0x80000013, (int)r1_func_0011BC80, (int)rq);
    if (result != 0) {
        r1_func_0011D9A8();
    }
    for (;;) {
        result = r1_func_0011B2F8(r1_D_00158080, 0x80000001, 0);
        if (result < 0) {
            return -1;
        }
        if (*(s32 *)(r1_D_00158080 + 0x24) != 0) {
            break;
        }
        for (i = 0x100000; i != -1; i--) {
        }
    }
    r1_func_0011B710();
    r1_func_00118CB0(r1_D_0012FDA0);
    for (slot = r1_D_00157E80; slot < r1_D_00157E80 + 0x200; slot += 0x10) {
        *(s32 *)(slot + 4) = 0;
    }
    r1_func_00118C90(r1_D_0012FDA0);
    r1_D_00156940[0] = r1_D_00157600;
    r1_D_00156940[1] = r1_D_00157600 + 0x440;
    result = r1_func_0011B4C8(r1_D_00158080, 0xFF, 0, r1_D_00156940, 8, r1_D_001575C0, 8, 0, 0);
    if (result < 0) {
        return (s32)0xFFFEFFFF;
    }
    *(struct W4 *)r1_D_001580A8 = *(struct W4 *)((u32)r1_D_001575C0 | 0x20000000);
    versionWord = *(struct W4 *)((u32)(r1_D_001575C0 + 4) | 0x20000000);
    r1_D_0012FD98[0] = (*(s32 *)&versionWord == 2);
    r1_D_0012FD94 = 1;
    return 0;
}

/* rac1-decomp src/core/00119D88.c: func_0011BEB8 */
/* Three-way compare-and-confirm: the slot r1_D_001580A8 has to agree with
   the scratch buffer r1_D_0012FCEC, then with the handle r1_D_0012FDA8, and
   finally the two of those with each other. Only the last comparison's
   result is reported, as a 0/1.

   The two globals are bound to locals, buffer first, purely to fix the
   order the compiler materialises their %hi halves in: used directly,
   the slot's lui comes first and the function is 4/140. Declaration
   order of the locals decides it. */
/* Compares three small buffers to see whether they all agree. Returns 1 only if they do. */
int iop_file_buffers_equal(void) {
    char *buf = r1_D_0012FCEC;
    char *slot = r1_D_001580A8;
    int result = 0;

    if (r1_func_001151B4(slot, buf, 4) != 0 &&
        r1_func_001151B4(slot, r1_D_0012FDA8, 4) != 0) {
        result = r1_func_001151B4(buf, r1_D_0012FDA8, 4) != 0;
    }
    return result;
}

/* rac1-decomp src/core/00119D88.c: func_0011BF48 */
/* Marks the file system as not ready and clears its saved buffer. */
int iop_file_reset_state(void) {
    r1_D_0012FD94 = 0;
    r1_func_001153FC(r1_D_001580A8, 0, 0x4);
    return 0;
}
