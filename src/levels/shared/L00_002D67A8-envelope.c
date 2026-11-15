#include "include_asm.h"
#include "names.h"

/* Level counterpart of func_0026F810. Scratch-array layout and pointer updates
 * follow RAC1 actuator_CalcPower, src/game/actuator.c
 * (OpenRAC/Lombyte, GPL-3.0). */
extern float func_00283CE0(int), func_00283180(float);
extern int func_00283CF0(float);
typedef struct {
    unsigned char kind, permanent, output, multiply;
    short delay, duration, frame, rise, fall;
    unsigned char amplitude, bias;
} WaveChannel;
extern WaveChannel D_L00_001B8C00[8];

/* Mixes the eight active wave channels into two output values, one per output. Returns how many channels are in use. */
int func_L00_002D6BA8(int *out)
{
    int scratch[3][4];
    int *outputCount;
    int *multiplyCount;
    int i, active = 0;

    multiplyCount = scratch[1];
    outputCount = scratch[2];
    for (i = 0; i < 2; i++) {
        out[i] = 0;
        scratch[0][i] = 0;
        scratch[1][i] = 0;
        scratch[2][i] = 0;
    }
    for (i = 0; i < 8; i++) {
        WaveChannel *channel;
        int phase, value;

        if (!D_L00_001B8C00[i].kind)
            continue;
        active++;
        if (!D_L00_001B8C00[i].permanent) {
            if (D_L00_001B8C00[i].duration-- <= 0)
                D_L00_001B8C00[i].kind = 0;
        }
        if (D_L00_001B8C00[i].delay) {
            D_L00_001B8C00[i].delay--;
            continue;
        }
        channel = &D_L00_001B8C00[i];
        D_L00_001B8C00[i].frame++;
        value = 0;
        phase = channel->frame % (channel->rise + channel->fall);
        switch (channel->kind) {
        case 0:
            break;
        case 1:
            if (phase < channel->rise)
                value = channel->amplitude + channel->bias;
            else
                value = channel->bias;
            break;
        case 2:
            if (phase < channel->rise)
                value = channel->amplitude * phase / channel->rise;
            else
                value = channel->amplitude * (channel->fall + channel->rise - phase) / channel->fall;
            value += channel->bias;
            break;
        case 3:
            if (phase < channel->rise)
                value = channel->amplitude * phase / channel->rise + channel->bias;
            break;
        case 4:
            if (phase >= channel->rise)
                value = channel->amplitude * (channel->fall + channel->rise - phase) / channel->fall + channel->bias;
            break;
        case 5: {
            float angle;

            if (phase < channel->fall)
                angle = IntToFloat(phase) * 3.1415927f / IntToFloat(channel->fall);
            else
                angle = 3.1415927f - IntToFloat(phase - channel->fall) * 3.1415927f / IntToFloat(channel->rise);
            angle = FastSinOrCosA(angle);
            {
                float a = IntToFloat(channel->amplitude);
                value = FloatToInt((angle * a + a) * 0.5f) + channel->bias;
            }
            if (value > 255)
                value = 255;
            break;
        }
        }
        if (channel->multiply) {
            scratch[0][channel->output] += value;
            {
                int *p = multiplyCount + channel->output;
                *p = *p + 1;
            }
        } else {
            out[channel->output] += value;
            {
                int *p = outputCount + channel->output;
                *p = *p + 1;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        int j = i;

        if (outputCount[j])
            out[j] /= outputCount[j];
        if (multiplyCount[j]) {
            scratch[0][j] /= multiplyCount[j];
            out[j] = out[j] * scratch[0][j] / 255;
        }
    }
    return active;
}
