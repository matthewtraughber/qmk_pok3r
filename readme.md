# Quantum Mechanical Keyboard Firmware for POK3R
#### NOTE: _This repository is a (manual) fork of [pok3r-custom\/qmk_pok3r](https://github.com/pok3r-custom/qmk_pok3), containing my specific Vortex POK3R config. See [Ewpratten\/qmk_core](https://github.com/Ewpratten/qmk_core) for a Vortex Core focused fork._

This repository contains keyboard firmware based on the [qmk\_firmware](http://github.com/qmk/qmk_firmware) project for a number of Holtek MCU-based keyboards. See below for supported and planned keyboards.

## Building

    make vortex/pok3r:default vortex/pok3r_rgb:default vortex/core:default

## Installation

__WARNING: This firmware only works on [unlocked](https://github.com/pok3r-custom/pok3r_re_firmware/wiki/HT32-Unlocking) keyboards.__

_On locked keyboards, the firmware will hard fault at boot, requiring a JTAG programmer to reprogram._

    ./pok3rtool -t pok3r flash "QMK_POK3R" <path_to_qmk_pok3r>/vortex_pok3r_default.bin

## Supported Keyboards

* [Vortex POK3R](/keyboards/vortex/pok3r/)
* [Vortex POK3R RGB](/keyboards/vortex/pok3r_rgb/) (not stable)
* [Vortex Core](/keyboards/vortex/core/) (not stable)
* Vortex RACE3 (planned)
* Vortex ViBE (planned)
* KBP V60 (planned)
* KBP V80 (planned)

## Related

* [pok3rtool](https://github.com/pok3r-custom/pok3rtool) - CLI dev tool for pok3r keyboards
* [Pok3rConf](https://github.com/pok3r-custom/Pok3rConf) - GUI configuration tool for pok3r keyboards
