extern float func_0034A4E0(char *object, int type, int *columns, int *rows, float *spacing, int *xOffset, int *yOffset, int *flag, float *extra);

void func_0034A808(char *object, int type, int value, float *x, float *y, float *size, int *mode)
{
    int quadrant = value % 4;
    int row = value >> 2;
    float vertical = 0.0f;
    int columns = 0;
    int rows = 0;
    float spacing = 0.0f;
    int xOffset = 0;
    int yOffset = 0;
    int flag = 0;
    float extra = 0.0f;
    *size = func_0034A4E0(object, type, &columns, &rows, &spacing, &xOffset, &yOffset, &flag, &extra);
    *x = row % columns;
    if (row >= columns)
        vertical = 1.0f;
    *y = vertical;
    flag = row >= columns;
    *x *= *size;
    *x += *x;
    *x *= spacing;
    *y *= *size;
    *y += *y;
    *y *= spacing;
    *x += (float)xOffset;
    *y += (float)yOffset;
    switch (quadrant) {
    case 0:
        *mode = 0;
        break;
    case 1:
        *mode = 2;
        *y += *size + extra;
        break;
    case 2:
        *mode = 1;
        *x += *size + extra;
        break;
    case 3:
        *mode = 3;
        *x += *size + extra;
        *y += *size + extra;
        break;
    }
    *x += (float)(flag << 1);
}
