/* 6 November 2026: exact 28/28 in USA v1.01, PAL and USA v2.00 as below (from #425, compiled
 * as a -g8.c unit), but only with the hardcoded scratchpad address 0x70002000, which matched C
 * may not contain. Naming it as a symbol (extern char D_70002000[]) swaps $s6/$s7 from the
 * prologue on, 0/28. Reopen with a symbol form that keeps retail's allocation.
 */
#include "common.h"

/* The sky's two piece renderers, called by func_002E3940: func_002E3998 draws textured pieces,
   func_002E3BD8 Gouraud-shaded ones. Each visible piece is copied by toSPR DMA into one of two
   scratchpad buffers while the previous one is transformed and drawn from the other. They read
   $gp small data (the buffer pair and its toggle), so this file is built with -G8. */

typedef struct {
    u8 pad[0x20];
    int data;           /* main-memory address of the piece's data, uploaded by DMA */
    s16 vertex_count;
    s16 face_count;
    s16 vertices;       /* byte offsets into the uploaded copy */
    s16 face_data;      /* texture ST (textured) or vertex colours (Gouraud) */
    s16 faces;
    s16 size;           /* upload size in bytes, a whole number of quadwords */
} SkyPiece;

typedef struct {
    int count;
} Sky;

#define PIECE(sky, k) ((SkyPiece *)((char *)(sky) + ((k) << 5)))

#define SKY_VERTEX_RECORDS 0x70002000   /* scratchpad: the transformed vertex records */

extern unsigned char *D_001B22A8;           /* the DMA packet cursor */
extern char D_00139300[];
extern char D_00139370[];
extern int D_001ABDD8[2] __attribute__((sda));  /* the two scratchpad buffers */
extern int D_001ABDE0 __attribute__((sda));     /* which buffer receives the next upload */
extern int D_001A72E0;

extern void func_002E4388(void *, int, void *);
extern int func_002E3E54(int, int, int);
extern void func_002E3FA0(int, int, int, int);
extern void func_002E40C8(int, int, int, int);
extern void func_0029CF58(int, int, int);
extern void func_0029CF78(void);
extern void func_002FC560(int, long);

void func_002E3998(Sky *sky)
{
    int count = sky->count;
    u8 visible[count];
    int i;

    if (count == 0)
        return;
    func_002E4388((char *)sky + 0x10, count, visible);
    *(int *)(D_001B22A8 + 0) = 0x30000007;
    *(int *)(D_001B22A8 + 4) = (int)D_00139370;
    *(int *)(D_001B22A8 + 8) = 0;
    *(int *)(D_001B22A8 + 0xC) = 0x50000007;
    D_001B22A8 = D_001B22A8 + 16;
    D_001ABDE0 = 1 - D_001ABDE0;
    if (visible[0] == 1)
        func_0029CF58(PIECE(sky, 0)->data, PIECE(sky, 0)->size >> 4, D_001ABDD8[D_001ABDE0]);
    for (i = 0; i < sky->count; i++) {
        if (visible[i] == 1)
            func_0029CF78();
        D_001ABDE0 = 1 - D_001ABDE0;
        if (i + 1 < sky->count && visible[i + 1] == 1)
            func_0029CF58(PIECE(sky, i + 1)->data, PIECE(sky, i + 1)->size >> 4,
                          D_001ABDD8[D_001ABDE0]);
        if (visible[i] == 1) {
            int base = D_001ABDD8[1 - D_001ABDE0];
            int faces, st, vertices, face_list, st_list;

            faces = PIECE(sky, i)->faces;
            vertices = PIECE(sky, i)->vertices;
            st = PIECE(sky, i)->face_data;
            face_list = base + faces;
            st_list = base + st;
            if (func_002E3E54(base + vertices, SKY_VERTEX_RECORDS, PIECE(sky, i)->vertex_count) == 0)
                func_002E40C8(PIECE(sky, i)->face_count, face_list, st_list, SKY_VERTEX_RECORDS);
        }
    }
}
