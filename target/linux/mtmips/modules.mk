#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

OTHER_MENU:=Other modules
define KernelPackage/sdhci-mt7620
  SUBMENU:=Other modules
  TITLE:=MT7620 SDCI
  DEPENDS:=@(TARGET_mtmips_mt7620||TARGET_mtmips_mt7628||TARGET_mtmips_mt7621) +kmod-sdhci
  KCONFIG:= \
  CONFIG_MTK_MMC \
  CONFIG_MTK_AEE_KDUMP=n \
  CONFIG_MTK_MMC_CD_POLL=n \
  CONFIG_MTK_MMC_EMMC_8BIT=n
  FILES:= \
  $(LINUX_DIR)/drivers/mmc/host/mtk-mmc/mtk_sd.ko
  AUTOLOAD:=$(call AutoLoad,89,mtk_sd)
endef

$(eval $(call KernelPackage,sdhci-mt7620))

I2C_MTK_MODULES:= \
  CONFIG_I2C_MTK:drivers/i2c/busses/i2c-mtk

define KernelPackage/i2c-mtk
  $(call i2c_defaults,$(I2C_MTK_MODULES),59)
  TITLE:=MTK I2C Controller
  DEPENDS:=@TARGET_mtmips kmod-i2c-core
endef

define KernelPackage/i2c-mtk/description
 Kernel modules for enable MTK i2c controller.
endef

$(eval $(call KernelPackage,i2c-mtk))

define KernelPackage/sound-mt7620
  TITLE:=MT7620 PCM/I2S Alsa Driver
  DEPENDS:=@TARGET_ramips_mt7620 +kmod-sound-soc-core +kmod-regmap
  KCONFIG:= \
	CONFIG_SND_MT7620_SOC_I2S \
	CONFIG_SND_MT7620_SOC_WM8960
  FILES:= \
	$(LINUX_DIR)/sound/soc/ralink/snd-soc-mt7620-i2s.ko \
	$(LINUX_DIR)/sound/soc/ralink/snd-soc-mt7620-wm8960.ko \
	$(LINUX_DIR)/sound/soc/codecs/snd-soc-wm8960.ko
  AUTOLOAD:=$(call AutoLoad,89,snd-soc-wm8960 snd-soc-mt7620-i2s snd-soc-mt7620-wm8960)
  $(call AddDepends/sound)
endef

define KernelPackage/sound-mt7620/description
 Alsa modules for ralink i2s controller.
endef

$(eval $(call KernelPackage,sound-mt7620))

define KernelPackage/mtk-usb3
  TITLE:=Support for MT7621 USB3 controllers
  DEPENDS:=@TARGET_mtmips_mt7621
  KCONFIG:= \
        CONFIG_USB_XHCI_HCD \
        CONFIG_USB_XHCI_PLATFORM=y \
        CONFIG_USB_XHCI_HCD_DEBUGGING=n \
        CONFIG_USB_MT7621_XHCI_PLATFORM=y
  FILES:= \
        $(LINUX_DIR)/drivers/usb/host/xhci-hcd.ko
  AUTOLOAD:=$(call AutoLoad,54,xhci-hcd)
  $(call AddDepends/usb)
endef

define KernelPackage/mtk-usb3/description
  support for MT7621 USB3 (XHCI) controllers
endef

$(eval $(call KernelPackage,mtk-usb3))

define KernelPackage/mtk-hnat
  CATEGORY:=Ralink Properties
  SUBMENU:=Drivers
  TITLE:=MTK Hardware NAT
  DEPENDS:=@(TARGET_mtmips_mt7620||TARGET_mtmips_mt7621)
  KCONFIG:= \
  CONFIG_RA_HW_NAT=m \
  CONFIG_RA_HW_NAT_LAN_VLANID=1 \
  CONFIG_RA_HW_NAT_WAN_VLANID=2 \
  CONFIG_RA_HW_NAT_BINDING_THRESHOLD=30 \
  CONFIG_RA_HW_NAT_TBL_1K=n \
  CONFIG_RA_HW_NAT_TBL_2K=n \
  CONFIG_RA_HW_NAT_TBL_4K=n \
  CONFIG_RA_HW_NAT_TBL_8K=n \
  CONFIG_RA_HW_NAT_TBL_16K=y \
  CONFIG_HNAT_V2=y \
  CONFIG_RA_HW_NAT_HASH0=n \
  CONFIG_RA_HW_NAT_HASH1=y \
  CONFIG_RA_HW_NAT_HASH2=n \
  CONFIG_RA_HW_NAT_HASH3=n \
  CONFIG_RA_HW_NAT_TCP_KA=1 \
  CONFIG_RA_HW_NAT_UDP_KA=1 \
  CONFIG_RA_HW_NAT_NTU_KA=1 \
  CONFIG_RA_HW_NAT_UNB_DLTA=3 \
  CONFIG_RA_HW_NAT_UNB_MNP=1000 \
  CONFIG_RA_HW_NAT_UDP_DLTA=5 \
  CONFIG_RA_HW_NAT_TCP_DLTA=5 \
  CONFIG_RA_HW_NAT_FIN_DLTA=5 \
  CONFIG_RA_HW_NAT_NTU_DLTA=5 \
  CONFIG_RA_HW_NAT_IPV6=n \
  CONFIG_RA_HW_NAT_PREBIND=n \
  CONFIG_PPE_MCAST=n \
  CONFIG_RA_HW_NAT_WIFI=y \
  CONFIG_RA_HW_NAT_NIC_USB=n \
  CONFIG_RA_HW_NAT_ACCNT_MAINTAINER=n \
  CONFIG_RA_HW_NAT_PPTP_L2TP=n \
  CONFIG_SUPPORT_WLAN_OPTIMIZE=y \
  CONFIG_SUPPORT_WLAN_OPTIMIZE_TX=n \
  CONFIG_SUPPORT_WLAN_OPTIMIZE_RX=y
  FILES:=$(LINUX_DIR)/net/nat/hw_nat/hw_nat.ko
endef

define KernelPackage/mtk-hnat/description
  This driver support MT7621/MT7620 hardware nat function.
endef

$(eval $(call KernelPackage,mtk-hnat))

