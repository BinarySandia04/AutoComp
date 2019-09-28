#include <bits/stdc++.h>
#include <experimental/filesystem>
#include "termcolor.hpp"
#include <stdio.h>
#include <stdlib.h>

#define endl '\n'

// Variable definitions
bool compile();
void copyMainCpp();
bool checkCompilation();
bool compareFile(std::string fa, std::string fb);
void testProgram();
void doPublicTests();

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

int main(){
	std::system("clear");
	std::cout << termcolor::blue << "---------------------------------------------------------------------------	" << termcolor::white << endl;
	std::cout << termcolor::magenta << "Auto CC for competitive programming by Aran Roig (c) 2019" << termcolor::white << endl;
	if(checkCompilation()) return 0;
	// Copiar
	copyMainCpp();
	// Ejecutar
	testProgram();
}

bool checkCompilation(){
	std::cout << "Checking if your program needs to be compiled..." << endl;
	if(!std::experimental::filesystem::exists(".mainold.cpp")){
		std::cout << termcolor::magenta << "Program needs to be compiled. Compiling..." << termcolor::white << endl;
		if(compile()) return true;
		return false;
	} else {
		// Comparar
		if(!compareFile("main.cpp", ".mainold.cpp")){
			std::cout << termcolor::magenta << "Program needs to be compiled. Compiling..." << termcolor::white << endl;
			if(compile()) return true;
			return false;
		}
	}
	return false;
}

void copyMainCpp(){
	std::ifstream copy("main.cpp", std::ios::binary);
    std::ofstream dest(".mainold.cpp", std::ios::binary);
    dest << copy.rdbuf();
}

bool compile(){
	// Check first if file exists
	if(!std::experimental::filesystem::exists("compile.txt")){
		std::cout << termcolor::yellow << "Creating new compile defaults..." << termcolor::white << endl;
		std::system("touch compile.txt");
		std::ofstream compile("compile.txt", std::ios::binary);
		compile << "g++ main.cpp -Wall -Wextra -O2 -std=c++17 -DLOCAL -o main";
		compile.close();
	}
	std::cout << termcolor::cyan << "Compiling..." << termcolor::white << endl;

	std::ifstream compilerLines("compile.txt");
	if(compilerLines.is_open()){
		std::string line, output;
		bool posibleErrors = false;
		while(std::getline(compilerLines, line)){
			output = exec(line.c_str());
			if(output != "") posibleErrors = true;
			std::cout << output << endl;
		}
		compilerLines.close();
		if(posibleErrors){
			std::cout << termcolor::red << "Maybe there are errors or warnings on the compilation. Continue anyways? (c to cancel)" << termcolor::white << endl;
			char c;
			std::cin >> c;
			if(c == 'c') return true;
		}
		return false;
	} else {
		std::cout << termcolor::red << "Unable to open compiler file!" << termcolor::white << endl;
		return true;
	}
}

bool compareFile(std::string fa, std::string fb){
	std::fstream main, oldmain;

	std::ifstream maincpp(fa, std::ios::binary);
	auto begin = maincpp.tellg();
	maincpp.seekg (0, std::ios::end);
	auto end = maincpp.tellg();
	const auto fsizemain = (end-begin);
	maincpp.close();

	std::ifstream mainoldcpp(fb, std::ios::binary);
	begin = mainoldcpp.tellg();
	mainoldcpp.seekg (0, std::ios::end);
	end = mainoldcpp.tellg();
	auto fsizemainold = (end-begin);
	mainoldcpp.close();

	if(fsizemain != fsizemainold){
		return false;
	} else {
		std::string a, b;
		std::fstream f1, f2;
		f1.open(fa);
		f2.open(fb);
		bool equal = true;
		while(std::getline(f1, a)){
			std::getline(f2, b);
			if(a != b){
				equal = false;
				break;
			}
		}
		f1.close();
		f2.close();
		if(equal) return true;
		else return false;
	}
}

void testProgram(){
	std::cout << termcolor::green << "Running your program..." << termcolor::white << endl;
	std::cout << termcolor::blue << "---------------------------------------------------------------------------" << termcolor::white << endl;
	std::system("./main");
	std::cout << termcolor::blue << "---------------------------------------------------------------------------" << termcolor::white << endl;
	std::cout << "Program execution terminated." << endl;
	std::cout << termcolor::magenta << "Do you want to execute public cases? ('y' = Yes)" << termcolor::white << endl;
	char c;
	std::cin >> c;
	if(c == 'y' || c == 'Y'){
		// Hacer tests publicos
		doPublicTests();
	}
}

void doPublicTests(){
	std::cout << termcolor::blue << "Executing public cases..." << termcolor::white << endl;

	std::system("./caex < cases.txt");
}