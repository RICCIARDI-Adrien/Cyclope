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
#include <unistd.h>

namespace ArtificialIntelligenceProgram
{
	void followObject()
	{
		// Grab camera stream
		cv::VideoCapture videoCapture(0);
		if (!videoCapture.isOpened())
		{
			LOG(LOG_ERR, "Failed to open camera stream.");
			return;
		}
		
		// TEST
		// Wait some time for the camera to stabilize
		usleep(3000000);
		cv::Mat mat;
		if (!videoCapture.read(mat))
		{
			LOG(LOG_ERR, "missed frame");
			return;
		}
		if (mat.empty())
		{
			LOG(LOG_ERR, "empty frame");
			return;
		}
		
		// TEST
		imwrite("/tmp/test.jpg", mat);
		return;
		
		while (1) // TODO use communication protocol method to ask for program exit
		{
			
		}
	}
}
