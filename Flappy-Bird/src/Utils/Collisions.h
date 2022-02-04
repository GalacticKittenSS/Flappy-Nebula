#pragma once

#include <Nebula.h>

inline bool AABBvsAABB(const Nebula::vec3& aMin, const Nebula::vec3& aMax, const Nebula::vec3& bMin, const Nebula::vec3& bMax) {
	return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
		(aMin.y <= bMax.y && aMax.y >= bMin.y) &&
		(aMin.z <= bMax.z && aMax.z >= bMin.z);
}