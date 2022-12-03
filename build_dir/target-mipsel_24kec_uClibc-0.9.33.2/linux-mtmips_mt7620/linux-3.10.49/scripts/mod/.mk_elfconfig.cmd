cmd_scripts/mod/mk_elfconfig := gcc -Wp,-MD,scripts/mod/.mk_elfconfig.d -O2 -I/home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include -Wall -Wmissing-prototypes -Wstrict-prototypes -Wno-unused-local-typedefs   -I/home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include -I/home/build/hiwifi/branch/release1.4/B50/14.07/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-mtmips_mt7620/linux-3.10.49/tools/include  -o scripts/mod/mk_elfconfig scripts/mod/mk_elfconfig.c  

source_scripts/mod/mk_elfconfig := scripts/mod/mk_elfconfig.c

deps_scripts/mod/mk_elfconfig := \
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
  /usr/include/stdlib.h \
  /usr/include/bits/waitflags.h \
  /usr/include/bits/waitstatus.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/endian.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/byteswap.h \
  /usr/include/byteswap.h \
  /usr/include/bits/byteswap.h \
  /usr/include/endian.h \
  /usr/include/bits/endian.h \
  /usr/include/sys/types.h \
  /usr/include/time.h \
  /usr/include/sys/select.h \
  /usr/include/bits/select.h \
  /usr/include/bits/sigset.h \
  /usr/include/bits/time.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h \
  /usr/include/alloca.h \
  /usr/include/string.h \
  /usr/include/xlocale.h \
  /usr/include/bits/string.h \
  /usr/include/bits/string2.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/elf.h \
  /usr/include/stdint.h \
  /usr/include/bits/wchar.h \

scripts/mod/mk_elfconfig: $(deps_scripts/mod/mk_elfconfig)

$(deps_scripts/mod/mk_elfconfig):
