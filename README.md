Test Linux on STM32F469-Disco
=============================

It's amazing that Linux can run on STM32F469-Disco. I can use buildroot
to get a runing system. After that, I want to push it a little further
to see how far I can go.

Building
--------

I'm starting with the "sd" build. Buildroot provide another "xip" option,
but I think "sd" is much flexible. See [readme.txt](https://github.com/buildroot/buildroot/blob/master/board/stmicroelectronics/stm32f469-disco/readme.txt) for more details.

Status
------

The buildroot default is quite usable. Following peripherals are tested:

* Serial Port
* GPIOs and Leds
* LCD (need to enabled first)

Kernel
======

Tested with kernel 5.14.12 comming from buildroot.
Tested with kernel 6.7.0-rc4.

I2C
====

When I2C is enabled in the dts file, the i2cdetect command can find a client
at address 2a.  Which should be 0x54(doubled?) as the touchscreen chip FT6206.
Maybe there is bug in the driver.

USB
====

USB is working when dwc2 is compiled in.  I just verified with lsusb, should
check on some usb devices later.

TODO
----

* better defconfig for kernel
* touch screen (edt-ft5x06.c is promising, will check after i2c works).
