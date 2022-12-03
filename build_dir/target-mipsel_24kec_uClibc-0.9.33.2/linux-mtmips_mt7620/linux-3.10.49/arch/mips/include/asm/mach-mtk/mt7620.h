#ifndef _MT7620_H_
#define _MT7620_H_

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/types.h>
#include <linux/bitops.h>
#include <asm/addrspace.h>

#define MT7620_SYSC_BASE		0x10000000
#define MT7620_TIMER_BASE		0x10000100
#define MT7620_INTC_BASE		0x10000200
#define MT7620_MEMC_BASE		0x10000300
#define MT7620_RBUSC_BASE		0x10000400
#define MT7620_UART0_BASE		0x10000500
#define MT7620_PIO_BASE			0x10000600
#define MT7620_NANDC_BASE		0x10000810
#define MT7260_I2C_BASE			0x10000900
#define MT7620_I2S_BASE			0x10000A00
#define MT7620_SPI_BASE			0x10000B00
#define MT7620_UART1_BASE		0x10000C00
#define MT7620_MIPS_CNT_BASE	0x10000D00
#define MT7620_PCM_BASE			0x10002000
#define MT7620_GDMA_BASE		0x10002800
#define MT7620_CE_BASE			0x10004000
#define MT7620_FE_BASE			0x10100000
#define MT7620_PPE_BASE			0x10100C00
#define MT7620_ETH_SW_BASE		0x10110000
#define MT7620_USB_DEV_BASE		0x10120000
#define MT7620_PCI_BASE			0x10140000
#define MT7620_WLAN_BASE		0x10180000
#define MT7620_USBHOST_BASE		0x101C0000
#define MT7620_BOOT_BASE		0x1C000000

#define MT7620_EHCI_BASE	(MT7620_USBHOST_BASE)
#define MT7620_OHCI_BASE	(MT7620_USBHOST_BASE + 0x1000)

#define MT7620_SYSC_SIZE	0x100
#define MT7620_TIMER_SIZE	0x100
#define MT7620_INTC_SIZE	0x100
#define MT7620_MEMC_SIZE	0x100
#define MT7620_UART0_SIZE	0x100
#define MT7620_UART1_SIZE	0x100
#define MT7620_PIO_SIZE		0x100
#define MT7620_FSCC_SIZE	0x100
#define MT7620_NANDC_SIZE	0x0f0
#define MT7620_I2C_SIZE		0x100
#define MT7620_I2S_SIZE		0x100
#define MT7620_SPI_SIZE		0x100
#define MT7620_PCM_SIZE		0x800
#define MT7620_GDMA_SIZE	0x800
#define MT7620_CODEC1_SIZE	0x800
#define MT7620_CODEC2_SIZE	0x800
#define MT7620_FE_SIZE		0x10000
#define MT7620_ROM_SIZE		0x4000
#define MT7620_USBDEV_SIZE	0x4000
#define MT7620_PCI_SIZE		0x40000
#define MT7620_WLAN_SIZE	0x40000
#define MT7620_USBHOST_SIZE	0x40000
#define MT7620_BOOT_SIZE	(32 * 1024 * 1024)

#define SYSC_REG_CHIP_NAME0		0x00
#define SYSC_REG_CHIP_NAME1		0x04
#define SYSC_REG_CHIP_REV		0x0c
#define SYSC_REG_SYSTEM_CONFIG0		0x10
#define MT7620N_CHIP_NAME0		0x33365452
#define MT7620N_CHIP_NAME1		0x20203235

#define MT7620A_CHIP_NAME0		0x3637544d
#define MT7620A_CHIP_NAME1		0x20203032

#define CHIP_REV_PKG_MASK		0x1
#define CHIP_REV_PKG_SHIFT		16
#define CHIP_REV_VER_MASK		0xf
#define CHIP_REV_VER_SHIFT		8
#define CHIP_REV_ECO_MASK		0xf

#define MT7620_SDRAM_SIZE_MIN	(2 * 1024 * 1024)
#define MT7620_SDRAM_SIZE_MAX	(64 * 1024 * 1024) 
#define MT7620_DDR1_SIZE_MIN	(32 * 1024 * 1024)
#define MT7620_DDR1_SIZE_MAX	(128 * 1024 * 1024)
#define MT7620_DDR2_SIZE_MIN	(32 * 1024 * 1024)
#define MT7620_DDR2_SIZE_MAX	(256 * 1024 * 1024)

#define SYSCFG0_DRAM_TYPE_MASK		0x3
#define SYSCFG0_DRAM_TYPE_SHIFT		4
#define SYSCFG0_DRAM_TYPE_SDRAM		0
#define SYSCFG0_DRAM_TYPE_DDR1		1
#define SYSCFG0_DRAM_TYPE_DDR2		2

#define MT7620_DRAM_BASE		0x0

#define MT7620_SYSC_REG_GPIO_MODE	0x60	/* GPIO Purpose Select */

#define MT7620_GPIO_MODE_I2C			BIT(0)
#define MT7620_GPIO_MODE_UART0_SHIFT	2
#define MT7620_GPIO_MODE_UART0_MASK	0x7
#define MT7620_GPIO_MODE_UART0(x)	((x) << MT7620_GPIO_MODE_UART0_SHIFT)
#define MT7620_GPIO_MODE_UARTF		0x0
#define MT7620_GPIO_MODE_PCM_UARTF	0x1
#define MT7620_GPIO_MODE_PCM_I2S	0x2
#define MT7620_GPIO_MODE_I2S_UARTF	0x3
#define MT7620_GPIO_MODE_PCM_GPIO	0x4
#define MT7620_GPIO_MODE_GPIO_UARTF	0x5
#define MT7620_GPIO_MODE_GPIO_I2S	0x6
#define MT7620_GPIO_MODE_GPIO		0x7
#define MT7620_GPIO_MODE_UART1		BIT(5)
#define MT7620_GPIO_MODE_MDIO		BIT(8)
#define MT7620_GPIO_MODE_GE1		BIT(9)
#define MT7620_GPIO_MODE_GE2		BIT(10)
#define MT7620_GPIO_MODE_SPI		BIT(11)
#define MT7620_GPIO_MODE_SPI_REF_CLK	BIT(12)
#define MT7620_GPIO_MODE_WLED		BIT(13)
#define MT7620_GPIO_MODE_JTAG		BIT(15)
#define MT7620_GPIO_MODE_EPHY		BIT(15)
#define MT7620_GPIO_MODE_PA			BIT(20)
#define MT7620_GPIO_MODE_WDT		BIT(22)

#define MT7620_GPIO_I2C_SD	1
#define MT7620_GPIO_I2C_SCLK	2
#define MT7620_GPIO_SPI_CS0	3
#define MT7620_GPIO_SPI_CLK	4
#define MT7620_GPIO_SPI_MOSI	5
#define MT7620_GPIO_SPI_MISO	6
/* GPIO 7-14 is shared between UART0, PCM  and I2S interfaces */
#define MT7620_GPIO_7		7
#define MT7620_GPIO_8		8
#define MT7620_GPIO_9		9
#define MT7620_GPIO_10		10
#define MT7620_GPIO_11		11
#define MT7620_GPIO_12		12
#define MT7620_GPIO_13		13
#define MT7620_GPIO_14		14
/* uartlite */
#define MT7620_GPIO_UART1_TXD	15
#define MT7620_GPIO_UART1_RXD	16
#define MT7620_GPIO_WDT_RST		17
/* LNA */
#define MT7620_GPIO_LNA_PE_A0	18
#define MT7620_GPIO_LNA_PE_A1	19
#define MT7620_GPIO_LNA_PE_G0	20
#define MT7620_GPIO_LNA_PE_G1	21
/* MDIO */
#define MT7620_GPIO_MDIO_MDC	22
#define MT7620_GPIO_MDIO_MDIO	23
/* rgmii1 */
#define MT7620_GPIO_GE1_TXD0	24
#define MT7620_GPIO_GE1_TXD1	25
#define MT7620_GPIO_GE1_TXD2	26
#define MT7620_GPIO_GE1_TXD3	27
#define MT7620_GPIO_GE1_TXEN	28
#define MT7620_GPIO_GE1_TXCLK	29
#define MT7620_GPIO_GE1_RXD0	30
#define MT7620_GPIO_GE1_RXD1	31
#define MT7620_GPIO_GE1_RXD2	32
#define MT7620_GPIO_GE1_RXD3	33
#define MT7620_GPIO_GE1_RXDV	34
#define MT7620_GPIO_GE1_RXCLK	35
/* PCIe reset */
#define MT7620_GPIO_PCIE_RST	36
/* SPI */
#define MT7620_GPIO_SPI_S1		37
#define MT7620_GPIO_SPI_HOLD	38
#define MT7620_GPIO_SPI_WP		39
/* JTAG adn EPHY */	
#define MT7620_GPIO_JTAG_TDO	40
#define MT7620_GPIO_JTAG_TDI	41
#define MT7620_GPIO_JTAG_TMS	42
#define MT7620_GPIO_JTAG_TCLK	43
#define MT7620_GPIO_JTAG_TRST_N	44
/* NAND */
#define MT7620_GPIO_NAND_CS_N	45
#define MT7620_GPIO_NAND_WE_N	46
#define MT7620_GPIO_NAND_RE_N	47
#define MT7620_GPIO_NAND_WP		48
#define MT7620_GPIO_NAND_RB_N	49
#define MT7620_GPIO_NAND_CLE	50
#define MT7620_GPIO_NAND_ALE	51
#define MT7620_GPIO_NAND_D0		52
#define MT7620_GPIO_NAND_D1		53
#define MT7620_GPIO_NAND_D2		54
#define MT7620_GPIO_NAND_D3		55
#define MT7620_GPIO_NAND_D4		56
#define MT7620_GPIO_NAND_D5		57
#define MT7620_GPIO_NAND_D6		58
#define MT7620_GPIO_NAND_D7		59
/* RGMII2 */
#define MT7620_GPIO_GE2_TXD0	60
#define MT7620_GPIO_GE2_TXD1	61
#define MT7620_GPIO_GE2_TXD2	62
#define MT7620_GPIO_GE2_TXD3	63
#define MT7620_GPIO_GE2_TXEN	64
#define MT7620_GPIO_GE2_TXCLK	65
#define MT7620_GPIO_GE2_RXD0	66
#define MT7620_GPIO_GE2_RXD1	67
#define MT7620_GPIO_GE2_RXD2	68
#define MT7620_GPIO_GE2_RXD3	69
#define MT7620_GPIO_GE2_RXDV	70
#define MT7620_GPIO_GE2_RXCLK	71
/* wlan led */
#define MT7620_GPIO_WLED		72

#define MT7620_GPIO_PIO_0_DATA_REG	(MT7620_PIO_BASE+0x20)
#define MT7620_GPIO_PIO_0_DIR_REG	(MT7620_PIO_BASE+0x24)
#define MT7620_GPIO_PIO_0_SET_REG	(MT7620_PIO_BASE+0x2c)
#define MT7620_GPIO_PIO_0_RESET_REG	(MT7620_PIO_BASE+0x30)
#define MT7620_GPIO_PIO_1_DATA_REG	(MT7620_PIO_BASE+0x48)
#define MT7620_GPIO_PIO_1_DIR_REG	(MT7620_PIO_BASE+0x4c)
#define MT7620_GPIO_PIO_1_SET_REG	(MT7620_PIO_BASE+0x54)
#define MT7620_GPIO_PIO_1_RESET_REG	(MT7620_PIO_BASE+0x58)
#define MT7620_GPIO_PIO_2_DATA_REG	(MT7620_PIO_BASE+0x70)
#define MT7620_GPIO_PIO_2_DIR_REG	(MT7620_PIO_BASE+0x74)
#define MT7620_GPIO_PIO_2_SET_REG	(MT7620_PIO_BASE+0x7c)
#define MT7620_GPIO_PIO_2_RESET_REG	(MT7620_PIO_BASE+0x80)

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

void mt7620_gpio_init(u32 mode);

#endif	/* _MT7620_H_ */
