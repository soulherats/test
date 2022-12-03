#ifndef __ASM_MACH_RALINK_COMMON_H
#define __ASM_MACH_RALINK_COMMON_H

#define RALINK_SYS_TYPE_LEN		64

extern unsigned char ralink_sys_type[RALINK_SYS_TYPE_LEN];

#ifndef CONFIG_RALINK_MT7621
extern unsigned long ramips_mem_size;
extern unsigned long ramips_mem_size_min;
extern unsigned long ramips_mem_size_max;
#endif
extern unsigned long ramips_mem_base;

void ramips_soc_prom_init(void);

#endif	/* __ASM_MACH_RALINK_COMMON_H */

