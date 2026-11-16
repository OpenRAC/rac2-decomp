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

extern PuzzleNode g_puzzle_node_directions[14];
extern int g_path_puzzle_adjacency[14][6];
extern u16 g_path_puzzle_duration __attribute__((sda));
extern f32 g_puzzle_rotation_quat[4] __attribute__((sda));
extern void vec_scale_to_length(void *, void *, f32);
extern f32 FastVecDot(void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern void mat_build_rotation_from_angles(void *, void *);
extern void func_001163A0(unsigned int);
extern void path_puzzle_generate_route(u8 *);
extern void SelectPathStepNodes(u8 *);
extern void choice_list_build(u8 *);
extern void path_puzzle_choose_next_node(u8 *);

/* Sets the fourteen node vectors to unit length and lists in each node's row of the shared
   six-entry neighbour table the nodes whose direction is close to its own (dot product above
   0.5, or above -0.1 when none of the node's components is zero); then sets the orientation
   from the angles at +0xF0, builds the path (func_L03_003E2968, func_L03_003E2C08) and the
   choice list, and starts the walk at node 0 with the starting timer. */
void InitializePathPuzzle(u8 *moby) {
    PuzzlePath *path_state = *(PuzzlePath **)(moby + 0x68);
    u8 *position;
    u8 *rotation;
    PuzzleNode *node;
    int k, row, col, i, j, n, m;
    f32 similarity, limit;

    for (k = 0; k < 14; k++) {
        vec_scale_to_length(&g_puzzle_node_directions[k], &g_puzzle_node_directions[k], 1.0f);
        path_state->facing[k] = 255;
    }
    path_state->facing[14] = 255;
    rotation = moby + 0xC0;
    position = moby + 0xF0;

    for (row = 0; row < 14; row++)
        for (col = 0; col < 6; col++)
            g_path_puzzle_adjacency[row][col] = -1;

    for (i = 0; i < 14; i++) {
        n = 0;
        for (j = 0; j < 14; j++) {
            if (i != j) {
                node = &g_puzzle_node_directions[i];
                similarity = FastVecDot(node, &g_puzzle_node_directions[j]);
                limit = 0.5f;
                if (node->x != 0.0f && node->y != 0.0f && node->z != 0.0f)
                    limit = -0.1f;
                if (similarity > limit)
                    g_path_puzzle_adjacency[i][n++] = j;
            }
        }
    }

    mat_get_euler_angles(rotation, position);
    mat_build_rotation_from_angles(g_puzzle_rotation_quat, position);
    func_001163A0(path_state->sound);
    path_puzzle_generate_route(moby);
    SelectPathStepNodes(moby);
    choice_list_build(moby);
    path_puzzle_choose_next_node(moby);

    for (m = 0; m < 16; m++) {
        path_state->order[m] = 255;
        path_state->visited[m] = 0;
    }
    path_state->order[0] = 0;
    path_state->visited[0] = 1;
    path_state->pending = -1;
    path_state->timer = g_path_puzzle_duration;
    path_state->current = 0;
    path_state->last = 0;
    path_state->next = 0;
    path_state->cursor = 0;
    path_state->depth = 0;
    path_state->length = 0;
}
