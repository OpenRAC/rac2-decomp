#include "common.h"

typedef struct Key_335960 {
    struct Key_335960 *next;
    int unknown;
    float time;
    float value[4];
} Key_335960;
typedef struct { char pad[12]; Key_335960 *first; unsigned int count; int mode; } Track_335960;
typedef struct { char pad[8]; Track_335960 *track; } Owner_335960;

/* Reads a value from a list of timed keys. It blends between the two keys around the given time. */
void InterpolateTrackVector(Owner_335960 *owner, float *out, float time) {
    Key_335960 *key, *previous;
    unsigned int i;
    float t;
    if (owner->track->count == 0) return;
    if (owner->track->count == 1) {
        out[0] = owner->track->first->value[0];
        out[1] = owner->track->first->value[1];
        out[2] = owner->track->first->value[2];
        out[3] = owner->track->first->value[3];
        return;
    }
    key = owner->track->first;
    previous = key;
    for (i = 0; i < owner->track->count; i++) {
        if (key->next != 0 && key->time <= time) {
            previous = key;
            key = key->next;
        } else {
            break;
        }
    }
    t = (time - previous->time) / (key->time - previous->time);
    switch (owner->track->mode) {
    case 0: case 1:
        out[0] = (1.0f-t)*previous->value[0] + t*key->value[0];
        out[1] = (1.0f-t)*previous->value[1] + t*key->value[1];
        out[2] = (1.0f-t)*previous->value[2] + t*key->value[2];
        out[3] = (1.0f-t)*previous->value[3] + t*key->value[3];
        break;
    case 2:
        break;
    }
}
