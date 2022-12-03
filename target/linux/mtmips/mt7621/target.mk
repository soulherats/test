#
# Copyright (C) 2009 OpenWrt.org
#

SUBTARGET:=mt7621
BOARDNAME:=MT7621 based boards
ARCH_PACKAGES:=mtmips_1004kc
FEATURES+=usb squashfs nand rtc
CPU_TYPE:=1004kc
CFLAGS:=-Os -pipe -mmt -mips32r2 -mtune=1004kc -g

define Target/Description
	Build firmware images for Ralink MT7621 based boards.
endef

