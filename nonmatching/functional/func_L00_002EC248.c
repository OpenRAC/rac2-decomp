/* functional: medium. Plain C written from the assembly. The argument types of the callees are the same as other callers declare; the floats are taken in the order retail uses them. */
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void func_00283098(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_00282C88(void *);
extern int func_00283D38(int, int, float);
extern void func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Emits `count` particles for the object: each gets a random velocity vector (func_002A7A00 with 0 and f12, turned by matrix a1) and a spread vector (f13, turned by matrix a2 and the object's matrix at +192), a random size, and a colour pair chosen by `mode` (1 to 3, otherwise the default); each is sent on to func_002BAA28 with the flag word 0x1003C. */
void func_L00_002EC248(void *object, void *matrix_a, void *matrix_b, int count, int mode,
                       float speed, float spread, float jitter, float rate, float scale)
{
    float velocity[4], spread_v[4], aux[4];
    float step = rate * 0.000277777785f;
    int flags = 0x1003C;

    if (count <= 0) {
        return;
    }
    do {
        float size, big;
        int r0, r1, r2, colour_a, colour_b;

        func_002A7A00(velocity, 0.0f, speed);
        func_00282CC0(velocity, velocity, matrix_a);
        func_L00_00324F18(object, velocity, velocity[0], velocity[1], velocity[2]);
        func_002A7A00(spread_v, 0.0f, spread);
        func_00282CC0(spread_v, spread_v, matrix_b);
        func_00283098(spread_v, spread_v, (char *)object + 192);
        size = scale * func_002A7878(0.5f, 1.5f);
        big = size * 10.0f;
        r0 = func_00283CF0(big);
        r1 = func_00283CF0(size * 40.0f);
        r2 = func_00283CF0(big);
        ((float *)spread_v)[3] = jitter * func_002A7878(0.1f, 0.4f);
        func_00282C88(aux);
        aux[2] = -step * (float)(r0 + r1 + r2);
        func_00282CC0(aux, aux, spread_v);
        switch (mode & 0xFF) {
        case 1:
            colour_a = func_00283D38(0x80102040, 0x801010A0, func_002A7878(0.0f, 1.0f));
            colour_b = func_00283D38(0x00102040, 0x001010A0, func_002A7878(0.0f, 1.0f));
            break;
        case 2:
            colour_a = func_00283D38(0x80104010, 0x8020A020, func_002A7878(0.0f, 1.0f));
            colour_b = func_00283D38(0x00104010, 0x0020A020, func_002A7878(0.0f, 1.0f));
            break;
        case 3:
            colour_a = func_00283D38(0x80201608, 0x80402510, func_002A7878(0.0f, 1.0f));
            colour_b = func_00283D38(0x00201608, 0x00402510, func_002A7878(0.0f, 1.0f));
            break;
        default:
            colour_a = func_00283D38(0x80004080, 0x80408080, func_002A7878(0.0f, 1.0f));
            colour_b = func_00283D38(0x00004080, 0x00408080, func_002A7878(0.0f, 1.0f));
            break;
        }
        func_002BAA28(velocity, spread_v, aux, colour_a, colour_b, r0, r1, r2, flags);
    } while (--count != 0);
}
