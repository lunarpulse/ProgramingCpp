#include <cstdlib>
#include <iostream>
 
using namespace std;
 
struct MemoryHeader
{
	const char* m_Filename{ nullptr };
	int m_Line{ -1 };
};
 
void* operator new(size_t size, const char* filename, int line) noexcept
{
	void* pMemory{ malloc(size + sizeof(MemoryHeader)) };
	 
	MemoryHeader* pMemoryHeader{ reinterpret_cast<MemoryHeader*>(pMemory) };
	pMemoryHeader->m_Filename = filename;
	pMemoryHeader->m_Line = line;
	 
	return static_cast<void*>(static_cast<char*>(pMemory)+sizeof(MemoryHeader));
}
 
void operator delete(void* pMemory) noexcept
{
	char* pMemoryHeaderStart{ reinterpret_cast<char*>(pMemory)-sizeof(MemoryHeader) };
	MemoryHeader* pMemoryHeader{ reinterpret_cast<MemoryHeader*>(pMemoryHeaderStart) };
	 
	cout << "Deleting memory allocated from: "
	<< pMemoryHeader->m_Filename << ":" << pMemoryHeader->m_Line << endl;
	 
	free(pMemoryHeader);
}
 
#define new new(__FILE__, __LINE__)
 
class MyClass
{
	public:
	MyClass()
	{}
	
	MyClass(int i):m_Value{i}
	{
		
	}
	
	private:
	int m_Value{ 1 };
	
	
	
};
 
int main(int argc, char* argv[])
{
	int* pInt{ new int };
	*pInt = 1;
	delete pInt;
	 
	MyClass* pClass{ new MyClass };
	delete pClass;
	 int* pInt1{ new int };
	*pInt1 = 23;
	delete pInt1;
	 
	MyClass* pClass1{ new MyClass(2) };
	delete pClass1;
	return 0;
}