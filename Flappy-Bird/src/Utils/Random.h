#pragma once

#include <memory>

template <typename T>
class Random {
public:
	Random() { Shuffle(); }
	T Shuffle();

	Random(T Min, T Max) { Shuffle(Min, Max); }
	T Shuffle(T Min, T Max);

	T GetRandom() { return m_Random; }
	operator T() const { return m_Random; }
private:
	T m_Random;
};

using Rand = Random<uint32_t>;
using Rand64 = Random<uint64_t>;

namespace std {
	template<typename T>
	struct hash<Random<T>> {
		std::size_t operator()(const Random<T>& rand) const {
			return hash<T>()((T)rand);
		}
	};
}