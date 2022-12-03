#
# Copyright (C) 2009 OpenWrt.org
#

SUBTARGET:=mt7620
BOARDNAME:=MT7620 based boards
ARCH_PACKAGES:=mtmips_24kec
FEATURES+=usb nand
CPU_TYPE:=24kec

define Target/Description
	Build firmware images for Mediatek MT7620 based boards.
endef

