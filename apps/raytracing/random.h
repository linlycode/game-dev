#ifndef RANDOM_H
#define RANDOM_H

#include <random>

template <typename T, typename Generator = std::mt19937>
class RandomNumberGenerator {
public:
	virtual T operator()() = 0;
};

template <typename Generator>
class RandomNumberGenerator<float, Generator> {
	Generator m_generator;
	std::uniform_real_distribution<float> m_distribution;

public:
	RandomNumberGenerator(float min, float max)
		: m_generator(std::random_device()()), m_distribution(min, max) {}

	float operator()() { return m_distribution(m_generator); }
};

#endif
