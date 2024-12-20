/** @file ArtificialIntelligenceProgramFollowTennisBall.cpp
 * See ArtificialIntelligenceProgramFollowTennisBall.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgramFollowTennisBall.hpp>
#include <cstdio>
#include <Lidar.hpp>
#include <Light.hpp>
#include <Log.hpp>
#include <Motor.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <unistd.h>

void ArtificialIntelligenceProgramFollowTennisBall::run()
{
	// Grab camera stream
	cv::VideoCapture videoCapture(0);
	if (!videoCapture.isOpened())
	{
		LOG(LOG_ERR, "Failed to open the camera stream.");
		return;
	}

	// Set frame size to HD (not working for now)
	/*// Frame width
	if (!videoCapture.set(cv::CAP_PROP_FRAME_WIDTH, 1280))
	{
		LOG(LOG_ERR, "Failed to set stream frame width.");
		return;
	}
	// Frame height
	if (!videoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, 720))
	{
		LOG(LOG_ERR, "Failed to set stream frame width.");
		return;
	}*/
	// Wait some time for the camera to stabilize
	usleep(3000000);

	cv::Mat matCameraFrame, matHsvFrame, matBinaryMask, matTemporary;
	cv::Point pointBallCenter;
	cv::Rect rectangleBiggestContour, rectangle;
	unsigned int i, count/*, j = 0*/;
	int area, ballHorizontalPositionPercentage;
	std::vector<std::vector<cv::Point>> contours;
	while (!_isExitRequested)
	{
		// Get next frame
		if (!videoCapture.read(matCameraFrame))
		{
			LOG(LOG_INFO, "Frame was missed.");
			continue;
		}
		if (matCameraFrame.empty())
		{
			LOG(LOG_ERR, "Captured frame is empty.");
			continue;
		}

		// Convert it to HSV color space to more easily track a specific color
		cv::cvtColor(matCameraFrame, matHsvFrame, cv::COLOR_BGR2HSV);

		// Isolate tennis ball color in a binary mask (ball color pixels will be white and everything else will be black)
		cv::inRange(matHsvFrame, cv::Scalar(50, 50, 50), cv::Scalar(70, 255, 255), matBinaryMask); // TEST follow green plastic box cap for now as it works better // Ball color hue is about 70° (which stands for 35 in OpenCV), use a +10/-10 range

		// Retrieve all object contours
		cv::findContours(matBinaryMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		// Keep the biggest one, this should be the ball
		count = contours.size();
		rectangleBiggestContour.width = 0; // Make sure every found rectangle will be bigger at the beginning
		rectangleBiggestContour.height = 0;
		for (i = 0; i < count; i++)
		{
			// Retrieve next rectangle area
			rectangle = cv::boundingRect(contours[i]);
			area = rectangle.width * rectangle.height;

			// Discard rectangle if it is too small
			if (area < 1000) continue;

			// Is this rectangle area bigger than the biggest found one ?
			if (area > (rectangleBiggestContour.width * rectangleBiggestContour.height)) rectangleBiggestContour = rectangle;
		}

		// Make robot move only if detected object is big enough
		if (rectangleBiggestContour.width * rectangleBiggestContour.height > 1000)
		{
			// Compute ball center
			pointBallCenter.x = rectangleBiggestContour.x + (rectangleBiggestContour.width / 2);
			pointBallCenter.y = rectangleBiggestContour.y + (rectangleBiggestContour.height / 2);

			// Convert ball center X coordinate to a percentage telling where the ball is on the horizontal axis (0% when the ball is at the leftmost position, 100% when the ball is at the rightmost position)
			ballHorizontalPositionPercentage = (100 * pointBallCenter.x) / matCameraFrame.cols;
			if (ballHorizontalPositionPercentage < 0) ballHorizontalPositionPercentage = 0;
			else if (ballHorizontalPositionPercentage > 100) ballHorizontalPositionPercentage = 100;

			// Ball is located too far on the left, try to center it better
			if (ballHorizontalPositionPercentage <= 35) Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_LEFT);
			// Ball is located too far on the right, try to center it better
			else if (ballHorizontalPositionPercentage >= 65) Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_RIGHT);
			// Go straight if ball is quite centered
			else Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD);

			// Tell human that ball is detected
			Light::setEnabled(true);

			// TEST
			/*{
				char stringFileName[128];

				cv::circle(matCameraFrame, pointBallCenter, 5, cv::Scalar(255, 0, 0), -1);
				cv::rectangle(matCameraFrame, rectangleBiggestContour, cv::Scalar(0, 0, 255));
				sprintf(stringFileName, "/media/data/test/test_raw%d.jpg", j);
				imwrite(stringFileName, matCameraFrame);
				sprintf(stringFileName, "/media/data/test/test_bin%d.jpg", j);
				imwrite(stringFileName, matBinaryMask);
				j++;
			}*/
		}
		else
		{
			Motor::setRobotMotion(Motor::ROBOT_MOTION_STOP);

			// Tell human that ball is no more detected
			Light::setEnabled(false);
		}
	}

	// Make sure light is turned off before leaving
	Light::setEnabled(false);
}
