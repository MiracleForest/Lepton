#include "game/Compat.h"

#include "mc/util/VariantParameterList.h"
#include "mc/world/actor/Mob.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/item/Item.h"
#include "mc/world/item/ItemDescriptor.h"
#include "mc/world/item/ItemStack.h"
#include "mc/world/item/ItemStackBase.h"
#include "mc/world/item/ItemTag.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/BlockTickingQueue.h"
#include "mc/world/level/Tick.h"
#include "mc/world/level/TickingQueueType.h"
#include "mc/world/level/block/Block.h"
#include "mc/world/level/block/BlockType.h"
#include "mc/world/level/block/actor/FurnaceBlockActor.h"
#include "mc/world/level/block/registry/BlockTypeRegistry.h"
#include "mc/world/level/chunk/LevelChunk.h"

#if LP_LL_VERSION >= 2660 && defined(LP_CLIENT)
#include "mc/util/NamedMolangScript.h" // completes a type ActorDefinitionDescriptor.h only declares
#include "mc/world/actor/ActorDefinitionDescriptor.h"
#endif

#ifdef LP_CLIENT
#include "mc/client/gui/Font.h"
#include "mc/client/gui/FontHandle.h"
#endif

namespace lp::game {

void updateNeighborsAt(BlockSource& region, BlockPos const& pos) {
#if LP_LL_VERSION >= 2660
    // 26.60 wants the neighbour change history, which mods cannot create; notify the six
    // neighbours the way updateNeighborsAt does.
    BlockPos const neighbours[] = {
        {pos.x, pos.y - 1, pos.z},
        {pos.x, pos.y + 1, pos.z},
        {pos.x, pos.y, pos.z - 1},
        {pos.x, pos.y, pos.z + 1},
        {pos.x - 1, pos.y, pos.z},
        {pos.x + 1, pos.y, pos.z},
    };
    for (auto const& n : neighbours) region.getBlock(n).neighborChanged(region, n, pos);
#else
    region.updateNeighborsAt(pos);
#endif
}

InteractionResult interact(Player& player, Actor& actor, Vec3 const& location) {
#if LP_LL_VERSION >= 2660
    return player.interact(actor, location, ::HandSlot::Mainhand);
#else
    return player.interact(actor, location);
#endif
}

float burnDuration(ItemStackBase const& item, float burnInterval) {
#if LP_LL_VERSION >= 2660
    // getBurnDuration(ItemStackBase const&, float) is gone; ask the overload that takes the item.
    auto const* type = item.isNull() ? nullptr : item.mItem.get();
    return type ? FurnaceBlockActor::getItemBurnDuration(*type, burnInterval) : 0.0f;
#else
    return FurnaceBlockActor::getBurnDuration(item, burnInterval);
#endif
}

float hardness(Block const& block) {
#if LP_LL_VERSION >= 2660
    // BlockType::getDestroySpeed() is gone. Without a tool no item-specific speed applies, so the
    // block's own destroy time is what is left.
    return block.getDestroySpeed(ItemStack::EMPTY_ITEM());
#else
    return block.getBlockType().getDestroySpeed();
#endif
}

bool hasItemTag(ItemStackBase const& stack, ItemTag const& tag) {
    // ItemStackBase::hasTag is client-only on 26.60; the item's tags are the same on both lines.
    auto const* item = stack.isNull() ? nullptr : stack.mItem.get();
    return item && item->hasTag(tag);
}

bool descriptorMatches(ItemDescriptor const& descriptor, ItemStack const& stack) {
#if LP_LL_VERSION >= 2660
    // sameItem(ItemStack const&, bool) is gone; compare with the stack's own descriptor.
    if (stack.isNull()) return false;
    return descriptor.sameItem(stack.getDescriptor(), false);
#else
    return descriptor.sameItem(stack, false);
#endif
}

void forEachBlockType(std::function<bool(BlockType const&)> const& fn) {
#if LP_LL_VERSION >= 2660
    // forEachBlockType is gone; it walked the registry's lookup map.
    for (auto const& [name, type] : *BlockTypeRegistry::get().mBlockLookupMap) {
        if (type && !fn(*type)) return;
    }
#else
    BlockTypeRegistry::get().forEachBlockType([&](BlockType const& t) { return fn(t); });
#endif
}

bool hasPendingTick(BlockSource& region, BlockPos const& pos) {
#if LP_LL_VERSION >= 2660 && defined(LP_CLIENT)
    // The client exports hasTickInPendingTicks(pos, queue type) no more; ask the tick queue the
    // block source uses (its own, or the chunk's) directly.
    BlockTickingQueue* queue = region.mTickQueue;
    if (!queue) {
        auto* chunk = region.getChunkAt(pos);
        if (!chunk) return false;
        queue = &chunk->getTickQueue();
    }
    Tick tick{};
    return queue->getNextUpdateForPos(pos, tick);
#else
    return region.hasTickInPendingTicks(pos, TickingQueueType::Internal);
#endif
}

bool isSwinging(Mob const& mob) {
#if LP_LL_VERSION >= 2660
    return mob.mSwingingHand->has_value(); // 26.60 records which hand swings
#else
    return static_cast<bool>(mob.mSwinging);
#endif
}

bool executeActorEvent(Actor& actor, std::string const& event) {
    VariantParameterList params{};
    params.mSelf = &actor;
#if LP_LL_VERSION >= 2660 && defined(LP_CLIENT)
    // The client exports Actor::executeEvent no more; the definition descriptor runs the same event.
    return ActorDefinitionDescriptor::executeEvent(actor, event, params);
#else
    return actor.executeEvent(event, params);
#endif
}

#ifdef LP_CLIENT
Font& fontOf(FontHandle const& handle) {
#if LP_LL_VERSION >= 2660
    // FontHandle::getFont() is gone from 26.60. The handle carries the font it was built with,
    // and the font repository keeps that font alive for as long as the client is up.
    return *handle.mDefaultFont;
#else
    return handle.getFont();
#endif
}
#endif

} // namespace lp::game
