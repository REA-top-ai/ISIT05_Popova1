#include <iostream>
#include <fstream>

static bool read_headers(const char* filename, unsigned char* data, int count) {
std::ifstream in(filename, std::ios::binary);
if (!in.is_open()) {
return false;
}
in.read((char*)data, count);
return true;
}

static int to_short(unsigned char* p) {
int result = p[0];
result = result + p[1] * 256;
return result;
}
static int to_int(unsigned char* p) {
int result = p[0];
result = result + p[1] * 256;
result = result + p[2] * 256 * 256;
result = result + p[3] * 256 * 256 * 256;
return result;
}

int main(int argc, char** argv) {
const char* filename = "image.bmp";
if (argc > 1) {
filename = argv[1];
}

unsigned char data[54];
if (!read_headers(filename, data, 54)) {
std::cout << "open error" << std::endl;
return 0;
}

if (data[0] != 'B' || data[1] != 'M') {
std::cout << "not a bmp" << std::endl;
return 0;
}

int fsize = to_int(data + 2);
int offset = to_int(data + 10);

int hsize = to_int(data + 14);
int w = to_int(data + 18);
int h = to_int(data + 22);
int planes = to_short(data + 26);
int bits = to_short(data + 28);
int compr = to_int(data + 30);
int imgsize = to_int(data + 34);
int xppm = to_int(data + 38);
int yppm = to_int(data + 42);
int used = to_int(data + 46);
int important = to_int(data + 50);

std::cout << "signature: " << data[0] << data[1] << std::endl;
std::cout << "file size: " << fsize << std::endl;
std::cout << "data offset: " << offset << std::endl;
std::cout << "info header size: " << hsize << std::endl;
std::cout << "width: " << w << std::endl;
std::cout << "height: " << h << std::endl;
std::cout << "planes: " << planes << std::endl;
std::cout << "bits per pixel: " << bits << std::endl;
std::cout << "compression: " << compr << std::endl;
std::cout << "image size: " << imgsize << std::endl;
std::cout << "x pixels per meter: " << xppm << std::endl;
std::cout << "y pixels per meter: " << yppm << std::endl;
std::cout << "colors used: " << used << std::endl;
std::cout << "colors important: " << important << std::endl;
return 0;
}
