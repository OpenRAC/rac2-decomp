#include "common.h"

extern int g_path_puzzle_adjacency[14][6];
extern int g_path_puzzle_step_count __attribute__((sda));
extern int math_random_int_below(int);

typedef struct {
    u8 pad[0x20];
    u8 path[16];
} PuzzleState29;

/* Builds a random route through the puzzle nodes, adding one node at a time until it is as long as the puzzle needs. */
void path_puzzle_generate_route(u8 *moby) {
    PuzzleState29 *state = *(PuzzleState29 **)(moby + 0x68);
    int count = 3, start, old, inserted, i, a, b, j, k, n, found, scan, shift;

    state->path[0] = 0;
    switch (math_random_int_below(4)) {
    case 0:
        state->path[1] = 1;
        state->path[2] = 2;
        break;
    case 1:
        state->path[2] = 3;
        state->path[1] = 2;
        break;
    case 2:
        state->path[1] = 3;
        state->path[2] = 4;
        break;
    default:
        state->path[1] = 4;
        state->path[2] = 1;
        break;
    }

    while (count < g_path_puzzle_step_count) {
        start = math_random_int_below(count);
        old = count;
        inserted = 0;
        for (i = 0; i < count; i++) {
            a = (start + i) % count;
            b = (start + i + 1) % count;
            for (j = 0; j < 6; j++) {
                n = g_path_puzzle_adjacency[state->path[a]][j];
                if (n == -1)
                    break;
                found = 0;
                for (scan = 0; scan < count; scan++)
                    if (n == state->path[scan])
                        found = 1;
                if (found)
                    continue;
                for (k = 0; k < 6; k++) {
                    if (g_path_puzzle_adjacency[n][k] == state->path[b]) {
                        for (shift = count - 1; shift > a; shift--)
                            state->path[shift + 1] = state->path[shift];
                        state->path[a + 1] = n;
                        count++;
                        inserted = 1;
                        break;
                    }
                }
                if (inserted)
                    break;
            }
            if (inserted)
                break;
        }
        if (old == count) {
            g_path_puzzle_step_count = count;
            break;
        }
    }
}
