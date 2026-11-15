#include "names.h"
/* Bordered text panel: background box, six border pieces, then the text lines.
   The border offsets are per-program records (ref_ names); 0x1D0 is a float field. */
typedef struct { float x, y; } BorderOffset_00338AD8;
typedef struct { int x, y; } TextOffset_00338AD8;
typedef struct { TextOffset_00338AD8 a, b, c; } TextOffsets_00338AD8;
extern BorderOffset_00338AD8 ref_00338AD8_00;
extern BorderOffset_00338AD8 ref_00338AD8_01;
extern TextOffsets_00338AD8 ref_00338AD8_02;
extern void gfx_draw_screen_rectangle(int, int, int, int, int, void *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void object_set_second_float4(void *, float, float, float, float);
extern void gfx_draw_screen_element_stored(void *);
extern void text_draw_small(int, int, long, signed char *, int);

/* Draws a text panel with a coloured background, border pieces on each side and its lines of text. */
void text_panel_draw(char *panel)
{
    unsigned int colors[4];
    BorderOffset_00338AD8 corner;
    BorderOffset_00338AD8 edge;
    TextOffsets_00338AD8 text;
    float centerX, centerY;
    int i = 0, textX, textY;
    char *cornerPiece = panel + 0x10;
    char *edgePiece = panel + 0x5c;
    colors[0] = **(unsigned int **)(panel + 8);
    colors[1] = colors[0];
    colors[2] = colors[0];
    colors[3] = colors[0];
    gfx_draw_screen_rectangle((int)((*(float **)panel)[0] - (float)*(int *)(panel + 0x1a8)),
                 (int)((*(float **)panel)[1] - (float)*(int *)(panel + 0x1ac)),
                 (int)((*(float **)panel)[0] + (float)*(int *)(panel + 0x1a8)),
                 (int)((*(float **)panel)[1] + (float)*(int *)(panel + 0x1ac)), 0xfffff0, colors);
    corner = ref_00338AD8_00;
    edge = ref_00338AD8_01;
    object_set_first_float4(cornerPiece, ((*(float **)panel)[0] - (float)*(int *)(panel + 0x1a8)) - corner.x,
                      ((*(float **)panel)[1] - (float)*(int *)(panel + 0x1ac)) - corner.y, 0.0f, 0.0f);
    object_set_second_float4(cornerPiece, -1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(cornerPiece);
    object_set_first_float4(cornerPiece, (*(float **)panel)[0] + (float)*(int *)(panel + 0x1a8) + corner.x + 1.0f,
                      ((*(float **)panel)[1] - (float)*(int *)(panel + 0x1ac)) - corner.y, 0.0f, 0.0f);
    object_set_second_float4(cornerPiece, 1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(cornerPiece);
    object_set_first_float4(edgePiece, (*(float **)panel)[0] + (float)*(int *)(panel + 0x1a8) + edge.x,
                       ((*(float **)panel)[1] - (float)*(int *)(panel + 0x1ac)) - edge.y, 0.0f, 0.0f);
    object_set_second_float4(edgePiece, 1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(edgePiece);
    object_set_first_float4(edgePiece, ((*(float **)panel)[0] - (float)*(int *)(panel + 0x1a8)) - edge.x + 1.0f,
                       ((*(float **)panel)[1] - (float)*(int *)(panel + 0x1ac)) - edge.y, 0.0f, 0.0f);
    object_set_second_float4(edgePiece, -1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(edgePiece);
    object_set_first_float4(edgePiece, (*(float **)panel)[0] + (float)*(int *)(panel + 0x1a8) + edge.x,
                       (((*(float **)panel)[1] - (float)*(int *)(panel + 0x1ac)) - edge.y) + *(float *)(panel + 0x1d0), 0.0f, 0.0f);
    object_set_second_float4(edgePiece, 1.0f, -1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(edgePiece);
    object_set_first_float4(edgePiece, (((*(float **)panel)[0] - (float)*(int *)(panel + 0x1a8)) - edge.x) + 1.0f,
                       (((*(float **)panel)[1] - (float)*(int *)(panel + 0x1ac)) - edge.y) + *(float *)(panel + 0x1d0), 0.0f, 0.0f);
    object_set_second_float4(edgePiece, -1.0f, -1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(edgePiece);
    centerX = (*(float **)panel)[0];
    centerY = (*(float **)panel)[1];
    text = ref_00338AD8_02;
    textX = (int)((centerX - (float)*(int *)(panel + 0x1a8)) + (float)*(int *)(panel + 0x1bc));
    textY = (int)(centerY - (float)*(int *)(panel + 0x1ac));
    if (*(int *)(panel + 0x1c4) == 1 && *(int *)(panel + 0x1d8)) {
        for (; i < *(int *)(panel + 0x1b0); i++)
            text_draw_small(textX + text.b.x, textY + text.b.y + i * 16,
                         **(unsigned int **)(panel + 12), ((signed char **)(panel + 0x1d8))[i], -1);
    }
}
