// AutoComp setup.
// (c) Aran Roig, 2020
//
// Aquest cpp s'encarrega de la configuracio dels directoris dels contests

// Includes
#include <bits/stdc++.h>
#include <experimental/filesystem>
#include "termcolor.hpp"
#include <stdio.h>
#include <stdlib.h>

// Includes linux
#ifdef linux
#include <sys/ioctl.h> 
#include <unistd.h>
#endif

// Defines
#define endl '\n'

// Namespace
namespace fs = std::experimental::filesystem;
	
// Definicions de funcions
int numberDigits(int n);
int getLines();
int getRows();

std::string printLine(char c, int offset);
std::string print(std::string s);
void printd(std::string s);

void clear();
void intro();
void header();
void warning(std::string s);
void printExplanation();
int promptNumber();

void initialSetup();

bool folderExists(const fs::path& p);

// Funcio main
int main(){
	intro();
	initialSetup();
}

void initialSetup(){
	// Create a dir
	if(!folderExists("contests")){
		std::system("mkdir contests");
		printd("Created contests folder");
		printd("Building run...");
		std::system("g++ run.cpp -lstdc++fs -std=gnu++0x -o run");
		printd("Run builded correctly");
		std::cout << endl;
		printExplanation();
		int p = promptNumber();
		std::cout << termcolor::red << "> " << termcolor::reset << "And how many problems for each folder?" << endl;
		int r = promptNumber();
		
		for(int x = 0; x < p; x++){
			std::string s = "mkdir ./contests/contest";
			s += std::to_string(x);
			std::system(s.c_str());
			for(int y = 1; y <= r; y++){
				std::string s2 = s;
				s += "/";
				s += y;
				std::system(s2.c_str());
				
				std::string s3 = "cp ./original/main.cpp ./contests/contest" + x + "/" + y + "/";
				std::string s4 = "cp ./run ./contests/contest/" + x + "/" + y + "/";

				std::system(s3.c_str());
				std::system(s4.c_str());
			}
		}
	} else {
		warning("Do you really want to reset the contest folder? (y = yes)");
		std::cout << endl;
		char r;
		std::cin >> r;
		if(r == 'y' || r == 'Y'){
			printd("Deleting contest folder...");
			
			// Delete contest folder
			std::system("rm -R contests");
			std::system("./setup");
		}
	}
}

int promptNumber(){
	std::cout << termcolor::cyan << "> " << termcolor::reset;
	int res;
	std::cin >> res;
	return res;
}

void printExplanation(){
	std::cout << termcolor::red << "> " << termcolor::reset << "Welcome to " << termcolor::reverse << "autocomp" << termcolor::reset << "!" << endl;
	std::cout << termcolor::red << "> " << termcolor::reset << "Autocomp is a executable that can help you in competitive programming contests. It provides case testing and time monitoring about your C++ algorithms. It's very easy to configure and to use. Let's start configuring your contest folders" << endl;
	std::cout << termcolor::red << "> " << termcolor::reset << "How many contest folders do you want to have?" << endl;
}

void warning(std::string s){
	std::cout << termcolor::on_red << termcolor::white << termcolor::bold << s << termcolor::reset << endl;
}

bool folderExists(const fs::path& p){	
	fs::file_status s = fs::file_status{};
	if(fs::status_known(s) ? fs::exists(s) : fs::exists(p)) return true;
	else return false;
}

// Les altres funcions
void printd(std::string s){
	std::cout << termcolor::green << "> " << termcolor::reset << s << endl;
}

// getLines retorna el nombre de lineas de la consola
int getLines(){
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w.ws_row;
}

// getRows retorna el nombre de columnes de la consola
int getRows(){
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w.ws_col;
}
void intro(){
	clear();
	header();
	std::cout << termcolor::cyan << termcolor::bold << print("xXxXxXx AutoComp xXxXxXx") << termcolor::white << endl;
	std::cout << termcolor::yellow << termcolor::blue << print("A Competitive Programming auto compiler kit") << endl;
	std::cout << termcolor::yellow << print("Aran Roig, (c) 2020") << termcolor::reset << endl;
	header();
	std::cout << endl;
}

void header(){
	std::cout << termcolor::reverse << printLine('#', 0) << termcolor::reset << endl;
}

// clear fa clear
void clear(){
	std::system("clear");
}

// print mostra un text centrat
std::string print(std::string s){
	std::string res = "";
	int cols = getRows() - s.size();
	for(int b = 0; b < cols / 2; b++) res += " ";
	for(int e = 0; e < s.size(); e++) res += s[e];
	for(int a = 0; a < cols / 2; a++) res += " ";
	return res;
}


// printLine mostra una linea cobrint tota la pantalla o amb un offset
std::string printLine(char c, int offset){
	std::string res = "";
	for(int i = 0; i < getRows() - offset; i++) res += c;
	return res;
}

// numberDigits retorna el nombre de digits que te n
int numberDigits(int n){
	return (int)(std::log10(n))+1;
}
