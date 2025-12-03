// include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _gf_opts_version() ;
void _gf_opts_help() ;
void _gf_opts_url() ;

// main
int main(
        int argc,
        char *optv[]
        )
{
    int i ;
    for (
            i = 1 ;
            i < argc;
            i++
        )
        printf(
                "%s\n",
                optv[i]);

    if (strncmp(optv[1], "version", 100) == 0)
        _gf_opts_version() ;
    else
        printf("other\n") ;

    return 0 ;
}


// opts
void _gf_opts_version()
{
    printf("version\n") ;
}

void _gf_opts_help()
{
    printf("help\n") ;
}

void _gf_opts_url()
{
    FILE *fp ;
    char buffer[80] ;
    fp = popen("ls -lhA --color", "r") ;
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        printf("%s", buffer) ;
    }
    pclose(fp) ;
}