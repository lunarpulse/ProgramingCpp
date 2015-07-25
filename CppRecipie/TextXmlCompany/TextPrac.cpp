#include <iostream>
#include "LocalizationManager.h"
#include <chrono>

using namespace std;
using namespace chrono;
using namespace literals;
uint32_t Localization::Manager::x{ 0 };
uint32_t Localization::Manager::y{ 0 };
int main()
{
	auto startTimePoint = system_clock::now();// measuring the time
		
	Localization::Manager localizationManager;
	
	auto endTimePoint = system_clock::now();
	auto timeTaken = duration_cast<microseconds>(endTimePoint - startTimePoint);
	
	 
	cout <<  "instantiation -- Time Taken: " << timeTaken.count() << endl;
	
	startTimePoint = system_clock::now();// measuring the time
	cout <<  "Time measuring"<< endl;
	
	localizationManager.SetColumn(Localization::Column::COMPANYNAME);
	
	endTimePoint = system_clock::now();
	timeTaken = duration_cast<microseconds>(endTimePoint - startTimePoint);
	cout  <<  "COMPANYNAME Setup -- Time Taken: " << timeTaken.count() << endl;
	
	string xmlContent{};
	startTimePoint = system_clock::now();// measuring the time
	
	for (uint32_t i{0}; i<Localization::Manager::x; ++i)
	{
		cout<< "COMPANYNAME Names: ";
		xmlContent = localizationManager.GetString(i);
		cout << xmlContent.c_str() << endl;
	}
	endTimePoint = system_clock::now();
	timeTaken = duration_cast<microseconds>(endTimePoint - startTimePoint);
	cout <<  "Loading -- Time Taken: " << timeTaken.count() << endl;
	
	startTimePoint = system_clock::now();// measuring the time
	localizationManager.SetColumn(Localization::Column::SYMBOL);
	for (uint32_t j{0}; j<Localization::Manager::x; ++j)
	{
		cout<< "SYMBOL version: ";
		xmlContent = localizationManager.GetString(j);
		cout << xmlContent.c_str() << endl;
	}
	
	endTimePoint = system_clock::now();
	timeTaken = duration_cast<microseconds>(endTimePoint - startTimePoint);
	cout <<  "Loading -- Time Taken: " << timeTaken.count() << endl;
	
	auto currentTimePoint = system_clock::now();
	auto currentTime = system_clock::to_time_t( currentTimePoint );
	auto timeText = ctime( &currentTime );
	
	cout << timeText << endl;
	
	return 0;
}