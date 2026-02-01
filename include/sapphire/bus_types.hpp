#pragma once

#include <cstdint>
#include <optional>

namespace sapphire {

// Abstract, hardware-relative timing cost.
// Has NO inherent meaning until Sapphire interprets it.
struct BusTiming {
    std::uint64_t time_cost = 0;
};

// What kind of access occurred
enum class BusAccessKind {
    Read,
    Write
};

// Bus-observable facts about the access
struct BusAccessFlags {
    bool open_bus   = false;
    bool contention = false;
    bool device_hit = true; // false means "no responder"
};

// Result of a single bus access.
// Purely descriptive. No authority.
struct BusAccessResult {
    BusAccessKind kind;
    BusTiming timing;
    BusAccessFlags flags;

    // Present only for reads
    std::optional<std::uint32_t> value;
};

} // namespace sapphire
