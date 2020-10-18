/** @file ArtificialIntelligenceProgram.cpp
 * See ArtificialIntelligenceProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgram.hpp>
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
		
		cv::Mat matCameraFrame;
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
			
			// TODO
		}
		
		// TEST
		imwrite("/tmp/test.jpg", matCameraFrame);
	}
}
