#include "include_asm.h"
#include "names.h"

typedef struct Rac2Native_428d1e2cc4aa1f21_Keyed {
    unsigned char unknown_00[28];
    char *owner_1c;
} Rac2Native_428d1e2cc4aa1f21_Keyed;

extern char *g_follow_camera_object;

extern Rac2Native_428d1e2cc4aa1f21_Keyed *g_camera_def_table;

/* Tries to claim the camera request slot. A new request wins if the current owner has a lower priority; returns -1 if the camera is not in the normal mode. */
int cam_claim_request_slot(char *request)
{
    char *camera = g_follow_camera_object;
    char *state;
    char *current;

    if (*(short *)(camera + 134) != 0) {
        return -1;
    }
    state = *(char **)(camera + 112);
    current = *(char **)(state + 576);
    if (current == 0) {
        *(char **)(state + 576) = request;
        return 1;
    }
    if (current == request) {
        return 1;
    }
    if (*(unsigned char *)(g_camera_def_table[*(short *)(current + 132)].owner_1c + 28) <
        *(unsigned char *)(g_camera_def_table[*(short *)(request + 132)].owner_1c + 28)) {
        *(char **)(state + 576) = request;
        return 1;
    }
    return 0;
}
