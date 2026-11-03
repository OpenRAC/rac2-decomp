/* functional: high. Retail's FPU code in C: both compares are made on the sum before it changes (the second sits in the first branch's delay slot); pi is subtracted, or added, twice rather than 2 pi once. */

/* a + b wrapped once into [-pi, pi). */
float func_00283B98(float a, float b)
{
    float s = a + b;
    float pi = 3.14159274f;
    int below_pi = s < pi;
    int below_mpi = s < -pi;

    if (!below_pi) {
        s = s - pi;
        s = s - pi;
    }
    if (below_mpi) {
        s = s + pi;
        s = s + pi;
    }
    return s;
}
