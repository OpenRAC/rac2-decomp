#include "common.h"

/* func_L03_003E26C8 reads the starting timer through $gp, and its float tests branch to the
   label on the mtc1 hazard nop: a -G8 unit of its own with -frac2-hazard-labels. */

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
extern u16 D_L03_001B0B5C __attribute__((sda));
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
void func_L03_003E26C8(u8 *moby) {
    PuzzlePath *pathState = *(PuzzlePath **)(moby + 0x68);
    u8 *position;
    u8 *rotation;
    PuzzleNode *node;
    int k, row, col, i, j, n, m;
    f32 similarity, limit;

    for (k = 0; k < 14; k++) {
        vec_scale_to_length(&D_L03_0029BBF0[k], &D_L03_0029BBF0[k], 1.0f);
        pathState->facing[k] = 255;
    }
    pathState->facing[14] = 255;
    rotation = moby + 0xC0;
    position = moby + 0xF0;

    for (row = 0; row < 14; row++)
        for (col = 0; col < 6; col++)
            D_0024A7B0[row][col] = -1;

    for (i = 0; i < 14; i++) {
        n = 0;
        for (j = 0; j < 14; j++) {
            if (i != j) {
                node = &D_L03_0029BBF0[i];
                similarity = FastVecDot(node, &D_L03_0029BBF0[j]);
                limit = 0.5f;
                if (node->x != 0.0f && node->y != 0.0f && node->z != 0.0f)
                    limit = -0.1f;
                if (similarity > limit)
                    D_0024A7B0[i][n++] = j;
            }
        }
    }

    GetEulerAnglesFromMatrix(rotation, position);
    BuildRotationFromAngles(D_L03_001B36B0, position);
    Srand(pathState->sound);
    GeneratePathPuzzleRoute(moby);
    SelectPathStepNodes(moby);
    BuildChoiceList(moby);
    ChoosePathPuzzleNextNode(moby);

    for (m = 0; m < 16; m++) {
        pathState->order[m] = 255;
        pathState->visited[m] = 0;
    }
    pathState->order[0] = 0;
    pathState->visited[0] = 1;
    pathState->pending = -1;
    pathState->timer = D_L03_001B0B5C;
    pathState->current = 0;
    pathState->last = 0;
    pathState->next = 0;
    pathState->cursor = 0;
    pathState->depth = 0;
    pathState->length = 0;
}
