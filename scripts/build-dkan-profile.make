api = 2
core = 7.x

;Include distro's make file.
includes[dkan] = "../projects/dkan/build-dkan.make"

;Only contribs, libraries and patches to be listed here.
projects[master][subdir] = "contrib"
projects[master][version] = "2.0-beta4"
