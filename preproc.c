#include <stdio.h>
#include <string.h>

// Macro constants and expressions
#define PI 3.14159265358979323846
#define BUF_SIZE 64

// Function-like macro (parenthesize params and whole expr!)
#define SQR(x) ((x) * (x))

// Stringizing and token pasting
#define STR(x) #x
#define CAT(a, b) a##b

// Conditional compilation flags (can be set with -D at compile time)
#ifndef BUILD_MODE
#define BUILD_MODE "dev"
#endif

// Header-guard pattern demo

// Inline helper controlled by feature macro
#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L
static inline int max_i(int a, int b) { return a > b ? a : b; }
#else
static int max_i(int a, int b) { return a > b ? a : b; }
#endif
#endif

// Pragmas and diagnostic controls are compiler-specific; avoid in portable code.

// Demonstrate macro pitfalls and safe patterns
static void macro_demos(void) {
    int a = 3 + 1;
    printf("SQR(%s) with a=3+1 -> %d (correct due to parentheses)\n", STR(3+1), SQR(a));

    int xy = 42;
    printf("Token pasting CAT(x, y) refers to variable named 'xy': %d\n", CAT(x, y));

    char buf[BUF_SIZE];
    snprintf(buf, sizeof buf, "pi~%.2f, mode=%s", (double)PI, BUILD_MODE);
    printf("BUF_SIZE=%d, %s\n", (int)sizeof buf, buf);
}

// Conditional compilation demonstration
static void conditional_demo(void) {
#if defined(NDEBUG)
    printf("Compiled with NDEBUG (asserts disabled).\n");
#else
    printf("Compiled without NDEBUG (asserts enabled).\n");
#endif

#ifdef _WIN32
    printf("Platform: Windows\n");
#elif defined(__APPLE__)
    printf("Platform: macOS\n");
#elif defined(__linux__)
    printf("Platform: Linux\n");
#else
    printf("Platform: unknown\n");
#endif
}

// Include guards explanation (conceptual example, not code):
// In headers, use:
//   #ifndef MY_HEADER_H
//   #define MY_HEADER_H
//   /* declarations */
//   #endif
// or modern:
//   #pragma once  // non-standard but widely supported

int main(void) {
    puts("-- Preprocessor Basics --");
    macro_demos();

    puts("\n-- Conditional Compilation --");
    conditional_demo();

    puts("\n-- Build Flags --");
    printf("BUILD_MODE=%s (change with -DBUILD_MODE=\"prod\")\n", BUILD_MODE);
    printf("Define NDEBUG to disable asserts: add -DNDEBUG to CFLAGS.\n");
    printf("Define feature flags: e.g., -DENABLE_X=1 and use #ifdef ENABLE_X.\n");

    return 0;
}

