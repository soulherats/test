#ifndef _MT7628_H_
#define _MT7628_H_

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/types.h>
#include <linux/bitops.h>
#include <asm/addrspace.h>

#define MT7628_SYSC_BASE		0x10000000
#define MT7628_SYSC_SIZE		0x100
#define SYSC_REG_CHIP_NAME0		0x00
#define SYSC_REG_CHIP_NAME1		0x04
#define SYSC_REG_CHIP_REV		0x0c
#define SYSC_REG_SYSTEM_CONFIG0		0x10
#define SYSC_REG_GPIO1_MDOE		0x60
#define SYSC_REG_GPIO2_MDOE		0x64

#define MT7628_CHIP_NAME0		0x3637544d
#define MT7628_CHIP_NAME1		0x20203832

#define CHIP_REV_PKG_MASK		0x1
#define CHIP_REV_PKG_SHIFT		16
#define CHIP_REV_VER_MASK		0xf
#define CHIP_REV_VER_SHIFT		8
#define CHIP_REV_ECO_MASK		0xf

#define MT7628_MEMC_BASE		0x10000300
#define MT7628_MEMC_SIZE		0x100

#define MT7628_DDR_CFG1			0x44
#define MT7628_DRAM_SIZE_SHIFT		18
#define MT7628_DRAM_SIZE_MASK		0x7
#define MT7628_DRAM_8M				0x1
#define MT7628_DRAM_16M				0x2
#define MT7628_DRAM_32M				0x3
#define MT7628_DRAM_64M				0x4
#define MT7628_DRAM_128M			0x5
#define MT7628_DRAM_256M			0x6

#define MT7628_GPIO_BASE		0x10000600

#define MT7628_SWITCH_LED_BASE	0x101100A4
#define MT7628_SWITCH_LEDP0		0x101100A4
#define MT7628_SWITCH_LEDP1		0x101100A8
#define MT7628_SWITCH_LEDP2		0x101100AC
#define MT7628_SWITCH_LEDP3		0x101100B0
#define MT7628_SWITCH_LEDP4		0x101100B4

#define MT7628_SWITCH_LED_MASK		0xf
#define MT7628_SWITCH_LED_NORMAL	0x5
#define MT7628_SWITCH_LED_OFF		0xb

#if 0
#define SYSCFG0_DRAM_TYPE_MASK		0x1
#define SYSCFG0_DRAM_TYPE_SHIFT		0
#define SYSCFG0_DRAM_TYPE_DDR1		1
#define SYSCFG0_DRAM_TYPE_DDR2		0

#define MT7628_DDR1_SIZE_MIN	(32 * 1024 * 1024)
#define MT7628_DDR1_SIZE_MAX	(128 * 1024 * 1024)
#define MT7628_DDR2_SIZE_MIN	(32 * 1024 * 1024)
#define MT7628_DDR2_SIZE_MAX	(256 * 1024 * 1024)
#endif

#define MT7628_DRAM_BASE	0x0

extern __iomem void *rt_sysc_membase;
extern __iomem void *rt_memc_membase;

static inline void rt_sysc_w32(u32 val, unsigned reg)
{
	__raw_writel(val, rt_sysc_membase + reg);
}

static inline u32 rt_sysc_r32(unsigned reg)
{
	return __raw_readl(rt_sysc_membase + reg);
}

static inline void rt_memc_w32(u32 val, unsigned reg)
{
	__raw_writel(val, rt_memc_membase + reg);
}

static inline u32 rt_memc_r32(unsigned reg)
{
	return __raw_readl(rt_memc_membase + reg);
}

static inline u32 rt_reg_r32(unsigned reg)
{
	return (*((volatile u32 *) (KSEG1ADDR(reg))));
}

static inline void rt_reg_w32(u32 val, unsigned reg)
{
	(*((volatile u32 *) (KSEG1ADDR(reg)))) = val;
}

void mt7628_gpio_set_mode(u32 mode1, u32 mode2);
void mt7628_gpio_init(u32 mode1, u32 mode2);

#endif	/* _MT7628_H_ */
