/* tests/test_keep_float_pun_source.py: -frac2-keep-float-pun-source, an int stored into a float
   keeps its register.  two_reads, two_helpers, three_reads, older_register, reads_in_loop and
   reads_across_branches are the cases; one_read, one_read_in_loop, read_side, plain_float,
   small_constant, double_word and pun_argument are controls.  */

extern void key(float time, float value, float a, float b, float c, char *object, int index);
extern void work(void);
extern void store_word(int word);

static inline float bits(int word)
{
    float value;

    *(int *)&value = word;
    return value;
}

/* The retail shape: the word is set after work(), moved once, and read twice.  */
void two_reads(char *object)
{
    float value;

    work();
    *(int *)&value = 0x60442D00;
    key(0.3f, value, 0.0f, 0.0f, 0.0f, object, 1);
    key(1.0f, value, 0.0f, 0.0f, 0.0f, object, 2);
}

/* The same through an inline helper: cse2 unifies the two reads.  */
void two_helpers(char *object)
{
    work();
    key(0.3f, bits(0x55F0C070), 0.0f, 0.0f, 0.0f, object, 1);
    key(1.0f, bits(0x55F0C070), 0.0f, 0.0f, 0.0f, object, 2);
}

/* Three reads give the float FP_REGS by default: reload then drops the second half.  */
void three_reads(char *object)
{
    float value;

    work();
    *(int *)&value = 0x60442D00;
    key(0.3f, value, 0.0f, 0.0f, 0.0f, object, 1);
    key(1.0f, value, 0.0f, 0.0f, 0.0f, object, 2);
    key(2.0f, value, 0.0f, 0.0f, 0.0f, object, 3);
}

/* Two reads in a loop, the word built once before it: by default reload drops the low half.  */
void reads_in_loop(char *object, int count)
{
    float value;
    int i;

    work();
    *(int *)&value = 0x60442D00;
    for (i = 0; i < count; i++) {
        key(0.3f, value, 0.0f, 0.0f, 0.0f, object, i);
        key(1.0f, value, 0.0f, 0.0f, 0.0f, object, i + 1);
    }
}

/* Reads in both arms of a branch and after it: by default the low half is lost too.  */
void reads_across_branches(char *object, int flag)
{
    float value;

    work();
    *(int *)&value = 0x55F0C070;
    if (flag)
        key(0.3f, value, 0.0f, 0.0f, 0.0f, object, 1);
    else
        key(0.5f, value, 0.0f, 0.0f, 0.0f, object, 2);
    key(1.0f, value, 0.0f, 0.0f, 0.0f, object, 3);
}

/* A control: a constant that needs no split goes through the output reload in both profiles.  */
void small_constant(char *object)
{
    float value;

    work();
    *(int *)&value = 0x1EFF;
    key(0.5f, value, 0.0f, 0.0f, 0.0f, object, 1);
    key(1.0f, value, 0.0f, 0.0f, 0.0f, object, 2);
}

/* The word is live in an older register; the store must not reuse it across calls.  */
void older_register(char *object)
{
    float value;

    store_word(0x60442D00);
    work();
    *(int *)&value = 0x60442D00;
    key(0.3f, value, 0.0f, 0.0f, 0.0f, object, 1);
    key(1.0f, value, 0.0f, 0.0f, 0.0f, object, 2);
}

/* Controls.  One read still folds to li.s, in a loop too.  */
void one_read(char *object)
{
    work();
    key(0.3f, bits(0x70202080), 0.0f, 0.0f, 0.0f, object, 1);
}

void one_read_in_loop(char *object, int count)
{
    int i;

    for (i = 0; i < count; i++)
        key(0.3f, bits(0x70202080), 0.0f, 0.0f, 0.0f, object, i);
}

/* A read-side pun has no SUBREG store: it folds as before.  */
void read_side(char *object)
{
    int word = 0x60442D00;

    work();
    key(0.3f, *(float *)&word, 0.0f, 0.0f, 0.0f, object, 1);
    key(1.0f, *(float *)&word, 0.0f, 0.0f, 0.0f, object, 2);
}

void plain_float(char *object)
{
    float value = 1.5f;

    work();
    key(0.3f, value, 0.0f, 0.0f, 0.0f, object, 1);
    key(1.0f, value, 0.0f, 0.0f, 0.0f, object, 2);
}

/* Only SFmode: a double punned through a 64-bit integer is untouched.  */
double double_word(void)
{
    double value;

    *(long long *)&value = 0x4000000000000000LL;
    return value + value;
}

/* The value keeps its bits whatever the source: not a constant here.  */
void pun_argument(char *object, int word)
{
    float value;

    work();
    *(int *)&value = word;
    key(0.3f, value, 0.0f, 0.0f, 0.0f, object, 1);
    key(1.0f, value, 0.0f, 0.0f, 0.0f, object, 2);
}
