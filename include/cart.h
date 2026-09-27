#pragma once
#include <stdint.h>
#include <Windows.h>

const int MAX_CART_SIZE = 1024 * 1024; // 1 MB
extern uint8_t cart_data[MAX_CART_SIZE];
extern bool cart_loaded;
extern char runtime_path_buffer[MAX_PATH];

struct cart_header {
	uint8_t entry_point[4]; // Entry point address
	uint8_t nintendo_logo[48]; // Nintendo logo
	uint8_t title[15]; // Game title
	uint8_t manufacturer_code[4]; // Manufacturer code
	uint8_t cgb_flag; // CGB flag
	uint8_t new_licensee_code[2]; // New licensee code
	uint8_t sgb_flag; // SGB flag
	uint8_t	cartridge_type; // Cartridge type
	uint8_t rom_size; // ROM size
	uint8_t ram_size; // RAM size
	uint8_t destination_code; // Destination code
	uint8_t old_licensee_code; // Old licensee code
	uint8_t mask_rom_version; // Mask ROM version
	uint8_t header_checksum; // Header checksum
	uint8_t global_checksum[2]; // Global checksum
};

extern cart_header* cart_hdr;

bool cart_open();
void cart_print_info();
bool cart_load(const char* filename);