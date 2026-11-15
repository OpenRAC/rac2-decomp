#include "names.h"
/* SPDX-License-Identifier: MIT
 * MIT License
 *
 * Copyright (c) 2026 RC2 decomp contributions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "common.h"

extern s32 GetEffectTextureDescriptor(s32);
extern void AppendRotatedSpriteQuad(f32, f32, s32, s32, s32, s32, s32, f32, f32, s32, s32, f32, f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 FastAddRotations(f32, f32);

/* Draws a sprite on screen at the given position, as one image, a spread of copies, or a 2x2 tile set. */
void gfx_draw_screen_sprite(s8 *sprite, f32 screenX, f32 screenY)
{
    f32 offsets[2][4];
    s32 texture;
    s32 type;
    s32 i;
    f32 angle;
    f32 baseSize;

    baseSize = 40.0f;
    texture = GetEffectTextureDescriptor((*(s32 *)((s8 *)(sprite) + (0x18))));
    type = (*(s32 *)((s8 *)(sprite) + (0x2C)));
    angle = (*(f32 *)((s8 *)(sprite) + (0x1C)));
    switch (type) {
    case 0:
        if ((*(s16 *)((s8 *)(sprite) + (0x26))) > 0) {
            i = 0;
            do {
                AppendRotatedSpriteQuad(screenX, screenY, 63, 63, texture, 0xFFFFF3, (*(s32 *)((s8 *)(sprite) + (0x14))),
                              baseSize * (*(f32 *)((s8 *)(sprite) + (0x10))), baseSize * (*(f32 *)((s8 *)(sprite) + (0x10))), 0, 0,
                              angle, 0.0f, 0.0f);
                i++;
                angle = FastAddRotations(angle, (*(f32 *)((s8 *)(sprite) + (0x28))));
            } while (i < (*(s16 *)((s8 *)(sprite) + (0x26))));
        }
        break;
    case 1:
        offsets[0][0] = math_fast_sin_or_cos_b(angle) * baseSize * (*(f32 *)((s8 *)(sprite) + (0x10)));
        offsets[0][1] = math_fast_sin_or_cos_a(angle) * baseSize * (*(f32 *)((s8 *)(sprite) + (0x10)));
        offsets[1][0] = math_fast_sin_or_cos_a(angle) * baseSize * (*(f32 *)((s8 *)(sprite) + (0x10)));
        offsets[1][1] = math_fast_sin_or_cos_b(angle) * -baseSize * (*(f32 *)((s8 *)(sprite) + (0x10)));
        ((void (*)(f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, f32, f32))AppendRotatedSpriteQuad)(
            screenX, screenY, (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize, (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize, angle,
            63, 63, texture, 0xFFFFF3, (*(s32 *)((s8 *)(sprite) + (0x14))), 0, 0, 0.0f, 0.0f);
        ((void (*)(f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, f32, f32))AppendRotatedSpriteQuad)(
            screenX + offsets[1][0], screenY + offsets[1][1], (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize, (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize, angle,
            63, 63, texture, 0xFFFFF3, (*(s32 *)((s8 *)(sprite) + (0x14))), 1, 0, 0.0f, 0.0f);
        ((void (*)(f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, f32, f32))AppendRotatedSpriteQuad)(
            screenX - offsets[0][0], screenY - offsets[0][1], (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize, (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize, angle,
            63, 63, texture, 0xFFFFF3, (*(s32 *)((s8 *)(sprite) + (0x14))), 0, 1, 0.0f, 0.0f);
        ((void (*)(f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, f32, f32))AppendRotatedSpriteQuad)(
            (screenX + offsets[1][0]) - offsets[0][0], (screenY + offsets[1][1]) - offsets[0][1], (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize,
            (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize, angle, 63, 63, texture, 0xFFFFF3, (*(s32 *)((s8 *)(sprite) + (0x14))), 1, 1, 0.0f, 0.0f);
        break;
    case 2:
        ((void (*)(f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, f32, f32))AppendRotatedSpriteQuad)(
            screenX, screenY, (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize, (*(f32 *)((s8 *)(sprite) + (0x10))) * baseSize, angle,
            63, 63, texture, 0xFFFFF3, (*(s32 *)((s8 *)(sprite) + (0x14))), 0, 0, 0.5f, 0.5f);
        break;
    }
}
