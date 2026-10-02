#ifndef THEMES_H
#define THEMES_H

// CTRComposer theme table.
//
// The engine's color macros (GOLD / INK / INK_DIM / GREEN_ON / BG in main.c) expand to
// RUNTIME arrays, not constants. ApplyTheme() copies one row of this table into those
// arrays, so switching a theme instantly recolors every menu without touching any of the
// hundreds of draw call sites. That indirection is the reusable part - the specific
// colors and how many you ship are entirely your choice.
//
// Roles:
//   gold  - titles, accents, the selection highlight
//   ink   - primary text
//   dim   - secondary / unselected text
//   green - "enabled" state (checkboxes, ON pills)
//   bg    - window background
//   parchment - 1 = draw a background IMAGE instead of a flat fill. The template ships no
//               background art, so leave this 0 unless you add your own and wire it up in
//               ComposeBackdrop().
//
// The template ships ONE neutral monochrome theme on purpose, so a new plugin isn't born
// wearing someone else's palette. Add as many rows as you like - or none, and delete the
// theme picker entirely. Auto-contrast (ThemeBgLight() in main.c) keeps text readable on
// light and dark backgrounds alike, so new themes need no per-theme tweaking.

typedef struct { const char *name; u8 gold[3], ink[3], dim[3], green[3], bg[3]; u8 parchment; } Theme;

static const Theme THEMES[] = {
    //  name         gold             ink              dim              green            bg          parchment
    { "Neutral", {230,230,230}, {242,242,242}, {150,150,150}, {200,200,200}, {18,18,20}, 0 },
    { "Raimon",  {255,196,40},  {250,250,245}, {176,186,194}, {74,220,105},  {18,42,75}, 0 },
    { "Zeus",    {255,214,72},  {255,250,224}, {202,181,130}, {126,235,165}, {55,31,76}, 0 },
    { "Aliea",   {90,235,255},  {235,255,255}, {130,190,204}, {80,255,160},  {8,35,43}, 0 },
    { "Ogre",    {255,72,72},   {255,240,235}, {200,145,140}, {255,180,65},  {48,12,18}, 0 },
    { "Chrono",  {130,220,255}, {240,250,255}, {145,175,205}, {245,100,255}, {20,28,58}, 0 },
    { "Galaxy",  {155,120,255}, {246,242,255}, {170,155,205}, {70,235,220},  {18,13,45}, 0 },
    { "Light",   {36,94,160},   {20,30,42},    {74,91,110},   {20,145,80},   {226,238,248}, 0 },
};
#define THEME_COUNT ((int)(sizeof(THEMES)/sizeof(THEMES[0])))

#endif
