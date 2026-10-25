/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Ryan
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "MSWindowsStaleMotionTests.h"

#include "platform/MSWindowsStaleMotion.h"

using deskflow::platform::isStaleMotionAfterLeave;
using std::chrono::milliseconds;

namespace {
// 1920x1080 primary monitor: the cursor is parked here while off screen
constexpr int32_t kXCenter = 960;
constexpr int32_t kYCenter = 540;
} // namespace

void MSWindowsStaleMotionTests::genuineMotionNearCenterIsKept()
{
  QVERIFY(!isStaleMotionAfterLeave(milliseconds(5), kXCenter + 12, kYCenter - 7, kXCenter, kYCenter));
}

void MSWindowsStaleMotionTests::motionAtLeftEdgeRightAfterLeaveIsStale()
{
  // left the screen on the left edge; a 1000 Hz mouse still delivers a few
  // events generated before the warp, reporting positions at x == 0
  QVERIFY(isStaleMotionAfterLeave(milliseconds(3), 0, 400, kXCenter, kYCenter));
}

void MSWindowsStaleMotionTests::motionAtBottomEdgeRightAfterLeaveIsStale()
{
  QVERIFY(isStaleMotionAfterLeave(milliseconds(3), 900, 1079, kXCenter, kYCenter));
}

void MSWindowsStaleMotionTests::staleZoneStartsPastTwoThirdsOfHalfScreen()
{
  // two thirds of 960 is 640, so 1600 is the last kept position on the right
  QVERIFY(!isStaleMotionAfterLeave(milliseconds(3), kXCenter + 640, kYCenter, kXCenter, kYCenter));
  QVERIFY(isStaleMotionAfterLeave(milliseconds(3), kXCenter + 641, kYCenter, kXCenter, kYCenter));
}

void MSWindowsStaleMotionTests::edgeMotionAfterGracePeriodIsKept()
{
  QVERIFY(!isStaleMotionAfterLeave(milliseconds(501), 0, 400, kXCenter, kYCenter));
}

void MSWindowsStaleMotionTests::graceBoundaryIsInclusive()
{
  QVERIFY(isStaleMotionAfterLeave(milliseconds(500), 0, 400, kXCenter, kYCenter));
}

QTEST_MAIN(MSWindowsStaleMotionTests)
