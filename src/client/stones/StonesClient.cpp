// U2 stones, client side: the celebratory lamps' tooltip line (always shown:
// Bedrock has no advanced-tooltip mode).
#ifdef LP_CLIENT

#include <string>
#include <vector>

#include "mc/world/item/ItemStackBase.h"

#include "client/Client.h"
#include "client/ui/Ui.h"
#include "feature/stones/Stones.h"
#include "game/Items.h"

LP_REGISTER_TOOLTIP([](ItemStackBase const& item, std::vector<std::string>& lines) {
    if (item.isNull() || !lp::feature::stones::isLamp(lp::game::itemId(item))) return;
    lines.push_back("§7" + lp::client::ctr("lepton.misc.celebration", "Made for celebrations"));
});

#endif
