#ifndef LIBMCUTILS_TESTS_TESTINGUTILS_H_
#define LIBMCUTILS_TESTS_TESTINGUTILS_H_

#ifdef TEST_USING_ARMADILLO
#   include <armadillo>
#endif // TEST_USING_ARMADILLO

#ifdef TEST_USING_ARMADILLO
arma::mat SetArmaMatFromArray(double* array, int rows, int cols);
#endif // TEST_USING_ARMADILLO

#endif // LIBMCUTILS_TESTS_TESTINGUTILS_H_
