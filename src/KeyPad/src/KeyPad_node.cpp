#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <termio.h>
#include <unistd.h>

#include <geometry_msgs/Twist.h>

int kbhit();
int getch();

int main(int argc, char **argv)
{
	ros::init(argc, argv, "msg_key_publisher");
	ros::NodeHandle nh3;

	//ros::Publisher pub2 = nh3.advertise<std_msgs::Int8>("data_msg", 100);
	ros::Publisher pub2 = nh3.advertise<geometry_msgs::Twist>("data_msg_key", 100);
	//ros::Rate loop_rate(1);
	geometry_msgs::Twist cmd;
    std_msgs::Int8 msg2;

	int key = 0;
	bool turn=true;
	printf("\nControl Your robot!\n");
    printf("---------------------------\n");
    printf("Moving around:\n");
    printf("         w    r\n");
    printf("    a    s    d\n");
	printf("         x     \n");
    //printf("    z    x    c\n\n");

	printf("\nESC to quit");
	int spd_send=30;
	int angle_send=90;
	while(true)
	{
		if(kbhit){
			key = getch();
		}else{
			key = 0;
		}

		switch(key){
			case 27:
               printf("ESCAPE\n");
            	return 0;
            	break;
			case 'w':
                //msg2.data = 1;
				if( ++spd_send> 200)
                     spd_send = 200;
				cmd.linear.x=spd_send;
               printf("speed=%d\n", spd_send);
				//cmd.angular.z=90;
				break;
			//left 2.00
			case 'a':
				//cmd.linear.x=50;
				if(++angle_send > 150)
					  angle_send = 150;
				cmd.angular.z=angle_send;
                printf("angle=%d\n", angle_send);
                //msg2.data = 3;
				break;

			//right 3.00
			case 'd':
				//cmd.linear.x=50;
                if(--angle_send < 30)
					  angle_send = 30;
				cmd.angular.z=angle_send;
				cmd.linear.x=spd_send;
                printf("angle=%d\n", angle_send);
                //msg2.data = 2;
				break;
			case 'x':
				//cmd.linear.x=50;
				if( --spd_send < -200)
                     spd_send = -200;
				cmd.linear.x=spd_send;
                printf("speed=%d\n", spd_send);
                //msg2.data = 2;
				break;
			case 's':
				spd_send=0;
				angle_send=90;
				cmd.linear.x=spd_send;
				cmd.angular.z=angle_send;
				printf("angle=%d\n",angle_send);
                //msg2.data = 2;
				break;
			case 'r':
				turn=!turn;
				cmd.linear.y=turn;
			    printf("mode changed to  %s\n", turn? "camera mode": "keypad mode");
                //msg2.data = 2;
				break;
		}

		pub2.publish(cmd);
		//loop_rate.sleep();

	}

	return 0;
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF)
    {
    ungetc(ch, stdin);
    return 1;
    }
    return 0;
}
int getch(){
    int ch;
    struct termios buf, save;
    tcgetattr(0,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}
