# Inazuma Eleven CTRPF

Multi-title cheat and memory-tools plugin for Nintendo 3DS. Version 0.3.4 uses the hook-free CTRComposer framebuffer engine, adds a first IE3 per-player editor, the remaining published IE3 unlock codes, a readable grid menu, eight selectable themes, and continuously presents the overlay while the unpaused game runs behind it.

## Supported title profiles

| Game | Title ID |
|---|---|
| IE3 Bomb Blast (EUR) | `00040000000F7B00` |
| IE3 Bomb Blast (EUR Multi-3) | `00040000000F7C00` |
| IE3 Lightning Bolt (EUR) | `00040000000F7D00` |
| IE3 Lightning Bolt (EUR Multi-3) | `00040000000F7E00` |
| IE3 Team Ogre Attacks! (EUR) | `00040000000F7F00` |
| IE3 Team Ogre Attacks! (EUR Multi-3) | `00040000000F8000` |
| GO Light (EUR) | `0004000000112F00` |
| GO Shadow (EUR) | `0004000000113000` |
| GO Chrono Stones Wildfire (EUR) | `0004000000136C00` |
| GO Chrono Stones Thunderflash (EUR) | `0004000000136D00` |
| GO Galaxy Big Bang (JPN/translation) | `000400000010BA00` |
| GO Galaxy Supernova (JPN/translation) | `000400000010BB00` |

Unknown title IDs get a read-only unsupported-title screen. No memory write entries are created.

## Included in 0.1.0

- Maximum money and friendship/passion where applicable
- All five Galaxy coin colours x999
- Quantities for owned items and techniques x99
- Quantities for owned equipment x99
- Published roster Level 99/experience edits
- Published roster maximum-stat edits
- Experimental Level 255 edits for Chrono Stones and Galaxy

These are one-shot, save-affecting editors. Back up the save before testing. Do not enable several entries at once, and verify the result after each entry.

## Install

The ready-to-copy ZIP contains the same `InazumaElevenCTRPF.3gx` under every supported title ID:

1. Extract the ZIP to the root of the SD card.
2. In Rosalina (`L` + D-Pad Down + `Select`), enable the plugin loader.
3. Start a supported game and press `Select` to open CTRPF.
4. Open **Game / compatibility status** first and confirm the detected title.

Only one `.3gx` should be present in each `luma/plugins/<title-id>/` directory.

## Testing protocol

1. Make a Checkpoint save backup.
2. Confirm the detected title name.
3. Test currency first and report the before/after values.
4. Test inventory on a save with at least one owned item and one owned equipment entry.
5. Test roster edits last, then play one match and save/reload.
6. If a result is wrong, restore the save and report the title ID shown by FBI plus the exact entry used.

Alternate IE3 Multi-3 IDs are provisionally mapped to their paired European layout and require hardware confirmation.

## Build

Requires devkitARM/devkitPro. In a shell with `DEVKITARM` set:

```sh
make clean
make
```

The output is `InazumaElevenCTRPF.3gx`. Version 0.2.0 is derived from the MIT-licensed CTRComposer engine; see `LICENSE-CTRComposer`.

## Roadmap

The long-term target is the complete discoverable cheat set. Work proceeds by verified game-family profiles: baseline/save editors, live match state, recruitment and team editing, unlocks/competition routes, movement and speed controls, player/technique editors, then new reverse-engineered features. Every entry should be classified as verified, provisional, or experimental.

## Sources and attribution

Initial address/code research comes from JourneyOver's CTRPF AR code database and Reshiban's 60 FPS database. CTRPluginFramework is by The Pixellizer Group and contributors. The modern build layout/tooling was adapted from `Gen6CTRPFrameworkOverhauled`.

This repository is intended for homebrew use with legally obtained games and saves. It does not contain game files.
