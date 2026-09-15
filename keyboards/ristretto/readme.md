# Ristretto

![Ristretto](https://i.imgur.com/VHX6ktEh.jpg)
![Ristretto-2](https://i.imgur.com/Hrc8vkph.jpg)

An Integrated, Column Stagger, 40% Keyboard with OLED and Rotary Encoder

* Keyboard Maintainer: [Fruit](https://github.com/Blewis308)
* Hardware Supported: Ristretto PCB, Atmega32u4
* Hardware Availability: Through Group Buy - May 2021

    To enter the bootloader, press the button marked "SW1" on the bottom of the PCB.

Build the default firmware after setting up your build environment:

    qmk compile -kb ristretto -km default

Matthew's keymap, macros, and OLED customization are under
`keyboards/ristretto/keymaps/homatthew`. See that folder's README for the
complete edit, build, flash, GitHub sync, GUI, and OLED artwork workflow.

    qmk compile -kb ristretto -km homatthew

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
