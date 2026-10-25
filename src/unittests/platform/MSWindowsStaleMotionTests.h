/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Ryan
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include <QTest>

class MSWindowsStaleMotionTests : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void genuineMotionNearCenterIsKept();
  void motionAtLeftEdgeRightAfterLeaveIsStale();
  void motionAtBottomEdgeRightAfterLeaveIsStale();
  void staleZoneStartsPastTwoThirdsOfHalfScreen();
  void edgeMotionAfterGracePeriodIsKept();
  void graceBoundaryIsInclusive();
};
