/*! ----------------------------------------------------------------------------
 *  @file    main.c
 *  @brief   use uwb to localize the posion of the robot
 *
 * @attention
 *
 *
 *
 * All rights reserved.
 *
 * @author lhj
 */

#include<stdio.h>
#include<stdlib.h>
#include"trilateration.h"
#include"read10.h"

using namespace std;



class uwb_localization
{
    /* 从api中得到标签到基站的距离，然后利用三边定位算法得到标签的坐标 */
private:
    /* data */
public:
    double update_rate;  //位置信息刷新率
    int result;
    int use4thAchor;  //四个基站或是三个，默认是三个
    int Range_deca[4]; //各基站到标签的距离,单位是毫米
    vec3d report; //解出的标签的坐标
    vec3d anchorArray[4];    //三个基站的坐标
    int init_anchor_position(vec3d *anchorArray); //输入一开始基站的坐标
   int read_distance(int* Range_deca);
    vec3d get_position(void);    
};

//初始化基站的坐标
int uwb_localization::init_anchor_position(vec3d *anchorArray){
    /*输入初始的基站坐标*/
    anchorArray[0].x = 0.000; //anchor0.x uint:m
	anchorArray[0].y = 0.000; //anchor0.y uint:m
	anchorArray[0].z = 0.000; //anchor0.z uint:m

	anchorArray[1].x = 1.80; //anchor1.x uint:m
	anchorArray[1].y = 0.000; //anchor1.y uint:m
	anchorArray[1].z = 0.000; //anchor1.z uint:m

	anchorArray[2].x = 0.000; //anchor2.x uint:m
	anchorArray[2].y = 2.800; //anchor2.y uint:m
	anchorArray[2].z = 0.000; //anchor2.z uint:m

	anchorArray[3].x = 0.000; //anchor3.x uint:m
	anchorArray[3].y = -5.80; //anchor3.y uint:m
	anchorArray[3].z = 0.000; //anchor3.z uint:m

    return 0;       
}

//调用串口通信协议，读取标签到各个基站的位置，其中可以改变刷新率(待定)

int uwb_localization::read_distance(int *Range_deca){
    read_range(Range_deca);
    return 0;   
}


vec3d uwb_localization::get_position(void)
{
    result = GetLocation(&report, use4thAchor, &anchorArray[0], &Range_deca[0]);
    return report;
}

int main()
{
    /*初始化*/
    int i = 0;
    uwb_localization local1;


    for(i = 0;i<4;i++)
        local1.Range_deca[i] = 0;

    local1.use4thAchor = 0;
    local1.init_anchor_position(&local1.anchorArray[0]);
    while (1)
    {
        local1.read_distance(&local1.Range_deca[0]);
        
         local1.get_position();
        printf("%f  %f  %f", local1.report.x, local1.report.y, local1.report.z);
        printf("%d  %d  %d /n", local1.Range_deca[0], local1.Range_deca[1], local1.Range_deca[2]);    
    

    }
    
    return 0;
}
