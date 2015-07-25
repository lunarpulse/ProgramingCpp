#include <chrono>
#include <iostream>
 
using namespace std;
 
void RunTest(unsigned int numberIterations)
{
	auto start = chrono::high_resolution_clock::now();
	 
	 unsigned int squared{1};
	 
	for (unsigned int i{ 1 }; i < numberIterations; ++i)
	{
		squared *= i*i;
	}
	 
	auto end = chrono::high_resolution_clock::now();
	auto difference = end - start;
	 
	cout << "Time taken: "
	<< chrono::duration_cast<chrono::microseconds>(difference).count()
	<< " microseconds!" << endl;
}
 
int main(int argc, char* argv[])
{
	RunTest(10000000);
	RunTest(100000000);
	RunTest(1000000000);
	 
	return 0;
}