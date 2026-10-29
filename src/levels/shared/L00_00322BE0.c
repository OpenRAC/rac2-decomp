/* Adapted from RAC1 update_moby_transform_history at 8bbc6b38,
 * src/overlays/shared/moby_path_and_manipulators.c (GPL-3.0), retaining its
 * Lombyte gameplay_state_00261968.c/FUN_L00_00262608 source provenance.
 * RAC2 adds per-follower blending and optional source-basis propagation. */
#include "common.h"

typedef struct { float f[4]; } HistoryVector __attribute__((aligned(16)));
typedef int HistoryQuad __attribute__((mode(TI)));
typedef struct { HistoryQuad rows[3]; } HistoryBasis;
typedef struct {
    char reserved00[0x10];
    HistoryVector position;
    unsigned char state, reserved21, reserved22, alpha;
    char reserved24[0x1C];
    unsigned char frame, previousFrame, sequence, previousSequence;
    float animationTime;
    char reserved48[0x10];
    void *frameData, *previousFrameData;
    char reserved60[0x1C];
    unsigned short matrixFlags;
    char reserved7E[0x2C];
    short classId;
    char reservedAC[0x14];
    HistoryBasis basis;
    HistoryVector rotation;
} HistoryMoby;
typedef struct {
    HistoryVector positions[8], rotations[8];
    int alpha[4], delay[4];
    HistoryMoby *followers[4];
    float blend[4];
    short head, count;
    HistoryMoby *source;
    int followersUsed, active;
} TransformHistory;
extern void func_L00_00322EC8(void *);
extern void func_0029F390(unsigned char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A0F48(void *);

/* 322AC0 independently bounds followersUsed to four; each persistent history
 * record has stride 0x150 and each ring contains eight complete 16-byte samples. */
void func_L00_00322BE0(TransformHistory *history, int fade)
{
    HistoryMoby *source, *follower;
    int head, i, sample, done;
    if (!history->active)
        return;
    source = history->source;
    if (!source || source->state == 0xFE || source->state == 0xFD) {
        func_L00_00322EC8(history);
        return;
    }
    head = history->head;
    qcopy(&history->positions[head], &source->position);
    qcopy(&history->rotations[head], &source->rotation);
    history->head = (head + 1) % 8;
    if (++history->count > 8)
        history->count = 8;
    for (i = 0; i < history->followersUsed; i++) {
        int lag;
        if (history->count >= (lag = history->delay[i])) {
            follower = history->followers[i];
            sample = (history->head - lag + 8) % 8;
            follower->sequence = history->source->sequence;
            follower->previousSequence = history->source->previousSequence;
            follower->frame = history->source->frame;
            follower->previousFrame = history->source->previousFrame;
            follower->animationTime = history->source->animationTime;
            if (follower->classId == 0) {
                follower->frameData = history->source->frameData;
                follower->previousFrameData = history->source->previousFrameData;
            } else {
                func_0029F390((unsigned char *)follower);
            }
            qcopy(&follower->position, &history->positions[sample]);
            qcopy(&follower->rotation, &history->rotations[sample]);
            if (history->blend[i] != 0.0f) {
                HistoryVector delta;
                func_00282CF0(&delta, &follower->position, &history->source->position);
                func_00282D30(&delta, &delta, history->blend[i]);
                func_00282CC0(&follower->position, &follower->position, &delta);
            }
            func_002A0F48(follower);
            {
                HistoryMoby *basisSource = history->source;
                if (basisSource->matrixFlags & 0x8000) {
                    follower->basis.rows[0] = basisSource->basis.rows[0];
                    follower->basis.rows[1] = basisSource->basis.rows[1];
                    follower->basis.rows[2] = basisSource->basis.rows[2];
                }
            }
        }
    }
    if (fade) {
        done = 1;
        for (i = 0; i < history->followersUsed; i++) {
            HistoryMoby *fading = history->followers[i];
            if (fading) {
                int amount = fading->alpha;
                int alpha = amount;
                if (fade < amount)
                    amount = fade;
                alpha -= amount;
                fading->alpha = alpha;
                if ((unsigned char)alpha)
                    done = 0;
            }
        }
        if (done)
            func_L00_00322EC8(history);
    }
}
