#include <stdio.h>
#include <cstring>
#include <string>
#include <cstdlib>

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
		sKey= aCopy.sKey;
	}
	
public:
	std::string Encode(const char * strIn);
	std::string Decode(const char * strIn);
private:
	std::string Xor(const char *strIN);
};

std::string StringCoding ::Xor(const char * strIn)
{
	std::string sOut="";
	int nIndex= 0;
	for(int i=0;i< (int)strlen(strIn);++i)
	{
		
		char c= (strIn[i]^sKey[nIndex]);
		sOut += c;
		nIndex ++;
		if(nIndex == sKey.length())
			nIndex =0;
	}
}

std::string StringCoding::Encode(const char * strIn)
{
	return Xor(strIn);
}

std::string StringCoding::Decode(const char * strIn)
{
	return Xor(strIn);
}

int main(int argc, char **argv)
{	
	if(argc<2)
	{
		printf("Usage : StringCoding inputstring1 {inputstring2...]\n");
		exit(1);
	}
	
	StringCoding key("XXX");
	for(int i=1; i<argc; ++i)
	{
		std::string sEncode = key.Encode(argv[i]);
		printf("Input	String : [%s]\n", argv[i]);
		printf("Encoded	String : [%s]\n", sEncode.str());
		std::string sDecode = key.Decode(argv[i]);
		printf("Decoded	String : [%s]\n", sDecode.str());
	}
	
	printf("%d strings encoded\n", argc-1);
	return 0;
}

