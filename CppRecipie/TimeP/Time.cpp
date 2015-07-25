
#include <ctime>
#include <chrono>
#include <iostream>
#include <thread>
 
using namespace std;
using namespace chrono;
using namespace literals;
 
int main()
{
	
	 
 auto currentTimePoint = system_clock::now();
auto currentTime = system_clock::to_time_t( currentTimePoint );
auto timeText = ctime( &currentTime );
 
cout << timeText << endl;
cout<< "How many iterations? ";
int m{0};
cin>>m;

int n{0};
while(n < m){

	auto startTimePoint = system_clock::now();
	 
	this_thread::sleep_for(1000ms);
	 
	auto endTimePoint = system_clock::now();
	 
	auto timeTaken = duration_cast<milliseconds>(endTimePoint - startTimePoint);
	 
	cout <<n+1 <<  "th iteration -- Time Taken: " << timeTaken.count() << endl;
	 
	 
	  currentTimePoint = system_clock::now();
	 currentTime = system_clock::to_time_t( currentTimePoint );
	 timeText = ctime( &currentTime );
	 
	cout << timeText << endl;
	++n;
}

return 0;

}