/*
 * RecastLayersDoctest.cpp
 *
 *  Created on: 2025-01-01
 */

#include "gtest/gtest.h"

typedef unsigned char uchar;
typedef unsigned short ushort;

bool rcTestContains(const uchar* a, const uchar an, const uchar v);
bool rcTestAddUnique(uchar* a, uchar& an, int anMax, uchar v);
bool rcTestOverlapRange(const ushort amin, const ushort amax,
						const ushort bmin, const ushort bmax);

TEST(RecastLayersDoctest, ContainsPresentAndAbsent) {
	const uchar values[] = {1, 3, 5};

	EXPECT_TRUE(rcTestContains(values, 3, 3));
	EXPECT_FALSE(rcTestContains(values, 3, 2));
}

TEST(RecastLayersDoctest, AddUniqueHandlesDuplicatesAndCapacity) {
	uchar values[2] = {4, 7};
	uchar count = 2;

	EXPECT_TRUE(rcTestAddUnique(values, count, 2, 7));
	EXPECT_EQ(count, 2);

	EXPECT_FALSE(rcTestAddUnique(values, count, 2, 9));
	EXPECT_EQ(count, 2);
}

TEST(RecastLayersDoctest, AddUniqueAddsWhenSpaceAvailable) {
	uchar values[3] = {2, 4, 0};
	uchar count = 2;

	EXPECT_TRUE(rcTestAddUnique(values, count, 3, 9));
	EXPECT_EQ(count, 3);
	EXPECT_EQ(values[2], 9);
}

TEST(RecastLayersDoctest, OverlapRangeDetectsOverlapAndDisjoint) {
	EXPECT_TRUE(rcTestOverlapRange(1, 5, 4, 10));
	EXPECT_FALSE(rcTestOverlapRange(1, 3, 4, 6));
}
