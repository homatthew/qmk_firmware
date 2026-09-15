# Matthew's Ristretto firmware

This is the working guide for the `homatthew` Ristretto keymap. The GitHub
source of truth is the `mh-ristretto` branch of
<https://github.com/homatthew/qmk_firmware>.

## Where to edit

- `keymap.c` contains the four layers and the custom macros.
- `homatthew_keymap.json` is the QMK Configurator representation of the layout.
- `../../ristretto.c` contains the encoder behavior, WPM display, OLED text,
  and the Bongo Cat animation byte arrays.
- `../../rules.mk` enables the encoder, OLED, WPM counter, and other firmware
  features; `../../config.h` tunes WPM behavior and defines the hardware.

The OLED implementation is currently keyboard-level code, so changes in
`ristretto.c` affect every Ristretto keymap compiled from this branch.

## Normal edit, build, and flash workflow

Use **QMK MSYS** on Windows. Start in the repository:

```sh
cd /c/Users/Matthew/qmk_firmware
git switch mh-ristretto
git status
qmk compile -kb ristretto -km homatthew
```

A successful build places `ristretto_homatthew.hex` in the repository root.
To flash from the command line:

```sh
qmk flash -kb ristretto -km homatthew
```

When prompted, press the `SW1` button on the bottom of the PCB to enter the
Atmel DFU bootloader. Do not unplug the board while it is being erased or
written.

## Keep GitHub up to date

The remotes in this clone are:

- `homatthew`: Matthew's writable GitHub fork.
- `upstream`: the official QMK repository.

After making and testing a change:

```sh
git status
git diff --check
git diff
qmk compile -kb ristretto -km homatthew
git add keyboards/ristretto
git commit -m "Update Ristretto keymap"
git push homatthew mh-ristretto
```

Before starting work on another computer, clone the fork and select the branch:

```sh
git clone https://github.com/homatthew/qmk_firmware.git
cd qmk_firmware
git switch mh-ristretto
git submodule update --init --recursive
qmk setup
```

If the clone already exists, update it only with a clean working tree:

```sh
git switch mh-ristretto
git status
git pull --ff-only homatthew mh-ristretto
```

`--ff-only` is intentional: it stops instead of silently creating a merge.
If `git status` lists edits, commit them first or use `git stash push -u`, pull,
then `git stash pop` and resolve any conflicts.

### Bringing in official QMK updates

This branch contains an old full QMK tree, so a large upstream merge can break
APIs used by the OLED and encoder code. Make a backup branch and test the build
before updating GitHub:

```sh
git fetch upstream
git switch mh-ristretto
git switch -c test/qmk-upstream-update
git merge upstream/master
qmk compile -kb ristretto -km homatthew
```

If that succeeds and the keyboard tests correctly, merge the test branch into
`mh-ristretto` and push it. Do not force-push `mh-ristretto`; a normal push
preserves its recoverable history.

For the longer term, consider moving only the personal keymap into a modern
[QMK external userspace](https://docs.qmk.fm/external_userspace). That avoids
maintaining a complete fork, but the keyboard definition and its custom OLED
code must first work against current QMK.

## GUI choices

### QMK Configurator: easiest visual key layout editor

Open <https://config.qmk.fm>, choose `ristretto`, and upload
`homatthew_keymap.json`. You can drag keys onto the layout, download the updated
JSON, and compile it in the browser.

Important limitations:

- The public Configurator builds official QMK, not this fork's branch. Its
  downloaded firmware may therefore omit this branch's custom OLED animation
  and macros.
- Configurator JSON cannot represent arbitrary C code. Treat the JSON as the
  visual layout source, then compile it locally or translate its layer changes
  back into `keymap.c` when custom macros are required.
- Keep the downloaded JSON in Git so the visual layout remains reproducible.

### QMK Toolbox: easiest GUI flasher

Install [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases), open
`ristretto_homatthew.hex`, press `SW1`, confirm that an Atmel DFU device appears,
and click **Flash**. Toolbox flashes firmware; it does not edit the keymap.

### VIA or Vial: live remapping without reflashing

The current firmware is not VIA- or Vial-enabled. Adding either is a separate
firmware project: enable dynamic keymaps, add the correct layout definition and
EEPROM settings, compile a compatible firmware, flash it once, and then use the
desktop/web GUI for routine remapping. VIA is the more standard QMK-adjacent
choice; Vial offers more live features but uses its own QMK fork. Neither GUI
normally edits the compiled OLED animation code.

## Change the OLED text or graphic

Text is the easy path. In `../../ristretto.c`, edit the strings in
`oled_task_user()` such as `I WUB`, `YOU`, `JULIA`, and `8.31.23`. Keep each
string short enough for the display region, compile, and flash.

The Bongo Cat graphic is an animation made from monochrome raw byte arrays near
the top of `../../ristretto.c`:

- `idle[IDLE_FRAMES][ANIM_SIZE]`
- `prep[][ANIM_SIZE]`
- `tap[TAP_FRAMES][ANIM_SIZE]`

Practical artwork options:

1. **Keep Bongo Cat and edit individual frames.** Draw each frame as a 1-bit
   black-and-white bitmap, convert it to a C byte array in the OLED's vertical
   byte order, and replace the matching array.
2. **Use one static logo.** Replace the animation arrays with one bitmap and
   call `oled_write_raw_P()` once. This is simpler and saves flash space.
3. **Use only text/status.** Remove `render_anim()` and its arrays, then use
   `oled_write_P()` for WPM, layer, Caps Lock, or a message. This uses the least
   firmware space.
4. **Modernize the graphics code.** On a current QMK base, use QMK's image
   conversion/Painter tooling. This is cleaner for assets but should be done as
   part of the upstream-QMK migration because this branch predates those APIs.

For any replacement animation, every frame in a two-dimensional C array must
contain exactly `ANIM_SIZE` bytes. If the generated size changes, update
`ANIM_SIZE` and verify the display bounds. More/larger frames consume the
ATmega32U4's limited flash; always check the size line at the end of a build.

## Recovery checklist

- Wrong keys: confirm the `ristretto` keyboard and `homatthew` keymap were built.
- No bootloader device: press `SW1`, try another data-capable USB cable/port,
  then run `qmk doctor` in QMK MSYS.
- OLED garbled or clipped: restore the last known-good commit and recheck byte
  count, rotation, and cursor positions.
- Bad change: use `git log --oneline`, then create a new revert commit with
  `git revert <commit>`; avoid rewriting the shared branch history.
