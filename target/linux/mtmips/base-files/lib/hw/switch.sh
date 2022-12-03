#!/bin/sh

. /lib/platform.sh
. /lib/functions/system.sh
. /usr/share/libubox/jshn.sh
. /lib/hw/base.sh

dump_wan_status() {
	local payload=$(himsg -p system.hboardd -m status_wan -rv 2>/dev/null | sed -n '/payload:/ s/payload://p')
	local test_speed="$1"

	if [ -n "$payload" ]; then
		json_load "$payload"
		json_get_var wan_link link
		json_get_var wan_speed speed 
		if [ "$wan_link" != "up" ]; then
			echo "wan port link failed"
			echo "$HIWIFI_HW_WAN_LINK_ERROR" >$HIWIFI_HW_TEST_FILE
			exit 1
		fi

		if [ "$test_speed" != "$wan_speed" ]; then
			echo "wan port test($test_speed $wan_speed) failed"
			echo "$HIWIFI_HW_WAN_SPEED_ERROR" >$HIWIFI_HW_TEST_FILE
			exit 1
		fi
	fi
}

dump_lan_status() {
	local board_name="$(tw_board_name)"
	local payload=$(himsg -p system.hboardd -m status_lan -rv 2>/dev/null | sed -n '/payload:/ s/payload://p')
	local test_speed="$1"
	local i=0

	if [ -n "$payload" ]; then
		json_load "$payload"
		json_select link
		json_get_values lan_link
		i=0
		for k in $lan_link; do
			if [ "$k" != "up" ]; then
				echo "lan$i link failed"
				echo "$HIWIFI_HW_LAN_LINK_ERROR" >$HIWIFI_HW_TEST_FILE
				exit 1
			fi

			i=`expr $i + 1`
		done

		json_load "$payload"
		json_select speed
		json_get_values lan_speed
		i=0
		for k in $lan_speed; do
			if [ "$board_name" == "HC5861" ]; then
				# HC5861 have a giga phy(LAN)
				if [ $i -eq 1 ]; then
					if [ "$k" != "1000M" ]; then
						echo "lan$i test($test_speed $k) failed"
						echo "$HIWIFI_HW_LAN_SPEED_ERROR" >$HIWIFI_HW_TEST_FILE
						exit 1
					fi
				else
					if [ "$k" != "$test_speed" ]; then
						echo "lan$i test($test_speed $k) failed"
						echo "$HIWIFI_HW_LAN_SPEED_ERROR" >$HIWIFI_HW_TEST_FILE
						exit 1
					fi
				fi
			else
				if [ "$k" != "$test_speed" ]; then
					echo "lan$i test($test_speed $k) failed"
					echo "$HIWIFI_HW_LAN_SPEED_ERROR" >$HIWIFI_HW_TEST_FILE
					exit 1
				fi
			fi

			i=`expr $i + 1`
		done
	fi
}

switch_test() {
	local cpu_name="$(get_cpu_system_type)"
	local board_name="$(tw_board_name)"

	case "$cpu_name" in
		*"Mediatek MT7621"*)
			dump_wan_status "1000M"
			dump_lan_status "1000M"
			;;

		*"Mediatek MT7620"*)
			case "$board_name" in
			"R32" | "B50")
				dump_wan_status "1000M"
				dump_lan_status "100M"
				;;
			"R33")
				dump_wan_status "1000M"
				dump_lan_status "1000M"
				;;
			*)
				dump_wan_status "100M"
				dump_lan_status "100M"
				;;
			esac
			;;

		*"Mediatek MT7628"*)
			dump_wan_status "100M"
			dump_lan_status "100M"
			;;
	esac
}

