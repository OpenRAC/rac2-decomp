#include "ps2_hw.h"
#include "names.h"
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
/* Finds the timestamp that belongs to the data the decoder is reading now and hands it back. */
int func_00351578(VideoBuffer_351578 *buf, Timestamp_351578 *timestamp) {
    unsigned int madr = D4_MADR;
    unsigned int top = IPU_BP;
    int bp = *(unsigned int *)((char *)buf + 0x38) & 0x7F;
    int size = buf->count << 11;
    int found = 0;
    int pos;
    int n;
    int end;
    int i;

    madr -= (((top >> 16) & 3) + ((top >> 8) & 0xF)) << 4;
    WaitSema(buf->sema);
    timestamp->pts = -1;
    timestamp->dts = -1;
    madr += bp >> 3;
    madr += size;
    pos = (madr - buf->base) % size;
    n = buf->f58;
    end = buf->f5C;
    for (i = 0; i < n && !found; i++) {
        int k = (end - n + buf->ntbl + i) % buf->ntbl;
        if (ts_dist(pos + size - ((Timestamp_351578 *)buf->tbl)[k].pos, size) < ((Timestamp_351578 *)buf->tbl)[k].len) {
            found = 1;
            timestamp->pts = ((Timestamp_351578 *)buf->tbl)[k].pts;
            timestamp->dts = ((Timestamp_351578 *)buf->tbl)[k].dts;
            ((Timestamp_351578 *)buf->tbl)[k].pts = -1;
            ((Timestamp_351578 *)buf->tbl)[k].dts = -1;
            buf->f58 -= (buf->f58 < 2) ? buf->f58 : 1;
        }
    }
    SignalSema(buf->sema);
    return 1;
}
