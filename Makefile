### argument
## pack
_gs_control_version := $(shell '/usr/bin/grep' "Version:" "./dpkg/DEBIAN/control")
_gs_build_version := $(subst Version: ,,$(_gs_control_version))
_gs_build_package := urlnotifyc_$(_gs_build_version)_all.deb



### array
## clean
_ga_exec_clean += '/usr/bin/git'
_ga_exec_clean += clean
_ga_exec_clean += -fxd


## mkdir
_ga_exec_mkdir += '/usr/bin/install'
_ga_exec_mkdir += -v
_ga_exec_mkdir += -d
_ga_exec_mkdir += -m 0755
_ga_exec_mkdir += "./build/create/DEBIAN"
_ga_exec_mkdir += "./build/create/bin"
_ga_exec_mkdir += "./build/create/info"
_ga_exec_mkdir += "./build/dpkg/DEBIAN"
_ga_exec_mkdir += "./build/dpkg/usr/bin"
_ga_exec_mkdir += "./build/dpkg/usr/share/applications"
_ga_exec_mkdir += "./build/dpkg/usr/share/icons/hicolor/512x512/apps"
_ga_exec_mkdir += "./build/dpkg/usr/share/urlnotifyc/main/info"
_ga_exec_mkdir += "./export"


## create
_ga_exec_version += echo
_ga_exec_version += "$(_gs_build_version)"
_ga_exec_version += >
_ga_exec_version += "./build/create/info/version"

_ga_exec_lib += '/usr/bin/pkg-config'
_ga_exec_lib += --cflags
_ga_exec_lib += --libs

_ga_exec_bin += '/usr/bin/gcc'
_ga_exec_bin += "./src/urlnotifyc.c"
_ga_exec_bin += -o
_ga_exec_bin += "./build/create/bin/urlnotifyc"
_ga_exec_bin += $(shell $(_ga_exec_lib) "libnotify")

_ga_exec_fdfind += cd "./dpkg"
_ga_exec_fdfind += &&
_ga_exec_fdfind += '/usr/bin/fdfind'
_ga_exec_fdfind += --strip-cwd-prefix
_ga_exec_fdfind += --type file
_ga_exec_fdfind += --exclude "./DEBIAN"
_ga_exec_fdfind += --exec
_ga_exec_fdfind += '/usr/bin/shasum'
_ga_exec_fdfind += --algorithm 256
_ga_exec_fdfind += >
_ga_exec_fdfind += "../build/create/DEBIAN/shasums"


## copy
_ga_exec_precopy += '/usr/bin/install'
_ga_exec_precopy += -v
_ga_exec_precopy += -p
_ga_exec_precopy += -m 0755
_ga_exec_precopy += "./build/create/bin/urlnotifyc"
_ga_exec_precopy += -t
_ga_exec_precopy += "./build/dpkg/usr/bin/"
_ga_exec_precopy += &&

_ga_exec_precopy += '/usr/bin/install'
_ga_exec_precopy += -v
_ga_exec_precopy += -p
_ga_exec_precopy += -m 0644
_ga_exec_precopy += "./dpkg/usr/share/applications/urlnotifyc.desktop"
_ga_exec_precopy += -t
_ga_exec_precopy += "./build/dpkg/usr/share/applications/"
_ga_exec_precopy += &&

_ga_exec_precopy += '/usr/bin/install'
_ga_exec_precopy += -v
_ga_exec_precopy += -p
_ga_exec_precopy += -m 0644
_ga_exec_precopy += "./resource/icon/urlnotifyc.png"
_ga_exec_precopy += -t
_ga_exec_precopy += "./build/dpkg/usr/share/icons/hicolor/512x512/apps/"
_ga_exec_precopy += &&

_ga_exec_precopy += '/usr/bin/install'
_ga_exec_precopy += -v
_ga_exec_precopy += -p
_ga_exec_precopy += -m 0644
_ga_exec_precopy += "./dpkg/usr/share/urlnotifyc/main/info/"*
_ga_exec_precopy += "./LICENSE"
_ga_exec_precopy += "./build/create/info/version"
_ga_exec_precopy += -t
_ga_exec_precopy += "./build/dpkg/usr/share/urlnotifyc/main/info/"

_ga_exec_postcopy += '/usr/bin/install'
_ga_exec_postcopy += -v
_ga_exec_postcopy += -p
_ga_exec_postcopy += -m 0644
_ga_exec_postcopy += "./dpkg/DEBIAN/control"
_ga_exec_postcopy += "./build/create/DEBIAN/shasums"
_ga_exec_postcopy += -t
_ga_exec_postcopy += "./build/dpkg/DEBIAN/"


## archive
_ga_exec_dpkg += '/usr/bin/dpkg-deb'
_ga_exec_dpkg += --root-owner-group
_ga_exec_dpkg += --build
_ga_exec_dpkg += "./build/dpkg"
_ga_exec_dpkg += "./export/$(_gs_build_package)"

_ga_exec_shasum += cd "./export"
_ga_exec_shasum += &&
_ga_exec_shasum += '/usr/bin/shasum'
_ga_exec_shasum += --algorithm 512
_ga_exec_shasum += "$(_gs_build_package)"
_ga_exec_shasum += >
_ga_exec_shasum += "$(_gs_build_package).shasum"



### target
## clean
.PHONY: clean-all
clean-all:
	$(_ga_exec_clean)


## build
.PHONY: build-bin
build-bin:
	$(_ga_exec_clean)
	$(_ga_exec_mkdir)
	$(_ga_exec_bin)

.PHONY: build-deb
build-deb:
	$(_ga_exec_clean)
	$(_ga_exec_mkdir)
	$(_ga_exec_bin)
	$(_ga_exec_version)
	$(_ga_exec_precopy)
	$(_ga_exec_fdfind)
	$(_ga_exec_postcopy)
	$(_ga_exec_dpkg)
	$(_ga_exec_shasum)

