#
# Copyright (C) 2008-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

ARCH:=mipsel
BOARD:=mtmips
BOARDNAME:=MTK MT7620/MT7628/MT7621
SUBTARGETS:=mt7620 mt7628 mt7621
FEATURES:=squashfs gpio

KERNEL_PATCHVER:=3.10

include $(INCLUDE_DIR)/target.mk
DEFAULT_PACKAGES += \
	kmod-leds-gpio kmod-gpio-button-hotplug mtk-switch image-check reg

define Target/Description
	Build firmware images for MTK MT7620/MT7628/MT7621 based boards.
endef

$(eval $(call BuildTarget))
