#include <opencv2/opencv.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "find_circle/Num.h"



using namespace cv;
using namespace std;
using namespace ros;

int main(int ac, char **av)
{

	ros::init(ac, av, "circle_find");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<find_circle::Num>("chatter", 1000);
	ros::Rate loop_rate(10);

	
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		printf("Can't open the camera \n");
		return -1;
	}

	Mat img_org;
	Mat img;
	Mat img_houghC;

	while(ros::ok())
	{

		find_circle::Num msg;
		// std::stringstream ss;

		cap>>img_org;

		cvtColor(img_org, img, COLOR_BGR2GRAY);

		Mat img_houghC;
		img.copyTo(img_houghC);

		vector<Vec3f> circles;
		HoughCircles(img_houghC, circles, HOUGH_GRADIENT, 1, 100, 100, 80, 0, 0);

		for (size_t i = 0; i < circles.size(); i++)
		{
			Vec3i c = circles[i];
			Point center(c[0], c[1]);
			int radius = c[2];

			
			// ss<< "x=" <<c[0];
			// num.x = ss.str();
			msg.id=i;
			msg.x=c[0];
			msg.y=c[1];

			cout<<"Id: "<<msg.id;
			cout<<" x : "<<msg.x;
			cout<<" y : "<<msg.y<<endl<<endl;

			chatter_pub.publish(msg);

			
			circle(img_houghC, center, radius, Scalar(0, 255, 0), 2);
			circle(img_houghC, center, 2, Scalar(0, 0, 255), 3);
		}


		

		
		
		loop_rate.sleep();

		imshow("img_houghC", img_houghC);
		if(waitKey(1)==3)
			break;
	}
	return 0;
}