#include "common.h"

/* func_PAL_L03_003E6CA8, the PAL copy of func_L03_003E26C8: the same C, where the starting timer
   is a word scaled to 50 Hz and set last, with the length cleared first. The function reads the
   starting timer through $gp, and its float tests branch to the label on the mtc1 hazard nop:
   a -G8 unit of its own with -frac2-hazard-labels. */

typedef struct {
    f32 x, y, z, w;
} PuzzleNode;

/* The path record at +0x68 of the puzzle object (the fields func_L03_003E21B0 and
   func_L03_003E2EC8 use from +0x50 on). */
typedef struct {
    u8 order[16];   /* the nodes walked, by path length */
    u8 visited[16];
    u8 path[16];    /* the generated path (func_L03_003E2968) */
    u8 facing[16];  /* per path length, the neighbour turned to the front (func_L03_003E3018) */
    u8 choices[16]; /* the neighbours that can be taken next, 255-terminated */
    s16 current;
    s16 next;
    u8 pad54[8];
    s16 last;
    s16 length;
    s16 maximumLength;
    s16 cursor;
    s16 depth;
    s16 pending;
    s16 timer;
    s16 active;
    s16 sound;
} PuzzlePath;

extern PuzzleNode D_L03_0029BBF0[14];
extern int D_0024A7B0[14][6];
extern int D_L03_001B0B5C __attribute__((sda));
extern f32 D_L03_001B36B0[4] __attribute__((sda));
extern void func_00282F20(void *, void *, f32);
extern f32 func_00282DB0(void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_002A91F0(void *, void *);
extern void func_001163A0(unsigned int);
extern void func_L03_003E2968(u8 *);
extern void func_L03_003E2C08(u8 *);
extern void func_L03_003E3308(u8 *);
extern void func_L03_003E3430(u8 *);

/* Sets the fourteen node vectors to unit length and lists in each node's row of the shared
   six-entry neighbour table the nodes whose direction is close to its own (dot product above
   0.5, or above -0.1 when none of the node's components is zero); then sets the orientation
   from the angles at +0xF0, builds the path (func_L03_003E2968, func_L03_003E2C08) and the
   choice list, and starts the walk at node 0 with the starting timer. */
void func_PAL_L03_003E6CA8(u8 *p) {
    PuzzlePath *q = *(PuzzlePath **)(p + 0x68);
    u8 *position;
    u8 *rotation;
    PuzzleNode *node;
    int k, row, col, i, j, n, m;
    f32 d, t;

    for (k = 0; k < 14; k++) {
        func_00282F20(&D_L03_0029BBF0[k], &D_L03_0029BBF0[k], 1.0f);
        q->facing[k] = 255;
    }
    q->facing[14] = 255;
    rotation = p + 0xC0;
    position = p + 0xF0;

    for (row = 0; row < 14; row++)
        for (col = 0; col < 6; col++)
            D_0024A7B0[row][col] = -1;

    for (i = 0; i < 14; i++) {
        n = 0;
        for (j = 0; j < 14; j++) {
            if (i != j) {
                node = &D_L03_0029BBF0[i];
                d = func_00282DB0(node, &D_L03_0029BBF0[j]);
                t = 0.5f;
                if (node->x != 0.0f && node->y != 0.0f && node->z != 0.0f)
                    t = -0.1f;
                if (d > t)
                    D_0024A7B0[i][n++] = j;
            }
        }
    }

    func_002AB6D8(rotation, position);
    func_002A91F0(D_L03_001B36B0, position);
    func_001163A0(q->sound);
    func_L03_003E2968(p);
    func_L03_003E2C08(p);
    func_L03_003E3308(p);
    func_L03_003E3430(p);

    for (m = 0; m < 16; m++) {
        q->order[m] = 255;
        q->visited[m] = 0;
    }
    q->order[0] = 0;
    q->visited[0] = 1;
    q->length = 0;
    q->pending = -1;
    q->current = 0;
    q->last = 0;
    q->next = 0;
    q->cursor = 0;
    q->depth = 0;
    q->timer = ((s32)(D_L03_001B0B5C) * 5 + 2) / 6;
}
