#pragma once

// The built-in emotes, as emote scripts (see EmoteScript.h). Pure C++.

#include <string>
#include <string_view>
#include <vector>

#include "feature/emotes/EmoteScript.h"

namespace lp::feature::emotes {

struct BuiltinEmote {
    std::string_view id;     ///< "wave"
    bool             patreon; ///< a supporter emote (tier 1 or 2)
    std::string_view script;
};

/// Every built-in emote: the 12 default ones, then the 6 supporter ones.
[[nodiscard]] std::vector<BuiltinEmote> const& builtinEmotes();
/// The built-in emote with that id, or nullptr.
[[nodiscard]] BuiltinEmote const* findBuiltin(std::string_view id);
/// The compiled built-in emote (compiled once), or nullptr.
[[nodiscard]] script::Emote const* compiledBuiltin(std::string_view id);
/// The default `enabledEmotes`.
[[nodiscard]] std::vector<std::string> defaultEnabledEmotes();

} // namespace lp::feature::emotes
