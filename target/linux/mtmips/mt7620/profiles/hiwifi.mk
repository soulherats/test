#
# Copyright (C) 2013-2014 www.hiwifi.com
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/HC5661
	NAME:=Hiwifi Wireless HC5661 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/HC5661/Description
	Default package set compatible with Hiwifi Wireless HC5661 Board.
endef
$(eval $(call Profile,HC5661))

define Profile/HC5761
	NAME:=Hiwifi Wireless HC5761 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/HC5761/Description
	Default package set compatible with Hiwifi Wireless HC5761 Board.
endef
$(eval $(call Profile,HC5761))

# MT7620A + MT7610E + PoE
define Profile/HB5881
	NAME:=HiWiFi Wireless HB5881 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/HB5881/Description
	Default package set compatible with HiWiFi Wireless HB5881(MT7620A + MT7610E + PoE) Board.
endef
$(eval $(call Profile,HB5881))

define Profile/HC5663
	NAME:=Hiwifi Wireless HC5663 Board
	PACKAGES:=\
		kmod-ata-core kmod-ata-ahci
endef

define Profile/HC5663/Description
	Default package set compatible with Hiwifi Wireless HC5663 Board.
endef
$(eval $(call Profile,HC5663))

define Profile/HB5811
	NAME:=HiWiFi Wireless HB5811 AP Board
endef

define Profile/HB5811/Description
	Default package set compatible with HiWiFi Wireless HB5811 AP Board(with HB5881).
endef
$(eval $(call Profile,HB5811))

# MT7620A + MT7612E
define Profile/HC5861
	NAME:=HiWiFi Wireless HC5861 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/HC5861/Description
	Default package set compatible with HiWiFi Wireless HC5861(MT7620A + MT7612E) Board.
endef
$(eval $(call Profile,HC5861))

# MT7620A + MT7612E
define Profile/B50
	NAME:=HiWiFi Wireless B50 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/B50/Description
	Default package set compatible with HiWiFi Wireless B50(MT7620A + MT7612E) Board.
endef
$(eval $(call Profile,B50))

# MT7620A + MT7612E
define Profile/R33
	NAME:=HiWiFi Wireless R33 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/R33/Description
	Default package set compatible with HiWiFi Wireless R33(MT7620A + MT7612E + RTL8367RB) Board.
endef
$(eval $(call Profile,R33))

define Profile/R32
	NAME:=HiWiFi Wireless R32 Board
endef

define Profile/R32/Description
	Default package set compatible with HiWiFi Wireless R32(MT7620A + MT7612E + RTL8211 + NAND FLASH) Board.
endef
$(eval $(call Profile,R32))

define Profile/G13
        NAME:=Hiwifi Wireless G13 Board
endef

define Profile/G13/Description
        Default package set compatible with Hiwifi Wireless G13 Board.
endef
$(eval $(call Profile,G13))

define Profile/HC5762
	NAME:=HiWiFi Wireless HC5762 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/HC5762/Description
	Default package set compatible with HiWiFi Wireless HC5762(MT7620A + MT7612E) Board.
endef
$(eval $(call Profile,HC5762))

# ZC
define Profile/ZC9525
	NAME:=HiWiFi Wireless ZC-9525 Board
endef

define Profile/ZC9525/Description
	Default package set compatible with HiWiFi Wireless ZC-9525 Board(256MB DDR2).
endef
$(eval $(call Profile,ZC9525))

define Profile/ZC9526
	NAME:=HiWiFi Wireless ZC-9526 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/ZC9526/Description
	Default package set compatible with HiWiFi Wireless ZC-9526 Board(256MB DDR2, fake PoE).
endef
$(eval $(call Profile,ZC9526))

define Profile/ZC9527
	NAME:=HiWiFi Wireless ZC-9527 Board
endef

define Profile/ZC9527/Description
	Default package set compatible with HiWiFi Wireless ZC-9527 Board(128MB DDR2, 802.3 PoE).
endef
$(eval $(call Profile,ZC9527))

define Profile/ZC9527R
	NAME:=HiWiFi Wireless ZC-9527 Router Board
endef

define Profile/ZC9527R/Description
	Default package set compatible with HiWiFi Wireless ZC-9527 Router Board(128MB DDR2, 802.3 PoE).
endef
$(eval $(call Profile,ZC9527R))

define Profile/ZC9528
	NAME:=HiWiFi Wireless ZC-9528 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/ZC9528/Description
	Default package set compatible with HiWiFi Wireless ZC-9528 Board(256MB DDR2, fake PoE).
endef
$(eval $(call Profile,ZC9528))

# B-LINK begin

# B-LINK MT7620A + MT7610E
define Profile/HB750ACH
	NAME:=HiWiFi Wireless HB750ACH B-LINK Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/HB750ACH/Description
	Default package set compatible with HiWiFi Wireless HB750ACH B-LINK Board.
endef
$(eval $(call Profile,HB750ACH))

define Profile/HB8100
	NAME:=HiWiFi Wireless HB8100 B-LINK Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/HB8100/Description
	Default package set compatible with HiWiFi Wireless HB8100 B-LINK Board.
endef
$(eval $(call Profile,HB8100))

# B-LINK MT7620N
define Profile/HB845H
	NAME:=Hiwifi Wireless HB845H B-LINK Board
endef

define Profile/HB845H/Description
	Default package set compatible with Hiwifi Wireless HB845H B-LINK Board.
endef
$(eval $(call Profile,HB845H))

# B-LINK MT7620 + MT7612E + MT7530
define Profile/BLW1210
        NAME:=Hiwifi Wireless B-LINK BL-W1210 Board
endef

define Profile/BLW1210/Description
        Default package set compatible with Hiwifi Wireless B-LINK BL-W1210 Board.
endef
$(eval $(call Profile,BLW1210))

# B-LINK end

# TCL
define Profile/HM578
	NAME:=Hiwifi Wireless HM578 Board
	PACKAGES:=\
		kmod-usb-core kmod-usb2
endef

define Profile/HM578/Description
	Default package set compatible with Hiwifi Wireless HM578 Board.
endef
$(eval $(call Profile,HM578))

# custom MT7620N
define Profile/WIFILink2950
	NAME:=Hiwifi Wireless WIFI-Link-2950 Board
endef

define Profile/WIFILink2950/Description
	Default package set compatible with Hiwifi Wireless WIFI-Link-2950 Board.
endef
$(eval $(call Profile,WIFILink2950))
