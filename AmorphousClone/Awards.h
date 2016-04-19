#pragma once
#include <cstdint>
#include <string>


class Awards {
public:
	Awards();
	~Awards();

	//Set up the awards class by taking the input numbers and decrypting them
	void loadAwards(uint32_t a, uint32_t b, uint32_t c);

	//Set the ith award (a = 0, b = 1, c = 2) flag (can set 1 bit or multiple) (awards[i] & flag)
	void setAward(unsigned int i, uint32_t flag) { awards[i] &= flag; }

	uint32_t getAward(unsigned int i) { return awards[i]; }

	//Save the awards to a string by encrypting them
	std::string saveAwards();

private:
	void encrypt();
	void decrypt();

	uint32_t awards[3];
};

