#include <stdio.h>

#include "argtable3.h"
#include "cmd.h"




int main(int argc, char *argv[])
{

    /* the global arg_xxx structs are initialised within the argtable */
    void *argtable[] = {
        help    = arg_litn(NULL, "help", 0, 1, "display this help and exit"),
        version = arg_litn(NULL, "version", 0, 1, "display version info and exit"),
	    port    = arg_intn(NULL, "port", "<n>", 0, 1, "add port number for web server"),
        level   = arg_intn(NULL, "level", "<n>", 0, 2, "foo value"),
		host 	= arg_str0(NULL,"host","<ip_adress>","Ip adress host"),
        end     = arg_end(10),
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
        printf("Command line usage:\n\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		printf("\n");
        exitcode = 0;
        goto exit;
    }


    if (version->count > 0)
    {
       printf("Verion: 0.01 \n");
       exitcode = 0;
       goto exit;
    }
	
	if (port->count > 0)
    {
       printf("Port: %d \n",port->ival[0]);
       exitcode = 0;
       goto exit;
    }
	
	if (host->count > 0)
    {
       printf("Host: %s \n",host->sval[0]);
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

      /* special case: uname with no command line options induces brief help */
    if (argc==1)
    {
        printf("Try '%s --help' for more information.\n",progname);
        exitcode=0;
        goto exit;
    }




exit:
    /* deallocate each non-null entry in argtable[] */
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return exitcode;
}
