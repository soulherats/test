/*
 *  Ralink SoC GPIO LED device support
 *
 *  Copyright (C) 2010-2011 Gabor Juhos <juhosg@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#ifndef __ASM_MACH_RALINK_DEV_GPIO_LEDS_H
#define __ASM_MACH_RALINK_DEV_GPIO_LEDS_H

#include <linux/leds.h>

void ramips_register_gpio_leds(int id, unsigned num_leds,
			       struct gpio_led *leds);

#endif /* __ASM_MACH_RALINK_DEV_GPIO_LEDS_H */
