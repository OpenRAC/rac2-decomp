#include "names.h"
/* Advances animation frames and decodes the current and next poses. */

typedef union Frame310D30 {
    unsigned int word;
    unsigned char *ptr;
    float *duration;
} Frame310D30;
typedef struct Track310D30 {
    unsigned char pad00[0x10];
    unsigned char frames;
    unsigned char pad11[2];
    volatile unsigned char extra; /* Retail rereads this byte after testing it. */
    unsigned char pad14[8];
    Frame310D30 data[1];
} Track310D30;
typedef struct Model310D30 {
    unsigned char pad00[8];
    unsigned char joints;
    unsigned char pad09[0x3f];
    Track310D30 *tracks[1];
} Model310D30;

/* Animation frame advancement and decoding. Partial views retain only fields read here. */
typedef struct AnimationState310D30 {
    short index, count;
    unsigned char active, events, currentPacked, nextPacked;
    char pad08[8];
    char *output;
    Model310D30 *model;
    unsigned char *nextModel;
    void *next;
    unsigned char currentFrame, nextFrame, currentTrack, nextTrack;
    float phase, rate, frameScale;
    char pad30[8];
    unsigned char *currentData, *nextData;
} AnimationState310D30;
extern void func_L00_003110E8(AnimationState310D30 *, int, int, unsigned char *);
extern void func_002A1130(unsigned char *, unsigned int, unsigned char *, int);
extern int func_0011AEA0(int);
extern void func_L00_00314D40(AnimationState310D30 *);
void func_L00_00310D30(void *unused, AnimationState310D30 *state)
{
    unsigned int data;
    short duration;
    state->events = 0;
    if (state->rate != 0.0f && state->frameScale != 0.0f) {
        state->phase += state->rate * state->frameScale;
        if (state->rate > 0.0f) {
            if (state->phase > 0.99f && state->phase < 1.01f)
                state->phase = 1.0f;
            while (state->phase >= 1.0f) {
                Track310D30 *nextTrack, *track;
                state->events |= 1;
                state->currentPacked = state->nextPacked;
                state->currentFrame = state->nextFrame;
                if (state->nextPacked)
                    state->currentData = state->nextData;
                state->nextFrame++;
                state->currentTrack = state->nextTrack;
                nextTrack = state->model->tracks[state->nextTrack];
                if (state->nextFrame >= nextTrack->frames) {
                    state->nextFrame = 0;
                    state->events |= 2;
                }
                state->phase = (state->phase - 1.0f) / state->frameScale;
                track = state->model->tracks[state->currentTrack];
                if (track->extra == 0xff) {
                    state->frameScale = *track->data[state->currentFrame].duration;
                } else {
                    data = track->data[state->currentFrame].word;
                    duration = *(short *)(data & 0x0fffffff);
                    if (duration == 0)
                        state->frameScale = 0.0f;
                    else
                        state->frameScale = 1.0f / duration;
                }
                state->phase *= state->frameScale;
            }
        }
    }
    if (state->currentPacked) {
        BuildDataBlockFromTables(state, state->currentTrack, state->currentFrame, state->currentData);
    } else {
        Track310D30 *track = state->model->tracks[state->currentTrack];
        if (track->extra == 0xff) {
            state->currentData = track->data[state->currentFrame].ptr;
        } else {
            func_002A1130((unsigned char *)(track->data + track->frames) + track->extra * 4,
                track->data[state->currentFrame].word,
                state->currentData, state->model->joints);
            FlushCache(0);
        }
    }
    if (state->nextPacked) {
        BuildDataBlockFromTables(state, state->nextTrack, state->nextFrame, state->nextData);
    } else {
        Track310D30 *track = state->model->tracks[state->nextTrack];
        if (track->extra == 0xff) {
            state->nextData = track->data[state->nextFrame].ptr;
        } else {
            func_002A1130((unsigned char *)(track->data + track->frames) + track->extra * 4,
                track->data[state->nextFrame].word,
                state->nextData, state->model->joints);
            FlushCache(0);
        }
    }
    func_L00_00314D40(state);
}
