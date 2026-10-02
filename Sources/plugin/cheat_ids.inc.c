// ============================================================================================
// PARTE DO JOGO - voce edita este arquivo.
//
// Incluido por Sources/main.c na posicao original, entao a ordem das declaracoes continua
// valendo. Nao e compilado sozinho: o Makefile so compila Sources/*.c, e este arquivo esta em
// Sources/plugin/.
// ============================================================================================

// Um CH_* por cheat. Precisa vir cedo: NUM_CHEATS dimensiona os arrays de config.

// ===================== Cheat IDs =====================
// Game-specific. One enum entry per cheat, then a row in a Folder below (IT_CHEAT) and an
// implementation in ApplyCheats() (continuous) or OneShot() (applied once).
// CH_CFG_* are not cheats - they are Settings rows reusing the same row-drawing code.
enum {
    CH_STATUS, CH_CURRENCY, CH_COINS, CH_ITEMS, CH_EQUIPMENT,
    CH_LEVEL99, CH_STATS, CH_LEVEL255, CH_SECRET, CH_TIMER,
    CH_MAPS, CH_TICKETS, CH_TOKENS, CH_BADGE,
    CH_PLAYER_SLOT, CH_PLAYER_EXP, CH_PLAYER_MAX,
    CH_EX_HOTKEY,
    // ---- Settings rows (not cheats) ----
    CH_CFG_TOAST, CH_CFG_AUTOFILL, CH_CFG_QMKEY, CH_CFG_HK1, CH_CFG_HK2,
    CH_CFG_HKRESET, CH_CFG_THEME, CH_CFG_LANG,
    NUM_CHEATS
};
static u8 cheatState[NUM_CHEATS];
static u8 favorite[NUM_CHEATS];
