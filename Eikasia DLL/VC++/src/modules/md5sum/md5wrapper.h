#ifndef MD5WRAPPER_H
#define MD5WRAPPER_H

#include <string>

class MD5;

class md5wrapper
{
	private:
		MD5 *md5;
	
		// internal hash function, calling the basic methods from md5.h
		std::string hashit(std::string text);

		// converts the numeric giets to a valid std::string
		std::string convToString(unsigned char *bytes);
		
	public:
		//constructor
		md5wrapper();

		//destructor
		~md5wrapper();
		
		// creates a MD5 hash from "text" and returns it as string
		std::string getHashFromString(std::string text);

		// creates a MD5 hash from a file specified in "filename" and	returns it as string
		std::string getHashFromFile(std::string filename);
};


#endif
