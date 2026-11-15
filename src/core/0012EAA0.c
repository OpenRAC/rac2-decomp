#include "common.h"
#include "structs.h"

extern long r1_func_0012AC80(int arg0, int arg1);

typedef struct {
    long key;
    long extra;
    int  cb;
    int  data;
} StrCbEnt;

 /* 0x18 */

typedef struct { char pad[8]; long extra; } Tbl16;

extern Tbl16 r1_D_00132FD8[];

extern int r1_func_0012AAA8(void *, int);

extern int r1_func_0012AB60(void *arg0, int arg1);

extern void r1_func_0012ABB0(void *arg0);

extern int mpeg_skip_system_header();

struct TypeEntry_12AC80 {
    u64 id;
    u64 type;
};
extern struct TypeEntry_12AC80 r1_D_00132FD8_12AC80[] __asm__("r1_D_00132FD8");

/* rac1-decomp src/core/0012AC80.c: func_0012EAA0 */
/* _type2id (libmpeg): for a type below 10, the 64-bit stream key
   r1_D_00132FD8[type].id with value shifted into the field its mask selects
   (0, 24 or 32 bits up); 0 for any other type.
   Adapted from Lombyte's project (GPL-3.0): src/sdk/library/type2id.c, _type2id. */
long mpeg_make_stream_id(int id, int value) {
    u64 result = 0;
    s32 shift = 0;

    if ((u32)id < 10) {
        switch (r1_D_00132FD8_12AC80[id].type) {
        case 0xFFFFFFFFFF:
            shift = 0;
            break;
        case 0xFFFF000000:
            shift = 24;
            break;
        case 0xFF00000000:
            shift = 32;
            break;
        }
        result = r1_D_00132FD8_12AC80[id].id | ((u64)value << shift);
    }
    return result;
}

typedef struct {
    u8 pad0[0x18];
    u64 pos;
    u8 pad20[0x10];
} SysBit;
typedef struct {
    s32 v[6];
} PackHdr;
typedef struct {
    u64 id;
    s32 len;
    s32 scrambling;
    s64 pts;
    s64 dts;
    s32 data;
    s32 datalen;
    s32 header;
    s32 pad2C;
} PesHdr;
typedef struct {
    PackHdr pack;
    PesHdr pes;
} PssHdr;
typedef struct {
    s32 type;
    u8 *header;
    u8 *data;
    u32 len;
    s64 pts;
    s64 dts;
} sceMpegCbDataStr;
typedef s32 (*sceMpegCallback)(void *mp, sceMpegCbDataStr *cbstr, void *data);
typedef struct {
    u64 id;
    u64 mask;
    sceMpegCallback func;
    void *data;
} StreamCb;
typedef struct {
    u8 pad0[0x44];
    StreamCb *tbl;
    s32 n;
} MpegSys;
typedef struct {
    u8 pad0[0x40];
    MpegSys *sys;
} sceMpeg;
extern void r1_func_0012AA70(SysBit *bs, u8 *start, u8 *bufstart, s32 bufsize);
extern s32 r1_func_0012AAA8_2AD10(SysBit *bs, s32 n) __asm__("r1_func_0012AAA8");
extern u8 *r1_func_0012AC50(SysBit *bs, s32 pos);
extern s32 r1_func_0012B100_2AD10(SysBit *bs, PackHdr *pack) __asm__("r1_func_0012B100");
extern s32 r1_func_0012B2C0_2AD10(MpegSys *sys, SysBit *bs, PesHdr *pes) __asm__("r1_func_0012B2C0");

/* rac1-decomp src/core/0012AC80.c: func_0012EB28 */
/* Adapted from Lombyte's project (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/sdk/dma/sce_mpeg_demux_pss_ring.c, sceMpegDemuxPssRing. */
/* Walks through a PSS movie stream in a ring buffer and calls the registered handler for each packet. Returns how many bytes it used. */
int sceMpegDemuxPssRing(sceMpeg *mp, u8 *start, int size, u8 *bufstart, int bufsize) {
    SysBit bs;
    PssHdr hdr;
    SysBit *b;
    PssHdr *h;
    sceMpegCbDataStr cb;
    sceMpegCallback cbfunc = 0;
    void *cbdata = 0;
    StreamCb *tbl;
    int ret;
    int i;
    int cont;
    MpegSys *sys;
    int headerpos;

    cont = 1;
    h = &hdr;
    sys = mp->sys;
    tbl = sys->tbl;
    r1_func_0012AA70(&bs, start, bufstart, bufsize);
    ret = 0;
    i = 0;
    b = &bs;
    if (i < sys->n) {
        do {
            if (tbl[i].id == 0xBDFF000000) {
                cbfunc = tbl[i].func;
                cbdata = tbl[i].data;
            }
            if (cbfunc != 0) {
                break;
            }
            i++;
        } while (i < sys->n);
    }
    for (;;) {
        if (r1_func_0012AAA8_2AD10(b, 32) == 0x1BA) {
            r1_func_0012B100_2AD10(b, &h->pack);
        }
        while (r1_func_0012AAA8_2AD10(b, 24) == 1 && r1_func_0012AAA8_2AD10(b, 32) != 0x1BA &&
               r1_func_0012AAA8_2AD10(b, 32) != 0x1B9 && b->pos < size * 8 && cont) {
            r1_func_0012B2C0_2AD10(sys, b, &h->pes);
            if (b->pos > size * 8) {
                continue;
            }
            for (i = 0; i < sys->n; i++) {
                if (tbl[i].id == (h->pes.id & tbl[i].mask)) {
                    headerpos = h->pes.header;
                    cb.type = 6;
                    cb.header = r1_func_0012AC50(b, headerpos);
                    cb.data = r1_func_0012AC50(b, h->pes.data);
                    cb.len = h->pes.datalen;
                    cb.pts = h->pes.pts;
                    cb.dts = h->pes.dts;
                    cont = tbl[i].func(mp, &cb, tbl[i].data);
                    break;
                }
            }
            if (i == sys->n && cbfunc != 0) {
                headerpos = h->pes.header;
                cb.type = 6;
                cb.header = r1_func_0012AC50(b, headerpos);
                cb.data = r1_func_0012AC50(b, h->pes.data);
                cb.len = h->pes.datalen;
                cb.pts = h->pes.pts;
                cb.dts = h->pes.dts;
                cont = cbfunc(mp, &cb, cbdata);
            }
            if (cont) {
                ret = b->pos >> 3;
            }
        }
        if (b->pos > size * 8 || r1_func_0012AAA8_2AD10(b, 32) != 0x1BA) {
            break;
        }
    }
    return ret;
}

/* rac1-decomp src/core/0012AC80.c: func_0012B008 */
/*
 * sceMpegAddStrCallback (libmpeg.a:pack.o): key = r1_func_0012AC80(arg1,
 * arg2) (a 64-bit stream/type key); linear-search the object's callback
 * table (handlers[7] reused as {table pointer, count} -- raw offsets,
 * not the Handler struct, per this file's warning about that array
 * overlapping) for a matching key, remembering its old callback (0 if
 * none found). Whether found or not (index lands on the match, or one
 * past the end), if there's room (< 0x40 entries), overwrite the slot
 * with the new key/data/callback and the type's extra 8 bytes from
 * r1_D_00132FD8[arg1], and bump the stored count unconditionally. Returns
 * the previous callback.
 */
/* Registers a handler for one kind of movie stream and returns the previous handler. */
int sceMpegAddStrCallback(void *mpeg, int streamType, int streamIndex, int callback, int userData) {
    int old = 0;
    char *sys = *(char **)((char *)mpeg + 0x40);
    StrCbEnt *handlers = *(StrCbEnt **)(sys + 0x44);
    long key = r1_func_0012AC80(streamType, streamIndex);
    int handlerCount = *(int *)(sys + 0x48);
    int i;

    for (i = 0; i < handlerCount; i++) {
        if (key == handlers[i].key) {
            old = handlers[i].cb;
            break;
        }
    }
    if (i < 0x40) {
        *(int *)(sys + 0x48) = handlerCount + 1;
        handlers[i].key = key;
        handlers[i].data = userData;
        handlers[i].cb = callback;
        handlers[i].extra = r1_D_00132FD8[streamType].extra;
    }
    return old;
}

/* rac1-decomp src/core/0012AC80.c: func_0012B100 */
/*
 * _pack_header (libmpeg.a:pack.o): ISO/IEC 11172-1 2.4.3.3 pack_header().
 * r1_func_0012AB60 is nextBit ("get n bits"), r1_func_0012ABB0 a marker-bit
 * skip, r1_func_0012AAA8 a 32-bit peek (nextStartCode-style). Reads the pack
 * start code's fixed fields (34 then 3, marker, 15, marker, 15, marker,
 * 9, marker), discarding the SCR/mux_rate pieces except for three: the
 * low bit of the first 3-bit group goes to +0x8, and the three groups
 * combine into +0x4 as (first<<30)|(second<<15)|third. The last field
 * read (3 bits) is pack_stuffing_length: that many stuffing bytes are
 * then skipped. Peeks the next 32 bits; a system_header_start_code
 * (0x1BB) sets +0xC and hands off into func_0012F070 (system_header
 * parsing -- called prototype-less here since retail's call site passes
 * it a second, unused argument, the same K&R situation as r1_func_00129F40
 * elsewhere in this file), otherwise clears +0xC. Always returns 1.
 */
/* Reads a movie stream pack header and stores the timing values. Returns 1. */
int mpeg_read_pack_header(void *stream, void *header) {
    char *hdr = (char *)header;
    unsigned int timeHigh, timeMid, timeLow, stuffing;
    unsigned int i;

    r1_func_0012AB60(stream, 0x22);
    timeHigh = r1_func_0012AB60(stream, 3);
    r1_func_0012ABB0(stream);
    timeMid = r1_func_0012AB60(stream, 0xF);
    r1_func_0012ABB0(stream);
    timeLow = r1_func_0012AB60(stream, 0xF);
    r1_func_0012ABB0(stream);
    *(int *)(hdr + 0x0) = r1_func_0012AB60(stream, 9);
    r1_func_0012AB60(stream, 0x1E);
    stuffing = r1_func_0012AB60(stream, 3);

    *(unsigned int *)(hdr + 0x8) = (timeHigh >> 2) & 1;
    *(unsigned int *)(hdr + 0x4) = (timeHigh << 30) | (timeMid << 15) | timeLow;

    for (i = 0; i < stuffing; i++) {
        r1_func_0012AB60(stream, 8);
    }

    if (r1_func_0012AAA8(stream, 0x20) == 0x1BB) {
        *(int *)(hdr + 0xC) = 1;
        mpeg_skip_system_header(stream, hdr);
    } else {
        *(int *)(hdr + 0xC) = 0;
    }
    return 1;
}
