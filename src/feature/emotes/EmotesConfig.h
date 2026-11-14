#pragma once

// `config/emotes.json` (U19): the Emotes and PatTheDogs options, plus the players' emote
// tiers.

#include <map>
#include <string>
#include <vector>

#include "feature/emotes/Builtins.h"

namespace lp::feature::emotes {

struct EmotesConfig {
    int version = 1;

    // ---- Emotes ------------------------------------------------------------------------------
    bool enableEmotes = true;
    /// The enabled default emotes. Remove from this list to disable them. You can also re-order
    /// them, if you feel like it.
    std::vector<std::string> enabledEmotes = defaultEnabledEmotes();
    /// The list of Custom Emotes to be loaded (client: `config/lepton_emotes/<name>.emote`).
    std::vector<std::string> customEmotes;
    /// Re-read custom emote files every time they're triggered (edit on the fly).
    bool customEmoteDebug = false;
    /// Shift of the chat screen's emote buttons (client).
    int buttonShiftX = 0;
    int buttonShiftY = 0;
    /// The supporter emotes (dance, tpose, dab: tier 1; jet, exorcist, zombie: tier 2) go to
    /// the players listed here
    /// (lower-case name or XUID -> tier); everyone else has `defaultEmoteTier`.
    std::map<std::string, int> emoteTiers;
    int                        defaultEmoteTier = 0;

    // ---- PatTheDogs ---------------------------------------------------------------------------
    bool enablePatTheDogs = true;
    /// How many ticks it takes for a dog to want affection after being pet/tamed; -1 disables.
    int dogsWantLove = -1;
    /// Whether you can pet all mobs.
    bool petAllMobs = false;
    /// If `petAllMobs` is set, these mobs still can't be pet.
    std::vector<std::string> pettableDenylist{"minecraft:ender_dragon", "minecraft:wither", "minecraft:armor_stand"};
    /// Even if `petAllMobs` is not set, these mobs can be pet.
    std::vector<std::string> pettableAllowlist;
};

} // namespace lp::feature::emotes
