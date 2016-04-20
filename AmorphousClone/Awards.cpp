#include "Awards.h"


Awards::Awards() {
	for(auto& i : awards) { i = 0; }
}


Awards::~Awards() {
}

void Awards::loadAwards(uint32_t a, uint32_t b, uint32_t c) {
	awards[0] = a;
	awards[1] = b;
	awards[2] = c;
	decrypt();
}

std::string Awards::saveAwards() {
	encrypt();
	std::string awards = std::to_string(awards[0]) + std::to_string(awards[0]) + std::to_string(awards[0]);
	decrypt();
	return awards;
}

void Awards::encrypt() {
	for(auto& i : awards) {
		i <<= 4;
		i = ~i;
		i ^= 0xBADB;
	}
}

void Awards::decrypt() {
	for(auto& i : awards) {
		i ^= 0xBADB;
		i = ~i;
		i >>= 4;
	}
}
