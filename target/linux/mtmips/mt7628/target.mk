#
# Copyright (C) 2009 OpenWrt.org
#

SUBTARGET:=mt7628
BOARDNAME:=MT7628 based boards
ARCH_PACKAGES:=mtmips_24kec
FEATURES+=usb
CPU_TYPE:=24kec

define Target/Description
	Build firmware images for Mediatek MT7628 based boards.
endef

