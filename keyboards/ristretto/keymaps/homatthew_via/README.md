# Ristretto Bongo Cat + VIA

This keymap targets current QMK and combines Matthew's Bongo Cat OLED animation
with a four-layer VIA dynamic keymap and layer-specific encoder mappings.

## Build

```sh
qmk compile -kb ristretto -km homatthew_via
```

The expected artifact is `ristretto_homatthew_via.hex`. Flash it with QMK
Toolbox after pressing `SW1` on the bottom of the PCB, or run:

```sh
qmk flash -kb ristretto -km homatthew_via
```

## Connect with VIA

1. Open <https://usevia.app> in a Chromium-based browser.
2. Open **Settings** and enable the **Design** tab.
3. In **Design**, load `ristretto_v3.json` from this directory.
4. Authorize the Ristretto when the browser requests HID access.
5. Use **Configure** to edit keys, four layers, macros, and the encoder.

If a newly compiled default layout does not appear, clear EEPROM once. VIA
stores later layout changes in EEPROM, so reflashing alone intentionally does
not overwrite them.

## OLED implementation

`bongo_cat.h` contains eight exact 128x32 monochrome framebuffers: five idle,
one preparation, and two typing frames. The previous arrays declared 636 bytes
per frame even though the display and QMK framebuffer contain only 512. The
extra 124 bytes per frame were implicit zeros and were truncated by QMK. This
version removes those 992 unreachable bytes without changing any displayed
pixel.

`keymap.c` renders a frame at most every 150 ms and overlays WPM, the active
layer, and the existing personal message. QMK's OLED dirty-block tracking avoids
transmitting unchanged blocks. The display sleeps after 60 seconds of keyboard
inactivity to reduce burn-in.

## Layers and encoder defaults

- 0 — Base typing; encoder controls volume.
- 1 — Numbers and symbols; encoder changes media track.
- 2 — Function and navigation; encoder sends Page Down/Page Up.
- 3 — System/media and VIA macro slots; encoder controls brightness.

All of these assignments can be changed in VIA without recompiling. Artwork,
animation thresholds, and custom OLED rendering remain compiled firmware
features and therefore survive VIA remapping.

## GitHub builds

Every push that changes the Ristretto files on the `mh-ristretto-via` branch
starts the **Build Ristretto Bongo Cat firmware** GitHub Actions workflow. Open
the completed workflow run, download the `ristretto-homatthew-via` artifact,
and flash the contained `.hex` with QMK Toolbox. This keeps normal builds
reproducible even when the local QMK MSYS installation needs maintenance.
