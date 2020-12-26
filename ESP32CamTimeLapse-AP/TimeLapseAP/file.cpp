#include "FS.h"
#include "SD_MMC.h"

bool writeFile(const char *path, const unsigned char *data, unsigned long len)
{
	Serial.printf("Writing file: %s\n", path);
	File file = SD_MMC.open(path, FILE_WRITE);
	if (!file)
	{
		Serial.println("Failed to open file for writing");
		return false;
	}
	if (file.write(data, len))
	{
		Serial.println("File written");
	}
	else
	{
		Serial.println("Write failed");
		return false;
	}
	file.close();
	return true;
}

bool appendFile(const char *path, const unsigned char *data, unsigned long len)
{
	Serial.printf("Appending to file: %s\n", path);

	File file = SD_MMC.open(path, FILE_APPEND);
	if (!file)
	{
		Serial.println("Failed to open file for writing");
		return false;
	}
	if (file.write(data, len))
	{
		Serial.println("File written");
	}
	else
	{
		Serial.println("Write failed");
		return false;
	}
	file.close();
	return true;
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void listDir2(const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = SD_MMC.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir2(file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

bool initFileSystem()
{
	if (!SD_MMC.begin("/sdcard",true))
	{
		Serial.println("Card Mount Failed");
    //switch FlashLED on
    pinMode(4, OUTPUT);
    digitalWrite(4, 1);
		return false;
	}
	uint8_t cardType = SD_MMC.cardType();

	if (cardType == CARD_NONE)
	{
		Serial.println("No SD card attached");
    //switch FlashLED on
    pinMode(4, OUTPUT);
    digitalWrite(4, 1);
		return false;
	}
	Serial.print("SD Card Type: ");
	if (cardType == CARD_MMC)
		Serial.println("MMC");
	else if (cardType == CARD_SD)
		Serial.println("SDSC");
	else if (cardType == CARD_SDHC)
		Serial.println("SDHC");
	else

		Serial.println("UNKNOWN");

	uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
	Serial.printf("SD Card Size: %lluMB\n", cardSize);
	Serial.printf("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024));
	Serial.printf("Used space: %lluMB\n", SD_MMC.usedBytes() / (1024 * 1024));

  //Testing listDir
  listDir(SD_MMC, "/", 0);
  listDir2("/", 0);
  
	return true;
}

bool createDir(const char *path)
{
	Serial.printf("Creating Dir: %s\n", path);
	if (SD_MMC.mkdir(path))
	{
		Serial.println("Dir created");
	}
	else
	{
		Serial.println("mkdir failed");
		return false;
	}
	return true;
}

bool fileExists(const char *path)
{
	return SD_MMC.exists(path);
}
