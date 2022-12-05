#include <exception>

using namespace std;

class file_error : public exception {
    virtual const char* what() const throw()
    {
        return "Cannot read file";
    }
};

class wrong_matrix_error : public exception {
    virtual const char* what() const throw()
    {
        return "Wrong matrix size";
    }
};

class out_of_index_error : public exception {
    virtual const char* what() const throw()
    {
        return "Wrong matrix index";
    }
};
