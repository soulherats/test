#
# Copyright (C) 2013-2014
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

ROM_PREFIX:=$(shell date '+%y%m%d-%H%M%S')

KDIR_TMP:=$(KDIR)/tmp

define mkcmdline
board=$(1) console=$(2),$(3)
endef

define imgname
$(BIN_DIR)/$(IMG_PREFIX)-$(2)-$(1)
endef

define sysupname
$(call imgname,$(1),$(2))-sysupgrade.bin
endef

# NAND ubifs: factory smt
define facupname
$(call imgname,$(1),$(2))-factory.bin
endef

ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
VMLINUX:=$(IMG_PREFIX)-vmlinux-initramfs
UIMAGE:=$(IMG_PREFIX)-uImage-initramfs
else
VMLINUX:=$(IMG_PREFIX)-vmlinux
UIMAGE:=$(IMG_PREFIX)-uImage
endif

ifeq ($(CONFIG_RALINK_MT7621),y)
MTK_ECC_TOOLS:=mt7621-ecc e 2048 64
define kernel_entry
-a $(CONFIG_KERNEL_START_ADDR) -e $(CONFIG_KERNEL_START_ADDR)
endef

else
MTK_ECC_TOOLS:=mt7620-ecc 64
define kernel_entry
-a 0x80000000 -e 0x80000000
endef
endif

define Image/Prepare
	$(CP) ./ubinize.cfg $(KDIR)
endef

define CompressLzma
	$(STAGING_DIR_HOST)/bin/lzma e $(1) -lc1 -lp2 -pb2 $(2)
endef

define PatchKernelLzma
	cp $(KDIR)/vmlinux $(KDIR)/vmlinux-$(1)
	$(STAGING_DIR_HOST)/bin/patch-cmdline $(KDIR)/vmlinux-$(1) '$(strip $(2))'
	$(call CompressLzma,$(KDIR)/vmlinux-$(1),$(KDIR)/vmlinux-$(1).bin.lzma)
endef

define MkImage
	$(eval imagename=$(if $(4),$(4),$(4) Linux-$(LINUX_VERSION)))
	mkimage -A mips -O linux -T kernel -C $(1) $(call kernel_entry)\
		-n "$(imagename)" \
		-d $(2) $(3)
endef

define MkImageLzma
	$(call PatchKernelLzma,$(1),$(2))
	$(call MkImage,lzma,$(KDIR)/vmlinux-$(1).bin.lzma,$(KDIR)/vmlinux-$(1).uImage,$(3))
endef

define MkImageLzma/initramfs
	$(call PatchKernelLzma,$(1)-initramfs,$(2))
	$(call MkImage,lzma,$(KDIR)/vmlinux-$(1)-initramfs.bin.lzma,$(KDIR)/vmlinux-$(1)-initramfs.uImage.bin,$(3))
endef

define CatFiles
	if [ `stat -c%s "$(1)"` -gt $(2) ]; then \
		echo "Warning: $(1) is too big"; \
	else if [ `stat -c%s $(3)` -gt $(4) ]; then \
		echo "Warning: $(3) is too big"; \
	else \
		( dd if=$(1) bs=$(2) conv=sync; dd if=$(3) ) > $(5); \
	fi; fi
endef

define AppendFiles
	( \
		dd if=$(1) bs=$(5) conv=sync; \
		dd if=$(2); \
	) > $(4); \
	if [ `stat -c%s $(4)` -gt $(3) ]; then \
		echo "Warning: sysup img is too big"; \
		rm -rf $(4); \
	fi
endef

# 1: file system name(squashfs)
# 2: board name(HC5661)
# 3: sysupgrade name
# 4: block size(spi:64K, nand: 128/256/512)
ifeq ($(CONFIG_FIRMWARE_BACKUP),y)
define Sysupgrade/KRuImage
	(dd if=$(KDIR)/vmlinux-$(2).uImage; echo 0 | printf %096x 0 | xxd -r -ps | dd conv=notrunc bs=1 count=48) >$(KDIR)/vmlinux-$(2)-md5.uImage
	$(call AppendFiles,$(KDIR)/vmlinux-$(2)-md5.uImage,$(KDIR)/root.$(1),$(3),$(call sysupname,$(1),$(2)),$(4))
	mksysup -f $(call sysupname,$(1),$(2))
endef
else
define Sysupgrade/KRuImage
	$(call AppendFiles,$(KDIR)/vmlinux-$(2).uImage,$(KDIR)/root.$(1),$(3),$(call sysupname,$(1),$(2)),$(4))
endef
endif

define SysupgradeNAND/KRuImage
	$(call Image/Build/SysupgradeNAND,$(2),squashfs,$(KDIR)/vmlinux-$(2).uImage)
	$(call AppendFiles,$(KDIR)/vmlinux-$(2).uImage,$(KDIR)/root-block-0x20000-min-0x800-eof.ubi,$(3),$(call facupname,$(1),$(2)),4096k)
endef

define Image/BuildKernel
	cp $(KDIR)/vmlinux.elf $(BIN_DIR)/$(VMLINUX).elf
	cp $(KDIR)/vmlinux $(BIN_DIR)/$(VMLINUX).bin
	$(call CompressLzma,$(KDIR)/vmlinux,$(KDIR)/vmlinux.bin.lzma)
	$(call MkImage,lzma,$(KDIR)/vmlinux.bin.lzma,$(KDIR)/uImage.lzma)
	cp $(KDIR)/uImage.lzma $(BIN_DIR)/$(UIMAGE).bin
ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)	
	$(call Image/Build/Initramfs)
endif
endef

define BuildFirmware/hcdebug
	(cd $(DEBUG_TARGET_DIR);cp -f $(LINUX_DIR)/vmlinux-debug $(DEBUG_TARGET_DIR); tar -czf $(BIN_DIR)/$(1)/debug-root-$(REVISION)-$(BOARD)-$(1).tgz *)
	(mkdir -p $(BIN_DIR)/debug-root)
	(cp -rf $(BIN_DIR)/$(1)/debug-root-$(REVISION)-$(BOARD)-$(1).tgz $(BIN_DIR)/debug-root/debug-root-$(REVISION)-$(BOARD)-$(1).tgz)
endef

#$(1)squashfs $(2)HCMT7620 $(3)board=HCMT7620 console=ttyS1, 115200 $(4)16318464 $(5)HCMT7620
define BuildFirmware/hc
	@mkdir -p $(BIN_DIR)/$(2)
	$(call MkImageLzma,$(2),$(3),$(5))
	$(call Sysupgrade/KRuImage,$(1),$(2),$(4),64k)
	$(CP) $(call sysupname,$(1),$(2)) $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin; \
	if [ -f "$(BIN_DIR)/$(2)-uboot.bin" ]; then \
		$(CP) $(BIN_DIR)/$(2)-uboot.bin $(BIN_DIR)/$(2)/; \
		if [ -f $(TOPDIR)/hiwifi-keys/hiwifi.key -a $(TOPDIR)/hiwifi-keys/hiwifi.crt ]; then \
			(dd if=$(BIN_DIR)/$(2)/$(2)-uboot.bin bs=196608 conv=sync;) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin; \
			$(STAGING_DIR_HOST)/bin/hc-sign -b $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin -s $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin -o $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sign -k $(TOPDIR)/hiwifi-keys/hiwifi.key -c $(TOPDIR)/hiwifi-keys/hiwifi.crt;\
			(dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin bs=196608 conv=sync; dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sign) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-sign.bin; \
			(dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-sign.bin bs=327680 conv=sync; dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin ) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-flash.bin; \
			rm -rf $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-sign.bin $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sign; \
		else \
			(dd if=$(BIN_DIR)/$(2)/$(2)-uboot.bin bs=327680 conv=sync; dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin ) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-flash.bin; \
		fi; \
	fi;
	$(call BuildFirmware/hcdebug,$(2))
endef

# mt7620 use old sign
# $(1)squashfs $(2)HCMT7620 $(3)board=HCMT7620 console=ttyS1, 115200 $(4)16318464 $(5)HCMT7620
define BuildFirmware/hcold
	@mkdir -p $(BIN_DIR)/$(2)
	$(call MkImageLzma,$(2),$(3),$(5))
	$(call Sysupgrade/KRuImage,$(1),$(2),$(4),64k)
	$(CP) $(call sysupname,$(1),$(2)) $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin; \
	if [ -f "$(BIN_DIR)/$(2)-uboot.bin" ]; then \
		$(CP) $(BIN_DIR)/$(2)-uboot.bin $(BIN_DIR)/$(2)/; \
		if [ -f $(TOPDIR)/hiwifi-keys/hiwifi.key -a $(TOPDIR)/hiwifi-keys/hiwifi.crt ]; then \
			(dd if=$(BIN_DIR)/$(2)/$(2)-uboot.bin bs=196608 conv=sync;) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin; \
			$(STAGING_DIR_HOST)/bin/hc-old-sign -i $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin -o $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sign -k $(TOPDIR)/hiwifi-keys/hiwifi.key -c $(TOPDIR)/hiwifi-keys/hiwifi.crt;\
			(dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin bs=196608 conv=sync; dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sign) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-sign.bin; \
			(dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-sign.bin bs=327680 conv=sync; dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin ) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-flash.bin; \
			rm -rf $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-sign.bin $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sign; \
		else \
			(dd if=$(BIN_DIR)/$(2)/$(2)-uboot.bin bs=327680 conv=sync; dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin ) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-flash.bin; \
		fi; \
	fi;
	$(call BuildFirmware/hcdebug,$(2))
endef

# u-boot: 512K
# config: 512K
# factory: 256K
# firmware: 32MB
# kpanic: 512K
# bdinfo: 512K
# reserve: 512K
# opt: ~
define BuildFirmware/hcNAND
	@mkdir -p $(BIN_DIR)/$(2)
	$(call MkImageLzma,$(2),$(3),$(5))
	$(call Sysupgrade/KRuImage,$(1),$(2),$(4),128k)
	$(CP) $(call sysupname,$(1),$(2)) $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin; \
	if [ -f "$(BIN_DIR)/$(2)-uboot.bin" ]; then \
		$(CP) $(BIN_DIR)/$(2)-uboot.bin $(BIN_DIR)/$(2)/; \
		if [ -f $(TOPDIR)/hiwifi-keys/hiwifi.key -a $(TOPDIR)/hiwifi-keys/hiwifi.crt ]; then \
			(dd if=$(BIN_DIR)/$(2)/$(2)-uboot.bin bs=524288 conv=sync;) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin; \
			$(STAGING_DIR_HOST)/bin/hc-sign -b $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin -s $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin -o $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sign -k $(TOPDIR)/hiwifi-keys/hiwifi.key -c $(TOPDIR)/hiwifi-keys/hiwifi.crt;\
			(dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin bs=524288 conv=sync; dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sign) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-sign.bin; \
			(dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-sign.bin bs=1310720 conv=sync; dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin ) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-flash.bin; \
			echo "use $(MTK_ECC_TOOLS) ecc";\
			$(STAGING_DIR_HOST)/bin/$(MTK_ECC_TOOLS) $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-flash.bin $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-flash-ecc.bin >/dev/null 2>&1; \
			rm -rf $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-pad.bin $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-uboot-sign.bin $(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sign; \
		else \
			(dd if=$(BIN_DIR)/$(2)/$(2)-uboot.bin bs=1310720 conv=sync; dd if=$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-sysupgrade.bin ) >$(BIN_DIR)/$(2)/$(2)-$(ROM_PREFIX)-flash.bin; \
		fi; \
	fi;
	$(call BuildFirmware/hcdebug,$(2))
endef

define BuildFirmware/hc/initramfs
	$(call MkImageLzma/initramfs,$(2),$(3),$(5))
	@cp -f $(KDIR)/vmlinux-$(2)-initramfs.uImage.bin $(BIN_DIR)/$(IMG_PREFIX)-$(2)-initramfs.uImage.bin
endef

define BuildFirmware/hc_8M
	$(call BuildFirmware/hc,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),7929856,$(6))
endef

define BuildFirmware/hc_16M
	$(call BuildFirmware/hc,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),16318464,$(6))
endef

define BuildFirmware/hc_32M
        $(call BuildFirmware/hc,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),33554432,$(6))
endef

define BuildFirmware/hcold_16M
	$(call BuildFirmware/hcold,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),16318464,$(6))
endef

define BuildFirmware/hc_N32M
	$(call BuildFirmware/hcNAND,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),33554432,$(6))
endef

define BuildFirmware/hc_8M/initramfs
	$(call BuildFirmware/hc/initramfs,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),7929856,$(6))
endef

define BuildFirmware/hc_16M/initramfs
	$(call BuildFirmware/hc/initramfs,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),16318464,$(6))
endef

define BuildFirmware/hc_32M/initramfs
        $(call BuildFirmware/hc/initramfs,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),33554432,$(6))
endef

define BuildFirmware/hc_N32M/initramfs
	$(call BuildFirmware/hc/initramfs,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),33554432,$(6))
endef

define Image/Build/squashfs
	# create ubifs and ubifs eof
	( cd $(KDIR); $(STAGING_DIR_HOST)/bin/ubinize -p 128KiB -m 2048 -o $(KDIR)/root-block-0x20000-min-0x800.ubi ubinize.cfg; $(STAGING_DIR_HOST)/bin/ubinize -p 128KiB -m 2048 -o $(KDIR)/root-block-0x20000-min-0x800-eof.ubi ubinize.cfg -E 5)
	# Align and append a JFFS marker
	$(call prepare_generic_squashfs,$(KDIR)/root.$(1))
endef

define BuildFirmware/hc_N16M
	$(call BuildFirmware/hcNAND,$(1),$(2),$(call mkcmdline,$(3),$(4),$(5)),16318464,$(6))
endef

define Image/Build/Profile/HCMT7621
	$(call BuildFirmware/hc_16M,$(1),HCMT7621,HCMT7621,ttyS1,115200,HCMT7621)
endef

define Image/Build/Profile/HCMT7621/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HCMT7621,HCMT7621,ttyS1,115200,HCMT7621)
endef

define Image/Build/Profile/HCMT7621-S128
	$(call BuildFirmware/hc_16M,$(1),HCMT7621-S128,HCMT7621-S128,ttyS1,115200,HCMT7621-S128)
endef

define Image/Build/Profile/HCMT7621-S128/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HCMT7621-S128,HCMT7621-S128,ttyS1,115200,HCMT7621-S128)
endef

define Image/Build/Profile/HCMT7621-N128
	$(call BuildFirmware/hc_N32M,$(1),HCMT7621-N128,HCMT7621-N128,ttyS1,115200,HCMT7621-N128)
endef

define Image/Build/Profile/HCMT7621-N128/initramfs
	$(call BuildFirmware/hc_N32M/initramfs,$(1),HCMT7621-N128,HCMT7621-N128,ttyS1,115200,HCMT7621-N128)
endef

define Image/Build/Profile/HC5961
	$(call BuildFirmware/hc_N32M,$(1),HC5961,HC5961,ttyS1,115200,HC5961)
endef

define Image/Build/Profile/HC5961/initramfs
	$(call BuildFirmware/hc_N32M/initramfs,$(1),HC5961,HC5961,ttyS1,115200,HC5961)
endef

define Image/Build/Profile/HC5962
	$(call BuildFirmware/hc_N32M,$(1),HC5962,HC5962,ttyS1,115200,HC5962)
endef

define Image/Build/Profile/HC5962/initramfs
	$(call BuildFirmware/hc_N32M/initramfs,$(1),HC5962,HC5962,ttyS1,115200,HC5962)
endef

define Image/Build/Profile/HC5963
        $(call BuildFirmware/hc_N32M,$(1),HC5963,HC5963,ttyS1,115200,HC5963)
endef

define Image/Build/Profile/HC5963/initramfs
        $(call BuildFirmware/hc_N32M/initramfs,$(1),HC5963,HC5963,ttyS1,115200,HC5963)
endef

define Image/Build/Profile/HC5964
        $(call BuildFirmware/hc_N32M,$(1),HC5964,HC5964,ttyS1,115200,HC5964)
endef

define Image/Build/Profile/HC5964/initramfs
        $(call BuildFirmware/hc_N32M/initramfs,$(1),HC5964,HC5964,ttyS1,115200,HC5964)
endef

define Image/Build/Profile/BLWR4122H
        $(call BuildFirmware/hc_32M,$(1),BL-WR4122H,BL-WR4122H,ttyS1,115200,BL-WR4122H)
endef

define Image/Build/Profile/BLWR4122H/initramfs
        $(call BuildFirmware/hc_32M/initramfs,$(1),BL-WR4122H,BL-WR4122H,ttyS1,115200,BL-WR4122H)
endef

# mt7620
define Image/Build/Profile/HC5661
	$(call BuildFirmware/hcold_16M,$(1),HC5661,HC5661,ttyS1,115200,HC5661)
endef

define Image/Build/Profile/HC5661/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HC5661,HC5661,ttyS1,115200,HC5661)
endef

define Image/Build/Profile/HC5761
	$(call BuildFirmware/hcold_16M,$(1),HC5761,HC5761,ttyS1,115200,HC5761)
endef

define Image/Build/Profile/HC5761/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HC5761,HC5761,ttyS1,115200,HC5761)
endef

define Image/Build/Profile/HC5861
	$(call BuildFirmware/hcold_16M,$(1),HC5861,HC5861,ttyS1,115200,HC5861)
endef

define Image/Build/Profile/HC5861/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HC5861,HC5861,ttyS1,115200,HC5861)
endef

define Image/Build/Profile/B50
	$(call BuildFirmware/hcold_16M,$(1),B50,B50,ttyS1,115200,B50)
endef

define Image/Build/Profile/B50/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),B50,B50,ttyS1,115200,B50)
endef

define Image/Build/Profile/HB845H
        $(call BuildFirmware/hcold_16M,$(1),BL-855R,BL-855R,ttyS1,115200,BL-855R)
endef

define Image/Build/Profile/HB845H/initramfs
        $(call BuildFirmware/hc_16M/initramfs,$(1),BL-855R,BL-855R,ttyS1,115200,BL-855R)
endef

# new MT7620 product; use new layout
define Image/Build/Profile/BLW1210
        $(call BuildFirmware/hc_16M,$(1),BL-W1210,BL-W1210,ttyS1,115200,BL-W1210)
endef

define Image/Build/Profile/BLW1210/initramfs
        $(call BuildFirmware/hc_16M/initramfs,$(1),BL-W1210,BL-W1210,ttyS1,115200,BL-W1210)
endef

define Image/Build/Profile/G13
        $(call BuildFirmware/hc_16M,$(1),G13,G13,ttyS1,115200,G13)
endef

define Image/Build/Profile/G13/initramfs
        $(call BuildFirmware/hc_16M/initramfs,$(1),G13,G13,ttyS1,115200,G13)
endef

define Image/Build/Profile/R33
	$(call BuildFirmware/hc_N32M,$(1),R33,R33,ttyS1,115200,R33)
endef

define Image/Build/Profile/R33/initramfs
	$(call BuildFirmware/hc_N32M/initramfs,$(1),R33,R33,ttyS1,115200,R33)
endef

define Image/Build/Profile/R32
	$(call BuildFirmware/hc_N32M,$(1),R32,R32,ttyS1,115200,R32)
endef

define Image/Build/Profile/R32/initramfs
	$(call BuildFirmware/hc_N32M/initramfs,$(1),R32,R32,ttyS1,115200,R32)
endef

# mt7628
define Image/Build/Profile/HC5661s
	$(call BuildFirmware/hc_16M,$(1),HC5661A,HC5661A,ttyS1,115200,HC5661s)
endef

define Image/Build/Profile/HC5661s/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HC5661A,HC5661A,ttyS1,115200,HC5661s)
endef

define Image/Build/Profile/HC5761s
	$(call BuildFirmware/hc_16M,$(1),HC5761A,HC5761A,ttyS1,115200,HC5761s)
endef

define Image/Build/Profile/HC5761s/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HC5761A,HC5761A,ttyS1,115200,HC5761s)
endef

define Image/Build/Profile/HC5642
	$(call BuildFirmware/hc_8M,$(1),HC5642,HC5642,ttyS1,115200,HC5642)
endef

define Image/Build/Profile/HC5642/initramfs
	$(call BuildFirmware/hc_8M/initramfs,$(1),HC5642,HC5642,ttyS1,115200,HC5642)
endef

define Image/Build/Profile/ZC9525A
	$(call BuildFirmware/hc_16M,$(1),ZC-9525A,ZC-9525A,ttyS1,115200,ZC-9525A)
endef

define Image/Build/Profile/ZC9525A/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),ZC-9525A,ZC-9525A,ttyS1,115200,ZC-9525A)
endef

define Image/Build/Profile/HC5611
	$(call BuildFirmware/hc_16M,$(1),HC5611,HC5611,ttyS1,115200,HC5611)
endef

define Image/Build/Profile/HC5611/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HC5611,HC5611,ttyS1,115200,HC5611)
endef

define Image/Build/Profile/R31
	$(call BuildFirmware/hc_16M,$(1),R31,R31,ttyS1,115200,R31)
endef

define Image/Build/Profile/R31/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),R31,R31,ttyS1,115200,R31)
endef

# mt7628 blink
define Image/Build/Profile/R7628AC1
	$(call BuildFirmware/hc_16M,$(1),R7628AC1,R7628AC1,ttyS1,115200,R7628AC1)
endef

define Image/Build/Profile/R7628AC1/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),R7628AC1,R7628AC1,ttyS1,115200,R7628AC1)
endef

define Image/Build/Profile/AC1200D
	$(call BuildFirmware/hc_16M,$(1),BL-AC1200D,BL-AC1200D,ttyS1,115200,BL-AC1200D)
endef

define Image/Build/Profile/AC1200D/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),BL-AC1200D,BL-AC1200D,ttyS1,115200,BL-AC1200D)
endef

define Image/Build/Profile/BLF300
        $(call BuildFirmware/hc_16M,$(1),BL-F300,BL-F300,ttyS1,115200,BL-F300)
endef

define Image/Build/Profile/BLF300/initramfs
        $(call BuildFirmware/hc_16M/initramfs,$(1),BL-F300,BL-F300,ttyS1,115200,BL-F300)
endef

define Image/Build/Profile/HC5861B
	$(call BuildFirmware/hc_16M,$(1),HC5861B,HC5861B,ttyS1,115200,HC5861B)
endef

define Image/Build/Profile/HC5861B/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HC5861B,HC5861B,ttyS1,115200,HC5861B)
endef

define Image/Build/Profile/HC5661B
	$(call BuildFirmware/hc_16M,$(1),HC5661B,HC5661B,ttyS1,115200,HC5661B)
endef

define Image/Build/Profile/HC5661B/initramfs
	$(call BuildFirmware/hc_16M/initramfs,$(1),HC5661B,HC5661B,ttyS1,115200,HC5661B)
endef

define Image/Build/Initramfs
	$(call Image/Build/Profile/$(PROFILE)/initramfs,$(1))
endef

define Image/Build
	$(call Image/Build/$(1),$(1))
	dd if=$(KDIR)/root.$(1) of=$(BIN_DIR)/$(IMG_PREFIX)-root.$(1) bs=64k conv=sync
	$(call Image/Build/Profile/$(PROFILE),$(1))
endef

$(eval $(call BuildImage))
