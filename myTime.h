#include <ctime>
#include <string>

class Date{
protected:
	int year, month, date;
};

// protected mode inheritance
class Time: protected Date {
public:
	int hour, min, sec;

	//operator overloading
	void operator = (std::tm* now){
		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		date = now->tm_mday;
		hour = now->tm_hour;
		min = now->tm_min;
		sec = now->tm_sec;
	}

	std::string printDate(){
		std::string written_date = std::to_string(month)
			 + " / " + std::to_string(date)
			 + " / " + std::to_string(year);
		return written_date;
	}
};