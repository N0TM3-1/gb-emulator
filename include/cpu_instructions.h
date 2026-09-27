#pragma once
#include <stdint.h>

struct cpu_instructions {
	const char* name;
	uint8_t operand_length;
	void* execute;
};

extern const cpu_instructions instructions[256];