// include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libnotify/notify.h>



// opts
    void
_gf_opts_version()
{
    char _lC_file_version[1024];
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


    void
_gf_opts_help()
{
    char _lC_file_help[1024];
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



// opts notify
char _zc_notify_action[1024];

static GMainLoop *_gp_loop_opts_notify;


    static void
_gf_opts_notify_callback(
        NotifyNotification  *_lp_notify_url,
        char                *_lc_notify_action,
        void                *_lv_notify_userdata
        )
{
    strncpy(
            _zc_notify_action,
            _lc_notify_action,
            sizeof(_zc_notify_action) - 1
           );

    notify_notification_close(
            _lp_notify_url,
            NULL
            );

    g_main_loop_quit(_gp_loop_opts_notify);
}


    void
_gf_opts_notify(
        char    *_lc_args_notify
        )
{
    _gp_loop_opts_notify = g_main_loop_new(
            NULL,
            FALSE
            );

    notify_init(
            "URLnotifyC"
            );

    NotifyNotification *_lp_notify_url;

    _lp_notify_url = notify_notification_new(
            "URL Notify",
            _lc_args_notify,
            NULL
            );

    notify_notification_set_app_icon(
            _lp_notify_url,
            "urlnotifyc"
            );

    notify_notification_set_urgency(
            _lp_notify_url,
            NOTIFY_URGENCY_CRITICAL
            );

    notify_notification_add_action(
            _lp_notify_url,
            "close",
            "Close",
            _gf_opts_notify_callback,
            NULL,
            NULL
            );

    notify_notification_add_action(
            _lp_notify_url,
            "copy",
            "Copy",
            _gf_opts_notify_callback,
            NULL,
            NULL
            );

    notify_notification_show(
            _lp_notify_url,
            NULL
            );

    g_main_loop_run(_gp_loop_opts_notify);

    g_object_unref(
            G_OBJECT(
                _lp_notify_url
                )
            );

    notify_uninit();

    if (
            strncmp(
                _zc_notify_action,
                "close",
                sizeof(_zc_notify_action)
                ) == 0
       )
    {
        printf("\n\033[33mAction 0: Nothing happen.\033[0m\n\n");
    }
    else if (
            strncmp(
                _zc_notify_action,
                "copy",
                sizeof(_zc_notify_action)
                ) == 0
            )
    {
        printf("\n\033[36mAction 1: Copy successful.\033[0m\n\n");
    }
    else
    {
        printf("\n\033[31mERROR: Unkown action.\033[0m\n\n");
    }
}



// main
    void
main(
        int     _gi_args_main,
        char    *_gC_args_main[]
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
