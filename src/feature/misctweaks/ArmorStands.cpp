// ArmedArmorStands: Bedrock armor stands already have arms; a shield goes to the off hand, as on Java.

#include "ll/api/memory/Hook.h"

#include "mc/deps/shared_types/legacy/EquipmentSlot.h"
#include "mc/world/actor/ArmorStand.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/gamemode/InteractionResult.h"
#include "mc/world/item/ItemStack.h"

#include "feature/misctweaks/Internal.h"
#include "game/Compat.h"
#include "game/Inventory.h"
#include "game/Items.h"
#include "mod/Log.h"

namespace lp::feature::misctweaks {

namespace {

#if LP_LL_VERSION >= 2660
// 26.60 has no ArmorStand::_trySwapItem to redirect, so the shield is put into the off hand when
// the player uses it on an armor stand, the way that swap would have done it.
LL_TYPE_INSTANCE_HOOK(
    ArmorStandSwapHook,
    ll::memory::HookPriority::Normal,
    Player,
    &Player::interact,
    InteractionResult,
    LP_INTERACT_PARAMS
) {
    if (!LP_INTERACT_MAINHAND || isClientSide() || !cfg().enableArmedArmorStands || isSneaking()
        || actor.getTypeName() != "minecraft:armor_stand" || game::itemId(getCarriedItem()) != "minecraft:shield"
        || !game::isEmpty(actor.getOffhandSlot())) {
        return origin(LP_INTERACT_ARGS);
    }
    ItemStack shield = getCarriedItem();
    actor.setOffhandSlot(shield);
    setCarriedItem(ItemStack::EMPTY_ITEM());
    game::inv::sync(*this);
    log().info("misctweaks: shield placed in an armor stand's off hand by {}", getRealName());
    InteractionResult r{};
    r.mSuccess = true;
    r.mSwing   = true;
    return r;
}
#else
using Slot = SharedTypes::Legacy::EquipmentSlot;

LL_TYPE_INSTANCE_HOOK(
    ArmorStandSwapHook,
    ll::memory::HookPriority::Normal,
    ArmorStand,
    &ArmorStand::_trySwapItem,
    bool,
    Player& player,
    Slot    slot
) {
    if (cfg().enableArmedArmorStands && slot == Slot::Mainhand && game::itemId(player.getCarriedItem()) == "minecraft:shield"
        && game::isEmpty(getOffhandSlot())) {
        bool ok = origin(player, Slot::Offhand);
        if (ok) log().info("misctweaks: shield placed in an armor stand's off hand by {}", player.getRealName());
        return ok;
    }
    return origin(player, slot);
}
#endif

} // namespace

void installArmorStands() { ArmorStandSwapHook::hook(); }
void uninstallArmorStands() { ArmorStandSwapHook::unhook(); }

} // namespace lp::feature::misctweaks
