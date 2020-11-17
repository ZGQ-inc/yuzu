// Copyright 2020 yuzu Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

// This file references various implementation details from Atmosphere, an open-source firmware for
// the Nintendo Switch. Copyright 2018-2020 Atmosphere-NX.

#pragma once

#include "common/assert.h"
#include "common/common_types.h"
#include "core/hardware_properties.h"

namespace Kernel {

class KAffinityMask {
private:
    static constexpr u64 AllowedAffinityMask = (1ul << Core::Hardware::NUM_CPU_CORES) - 1;

private:
    u64 mask;

private:
    static constexpr u64 GetCoreBit(s32 core) {
        ASSERT(0 <= core && core < static_cast<s32>(Core::Hardware::NUM_CPU_CORES));
        return (1ull << core);
    }

public:
    constexpr KAffinityMask() : mask(0) {
        ASSERT(this);
    }

    constexpr u64 GetAffinityMask() const {
        return this->mask;
    }

    constexpr void SetAffinityMask(u64 new_mask) {
        ASSERT((new_mask & ~AllowedAffinityMask) == 0);
        this->mask = new_mask;
    }

    constexpr bool GetAffinity(s32 core) const {
        return this->mask & GetCoreBit(core);
    }

    constexpr void SetAffinity(s32 core, bool set) {
        ASSERT(0 <= core && core < static_cast<s32>(Core::Hardware::NUM_CPU_CORES));

        if (set) {
            this->mask |= GetCoreBit(core);
        } else {
            this->mask &= ~GetCoreBit(core);
        }
    }

    constexpr void SetAll() {
        this->mask = AllowedAffinityMask;
    }
};

} // namespace Kernel
