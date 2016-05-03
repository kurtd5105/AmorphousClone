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
	// Encrypt temporarily to save it to a string.
	encrypt();

	// Create the string by combining the string.
	std::string awards = std::to_string(awards[0]) + std::to_string(awards[1]) + std::to_string(awards[2]);

	// Decrypt the awards again so they are unchanged after the function returns.
	decrypt();
	return awards;
}

void Awards::encrypt() {
	// Perform a bitwise shift, bitwise negation, and then XOR with 0xBADB.
	for(auto& i : awards) {
		i <<= 4;
		i = ~i;
		i ^= 0xBADB;
	}
}

void Awards::decrypt() {
	// Reverse the encryption process by following the encryption process in reverse.
	for(auto& i : awards) {
		i ^= 0xBADB;
		i = ~i;
		i >>= 4;
	}
}
