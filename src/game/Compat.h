#pragma once

// The few game calls that differ between the LeviLamina lines Lepton builds for. The build defines
// LP_LL_VERSION as the line (2651 for 26.51.x, 2660 for 26.60.x); everything else calls these
// helpers instead of guarding the call itself.
//
//     lp::game::destroyBlock(level, region, pos, true, ctx);   // the destroy sound plays, as before
//     lp::game::updateNeighborsAt(region, pos);
//     float hardness = lp::game::hardness(block);

#include <functional>
#include <string>

#include "mc/world/gamemode/InteractionResult.h"

#if LP_LL_VERSION >= 2660
#include "mc/world/item/HandSlot.h"
#include "mc/world/level/BlockDestroySound.h"
#endif

class Actor;
class Block;
class BlockChangeContext;
class BlockPos;
class BlockSource;
class BlockType;
class ItemDescriptor;
class ItemStack;
class ItemStackBase;
class Mob;
class Player;
class Vec3;
struct ItemTag;
#ifdef LP_CLIENT
class Font;
class FontHandle;
#endif

// Player::interact: 26.60 added the hand that interacts. Hooks of it take LP_INTERACT_PARAMS, pass
// LP_INTERACT_ARGS to origin(), and act on the main hand only (LP_INTERACT_MAINHAND), as 26.51
// did: 26.60 offers the interaction to the off hand when the main hand did nothing.
#if LP_LL_VERSION >= 2660
#define LP_INTERACT_PARAMS   ::Actor& actor, ::Vec3 const& location, ::HandSlot handSlot
#define LP_INTERACT_ARGS     actor, location, handSlot
#define LP_INTERACT_MAINHAND (handSlot == ::HandSlot::Mainhand)
#else
#define LP_INTERACT_PARAMS   ::Actor& actor, ::Vec3 const& location
#define LP_INTERACT_ARGS     actor, location
#define LP_INTERACT_MAINHAND true
#endif

namespace lp::game {

/// Level::destroyBlock with the destroy sound (26.60 made the sound a parameter).
template <class TLevel>
bool destroyBlock(TLevel& level, BlockSource& region, BlockPos const& pos, bool drop, BlockChangeContext const& ctx) {
#if LP_LL_VERSION >= 2660
    return level.destroyBlock(region, pos, drop, ctx, ::BlockDestroySound::Play);
#else
    return level.destroyBlock(region, pos, drop, ctx);
#endif
}

/// Tells the six neighbours of `pos` that it changed (BlockSource::updateNeighborsAt).
void updateNeighborsAt(BlockSource& region, BlockPos const& pos);

/// Player::interact with the main hand.
InteractionResult interact(Player& player, Actor& actor, Vec3 const& location);

/// How long `item` burns in a furnace whose smelt takes `burnInterval` ticks (0 if it is no fuel).
[[nodiscard]] float burnDuration(ItemStackBase const& item, float burnInterval);

/// The block's hardness ("destroy_time"): -1 for unbreakable blocks, 0 for instantly broken ones.
[[nodiscard]] float hardness(Block const& block);

/// Whether the stack's item has the item tag.
[[nodiscard]] bool hasItemTag(ItemStackBase const& stack, ItemTag const& tag);

/// Whether the stack is one of the items `descriptor` stands for (the data value is not compared).
[[nodiscard]] bool descriptorMatches(ItemDescriptor const& descriptor, ItemStack const& stack);

/// Calls `fn` for every registered block type until it returns false.
void forEachBlockType(std::function<bool(BlockType const&)> const& fn);

/// Whether a scheduled (not random) tick is pending for the block at `pos`.
[[nodiscard]] bool hasPendingTick(BlockSource& region, BlockPos const& pos);

/// Whether the mob is swinging an arm right now.
[[nodiscard]] bool isSwinging(Mob const& mob);

/// Fires the actor definition event `event` on the actor (as /event entity does).
bool executeActorEvent(Actor& actor, std::string const& event);

#ifdef LP_CLIENT
/// The font a font handle stands for.
[[nodiscard]] Font& fontOf(FontHandle const& handle);
#endif

} // namespace lp::game
