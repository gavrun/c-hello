#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256

// Reads a line safely into buf and strips trailing newline.
// Returns 1 on success, 0 on EOF, -1 on error.
static int read_line(char *buf, size_t size) {
    if (!fgets(buf, size, stdin)) {
        if (feof(stdin)) return 0; // EOF
        return -1;                 // Error
    }
    size_t len = strlen(buf);
    if (len && buf[len - 1] == '\n') buf[len - 1] = '\0';
    else {
        // Line too long; consume rest of line
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* discard */
        }
    }
    return 1;
}

// Flushes any leftover characters on stdin until newline or EOF.
static void flush_stdin_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

// Example 1: Echo line
static void ex_echo_line(void) {
    char buf[BUF_SIZE];
    printf("Enter a line: ");
    fflush(stdout);
    int rc = read_line(buf, sizeof buf);
    if (rc == 1) printf("You entered: %s\n", buf);
    else if (rc == 0) printf("Reached EOF.\n");
    else perror("fgets");
}

// Example 2: Read an int safely with fgets + strtol
static void ex_read_int(void) {
    char buf[BUF_SIZE];
    long value;
    for (;;) {
        printf("Enter an integer: ");
        fflush(stdout);
        if (read_line(buf, sizeof buf) != 1) {
            printf("No input.\n");
            return;
        }
        char *end = NULL;
        errno = 0;
        value = strtol(buf, &end, 10);
        if (errno == ERANGE || end == buf) {
            printf("Not a valid integer, try again.\n");
            continue;
        }
        // Skip trailing spaces
        while (end && *end && isspace((unsigned char)*end)) end++;
        if (end && *end) {
            printf("Extra characters after number, try again.\n");
            continue;
        }
        break;
    }
    printf("You entered integer: %ld\n", value);
}

// Example 3: Using scanf carefully
static void ex_scanf_basics(void) {
    int a = 0, b = 0;
    printf("Enter two integers separated by space: ");
    fflush(stdout);
    int read = scanf("%d %d", &a, &b);
    if (read != 2) {
        printf("scanf couldn't read two ints (read %d).\n", read);
    } else {
        printf("Read: a=%d, b=%d\n", a, b);
    }
    flush_stdin_line(); // clear leftover input to keep stream consistent
}

// Example 4: Format specifiers
static void ex_formatting(void) {
    int i = 42;
    double d = 3.1415926535;
    const char *s = "C I/O";
    printf("int: %d, hex: 0x%X, padded: %05d\n", i, i, i);
    printf("double default: %f, 2dp: %.2f, exp: %e\n", d, d, d);
    printf("string: %s, width 10: '%10s'\n", s, s);
}

// Example 5: Re-prompt loop + cancel with empty input
static void ex_prompt_loop(void) {
    char name[BUF_SIZE];
    while (1) {
        printf("Enter your name (empty to stop): ");
        fflush(stdout);
        int rc = read_line(name, sizeof name);
        if (rc != 1) break;
        if (name[0] == '\0') break;
        printf("Hello, %s!\n", name);
    }
}

// Example 6: Reading a character command
static void ex_read_char(void) {
    printf("Proceed? [y/n]: ");
    fflush(stdout);
    int ch = getchar();
    if (ch == EOF) {
        printf("EOF encountered.\n");
        return;
    }
    printf("You typed '%c'\n", ch);
    flush_stdin_line();
}

static void print_menu(void) {
    printf("\n-- Console I/O Basics --\n");
    printf("1) Echo a line (fgets)\n");
    printf("2) Read integer (strtol)\n");
    printf("3) scanf basics (+flush)\n");
    printf("4) Formatting examples\n");
    printf("5) Prompt loop with exit\n");
    printf("6) Read single character\n");
    printf("0) Quit\n> ");
    fflush(stdout);
}

int main(void) {
    for (;;) {
        print_menu();
        char buf[BUF_SIZE];
        int rc = read_line(buf, sizeof buf);
        if (rc != 1) break;
        if (strcmp(buf, "0") == 0) break;
        else if (strcmp(buf, "1") == 0) ex_echo_line();
        else if (strcmp(buf, "2") == 0) ex_read_int();
        else if (strcmp(buf, "3") == 0) ex_scanf_basics();
        else if (strcmp(buf, "4") == 0) ex_formatting();
        else if (strcmp(buf, "5") == 0) ex_prompt_loop();
        else if (strcmp(buf, "6") == 0) ex_read_char();
        else printf("Unknown option.\n");
    }
    printf("Goodbye!\n");
    return 0;
}

