# Test Linux on STM32F469-Disco

It's amazing that Linux can run on STM32F469-Disco. I can use buildroot
to get a runing system. After that, I want to push it a little further
to see how far I can go.

## Building

I'm starting with the "sd" build. Buildroot provide another "xip" option,
but I think "sd" is much flexible. See [readme.txt](https://github.com/buildroot/buildroot/blob/master/board/stmicroelectronics/stm32f469-disco/readme.txt) for more details.

## Status

The buildroot default is quite usable. Following peripherals are tested:

* Serial Port
* GPIOs and Leds
* I2C

### Kernel

* Tested with kernel 5.14.12 comming from buildroot.
* Tested with kernel 6.7.0-rc4.
* Tested with kernel 6.10.0-rc3.

### Accepted patches
* commit [0fc78aa67b3f](https://github.com/torvalds/linux/commit/0fc78aa67b3f9a7cc6b67ddbc511e4a5022cfd01) ("ARM: stm32: dts: Missing clocks for stm32f429's syscfg.")
* commit [3b65cc989242](https://github.com/torvalds/linux/commit/3ccea4784fddd96fbd6c4497eb28b45dab638c2a) ("ARM: Remove address checking for MMUless devices")

### I2C

When I2C is enabled in the dts file, use following command to get chip ID from
FT6206.
```
i2cget -y 0 0x2a 0xa8
```
Howerver, i2cdetect(from busybox) will make i2c bus busy forever when probe range
after address 0x30.

I2C2 is not defined in stm32f429.dtsi. Don't know why. Maybe I should send a patch.
When I2C2 is enabled, i2cdetect can't find any chip on it. It should have a audio
codec available, maybe need to power on.

### USB

USB is working when dwc2 is compiled in.  I just verified with lsusb, should
check on some usb devices later.

### Touch Screen

Touch screen with edt-ft5x06 driver works. Test code is [available](code/tst.c).
It's a bit unstable, maybe related with I2C.
```
[  202.012553] edt_ft5x06 0-002a: Unable to fetch data, error: -110
[  202.021075] edt_ft5x06 0-002a: Unable to fetch data, error: -16
```

### LCD

The LCD is broken since kernel 6.11-rc1. The culprit is commit 185f99b6144 (drm/stm:
dsi: expose DSI PHY internal clock). Still trying to figure out why.

## TODO

* Testing ADC/DAC
* Testing audio codec
