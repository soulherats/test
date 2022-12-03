#!/bin/sh
#
# Copyright (C) 2010-2013 OpenWrt.org
#

RAMIPS_BOARD_NAME=
RAMIPS_MODEL=

mtmips_bootloader_ver() {
	dd if=/dev/mtdblock0 ibs=64 skip=3071 2>/dev/null | dd of=/tmp/sysinfo/boot_ver bs=15 skip=0 count=1 2>/dev/null
	cat /tmp/sysinfo/boot_ver | grep -qs "U_BOOT"
	if [ $? -ne 0 ]; then
		echo "U_BOOT 00000000" >/tmp/sysinfo/boot_ver
	fi
}

mtmips_old_bootloader_ver() {
	dd if=/dev/mtdblock0 ibs=64 skip=3071 2>/dev/null | dd of=/tmp/sysinfo/boot_ver bs=20 skip=0 count=1 2>/dev/null
	cat /tmp/sysinfo/boot_ver | grep -qs "HIWIFI_BOOT"
	if [ $? -ne 0 ]; then
		echo "HIWIFI_BOOT 00000000" >/tmp/sysinfo/boot_ver
	fi
}

mtmips_old_get_img_ver() {
	get_image "$@" | dd ibs=64 skip=3071 2>/dev/null | dd bs=20 skip=0 count=1 2>/dev/null | awk '{print $2}'
}

mtmips_bootloader_ver_nand() {
	dd if=/dev/mtdblock0 ibs=64 skip=4095 2>/dev/null | dd of=/tmp/sysinfo/boot_ver bs=15 skip=0 count=1 2>/dev/null
	cat /tmp/sysinfo/boot_ver | grep -qs "U_BOOT"
	if [ $? -ne 0 ]; then
		echo "U_BOOT 00000000" >/tmp/sysinfo/boot_ver
	fi
}

mtmips_get_img_ver() {
	get_image "$@" | dd ibs=64 skip=3071 2>/dev/null | dd bs=15 skip=0 count=1 2>/dev/null | awk '{print $2}'
}

mtmips_get_img_ver_nand() {
	get_image "$@" | dd ibs=64 skip=4095 2>/dev/null | dd bs=15 skip=0 count=1 2>/dev/null | awk '{print $2}'
}

mtmips_get_bootloader_ver() {
	cat /tmp/sysinfo/boot_ver | awk '{print $2}'
}

mtmips_board_flash() {
	local name="spi"

	[ -f /proc/driver/nand ] && name="nand"

	echo "$name"
}

mtmips_board_detect() {
	local machine
	local name
	local cpu_name
	local board_flash=$(mtmips_board_flash)
	local total_memory

	machine=$(awk 'BEGIN{FS="[ \t]+:[ \t]"} /machine/ {print $2}' /proc/cpuinfo)
	cpu_name=$(awk 'BEGIN{FS="[ \t]+:[ \t]"} /system type/ {print $2}' /proc/cpuinfo)
	total_memory=$(awk '/MemTotal:/ {print $2}' /proc/meminfo)

	case "$machine" in
	*"HiWiFi Wireless HC5661 Board")
		name="HC5661"
		;;
	*"HiWiFi Wireless HC5761s Board")
		name="HC5761s"
		;;
	*"HiWiFi Wireless HC5642 Board")
		name="HC5642"
		;;
	*"HiWiFi Wireless HC5661s Board")
		name="HC5661s"
		;;
	*"HiWiFi Wireless HC5611 Board")
		name="HC5611"
		;;
	*"HiWiFi Wireless HC5861B Board")
		name="HC5861B"
		;;
	*"HiWiFi Wireless HC5661B Board")
		name="HC5661B"
		;;
	*"HiWiFi Wireless HB5801 Board")
		name="HB5801"
		;;
	*"HiWiFi Wireless R7628AC1 Board")
		name="R7628AC1"
		;;
	*"HiWiFi Wireless BL-AC1200D Board")
		name="BL-AC1200D"
		;;
        *"HiWiFi Wireless BL-F300 Board")
                name="BL-F300"
                ;;
        *"HiWiFi Wireless BL-W1210 Board")
                name="BL-W1210"
                ;;
	*"HiWiFi Wireless HC5661 Board")
		name="HC5661"
		;;
	*"HiWiFi Wireless HC5663 Board")
		name="HC5663"
		;;
	*"HiWiFi Wireless HC5761 Board")
		name="HC5761"
		;;
	*"HiWiFi Wireless HC5861 Board")
		name="HC5861"
		;;
	*"HiWiFi Wireless B50 Board")
		name="B50"
		;;
	*"HiWiFi Wireless R32 Board")
		name="R32"
		;;
	*"HiWiFi Wireless R33 Board")
		name="R33"
		;;
	*"HiWiFi Wireless HB5881 Board")
		name="HB5881"
		;;
	*"HiWiFi Wireless HB5811 Board")
		name="HB5811"
		;;
	*"HiWiFi-HB-845H Board")
		name="BL-855R"
		;;
	*"HiWiFi-HB-750ACH Board")
		name="BL-H750AC"
		;;
	*"HiWiFi-HB-8100 Board")
		name="BL-T8100"
		;;
	*"HiWiFi Wireless ZC-9525 Board")
		name="ZC-9525"
		;;
	*"HiWiFi Wireless ZC-9526 Board")
		name="ZC-9526"
		;;
	*"HiWiFi Wireless ZC-9527 Board")
		name="ZC-9527"
		;;
	*"HiWiFi Wireless ZC-9527R Board")
		name="ZC-9527R"
		;;
	*"HiWiFi Wireless ZC-9528 Board")
		name="ZC-9528"
		;;
	*"HiWiFi Wireless WIFI-Link-2950 Board")
		name="WIFI-Link-2950"
		;;
	*"HiWiFi Wireless HC5961 Board")
		name="HC5961"
		;;
        *"HiWiFi Wireless BL-WR4122H Board")
                name="BL-WR4122H"
                ;;
	*"HiWiFi Wireless HC5962 Board")
		name="HC5962"
		;;
        *"HiWiFi Wireless HC5963 Board")
                name="HC5963"
                ;;
        *"HiWiFi Wireless HC5964 Board")
                name="HC5964"
                ;;
	*"HiWiFi Wireless R31 Board")
		name="R31"
		;;
        *"HiWiFi Wireless G13 Board")
                name="G13"
                ;;
	*)
		name="generic"
		;;
	esac

	[ -z "$RAMIPS_BOARD_NAME" ] && RAMIPS_BOARD_NAME="$name"
	[ -z "$RAMIPS_MODEL" ] && RAMIPS_MODEL="$machine"
	[ -z "$total_memory" ] && total_memory=0

	[ -e "/tmp/sysinfo/" ] || mkdir -p "/tmp/sysinfo/"

	echo "$RAMIPS_BOARD_NAME" > /tmp/sysinfo/board_name
	echo "$RAMIPS_MODEL" > /tmp/sysinfo/model
	echo "$total_memory" > /tmp/sysinfo/total_memory

	case "$board_flash" in
	"nand")
		mtmips_bootloader_ver_nand
		;;
	*)
		case "$cpu_name" in
		*"Mediatek MT7628"*)
			mtmips_old_bootloader_ver
			;;
		*"Mediatek MT7620"*)
			mtmips_old_bootloader_ver
			;;
		*)
			mtmips_bootloader_ver
			;;
		esac
		;;
	esac
}

tw_board_name() {
	local name

	[ -f /tmp/sysinfo/board_name ] && name=$(cat /tmp/sysinfo/board_name)
	[ -z "$name" ] && name="unknown"

	echo "$name"
}

tw_total_memory() {
	[ -f /tmp/sysinfo/total_memory ] && memory=$(cat /tmp/sysinfo/total_memory)
	[ -z "$memory" ] && memory="0"

	echo "$memory"
}

tw_get_mac() {
	ifconfig eth2 | grep HWaddr | awk '{ print $5 }' | awk -F: '{printf $1$2$3$4$5$6}'
}

platfrom_console_login_fixup() {
	if [ "$1" -eq 0 ]; then
		# disable console login
		sed -i "/--login/d" /etc/inittab
		sync
	else
		# enable console login
		local initline="::askconsole:/bin/ash --login"

		grep -qs "^$initline" /etc/inittab || {
			echo "$initline" >> /etc/inittab
			sync
		}
	fi
}

platform_guest_ifname() {
	local board=$(tw_board_name)
	local apflag=$(uci get hiwifi.board.type)

	if [ "$apflag" = "ap" ]; then
		case $board in
		"HC5961" | "HC5962")
			echo "eth3.3 "
			;;
		*)
			echo "eth2.3 "
			;;
		esac
	else
		echo "eth2.3 "
	fi
}

hiwifi_hardware_version() {
	if [ -f /proc/hiwifi/hardware_version ]; then
		cat /proc/hiwifi/hardware_version
	else
		echo "1"
	fi
}
