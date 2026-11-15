#include "common.h"
#include "structs.h"

extern void mpeg_send_event_one(int);

extern int r1_func_00128C90(void *);

extern int mpeg_stop_decoding(void *);

extern int r1_func_00129690(void *, int);

extern int r1_func_00129530(void *);

extern void r1_func_00129600(void *, int, int);

extern int mpeg_decode_field(void *, int, int);

struct MpegFieldDec
{
  int unk0;
  int unk4;
  int unk8;
  unsigned char pad_C[0xA0];
  int unkAC;
  unsigned char pad_B0[0x24];
  int unkD4;
  unsigned char pad_D8[0x40];
  int unk118;
  int unk11C;
  int unk120;
  unsigned char pad_124[0x50];
  int unk174;
};

struct MpegHandle
{
  unsigned char pad_0[0x8];
  int unk8;
  unsigned char pad_C[0x34];
  struct MpegFieldDec *unk40;
};

extern int r1_func_00129530();

extern int r1_func_00129690();

extern void r1_func_00129600();

/* rac1-decomp src/core/0012AC80.c: func_0012C0A0 */
/* _decodeOrSkipField (libmpeg). Adapted from Lombyte (GPL-3.0) for PAL. */
/* Decodes or skips one video field and moves the field counters forward. */
int mpeg_decode_field(void *mpeg, int fieldIndex, int fieldLimit)
{
  struct MpegHandle *wrapper = mpeg;
  struct MpegFieldDec *decoder;
  int shouldDecode;
  unsigned int ref;
  int wantedMode;
  long status;
  int result;
  int hasReference;
  shouldDecode = 0;
  decoder = wrapper->unk40;
  decoder->unk120 = 0;
  if ((fieldLimit == (-1)) || (fieldIndex < fieldLimit))
  {
    shouldDecode = 1;
  }
  if (decoder->unk8 == 0)
  {
    wrapper->unk8 = 0;
    decoder->unk8 = 1;
  }
  status = r1_func_00129690(decoder, 0);
  if ((status != 0) && (shouldDecode != 0))
  {
    r1_func_00129530(decoder);
  }
  decoder->unk120 = 1;
  status = r1_func_00128C90(decoder);
  if (status == 0)
  {
    mpeg_stop_decoding(wrapper);
    decoder->unk0 = 1;
    return 0;
  }
  wantedMode = 2;
  if (decoder->unkD4 != 1)
  {
    wantedMode = 1;
  }
  if (decoder->unk174 != wantedMode)
  {
    return -1;
  }
  ref = r1_func_00129690(decoder, 1);
  hasReference = 0;
  if (ref != 0)
  {
    hasReference = 1;
  }
  result = 0;
  if (hasReference != 0)
  {
    if (shouldDecode == 0)
    {
      goto out;
    }
    status = r1_func_00129530(decoder);
    if (status != 0)
    {
      result = 1;
    }
  }
  out:
  r1_func_00129600(decoder, decoder->unk118, decoder->unk4);

  decoder->unk120 = 0;
  wrapper->unk8 = decoder->unk118 - decoder->unkAC;
  decoder->unk118 = decoder->unk118 + 1;
  decoder->unk4 = (unsigned long long) (decoder->unk4 + 1);
  if (shouldDecode == 0)
  {
    mpeg_send_event_one((int)wrapper);
  }
  return result;
}
