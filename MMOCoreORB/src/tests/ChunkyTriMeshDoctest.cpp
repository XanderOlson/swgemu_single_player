#include "tests/doctest/doctest.h"

#include "pathfinding/ChunkyTriMesh.h"

TEST_CASE("ChunkyTriMesh helpers longestAxis") {
	CHECK(chunky_trimesh::test::LongestAxis(5.0f, 3.0f) == 0);
	CHECK(chunky_trimesh::test::LongestAxis(2.0f, 7.0f) == 1);
}

TEST_CASE("ChunkyTriMesh helpers checkOverlapRect") {
	const float aMin[2] = {0.0f, 0.0f};
	const float aMax[2] = {2.0f, 2.0f};
	const float bMinOverlap[2] = {1.0f, 1.0f};
	const float bMaxOverlap[2] = {3.0f, 3.0f};
	const float bMinNoOverlap[2] = {3.5f, 3.5f};
	const float bMaxNoOverlap[2] = {4.0f, 4.0f};

	CHECK(chunky_trimesh::test::CheckOverlapRect(aMin, aMax, bMinOverlap, bMaxOverlap));
	CHECK_FALSE(chunky_trimesh::test::CheckOverlapRect(aMin, aMax, bMinNoOverlap, bMaxNoOverlap));
}

TEST_CASE("ChunkyTriMesh helpers checkOverlapSegment") {
	const float boxMin[2] = {0.0f, 0.0f};
	const float boxMax[2] = {2.0f, 2.0f};
	const float crossingStart[2] = {-1.0f, 1.0f};
	const float crossingEnd[2] = {3.0f, 1.0f};
	const float outsideStart[2] = {3.0f, 3.0f};
	const float outsideEnd[2] = {4.0f, 4.0f};

	CHECK(chunky_trimesh::test::CheckOverlapSegment(crossingStart, crossingEnd, boxMin, boxMax));
	CHECK_FALSE(chunky_trimesh::test::CheckOverlapSegment(outsideStart, outsideEnd, boxMin, boxMax));
}
