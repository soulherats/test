#
# Copyright (C) 2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/HCMT7621
	NAME:=HiWiFi HCMT7621 Board(SPI FLASH + 512MB DDR3)
	PACKAGES:=\
			kmod-usb-core kmod-mtk-usb3 \
			kmod-ledtrig-usbdev
endef

define Profile/HCMT7621/Description
	Default package set compatible with most boards.
endef

$(eval $(call Profile,HCMT7621))

define Profile/HCMT7621-S128
	NAME:=HiWiFi HCMT7621 S128 Board(SPI FLASH + 128MB DDR3)
	PACKAGES:=\
			kmod-usb-core kmod-mtk-usb3 \
			kmod-ledtrig-usbdev
endef

define Profile/HCMT7621-S128/Description
	Default package set compatible with most boards.
endef

$(eval $(call Profile,HCMT7621-S128))

define Profile/HCMT7621-N128
	NAME:=HiWiFi HCMT7621 N128 Board(NAND FLASH + 128MB DDR3)
	PACKAGES:=\
			kmod-usb-core kmod-mtk-usb3 \
			kmod-ledtrig-usbdev
endef

define Profile/HCMT7621-N128/Description
	Default package set compatible with most boards.
endef

$(eval $(call Profile,HCMT7621-N128))

define Profile/HC5961
	NAME:=HiWiFi HC5961 Board(NAND FLASH + 512MB DDR3 + USB 3.0)
	PACKAGES:=\
			kmod-usb-core kmod-mtk-usb3 \
			kmod-ledtrig-usbdev
endef

define Profile/HC5961/Description
	Default package set compatible with most boards.
endef

$(eval $(call Profile,HC5961))

define Profile/HC5962
	NAME:=HiWiFi HC5962 Board(NAND FLASH + 256MB DDR3 + USB 3.0)
	PACKAGES:=\
			kmod-usb-core kmod-mtk-usb3 \
			kmod-ledtrig-usbdev
endef

define Profile/HC5962/Description
	Default package set compatible with most boards.
endef

$(eval $(call Profile,HC5962))

define Profile/HC5963
        NAME:=HiWiFi HC5963 Board(NAND FLASH + 512MB DDR3 + USB 3.0)
        PACKAGES:=\
                        kmod-usb-core kmod-mtk-usb3 \
                        kmod-ledtrig-usbdev
endef

define Profile/HC5963/Description
        Default package set compatible with most boards.
endef

$(eval $(call Profile,HC5963))

define Profile/HC5964
        NAME:=HiWiFi HC5964 Board(NAND FLASH + 256MB DDR3 + USB 3.0)
        PACKAGES:=\
                        kmod-usb-core kmod-mtk-usb3 \
                        kmod-ledtrig-usbdev
endef

define Profile/HC5964/Description
        Default package set compatible with most boards.
endef

$(eval $(call Profile,HC5964))

define Profile/BLWR4122H
        NAME:=Hiwifi Wireless(BLINK) BL-WR4122H Board
endef

define Profile/BLWR4122H/Description
        Default package set compatible with Hiwifi Wireless(BLINK) BL-WR4122H Board.
endef
$(eval $(call Profile,BLWR4122H))
