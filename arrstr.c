#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN(x) (sizeof(x)/sizeof((x)[0]))

// Print an int array
static void print_int_array(const int *a, size_t n, const char *label) {
    printf("%s[", label ? label : "");
    for (size_t i = 0; i < n; ++i) {
        printf("%d%s", a[i], (i + 1 < n) ? ", " : "");
    }
    printf("]\n");
}

// Basic array initialization, iteration, and modification
static void array_basics(void) {
    int a[5] = {1,2,3,4,5};
    print_int_array(a, LEN(a), "start: ");

    // Modify elements
    for (size_t i = 0; i < LEN(a); ++i) a[i] *= 2;
    print_int_array(a, LEN(a), "doubled: ");

    // Partial initialization: missing elements become 0
    int b[5] = {10, 20};
    print_int_array(b, LEN(b), "partial: ");

    // Designated initializers (C99)
    int c[6] = {[0]=7, [5]=42};
    print_int_array(c, LEN(c), "designated: ");
}

// Multidimensional arrays
static void multi_arrays(void) {
    int m[2][3] = {
        {1,2,3},
        {4,5,6}
    };
    printf("matrix 2x3:\n");
    for (size_t r = 0; r < LEN(m); ++r) {
        for (size_t c = 0; c < LEN(m[0]); ++c) {
            printf("%d ", m[r][c]);
        }
        printf("\n");
    }
}

// Passing arrays to functions (decay to pointer) and size parameter
static int sum_array(const int *a, size_t n) {
    int s = 0; for (size_t i = 0; i < n; ++i) s += a[i]; return s;
}

// String basics: literals, arrays, and safety
static void string_basics(void) {
    // String literal (read-only storage). Do not modify.
    const char *hello = "hello";
    printf("literal: %s (len=%zu)\n", hello, strlen(hello));

    // Mutable char array initialized from literal (includes NUL terminator)
    char buf[16] = "world"; // capacity 16, length 5
    size_t len = strlen(buf);
    printf("buf: '%s' (len=%zu, cap=%zu)\n", buf, len, LEN(buf));

    // Safe concatenation with bound checks using strncat-like pattern
    const char *suffix = "!!!";
    size_t cap = LEN(buf);
    size_t avail = cap - len - 1; // keep space for NUL
    strncat(buf, suffix, avail);
    printf("concat: '%s'\n", buf);

    // Copying safely with snprintf (avoids non-terminated copies)
    char dst[8];
    snprintf(dst, sizeof dst, "%s-%s", "ab", "cdEFGH");
    printf("snprintf: '%s'\n", dst);
}

// Reading a line safely into buffer
static int read_line(char *buf, size_t size) {
    if (!fgets(buf, size, stdin)) return 0;
    size_t n = strlen(buf);
    if (n && buf[n-1] == '\n') buf[n-1] = '\0';
    else { int ch; while ((ch = getchar()) != '\n' && ch != EOF) {} }
    return 1;
}

// Tokenizing strings using strtok (and a safer alternative demo)
static void tokenize_demo(void) {
    char line[64] = "one,two;three four";
    const char *delims = ",; ";
    printf("strtok tokens: ");
    for (char *tok = strtok(line, delims); tok; tok = strtok(NULL, delims)) {
        printf("[%s] ", tok);
    }
    printf("\n");

    // Safer iteration without modifying original using a copy
    const char *text = "alpha beta gamma";
    char copy[64];
    snprintf(copy, sizeof copy, "%s", text);
    printf("copy tokens: ");
    for (char *tok = strtok(copy, " "); tok; tok = strtok(NULL, " ")) {
        printf("{%s} ", tok);
    }
    printf("\n");
}

// Arrays of strings (array of pointers)
static void array_of_strings(void) {
    const char *colors[] = {"red", "green", "blue"};
    for (size_t i = 0; i < LEN(colors); ++i) {
        printf("color[%zu]=%s (len=%zu)\n", i, colors[i], strlen(colors[i]));
    }
}

// Sorting an int array using qsort
static int cmp_int_asc(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

static void sort_with_qsort(void) {
    int arr[] = {5,2,9,1,5,6};
    printf("before sort: ");
    print_int_array(arr, LEN(arr), "");
    qsort(arr, LEN(arr), sizeof arr[0], cmp_int_asc);
    printf("after  sort: ");
    print_int_array(arr, LEN(arr), "");
}

int main(void) {
    puts("-- Array Basics --");
    array_basics();
    int demo[] = {1,2,3,4,5};
    printf("sum_array = %d\n", sum_array(demo, LEN(demo)));

    puts("\n-- Multidimensional --");
    multi_arrays();

    puts("\n-- String Basics --");
    string_basics();

    puts("\n-- Tokenizing --");
    tokenize_demo();

    puts("\n-- Array of Strings --");
    array_of_strings();

    puts("\n-- qsort --");
    sort_with_qsort();

    return 0;
}

