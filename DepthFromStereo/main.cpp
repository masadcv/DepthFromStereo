#include "opencv2\opencv.hpp"

int main()
{
	cv::Mat img1, img2, g1, g2;
	cv::Mat disp, disp8;

	img1 = cv::imread("scene11.ppm");
	img2 = cv::imread("scene12.ppm");

	cv::imshow("ImageLeft", img1);
	cv::imshow("ImageRight", img2);
	cv::imwrite("ImageLeft.png", img1);
	cv::imwrite("ImageRight.png", img2);

	//wait until keypress from user
	cv::waitKey(0);
	cv::cvtColor(img1, g1, CV_BGR2GRAY);
	cv::cvtColor(img2, g2, CV_BGR2GRAY);

	// for now trying basic preset, but can be specific
	cv::StereoBM sbm(cv::StereoBM::BASIC_PRESET);
	//sbm.state->SADWindowSize = 9;
	//sbm.state->numberOfDisparities = 112;
	//sbm.state->preFilterSize = 5;
	//sbm.state->preFilterCap = 61;
	//sbm.state->minDisparity = -39;
	//sbm.state->textureThreshold = 507;
	//sbm.state->uniquenessRatio = 0;
	//sbm.state->speckleWindowSize = 0;
	//sbm.state->speckleRange = 8;
	//sbm.state->disp12MaxDiff = 1;

	sbm(g1, g2, disp);
	cv::normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

	cv::imshow("left", img1);
	cv::imshow("right", img2);
	cv::imshow("disp", disp8);

	cv::imwrite("disparity.png", disp8);
	// from http://stackoverflow.com/questions/23039961/getting-real-depth-from-disparity-map
	//you can use CVs stereo correspondence functions,
	//such as Stereo Block Matching or Semi Global Block Matching. 
	//This will give you a disparity map for the entire image which 
	//can be transformed to 3D points using the Q matrix (cv::reprojectImageTo3D).

	//TODO: we need to calculate Q Matrix using camera calibration
	//http://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html#void%20stereoRectify%28InputArray%20cameraMatrix1,%20InputArray%20distCoeffs1,%20InputArray%20cameraMatrix2,%20InputArray%20distCoeffs2,%20Size%20imageSize,%20InputArray%20R,%20InputArray%20T,%20OutputArray%20R1,%20OutputArray%20R2,%20OutputArray%20P1,%20OutputArray%20P2,%20OutputArray%20Q,%20int%20flags,%20double%20alpha,%20Size%20newImageSize,%20Rect*%20validPixROI1,%20Rect*%20validPixROI2%29

	// wait until keypress
	cv::waitKey(0);
}