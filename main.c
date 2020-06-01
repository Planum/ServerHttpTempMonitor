#include <stdio.h>

#include "argtable3.h"

/* global arg_xxx structs */
struct arg_lit *help, *version;
struct arg_int *level;
struct arg_end *end;

int main(int argc, char *argv[])
{
    /* the global arg_xxx structs are initialised within the argtable */
    void *argtable[] = {
        help    = arg_litn("h", "help", 0, 1, "display this help and exit"),
        version = arg_litn("v", "version", 0, 1, "display version info and exit"),
        level   = arg_intn("l", "level", "<n>", 0, 1, "foo value"),
        end     = arg_end(20),
    };

    int exitcode = 0;
    char progname[] = "ServerHttpTempMonitor";

    int nerrors;
    nerrors = arg_parse(argc,argv,argtable);

    /* special case: '--help' takes precedence over error reporting */
    if (help->count > 0)
    {
        printf("Usage: %s", progname);
        arg_print_syntax(stdout, argtable, "\n");
        printf("Demonstrate command-line parsing in argtable3.\n\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
        exitcode = 0;
        goto exit;
    }


    if (version->count > 0)
    {
       printf("Verion: 0.01 \n");
       exitcode = 0;
       goto exit;
    }

    /* If the parser returned any errors then display them and exit */
    if (nerrors > 0)
    {
        /* Display the error details contained in the arg_end struct.*/
        arg_print_errors(stdout, end, progname);
        printf("Try '%s --help' for more information.\n", progname);
        exitcode = 1;
        goto exit;
    }




exit:
    /* deallocate each non-null entry in argtable[] */
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return exitcode;
}
