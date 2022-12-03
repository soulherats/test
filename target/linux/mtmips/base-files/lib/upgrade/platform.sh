#
# Copyright (C) 2010 OpenWrt.org
#

. /lib/mtmips.sh

BOOT_NAME=u-boot
if [ -z "$(cat /proc/mtd | grep -w firmware_backup)" ]; then
PART_NAME=firmware
else
PART_NAME=firmware_backup
fi
RAMFS_COPY_DATA=/lib/mtmips.sh

platform_leds_blink() {
	. /lib/functions/leds.sh

	led_count=$(ls -al /sys/class/leds/ | grep "^l" | wc -l)
	led_delay_on=500
	let timer_count=led_count*1000
	let timer_count=timer_count-led_delay_on

	ls_file=$(ls /sys/class/leds)
	for filename in $ls_file
	do
		led_timer $filename $led_delay_on $timer_count
		sleep 1
	done
}

platform_check_image() {
	return 0
}

platform_hc_check_image() {
	local board=$(tw_board_name)
	local board_flash=$(mtmips_board_flash)
	local cpu_name=$(awk 'BEGIN{FS="[ \t]+:[ \t]"} /system type/ {print $2}' /proc/cpuinfo)

	[ "$#" -gt 1 ] && return 1

	case "$board_flash" in
	"nand")
		icheck -b "$board" -o 0x80000 -f "$1" -m >>$UPGRADE_LOG_FILE 2>&1
		;;
	*)
		case "$cpu_name" in
		*"Mediatek MT7620"*)
			case "$board" in
			"R33" | "R32" | "BL-W1210" | "G13")
				# new MT7620 board
				icheck -b "$board" -o 0x30000 -f "$1" >>$UPGRADE_LOG_FILE 2>&1
				;;
			*)
				icheck -b "$board" -o 0x30000 -f "$1" -n >>$UPGRADE_LOG_FILE 2>&1
				;;
			esac
			;;
		*)
			icheck -b "$board" -o 0x30000 -f "$1" >>$UPGRADE_LOG_FILE 2>&1
			;;
		esac
		;;
	esac

	return "$?"
}

# $1: image file
# $2: uboot exist (0/1)
# $3: save config (0/1)
do_upgrade_firmware() {
	local save_config_str=""

	upgrade_log "upgrade firmware"

	[ $3 -eq 1 ] && {
		sysupgrade_log "save config"
		save_config_str="-j $CONF_TAR"
	}

	if [ $2 -eq 0 ]; then
		get_image "$1" | mtd $save_config_str write - "${PART_NAME:-image}" >>$UPGRADE_LOG_FILE 2>&1
	else
		get_image "$1" | dd bs=2k skip=160 conv=sync 2>/dev/null | mtd $save_config_str write - "${PART_NAME:-image}" >>$UPGRADE_LOG_FILE 2>&1
	fi
}

platform_hc_upgrade_force() {
	local magic_boot="$(get_magic_boot "$1")"
	if [ $magic_boot == "ff00001000000000fd00001000000000" ]; then
		echo "Image has uboot (Force)"
		upgrade_log "Image has uboot (Force)"
		do_upgrade_firmware "$1" 1 $2
	else
		echo "Image no uboot (Force)"
		upgrade_log "Image no uboot (Force)"
		do_upgrade_firmware "$1" 0 $2
	fi
}

platform_hc_upgrade() {
	local cpu_name

	sync
	sync

	platform_leds_blink
	upgrade_log "memory"
	upgrade_log "mount"
	ps >>$UPGRADE_LOG_FILE
	upgrade_log_end

	if [ "$UPGRADE_BOOT" -eq 1 ]; then
		cpu_name=$(awk 'BEGIN{FS="[ \t]+:[ \t]"} /system type/ {print $2}' /proc/cpuinfo)
		case "$cpu_name" in
		*"Mediatek MT7621"*)
			img_bootloader_ver="$(mtmips_get_img_ver "$1")"
			;;
		*)
			img_bootloader_ver="$(mtmips_old_get_img_ver "$1")"
			;;
		esac
		bootloader_ver="$(mtmips_get_bootloader_ver "$1")"

		if [[ "$img_bootloader_ver" -gt "$bootloader_ver" ]]; then
			upgrade_log "upgrade uboot"
			get_image "$1" | dd bs=2k count=96 conv=sync 2>/dev/null | mtd write - "${BOOT_NAME:-image}" >>$UPGRADE_LOG_FILE 2>&1
			upgrade_log_end
		fi

		if [ "$SAVE_CONFIG" -eq 1 ]; then
			get_image "$1" | dd bs=2k skip=160 conv=sync 2>/dev/null | mtd $MTD_CONFIG_ARGS -j "$CONF_TAR" write - "${PART_NAME:-image}" >>$UPGRADE_LOG_FILE 2>&1
		else
			get_image "$1" | dd bs=2k skip=160 conv=sync 2>/dev/null | mtd write - "${PART_NAME:-image}" >>$UPGRADE_LOG_FILE 2>&1
		fi
	else
		platform_hc_upgrade_force "$ARGV"
	fi

	ret=$?

	if [ "$ret" -eq 0 ]; then
		upgrade_log "mtd ok"
	else
		upgrade_log "mtd failed with $ret"
	fi
	upgrade_log_end
}

platform_hc_nand_upgrade() {
	sync
	sync

	platform_leds_blink
	upgrade_log "memory"
	upgrade_log "mount"
	ps >>$UPGRADE_LOG_FILE
	upgrade_log_end

	if [ "$UPGRADE_BOOT" -eq 1 ]; then
		img_bootloader_ver="$(mtmips_get_img_ver_nand "$1")"
		bootloader_ver="$(mtmips_get_bootloader_ver "$1")"

		if [[ "$img_bootloader_ver" -gt "$bootloader_ver" ]]; then
			upgrade_log "upgrade uboot"
			get_image "$1" | dd bs=2k count=128 conv=sync 2>/dev/null | mtd write - "${BOOT_NAME:-image}" >>$UPGRADE_LOG_FILE 2>&1
			upgrade_log_end
		fi

		# squashfs + ubifs, skip 1280K
		get_image "$1" | dd bs=2k skip=640 conv=sync 2>/dev/null | mtd write - "${PART_NAME:-image}" >>$UPGRADE_LOG_FILE 2>&1
	else
		get_image "$1" | mtd write - "${PART_NAME:-image}" >>$UPGRADE_LOG_FILE 2>&1
	fi

	ret=$?

	if [ "$ret" -eq 0 ]; then
		upgrade_log "mtd ok"
	else
		upgrade_log "mtd failed with $ret"
	fi
	upgrade_log_end
}

platform_hc_copy_config() {
	local board_flash=$(mtmips_board_flash)

	case "$board_flash" in
	"nand")
		upgrade_log "Save config"
		rm -rf $1/*
		cp -af "$CONF_TAR" $1/
		sync
		;;
	esac
}

platform_hc_remove_config() {
	local board_flash=$(mtmips_board_flash)

	case "$board_flash" in
	"nand")
		upgrade_log "Drop config"
		rm -rf $1/*
		;;
	esac
}

platform_do_upgrade() {
	local board_flash=$(mtmips_board_flash)

	case "$board_flash" in
	"nand")
		platform_hc_nand_upgrade "$ARGV"
		;;
	*)
		platform_hc_upgrade "$ARGV"
		;;
	esac
}

platform_firmware_backup_upgrade() {
	. /lib/functions.sh

	fbackup=$(find_mtd_index "firmware_backup")
	if [ -n "$fbackup"  ]; then
		local board_flash=$(mtmips_board_flash)

		case "$board_flash" in
		"nand")
			upgrade_log "start backup($board)"
			platform_hc_nand_upgrade "$ARGV"
			if [ "$SAVE_CONFIG" -eq 1  ] && type 'platform_hc_copy_config' >/dev/null 2>/dev/null; then
				platform_hc_copy_config /overlay
			fi

			if [ "$SAVE_CONFIG" -eq 0  ] && type 'platform_hc_remove_config' >/dev/null 2>/dev/null; then
				platform_hc_remove_config /overlay
			fi
			sync
			reboot -f
			sleep 1
			force_reboot
			exit 1
			;;
		esac
	fi
}

disable_watchdog() {
	/etc/init.d/watchdog stop >/dev/null 2>&1
	killall watchdog >/dev/null 2>&1
	( ps | grep -v 'grep' | grep '/dev/watchdog' ) && {
		echo 'Could not disable watchdog'
		upgrade_log "stop watchdog failed"
		upgrade_log_end
		return 1
	}
}

append sysupgrade_pre_upgrade disable_watchdog
