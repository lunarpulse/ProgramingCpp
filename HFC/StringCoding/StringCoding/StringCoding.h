#include <stdio.h>
#include <string.h>

using namespace std;

class StringCoding
{
private:
	std::string sKey;
public:

	StringCoding(void)
	{
		sKey =  "ATest";
	}
	
	StringCoding(const char *strKey)
	{
		if(strKey)
			sKey= strKey;
		else
			sKey = "Atest";
	}
	
	StringCoding(const StringCoding& aCopy)
	{
		skey= aCopy.sKey;
	}
	
public:
	std::string Encode(const char * strIn);
	std::string Decode(const char * strIn);
private:
	std::string Xor(const char *strIN);
};

