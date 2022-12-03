#!/bin/sh
# setup mediatek switch

setup_switch() {
	local vlan
	config_load network
	config_get vlan "mtkswitch" vlan
	mtk_config_vlan $vlan
}

reset_switch_vlan() {
	local vlan
	local cpu_name
	cpu_name=$(awk 'BEGIN{FS="[ \t]+:[ \t]"} /system type/ {print $2}' /proc/cpuinfo)
	
	config_load network
	config_get vlan "mtkswitch" vlan

	case "$cpu_name" in
	*"Mediatek MT7621"*)
		local ifname
		config_get ifname "wan" "ifname"
		case "$ifname" in
		"eth2."*)
			if [ -n "$vlan" ]; then
				config_mt7621_esw "$vlan" "0"
			else
				config_mt7621_esw LLLLW "0"
			fi
			;;
		*)
			config_mt7620_esw_restore
			;;
		esac
		;;
	esac
}

mtk_config_vlan() {

	. /lib/mtmips.sh
	local cpu_name
	local board
	local vlan="$1"
	cpu_name=$(awk 'BEGIN{FS="[ \t]+:[ \t]"} /system type/ {print $2}' /proc/cpuinfo)
	
	board=$(tw_board_name)

	case "$cpu_name" in
	*"Mediatek MT7620"*)
		ifconfig eth2 up
		case "$board" in
		"HCMT7620-MT7530")
			config_mt7620_esw LLLLW
			;;
		*)
			if [ -n "$vlan" ]; then
				config_mt7620_esw "$vlan"
			else
				config_mt7620_esw WLLLL
			fi
			;;
		esac
		;;
	*"Mediatek MT7621"*)
		local ifname
		config_get ifname "wan" "ifname"
		config_get_bool disabled "wan" disabled 0
		[ $disabled = 0 ] && {
			ifconfig eth2 down
			ifconfig eth2 up
		}

		case "$ifname" in
		"eth2."*)
			if [ -n "$vlan" ]; then
				config_mt7621_esw "$vlan" "1"
			else
				config_mt7621_esw LLLLW "1"
			fi
			;;
		*)
			config_mt7620_esw_restore
			;;
		esac
		;;
	*"Mediatek MT7628"*)
		ifconfig eth2 up
		if [ -n "$vlan" ]; then
			config_mt7628_esw "$vlan"
		else
			config_mt7628_esw LLLLW
		fi
		;;
	esac
}

config_mt7620_igmp_restore()
{
	switch reg w 0x18 0x7f027dff
	switch reg w 0x2008 0x8000
	switch reg w 0x2108 0x8000
	switch reg w 0x2208 0x8000
	switch reg w 0x2308 0x8000
	switch reg w 0x2408 0x8000
	switch reg w 0x2508 0x8000
	switch reg w 0x2608 0x8000
}

config_mt7620_esw_restore()
{
	#port matrix mode
	switch reg w 2004 ff0000 #port0
	switch reg w 2104 ff0000 #port1
	switch reg w 2204 ff0000 #port2
	switch reg w 2304 ff0000 #port3
	switch reg w 2404 ff0000 #port4
	switch reg w 2504 ff0000 #port5
	switch reg w 2604 ff0000 #port6
	switch reg w 2704 ff0000 #port7

	# enable SA Learning
	switch reg w 200c 0xfff00
	switch reg w 210c 0xfff00
	switch reg w 220c 0xfff00
	switch reg w 230c 0xfff00
	switch reg w 240c 0xfff00
	switch reg w 250c 0xfff00

	#LAN/WAN ports as transparent mode
	switch reg w 2010 810000c0 #port0
	switch reg w 2110 810000c0 #port1
	switch reg w 2210 810000c0 #port2
	switch reg w 2310 810000c0 #port3   
	switch reg w 2410 810000c0 #port4
	switch reg w 2510 810000c0 #port5
	switch reg w 2610 810000c0 #port6
	switch reg w 2710 810000c0 #port7

	#clear mac table if vlan configuration changed
	# IGMP redirect to CPU port
	#switch reg w 0x18 0x6ff40
	#switch reg w 0x2008 0x9755
	#switch reg w 0x2108 0x9755
	#switch reg w 0x2208 0x9755
	#switch reg w 0x2308 0x9755

	#switch reg w 0x2608 0x9355

	config_mt7620_igmp_restore

	switch clear
}

config_mt7530_esw_restore()
{
	#port matrix mode
	switch_mt7530 reg w 2004 ff0000 #port0
	switch_mt7530 reg w 2104 ff0000 #port1
	switch_mt7530 reg w 2204 ff0000 #port2
	switch_mt7530 reg w 2304 ff0000 #port3
	switch_mt7530 reg w 2404 ff0000 #port4
	switch_mt7530 reg w 2504 ff0000 #port5
	switch_mt7530 reg w 2604 ff0000 #port6
	switch_mt7530 reg w 2704 ff0000 #port7

	# enable SA Learning
	switch_mt7530 reg w 200c ff00
	switch_mt7530 reg w 210c ff00
	switch_mt7530 reg w 220c ff00
	switch_mt7530 reg w 230c ff00
	switch_mt7530 reg w 240c ff00
	switch_mt7530 reg w 250c ff00

	#LAN/WAN ports as transparent mode
	switch_mt7530 reg w 2010 810000c0 #port0
	switch_mt7530 reg w 2110 810000c0 #port1
	switch_mt7530 reg w 2210 810000c0 #port2
	switch_mt7530 reg w 2310 810000c0 #port3   
	switch_mt7530 reg w 2410 810000c0 #port4
	switch_mt7530 reg w 2510 810000c0 #port5
	switch_mt7530 reg w 2610 810000c0 #port6
	switch_mt7530 reg w 2710 810000c0 #port7

	#clear mac table if vlan configuration changed
	switch_mt7530 clear
}

config_mt7530_lan_downup()
{
	local lanports=$(uci get hiwifi.switch.lanports)
	for port in $lanports
	do
		switch_mt7530 phy w $port 0 0x3300
	done
}

config_mt7620_esw()
{
	local switch_name=$(uci -q get hiwifi.switch.name)

	#LAN/WAN ports as security mode, egress mode = untagged
	switch reg w 2004 ff0003 #port0
	switch reg w 2104 ff0003 #port1
	switch reg w 2204 ff0003 #port2
	switch reg w 2304 ff0003 #port3
	switch reg w 2404 ff0003 #port4
	switch reg w 2504 ff0003 #port5
	#LAN/WAN ports as transparent port
	switch reg w 2010 810000c0 #port0
	switch reg w 2110 810000c0 #port1
	switch reg w 2210 810000c0 #port2
	switch reg w 2310 810000c0 #port3
	switch reg w 2410 810000c0 #port4
	switch reg w 2510 810000c0 #port5
	#set CPU/P7 port as user port
	switch reg w 2610 81000000 #port6
	switch reg w 2710 81000000 #port7

	switch reg w 2604 20ff0003 #port6, Egress VLAN Tag Attribution=tagged
	switch reg w 2704 20ff0003 #port7, Egress VLAN Tag Attribution=tagged
	switch reg w 2610 81000000 #port6

	case "$1" in
	"LLLLW")
		case "$switch_name" in
		"rtl8367")
			local hiwifi_mode=$(cat /proc/hiwifi/mode)
			[ $hiwifi_mode -ne 0 ] && {
				# reset as router mode
				echo 0 >/proc/hiwifi/mode
			}
			;;
		esac
		#set PVID
		switch reg w 2014 10001 #port0
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 10002 #port4
		switch reg w 2514 10001 #port5

		# disable WAN port SA Learning
		switch reg w 240c ff10

		#VLAN member port
		switch vlan set 0 1 11110111
		switch vlan set 1 2 00001011

		#set LAN ports as user port for guest vlan
		switch reg w 2010 81000000
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 11110111
		#per vlan engress tag control
		switch reg w 0x94 0x50ef0001 # pre vlan tag en(port member: WAN port)
		switch reg w 0x98 0xa8aa # per port engress tag control(WAN port is untaged, other is taged)
		switch reg w 0x90 0x80001002 #vlan index 2

		case "$switch_name" in
		"rtl8367")
			# IGMP init in driver
			switch phy w 1 0 0x1340
			switch phy w 2 0 0x1340
			switch phy w 3 0 0x1340
			switch phy w 4 0 0x1340
			;;
		"mt7530")
			config_mt7530_esw_restore
			config_mt7530_lan_downup
			;;
		*)
			# IGMP redirect to CPU port
			switch reg w 0x18 0x6ff40
			switch reg w 0x2008 0x9755
			switch reg w 0x2108 0x9755
			switch reg w 0x2208 0x9755
			switch reg w 0x2308 0x9755
		switch reg w 0x2408 0x8000
			switch reg w 0x2508 0x9755

			switch reg w 0x2608 0x9355

			switch phy w 0 0 0x3300
			switch phy w 1 0 0x3300
			switch phy w 2 0 0x3300
			switch phy w 3 0 0x3300
			switch phy w 5 0 0x3300
			;;
		esac

		echo "4" > /proc/hiwifi/wan_phy_num
		;;
	"WLLLL")
		#set PVID
		switch reg w 2014 10002 #port0
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 10001 #port4
		switch reg w 2514 10001 #port5

		# disable WAN port SA Learning
		switch reg w 200c ff10

		#VLAN member port
		switch vlan set 0 1 01111111
		switch vlan set 1 2 10000011

		#set LAN ports as user port for guest vlan
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2410 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 01111111
		#per vlan engress tag control
		switch reg w 0x94 0x50fe0001
		switch reg w 0x98 0xaaa8 #per port engress tag control
		switch reg w 0x90 0x80001002 #vlan index 2

		# IGMP redirect to CPU port
		switch reg w 0x18 0x6ff40
		switch reg w 0x2008 0x8000
		switch reg w 0x2108 0x9755
		switch reg w 0x2208 0x9755
		switch reg w 0x2308 0x9755
		switch reg w 0x2408 0x9755
		switch reg w 0x2508 0x9755

		switch reg w 0x2608 0x9355

		case "$switch_name" in
		"mt7530")
			config_mt7530_esw_restore
			config_mt7530_lan_downup
			;;
		*)
			switch phy w 1 0 0x3300
			switch phy w 2 0 0x3300
			switch phy w 3 0 0x3300
			switch phy w 4 0 0x3300
			switch phy w 5 0 0x3300
			;;
		esac

		echo "0" >/proc/hiwifi/wan_phy_num
		;;
	"LLLLL")
		# reset as ap mode first
		case "$switch_name" in
		"rtl8367")
			local hiwifi_mode=$(cat /proc/hiwifi/mode)
			[ $hiwifi_mode -ne 1 ] && {
				# reset as ap mode
				echo 1 >/proc/hiwifi/mode
			}
			;;
		esac
		#set PVID
		switch reg w 2014 10001 #port0
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 10001 #port4
		switch reg w 2514 10001 #port5
		#VLAN member port
		switch vlan set 0 1 11111111
		switch vlan set 1 2 00000011

		#set LAN ports as user port for guest vlan
		switch reg w 2010 81000000
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2410 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 11111111
		#per vlan engress tag control
		switch reg w 0x94 0x50ff0001
		switch reg w 0x98 0xaaaa #per port engress tag control
		switch reg w 0x90 0x80001002 #vlan index 2

		# enable SA Learning
		switch reg w 200c 0xfff00
		switch reg w 210c 0xfff00
		switch reg w 220c 0xfff00
		switch reg w 230c 0xfff00
		switch reg w 240c 0xfff00
		switch reg w 250c 0xfff00

		case "$switch_name" in
		"rtl8367")
			switch phy w 0 0 0x1340
			switch phy w 1 0 0x1340
			switch phy w 2 0 0x1340
			switch phy w 3 0 0x1340
			switch phy w 4 0 0x1340
			;;
		"mt7530")
			config_mt7530_esw_restore
			config_mt7530_lan_downup
			;;
		*)
			switch phy w 0 0 0x3300
			switch phy w 1 0 0x3300
			switch phy w 2 0 0x3300
			switch phy w 3 0 0x3300
			switch phy w 4 0 0x3300
			switch phy w 5 0 0x3300
			;;
		esac
		;;
	"GLLLL")
		#set PVID
		switch reg w 2014 10001 #port0
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 10001 #port4
		switch reg w 2514 10002 #port5

		# disable WAN port SA Learning
		switch reg w 250c 0xfff10

		#VLAN member port
		switch vlan set 0 1 11111011
		switch vlan set 1 2 00000111

		#set LAN ports as user port for guest vlan
		switch reg w 2010 81000000
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2410 81000000

		#vlan for guest
		switch vlan set 2 3 11111011
		#per vlan engress tag control
		switch reg w 0x94 0x50df0001	# pre vlan tag en(port member: WAN port)
		switch reg w 0x98 0xa2aa # per port engress tag control(WAN port is untaged, other is taged)
		switch reg w 0x90 0x80001002 #vlan index 2

		# IGMP redirect to CPU port
		#switch reg w 0x18 0x6ff40
		#switch reg w 0x2008 0x9755
		#switch reg w 0x2108 0x9755
		#switch reg w 0x2208 0x9755
		#switch reg w 0x2308 0x9755
		#switch reg w 0x2408 0x9755
		#switch reg w 0x2508 0x8000
		#switch reg w 0x2608 0x9355

		switch phy w 0 0 0x3300
		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 4 0 0x3300

		echo "5" >/proc/hiwifi/wan_phy_num
		;;
	"ELLLL")
		local phy_reg="0x3300"
		local phy_cmd="switch"

		case "$switch_name" in
		"rtl8367")
			phy_reg="0x1340"
			local hiwifi_mode=$(cat /proc/hiwifi/mode)
			[ $hiwifi_mode -ne 1 ] && {
				# reset as ap mode
				echo 1 >/proc/hiwifi/mode
			}
			;;
		"mt7530")
			phy_cmd="switch_mt7530"
			config_mt7530_esw_restore
			;;
		esac

		switch vlan set 0 1 11111111

		config_mt7620_esw_restore
		local lanports=$(uci get hiwifi.switch.lanports)
		for port in $lanports
		do
			$phy_cmd phy w $port 0 $phy_reg
		done
		;;
	"WLLLL-unicom")
		config_get unicomivid "mtkswitch" unicomivid
		config_get unicomtvid "mtkswitch" unicomtvid
		local unicom_ivid=$(printf %x $unicomivid)
		local unicom_tvid=$(printf %x $unicomtvid)
		local vid_len=${#unicomivid}

		if [ "$vid_len" -eq "1" ]; then
			vlan_prefix="1000"
		else
			vlan_prefix="100"
		fi

		local wan_pvid=$vlan_prefix$unicom_ivid

		#set PVID
		switch reg w 2014 $wan_pvid #port0 WAN unicom internet vid (PVID)
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 10001 #port4
		switch reg w 2514 10001 #port5

		switch reg w 2004 20ff0003 #port0 TAG mode (WAN)

		# disable WAN port SA Learning
		switch reg w 200c 0xfff10

		#VLAN member port
		switch vlan set 0 1 01111111
		switch vlan set 1 0x$unicom_ivid 10000011	# unicom internet vlan(WAN)

		#set WAN ports as user port for unicom
		switch reg w 2010 81000000

		#set LAN ports as user port for guest vlan
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2410 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 01111111
		#per vlan engress tag control
		switch reg w 0x94 0x50fe0001
		switch reg w 0x98 0xaaa8 #per port engress tag control
		switch reg w 0x90 0x80001002 #vlan index 2

		switch vlan set 3 0x$unicom_tvid 10000011	# unicom iptv vlan(WAN)

		# IGMP redirect to CPU port
		switch reg w 0x18 0x6ff40
		switch reg w 0x2008 0x8000
		switch reg w 0x2108 0x9755
		switch reg w 0x2208 0x9755
		switch reg w 0x2308 0x9755
		switch reg w 0x2408 0x9755
		switch reg w 0x2508 0x9755

		switch reg w 0x2608 0x9355

		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 4 0 0x3300
		switch phy w 5 0 0x3300

		echo "0" >/proc/hiwifi/wan_phy_num
		;;
	"WLLLL-unicom-b")
		config_get unicomivid "mtkswitch" unicomivid
		config_get unicomtvid "mtkswitch" unicomtvid
		local unicom_ivid=$(printf %x $unicomivid)
		local unicom_tvid=$(printf %x $unicomtvid)
		local ivid_len=${#unicomivid}
		local tvid_len=${#unicomtvid}

		if [ "$ivid_len" -eq "1" ]; then
			ivlan_prefix="1000"
		else
			ivlan_prefix="100"
		fi
		local wan_pvid=$ivlan_prefix$unicom_ivid

		if [ "$tvid_len" -eq "1" ]; then
			tvlan_prefix="1000"
		else
			tvlan_prefix="100"
		fi
		local wan_bvid=$tvlan_prefix$unicom_tvid

		#set PVID
		switch reg w 2014 $wan_pvid #port0 WAN unicom internet vid
		switch reg w 2114 $wan_bvid #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 10001 #port4
		switch reg w 2514 10001 #port5

		switch reg w 2004 20ff0003 #port0 TAG mode (WAN)

		# enable WAN port SA Learning
		switch reg w 200c 0xfff00

		#VLAN member port
		switch vlan set 0 1 01111111
		switch vlan set 1 0x$unicom_ivid 10000011

		#set WAN ports as user port for unicom
		switch reg w 2010 81000000

		#set LAN ports as user port for guest vlan
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2410 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 00111111
		#per vlan engress tag control
		switch reg w 0x94 0x50fc0001
		switch reg w 0x98 0xaaa0 #per port engress tag control
		switch reg w 0x90 0x80001002 #vlan index 2

		switch vlan set 3 0x$unicom_tvid 11000011	# unicom iptv 112 (WAN)

		# IGMP redirect to CPU port
		switch reg w 0x18 0x6ff40
		switch reg w 0x2008 0x8000
		switch reg w 0x2108 0x8000
		switch reg w 0x2208 0x9755
		switch reg w 0x2308 0x9755
		switch reg w 0x2408 0x9755
		switch reg w 0x2508 0x9755

		switch reg w 0x2608 0x9355

		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 4 0 0x3300
		switch phy w 5 0 0x3300

		echo "0" >/proc/hiwifi/wan_phy_num
		;;
	esac

	/etc/init.d/hnat restart
	switch clear
}

config_mt7621_esw()
{
	#LAN/WAN ports as security mode, egress mode = untagged
	switch reg w 2004 ff0003 #port0
	switch reg w 2104 ff0003 #port1
	switch reg w 2204 ff0003 #port2
	switch reg w 2304 ff0003 #port3
	switch reg w 2404 ff0003 #port4
	switch reg w 2504 ff0003 #port5
	#LAN/WAN ports as transparent port
	switch reg w 2010 810000c0 #port0
	switch reg w 2110 810000c0 #port1
	switch reg w 2210 810000c0 #port2
	switch reg w 2310 810000c0 #port3
	switch reg w 2410 810000c0 #port4
	switch reg w 2510 810000c0 #port5
	#set CPU/P7 port as user port
	switch reg w 2610 81000000 #port6
	switch reg w 2710 81000000 #port7

	switch reg w 2604 20ff0003 #port6, Egress VLAN Tag Attribution=tagged
	switch reg w 2704 20ff0003 #port7, Egress VLAN Tag Attribution=tagged
	switch reg w 2610 81000000 #port6

	case "$1" in
	"LLLLW")
		#set PVID
		switch reg w 2014 10001 #port0
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 10002 #port4
		switch reg w 2514 10001 #port5

		# disable WAN port SA Learning
		switch reg w 240c 0xfff10

		#VLAN member port
		switch vlan set 0 1 11110111
		switch vlan set 1 2 00001011

		#set LAN ports as user port for guest vlan
		switch reg w 2010 81000000
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 11110111
		#per vlan engress tag control
		switch reg w 0x94 0x50ef0001 # pre vlan tag en(port member: WAN port)
		switch reg w 0x98 0xa8aa # per port engress tag control(WAN port is untaged, other is taged)
		switch reg w 0x90 0x80001003 #VID 3

		# IGMP redirect to CPU port
		switch reg w 0x18 0x6ff40
		switch reg w 0x2008 0x9755
		switch reg w 0x2108 0x9755
		switch reg w 0x2208 0x9755
		switch reg w 0x2308 0x9755
		switch reg w 0x2408 0x8000
		switch reg w 0x2508 0x9755

		switch reg w 0x2608 0x9355

		if [ "$2" == "1" ]; then
		switch phy w 0 0 0x3300
		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 5 0 0x3300
		fi

		echo "4" > /proc/hiwifi/wan_phy_num
		;;
	"WLLLL")
		#set PVID
		switch reg w 2014 10002 #port0
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 10001 #port4
		switch reg w 2514 10001 #port5

		# disable WAN port SA Learning
		switch reg w 200c ff10

		#VLAN member port
		switch vlan set 0 1 01111111
		switch vlan set 1 2 10000011

		#set LAN ports as user port for guest vlan
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2410 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 01111111
		#per vlan engress tag control
		switch reg w 0x94 0x50fe0001
		switch reg w 0x98 0xaaa8 #per port engress tag control
		switch reg w 0x90 0x80001003 #VID 3

		# IGMP redirect to CPU port
		switch reg w 0x18 0x6ff40
		switch reg w 0x2008 0x8000
		switch reg w 0x2108 0x9755
		switch reg w 0x2208 0x9755
		switch reg w 0x2308 0x9755
		switch reg w 0x2408 0x9755
		switch reg w 0x2508 0x9755

		switch reg w 0x2608 0x9355

		if [ "$2" == "1" ]; then
		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 4 0 0x3300
		switch phy w 5 0 0x3300
		fi

		echo "0" >/proc/hiwifi/wan_phy_num
		;;
	"LLLLL")
		#set PVID
		switch reg w 2014 10001 #port0
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 10001 #port4
		switch reg w 2514 10001 #port5
		#VLAN member port
		switch vlan set 0 1 11111111
		switch vlan set 1 2 00000011

		#set LAN ports as user port for guest vlan
		switch reg w 2010 81000000
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2410 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 11111111
		#per vlan engress tag control
		switch reg w 0x94 0x50ff0001
		switch reg w 0x98 0xaaaa #per port engress tag control
		switch reg w 0x90 0x80001003 #VID 3

		# enable SA Learning
		switch reg w 200c 0xfff00
		switch reg w 210c 0xfff00
		switch reg w 220c 0xfff00
		switch reg w 230c 0xfff00
		switch reg w 240c 0xfff00
		switch reg w 250c 0xfff00

		if [ "$2" == "1" ]; then
		switch phy w 0 0 0x3300
		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 4 0 0x3300
		switch phy w 5 0 0x3300
		fi
		;;
	"LLLLW-unicom")
		config_get unicomivid "mtkswitch" unicomivid
		config_get unicomtvid "mtkswitch" unicomtvid
		local unicom_ivid=$(printf %x $unicomivid)
		local unicom_tvid=$(printf %x $unicomtvid)
		local vid_len=${#unicomivid}

		if [ "$vid_len" -eq "1" ]; then
			vlan_prefix="1000"
		else
			vlan_prefix="100"
		fi

		local wan_pvid=$vlan_prefix$unicom_ivid

		#set PVID
		switch reg w 2014 10001 #port0
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 10001 #port3
		switch reg w 2414 $wan_pvid #port4 VLAN 100 for internet(PVID)
		switch reg w 2514 10001 #port5

		switch reg w 2404 20ff0003 #port4 TAG mode

		# disable WAN port SA Learning
		switch reg w 240c 0xfff10

		#VLAN member port
		switch vlan set 0 1 11110111
		switch vlan set 1 0x$unicom_ivid 00001011		# unicom internet 100(VLAN)

		#set WAN ports as user port for unicom
		switch reg w 2410 81000000

		#set LAN ports as user port for guest vlan
		switch reg w 2010 81000000
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 11110111
		#per vlan engress tag control
		switch reg w 0x94 0x50ef0001 # pre vlan tag en(port member: WAN port)
		switch reg w 0x98 0xa8aa # per port engress tag control(WAN port is untaged, other is taged)
		switch reg w 0x90 0x80001003 #VID 3

		switch vlan set 3 0x$unicom_tvid 00001011	# unicom iptv 112

		# IGMP redirect to CPU port
		switch reg w 0x18 0x6ff40
		switch reg w 0x2008 0x9755
		switch reg w 0x2108 0x9755
		switch reg w 0x2208 0x9755
		switch reg w 0x2308 0x9755
		switch reg w 0x2408 0x8000	# disable wan port igmp snooping
		switch reg w 0x2508 0x9755

		switch reg w 0x2608 0x9355

		if [ "$2" == "1" ]; then
		switch phy w 0 0 0x3300
		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 5 0 0x3300
		fi

		echo "4" > /proc/hiwifi/wan_phy_num
		;;
	"LLLLW-unicom-b")
		config_get unicomivid "mtkswitch" unicomivid
		config_get unicomtvid "mtkswitch" unicomtvid
		local unicom_ivid=$(printf %x $unicomivid)
		local unicom_tvid=$(printf %x $unicomtvid)
		local ivid_len=${#unicomivid}
		local tvid_len=${#unicomtvid}

		if [ "$ivid_len" -eq "1" ]; then
			ivlan_prefix="1000"
		else
			ivlan_prefix="100"
		fi
		local wan_pvid=$ivlan_prefix$unicom_ivid

		if [ "$tvid_len" -eq "1" ]; then
			tvlan_prefix="1000"
		else
			tvlan_prefix="100"
		fi
		local wan_bvid=$tvlan_prefix$unicom_tvid

		#set PVID
		switch reg w 2014 10001 #port0
		switch reg w 2114 10001 #port1
		switch reg w 2214 10001 #port2
		switch reg w 2314 $wan_bvid #port3 for iptv VLAN bridge
		switch reg w 2414 $wan_pvid #port4 VLAN 100 for internet
		switch reg w 2514 10001 #port5

		switch reg w 2404 20ff0003 #port4 TAG mode

		# enable WAN port SA Learning
		switch reg w 240c 0xfff00

		#VLAN member port
		switch vlan set 0 1 11100111
		switch vlan set 1 0x$unicom_ivid 00001011		# unicom internet 100

		#set WAN ports as user port for unicom
		switch reg w 2410 81000000

		#set LAN ports as user port for guest vlan
		switch reg w 2010 81000000
		switch reg w 2110 81000000
		switch reg w 2210 81000000
		switch reg w 2310 81000000
		switch reg w 2510 81000000
		#vlan for guest
		switch vlan set 2 3 11100111
		#per vlan engress tag control
		switch reg w 0x94 0x50e70001 # pre vlan tag en(port member: WAN port)
		switch reg w 0x98 0xa82a # per port engress tag control(WAN/bridge port is untaged, other is taged)
		switch reg w 0x90 0x80001003 #VID 3

		switch vlan set 3 0x$unicom_tvid 00011000	# unicom iptv 112

		# IGMP redirect to CPU port
		switch reg w 0x18 0x6ff40
		switch reg w 0x2008 0x9755
		switch reg w 0x2108 0x9755
		switch reg w 0x2208 0x9755
		switch reg w 0x2308 0x8000 # disable bridge port igmp snooping
		switch reg w 0x2408 0x8000 # disable wan port igmp snooping
		switch reg w 0x2508 0x9755

		switch reg w 0x2608 0x9355

		if [ "$2" == "1" ]; then
		switch phy w 0 0 0x3300
		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 5 0 0x3300
		fi

		echo "4" > /proc/hiwifi/wan_phy_num
		;;
	esac

	if [ "$2" == "1" ]; then
	/etc/init.d/hnat restart
	fi

	switch clear
}

config_mt7628_esw_restore()
{
	switch reg w 14 5555
	switch reg w 40 1001
	switch reg w 44 1001
	switch reg w 48 1001
	switch reg w 4c 1
	switch reg w 50 2001
	switch reg w 70 ffffffff
	switch reg w 74 ffffffff
	switch reg w 98 7f7f
	switch reg w e4 7f

	# enable SA Learning
	switch reg w 94 0x0

	#clear mac table if vlan configuration changed
	switch clear
}

config_mt7628_esw()
{
	switch reg w 14 405555 >/dev/null 2>&1
	switch reg w 50 2001 >/dev/null 2>&1
	switch reg w 54 4003 >/dev/null 2>&1 #set vlanid 3 of guest wifi
	switch reg w 98 ff3f >/dev/null 2>&1 #enable per port per vlan untag
	#switch reg w e4 3f >/dev/null 2>&1 # double vlan

	case "$1" in
	"LLLLW")
		switch reg w 40 1001 >/dev/null 2>&1
		switch reg w 44 1001 >/dev/null 2>&1
		switch reg w 48 1002 >/dev/null 2>&1
		switch reg w 70 ff6f506f >/dev/null 2>&1 #set vlanid 3' membership equal to lan
		switch reg w 100 82f >/dev/null 2>&1 #set vlanid 1 & 2' per port vlan untag
		
		# disable WAN port SA Learning
		switch reg w 94 0x1000

		switch phy w 0 0 0x3300
		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		;;
	"WLLLL")
		switch reg w 40 1002 >/dev/null 2>&1
		switch reg w 44 1001 >/dev/null 2>&1
		switch reg w 48 1001 >/dev/null 2>&1
		switch reg w 70 ff7e417e >/dev/null 2>&1
		switch reg w 100 be >/dev/null 2>&1
		
		# disable WAN port SA Learning
		switch reg w 94 0x100

		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 4 0 0x3300
		;;
	"LLLWL")
		switch reg w 40 1001 >/dev/null 2>&1
		switch reg w 44 2001 >/dev/null 2>&1
		switch reg w 48 1001 >/dev/null 2>&1
		switch reg w 70 ff774877 >/dev/null 2>&1 #set vlanid 3' membership equal to lan
		switch reg w 100 437 >/dev/null 2>&1 #set vlanid 1 & 2' per port vlan untag

		# disable WAN port SA Learning
		switch reg w 94 0x800

		switch phy w 0 0 0x3300
		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 4 0 0x3300
		;;
	"LLLLL")
		switch reg w 40 1001 >/dev/null 2>&1
		switch reg w 44 1001 >/dev/null 2>&1
		switch reg w 48 1001 >/dev/null 2>&1
		switch reg w 70 ff7f407f >/dev/null 2>&1 #add port 4 to vlanid 1 & 3
		switch reg w 100 3f >/dev/null 2>&1

		# enable SA Learning
		switch reg w 94 0x0

		switch phy w 0 0 0x3300
		switch phy w 1 0 0x3300
		switch phy w 2 0 0x3300
		switch phy w 3 0 0x3300
		switch phy w 4 0 0x3300
		;;
	"ELLLL")
		config_mt7628_esw_restore

		local lanports=$(uci get hiwifi.switch.lanports)
		for port in $lanports
		do
			switch phy w $port 0 0x3300
		done
		;;
	esac

	switch clear
}
