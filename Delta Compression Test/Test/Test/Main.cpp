#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	FILE* f;
	fopen_s(&f, "a.zip", "rb");
	string a = "";
	while (!feof(f)) {
		a += fgetc(f);
	}
	fclose(f);
	fopen_s(&f, "b.zip", "rb");
	string b = "";
	while (!feof(f)) {
		b += fgetc(f);
	}
	fclose(f);
	fopen_s(&f, "c.zip", "wb");
	for (int i = 0; i < a.size() && i < b.size(); i++) {
		fputc((a[i] ^ b[i]), f);
	}
	fclose(f);
}