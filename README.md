# algs
Generic C++ implementations of useful data structures and algorithms.

Inspired by the books:

*Algorithms, 4th Edition* by R. Sedgewick and K. Wayne (2011)

*Algorithms in C++, Third Edition, Parts 1–4: Fundamentals, Data Structures, Sorting, Searching* by R. Sedgewick and C. J. Van Wyk (1998)

# motivation
Both books are excellent. This project aims to bring together the best elements of both:

The first book has been modernised very recently (see https://algs4.cs.princeton.edu/faq/). However, it is written in Java.

The second book is written in C++, but in a very old-fashioned, C-like style.

Here we attempt to provide implementations of the algorithms in both books, while also using modern C++ features such as concepts, STL containers, smart pointers, etc. Implementations are standalone and header-only where possible, so that they can be drag-and-dropped into another project if need be. The algorithms are also extensively unit tested.

# compilation
    mkdir build
    cd build/
    cmake ../src
    make

You may need to pass the additional arguments -DCMAKE_BUILD_TYPE=<...> and/or -DCMAKE_CXX_COMPILER=<...> to cmake depending on your cmake and compiler versions.
Also works with the `ninja` buildsystem. Other buildsystems have not been tested.

# testing
    cd build/
    make
    ctest
