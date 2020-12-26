#pragma once
#include "FS.h"

bool writeFile(const char *path, const unsigned char *data, unsigned long len);
bool appendFile(const char *path, const unsigned char *data, unsigned long len);
bool initFileSystem();
bool createDir(const char *path);
bool fileExists(const char *path);
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void listDir2(const char * dirname, uint8_t levels);
