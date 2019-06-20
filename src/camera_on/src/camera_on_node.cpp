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
//#include "camera_test/where.h"

using namespace std;
using namespace cv;

int main(int argc, char**argv){
  //for cam----------------------------------------------
  VideoCapture cap(0);
  Mat frame, grayframe; 

  if(!cap.isOpened()){
    cout<<"no camera"<<endl;
    return -1;
  }

  int const Xcenter = 160;//X center
  int const Yvalue = 200;//Y center
  int const width =639;
  int const range =40;
  Point p1(1,Yvalue), p2(width/2,Yvalue);//from right to middle
  Point p3(Xcenter,Yvalue-20), p4(Xcenter,Yvalue+20);// make center mark
  int Lvalue=130;
  int Lpixel=0, Rpixel=0;
  int Ldistance=275, Rdistance=320, pastL;
  int differ;
  //--------------------------------------------------
  //for msg pub --------------------------------------
  ros::init(argc, argv, "cam_msg_publisher");
  ros::NodeHandle nh;
  std_msgs::Int16 cam_msg;
  ros::Publisher pub = nh.advertise<std_msgs::Int16>("cam_msg",100);
  //ros::Publisher pub("cam_msg", &cam_msg);
  //nh.advertise(pub);
  int cccccc=0;
  //ros::Publisher pub = nh.advertise<camera_test::where>("cam_msg",100);
  //camera_test::where cam_msg;
  int init_past=1;
  int pub_value;
  //--------------------------------------------------
  ros::Rate loop_rate(50);
  cout<<"start"<<endl;
 
  //clock_t tStart = clock();
  for(;;){
	
    cap>>frame;
    if(waitKey(30) >=0 )break; 
   	resize(frame,frame,Size(320,240)); 
   
	cvtColor(frame,grayframe,COLOR_BGR2GRAY) ; 
    //imshow("frame",frame);
    adaptiveThreshold(grayframe,grayframe,255,ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY_INV,21,5);
    medianBlur(grayframe,grayframe,11);




   

    for(int c1=Xcenter;c1<639;c1++){
      Rpixel = grayframe.at<uchar>(Yvalue,c1);
      if(Rpixel == 255){
        Rdistance = c1-Xcenter;
        break;
      }

    }
    //cout<<Rdistance<<endl;
    for(int c2=Xcenter;c2>0;c2--){
      Lpixel = grayframe.at<uchar>(Yvalue,c2);
      if(Lpixel == 255){
        Ldistance = Xcenter-c2;
		if(init_past==1){
			pastL=Ldistance;
			init_past=0;
		}
        break;
      }

    }
    differ = Ldistance - Rdistance; // detect error
	cam_msg.data=differ;

    pub.publish(cam_msg);

    loop_rate.sleep();
	//printf("time::: %.fs\n",(double)(clock()-tStart)/CLOCKS_PER_SEC);   
  }



  cout<<"Camera off"<<endl;
  return 0;
}
