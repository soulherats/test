#!/bin/sh

. /lib/functions/system.sh
. /lib/hw/base.sh

cpu_name="$(get_cpu_system_type)"

mmc_test() {
	local mmc="$(uci -q get hiwifi.info.mmc)"
	if [ -z "$mmc" -o "$mmc" == "0" ]; then
		echo "mmc test pass"
		return
	fi

	local mmc_dev=$(ls -al /sys/block/ | grep "mmc" | awk '{print $9}')

	if [ -z "$mmc_dev" ]; then
		echo "mmc(no device) test fail"
		echo "$HIWIFI_HW_MMC_DEV_ERROR" >$HIWIFI_HW_TEST_FILE
		exit 1
	fi

	mount | grep -q "$mmc_dev" | grep -q "ro,"

	if [ $? -eq 0 ]; then
		echo "mmc test fail"
		echo "$HIWIFI_HW_MMC_RO_ERROR" >$HIWIFI_HW_TEST_FILE
		exit 1
	else
		echo "mmc test pass"
	fi
}

usb2_test() {
	local usb2="$(uci -q get hiwifi.info.usb2)"

	if [ -z "$usb2" -o "$usb2" == "0" ]; then
		echo "usb2.0(none) test pass"
		return
	fi

	case "$cpu_name" in
	*"Mediatek MT7621"*)
		local usb_dev=$(ls -al /sys/block/ | grep "usb1" | awk '{print $9}')

		if [ -z "$usb_dev" ]; then
			echo "usb2.0(no device) test fail"
			echo "$HIWIFI_HW_USB2_DEV_ERROR" >$HIWIFI_HW_TEST_FILE
			exit 1
		fi

		mount | grep -q "$usb_dev" | grep -q "ro,"

		if [ $? -eq 0 ]; then
			echo "usb2.0 test fail"
			echo "$HIWIFI_HW_USB2_RO_ERROR" >$HIWIFI_HW_TEST_FILE
			exit 1
		else
			echo "usb2.0 test pass"
		fi
		;;
	*)
		local usb_dev=$(ls -al /sys/block/ | grep "usb1" | awk '{print $9}')

		if [ -z "$usb_dev" ]; then
			echo "usb2.0(no device) test fail"
			echo "$HIWIFI_HW_USB2_DEV_ERROR" >$HIWIFI_HW_TEST_FILE
			exit 1
		fi

		mount | grep -q "$usb_dev" | grep -q "ro,"

		if [ $? -eq 0 ]; then
			echo "usb2.0 test fail"
			echo "$HIWIFI_HW_USB2_RO_ERROR" >$HIWIFI_HW_TEST_FILE
			exit 1
		else
			echo "usb2.0 test pass"
		fi
		;;
	esac	
}

usb3_test() {
	local usb3="$(uci -q get hiwifi.info.usb3)"

	if [ -z "$usb3" -o "$usb3" == "0" ]; then
		echo "usb3.0(none) test pass"
		return
	fi

	case "$cpu_name" in
	*"Mediatek MT7621"*)
		local usb_dev=$(ls -al /sys/block/ | grep "usb2" | awk '{print $9}')

		if [ -z "$usb_dev" ]; then
			echo "usb3.0(no device) test fail"
			echo "$HIWIFI_HW_USB3_DEV_ERROR" >$HIWIFI_HW_TEST_FILE
			exit 1
		fi

		mount | grep -q "$usb_dev" | grep -q "ro,"

		if [ $? -eq 0 ]; then
			echo "usb3.0 test fail"
			echo "$HIWIFI_HW_USB3_RO_ERROR" >$HIWIFI_HW_TEST_FILE
			exit 1
		else
			echo "usb3.0 test pass"
		fi
		;;
	*)
		echo "usb3.0 test pass"
		;;
	esac
}

sata_test() {
	local sata="$(uci -q get hiwifi.info.sata)"

	if [ -z "$sata" -o "$sata" == "0" ]; then
		echo "sata(none) test pass"
		return
	fi

	local ata_dev=$(ls -al /sys/block/ | grep "ata" | awk '{print $9}')

	if [ -z "$ata_dev" ]; then
		echo "sata(no device) test fail"
		echo "$HIWIFI_HW_SATA_DEV_ERROR" >$HIWIFI_HW_TEST_FILE
		exit 1
	fi

	mount | grep -q "$ata_dev" | grep -q "ro,"

	if [ $? -eq 0 ]; then
		echo "sata test fail"
		echo "$HIWIFI_HW_SATA_RO_ERROR" >$HIWIFI_HW_TEST_FILE
		exit 1
	else
		echo "sata test pass"
	fi
}

nand_test() {
	local nand="$(uci -q get hiwifi.info.nand)"

	if [ -z "$nand" -o "$nand" == "0" ]; then
		echo "nand(none) test pass"
		return
	fi

	mount | grep -q "opt"

	if [ $? -ne 0 ]; then
		echo "nand test fail"
		echo "$HIWIFI_HW_NAND_ERROR" >$HIWIFI_HW_TEST_FILE
		exit 1
	else
		echo "nand test pass"
	fi
}