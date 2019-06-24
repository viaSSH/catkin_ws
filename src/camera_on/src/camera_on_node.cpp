#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <cv.hpp>
#include <iostream>

#include "std_msgs/Int16.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <termio.h>
#include <unistd.h>

#include <time.h>
//#include <gsl/gsl_fit.h>

//float trap_bottom_width =0; //0.85;  // width of bottom edge of trapezoid, expressed as percentage of image width
//float trap_top_width =0; //0.07;     // ditto for top edge of trapezoid
//float trap_height =0; //0.4;         // height of the trapezoid expressed as percentage of image height
bool draw_right = true;
bool draw_left = true;

#define PI 3.1415926
using namespace std;
using namespace cv;

int const Xcenter = 160;//X center
int const Yvalue = 100;//Y center
int const range = 40;
int ldistance=0, rdistance=0;
//-----------------
Mat roi;
float left_slope_mem=1, right_slope_mem=1, right_b_mem=0, left_b_mem=0;
float left_x0,left_x120,right_x0,right_x120;
void find_lines(vector<cv::Vec4i> &lines,
  	        float *left_m, float *left_b, float *right_m, float *right_b)
{
//y = m*x + b--> x = (y - b) / m

    int Lvalue=130;
    int Lpixel=0, Rpixel=0;
    int Ldistance=275, Rdistance=320, pastL;

    draw_left = true;
    draw_right = true;

    //cout<<"lines:"<<lines.size()<<endl;

    int width = 320;
    int height = 120;
    float slope_threshold = 0.5;
    vector<float> slopes;
    vector<Vec4i> new_lines;


    for (int i = 0; i < lines.size(); i++)
    {
      Vec4i line = lines[i];
      int x1 = line[0];
      int y1 = line[1];
      int x2 = line[2];
      int y2 = line[3];

      float slope;
      //Calculate slope
      if (x2 - x1 == 0) //corner case, avoiding division by 0
        slope = 999.0; //practically infinite slope
      else
        slope = (y2 - y1) / (float)(x2 - x1);

      //Filter lines based on slope
      if (abs(slope) > slope_threshold) {
        slopes.push_back(slope);
        new_lines.push_back(line);
      }
    }


    // Split lines into right_lines and left_lines, representing the right and left lane lines
    // Right / left lane lines must have positive / negative slope, and be on the right / left half of the image
   vector<Vec4i> right_lines;
   vector<Vec4i> left_lines;

   for (int i = 0; i < new_lines.size(); i++)
   {

		Vec4i line = new_lines[i];
		float slope = slopes[i];

		int x1 = line[0];
		int y1 = line[1];
		int x2 = line[2];
		int y2 = line[3];


		float cx = 160; //x coordinate of center of image

		if (slope > 0 && x1 > cx && x2 > cx)//
			right_lines.push_back(line);
		else if (slope < 0 && x1 < cx && x2 < cx)//slope < 0 && x1 < cx && x2 < cx
			left_lines.push_back(line);
   }
	float right_avg_x=0, right_avg_y=0, left_avg_x=0, left_avg_y=0,left_avg_slope=0,right_avg_slope=0;
	for(int i =0; i < left_lines.size(); i++)//calculate right avg of x and y and slope
    {
        Scalar color;
		color = Scalar(rand()%256, rand()%256, rand()%256);
        //line(roi, Point(left_lines[i][0],left_lines[i][1]), Point(left_lines[i][2],left_lines[i][3]), color, 3);
 		left_avg_x+= left_lines[i][0];
		left_avg_x+= left_lines[i][2];
		left_avg_y+= left_lines[i][1];
		left_avg_y+= left_lines[i][3];
		left_avg_slope += (left_lines[i][3] - left_lines[i][1]) / (float)(left_lines[i][2] - left_lines[i][0]);
	}
	left_avg_x=left_avg_x/(left_lines.size()*2);
	left_avg_y=left_avg_y/(left_lines.size()*2);
	left_avg_slope=left_avg_slope/left_lines.size();

	for(int i =0; i < right_lines.size(); i++)//calculate right avg of x and y and slope
    {
        Scalar color;
		color = Scalar(rand()%256, rand()%256, rand()%256);
        //line(roi, Point(right_lines[i][0],right_lines[i][1]), Point(right_lines[i][2],right_lines[i][3]), color, 3);
		right_avg_x+= right_lines[i][0];
		right_avg_x+= right_lines[i][2];
		right_avg_y+= right_lines[i][1];
		right_avg_y+= right_lines[i][3];
		right_avg_slope += (right_lines[i][3] - right_lines[i][1]) / (float)(right_lines[i][2] - right_lines[i][0]);
	}
	right_avg_x=right_avg_x/(right_lines.size()*2);
	right_avg_y=right_avg_y/(right_lines.size()*2);
	right_avg_slope=right_avg_slope/right_lines.size();

	//b=y-ax //find linear equation
	float b_left=left_avg_y-left_avg_slope*left_avg_x;
	float b_right=right_avg_y-right_avg_slope*right_avg_x;
	//0 ,120
	cout<<"left_lines:"<<left_lines.size()<<"//";
	cout<<"right_lines:"<<right_lines.size()<<endl;

	if(left_lines.size()!=0){
		left_x0=(-b_left)/left_avg_slope;
		left_x120=(120-b_left)/left_avg_slope;
		left_slope_mem=left_avg_slope;
		left_b_mem=b_left;
	}
	if(right_lines.size()!=0){
		right_x0=(-b_right)/right_avg_slope;
		right_x120=(120-b_right)/right_avg_slope;
		right_slope_mem=right_avg_slope;
		right_b_mem=b_right;
	}

	ldistance = 160-((Yvalue - left_b_mem) / left_slope_mem);
	rdistance = ((Yvalue - right_b_mem) / right_slope_mem)-160;

	line(roi, Point(left_x0, 0), Point(left_x120, 120), Scalar(255,100,100), 3);
	line(roi, Point(right_x0, 0), Point(right_x120, 120), Scalar(100,255,100), 3);


}


int img_process(Mat &frame, std_msgs::Int16 &cam_msg)
{
    Mat grayframe, line_frame;//, roi;

    cvtColor(frame, grayframe, COLOR_BGR2GRAY);
    Rect rect_roi(0,120,320,120);
    roi = frame(rect_roi);

    cvtColor(roi,grayframe,COLOR_BGR2GRAY) ;
    GaussianBlur(grayframe,grayframe,Size(5,5),1.5);
    Canny(grayframe,line_frame,70,150,3); //min_val, max val , filter size

    vector<cv::Vec4i> lines;

    cv::HoughLinesP(line_frame,lines,1,PI/180,30,30,10);

    for(int i =0; i < lines.size(); i++)
    {
        Scalar color;
		color = Scalar(rand()%256, rand()%256, rand()%256);
        //line(roi, Point(lines[i][0],lines[i][1]), Point(lines[i][2],lines[i][3]), color, 3);
    }

    float right_m, right_b, left_m, left_b;

    find_lines(lines, &left_m, &left_b, &right_m, &right_b);

    //Find 2 end points for right and left lines, used for drawing the line
    //y = m*x + b--> x = (y - b) / m




    // int differ=rdistance-ldistance;
    int differ = ldistance - rdistance;
    cam_msg.data=differ;

    circle (roi, Point(Xcenter, Yvalue), 5, Scalar(0,0,0),-1);
    putText(frame,format("%d - %d = %d",rdistance, ldistance, differ),Point(10,30),FONT_HERSHEY_SIMPLEX,1,Scalar(0,200,200),3);
    //imshow("roi",roi);
    //imshow("frame",frame);
    //imshow("edgeframe",line_frame);
}

int main(int argc, char**argv)
{

  // VideoCapture cap("/home/cseecar/sample_video.mp4");//"/home/cseecar/sample_video.mp4"
  VideoCapture cap(0);
  Mat frame, roi;

  if(!cap.isOpened()){
    cout<<"no camera!"<<endl;
    return -1;
  }

  ros::init(argc, argv, "cam_msg_publisher");
  ros::NodeHandle nh;
  std_msgs::Int16 cam_msg;
  ros::Publisher pub = nh.advertise<std_msgs::Int16>("cam_msg",100);

  int init_past=1;
  //--------------------------------------------------

  ros::Rate loop_rate(50);
  cout<<"start"<<endl;

  //clock_t tStart = clock();
  for(;;){

    cap>>frame;
    if(waitKey(30) >=0 )
	break;
    resize(frame,frame,Size(320,240));

    img_process(frame, cam_msg);

    pub.publish(cam_msg);

    loop_rate.sleep();
  }

  cout<<"Camera off"<<endl;
  return 0;
}
