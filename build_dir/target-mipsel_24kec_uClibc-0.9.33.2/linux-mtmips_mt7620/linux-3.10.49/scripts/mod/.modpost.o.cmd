cmd_scripts/mod/modpost.o := gcc -Wp,-MD,scripts/mod/.modpost.o.d -O2 -I/home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include -Wall -Wmissing-prototypes -Wstrict-prototypes -Wno-unused-local-typedefs   -I/home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include -I/home/build/hiwifi/branch/release1.4/B50/14.07/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-mtmips_mt7620/linux-3.10.49/tools/include  -c -o scripts/mod/modpost.o scripts/mod/modpost.c

source_scripts/mod/modpost.o := scripts/mod/modpost.c

deps_scripts/mod/modpost.o := \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/module/srcversion/all.h) \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/relocatable.h) \
    $(wildcard include/config/module/stripped.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/debug/section/mismatch.h) \
  /usr/include/stdio.h \
  /usr/include/features.h \
  /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-64.h \
  /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stddef.h \
  /usr/include/bits/types.h \
  /usr/include/bits/typesizes.h \
  /usr/include/libio.h \
  /usr/include/_G_config.h \
  /usr/include/wchar.h \
  /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stdarg.h \
  /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h \
  /usr/include/bits/stdio.h \
  /usr/include/ctype.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/endian.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/byteswap.h \
  /usr/include/byteswap.h \
  /usr/include/bits/byteswap.h \
  /usr/include/endian.h \
  /usr/include/bits/endian.h \
  /usr/include/xlocale.h \
  /usr/include/string.h \
  /usr/include/bits/string.h \
  /usr/include/bits/string2.h \
  /usr/include/stdlib.h \
  /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/limits.h \
  /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/syslimits.h \
  /usr/include/limits.h \
  /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h \
  /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/include/bits/xopen_lim.h \
  /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stdbool.h \
  scripts/mod/modpost.h \
  /usr/include/bits/waitflags.h \
  /usr/include/bits/waitstatus.h \
  /usr/include/sys/types.h \
  /usr/include/time.h \
  /usr/include/sys/select.h \
  /usr/include/bits/select.h \
  /usr/include/bits/sigset.h \
  /usr/include/bits/time.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h \
  /usr/include/alloca.h \
  /usr/include/sys/stat.h \
  /usr/include/bits/stat.h \
  /usr/include/sys/mman.h \
  /usr/include/bits/mman.h \
  /usr/include/fcntl.h \
  /usr/include/bits/fcntl.h \
  /usr/include/bits/uio.h \
  /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h \
  /usr/include/bits/environments.h \
  /usr/include/bits/confname.h \
  /usr/include/getopt.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/elf.h \
  /usr/include/stdint.h \
  /usr/include/bits/wchar.h \
  scripts/mod/elfconfig.h \
  scripts/mod/../../include/linux/license.h \
  scripts/mod/../../include/linux/export.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/unused/symbols.h) \

scripts/mod/modpost.o: $(deps_scripts/mod/modpost.o)

$(deps_scripts/mod/modpost.o):
