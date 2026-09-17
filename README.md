# Testing Linux on the STM32F469-Disco

It's amazing that Linux can run on the STM32F469-Disco. I used Buildroot
to get a running system. After that, I wanted to push it a little further
to see how far I could go.

## Building

I started with the `sd` build. Buildroot provides another `xip` option,
but I think `sd` is more flexible. See [readme.txt](https://github.com/buildroot/buildroot/blob/master/board/stmicroelectronics/stm32f469-disco/readme.txt) for more details.

## Status

The Buildroot default is quite usable. The following peripherals are tested:

* Serial Port
* GPIOs and LEDs
* I2C

### Kernel

* Tested with kernel 5.14.12 coming from Buildroot.
* Tested with kernel 6.7.0-rc4.
* Tested with kernel 6.10.0-rc3.

### Accepted Patches

* Commit [0fc78aa67b3f](https://github.com/torvalds/linux/commit/0fc78aa67b3f9a7cc6b67ddbc511e4a5022cfd01) ("ARM: stm32: dts: Missing clocks for stm32f429's syscfg.")
* Commit [3ccea4784fdd](https://github.com/torvalds/linux/commit/3ccea4784fddd96fbd6c4497eb28b45dab638c2a) ("ARM: Remove address checking for MMUless devices")

### I2C

When I2C is enabled in the device tree (DTS) file, use the following command
to get the chip ID from FT6206.
```shell
i2cget -y 0 0x2a 0xa8
```
However, i2cdetect (from BusyBox) will hang the I2C bus forever when it
probes addresses above 0x30.

I2C2 is not defined in stm32f429.dtsi; I don't know why. Maybe I should send
a patch. When I2C2 is enabled, i2cdetect can't find any chip on it. It should
have an audio codec available, maybe it needs to be powered on.

### USB

USB is working when `dwc2` is compiled in. I just verified with `lsusb`; I
should test it with some USB devices later.

### Touch Screen

The touch screen works with the `edt-ft5x06` driver. Test code is
[available](code/tst.c). It's a bit unstable, maybe related to I2C. I have a
[workaround](patches/0005-Input-edt-ft5x06-fetch-the-touch-frame-in-small-chun.patch),
but the real fix should be in the I2C driver.
```
[  202.012553] edt_ft5x06 0-002a: Unable to fetch data, error: -110
[  202.021075] edt_ft5x06 0-002a: Unable to fetch data, error: -16
```

### LCD

The LCD has been broken since kernel 6.11-rc1. The culprit is commit 185f99b6144
(drm/stm: dsi: expose DSI PHY internal clock). I have a working
[patch](patches/0002-drm-stm-dsi-use-clk_get_rate-to-set-pll_in_khz.patch), but
it is not ready to merge.

## TODO

* Test ADC/DAC
* Test the audio codec
