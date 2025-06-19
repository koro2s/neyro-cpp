#include "emotion_detector.h"
#include "utils.h"

const std::vector<std::string> EmotionDetector::emotionLabels = {
    "Neutral", "Happiness", "Surprise", "Sadness",
    "Anger", "Disgust", "Fear", "Contempt"
};

void EmotionDetector::loadModel(const std::string& modelFileName)
{
    net = cv::dnn::readNetFromONNX(modelFileName);
}

cv::Mat EmotionDetector::preprocessImage(const cv::Mat& image)
{
    cv::Mat processed;
    image.convertTo(processed, CV_32F, 1.0 / 255.0);
    cv::resize(processed, processed, cv::Size(64, 64));
    return cv::dnn::blobFromImage(processed);
}

std::pair<std::string, float> EmotionDetector::detectFromImage(const std::string& imagePath)
{
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        throw std::runtime_error("Failed to load image");
    }

    cv::Mat blob = preprocessImage(image);
    net.setInput(blob);
    cv::Mat result = net.forward();
    cv::Mat probs = softmax(result);

    cv::Point classIdPoint;
    double confidence;
    cv::minMaxLoc(probs, 0, &confidence, 0, &classIdPoint);

    return {emotionLabels[classIdPoint.x], static_cast<float>(confidence)};
}