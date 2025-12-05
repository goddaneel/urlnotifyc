// include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libnotify/notify.h>



// opts info
    void
_gf_opts_info(
        char    *_lc_args_info
        )
{
    char _lC_file_info[1024];
    FILE *_lp_file_info;

    char _lc_path_info[] = "/usr/share/urlnotifyc/main/info/";

    strncat(
            _lc_path_info,
            _lc_args_info,
            sizeof(_lc_path_info) - strlen(_lc_path_info) - 1
           );

    _lp_file_info = fopen(
            _lc_path_info,
            "r"
            );

    if (
            _lp_file_info == NULL
       )
    {
        printf("\n\033[31mERROR: File opening failed.\033[0m\n\n");
        exit(1);
    }

    while (
            fgets(
                _lC_file_info,
                sizeof(_lC_file_info),
                _lp_file_info
                )
          )
    {
        printf("%s", _lC_file_info);
    }

    if (
            fclose(_lp_file_info) != 0
       )
    {
        printf("\n\033[31mERROR: File closing failed.\033[0m\n\n");
    }
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

    g_signal_connect(
            G_OBJECT(_lp_notify_url),
            "closed",
            G_CALLBACK(_gf_opts_notify_callback),
            "close"
            );

    notify_notification_add_action(
            _lp_notify_url,
            "copy",
            "Copy",
            _gf_opts_notify_callback,
            NULL,
            NULL
            );

    notify_notification_add_action(
            _lp_notify_url,
            "close",
            "Close",
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

    int _li_notify_status = 0;

    NotifyNotification *_lp_notify_action;

    if (
            strncmp(
                _zc_notify_action,
                "close",
                sizeof(_zc_notify_action)
                ) == 0
       )
    {
        _li_notify_status = 1;
        //      //
        printf("\n\033[33mAction 0: Nothing happen.\033[0m\n\n");
        //      //
        _lp_notify_action = notify_notification_new(
                "Action 0",
                "Nothing happen.",
                NULL
                );
    }
    else if (
            strncmp(
                _zc_notify_action,
                "copy",
                sizeof(_zc_notify_action)
                ) == 0
            )
    {
        char *_lC_exec_wlcopy[] = {
            "/usr/bin/wl-copy",
            "--trim-newline",
            "--",
            _lc_args_notify,
            NULL
        };
        //      //
        execvp(
                _lC_exec_wlcopy[0],
                _lC_exec_wlcopy
              );
        //      //
        printf("\n\033[36mAction 1: Copy successful.\033[0m\n\n");
        //      //
        _lp_notify_action = notify_notification_new(
                "Action 1",
                "Copy successful.",
                NULL
                );
    }
    else
    {
        _li_notify_status = 1;
        //      //
        printf("\n\033[31mERROR: Unkown action.\033[0m\n\n");
        //      //
        _lp_notify_action = notify_notification_new(
                "ERROR",
                "Unkown action.",
                NULL
                );
    }

    notify_notification_set_app_icon(
            _lp_notify_action,
            "urlnotifyc"
            );

    notify_notification_set_urgency(
            _lp_notify_action,
            NOTIFY_URGENCY_NORMAL
            );

    notify_notification_show(
            _lp_notify_action,
            NULL
            );

    g_object_unref(
            G_OBJECT(
                _lp_notify_action
                )
            );

    notify_uninit();

    if (_li_notify_status != 0)
    {
        exit(_li_notify_status);
    }
}



// main
    int
main(
        int     _gi_args_main,
        char    *_gC_args_main[]
    )
{
    if (_gi_args_main < 2)
    {
        printf("\n\033[31mERROR: Empty option.\033[0m\n\n");
        //      //
        return 1;
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
        _gf_opts_info("version");
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
        _gf_opts_info("help");
    }
    else if (_gi_args_main < 3)
    {
        printf("\n\033[31mERROR: Missing argument.\033[0m\n\n");
        //      //
        return 1;
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
        //      //
        return 1;
    }

    return 0;
}
