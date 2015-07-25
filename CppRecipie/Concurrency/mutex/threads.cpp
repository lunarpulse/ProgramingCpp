#include <cstdlib>
#include <iostream>
#include <stack>
#include <thread>
#include <vector>
#include <mutex>
#include <string>
 
using namespace std;
 
class MyManagedObject
{
private:
	static const unsigned int MAX_OBJECTS{ 8 };
	 
	using MyManagedObjectCollection = vector < MyManagedObject >;
	static MyManagedObjectCollection s_ManagedObjects;
	 
	static stack<unsigned int> s_FreeList;
	static mutex s_Mutex;
	 
	unsigned int m_Value{ 0xFFFFFFFF };
	
	string m_Name{};
	
public:
	MyManagedObject() = default;
	MyManagedObject(unsigned int value)
	: m_Value{ value }
	{
		m_Name.assign("MObj");
		m_Name.append(to_string(value));
	}
	
	//MyManagedObject(const MyManagedObject& other) = default;
	//MyManagedObject& operator=(const MyManagedObject& other) = default;
	
	MyManagedObject(const MyManagedObject& other)
	{
		
		m_Value = other.m_Value;
		//m_Name = other.m_Name;
		m_Name.replace(m_Name.begin(),m_Name.end(),other.m_Name);
		
				//cout<<"copy constructing object:"<<this.m_Name<<endl;
	}
	
	MyManagedObject& operator=(const MyManagedObject& other)
	{
		
		m_Value = other.m_Value;
		//m_Name = other.m_Name;
		m_Name.replace(m_Name.begin(),m_Name.end(),other.m_Name);
				//cout<<"copying object:"<<this.m_Name<<endl;
				
		return *this;
	}
	
	MyManagedObject(unsigned int value, string name)
	: m_Value{ value },m_Name{name}
	{

	}
	
	/*
	~MyManagedObject()
	{
		cout<<"deconsructing object:"<<m_Name<<endl;
		if(m_Name.empty())
		m_Name.clear();
	}
	*/
	
	 int GetValue()
	 {
		 return m_Value;
	 }
	 
	 string GetName()
	 {
		 return m_Name;
	 }
	 
	void* operator new(size_t numBytes)
	{
		lock_guard<mutex> lock{s_Mutex};
		
		void* objectMemory{};
				
		if (s_ManagedObjects.capacity() < MAX_OBJECTS)
		{
			s_ManagedObjects.reserve(MAX_OBJECTS);
		}
		 
		if (numBytes == sizeof(MyManagedObject) &&
			s_ManagedObjects.size() < s_ManagedObjects.capacity())
		{
			unsigned int index{ 0xFFFFFFFF };
			if (s_FreeList.size() > 0)
			{
				index = s_FreeList.top();
				s_FreeList.pop();
			}
			 
			if (index == 0xFFFFFFFF)
			{
				s_ManagedObjects.push_back({});
				index = s_ManagedObjects.size() - 1;
			}
			 
			objectMemory = s_ManagedObjects.data() + index;
		}
		else
		{
			objectMemory = malloc(numBytes);
		}
		 
		return objectMemory;
	}
	 
	void operator delete(void* pMem)
	{
		lock_guard<mutex> lock{s_Mutex};
		
		const intptr_t index{
			(static_cast<MyManagedObject*>(pMem)-s_ManagedObjects.data()) /
				static_cast<intptr_t>(sizeof(MyManagedObject)) };
		if (0 <= index && index < static_cast< intptr_t >(s_ManagedObjects.size()))
		{
			s_FreeList.emplace(static_cast<unsigned int>(index));
		}
		else
		{
			free(pMem);
		}
		
	}
	
	void printObject()
	{
		lock_guard<mutex> lock{s_Mutex};
		cout << GetName()<<": " << hex << showbase<< this << " , enclosed value: "<< dec << showbase<<GetValue()<< endl;
	}
};
 
MyManagedObject::MyManagedObjectCollection MyManagedObject::s_ManagedObjects{};
stack<unsigned int> MyManagedObject::s_FreeList{};
mutex MyManagedObject::s_Mutex;


void ThreadTask()
{
	MyManagedObject* pObject4{ new MyManagedObject(5)};
		
	pObject4->printObject();
	
	//cout << "pObject4: " << pObject4 << " , enclosed value: "<<pObject4.GetValue<< endl;
	 
	MyManagedObject* pObject5{ new MyManagedObject(6)};
	pObject5->printObject();
	 
	//cout << "pObject5: " << pObject5 << " , enclosed value: "<<pObject4.GetValue<< endl;
	 	cout<< "	deleting object 4"<<endl; 
	delete pObject4;
	pObject4 = nullptr;
	 
	MyManagedObject* pObject6{ new MyManagedObject(7)};
	pObject6->printObject(); 
	//cout << "pObject6: " << pObject6 << " , enclosed value: "<<pObject6.GetValue<< endl;
	 
	pObject4 = new MyManagedObject(8);
	pObject4->printObject(); 
	//cout << "pObject4: " << pObject4<< " , enclosed value: "<<pObject7.GetValue << endl;
	cout<< "	deleting object 4 to 6"<<endl; 
	delete pObject5;
	pObject5 = nullptr;
	 
	delete pObject6;
	pObject6 = nullptr;
	 
	delete pObject4;
	pObject4 = nullptr;
}
 
int main(int argc, char* argv[])
{
	//cout << hex << showbase;
	 
	thread myThread{ ThreadTask };
	 
	MyManagedObject* pObject1{ new MyManagedObject(1)};
	 
	pObject1->printObject();
	//cout << "pObject1: " << pObject1 << endl;
	 
	MyManagedObject* pObject2{ new MyManagedObject(2)};
	
	pObject2->printObject(); 
	//cout << "pObject2: " << pObject2 << endl;
	 
	delete pObject1;
	pObject1 = nullptr;
	 	cout<< "	deleting object 1"<<endl; 
	MyManagedObject* pObject3{ new MyManagedObject(3)};
	pObject3->printObject();
	//cout << "pObject3: " << pObject3 << endl;
	pObject1 = new MyManagedObject(4);
	
	pObject1->printObject();
	//cout << "pObject1: " << pObject1 << endl;
	 	cout<< "	deleting object 1 to 3"<<endl; 
	delete pObject2;
	pObject2 = nullptr;
	 
	delete pObject3;
	pObject3 = nullptr;
	 
	delete pObject1;
	pObject1 = nullptr;
	 
	myThread.join();
	 
	return 0;
}