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

TODO
----

* better defconfig for kernel
* I2C
* touch screen

