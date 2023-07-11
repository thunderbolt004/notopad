#include "myTime.h"
#include <vector>

class Entry{
	//concept of containership
	Time written;
	std::string username, passwd;
	std::vector<std::string> data;
	
public:
	void setTime(void){
		std::time_t t = std::time(0);
		std::tm* now=  std::localtime(&t);
		written = now;
	}

	Entry(std::string _username, std::string _passwd, std::vector<std::string>* _data){
		username = _username;
		passwd = _passwd;
		data = *_data;
		setTime();
	}

	std::string printTime(){
		std::string written_time = std::to_string(written.hour)
		 + " : " + std::to_string(written.min)
		 + " : " + std::to_string(written.sec);
		return written_time;
	}
	std::vector<std::string> getData(){
		return data;
	}
};