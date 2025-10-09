#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Function declarations (prototypes)
int add(int a, int b);
int max3(int a, int b, int c);
unsigned long long fact_iter(unsigned int n);
unsigned long long fact_rec(unsigned int n);
int abs_i(int x);
bool is_even(int x);
int clamp(int x, int lo, int hi);
int sum_array(const int *arr, size_t n);
void swap(int *a, int *b);

// Function definitions
int add(int a, int b) { return a + b; }

int max3(int a, int b, int c) {
    int m = a;
    if (b > m) m = b;      // if statement
    if (c > m) m = c;      // chained comparisons
    return m;
}

unsigned long long fact_iter(unsigned int n) {
    unsigned long long r = 1ULL;
    for (unsigned int i = 2; i <= n; ++i) { // for loop
        r *= i;
    }
    return r;
}

unsigned long long fact_rec(unsigned int n) { // recursion
    if (n <= 1) return 1ULL;                  // base case
    return n * fact_rec(n - 1);
}

int abs_i(int x) { return x < 0 ? -x : x; } // conditional (ternary) operator

bool is_even(int x) { return (x & 1) == 0; } // bit trick for even/odd

int clamp(int x, int lo, int hi) {
    if (lo > hi) { // guard clause
        int tmp = lo; lo = hi; hi = tmp;
    }
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}

int sum_array(const int *arr, size_t n) {
    int s = 0;
    size_t i = 0;
    while (i < n) { // while loop
        s += arr[i++];
    }
    return s;
}

void swap(int *a, int *b) {
    if (!a || !b) return; // pointer null-check
    int t = *a; *a = *b; *b = t;
}

// Demonstration of switch, loops, and early returns
static void control_flow_demos(void) {
    // switch examples
    for (int day = 1; day <= 8; ++day) {
        const char *name;
        switch (day) {
            case 1: name = "Mon"; break;
            case 2: name = "Tue"; break;
            case 3: name = "Wed"; break;
            case 4: name = "Thu"; break;
            case 5: name = "Fri"; break;
            case 6: // fallthrough
            case 7: name = "Weekend"; break;
            default: name = "?"; break; // default branch
        }
        printf("Day %d -> %s\n", day, name);
    }

    // break / continue
    printf("First 10 odd numbers: ");
    int count = 0;
    for (int x = 0; ; ++x) {
        if (x % 2 == 0) continue; // skip evens
        printf("%d ", x);
        if (++count == 10) break;  // stop after 10 odds
    }
    printf("\n");
}

// Demonstrate functions and basic patterns
static void function_demos(void) {
    printf("add(2, 3) = %d\n", add(2, 3));
    printf("max3(7, -4, 5) = %d\n", max3(7, -4, 5));
    printf("abs_i(-42) = %d\n", abs_i(-42));
    printf("is_even(10) = %s\n", is_even(10) ? "true" : "false");
    printf("clamp(15, 0, 10) = %d\n", clamp(15, 0, 10));

    unsigned int n = 10;
    printf("fact_iter(%u) = %llu\n", n, fact_iter(n));
    printf("fact_rec(%u) = %llu\n", n, fact_rec(n));

    int arr[] = {1, 2, 3, 4, 5};
    printf("sum_array([1..5]) = %d\n", sum_array(arr, sizeof arr / sizeof arr[0]));

    int a = 5, b = 9;
    printf("before swap: a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("after  swap: a=%d, b=%d\n", a, b);
}

int main(void) {
    printf("-- Control Flow Demos --\n");
    control_flow_demos();

    printf("\n-- Function Demos --\n");
    function_demos();

    return 0;
}

