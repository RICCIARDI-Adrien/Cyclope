/** @file ArtificialIntelligenceProgram.cpp
 * See ArtificialIntelligenceProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgram.hpp>
#include <cstdio>
#include <Light.hpp>
#include <Log.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <Network.hpp>
#include <unistd.h>

namespace ArtificialIntelligenceProgram
{
	void followTennisBall()
	{
		// Grab camera stream
		cv::VideoCapture videoCapture(0);
		if (!videoCapture.isOpened())
		{
			LOG(LOG_ERR, "Failed to open camera stream.\n");
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
		
		// TEST
		// Wait some time for the camera to stabilize
		usleep(3000000);
		
		cv::Mat matCameraFrame, matHsvFrame, matBinaryMask;
		cv::Moments moments;
		cv::Point pointBallCenter;
		int i = 0;
		char stringFileName[128];
		while (Network::isProgramRunning())
		{
			// Get next frame
			if (!videoCapture.read(matCameraFrame))
			{
				LOG(LOG_INFO, "Frame was missed.\n");
				continue;
			}
			if (matCameraFrame.empty())
			{
				LOG(LOG_ERR, "Captured frame is empty.\n");
				continue;
			}
			
			// Convert it to HSV color space to more easily track a specific color
			cv::cvtColor(matCameraFrame, matHsvFrame, cv::COLOR_BGR2HSV);
			
			// Isolate tennis ball color in a binary mask (ball color pixels will be white and everything else will be black)
			cv::inRange(matHsvFrame, cv::Scalar(25, 50, 50), cv::Scalar(45, 255, 255), matBinaryMask); // Ball color hue is about 70° (which stands for 35 in OpenCV), use a +10/-10 range
			
			// Detect ball center
			moments = cv::moments(matBinaryMask, true);
			pointBallCenter.x = moments.m10 / moments.m00;
			pointBallCenter.y = moments.m01 / moments.m00;
			
			// TEST
			if ((pointBallCenter.x > 0) && (pointBallCenter.y > 0))
			{
				Light::setEnabled(true);
				cv::circle(matCameraFrame, pointBallCenter, 5, cv::Scalar(255, 0, 0), -1);
				sprintf(stringFileName, "/media/data/test/test_raw%d.jpg", i);
				imwrite(stringFileName, matCameraFrame);
				sprintf(stringFileName, "/media/data/test/test_bin%d.jpg", i);
				imwrite(stringFileName, matBinaryMask);
				i++;
			}
			else Light::setEnabled(false);
			
			// TODO
		}
		
		// TEST
		Light::setEnabled(false);
	}
}
