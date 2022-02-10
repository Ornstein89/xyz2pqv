#include <iostream>
#include <map>
#include <string>
#include <fstream>

std::map<std::string, std::string> args2map(int argc, char** argv)
{
    std::map<std::string, std::string> result;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            std::string key = argv[i];
            std::string value = "";
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                value = std::string(argv[i + 1]);
                i++;
            }

            result[key] = value;
        }
    }
    return result;
}

void print_manual()
{
	std::cout << "MANUAL" << std::endl;
	std::cout << "\tEXAMPLE: test -t 1000 -s gpx.csv -o out.csv" << std::endl;
    std::system("pause");
}

int main(int argc, char** argv)
{
    int result = 0;
    double timedelta = 0;
    std::string input_file;
    std::string output_file;
    std::ifstream ifs;
    std::ofstream ofs;


    if (argc != 7) {
        print_manual();
        return -1;
    }
    
    auto args_map = args2map(argc, argv);

    try {
        input_file = args_map["-s"];
        output_file = args_map["-o"];
        timedelta = std::stod(args_map["-t"]);
    }
    catch (...) {
        std::cout << "ERROR: some parameter is missing "
            << "or no \"-t\" value is not valid floating point number"
            << std::endl << std::endl;
        print_manual();
        return -1;
    }
        

    ifs.open(input_file, std::ios::in);
    if(!ifs.is_open())
    {
        std::cout << "ERROR: can't open file \"-s "
            << input_file << "\" in input mode"
            << std::endl << std::endl;
        print_manual();
        return -1;
    }

    //TODO обработать, если файл output_file существует
    ofs.open(output_file, std::ios::out | std::ios::trunc);
    if (!ofs.is_open())
    {
        std::cout << "ERROR: can't open file \"-o "
            << output_file << "\" in input mode"
            << std::endl << std::endl;
        print_manual();
        return -1;
    }

    //TODO

    ofs.close();
    ifs.close();
	return result;
}