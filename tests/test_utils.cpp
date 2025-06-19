#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include "utils.h"
#include <fstream>

// ---------- Тестирование softmax ----------
TEST(SoftmaxTest, SimpleVector)
{
    // Вектор [1.0, 2.0, 3.0]
    cv::Mat logits = (cv::Mat_<float>(1, 3) << 1.0f, 2.0f, 3.0f);
    cv::Mat probs = softmax(logits);

    // Проверка, что сумма равна 1.0
    float sum = cv::sum(probs)[0];
    EXPECT_NEAR(sum, 1.0f, 1e-5f);

    // Проверка порядка значений: softmax(3.0) > softmax(2.0) > softmax(1.0)
    EXPECT_GT(probs.at<float>(0, 2), probs.at<float>(0, 1));
    EXPECT_GT(probs.at<float>(0, 1), probs.at<float>(0, 0));
}

TEST(SoftmaxTest, AllZeros)
{
    // Вектор [0.0, 0.0, 0.0]
    cv::Mat logits = cv::Mat::zeros(1, 3, CV_32F);
    cv::Mat probs = softmax(logits);

    // Все значения должны быть равны 1/3
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_NEAR(probs.at<float>(0, i), 1.0f / 3.0f, 1e-5f);
    }
}

// ---------- Тестирование fileExists ----------
TEST(FileExistsTest, ExistingFile)
{
    const std::string filename = "test_temp_file.txt";
    std::ofstream outfile(filename);
    outfile << "test" << std::endl;
    outfile.close();

    EXPECT_TRUE(fileExists(filename));

    std::remove(filename.c_str());
}

TEST(FileExistsTest, NonExistingFile)
{
    EXPECT_FALSE(fileExists("file_that_should_not_exist_123456.txt"));
}