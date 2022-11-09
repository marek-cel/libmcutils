#ifndef LIBMCSIM_TESTS_XCOSBINFILEREADER_H_
#define LIBMCSIM_TESTS_XCOSBINFILEREADER_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The XcosBinFileReader class
 */
class XcosBinFileReader
{
public:

    /**
     * @brief Reads data from Xcos binary output file
     * @param filePath file path
     * @param vals vector of doubles to store data
     * @return true on success false on failure
     */
    static bool readData( const char *filePath, std::vector<double> *vals );
};

////////////////////////////////////////////////////////////////////////////////

#endif // LIBMCSIM_TESTS_XCOSBINFILEREADER_H_
