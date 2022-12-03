#!/bin/sh

. /lib/functions/system.sh

cpu_name="$(get_cpu_system_type)"
case "$cpu_name" in
*"Mediatek MT7621"*)
	# optimized for wifi and ethernet(WAN)
	echo 2 > /proc/irq/3/smp_affinity  #GMAC
	echo 8 > /proc/irq/4/smp_affinity  #PCIe0
	echo 4 > /proc/irq/24/smp_affinity #PCIe1
	echo 8 > /proc/irq/25/smp_affinity #PCIe2
	echo 8 > /proc/irq/19/smp_affinity #VPN
	echo 8 > /proc/irq/20/smp_affinity #SDXC
	echo 8 > /proc/irq/22/smp_affinity #USB

	[ -e /sys/class/net/ra0/queues/rx-0/rps_cpus ] && echo 3 > /sys/class/net/ra0/queues/rx-0/rps_cpus
	[ -e /sys/class/net/rai0/queues/rx-0/rps_cpus ] && echo 9 > /sys/class/net/rai0/queues/rx-0/rps_cpus
	[ -e /sys/class/net/eth2/queues/rx-0/rps_cpus ] && echo 5 > /sys/class/net/eth2/queues/rx-0/rps_cpus
	[ -e /sys/class/net/eth3/queues/rx-0/rps_cpus ] && echo d > /sys/class/net/eth3/queues/rx-0/rps_cpus

	# for samba
	smb_pid=$(pidof smbd)
	nmb_pid=$(pidof nmbd)
	ntfs_3g_pid=$(pidof ntfs-3g)
	[ -n "$smb_pid" ] && {
 		taskset -p 0x1 $smb_pid
 	}

 	[ -n "$nmb_pid" ] && {
		taskset -p 0x1 $nmb_pid
 	}

 	[ -n "$ntfs_3g_pid" ] && {
		taskset -p 0x8 $ntfs_3g_pid
 	}
	;;
esac
