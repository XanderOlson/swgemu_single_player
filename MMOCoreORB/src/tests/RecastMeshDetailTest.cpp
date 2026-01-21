/*
 * RecastMeshDetailTest.cpp
 */

#include "gtest/gtest.h"

extern float rcTestVdot2(const float* a, const float* b);
extern float rcTestVdistSq2(const float* p, const float* q);
extern float rcTestVdist2(const float* p, const float* q);
extern float rcTestVcross2(const float* p1, const float* p2, const float* p3);

TEST(RecastMeshDetailTests, Vdot2HandlesOrthogonalVectors) {
	const float a[3] = {1.0f, 0.0f, 0.0f};
	const float b[3] = {0.0f, 0.0f, 1.0f};

	EXPECT_FLOAT_EQ(rcTestVdot2(a, b), 0.0f);
}

TEST(RecastMeshDetailTests, Vdot2HandlesParallelVectors) {
	const float a[3] = {2.0f, 0.0f, 3.0f};
	const float b[3] = {4.0f, 0.0f, 5.0f};

	EXPECT_FLOAT_EQ(rcTestVdot2(a, b), 23.0f);
}

TEST(RecastMeshDetailTests, VdistSq2MatchesExpectedDistanceSquared) {
	const float p[3] = {0.0f, 0.0f, 0.0f};
	const float q[3] = {3.0f, 0.0f, 4.0f};

	EXPECT_FLOAT_EQ(rcTestVdistSq2(p, q), 25.0f);
}

TEST(RecastMeshDetailTests, Vdist2MatchesExpectedDistance) {
	const float p[3] = {0.0f, 0.0f, 0.0f};
	const float q[3] = {3.0f, 0.0f, 4.0f};

	EXPECT_FLOAT_EQ(rcTestVdist2(p, q), 5.0f);
}

TEST(RecastMeshDetailTests, Vcross2MatchesOrientation) {
	const float p1[3] = {0.0f, 0.0f, 0.0f};
	const float p2[3] = {1.0f, 0.0f, 0.0f};
	const float p3[3] = {0.0f, 0.0f, 1.0f};
	const float p4[3] = {0.0f, 0.0f, -1.0f};

	EXPECT_FLOAT_EQ(rcTestVcross2(p1, p2, p3), 1.0f);
	EXPECT_FLOAT_EQ(rcTestVcross2(p1, p2, p4), -1.0f);
}
