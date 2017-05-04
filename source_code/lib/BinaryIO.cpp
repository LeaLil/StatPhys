#include "BinaryIO.h"

void BinaryIO::read(std::istream &in, std::vector<double> &array) {
    size_t length = array.size();
    in.read(reinterpret_cast<char*>(array.data()), length * sizeof(double));
}

void BinaryIO::write(std::ostream &out, const std::vector<double> &array) {
    size_t length = array.size();
    out.write(reinterpret_cast<const char*>(array.data()), length * sizeof(double));
}
