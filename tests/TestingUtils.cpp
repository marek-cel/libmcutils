#include <TestingUtils.h>

#ifdef TEST_USING_ARMADILLO
arma::mat SetArmaMatFromArray(double* array, int rows, int cols)
{
    arma::mat m = arma::mat(array, rows, cols, false).t();
    return m;
}
#endif // TEST_USING_ARMADILLO
