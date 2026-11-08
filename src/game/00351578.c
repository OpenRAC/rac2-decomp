#include "ps2_hw.h"
/* Kept separate so existing wrappers retain external call bindings. */
typedef struct Timestamp_351578 {
    long pts;
    long dts;
    int pos;
    int len;
} Timestamp_351578;

typedef struct VideoBuffer_351578 {
    unsigned int base;      /* 0x0 */
    unsigned char *tags;    /* 0x4 */
    int count;              /* 0x8 */
    int fC;                 /* 0xC */
    int f10;                /* 0x10 */
    int f14;                /* 0x14 */
    int f18;
    char pad1C[0x24];
    int sema;               /* 0x40 */
    int f44;                /* 0x44 */
    char pad48[8];
    char *tbl;              /* 0x50, entries of 0x18 bytes */
    int ntbl;               /* 0x54 */
    int f58;                /* 0x58 */
    int f5C;                /* 0x5C */
} VideoBuffer_351578;


extern int func_0011AC60(int);
extern int func_0011AC40(int);
static inline int ts_dist(int a, int size) {
    return a % size;
}

/* func_00351578(VideoBuffer_351578 *, Timestamp_351578 *) */
int func_00351578(VideoBuffer_351578 *vb, Timestamp_351578 *ts) {
    unsigned int madr = D4_MADR;
    unsigned int top = IPU_BP;
    int bp = *(unsigned int *)((char *)vb + 0x38) & 0x7F;
    int size = vb->count << 11;
    int found = 0;
    int pos;
    int n;
    int end;
    int j;

    madr -= (((top >> 16) & 3) + ((top >> 8) & 0xF)) << 4;
    func_0011AC60(vb->sema);
    ts->pts = -1;
    ts->dts = -1;
    madr += bp >> 3;
    madr += size;
    pos = (madr - vb->base) % size;
    n = vb->f58;
    end = vb->f5C;
    for (j = 0; j < n && !found; j++) {
        int k = (end - n + vb->ntbl + j) % vb->ntbl;
        if (ts_dist(pos + size - ((Timestamp_351578 *)vb->tbl)[k].pos, size) < ((Timestamp_351578 *)vb->tbl)[k].len) {
            found = 1;
            ts->pts = ((Timestamp_351578 *)vb->tbl)[k].pts;
            ts->dts = ((Timestamp_351578 *)vb->tbl)[k].dts;
            ((Timestamp_351578 *)vb->tbl)[k].pts = -1;
            ((Timestamp_351578 *)vb->tbl)[k].dts = -1;
            vb->f58 -= (vb->f58 < 2) ? vb->f58 : 1;
        }
    }
    func_0011AC40(vb->sema);
    return 1;
}
