#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Entry.h"

class Account{
	std::string username, passwd;
	std::vector<Entry*> entries;
	
public:
	Account(std::string user, std::string _passwd){
		username = user;
		passwd = _passwd;
	}

	void newEntry(sf::String data, int size){
		std::string str;
		std::ofstream acc(username+".txt", std::ios::app);
		std::vector<std::string> all;
		for(auto it = data.begin() +size +1; it < data.end(); ++it){
			if(*it == '\n'){
				all.push_back(str);
				acc<<str<<std::endl;
				str = "";
			}
			else str.push_back(*it);
		}
		if(!str.empty()){
			all.push_back(str);
			acc<<str<<std::endl;
		}
		acc<<std::endl;
		entries.push_back(new Entry(username, passwd, &all));
	}

	void showEntry(){
		system("clear");
		for(Entry* entry: entries){
			entry->printTime();
			std::cout<<"At "<<entry->printTime()<<", "<<username<<" wrote: \n";
			for(std::string line: (entry->getData())){
				std::cout<<line<<std::endl;
			}
		}
	}
	
	std::string getPass(){
		return passwd; 
	}
};