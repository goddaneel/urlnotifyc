#!/bin/bash


### init
## set
set -e


### function
## tool
function _gF_tool_echo () 
{
        echo -e "\n${3}\033[${1:?}${2:?}\033[0m" ;
}
declare -fr '_gF_tool_echo'


## unit
function _gF_unit_clean () 
{
        '/usr/bin/git' clean -fxd ;
}
declare -fr '_gF_unit_clean'

function _gF_unit_mkdir () 
{
        declare -a "_la_exec_install" ;
        #               #
        _la_exec_install=(
                '/usr/bin/install'
                -v
                -d
                -m 0755
                "./build/create/DEBIAN"
                "./build/create/info"
                "./build/dpkg/DEBIAN"
                "./build/dpkg/usr/bin"
                "./build/dpkg/usr/share/applications"
                "./build/dpkg/usr/share/icons/hicolor/512x512/apps"
                "./build/dpkg/usr/share/urlnotifyc/main/info"
                "./export"
        )
        #               #
        "${_la_exec_install[@]}" ;
}
declare -fr '_gF_unit_mkdir'

function _gF_unit_bin () 
{
        declare -a "_la_exec_gcc" ;
        declare -a "_la_exec_lib" ;
        #               #
        _la_exec_lib=(
                '/usr/bin/pkg-config'
                --cflags
                --libs
                "libnotify"
        )
        #               #
        _la_exec_gcc=(
                '/usr/bin/gcc'
                "./src/urlnotifyc.c"
                -o
                "./build/create/bin/urlnotifyc"
                $("${_la_exec_lib[@]}")
        )
        #               #
        "${_la_exec_bin[@]}" ;
}
declare -fr '_gF_unit_bin'

function _gF_unit_precopy () 
{
        declare -a "_la_exec_install" ;
        declare -a "_la_exec_fdfind" ;
        #               #
        #               #
        _la_exec_install=(
                '/usr/bin/install'
                -v
                -p
                -m 0755
                -t
                "./build/dpkg/usr/bin/"
                --
                "./dpkg/usr/bin/urlnotifyc"
        )
        #               #
        "${_la_exec_install[@]}" ;
        #               #
        #               #
        _la_exec_install=(
                '/usr/bin/install'
                -v
                -p
                -m 0644
                -t
                "./build/dpkg/usr/share/urlnotifyc/main/info/"
                --
                "./LICENSE"
        )
        #               #
        "${_la_exec_install[@]}" ;
        #               #
        #               #
        _la_exec_install=(
                '/usr/bin/install'
                -v
                -p
                -m 0644
                -t
                "./build/dpkg/usr/share/applications/"
                --
                "./dpkg/usr/share/applications/urlnotifyc.desktop"
        )
        #               #
        "${_la_exec_install[@]}" ;
        #               #
        #               #
        _la_exec_install=(
                '/usr/bin/install'
                -v
                -p
                -m 0644
                -t
                "./build/dpkg/usr/share/icons/hicolor/512x512/apps/"
                --
                "./resource/icon/urlnotifyc.png"
        )
        #               #
        "${_la_exec_install[@]}" ;
        #               #
        #               #
        echo "${_gs_build_version}" > "./build/create/info/version" ;
        #               #
        _la_exec_fdfind=(
                '/usr/bin/fdfind'
                --type file
                .
                "./build/create/info"
                "./dpkg/usr/share/urlnotifyc/main/info"
                --exec
                '/usr/bin/install'
                -v
                -p
                -m 0644
                -t
                "./build/dpkg/usr/share/urlnotifyc/main/info/"
                --
        )
        #               #
        "${_la_exec_fdfind[@]}" ;
}
declare -fr '_gF_unit_precopy'

function _gF_unit_postcopy () 
{
        declare -a "_la_exec_install" ;
        #               #
        _la_exec_install=(
                '/usr/bin/install'
                -v
                -p
                -m 0644
                -t
                "./build/dpkg/DEBIAN/"
                --
                "./dpkg/DEBIAN/control"
                "./build/create/DEBIAN/shasums"
        )
        #               #
        "${_la_exec_install[@]}" ;
}
declare -fr '_gF_unit_postcopy'

function _gF_unit_shasum () 
{
        ( cd "./dpkg" ;
        #               #
        declare -a "_la_exec_fdfind" ;
        #               #
        _la_exec_fdfind=(
                '/usr/bin/fdfind'
                --strip-cwd-prefix
                --type file
                --exclude "./DEBIAN"
                --exec
                '/usr/bin/shasum'
                --algorithm 256
        )
        #               #
        "${_la_exec_fdfind[@]}" > "../build/create/DEBIAN/shasums" ;
        #               #
        exit ) ;
}
declare -fr '_gF_unit_shasum'

function _gF_unit_dpkg () 
{
        declare -a "_la_exec_dpkg" ;
        #               #
        _la_exec_dpkg=(
                '/usr/bin/dpkg-deb'
                --root-owner-group
                --build
                "./build/dpkg"
                "./export/${_gs_build_package}"
        )
        #               #
        "${_la_exec_dpkg[@]}" ;
        #               #
        ( cd "./export" ;
        #               #
        declare -a "_la_exec_shasum" ;
        #               #
        _la_exec_shasum=(
                '/usr/bin/shasum'
                --algorithm 512
                "${_gs_build_package}"
        )
        #               #
        "${_la_exec_shasum[@]}" > "${_gs_build_package}.shasum" ;
        #               #
        exit ) ;
}
declare -fr '_gF_unit_dpkg'



### variable
## name
declare -g "_gs_control_version"
declare -g "_gs_build_version"
declare -g "_gs_build_package"


## value
declare -g _gs_1_opt="${1}"


## command
_gs_control_version="$('/usr/bin/grep' "Version:" "./dpkg/DEBIAN/control")"
_gs_build_version="${_gs_control_version##"Version: "}"
_gs_build_package="urlnotifyc_${_gs_build_version}_all.deb"



### exec
## case
case "${_gs_1_opt}" in
        "clean-all")
                '_gF_unit_clean'
                ;;
        "build-bin")
                '_gF_unit_clean'
                '_gF_unit_mkdir'
                '_gF_unit_bin'
                ;;
        "build-deb")
                '_gF_unit_clean'
                '_gF_unit_mkdir'
                '_gF_unit_bin'
                '_gF_unit_precopy'
                '_gF_unit_shasum'
                '_gF_unit_postcopy'
                '_gF_unit_dpkg'
                ;;
        *)
                '_gF_tool_echo' "31m" "ERROR: Unkown Option."
                ;;
esac
