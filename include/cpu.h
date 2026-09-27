#pragma once
#include <stdint.h>
struct registers {
	struct { // AF register
		union {
			uint8_t f; // Flags
			uint8_t a; // Accumulator
		};
		uint16_t af;
	};
	struct { // BC register
		union {
			uint8_t c;
			uint8_t b;
		};
		uint16_t bc;
	};
	struct { // DE register
		union {
			uint8_t e;
			uint8_t d;
		};
		uint16_t de;
	};
	struct { // HL register
		union {
			uint8_t l;
			uint8_t h;
		};
		uint16_t hl;
	};
	uint16_t sp; // Stack pointer
	uint16_t pc; // Program counter
};

extern registers cpu_registers;

void cpu_init();
void cpu_fetch();
void cpu_execute();