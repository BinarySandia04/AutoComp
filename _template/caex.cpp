#include <bits/stdc++.h>
#include "termcolor.hpp"

#define endl '\n'

void tle();

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

void graph(long int x){
	while(x > 0){
		if(x <= 250){
			std::cout << termcolor::green << "-";
			x -= 50;
		} else if (x <= 1000){
			std::cout << termcolor::yellow << "-";
			x -= 70;
		} else {
			std::cout << termcolor::red << "-";
			x -= 100;
		}
	}
}

void graph(long int x, int tests){
	while(x > 0){
		if(x <= 250 * tests){
			std::cout << termcolor::green << "-";
			x -= 20 * tests;
		} else if (x <= 400 * tests){
			std::cout << termcolor::yellow << "-";
			x -= 30 * tests;
		} else {
			std::cout << termcolor::red << "-";
			x -= 50 * tests;
		}
	}
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

bool compareFile(std::string a, std::string b){
	if(exec("diff -q -w ._cout.txt ._tcout.txt").size() > 10){
		return false;
	} else return true;
}

std::string getline(){
	std::string line;
	std::getline(std::cin, line);
	std::cout << line << endl;
	return line;
}

int main(){
	int casenumber = 1;
	std::vector<int> results;
	std::string line;
	std::getline(std::cin, line);
	std::cout << termcolor::cyan << line << termcolor::white << endl;
	std::cout << termcolor::blue << "---------------------------------------------------------------------------	" << termcolor::white << endl;
	while(std::getline(std::cin, line)){
		std::string casecin = "";
		std::getline(std::cin, line);
		while(line.find("---------------------------") == std::string::npos){
			casecin += line + endl;
			std::getline(std::cin, line);
		}

		std::getline(std::cin, line);
		std::string caseout = "";
		while(line.find("---------------------------") == std::string::npos){
			caseout += line + endl;
			std::getline(std::cin, line);
		}

		std::ofstream filein, fileout;
		filein.open("._cin.txt");
		fileout.open("._cout.txt");
		filein << casecin;
		fileout << caseout;
		fileout.close();
		filein.close();

		std::cout << termcolor::white << casenumber << " " << termcolor::magenta << ".........." << std::flush;

		auto beginc = std::chrono::high_resolution_clock::now();
		std::system("./main < ._cin.txt > ._tcout.txt");
		auto endc = std::chrono::high_resolution_clock::now();
		auto dur = endc - beginc;
		long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

		std::cout << " ";

		if(compareFile("._cout.txt", "._tcout.txt")){
			if(ms > 1000){
				std::cout << termcolor::yellow << "CORRECT TLE " << termcolor::white << ms << "ms ";
				graph(ms);
				std::cout << termcolor::white << endl;
			} else {
				std::cout << termcolor::green << "CORRECT " << termcolor::white << ms << "ms ";
				graph(ms);
				std::cout << termcolor::white << endl;
			}
			results.push_back(ms);
		} else {
			std::cout << termcolor::red << "INCORRECT" << termcolor::white << endl;
			results.push_back(-1);
			std::cout << termcolor::magenta << "Excepted:" << termcolor::white << endl;
			std::cout << exec("cat ._cout.txt");
			std::cout << termcolor::magenta << "Got:" << termcolor::white << endl;
			std::cout << exec("cat ._tcout.txt");
		}
		std::system("rm ._cin.txt");
		std::system("rm ._cout.txt");
		std::system("rm ._tcout.txt");

		casenumber++;
	}
	std::cout << termcolor::blue << "---------------------------------------------------------------------------" << termcolor::white << endl;

	// Hacer un resumen de los casos
	int total = std::accumulate(results.begin(), results.end(), 0);
	std::cout << "Total time: ";
	colorize(total, casenumber);
	std::cout << "ms ";
	graph(total, casenumber);
	std::cout << endl;
	if(std::find(results.begin(), results.end(), -1) != results.end()){
		std::cout << termcolor::red << "TEST FAILED" << termcolor::white << endl;
	} else if(total >= 250 * casenumber){
		std::cout << termcolor::yellow << "CORRECT BUT SLOW" << termcolor::white << endl;
	} else {
		std::cout << termcolor::green << "PERFECT" << termcolor::white << endl;
	}
}

void tle(){
	sleep(2);
	std::cout << termcolor::red << "TLE" << termcolor::white << endl;
}