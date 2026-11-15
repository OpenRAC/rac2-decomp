#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

/* Copied mechanically from Lombyte sdk/library/update_temp_track_data.c; current source and actual
 * SDK-built full object/ref body pinned in donor-proof.json. Algorithm,
 * layout, signedness, expressions and source order preserved. Function
 * rename and duplicate EE scalar-type/include context removal only.
 * The donor SDK compiler b9aef69 differs; RAC2 acceptance requires its own qualification. */
/*
MIT License

Copyright (c) 2026 Mateusz Kłysz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
struct M2c_arg0
{
  u8 pad_0[0x150];
  s32 pictureCodingType;
  u8 pad_154[0x58];
  s32 tempRefAdjusted;
  u8 pad_1B0[0x69C];
  s32 tempRefBase;
  s32 tempRefMax;
  s32 gopStartFlag;
};

/* Keeps track of the frame order numbers of pictures so they stay in step when a new group starts. */
void mpeg_update_temporal_tracking(struct M2c_arg0 *decoder, s32 tempRefDelta)
{
  s32 unusedTemp;
  s32 adjustedRef;
  s32 currentRef;
  s32 deltaRef;
  s32 needsWrapFix;
  needsWrapFix = 0;
  deltaRef = 0;
  if ((decoder->pictureCodingType != 3) && (tempRefDelta != 0))
  {
    if (tempRefDelta < 0)
    {
      needsWrapFix = decoder->gopStartFlag == 0;
    }
    decoder->gopStartFlag = 0;
    deltaRef = tempRefDelta;
  }
  adjustedRef = decoder->tempRefBase + tempRefDelta;
  decoder->tempRefAdjusted = adjustedRef;
  if ((needsWrapFix != 0) && (deltaRef >= tempRefDelta))
  {
    decoder->tempRefAdjusted = (s32) (adjustedRef + 0x400);
  }
  ;
  currentRef = decoder->tempRefAdjusted;
  decoder->tempRefMax = (s32) ((decoder->tempRefMax < currentRef) ? (currentRef) : (decoder->tempRefMax));
}

extern int mpeg_read_bits(void *, int);
extern void mpeg_read_extension_data(void *);

/* Reads a group of pictures header and resets the frame order tracking. */
void mpeg_read_gop_header(char *decoderBytes) {
    *(int *)(decoderBytes + 0xE8) = 0;
    *(int *)(decoderBytes + 0x854) = 1;
    *(int *)(decoderBytes + 0x84C) = *(int *)(decoderBytes + 0x850) + 1;
    mpeg_read_bits(decoderBytes, 1);
    mpeg_read_bits(decoderBytes, 5);
    mpeg_read_bits(decoderBytes, 6);
    mpeg_read_bits(decoderBytes, 1);
    mpeg_read_bits(decoderBytes, 6);
    mpeg_read_bits(decoderBytes, 6);
    *(int *)(decoderBytes + 0x1A4) = mpeg_read_bits(decoderBytes, 1);
    *(int *)(decoderBytes + 0x1A8) = mpeg_read_bits(decoderBytes, 1);
    mpeg_read_extension_data(decoderBytes);
}
