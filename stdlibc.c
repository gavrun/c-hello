#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <locale.h>
#include <math.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Error handling with errno + perror/strerror
static void error_handling_demo(void) {
    FILE *f = fopen("/path/that/does/not/exist", "r");
    if (!f) {
        // errno set by fopen on failure
        fprintf(stderr, "fopen failed: %s (errno=%d)\n", strerror(errno), errno);
        perror("perror says");
    } else {
        fclose(f);
    }
}

// Environment variables and program arguments style helpers
static void env_vars_demo(void) {
    const char *user = getenv("USER");
    printf("$USER = %s\n", user ? user : "(not set)");

    // setenv/putenv availability varies; setenv is POSIX. Use if present.
#ifdef _POSIX_VERSION
    setenv("DEMO_VAR", "42", 1);
    printf("$DEMO_VAR = %s\n", getenv("DEMO_VAR"));
    unsetenv("DEMO_VAR");
#endif
}

// String conversions: strtol/strtoul/strtod with error checks
static void strto_demo(void) {
    const char *s = "1234x";
    char *end = NULL;
    errno = 0;
    long v = strtol(s, &end, 10);
    printf("strtol('%s') -> v=%ld, stopped at '%s', errno=%d\n",
           s, v, end && *end ? end : "\\0", errno);

    const char *f = "3.14e2";
    errno = 0; end = NULL;
    double d = strtod(f, &end);
    printf("strtod('%s') -> d=%f, rest='%s'\n", f, d, end && *end ? end : "");
}

// Character classification and case conversion
static void ctype_demo(void) {
    const char *txt = "Az09!? ";
    for (const unsigned char *p = (const unsigned char*)txt; *p; ++p) {
        printf("'%c': isalpha=%d isdigit=%d isspace=%d toupper=%c\n",
               *p, isalpha(*p), isdigit(*p), isspace(*p), toupper(*p));
    }
}

// Memory utilities: memset, memcpy, memmove, memcmp
static void memory_utils_demo(void) {
    char buf[16];
    memset(buf, '-', sizeof buf);
    buf[15] = '\0'; // make it a string for printing
    printf("memset: '%s'\n", buf);

    char src[] = "Hello, world";
    memcpy(buf, src, strlen(src) + 1);
    printf("memcpy: '%s'\n", buf);

    // memmove safe for overlapping regions
    memmove(buf + 2, buf, 5); // shift "Hello" two chars right
    buf[7] = '\0';
    printf("memmove overlap -> '%s'\n", buf);

    printf("memcmp('abc','abd',3) = %d\n", memcmp("abc", "abd", 3));
}

// Time and date: time(), localtime(), strftime()
static void time_demo(void) {
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);
    char out[64];
    if (lt && strftime(out, sizeof out, "%Y-%m-%d %H:%M:%S", lt)) {
        printf("local time: %s\n", out);
    }
}

// Random numbers: srand/rand (note: for real randomness prefer better APIs)
static void rand_demo(void) {
    srand((unsigned)time(NULL));
    printf("rand: %d %d %d\n", rand(), rand(), rand());
}

// Variable argument functions (va_list)
static void logf_simple(const char *level, const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    printf("[%s] ", level);
    vprintf(fmt, ap);
    printf("\n");
    va_end(ap);
}

// Math library basics (need to link with -lm on some systems)
static void math_demo(void) {
    double x = 2.0;
    printf("sqrt(2)=%.6f, pow(2,10)=%.0f, fabs(-3.5)=%.1f\n",
           sqrt(x), pow(2.0, 10.0), fabs(-3.5));
}

// Assert usage for defensive programming
static int divide_checked(int a, int b) {
    assert(b != 0 && "b must not be zero");
    return a / b;
}

// Locale example (affects ctype and formatting)
static void locale_demo(void) {
    const char *prev = setlocale(LC_ALL, NULL);
    printf("current locale: %s\n", prev ? prev : "(null)");
    // Try setting to user default environment
    setlocale(LC_ALL, "");
    printf("after setlocale(\"\"): %s\n", setlocale(LC_ALL, NULL));
}

int main(void) {
    puts("-- libc: error handling --");
    error_handling_demo();

    puts("\n-- libc: env vars --");
    env_vars_demo();

    puts("\n-- libc: strto* conversions --");
    strto_demo();

    puts("\n-- libc: ctype --");
    ctype_demo();

    puts("\n-- libc: memory utils --");
    memory_utils_demo();

    puts("\n-- libc: time/date --");
    time_demo();

    puts("\n-- libc: rand --");
    rand_demo();

    puts("\n-- libc: varargs --");
    logf_simple("INFO", "Pi approx: %.2f", 3.14159);

    puts("\n-- libc: math --");
    math_demo();

    puts("\n-- libc: assert --");
    printf("divide_checked(8,2) = %d\n", divide_checked(8,2));
    // divide_checked(1,0); // would abort in debug builds

    puts("\n-- libc: locale --");
    locale_demo();

    return 0;
}

