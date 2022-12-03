#!/bin/sh
# mediatek.sh
# controlling script of mediatek wireless driver for openwrt system
# (c)2013 Beijing Geek-Geek Technology Co., Ltd.

append DRIVERS "mediatek"

. /lib/platform.sh
. /usr/share/libubox/jshn.sh

set_wireless_cmd() {
	json_init
	[ -n "$2" ] && json_add_string device "$2"
	himsg -p wireless -m "$1" -b "$(json_dump)"
}

set_wireless_iface_cmd() {
	json_init
	[ -n "$2" ] && json_add_string ifname "$2"
	[ -n "$3" ] && json_add_string command "$3"
	[ -n "$4" ] && json_add_string argu "$4"
	himsg -p wireless -m "$1" -b "$(json_dump)"
}

start_mediatek_vif() {
	local vif="$1"
	local ifname="$2"

	local net_cfg
	net_cfg="$(find_net_config "$vif")"
	[ -z "$net_cfg" ] || start_net "$ifname" "$net_cfg"

	set_wifi_up "$vif" "$ifname"
}

find_mediatek_phy() {
	local device="$1"

	config_get vifs "$device" vifs
	for vif in $vifs; do
		config_get_bool disabled "$vif" disabled 0
		[ $disabled = 0 ] || continue
		return 0
	done

	return 1
}

sync_mediatek() {
	local devdst="$1"
	local devsrc="$2"

	config_get disabled "$devsrc" disabled
	config_get txpwr "$devsrc" txpwr
	config_get vifs "$devsrc" vifs

	uci set wireless.${devdst}.disabled="$disabled"
	#uci set wireless.${devdst}.txpwr="$txpwr"

	for vif in $vifs; do
		config_get ifname "$vif" ifname
		config_get ssid "$vif" ssid
		config_get hidden "$vif" hidden
		config_get macfilter "$vif" macfilter
		config_get encryption "$vif" encryption
		config_get key "$vif" key
		config_get rekey "$vif" rekey
		config_get ssidprefix "$vif" ssidprefix

		config_get_bool disabled "$vif" disabled 0
		config_get_bool isolate "$vif" isolate 0

		[ "$ifname" = "ra0" ] || break
		maclist=$(uci -q get wireless.master.maclist)
		uci -q delete wireless.masterac.maclist
		for mac in $maclist; do
			uci add_list wireless.masterac.maclist="$mac"
		done
		uci set wireless.masterac.ssid="$ssidprefix""$ssid""_5G"
		[ -n "$hidden" ] && uci set wireless.masterac.hidden="$hidden"
		[ -n "$macfilter" ] && uci set wireless.masterac.macfilter="$macfilter"
		[ -n "$encryption" ] && uci set wireless.masterac.encryption="$encryption"
		[ -n "$key" ] && uci set wireless.masterac.key="$key"
		[ -n "$rekey" ] && uci set wireless.masterac.rekey="$rekey"
		[ -n "$disabled" ] && uci set wireless.masterac.disabled="$disabled"
		[ -n "$isolate" ] && uci set wireless.masterac.isolate="$isolate"
	done
	uci commit wireless
}

scan_mediatek() {
	local device="$1"
	config_get vifs "$device" vifs

	[ "$2" = "disable" ] || return 

	[ "$device" = "radio0" ] && {
		for vif in $vifs; do
			config_get ifname "$vif" ifname
			[ "$ifname" = "ra0" ] || break
			config_get ssidprefix "$vif" ssidprefix
			config_get ssid "$vif" ssid
			uci set wireless.@wifi-iface[0].ssid="$ssidprefix""${ssid##$ssidprefix}"
		done
		return 0
	}
	return 0
}

start_mediatek() {
	local vif="$1"

	config_get_bool disabled "$vif" disabled 0
	[ $disabled -eq 0 ] || continue

	echo "$(date '+%F %X') start $1" >> /tmp/wifi.log

	set_wireless_iface_cmd start "$vif"
}

stop_mediatek() {
	local vif="$1"

	echo "$(date '+%F %X') stop $1" >> /tmp/wifi.log

	set_wireless_iface_cmd stop "$vif"
}

enable_mediatek() {
	local device="$1"
	config_get vifs "$device" vifs
	config_get_bool smt "$device" smt 0
	config_get channel "$device" channel
	config_get htbw "$device" htbw

	find_mediatek_phy "$device" || return 0

	echo "$(date '+%F %X') $device enable" >> /tmp/wifi.log

	set_wireless_cmd up $device

	for vif in $vifs; do
		config_get_bool disabled "$vif" disabled 0
		[ $disabled -eq 0 ] || continue

		config_get ifname "$vif" ifname
		config_get network "$vif" network

		[ "$network" = "wan" ] || {
			start_mediatek_vif "$vif" "$ifname"
		}
	done

	[ $smt -eq 0 ] || {
		himsg -e "wireless.smartconfig" -b '{"action":"radioup"}'
	}

	[ "$htbw" = "auto" ] && {
		local mifname=""
		for vif in $vifs; do
			mifname=${mifname:-$vif}
			break
		done
		[ "$channel" = "0" ] || himsg -p wireless -m set -b "{\"ifname\":\"$mifname\",\"command\":\"scan\",\"argu\":\"\"}"
		hwf-at 10 "himsg -p wireless -m set -b '{\"ifname\":\"$ifname\",\"command\":\"htbw\",\"argu\":\"auto\"}'"
	}

	return 0
}

disable_mediatek() {
	local device="$1"
	config_get vifs "$device" vifs
	
	set_wifi_down "$device"
	set_wireless_cmd down $device

	echo "$(date '+%F %X') $device disable" >> /tmp/wifi.log

	include /lib/network
	for vif in $vifs; do
		config_get ifname "$vif" ifname
		config_get network "$vif" network

		brctl show | grep -qs "$ifname"
		if [ $? -eq 0 ]; then
			unbridge1 $ifname $network 2>/dev/null
		fi
	done

	return 0
}

post_mediatek() {
	. /lib/functions/hiwifi.sh

	hiwifi_led_state
	
	# if led is disable; just disable 5G led
	if [ $? -eq 0 ]; then
		iwpriv rai0 set WlanLed=0 >/dev/null 2>&1
	fi
}

detect_mediatek_ra() {
	local device="$1"

	mac_suffix=$(tw_get_mac)
	mac_suffix=${mac_suffix:6:6}
	country=$(bdinfo get country)
	[ -z "$country" ] && {
		country="CN"
	}

	cat <<EOF
config wifi-device $device
	option type	mediatek
	option channel	0
	option txpwr	150
	option htbw	auto
	option country	${country}

config wifi-iface	master
	option device	$device
	option ifname	ra0
	option network	lan
	option mode	ap
	option ssid	HiWiFi_${mac_suffix}
	option encryption none
	option macfilter deny

config wifi-iface	slave
	option device	$device
	option ifname	apcli0
	option network	lan
	option mode	sta
	option ssid	HiWiFi_${mac_suffix}
	option encryption none
	option disabled 1

config wifi-iface	guest
	option device	$device
	option ifname	ra1
	option network	lan1
	option mode	ap
	option ssid	-HiWiFi-Guest-${mac_suffix:3}
	option encryption none
	option isolate 	1
	option disabled 1
	option macfilter deny

EOF
}

detect_mediatek_rai() {
	local device="$1"

	mac_suffix=$(tw_get_mac)
	mac_suffix=${mac_suffix:6:6}
	country=$(bdinfo get country)
	[ -z "$country" ] && {
		country="CN"
	}

	cat <<EOF
config wifi-device $device
	option type	mediatek
	option channel	0
	option txpwr	150
	option htbw auto
	option country	${country}

config wifi-iface	masterac
	option device	$device
	option ifname	rai0
	option network	lan
	option mode	ap
	option ssid	HiWiFi_${mac_suffix}_5G
	option encryption none
	option macfilter deny

config wifi-iface	slaveac
	option device	$device
	option ifname	apclii0
	option network	lan
	option mode	sta
	option ssid	HiWiFi_${mac_suffix}
	option encryption none
	option disabled 1

config wifi-iface	guestac
	option device	$device
	option ifname	rai1
	option network	lan1
	option mode	ap
	option ssid	-HiWiFi-Guest-${mac_suffix:3}
	option encryption none
	option isolate 	1
	option disabled 1
	option macfilter deny
EOF
}

detect_mediatek() {
	config_load wireless
	config_get type "radio0" type

	[ -n "$type" ] || detect_mediatek_ra "radio0"
	config_get type "radio1" type
	[ -n "$type" ] || {
		grep -qs "^ *rai0:" /proc/net/dev && detect_mediatek_rai "radio1"
	}
}
