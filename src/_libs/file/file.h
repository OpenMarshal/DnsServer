#ifndef _LIBS_FILE_H
#define	_LIBS_FILE_H

#include "FileNotFoundException.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <vector>

class IFile
{
public:
	virtual const char* getPath() = 0;
	
	virtual std::vector<IFile*> listFiles() throw(int) = 0;
	
	virtual bool exists() = 0;
	
	virtual bool isDir() = 0;
	virtual bool isFile() = 0;
	
	virtual bool remove() = 0;
	
	virtual char readChar() = 0;
	virtual void readChar(char* charPtr) = 0;
	virtual int read(char* buffer, int max) = 0;
	
	virtual bool makeFile() = 0;
	virtual bool makeDir() = 0;
	
	virtual bool copy(const char* newPath) = 0;
	virtual bool copy(std::string newPath) = 0;
	virtual bool move(const char* newPath) = 0;
	virtual bool move(std::string newPath) = 0;
	
	virtual std::istream* getInputStream() = 0;
	
	virtual void write(char c) = 0;
	virtual void write(std::string data) = 0;
	virtual void write(const char* data) = 0;
	virtual void write(const char* data, int size) = 0;
	virtual void write(const char* data, int start, int size) = 0;
	
	virtual bool isOpen() = 0;
	
	virtual bool open() throw(FileNotFoundException) = 0;
	virtual bool openWrite() = 0;
	virtual bool openAppend() = 0;
	virtual void close() = 0;
	
	virtual const char* getFileName() = 0;
	virtual const char* getExtension() = 0;
	virtual const char* getMimeType() = 0;
	
	virtual bool isEndOfFile() = 0;
	
	virtual struct tm getLastModifiedTime() = 0;
	virtual struct tm getLastStatusChangedTime() = 0;
	virtual struct tm getLastAccessTime() = 0;
	
	virtual off_t getSize() = 0;
};

class File : public IFile
{
public:
	File(const char* path);
	File(std::string path);
	
	~File()
	{
		delete[](path);
	}
	
	const char* getPath();
	
	std::vector<IFile*> listFiles() throw(int);
	
	bool exists();
	
	bool isDir();
	bool isFile();
	
	bool remove();
	
	char readChar();
	void readChar(char* charPtr);
	int read(char* buffer, int max);
	
	std::istream* getInputStream();
	
	void write(char c);
	void write(std::string data);
	void write(const char* data);
	void write(const char* data, int size);
	void write(const char* data, int start, int size);
	
	bool makeFile();
	bool makeDir();
	
	bool copy(const char* newPath);
	bool copy(std::string newPath);
	bool move(const char* newPath);
	bool move(std::string newPath);
	
	bool isOpen();
	
	bool open() throw(FileNotFoundException);
	bool openWrite();
	bool openAppend();
	void close();
	
	const char* getFileName();
	const char* getExtension();
	const char* getMimeType();
	
	bool isEndOfFile();
	
	struct tm getLastModifiedTime();
	struct tm getLastStatusChangedTime();
	struct tm getLastAccessTime();
	
	off_t getSize();
	static off_t getMaxSize();
	
private:
	struct stat info;
	bool infoInitialized;
	bool exist;
	
	std::ifstream* inStream;
	std::ofstream* outStream;
	
	const char* path;
	
	struct stat& getInfo();
};



#endif	/* _LIBS_FILE_H */

