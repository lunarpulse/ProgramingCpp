#include <future>
#include <iostream>
 
using namespace std;
 
long long Factorial(unsigned int value)
{
	cout <<showbase << hex << "ThreadTask thread: " << this_thread::get_id() << endl;
	return value == 1
		? 1
			: value * Factorial(value - 1);
}
 
 void printResult(int result)
 {
	 cout << showbase<<dec<<"Factorial result was " << result<< endl;
 }
int main(int argc, char* argv[])
{
	using namespace chrono;
	
	cout << "main thread: " << showbase<<hex<< this_thread::get_id() << endl;
	 
	auto taskFuture1 = async(Factorial, 3);
	printResult(taskFuture1.get());
	 
	auto taskFuture2 = async(launch::async, Factorial, 3);
	printResult(taskFuture2.get());
	 
	auto taskFuture3 = async(launch::deferred, Factorial, 3);
	printResult(taskFuture3.get());
	 
	auto taskFuture4 = async(launch::async | launch::deferred, Factorial, 3);
	printResult(taskFuture4.get());
	 
	return 0;
}