/* -frac2-fix-scratch-reuse control: two float-to-int truncations in one block. Stock reload
   gives the second one's (never emitted) integer scratch the first free register; with the
   switch it reuses the first truncation's scratch. */
extern float scale;
extern int out[8];

void control(float x, float y, int a, int b, int c)
{
    int t0 = a * b;
    out[0] = (int)(x * scale);
    out[1] = t0;
    out[7] = (int)(y * scale);
}
