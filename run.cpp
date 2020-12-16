#include <bits/stdc++.h>
#include <experimental/filesystem>
#include "termcolor.hpp"
#include <stdio.h>
#include <stdlib.h>

// Getting linux console
#ifdef linux
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#define endl '\n'

// Variable definitions

// Function definitions
bool compile();
void copyMainCpp();
bool checkCompilation();
bool compareFile(std::string fa, std::string fb);
void testProgram();
void doPublicTests();
void colorize(long int x, int tests); // Per coloritzar coses
void graph(long int x); // Fa una grafica molt bonica
void graph(long int x, int tests); // Fa una grafica encara mes bonica amb tests
std::string exec(std::string cmd); // Executa una cosa molt bonica al cmd
bool compareFile(std::string a, std::string b); // Compara dos files
int numberDigits(int n);
void generateMainCpp();
//
//

int numberDigits(int n){
	return (int)(std::log10(n)) + 1;
}

// Getting console height and width
int getLines(){
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w.ws_row;
}

int getCols(){
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w.ws_col;
}

std::string getRaya(char c, int off){
	std::string s = "";
	for(int i = 0; i < getCols() - off; i++){
		s += c;
	}
	return s;
}

std::string print(std::string s){
	std::string res = "";
	int cols = getCols() - s.size();
	for(int b = 0; b < cols / 2; b++) res += " ";
	for(int e = 0; e < s.size(); e++) res += s[e];
	for(int a = 0; a < cols / 2; a++) res += " ";
	return res;
}

void testProgramYeet(){
	int cols = getCols();

	std::ifstream test ("cases.txt");
	if(!test.is_open()){
		std::cout << termcolor::red << termcolor::reverse << "FATAL ERROR OPENING cases.txt!!!" << termcolor::reset << endl;
		return;
	}
	int casenumber = 1;
	std::vector<int> results;
	std::string line;
	std::getline(test, line);
	std::cout << termcolor::cyan << termcolor::reverse << line << termcolor::reset << endl;
	std::cout << termcolor::white << termcolor::on_blue << getRaya('-', 0) << termcolor::reset << endl << endl;
	while(std::getline(test, line)){
		std::string casecin = "";
		std::getline(test, line);
		while(line.find("~~~~~~~~~~~~~~~~~~~~~~~~~~") == std::string::npos){
			casecin += line + endl;
			std::getline(test, line);
		}

		std::getline(test, line);
		std::string caseout = "";
		while(line.find("~~~~~~~~~~~~~~~~~~~~~~~~~~~") == std::string::npos){
			caseout += line + endl;
			std::getline(test, line);
		}

		std::ofstream filein, fileout;
		filein.open("._cin.txt");
		fileout.open("._cout.txt");
		filein << casecin;
		fileout << caseout;
		fileout.close();
		filein.close();
		
		int caseTextLength = numberDigits(casenumber) + 6; 

		std::cout << termcolor::white << termcolor::reverse << "CASE " << casenumber << termcolor::reset << " " << getRaya('-', caseTextLength) << std::flush;
		auto beginc = std::chrono::high_resolution_clock::now();
		std::system("./main < ._cin.txt > ._tcout.txt");
		auto endc = std::chrono::high_resolution_clock::now();
		auto dur = endc - beginc;
		long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

		std::cout << endl << endl;

		if(compareFile("._cout.txt", "._tcout.txt")){
			if(ms > 1000){
				std::cout << termcolor::yellow << termcolor::reverse << "CORRECT TLE " << termcolor::reset << ms << "ms ";
				graph(ms);
				std::cout << termcolor::white << endl;
			} else {
				std::cout << termcolor::green << termcolor::reverse << "CORRECT" << termcolor::reset << " "  << ms << "ms ";
				graph(ms);
				std::cout << termcolor::white << endl;
			}
			std::cout << endl;
			results.push_back(ms);
		} else {
			std::cout << termcolor::red << termcolor::reverse << "INCORRECT" << termcolor::reset << endl;
			results.push_back(-1);
			std::cout << termcolor::green << "Input: " << termcolor::reset << endl;
			std::cout << exec("cat ._cin.txt") << endl;
			std::cout << termcolor::red << "Excepted:" << termcolor::reset << endl;
			std::cout << exec("cat ._cout.txt");
			std::cout << endl;
			std::cout << termcolor::cyan << "Got:" << termcolor::reset << endl;
			std::cout << exec("cat ._tcout.txt");
		}
		std::system("rm ._cin.txt");
		std::system("rm ._cout.txt");
		std::system("rm ._tcout.txt");

		casenumber++;
	}
	
	test.close();

	std::cout << termcolor::white << termcolor::on_blue << getRaya('-', 0) << termcolor::reset << endl;

	// Hacer un resumen de los casos
	int total = std::accumulate(results.begin(), results.end(), 0);
	std::cout << "Total time: ";
	colorize(total, casenumber);
	std::cout << "ms ";
	graph(total, casenumber);
	std::cout << endl;
	if(std::find(results.begin(), results.end(), -1) != results.end()){
		std::cout << termcolor::white << termcolor::on_red << "TEST FAILED" << termcolor::reset << endl;
	} else if(total >= 250 * casenumber){
		std::cout << termcolor::white << termcolor::on_yellow << "CORRECT BUT SLOW MAYBE" << termcolor::reset << endl;
	} else {
		std::cout << termcolor::white << termcolor::on_green << "PERFECT" << termcolor::reset << endl;
	}
}

bool compareFile(std::string a, std::string b){
	if(exec("diff -q -w ._cout.txt ._tcout.txt").size() > 10){
		return false;
	} else return true;
}

std::string exec(std::string cmd) {
	std::string data;
	std::FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream))
		if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
		pclose(stream);
	}
	return data;
}



void graph(long int x, int tests){
	while(x > 0){
		if(x <= 250 * tests){
			std::cout << termcolor::on_green << " ";
			x -= 20 * tests;
		} else if (x <= 400 * tests){
			std::cout << termcolor::on_yellow << " ";
			x -= 30 * tests;
		} else {
			std::cout << termcolor::on_red << " ";
			x -= 50 * tests;
		}
	}
}

void graph(long int x){
	while(x > 0){
		if(x <= 250){
			std::cout << termcolor::on_green << " ";
			x -= 50;
		} else if (x <= 1000){
			std::cout << termcolor::on_yellow << " ";
			x -= 70;
		} else {
			std::cout << termcolor::on_red << " ";
			x -= 100;
		}
	}
}

void colorize(long int x, int tests){

	if(x <= 200 * tests){
		std::cout << termcolor::green << x;
		return;
	}
	if(x <= 300 * tests){
		std::cout << termcolor::yellow << x;
		return;
	}
	std::cout << termcolor::red << x;
	return;
}

void header(){
	std::cout << termcolor::reverse << getRaya('#', 0) << termcolor::reset << endl;
}

int main(){
	std::system("clear");
	header();
	std::cout << termcolor::cyan << termcolor::bold << print("xXxXxXx AutoComp xXxXxXx") << termcolor::white << endl;
	std::cout << termcolor::yellow << termcolor::blue << print("A Competitive Programming auto compiler kit") << endl;
	std::cout << termcolor::yellow << print("Aran Roig, (c) 2020") << termcolor::reset << endl;
	header();
	std::cout << endl;
	if(checkCompilation()) return 0;
	
	// Generar
	generateMainCpp();

	// Copiar
	copyMainCpp();
	
	// Ejecutar
	testProgram();
	
	std::cout << endl << termcolor::reverse << "End of working!" << termcolor::reset << endl << std::flush;
std::this_thread::sleep_for(std::chrono::milliseconds(750));	
	std::system("clear");
}

void generateMainCpp(){
	// Muy facil, haz un archivo que se llame out.cpp, que sea la combinación de header.cpp y main.cpp
}

bool checkCompilation(){
	std::cout << termcolor::green <<  "> " << termcolor::yellow << "Checking if your program needs to be compiled..." << endl;
	if(!std::experimental::filesystem::exists(".mainold.cpp")){
		std::cout << termcolor::green << "> " << termcolor::white << "Program needs to be compiled. " << endl << termcolor::reverse << "Compiling..." << termcolor::reset << endl;
		if(compile()) return true;
		return false;
	} else {
		// Comparar
		if(!compareFile("out.cpp", ".mainold.cpp")){
			std::cout << termcolor::green << "> " << termcolor::white << "Program needs to be compiled. " << endl << endl << termcolor::reverse << "Compiling..." << termcolor::reset << endl << endl;
			if(compile()) return true;
			return false;
	
		}
	}
	return false;
}

void copyMainCpp(){
	std::ifstream copy("out.cpp", std::ios::binary);
    std::ofstream dest(".mainold.cpp", std::ios::binary);
    dest << copy.rdbuf();
}

bool compile(){
	// Check first if file exists
	if(!std::experimental::filesystem::exists("compile.txt")){
		std::cout << termcolor::green << "> " << termcolor::white << "Creating new compile defaults..." << termcolor::white << endl;
		std::system("touch compile.txt");
		std::ofstream compile("compile.txt", std::ios::binary);
		compile << "g++ out.cpp -Wall -Wextra -O2 -std=c++17 -DLOCAL -o run";
		compile.close();
		std::cout << termcolor::green << "> " << termcolor::white << "Compile defaults " << termcolor::reverse << "saved" << termcolor::reset << endl;
		std::cout << termcolor::cyan << termcolor::reverse << "INFO:" << termcolor::reset << " compile defaults are the file where you put your commands to compile your code. This file is saved in " << termcolor::reverse << "compile.txt" << termcolor::reset << " and the default settings are " << termcolor::reverse << "g++ out.cpp -Wall -Wextra -02 -std=c++17 -DLOCAL -o main" << termcolor::reset << endl;
	}

	std::ifstream compilerLines("compile.txt");
	if(compilerLines.is_open()){
		std::string line, output;
		bool posibleErrors = false;

		while(std::getline(compilerLines, line)){
			output = exec(line.c_str());
			if(output != ""){
				std::cout << termcolor::red << termcolor::reverse << "Build resulted with an error or warning!" << termcolor::white << endl;
				std::cout << endl << output << endl;
			       	posibleErrors = true;
			}
		}

		compilerLines.close();
		if(posibleErrors){
			std::cout << termcolor::cyan << termcolor::reverse << "INFO:" << termcolor::reset << " if the error was caused by a " << termcolor::reverse << "warning" << termcolor::reset << ", you can remove the default parameters " << termcolor::reverse << "-Wall -Wextra" << termcolor::reset << " in the " << termcolor::reverse << "compile.txt" << termcolor::reset << " file." << endl << endl; 
			std::cout << termcolor::red << termcolor::reverse << "Error compilating out.cpp" << termcolor::reset << endl;
			std::cout << endl;
			header();
			std::cout << endl << termcolor::reverse << "Press enter to exit" << termcolor::reset << endl;
			std::cin.ignore();
			std::system("clear");
			return true;
		}
		return false;
	} else {
		std::cout << termcolor::red << termcolor::reverse << "Unable to open compiler file!" << termcolor::reset << endl;
		return true;
	}
}


void testProgram(){
	std::cout << termcolor::green << "> " << termcolor::white << "Running your program..." << termcolor::white << endl << endl;
	std::cout << termcolor::white << termcolor::on_blue << getRaya('-', 0) << endl << "PROGRAM EXECUTION:" << endl << termcolor::reset << std::flush;
	std::system("./run");
	std::cout << termcolor::on_blue << getRaya('-', 0) << termcolor::reset << endl << endl;
	std::cout << termcolor::green << "> " << termcolor::reset << "Program execution terminated." << endl << endl;
	std::cout << termcolor::green << "> " << termcolor::reset << termcolor::reverse << "Do you want to execute public cases?" << termcolor::reset << " ('y' = Yes)" << termcolor::white << endl;
	char c;
	std::cin >> c;
	if(c == 'y' || c == 'Y'){
		// Hacer tests publicos
		doPublicTests();
	}
}

void doPublicTests(){
	std::cout << termcolor::green << "> " << termcolor::white << " Executing public cases..." << endl << endl;
	
	// Introducir aqui caex
	testProgramYeet();
	std::cout << termcolor::reverse << endl << "Press a key to continue" << termcolor::reset;
	std::cin.ignore();
	std::cin.ignore();
}
