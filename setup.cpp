// AutoComp setup.
// (c) Aran Roig, 2020 XDDDDD
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

bool restart = false;

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

bool folderExists(std::string p);
void createFolder(std::string p);
bool fileExists(std::string p);
bool fileEmpty(std::string p);
void copyFile(std::string a, std::string b);

void checkContests();
void createContests();
void generateContestsFolder(int p, int r);

void buildRun();
void applyRunAlias();
void printCompilerSettings();

void cleanup();
void deleteContestFolder();

std::string getFile(std::string p);
std::string getCaseLine();

// Funcio main
int main(){
	intro();
	initialSetup();
}

void initialSetup(){
	// Create a dir
	
	printd("Checking resource folder and files...");	
	if(!folderExists("rsc")){
		warning("No resource folder! Aborting...");
		return;
	}

	if(!fileExists("rsc/main.cpp")){
		warning("No main.cpp file! Aborting...");
		return;
	}

	if(!fileExists("rsc/compile.txt")){
		warning("No compile.txt file! Aborting...");
	}

	if(!fileExists("rsc/debug.h")){
		warning("No debug.h file! Aorting...");
		return;
	}
	
	printd("Checking contests folder...");
	checkContests();
}

void buildRun(){
	printd("Building run...");
	std::system("g++ run.cpp -lstdc++fs -std=gnu++0x -o run");
	printd("Run builded correctly");	
}

void applyRunAlias(){
	std::system("grep 'alias run' ~/.bashrc > .resgrep.p");
	if(fileEmpty(".resgrep.p")){
		printd("Adding alias run...");
		std::system("echo 'alias run=./run' >> ~/.bashrc");
		printd("Alias run added. Write run inside the console to execute AutoComp");
	}
	std::remove(".resgrep.p");
	printd("Done.");
	std::cout << termcolor::cyan << termcolor::reverse << "NOTE:" << termcolor::reset << " you will need to restart the terminal to run your programs" << endl;
}

void printCompilerSettings(){
	printd("Default compiler settings:");
	std::cout << endl << getFile("rsc/compile.txt") << endl << endl;
	printd("Generating contest folders. This might take a while...");
}

void checkContests(){
	if(!folderExists("contests")){
		createContests();
	} else {
		deleteContestFolder();
	}
}

void deleteContestFolder(){
	warning("Do you really want to delete the contest folder? (y = yes)");
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

void cleanup(){
	printd("Removing run...");
	std::remove("run");
	printd("Run removed.");
	std::cout << endl;
	printd("Done! Happy coding! ;)");
	
}

void createContests(){
	createFolder("contests");
	printd("Created contests folder");
	
	buildRun();
		
	applyRunAlias();

	printExplanation();
		
	// Ask for contest number

	int p = promptNumber();
	while(p > 25){
		std::cout << termcolor::red << "> Invalid number. It must be smaller than 26" << endl << "> ";
		std::cin >> p;
	}
	std::cout << termcolor::red << "> " << termcolor::reset << "And how many problems for each folder?" << endl;
	int r = promptNumber();
	
	printCompilerSettings();

	generateContestsFolder(p, r);

	cleanup();
}

void generateContestsFolder(int p, int r){
	for(int x = 0; x < p; x++){
		std::string path = "contests/";
		path += x + 'A';
		createFolder(path);
		path += '/';
		for(int y = 1; y <= r; y++){
			std::string pPath = path + std::to_string(y);
			createFolder(pPath);
			copyFile("rsc/main.cpp", pPath + "/main.cpp");
			copyFile("run", pPath + "/run");
			copyFile("rsc/compile.txt", pPath + "/compile.txt");
			copyFile("rsc/debug.h", pPath + "/debug.h");
			copyFile("rsc/header.cpp", pPath + "/header.cpp");
			// Generar cases.txt
			std::ofstream cases;
			cases.open(pPath + "/cases.txt");
			// Poner el titulo
			cases << "Contest " << (char)(x + 'A') << " - Problem " << y << endl;
			cases << endl << "// Input Here" << endl;
			cases << getCaseLine() << endl;
			cases << endl << "// Output here" << endl;
			cases << getCaseLine() << endl << endl;
			cases << "// Second input here" << endl;
			cases << getCaseLine() << endl << "// Second" << endl << "// Output" << endl << "// Here" << endl << getCaseLine() << endl;

			cases.close();
		}
	}

}

std::string getFile(std::string p){
	std::stringstream ss;
	std::string temp;
	std::ifstream infile;
	infile.open(p);
	while(std::getline(infile, temp)) ss << temp;
	infile.close();
	return ss.str();
}

std::string getCaseLine(){
	std::string res = "";
	for(int i = 0; i < 50; i++) res += '~';
	return res;	
}

void createFolder(std::string p){
	if(!folderExists(p)) fs::create_directory(p.c_str());
}

bool fileExists(std::string p){
	return fs::exists(p);
}

bool fileEmpty(std::string p){
	std::ifstream pFile;
	pFile.open(p.c_str());
	return pFile.peek() == std::ifstream::traits_type::eof();
}

void copyFile(std::string a, std::string b){
	fs::copy(a.c_str(), b.c_str());
}

int promptNumber(){
	std::cout << termcolor::cyan << "> " << termcolor::reset;
	int res;
	std::cin >> res;
	return res;
}

void printExplanation(){
	std::cout << termcolor::red << "> " << termcolor::reset << "Welcome to " << termcolor::reverse << "autocomp" << termcolor::reset << "!" << endl;
	std::cout << termcolor::red << "> " << termcolor::reset << "Autocomp is a executable that can help you in competitive programming contests. It provides case testing and time monitoring about your C++ algorithms. It's very easy to configure and to use. Let's start configuring your contest folders" << endl << endl;
	std::cout << termcolor::red << "> " << termcolor::reset << "Each problem will have its own " << termcolor::reverse << "cases.txt" << termcolor::reset << " file. In this file you can add cases to test your problem. You will only need to type the input once, and you will save a " << termcolor::reverse << "lot" << termcolor::reset << " of time." << endl << endl;
	std::cout << termcolor::cyan << termcolor::reverse << "NOTE:" << termcolor::reset << " You can change the compile settings of the problems in the " << termcolor::reverse << "compile.txt" << termcolor::reset << " file inside the " << termcolor::reverse << "rsc" << termcolor::reset << " directory. This file will be copied in the contest subfolders with the " << termcolor::reverse << "debug.h" << termcolor::reset << " File. In debug.h you shuld have all your debug functions." << endl << termcolor::red << "> " << termcolor::reset << " If you want to change it now, exit the setup by pressing " << termcolor::reverse << "Ctrl+C" << termcolor::reset << "." << endl << endl;
	std::cout << termcolor::red << "> " << termcolor::reset << "How many contest folders do you want to have?" << endl;
}

void warning(std::string s){
	std::cout << termcolor::on_red << termcolor::white << termcolor::bold << s << termcolor::reset << endl;
}

bool folderExists(std::string p){
	fs::path pa = p.c_str();
	fs::file_status s = fs::file_status{};
	if(fs::status_known(s) ? fs::exists(s) : fs::exists(pa)) return true;
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
	std::cout << termcolor::cyan << termcolor::bold << print("AutoComp") << termcolor::white << endl;
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
