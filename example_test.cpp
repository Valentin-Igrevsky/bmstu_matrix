#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include "bmstu_matriXXX.h"

TEST(Constructor, Default) {
    bmstu::matrix<int> my_matrix;
    ASSERT_EQ(my_matrix(0, 0), 0);
}

TEST(Constructor, Parameter) {
    bmstu::matrix<int> my_matrix(4, 5);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            ASSERT_EQ(my_matrix(i, j), 0);
        }
    }
}

TEST(Constructor, IList) {
    bmstu::matrix my_matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(my_matrix(i, j), i * 3 + j + 1);
        }
    }

    try{
        bmstu::matrix bad_matrix({1, 2, 3, 4, 5}, 2, 3);
    }
    catch (const std::out_of_range &err){
        ASSERT_EQ(err.what(), std::string("Current matrix pos wrong (2, 3) != 5"));
    }
}

TEST(Operator, LeftShift) {
    bmstu::matrix my_matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    std::stringstream ss;
    ss << my_matrix;
    ASSERT_STREQ(ss.str().c_str(), "1 2 3 \r\n4 5 6 \r\n");
}

TEST(Operator, Subscript) {
    const bmstu::matrix my_matrix_1({1, 2, 3, 4, 5, 6}, 2, 3);
    std::vector line_1_1 = my_matrix_1[1];
    std::vector correct({4, 5, 6});
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(line_1_1[i], correct[i]);
    }

    line_1_1[0] = 0;
    line_1_1[1] = 1;
    line_1_1[2] = 2;
    std::vector line_1_2 = my_matrix_1[1];
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(line_1_1[i], i);
        ASSERT_EQ(line_1_2[i], i + 4);
    }

    bmstu::matrix my_matrix_2({1, 2, 3, 4, 5, 6}, 2, 3);
    std::vector line_2_1 = my_matrix_2[1];
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(*line_2_1[i], correct[i]);
    }

    *line_2_1[0] = 0;
    *line_2_1[1] = 1;
    *line_2_1[2] = 2;
    std::vector line_2_2 = my_matrix_2[1];
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(*line_2_1[i], i);
        ASSERT_EQ(*line_2_2[i], i);
    }
}


TEST(Method, det) {
    bmstu::matrix good_matrix({1, 0, 2, 1, 3, 4, -1, 3, 2, 5, -3, 2, -4, 5, -7, 2, 3, 19, 5, 8, 5, -3, -5, -1, 4}, 5,
                              5);
    ASSERT_EQ(good_matrix.det(), -240);

    bmstu::matrix bad_matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    try{
        bad_matrix.det();
    }
    catch (const std::logic_error &err) {
        ASSERT_EQ(err.what(), std::string("Matrix have determinant if (rows == colimns)!"));
    }
}

TEST(Operator, Multiplication_1) {
    bmstu::matrix left_1({1, 3, 4, 4, 1, 2, 5, 8, 6}, 3, 3);
    bmstu::matrix right_1({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    bmstu::matrix res_1 = left_1 * right_1;
    bmstu::matrix correct_1({41, 49, 57, 22, 29, 36, 79, 98, 117}, 3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(res_1(i, j), correct_1(i, j));
        }
    }

    bmstu::matrix left_2({1, 3, 4, 1, 5, 8}, 3, 2);
    bmstu::matrix right_2({1, 2, 3, 1, 10, 4, 5, 6, 4, -5}, 2, 5);
    bmstu::matrix res_2 = left_2 * right_2;
    bmstu::matrix correct_2({13, 17, 21, 13, -5, 8, 13, 18, 8, 35, 37, 50, 63, 37, 10}, 3, 5);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            ASSERT_EQ(res_2(i, j), correct_2(i, j));
        }
    }

    try{
        left_1 * right_2;
    }
    catch (const std::logic_error &err) {
        ASSERT_EQ(err.what(), std::string("The left matrix must have as many columns at the right one has rows!"));
    }
}

TEST(Operator, Multiplication_2) {
    bmstu::matrix my_matrix({5, 6, 3, -7, 4, 0, 4, 1, -8}, 3, 3);
    bmstu::matrix res = my_matrix * 3;
    bmstu::matrix correct({15, 18, 9, -21, 12, 0, 12, 3, -24}, 3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(res(i, j), correct(i, j));
        }
    }
}

TEST(Operator, Concatenation) {
    bmstu::matrix left_1({1, 3, 4, 4, 1, 2, 5, 8, 6}, 3, 3);
    bmstu::matrix right_1({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    bmstu::matrix res_1 = left_1 + right_1;
    bmstu::matrix correct_1({2, 5, 7, 8, 6, 8, 12, 16, 15}, 3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(res_1(i, j), correct_1(i, j));
        }
    }

    bmstu::matrix left_2({1, 3, 4, 1, 5, 8}, 3, 2);
    bmstu::matrix right_2({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

    try{
        left_2 + right_2;
    }
    catch (const std::logic_error &err) {
        ASSERT_EQ(err.what(), std::string("Matries must have the same dimension!"));
    }
}

TEST(Operator, Subtraction) {
    bmstu::matrix left_1({1, 3, 4, 4, 1, 2, 5, 8, 6}, 3, 3);
    bmstu::matrix right_1({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    bmstu::matrix res_1 = left_1 - right_1;
    bmstu::matrix correct_1({0, 1, 1, 0, -4, -4, -2, 0, -3}, 3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(res_1(i, j), correct_1(i, j));
        }
    }

    bmstu::matrix left_2({1, 3, 4, 1, 5, 8}, 3, 2);
    bmstu::matrix right_2({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

    try{
        left_2 - right_2;
    }
    catch (const std::logic_error &err) {
        ASSERT_EQ(err.what(), std::string("Matries must have the same dimension!"));
    }

}

TEST(Method, get_minor_matrix) {
    bmstu::matrix my_matrix({1, 2, 3, 1, 10, 4, 5, 6, 4, -5, 4, 7}, 4, 3);
    bmstu::matrix minor = my_matrix.get_minor_matrix(1, 1);
    bmstu::matrix correct({1, 3, 5, 4, -5, 7}, 3, 2);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            ASSERT_EQ(minor(i, j), correct(i, j));
        }
    }

    try{
        my_matrix.get_minor_matrix(-1, 1);
    }
    catch (const std::out_of_range &err) {
        ASSERT_EQ(err.what(), std::string("Wrong number of rows or columns!"));
    }

    try{
        my_matrix.get_minor_matrix(0, -1);
    }
    catch (const std::out_of_range &err) {
        ASSERT_EQ(err.what(), std::string("Wrong number of rows or columns!"));
    }

    try{
        my_matrix.get_minor_matrix(4, 1);
    }
    catch (const std::out_of_range &err) {
        ASSERT_EQ(err.what(), std::string("Wrong number of rows or columns!"));
    }

    try{
        my_matrix.get_minor_matrix(0, 3);
    }
    catch (const std::out_of_range &err) {
        ASSERT_EQ(err.what(), std::string("Wrong number of rows or columns!"));
    }
}

TEST(Method, transpose) {
    bmstu::matrix my_matrix({1, 2, 3, 1, 10, 4, 5, 6, 4, -5, 4, 7}, 4, 3);
    my_matrix.transpose();
    bmstu::matrix correct({1, 1, 5, -5, 2, 10, 6, 4, 3, 4, 4, 7}, 3, 4);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            ASSERT_EQ(my_matrix(i, j), correct(i, j));
        }
    }
}

TEST(Method, adj) {
    bmstu::matrix my_matrix({2, 5, 7, 6, 3, 4, 5, -2, -3}, 3, 3);
    bmstu::matrix adj_matrix = my_matrix.adj();
    bmstu::matrix correct({-1, 1, -1, 38, -41, 34, -27, 29, -24}, 3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(adj_matrix(i, j), correct(i, j));
        }
    }

    bmstu::matrix bad_matrix({1, 2, 3, 1, 10, 4, 5, 6, 4, -5, 4, 7}, 4, 3);
    try{
        bad_matrix.adj();
    }
    catch (std::logic_error &err){
        ASSERT_EQ(err.what(), std::string("Matrix have adjugate matrix if (rows == columns)"));
    }
}

TEST(Method, reverse) {
    bmstu::matrix<double> my_matrix({2, 5, 7, 6, 3, 4, 5, -2, -3}, 3, 3);
    bmstu::matrix res = my_matrix.reverse();
    bmstu::matrix correct({1, -1, 1, -38, 41, -34, 27, -29, 24}, 3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(res(i, j), correct(i, j));
        }
    }

    bmstu::matrix E1 = res * my_matrix;
    bmstu::matrix E2 = my_matrix * res;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) {
                ASSERT_EQ(E1(i, j), 1);
                ASSERT_EQ(E2(i, j), 1);
            } else {
                ASSERT_EQ(E1(i, j), 0);
                ASSERT_EQ(E2(i, j), 0);
            }
        }
    }

    bmstu::matrix<double> bad_matrix_1({1, 1, 5, -5, 2, 10, 6, 4, 3, 4, 4, 7}, 3, 4);
    try{
        bad_matrix_1.reverse();
    }
    catch (const std::logic_error &err) {
        ASSERT_EQ(err.what(), std::string("The matrix must be square!"));
    }

    bmstu::matrix<double> bad_matrix_2({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    try{
        bad_matrix_2.reverse();
    }
    catch (const std::logic_error &err) {
        ASSERT_EQ(err.what(), std::string("The determinant of the matrix is 0. The reversed matrix does not exist!"));
    }
}
