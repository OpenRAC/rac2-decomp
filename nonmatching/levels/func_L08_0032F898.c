/* Bounded near miss, 2026-10-28: 720/744 bytes after four forms.
 * Disabling strength reduction preserves the real index shift and restores
 * the persistent filter-pointer/save roles; ordinary canonical count accesses
 * plus the measured GP refresh keep the complete unknown list owner.
 * Reordering status/acceptance first-use lifetimes and a subsequent-fno-gcse
 * trial tie720. The broad control is removed. Retail keeps two hero-rejection
 * status stores that this compiler merges; several count/address setup words
 * differ. Reopen with genuine status/count CFG or first-use lifetime evidence.
 * Canonical five-GPR probe returnsint and takes index plus three pointers.
 * Old callers pass stored-address words and-1 sentinel through int declarations;
 * lead must audit those callers before any future candidate promotion.
 * Output48hex bytes (fourvector16,pointer4,status4), objectpoolstride256,
 * class/state/rotation reads through0x100; count/index storage stays incomplete.
 * All vectors are copied from existing pose storage or zeroed by approved
 * helpers. No fabricated fourth-lane initialization, volatile or padding.
 */
#include "common.h"

struct SelectedTarget {
    float position[4], rotation[4], first[4], second[4];
    char *object;
    int status;
};
extern char D_00189E20[];
extern short D_L08_001B2B30[];
/* Only the count refresh after probes selects the real GP view. Both
 * declarations preserve the complete unknown count/index owner. */
extern unsigned short D_L08_001B2B30_gp[] SDATA(D_L08_001B2B30);
extern unsigned char *D_L08_001B29DC __attribute__((sda));
extern int func_L01_003165E8(char *, int, char *, char *, char *);
extern float func_00282E80(void *, void *);

/* The native pool uses256-byte objects; direct class/state/pose accesses end
 * at0x100. The count plus signed native indices remain an incomplete owner.
 * Output is four complete16-byte vectors, one pointer and one integer status.
 * Three filter pointers retain the verified probe interface, including the
 * caller's stored-address or-1 sentinel values; neither is silently narrowed. */
int func_L08_0032F898(char *origin, struct SelectedTarget *out,
                    float best_distance, float unconditional_distance,
                    int index, char *filter_a, char *filter_b, char *filter_c)
{
    char *hero = D_00189E20;
    char *selected = *(char **)(hero + 0x2290);
    int status = 0, i;
    float *hero_position;
    float *rotation, *first, *second;
    if (*(int *)(hero + 0x229c) == 24 || *(int *)(hero + 0x2294) == 111) {
        status = 2;
        selected = 0;
    } else {
        hero_position = (float *)(hero + 0x80);
        if (!func_L01_003165E8((char *)hero_position, index, filter_a, filter_b, filter_c) &&
            unconditional_distance < func_00282E80(origin + 0x10, hero_position)) {
            selected = 0;
            status = 2;
        }
    }
    rotation = out->rotation;
    first = out->first;
    second = out->second;
    i = 1;
    {
        int initial_count = D_L08_001B2B30[0];
        unsigned short count = (unsigned short)D_L08_001B2B30[0];
        if (initial_count > 0) do {
            char *candidate = (char *)D_L08_001B29DC + ((int)D_L08_001B2B30[i] << 8);
            if (candidate) {
                int class_id = *(short *)(candidate + 0xaa);
                unsigned char state;
                int accepted;
                float distance;
                if (class_id != 0xcb && class_id != 0x76c && class_id != 0xeb0) goto next;
                state = candidate[0x20];
                if (state == 0xfe) goto next;
                if (state == 0xfd) goto next;
                if (state != 3) goto next;
                accepted = 1;
                distance = func_00282E80(origin + 0x10, candidate + 0x10);
                if (best_distance <= distance) accepted = 0;
                else if (!(distance < unconditional_distance) &&
                    !func_L01_003165E8(candidate + 0x10, index, filter_a, filter_b, filter_c)) accepted = 0;
                count = D_L08_001B2B30_gp[0];
                if (accepted) {
                    selected = candidate;
                    status = 1;
                    best_distance = distance;
                }
            }
next:
            ++i;
        } while ((short)count >= i);
    }
    if (selected) {
        out->object = selected;
        qcopy(out->position, selected + 0x10);
        qcopy(rotation, selected + 0xf0);
        hero = D_00189E20;
        if (selected == *(char **)(hero + 0x2290)) {
            qcopy(first, hero + 0xd0);
            qcopy(second, hero + 0xe0);
        } else {
            qcopy(second, out->position);
            second[2] += 0.6f;
            qcopy(first, second);
        }
    } else {
        out->object = 0;
        qzero(out->position);
        qzero(rotation);
        qzero(second);
        qzero(first);
    }
    out->status = status;
    return status;
}
