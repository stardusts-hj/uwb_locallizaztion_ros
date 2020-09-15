/*! ----------------------------------------------------------------------------
 *  @file    main.c
 *  @brief   use uwb to localize the posion of the robot
 *
 * @attention
 *
 * All rights reserved.
 *
 * @author lhj
 */

#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */ 
#include <errno.h>   /* ERROR Number Definitions           */
#include "trilateration.h" /*三边算法*/
#include "read_data.h"  /*从串口读取数据*/

using namespace std;



class uwb_localization
{
    /* 从serial port communication中得到标签到基站的距离，然后利用三边定位算法得到标签的坐标 */
public:
    double update_rate;  //位置信息刷新率
    int result;
    int use4thAchor;  //四个基站或是三个，默认是三个
    int Range_deca[4]; //各基站到标签的距离,单位是毫米
    vec3d report; //解出的标签的坐标
    vec3d anchorArray[4];    //三个基站的坐标
    int init_anchor_position(vec3d *input_anchorArray); //输入一开始基站的坐标, 单位:米
    int init_serial_port(void);
    int read_distance(void);
    vec3d get_position(void);
        
};

//初始化基站的坐标
int uwb_localization::init_anchor_position(vec3d *input_anchorArray){
    /*输入初始的基站坐标*/
    int i = 0;
    for(i = 0; i < 4; i++){
        anchorArray[i].x = input_anchorArray[i].x;
        anchorArray[i].y = input_anchorArray[i].y;
        anchorArray[i].z = input_anchorArray[i].z;
    }
    return 0;       
}


//串口通信的初始化
int uwb_localization::init_serial_port(void){
    init_port();
    return 0;
}




//调用串口通信协议，读取标签到各个基站的位置，其中可以改变刷新率(待定)

int uwb_localization::read_distance(){
    read_data(Range_deca);
    return 0;   
}


vec3d uwb_localization::get_position()
{
    result = GetLocation(&report, use4thAchor, &anchorArray[0], &Range_deca[0]);
    return report;
}

int main()
{
    /*初始化*/
    int i = 0;
    uwb_localization uwb;

// 输入定位基站的坐标

    vec3d input_anchorArray[4];

    input_anchorArray[0].x = 0.000; //anchor0.x uint:m
	input_anchorArray[0].y = 0.000; //anchor0.y uint:m
	input_anchorArray[0].z = 0.000; //anchor0.z uint:m

	input_anchorArray[1].x = 1.800; //anchor1.x uint:m
	input_anchorArray[1].y = 0.000; //anchor1.y uint:m
	input_anchorArray[1].z = 0.000; //anchor1.z uint:m

	input_anchorArray[2].x = 0.000; //anchor2.x uint:m
	input_anchorArray[2].y = 2.800; //anchor2.y uint:m
	input_anchorArray[2].z = 0.000; //anchor2.z uint:m

	input_anchorArray[3].x = 0.000; //anchor3.x uint:m
	input_anchorArray[3].y = 0.000; //anchor3.y uint:m
	input_anchorArray[3].z = 0.000; //anchor3.z uint:m

// 初始化标签到各个基站的距离
    for(i = 0;i<4;i++)
        uwb.Range_deca[i] = 0;

    uwb.use4thAchor = 0;  // 仅用3个基站
    uwb.init_anchor_position(&input_anchorArray[0]);
    uwb.init_serial_port();

       for(i = 0;i<4;i++){
           printf(" %d : %f  %f  %f \n ", i, uwb.anchorArray[i].x, uwb.anchorArray[i].y, uwb.anchorArray[i].z);
       }


   while (1)
   {
        uwb.read_distance();
        
       

       // tag 到 基站的距离信息 
        printf("\n %d  %d  %d \n", uwb.Range_deca[0], uwb.Range_deca[1], uwb.Range_deca[2]);  
        uwb.get_position();
       // 计算出距离信息 
        printf("%f  %f  %f", uwb.report.x, uwb.report.y, uwb.report.z);
          
    
   }
   
      
    
    return 0;
}





 