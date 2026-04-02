#include <iostream>
#include <vector>
#include <string>
#include <map>

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
			if (args[i].starts_with("--") {
				arg = args[i];
			} else {
				switch(args[i]) {
					case "-I":
						arg = "--file";
						break;
					case "-O":
						arg = "--output";
						break;
					default:
						arg = args[i];
				}
			}
		} else {
			out[arg].append(args[i]);
		}
	}
	return out;
}

int main(int argc, char *argv[]) {
	argd = argp(argc, argv);
	std::cout << argd["--file"];
}
