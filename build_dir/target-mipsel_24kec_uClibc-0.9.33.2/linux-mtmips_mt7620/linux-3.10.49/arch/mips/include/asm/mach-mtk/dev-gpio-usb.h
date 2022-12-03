/*
 *  Mediatek SoC GPIO usb power support
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#ifndef __ASM_MACH_RALINK_DEV_GPIO_USB_H
#define __ASM_MACH_RALINK_DEV_GPIO_USB_H

void ramips_set_usb_power_gpio(unsigned int gpio, unsigned long flags,
			       const char *label);

void hc_init_power(void);
void hc_add_power(unsigned int gpio, unsigned long flags, const char *label);

#endif /* __ASM_MACH_RALINK_DEV_GPIO_USB_H */
