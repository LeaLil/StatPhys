#ifndef BINARYIO_H
#define BINARYIO_H

#include <iostream>
#include <vector>

/*!
 * This class implements r/w operations of arrays in binary form.
 */
class BinaryIO {
  public:
    // read binary input stream as data of type double into an array
    //     in     - input stream
    //     array  - target array, that already has the correct size
    static void read(std::istream &in, std::vector<double> &array);

    // write contents of an array of data of type double to output stream as binary data.
    //     out    - output stream
    //     array  - target array
    static void write(std::ostream &out, const std::vector<double> &array);
};


#endif // BINARYIO_H