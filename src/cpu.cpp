#include <iostream>
#include "../include/cpu.h"
#include "../include/cart.h"

registers cpu_registers;
uint8_t current_opcode = 0;
uint32_t instruction_counter = 0;
void* current_instruction = nullptr;

void cpu_init() {
	cpu_registers.af = 0x01B0; // Set the AF register to its initial value
	cpu_registers.bc = 0x0013; // Set the BC register to its initial value
	cpu_registers.de = 0x00D8; // Set the DE register to its initial value
	cpu_registers.hl = 0x014D; // Set the HL register to its initial value
	cpu_registers.sp = 0xFFFE; // Set the stack pointer to its initial value
	cpu_registers.pc = 0x100; // Set the program counter to the entry point of the cartridge
}

void cpu_fetch() {
	current_opcode = cart_data[cpu_registers.pc++];
	printf("Fetched opcode: %02X at PC: %04X\n", current_opcode, cpu_registers.pc - 1);
}

void cpu_execute() {

}