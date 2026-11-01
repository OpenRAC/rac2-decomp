/* functional: medium. Written from the assembly, with func_002A0A28 (the catalogue's second half of this routine, reached only by a jump from here): plain floats in place of VU0 macro code; a level's own moby table and bucket arrays resolve by name. */
#include "common.h"

extern float D_001B5340[4];         /* the eye */
extern char *D_001B1B5C;            /* the moby table: 0x100 bytes each */
extern int D_001B1B78;              /* grid chunks */
extern short *D_001EE5A0[];         /* a chunk's moby list, ended by its negative entry */
extern void *D_001EE960[];          /* the chain of mobys with flag 0x1000, ended by 0 */

#define SCRATCH ((char *)0x70000000)
#define BUCKETS 0
#define ORDER 0x800
#define CHUNKS 0xD00

static int negative_002A08A0(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i < 0;
}

static short *chain_002A08A0(short *order, char *m, int index, int bucket, int flags)
{
    char *b = SCRATCH + BUCKETS + bucket * 8;
    char *tail = *(char **)(b + 4);

    *order = (short)index;
    if (flags & 0x1000) {
        order++;
    }
    *(char **)(b + 4) = m;
    if (tail == 0) {
        *(char **)b = m;
    } else {
        *(char **)(tail + 40) = m;
    }
    return order;
}

/* BuildActiveMobyChain: walks the moby table up to the end marker (state -1). A moby in a grid
   chunk (byte 0x21 >= 0) marks its chunk if it is near enough the eye (byte 0x30 is its range, 255
   always, byte 0x31 > 0 always); a moby in none goes straight into the bucket of its class (byte
   0x22). The marked chunks' lists go into the buckets too. Returns the buckets' mobys chained
   through +40, the flagged ones listed at D_001EE960. */
void *func_002A08A0(void)
{
    short *order = (short *)(SCRATCH + ORDER), *list;
    char *base = D_001B1B5C, *m = base - 256, *b;
    unsigned char *chunk;
    float *eye = D_001B5340;
    void **out;
    char *head, *tail;
    int index = -1, i, n, entry;

    for (i = 0; i < 1920; i += 16) {
        ((long *)(SCRATCH + i))[0] = 0;
        ((long *)(SCRATCH + i))[1] = 0;
    }
    for (i = 0; i < 1024; i += 16) {
        ((long *)(SCRATCH + ORDER + i))[0] = 0;
        ((long *)(SCRATCH + ORDER + i))[1] = 0;
    }
    for (i = 0; i < 256; i += 16) {
        ((long *)(SCRATCH + CHUNKS + i))[0] = 0;
        ((long *)(SCRATCH + CHUNKS + i))[1] = 0;
    }

    for (;;) {
        signed char state = *(signed char *)(m + 288);
        int flags, range, near, group;

        m += 256;
        index++;
        if (state < 0) {
            if (state != -1) {
                continue;
            }
            break;
        }
        flags = *(unsigned short *)(m + 52);
        range = *(unsigned char *)(m + 48);
        near = *(unsigned char *)(m + 49);
        if (flags & 2) {
            continue;
        }
        if (near == 0 && range != 255) {
            float dx = ((float *)(m + 16))[0] - eye[0];
            float dy = ((float *)(m + 16))[1] - eye[1];
            float dz = ((float *)(m + 16))[2] - eye[2];
            float r = (float)range;
            float left = r * r - dx * dx;
            left = left - dy * dy;
            left = left - dz * dz;
            if (negative_002A08A0(left)) {
                continue;
            }
        }
        group = *(signed char *)(m + 33);
        *(unsigned char *)(SCRATCH + CHUNKS + group) = 1;
        if (group >= 0) {
            continue;
        }
        order = chain_002A08A0(order, m, index, *(unsigned char *)(m + 34), flags);
    }

    chunk = (unsigned char *)(SCRATCH + CHUNKS);
    n = D_001B1B78;
    for (i = 0; i < n; i++) {
        if (chunk[i] == 0) {
            continue;
        }
        list = D_001EE5A0[i];
        do {
            entry = *list++;
            {
                int id = entry & 0x7FFF;
                char *o = base + (id << 8);
                int flags = *(unsigned short *)(o + 52);

                *order = (short)id;
                if (*(signed char *)(o + 32) >= 0 && !(flags & 2)) {
                    order = chain_002A08A0(order, o, id, *(unsigned char *)(o + 34), flags);
                }
            }
        } while (entry >= 0);
    }

    out = D_001EE960;
    for (list = (short *)(SCRATCH + ORDER); list != order; list++) {
        *out++ = base + (*(unsigned short *)list << 8);
    }
    *out = 0;

    head = 0;
    tail = 0;
    for (b = SCRATCH + BUCKETS; b != SCRATCH + BUCKETS + 1920; b += 8) {
        char *first = *(char **)b, *last;
        if (first == 0) {
            continue;
        }
        last = *(char **)(b + 4);
        if (head == 0) {
            head = first;
        } else {
            *(char **)(tail + 40) = first;
        }
        tail = last;
        *(char **)(last + 40) = 0;
    }
    return head;
}
