// include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <libnotify/notify.h>



// opts info
        void
_gf_opts_info(
                char    *_lc_arg1_info
             )
{
        char _lC_file_info[1024];

        FILE *_lp_file_info;

        char _lc_path_info[128] = "/usr/share/urlnotifyc/main/info/";

        strncat(
                        _lc_path_info,
                        _lc_arg1_info,
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
                fprintf(
                                stderr,
                                "\n\033[31m"
                                "ERROR: File opening failed."
                                "\033[0m\n\n"
                       );
                //      //
                exit(EXIT_FAILURE);
        }

        while (
                        fgets(
                                _lC_file_info,
                                sizeof(_lC_file_info),
                                _lp_file_info
                             )
              )
        {
                printf(
                                "%s",
                                _lC_file_info
                      );
        }

        if (
                        fclose(_lp_file_info) != 0
           )
        {
                fprintf(
                                stderr,
                                "\n\033[31m"
                                "ERROR: File closing failed."
                                "\033[0m\n\n"
                       );
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
_gf_opts_notify_url(
                char    *_lc_arg1_notify_url
                )
{
        _gp_loop_opts_notify = g_main_loop_new(
                        NULL,
                        FALSE
                        );

        NotifyNotification *_lp_notify_url;

        _lp_notify_url = notify_notification_new(
                        "URL",
                        _lc_arg1_notify_url,
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
                        G_OBJECT(_lp_notify_url)
                      );
}


        void
_gf_opts_notify_copy(
                char    *_lc_arg1_notify_copy
                )
{
        pid_t _li_pid_copy;

        _li_pid_copy = fork();

        if (_li_pid_copy == 0)
        {
                char *_lC_exec_wlcopy[] = {
                        "/usr/bin/wl-copy",
                        "--trim-newline",
                        "--",
                        _lc_arg1_notify_copy,
                        NULL
                };
                //      //
                execvp(
                                _lC_exec_wlcopy[0],
                                _lC_exec_wlcopy
                      );
                //      //
                exit(EXIT_FAILURE);
        }
        else if (
                        _li_pid_copy < 0
                        || waitpid(
                                _li_pid_copy,
                                NULL,
                                0
                                ) < 0
                )
        {
                fprintf(
                                stderr,
                                "\n\033[31m"
                                "ERROR: Copy execution failed."
                                "\033[0m\n\n"
                       );
                //      //
                exit(EXIT_FAILURE);
        }
}


        void
_gf_opts_notify(
                int     _li_args_notify,
                char    *_lC_args_notify[]
               )
{
        notify_init(
                        "URLnotifyC"
                   );

        if (_li_args_notify < 3)
        {
                strncpy(
                                _zc_notify_action,
                                "null",
                                sizeof(_zc_notify_action) - 1
                       );
        }
        else
        {
                _gf_opts_notify_url(_lC_args_notify[2]);
        }

        int _li_notify_status = EXIT_SUCCESS;

        NotifyNotification *_lp_notify_action;

        if (
                        strncmp(
                                _zc_notify_action,
                                "null",
                                sizeof(_zc_notify_action)
                               ) == 0
           )
        {
                _li_notify_status = EXIT_FAILURE;
                //      //
                fprintf(
                                stderr,
                                "\n\033[31m"
                                "WARNING: URL is null."
                                "\033[0m\n\n"
                       );
                //      //
                _lp_notify_action = notify_notification_new(
                                "ERROR",
                                "URL is null.",
                                NULL
                                );
        }
        else if (
                        strncmp(
                                _zc_notify_action,
                                "close",
                                sizeof(_zc_notify_action)
                               ) == 0
                )
        {
                _li_notify_status = EXIT_FAILURE;
                //      //
                fprintf(
                                stderr,
                                "\n\033[33m"
                                "Close: "
                                "%s"
                                "\033[0m\n\n",
                                _lC_args_notify[2]
                       );
                //      //
                _lp_notify_action = notify_notification_new(
                                "Close",
                                _lC_args_notify[2],
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
                _gf_opts_notify_copy(_lC_args_notify[2]);
                //      //
                printf(
                                "\n\033[36m"
                                "Copy: "
                                "%s"
                                "\033[0m\n\n",
                                _lC_args_notify[2]
                      );
                //      //
                _lp_notify_action = notify_notification_new(
                                "Copy",
                                _lC_args_notify[2],
                                NULL
                                );
        }
        else
        {
                _li_notify_status = EXIT_FAILURE;
                //      //
                fprintf(
                                stderr,
                                "\n\033[31m"
                                "ERROR: Unkown action."
                                "\033[0m\n\n"
                       );
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
                        G_OBJECT(_lp_notify_action)
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
                fprintf(
                                stderr,
                                "\n\033[31m"
                                "ERROR: Empty option."
                                "\033[0m\n\n"
                       );
                //      //
                return EXIT_FAILURE;
        }
        else if (
                        strncmp(
                                _gC_args_main[1],
                                "-v",
                                sizeof(_gC_args_main[1])
                               ) == 0
                        || strncmp(
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
                               ) == 0
                        || strncmp(
                                _gC_args_main[1],
                                "--help",
                                sizeof(_gC_args_main[1])
                                ) == 0
                )
        {
                _gf_opts_info("help");
        }
        else if (
                        strncmp(
                                _gC_args_main[1],
                                "-n",
                                sizeof(_gC_args_main[1])
                               ) == 0
                        || strncmp(
                                _gC_args_main[1],
                                "--notify",
                                sizeof(_gC_args_main[1])
                                ) == 0
                )
        {
                _gf_opts_notify(
                                _gi_args_main,
                                _gC_args_main
                               );
        }
        else
        {
                fprintf(
                                stderr,
                                "\n\033[31m"
                                "ERROR: Invalid option."
                                "\033[0m\n\n"
                       );
                //      //
                _gf_opts_info("help");
                //      //
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
