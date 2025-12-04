// include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libnotify/notify.h>



// function
void _gf_opts_version();
void _gf_opts_help();
void _gf_opts_notify();



// main
int main(
        int _gi_args_main,
        char *_gC_args_main[]
        )
{
    if (_gi_args_main < 2)
    {
        printf("\n\033[31mERROR: Empty option.\033[0m\n\n");
    }
    else if (
            strncmp(
                _gC_args_main[1],
                "-v",
                sizeof(_gC_args_main[1])
                ) == 0 ||
            strncmp(
                _gC_args_main[1],
                "--version",
                sizeof(_gC_args_main[1])
                ) == 0
            )
    {
        _gf_opts_version();
    }
    else if (
            strncmp(
                _gC_args_main[1],
                "-h",
                sizeof(_gC_args_main[1])
                ) == 0 ||
            strncmp(
                _gC_args_main[1],
                "--help",
                sizeof(_gC_args_main[1])
                ) == 0
            )
    {
        _gf_opts_help();
    }
    else if (_gi_args_main < 3)
    {
        printf("\n\033[31mERROR: Missing argument.\033[0m\n\n");
    }
    else if (
            strncmp(
                _gC_args_main[1],
                "-n",
                sizeof(_gC_args_main[1])
                ) == 0 ||
            strncmp(
                _gC_args_main[1],
                "--notify",
                sizeof(_gC_args_main[1])
                ) == 0
            )
    {
        _gf_opts_notify(
                _gC_args_main[2]
                );
    }
    else
    {
        printf("\n\033[31mERROR: Invalid option.\033[0m\n\n");
    }

    return 0;
}



// opts
void _gf_opts_version()
{
    char _lC_file_version[100];
    FILE *_lp_file_version;

    _lp_file_version = fopen(
            "/usr/share/urlnotifyc/main/info/version",
            "r"
            );

    while (
            fgets(
                _lC_file_version,
                sizeof(_lC_file_version),
                _lp_file_version
                )
          )
    {
        printf("%s", _lC_file_version);
    }

    fclose(_lp_file_version);
}


void _gf_opts_help()
{
    char _lC_file_help[100];
    FILE *_lp_file_help;

    _lp_file_help = fopen(
            "/usr/share/urlnotifyc/main/info/help",
            "r"
            );

    while (
            fgets(
                _lC_file_help,
                sizeof(_lC_file_help),
                _lp_file_help
                )
          )
    {
        printf("%s", _lC_file_help);
    }

    fclose(_lp_file_help);
}


void _gf_opts_notify(
        char *_lc_args_notify
        )
{
    char *_lC_exec_notifyurl[] = {
        "/usr/bin/notify-send",
        "--app-name=URLnotifyC",
        "--icon=urlnotifyc",
        "--urgency=critical",
        "--action=0=Close",
        "--action=1=Copy",
        "--",
        "URL Notify",
        _lc_args_notify,
        NULL
    };

    char *_lC_exec_notifyaction0[] = {
        "/usr/bin/notify-send",
        "--app-name=URLnotifyC",
        "--icon=urlnotifyc",
        "--urgency=normal",
        "--",
        "Action 0",
        "Nothing happen.",
        NULL
    };

    char *_lC_exec_notifyaction1[] = {
        "/usr/bin/notify-send",
        "--app-name=URLnotifyC",
        "--icon=urlnotifyc",
        "--urgency=normal",
        "--",
        "Action 1",
        "Copy successful.",
        NULL
    };

    char *_lC_exec_notifyactiond[] = {
        "/usr/bin/notify-send",
        "--app-name=URLnotifyC",
        "--icon=urlnotifyc",
        "--urgency=normal",
        "--",
        "ERROR",
        "Unkown action",
        NULL
    };

    int _li_notify_action = execvp(
            _lC_exec_notifyurl[0],
            _lC_exec_notifyurl
            );

    switch (_li_notify_action)
    {
        case '0':
            printf("\n\033[33mAction 0: Nothing happen.\033[0m\n\n");
            execvp(
                    _lC_exec_notifyaction0[0],
                    _lC_exec_notifyaction0
                  );
        case '1':
            printf("\n\033[36mAction 1: Copy successful.\033[0m\n\n");
            execvp(
                    _lC_exec_notifyaction1[1],
                    _lC_exec_notifyaction1
                  );
        default:
            printf("\n\033[31mERROR: Unkown action.\033[0m\n\n");
            execvp(
                    _lC_exec_notifyactiond[1],
                    _lC_exec_notifyactiond
                  );
    }
}