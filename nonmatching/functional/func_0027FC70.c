/* functional: medium. Starts from the near-miss reconstruction: same reads, writes and calls in retail order; byte differences are register allocation and frame size only. */
typedef unsigned char u8;
typedef unsigned long u64;
extern int D_001B1668 __attribute__((sda));
extern int D_001A89B0[] __attribute__((sda));
extern int func_0027F128(u8 *, int, u8 *);
extern void func_0027F640(u64, u8 *, int, u64, u8 *, float, float, float);
extern void func_0027F2A8(int, int, u64, u8 *, int, u64, u8 *);
extern int D_001A8BB0 __attribute__((sda));
extern int D_001B166C __attribute__((sda));
extern int D_001A7340, D_001A7344;
extern void func_002FC620(int, int, int, int);

void func_0027FC70(unsigned short *layout, u64 color, u8 *text, int length,
                   u64 texture, u8 *metrics)
{
    short starts[32], ends[32], styles[32];
    int width, original_width;
    int style, expanded, prior_count, last_width;
    int count, cursor, y, i;
    short *box = (short *)layout;
    if (D_001A8BB0 != 1)
        func_002FC620(box[2], box[3] - 1, box[0], box[1] - 1);
    D_001B166C = 1;
    if (!(layout[9] & 1))
        width = box[3] - box[4];
    else {
        int left = box[4] - box[2];
        int right = box[3] - box[4];
        width = (left < right ? left : right) << 1;
    }
    original_width = width;
    style = 0;
    expanded = 0;
    prior_count = 0;
    last_width = 0;
retry_wrap:
    count = 0;
    cursor = 0;
    if (length != 0 && text[0] != 0) {
        do {
            int end, row_width = 0;
            starts[count] = cursor;
            styles[count] = style;
            end = cursor;
            if (width > 0) {
                do {
                    int advance;
                    if (text[cursor] == 32 || text[cursor] < 16)
                        end = cursor;
                    if (D_001B1668 && (unsigned int)(text[cursor] - 8) < 8)
                        style = text[cursor] - 8;
                    if (text[cursor] < 2)
                        break;
                    advance = ((signed char *)metrics)[text[cursor] * 4 + 3];
                    cursor++;
                    if (advance != 0)
                        row_width += advance;
                } while (row_width < width);
            }
            ends[count] = end;
            if (ends[count] == starts[count])
                ends[count] = cursor;
            cursor = ends[count];
            if (text[cursor] == 32 || text[cursor] < 16)
                ends[count]--;
            count++;
            if (text[cursor] == 0) {
                last_width = row_width;
                break;
            }
            cursor++;
            if (cursor == length)
                break;
        } while (text[cursor] != 0);
    }
    if (!expanded && count >= 2) {
        if (prior_count == 0)
            prior_count = count;
        if (prior_count < count) {
            width = original_width;
            expanded = 1;
            goto retry_wrap;
        }
        if (last_width < width / 3) {
            width -= 16;
            goto retry_wrap;
        }
    }
    box[6] = 0;
    box[7] = count * box[8];
    y = box[5];
    if (layout[9] & 2)
        y -= box[7] >> 1;
    for (i = 0; i < count; i++, y += box[8]) {
        int amount, pixels;
        if (y + box[8] < box[0])
            continue;
        if (y > box[1])
            continue;
        amount = ends[i] - starts[i] + 1;
        if (length > 0 && amount > length)
            amount = length;
        pixels = func_0027F128(text + starts[i], amount, metrics);
        if (box[6] < pixels)
            box[6] = pixels;
        if (!(layout[9] & 4)) {
            D_001A89B0[0] = (int)color;
            if (layout[9] & 8) {
                float x;
                if (layout[9] & 1)
                    x = (float)(box[4] - (pixels >> 1)) + (float)box[10] * 0.0625f;
                else
                    x = (float)box[4] + (float)box[10] * 0.0625f;
                func_0027F640((long)D_001A89B0[styles[i]], text + starts[i], amount,
                              texture, metrics, x, (float)y + (float)box[11] * 0.0625f, 1.0f);
            } else if (layout[9] & 1) {
                func_0027F2A8(box[4] - (pixels >> 1), y, (long)D_001A89B0[styles[i]],
                              text + starts[i], amount, texture, metrics);
            } else {
                func_0027F2A8(box[4], y, (long)D_001A89B0[styles[i]],
                              text + starts[i], amount, texture, metrics);
            }
        }
        if (length > 0) {
            length -= amount;
            if (length <= 0)
                break;
        }
    }
    D_001B166C = 0;
    if (D_001A8BB0 != 1)
        func_002FC620(0, D_001A7340 - 1, 0, D_001A7344 - 1);
}
