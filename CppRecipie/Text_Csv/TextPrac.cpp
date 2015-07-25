#include <iostream>
#include "LocalizationManager.h"
#include <chrono>

using namespace std;
using namespace chrono;
using namespace literals;

int main()
{
	auto currentTimePoint = system_clock::now();
	auto currentTime = system_clock::to_time_t( currentTimePoint );
	auto timeText = ctime( &currentTime );
	
	auto startTimePoint = system_clock::now();// measuring the time
		
	Localization::Manager localizationManager;
	
	auto endTimePoint = system_clock::now();
	auto timeTaken = duration_cast<microseconds>(endTimePoint - startTimePoint);
	
	 
	cout <<  "instantiation -- Time Taken: " << timeTaken.count() << endl;
	startTimePoint = system_clock::now();// measuring the time
	
	string color{ localizationManager.GetString(Localization::STRING_COLOR) };
	cout << "EN_US Localized string: " << color.c_str() << endl;
	localizationManager.SetLanguage(Localization::Languages::EN_GB);
	color = localizationManager.GetString(Localization::STRING_COLOR);
	cout << "EN_GB Localized string: " << color.c_str() << endl;
	
	endTimePoint = system_clock::now();
	timeTaken = duration_cast<microseconds>(endTimePoint - startTimePoint);
	cout  <<  "Setup -- Time Taken: " << timeTaken.count() << endl;
	
	startTimePoint = system_clock::now();// measuring the time
	
	cout<< "GB version"<<endl;
	color = localizationManager.GetString(0);
	cout << color.c_str() << endl;
	 
	color = localizationManager.GetString(1);
	cout << color.c_str() << endl;
	
	 
	color = localizationManager.GetString(2);
	cout << color.c_str() << endl;
	
	 
	color = localizationManager.GetString(3);
	cout << color.c_str() << endl;
	
	endTimePoint = system_clock::now();
	timeTaken = duration_cast<microseconds>(endTimePoint - startTimePoint);
	cout <<  "GB -- Time Taken: " << timeTaken.count() << endl;
	
	
	localizationManager.SetLanguage(Localization::Languages::EN_US);
	
	cout<< "US version"<<endl;
	color = localizationManager.GetString(0);
	cout << color.c_str() << endl;
	 
	color = localizationManager.GetString(1);
	cout << color.c_str() << endl;
	
	 
	color = localizationManager.GetString(2);
	cout << color.c_str() << endl;
	
	 
	color = localizationManager.GetString(3);
	cout << color.c_str() << endl;
		
	return 0;
}