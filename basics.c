#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Show core integer and floating types with sizes and ranges conceptually
static void data_types(void) {
    printf("-- Data Types --\n");
    printf("bool:        %zu byte(s)\n", sizeof(bool));
    printf("char:        %zu\n", sizeof(char));
    printf("short:       %zu\n", sizeof(short));
    printf("int:         %zu\n", sizeof(int));
    printf("long:        %zu\n", sizeof(long));
    printf("long long:   %zu\n", sizeof(long long));
    printf("float:       %zu\n", sizeof(float));
    printf("double:      %zu\n", sizeof(double));
    printf("long double: %zu\n", sizeof(long double));
    printf("int8_t:      %zu, uint64_t: %zu\n", sizeof(int8_t), sizeof(uint64_t));
}

// Demonstrate basic operators
static void operators_demo(void) {
    printf("\n-- Operators --\n");
    int a = 7, b = 3;
    printf("a+b=%d a-b=%d a*b=%d a/b=%d a%%b=%d\n", a+b, a-b, a*b, a/b, a%b);
    printf("++a=%d, b++=%d (then b=%d)\n", ++a, b++, b);
    int x = 0b1010, y = 0b0110; // C23 binary literal; many compilers support as ext
    printf("bitwise: x&y=%d x|y=%d x^y=%d ~x=%d x<<1=%d x>>1=%d\n",
           x&y, x|y, x^y, ~x, x<<1, x>>1);
    int c = 5; c += 2; c *= 3; // compound assignment
    printf("compound c=%d, ternary: %d\n", c, (c>10?1:0));
}

// Control flow essentials
static void control_flow(void) {
    printf("\n-- Control Flow --\n");
    int n = 5;
    if (n > 0) {
        printf("if: n is positive\n");
    } else if (n == 0) {
        printf("if/else: n is zero\n");
    } else {
        printf("if/else: n is negative\n");
    }

    printf("for: ");
    for (int i = 0; i < 5; ++i) printf("%d ", i);
    printf("\n");

    int i = 0; printf("while: ");
    while (i < 3) { printf("%d ", i++); }
    printf("\n");

    i = 0; printf("do-while: ");
    do { printf("%d ", i++); } while (i < 2);
    printf("\n");

    int day = 6; // switch with fallthrough
    switch (day) {
        case 1: printf("Mon\n"); break;
        case 2: printf("Tue\n"); break;
        case 3: printf("Wed\n"); break;
        case 4: printf("Thu\n"); break;
        case 5: printf("Fri\n"); break;
        case 6: // fallthrough
        case 7: printf("Weekend\n"); break;
        default: printf("?\n"); break;
    }
}

// Basic I/O
static void basic_io(void) {
    printf("\n-- Basic I/O --\n");
    int a = 0; double d = 0.0; char s[32];
    printf("Enter an int, a double, and a word: ");
    if (scanf("%d %lf %31s", &a, &d, s) == 3) {
        printf("You entered: a=%d d=%.2f s='%s'\n", a, d, s);
    } else {
        printf("Input parse failed.\n");
        // Clear line to keep stdin in good state
        int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
}

// Functions and pass-by-value semantics
static int square(int v) { return v*v; }

static void functions_demo(void) {
    printf("\n-- Functions --\n");
    int z = 6;
    printf("square(%d)=%d\n", z, square(z));
}

int main(void) {
    data_types();
    operators_demo();
    control_flow();
    basic_io();
    functions_demo();
    return 0;
}

