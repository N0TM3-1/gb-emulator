#include "../include/cart.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

uint8_t cart_data[MAX_CART_SIZE];
bool cart_loaded = false;
cart_header* cart_hdr = (cart_header*)(cart_data + 0x100);
char runtime_path_buffer[MAX_PATH];

bool get_runtime_path() {
	if (!GetCurrentDirectoryA(MAX_PATH, runtime_path_buffer))
		return false;
	else
		return true;
}

bool cart_open() {
	if (!get_runtime_path()) {
		std::cerr << "Failed to get runtime path." << std::endl;
		return false;
	}

	char filename[MAX_PATH];
	OPENFILENAMEA ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Game Boy ROMs (*.gb;*.gbc)\0*.gb\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.lpstrInitialDir = runtime_path_buffer;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Open Game Boy ROM";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	if (GetOpenFileNameA(&ofn)) {
		cart_load(filename);
		return true;
	}
	return false;
}

void cart_print_info() {
	printf("Cart entry point: %02X %02X %02X %02X\n",
		cart_hdr->entry_point[0],
		cart_hdr->entry_point[1],
		cart_hdr->entry_point[2],
		cart_hdr->entry_point[3]);
	printf("Cart title: %s\n", cart_hdr->title);
	printf("GCB flag: %02X\n", cart_hdr->cgb_flag);
	printf("New licensee code: %02X %02X\n", cart_hdr->new_licensee_code[0], cart_hdr->new_licensee_code[1]);
	printf("SGB flag: %02X\n", cart_hdr->sgb_flag);
	printf("Cart type: %02X\n", cart_hdr->cartridge_type);
	printf("ROM size: %02X\n", cart_hdr->rom_size);
	printf("RAM size: %02X\n", cart_hdr->ram_size);
	printf("Destination code: %02X\n", cart_hdr->destination_code);
	printf("Old licensee code: %02X\n", cart_hdr->old_licensee_code);
	printf("Version: %02X\n", cart_hdr->mask_rom_version);
	printf("Header checksum: %02X\n", cart_hdr->header_checksum);
	printf("Global checksum: %02X %02X\n", cart_hdr->global_checksum[0], cart_hdr->global_checksum[1]);
}

bool cart_load(const char* filename) {
	std::streampos size;
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()) {
		size = file.tellg();
		file.seekg(0, std::ios::beg);
		file.read((char*)cart_data, MAX_CART_SIZE);
		file.close();
		printf("ROM loaded: %s; Size: %lli bytes\n", filename, std::streamoff(size));
		return true;
	}
	printf("Failed to load ROM: %s\n", filename);
	return false;
}