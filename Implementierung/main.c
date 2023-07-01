#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

#include "conversion.h"

const char *usage_msg =
        "Usage: %s [options] <number>\n"
        "       %s [options] <real>,<imaginary>\n"
        "       %s -V<version> -B<repetitions> <number>\n"
        "       %s -V<version> -B<repetitions> <real>,<imaginary>\n"
        "       %s -h | --help\n";

const char *help_msg =
        "Positional arguments:\n"
        "       <number>            Interpret the number as a number in base (- 1 + i) and call to_carthesian\n"
        "  or:  <real>,<imaginary>  Interpret the number as a complex number and call to_bm1pi\n"
        "\n"
        "Optional arguments:\n"
        "  -V<version>              Specify the implementation version (default: 0)\n"
        "  -B<repetitions>          Measure and output the runtime of the specified implementation\n"
        "                           with the given number of repetitions\n"
        "  -h, --help               Show this help message and exit\n";

void print_usage(const char *program_name) {
    fprintf(stderr, usage_msg, program_name, program_name, program_name, program_name, program_name);
}

void print_help(const char *program_name) {
    print_usage(program_name);
    fprintf(stderr, "\n%s", help_msg);
}

void print_uint128_binary(unsigned __int128 num, bool leading_zeros) {
    if (num == 0) {
        printf("0\n");
        return;
    }

    unsigned __int128 mask = (unsigned __int128) 1 << 127;

    for (int i = 0; i < 128; ++i, mask >>= 1) {
        if (num & mask) {
            leading_zeros = 1;
            printf("1");
        } else if (leading_zeros) {
            printf("0");
        }
    }
    printf("\n");
}

void malloc_failed() {
    fprintf(stderr, "Malloc failed. Exiting.\n");
    exit(EXIT_FAILURE);
}

// TODO: implement tests
unsigned tests(size_t repetitions) {
    unsigned failed = 0;

    return failed;
}

// DONE: implementation of different modes and according parameters, and also help
int main(int argc, char **argv) {

    const char *program_name = argv[0];

    if (argc == 1) {
        print_usage(program_name);
        return EXIT_FAILURE;
    }

    size_t version = 0;
    size_t repetitions = 0;

    //it could be that a positional argument with a negative number is in argv
    //before getopt_long takes it as an option because of the starting '-' check if it seems to have the correct format -number...
    //if so set it as positional argument, remove it from argv and skip setting it later by checking if p_arg is not NULL
    //else it's an invalid option don't touch it
    const char *p_arg = NULL;
    for (int i = 0; i < argc; ++i) {
        if (strlen(argv[i]) > 1 && argv[i][0] == '-' && argv[i][1] >= '0' && argv[i][1] <= '9') {
            p_arg = argv[i];
            argv[i] = "";
            break;
        }
    }

    int opt;
    struct option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {0, 0,                0, 0}
    };

    while ((opt = getopt_long(argc, argv, "V:B:h", long_options, NULL)) != -1) {
        switch (opt) {
            case 'V':
                version = atol(optarg);
                break;
            case 'B':
                repetitions = atol(optarg);
                break;
            case 'h':
                print_help(program_name);
                return EXIT_SUCCESS;
            default:
                print_usage(program_name);
                return EXIT_FAILURE;
        }
    }

    if (optind >= argc) {
        printf("%s: Missing positional argument -- 'number' or 'real,imaginary'\n", program_name);
        print_usage(program_name);
        return EXIT_FAILURE;
    }

    if (optind < argc - 1) {
        printf("%s: only one positional argument -- 'number' or 'real,imaginary' is expected\n", program_name);
        print_usage(program_name);
        return EXIT_FAILURE;
    }

    //parsing the positional argument, set it if not already set
    if (p_arg == NULL) p_arg = argv[optind];
    char *comma_pos = strchr(p_arg, ',');
    bool is_bm1pi = (comma_pos == NULL);


    unsigned __int128 bm1pi;
    __int128 real = 0;
    __int128 imag = 0;

    if (is_bm1pi) {
        // String is a single number

        // TODO: discuss if this is needed or too restrictive. (unary negation can also be interpreted)
        if (p_arg[0] == '-') {
            fprintf(stderr, "Wrong Format, a number in basis (-1+i) is unsigned. Exiting.\n");
            print_usage(program_name);
            return EXIT_FAILURE;
        }

        char *endptr = NULL;
        bm1pi = (unsigned __int128) strtoull(p_arg, &endptr, 2);
        if (endptr < p_arg + strlen(p_arg)) {
            fprintf(stderr, "Wrong Format, a number in basis (-1+i) consists only of '1' and '0'. Exiting.\n");
            print_usage(program_name);
            return EXIT_FAILURE;
        }
        to_carthesian(bm1pi, &real, &imag);
        printf("%lld%c%lldi\n", (long long) real, (imag < 0 ? '\0' : '+'), (long long) imag);
    } else {
        // String contains a comma, treat it as "real,imag"
        char *realStr = malloc((comma_pos - p_arg + 1) * sizeof(char));
        if (!realStr) malloc_failed();
        strncpy(realStr, p_arg, comma_pos - p_arg);
        realStr[comma_pos - p_arg] = '\0';

        char *imagStr = malloc((strlen(comma_pos)) * sizeof(char));
        if (!imagStr) malloc_failed();
        strcpy(imagStr, comma_pos + 1);

        char *endptr_real = NULL, *endptr_imag = NULL;
        real = (__int128) strtoll(realStr, &endptr_real, 10);
        imag = (__int128) strtoll(imagStr, &endptr_imag, 10);
        if ((endptr_real < realStr + strlen(realStr)) || (endptr_imag < imagStr + strlen(imagStr))) {
            fprintf(stderr, "Wrong Number Format. Exiting.\n");
            print_usage(program_name);
            return EXIT_FAILURE;
        }

        bm1pi = to_bm1pi(real, imag);
        print_uint128_binary(bm1pi, false);

        free(realStr);
        free(imagStr);
    }

    //TODO: Implement different program flow if options -V and -B are set.

    return EXIT_SUCCESS;
}
