// include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libnotify/notify.h>



// function
void _gf_opts_version();
void _gf_opts_help();



// main
int main(
        int _gi_args_main,
        char *_gc_args_main[]
        )
{
    if (_gi_args_main < 2)
    {
        printf("\n\033[31mERROR: Empty option.\033[0m\n\n");
    }
    else if (
            strncmp(
                _gc_args_main[1],
                "-v",
                sizeof(_gc_args_main[1])
                ) == 0 ||
            strncmp(
                _gc_args_main[1],
                "--version",
                sizeof(_gc_args_main[1])
                ) == 0
            )
    {
        _gf_opts_version();
    }
    else if (
            strncmp(
                _gc_args_main[1],
                "-h",
                sizeof(_gc_args_main[1])
                ) == 0 ||
            strncmp(
                _gc_args_main[1],
                "--help",
                sizeof(_gc_args_main[1])
                ) == 0
            )
    {
        _gf_opts_help();
    }
    else
    {
        printf("\n\033[31mERROR: Unkown option.\033[0m\n\n");
    }

    return 0;
}



// opts
void _gf_opts_version()
{
    char _lc_file_version[100];
    FILE *_lp_file_version;

    _lp_file_version = fopen(
            "/usr/share/urlnotifyc/main/info/version",
            "r"
            );

    while (
            fgets(
                _lc_file_version,
                sizeof(_lc_file_version),
                _lp_file_version
                )
          )
    {
        printf("%s", _lc_file_version);
    }

    fclose(_lp_file_version);
}


void _gf_opts_help()
{
    char _lc_file_help[100];
    FILE *_lp_file_help;

    _lp_file_help = fopen(
            "/usr/share/urlnotifyc/main/info/help",
            "r"
            );

    while (
            fgets(
                _lc_file_help,
                sizeof(_lc_file_help),
                _lp_file_help
                )
          )
    {
        printf("%s", _lc_file_help);
    }

    fclose(_lp_file_help);
}