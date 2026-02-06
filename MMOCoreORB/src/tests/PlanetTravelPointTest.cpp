/*
 * PlanetTravelPointTest.cpp
 *
 *  Created on: 2025-01-01
 */

#include "gtest/gtest.h"

bool shouldBypassInterplanetaryCheckForTravel();

TEST(PlanetTravelPointTest, AlwaysAllowsInterplanetaryTravelOverride) {
	EXPECT_TRUE(shouldBypassInterplanetaryCheckForTravel());
}
