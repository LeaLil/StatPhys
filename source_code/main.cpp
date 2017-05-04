#include <MDSimulation.h>
#include <iostream>

/*!
 * main function.
 * The program expects one argument for the input file (parameters), an one optional argument for
 * the  file with the initial coordinates.
 */

int main(int argc, char* argv[]) {
    switch (argc) {
        case 2: break;
        case 3: break;
        default:
        std::cerr << "Usage: mdatom input_file [coordinate_file] > output \n";
            return 1;
    }

    std::string parameterFile = argv[1];
    std::string coordinatesFile; // NB: might be empty
    if (argc > 2)
        coordinatesFile = argv[2];

    MDSimulation md(std::cout);
    try {
        md.performSimulation(parameterFile, coordinatesFile);
    }
    catch (std::exception& e) {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}
