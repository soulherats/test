cmd_scripts/sortextable := gcc -Wp,-MD,scripts/.sortextable.d -O2 -I/home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include -Wall -Wmissing-prototypes -Wstrict-prototypes -Wno-unused-local-typedefs   -I/home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include -I/home/build/hiwifi/branch/release1.4/B50/14.07/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-mtmips_mt7620/linux-3.10.49/tools/include -I/home/build/hiwifi/branch/release1.4/B50/14.07/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-mtmips_mt7620/linux-3.10.49/tools/include -o scripts/sortextable scripts/sortextable.c  

source_scripts/sortextable := scripts/sortextable.c

deps_scripts/sortextable := \
  /usr/include/sys/types.h \
  /usr/include/features.h \
  /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-64.h \
  /usr/include/bits/types.h \
  /usr/include/bits/typesizes.h \
  /usr/include/time.h \
  /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stddef.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/endian.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/byteswap.h \
  /usr/include/byteswap.h \
  /usr/include/bits/byteswap.h \
  /usr/include/endian.h \
  /usr/include/bits/endian.h \
  /usr/include/sys/select.h \
  /usr/include/bits/select.h \
  /usr/include/bits/sigset.h \
  /usr/include/bits/time.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h \
  /usr/include/sys/mman.h \
  /usr/include/bits/mman.h \
  /usr/include/sys/stat.h \
  /usr/include/bits/stat.h \
  /usr/include/getopt.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/staging_dir/host/include/elf.h \
  /usr/include/stdint.h \
  /usr/include/bits/wchar.h \
  /usr/include/fcntl.h \
  /usr/include/bits/fcntl.h \
  /usr/include/setjmp.h \
  /usr/include/bits/setjmp.h \
  /usr/include/stdio.h \
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
  /usr/include/alloca.h \
  /usr/include/string.h \
  /usr/include/xlocale.h \
  /usr/include/bits/string.h \
  /usr/include/bits/string2.h \
  /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h \
  /usr/include/bits/environments.h \
  /usr/include/bits/confname.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-mtmips_mt7620/linux-3.10.49/tools/include/tools/be_byteshift.h \
  /usr/include/linux/types.h \
  /usr/include/asm/types.h \
  /usr/include/asm-generic/types.h \
  /usr/include/asm-generic/int-ll64.h \
  /usr/include/asm/bitsperlong.h \
  /usr/include/asm-generic/bitsperlong.h \
    $(wildcard include/config/64bit.h) \
  /usr/include/linux/posix_types.h \
  /usr/include/linux/stddef.h \
  /usr/include/asm/posix_types.h \
  /usr/include/asm/posix_types_64.h \
  /home/build/hiwifi/branch/release1.4/B50/14.07/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-mtmips_mt7620/linux-3.10.49/tools/include/tools/le_byteshift.h \
  scripts/sortextable.h \

scripts/sortextable: $(deps_scripts/sortextable)

$(deps_scripts/sortextable):
