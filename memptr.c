#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// Swap using pointers
static void swap(int *a, int *b) {
    if (!a || !b) return;
    int t = *a; *a = *b; *b = t;
}

static void pointer_basics(void) {
    int x = 42;
    int *px = &x;                 // pointer to int
    printf("x=%d, &x=%p, px=%p, *px=%d\n", x, (void*)&x, (void*)px, *px);

    *px = 100;                    // mutate via pointer
    printf("after *px=100 -> x=%d\n", x);

    int y = 5;
    int *py = &y;
    int **ppy = &py;              // pointer to pointer
    printf("y=%d, *py=%d, **ppy=%d\n", y, *py, **ppy);

    int q = 5;
    int r = 25;
    printf("Before: q=%d, r=%d\n", q, r);
    swap(&q, &r);                   // swap using pointers
    printf("After: q=%d, r=%d\n", q, r);
}

static void dynamic_memory(void) {
    size_t n = 5;
    int *arr = malloc(n * sizeof *arr); // uninitialized
    if (!arr) { perror("malloc"); return; }
    for (size_t i = 0; i < n; ++i) arr[i] = (int)(i + 1);
    printf("malloc arr: ");
    for (size_t i = 0; i < n; ++i) printf("%d ", arr[i]);
    printf("\n");

    // Grow with realloc
    size_t new_n = 8;
    int *tmp = realloc(arr, new_n * sizeof *arr);
    if (!tmp) { // realloc failure handling; original ptr still valid
        perror("realloc");
        free(arr);
        return;
    }
    arr = tmp;
    for (size_t i = n; i < new_n; ++i) arr[i] = (int)((i + 1) * 10);
    printf("realloc arr: ");
    for (size_t i = 0; i < new_n; ++i) printf("%d ", arr[i]);
    printf("\n");

    free(arr); // always free what you malloc
}

static void calloc_zero_init(void) {
    size_t n = 4;
    int *z = calloc(n, sizeof *z); // zero-initialized
    if (!z) { perror("calloc"); return; }
    printf("calloc zeros: ");
    for (size_t i = 0; i < n; ++i) printf("%d ", z[i]);
    printf("\n");
    free(z);
}

// Demonstrate pointer arithmetic with arrays
static void pointer_arithmetic(void) {
    int a[] = {10, 20, 30, 40};
    int *p = a; // array decays to pointer to first element
    printf("pointer arithmetic: ");
    for (size_t i = 0; i < sizeof a / sizeof a[0]; ++i) {
        printf("%d ", *(p + i)); // same as a[i]
    }
    printf("\n");
}

// Safe string duplication example
static char *safe_strdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *p = malloc(len);
    if (!p) return NULL;
    memcpy(p, s, len);
    return p;
}

static void ownership_and_lifetimes(void) {
    char *name = safe_strdup("Alice"); // heap-allocated copy
    if (!name) { perror("malloc"); return; }
    printf("name='%s' at %p\n", name, (void*)name);
    free(name); // release ownership

    // Dangling pointer demo (don’t do this)
    int *dangling = malloc(sizeof *dangling);
    if (!dangling) { perror("malloc"); return; }
    *dangling = 7;
    free(dangling);
    // dangling now invalid; set to NULL after free
    dangling = NULL;
}

// Demonstrate const-correctness
static int sum_const(const int *arr, size_t n) {
    int s = 0;
    for (size_t i = 0; i < n; ++i) s += arr[i];
    return s;
}

// Out-parameter pattern
static bool try_parse_int(const char *s, int *out) {
    if (!s || !out) return false;
    char *end = NULL;
    long v = strtol(s, &end, 10);
    if (end == s || *end != '\0') return false;
    *out = (int)v;
    return true;
}

// Struct and pointer example
struct Point { int x, y; };

static void move_point(struct Point *p, int dx, int dy) {
    if (!p) return;
    p->x += dx;
    p->y += dy;
}

int main(void) {
    puts("-- Pointer Basics --"); 
    pointer_basics();

    puts("\n-- Dynamic Memory --");
    dynamic_memory();
    calloc_zero_init();

    puts("\n-- Pointer Arithmetic --");
    pointer_arithmetic();

    puts("\n-- Ownership & Lifetimes --");
    ownership_and_lifetimes();

    puts("\n-- Const Correctness & Out params --");
    int arr[] = {1,2,3,4};
    printf("sum_const = %d\n", sum_const(arr, sizeof arr / sizeof arr[0]));
    int out = 0; 
    printf("try_parse_int('123') -> %s, out=%d\n",
            try_parse_int("123", &out) ? "true" : "false", out);

    puts("\n-- Struct Pointers --");
    struct Point pt = { .x = 1, .y = 2 };
    move_point(&pt, 3, -1);
    printf("Point(%d, %d)\n", pt.x, pt.y);

    return 0;
}

