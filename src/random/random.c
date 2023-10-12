#include "random.h"
#include <time.h>

_Thread_local u64 seedseed_ = 0;
_Thread_local u64 seed_[4] = {0};

u64 splitmix64() {
	seedseed_ += 0x9e3779b97f4a7c15;
	u64 z = seedseed_;
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	z = (z ^ (z >> 31));
	return z;
}

void random_seed(u64 seed) {
	if (seed == 0) {
		if (seedseed_ == 0) {
			struct timespec time;
			timespec_get(&time, TIME_UTC);
			seedseed_ = time.tv_nsec;
		} else {
			return;
		}
	} else {
		seedseed_ = seed;
	}
	seed_[0] = splitmix64();
	seed_[1] = splitmix64();
	seed_[2] = splitmix64();
	seed_[3] = splitmix64();
}

u64 rotl(u64 x, u64 k) {return (x << k) | (x >> (64 - k));}
u64 random_u64(void) {
	u64 result = rotl(seed_[1] * 5, 7) * 9;
	u64 t = seed_[1] << 17;
	seed_[2] ^= seed_[0];
	seed_[3] ^= seed_[1];
	seed_[1] ^= seed_[2];
	seed_[0] ^= seed_[3];
	seed_[2] ^= t;
	seed_[3] = rotl(seed_[3], 45);
	return result;
}

f64 random_f64(void) {
	return (random_u64() >> 11) * 0x1.0p-53;
}

void random_jump(void) {
	u64 jump[] = {
		0x180ec6d33cfd0aba,
		0xd5a61266f0c9392c,
		0xa9582618e03fc9aa,
		0x39abdc4529b1661c
	};
	u64 s0 = 0;
	u64 s1 = 0;
	u64 s2 = 0;
	u64 s3 = 0;
	for (u64 i = 0; i < 4; i++) {
		for (u64 b = 0; b < 64; b++) {
			if (jump[i] & 1ull << b) {
				s0 ^= seed_[0];
				s1 ^= seed_[1];
				s2 ^= seed_[2];
				s3 ^= seed_[3];
			}
			random_u64();
		}
	}
	seed_[0] = s0;
	seed_[1] = s1;
	seed_[2] = s2;
	seed_[3] = s3;
}
