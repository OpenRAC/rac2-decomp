#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

typedef struct {
    int v[9];
} InitValues;

extern InitValues g_hoverbike_course_init_values;
/* Retail forms these three addresses as single lui/addiu pairs. */
extern char g_route_frame_origin[] __attribute__((sda));
extern char g_route_frame_delta[] __attribute__((sda));
extern char g_route_frame_forward[] __attribute__((sda));
extern char g_race_ruler_slots[];
extern char g_race_course_records[];
extern int g_race_ruler_scroll_offset;
extern int g_current_race_index __attribute__((sda));
extern char *g_moby_l04_pool[] __attribute__((sda));
extern void racer_reset_state(void *, int);
extern void InitRaceParticipants(void *);
extern void FastVecScale(void *, void *, float);
extern int GetFirstMobyInGroup(char **, int, int, int);
extern int GetNextMobyInGroup(char **, char *, int, int);

/* Reset the controller state, snapshot the object's position and matrix,
 * seed the nine-entry value table, then enable or disable the mobys of two
 * groups and four indexed mobys according to the current record's flags. */
void hoverbike_init_race_course(char *obj)
{
    InitValues vals = g_hoverbike_course_init_values;
    char *data = *(char **)(obj + 0x68);
    char *moby;
    char *other;
    char *matrix;
    int *indices;
    char *mobys;
    int j;

    racer_reset_state(obj, 0);
    *(int *)(data + 0x494) = -1;
    *(int *)(data + 0x498) = 0;
    *(float *)(data + 0x4A4) = -1;
    *(int *)(data + 0x49C) = -1;
    *(int *)(data + 0x4A0) = -1;
    *(int *)(data + 0x4B0) = 0;
    *(int *)(data + 0x4A8) = 0;
    *(int *)(data + 0x4AC) = 0;
    *(Quad *)g_route_frame_origin = *(Quad *)(obj + 0x10);
    matrix = g_route_frame_delta;
    *(Quad *)matrix = *(Quad *)(obj + 0xC0);
    *(Quad *)(matrix + 0x10) = *(Quad *)(obj + 0xD0);
    *(Quad *)(matrix + 0x20) = *(Quad *)(obj + 0xE0);
    FastVecScale(g_route_frame_forward, g_route_frame_forward, -1);
    g_race_ruler_scroll_offset = 0;
    for (j = 0; j < 9; j++) {
        *(int *)(g_race_ruler_slots + j * 8) = 0;
        *(float *)(g_race_ruler_slots + j * 8 + 4) = vals.v[j];
    }
    indices = (int *)(data + 0x23C);

    if (*(int *)(data + 0x260) != -1) {
        GetFirstMobyInGroup(&moby, *(int *)(data + 0x260), 0, 0);
        if (moby) do {
            if (*(short *)(moby + 0xAA) == MOBY_CLASS_HOVERBIKE_RACE_ITEM_BOX) {
                if (*(int *)(g_race_course_records + (g_current_race_index << 6)) & 1) {
                    **(int **)(moby + 0x68) = 0;
                    *(unsigned short *)(moby + 0x34) &= 0xFFBE;
                    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
                    *(unsigned short *)(moby + 0x34) &= 0xFFFD;
                } else {
                    *(unsigned short *)(moby + 0x34) |= 0x41;
                    *(int *)(moby + 0x98) = 0;
                    *(unsigned short *)(moby + 0x34) |= 2;
                }
            }
            GetNextMobyInGroup(&moby, moby, 0, 0);
        } while (moby);
    }

    if (*(int *)(data + 0x25C) != -1) {
        GetFirstMobyInGroup(&other, *(int *)(data + 0x25C), 0, 0);
        if (other) do {
            if (*(short *)(other + 0xAA) == 0xA99 /* moby class 2713 */) {
                **(int **)(other + 0x68) = 0;
                *(unsigned short *)(other + 0x34) &= 0xFFBE;
            }
            GetNextMobyInGroup(&other, other, 0, 0);
        } while (other);
    }

    {
        int record = g_current_race_index;
        int i;

        mobys = g_moby_l04_pool[0];
        for (i = 0; i < 4; i++) {
            if (indices[i] != -1) {
                char *target = mobys + (indices[i] << 8);
                if (target) {
                    if (*(int *)(g_race_course_records + (record << 6)) & 4) {
                        *(int *)(target + 0x98) = 0;
                        *(unsigned short *)(target + 0x34) |= 0x41;
                    } else {
                        *(unsigned short *)(target + 0x34) &= 0xFFBE;
                        *(int *)(target + 0x98) = *(int *)(*(char **)(target + 0x24) + 0x10);
                    }
                }
            }
        }
    }
    InitRaceParticipants(obj);
}
