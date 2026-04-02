#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

std::map<std::string, std::string> vartypes;
std::string kernel = "win32";
std::map<std::string, std::string> argd;

std::map<std::string, std::string> argp(int argc, char* argv[]) {
	std::vector<std::string> args = {};
	for (int i=1; i<argc; i++) {
		args.push_back(argv[i]);
	}
	
	std::string arg = "--file";
	std::map<std::string, std::string> out = { {"--kernel", "win32"} };
	for (int i=0; i<argc-1; i++) {
		if (args[i].starts_with("-")) {
			if (args[i].starts_with("--")) {
				arg = args[i];
			} else {
				if (args[i] == "-I") {
					arg = "--file";
				} else if (args[i] == "-O") {
					arg = "--output";
				} else if (args[i] == "-S") {
					arg = "--stdlib";
				} else {
					arg = args[i];
				}
			}
		} else {
			out[arg].append(args[i]);
		}
	}
	return out;
}

std::string read(std::string name) {
	std::ifstream f(name);
	std::string out;
	if (!f.is_open()) {
		std::cerr << "Error: File cannot be opened" << std::endl;
	} else {
		std::string l;
		while (std::getline(f, l)) {
			out.append(l);
			out.append("\n");
		}
	}
	f.close();
	return out;
}

std::string istdlib(std::string lib, std::string stdlib, std::string ker="win32") {
	std::string loc = stdlib;
	loc.append("/");
	loc.append(ker);
	loc.append("/");
	loc.append(lib);
	std::string out = read(loc);
	return out;
}

std::map<std::string, std::string> mac = {};

int main(int argc, char *argv[]) {
	argd = argp(argc, argv);
	std::string dat = istdlib("stdout.asm", argd["--stdlib"]);
	std::cout << dat;
	return 0;
}
