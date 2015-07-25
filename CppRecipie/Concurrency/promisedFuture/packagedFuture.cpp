#include <future>
#include <iostream>
#include <sstream>

using namespace std;
 
long long Factorial(unsigned int value)
{
	this_thread::sleep_for(chrono::seconds(1));
	return value == 1
		? 1
			: value * Factorial(value - 1);
}
 
int main(int argc, char* argv[])
{
	if (argc != 2) {
     fprintf(stderr, "You need to give 1 argument of number\n");
     return 1;
   }
    
	using namespace chrono;
	 
	packaged_task<long long(unsigned int)> task{ Factorial };
	future<long long> taskFuture{ task.get_future() };
	
	istringstream ss(argv[1]);
	int x;
	if(!(ss>>x))
	{
		cerr<<"Invalid number"<<endl;
		return 1;
	}
	thread taskThread{ std::move(task), x};
	 
	while (taskFuture.wait_until(system_clock::now() + seconds(1)) != future_status::ready)
	{
		cout << "Still Waiting!" << endl;
	}
	 
	cout << "Factorial result was " << taskFuture.get() << endl;
	 
	taskThread.join();
	 
	return 0;
}