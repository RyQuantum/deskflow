/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Ryan
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include <chrono>
#include <cstdint>
#include <cstdlib>

namespace deskflow::platform {

// how long after leave() a motion event may still be one that the hardware
// generated before the cursor was warped to center
inline constexpr auto kStaleMotionGracePeriod = std::chrono::milliseconds(500);

//! Is a motion event received while off screen stale?
/*!
While off screen, the cursor is parked at the warp center, so a genuine
relayed event reports a position within one event's travel of it. An event
generated before leave() warped the cursor still reports a position near the
edge we left on that axis -- at least two thirds of the way from center to
edge. Only events within kStaleMotionGracePeriod of leave() are considered.
*/
inline bool isStaleMotionAfterLeave(
    std::chrono::steady_clock::duration sinceLeave, int32_t mx, int32_t my, int32_t xCenter, int32_t yCenter
)
{
  if (sinceLeave > kStaleMotionGracePeriod) {
    return false;
  }

  constexpr int32_t kStaleZoneNumerator = 2;
  constexpr int32_t kStaleZoneDenominator = 3;
  int32_t const staleZoneX = xCenter * kStaleZoneNumerator / kStaleZoneDenominator;
  int32_t const staleZoneY = yCenter * kStaleZoneNumerator / kStaleZoneDenominator;
  return std::abs(mx - xCenter) > staleZoneX || std::abs(my - yCenter) > staleZoneY;
}

} // namespace deskflow::platform
