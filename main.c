#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs_define.h"
#include "structs_initialize.h"
int time=0;
int block_time=1,split_time=1,map_time=1,reduce_time=1;

void DataBlock(int DataTotal, int BlockSize)
{
	printf("DataBlock start\n");
	time+=block_time;
	printf("DataBlock finish\n");
}

void DataSplit(int BlockSize, int SplitSize)
{
	printf("DataSplit start\n");
	time+=split_time;
	printf("DataSplit finish\n");
}

void Map(int nodes,int nodemaps)
{
	int i,j;
	printf("Map start\n");
	for(i=0;i<split_size;i++)
	{
	printf("Node%d's Split%d send to Node%d's Map%d\n",splits_DN[i][0],i,i/2%dataNode_size,i%2);
	if(split_size%nodemaps*dataNode_size==0)
	{
		time+=map_time;
	}
	}
	printf("Map finish\n");
}

void Reduce(int nodes,int nodereduces)
{
	int i,j;
	printf("Reduce start\n");
	for(i=0;i<dataNode_size;i++)
        {   
                for(j=0;j<dataNode_size*reducer_size;j++)
                {   
                        printf("Node%d's shuffle send to Node%d's Reduce%d\n",i,j/reducer_size,j%2);
                }   
        time+=reduce_time;
        }	
	printf("Reduce finish\n");
}

void Generic_Log()
{
	int t0,t1,t2,t3,t4,t5,t6,t7,t8;
	int D=64,N=16,M=640,R=160;
	int time=0;
	FILE *fp1;
	char input_data[1024];
	int i,j;
	t0=0;
	t1=(int)8.0+0.70536*D/N-0.07812*M/N;
	t2=(int)19.0-9.28571*D/N+1.0*M/N;
	t3=(int)29.5+16.64286*D/N+2.0*M/N;
	t4=(int)30.5+78.64286*D/N-1.0*M/N;
	t6=(int)36.5+18.35714*D/N+2.0*M/N;
	t5=(int)47.5-64.78571*D/N+7.0*M/N;
	t7=(int)83.0+171.14286*D/N-4.0*M/N;
	t8=(int)86.0+171.57143*D/N-4.0*M/N;
	t1=9,t2=114,t3=388,t4=395,t5=401,t6=505,t7=694,t8=698;
	printf("%d %d %d %d %d %d %d %d\n",t1,t2,t3,t4,t5,t6,t7,t8);
	for(i=0;i<16;i++)
	{
	for(j=0;j<16;j++)
	{
	if(i!=j)
	{
	char log_name[100];
	sprintf(log_name,"./log/%d-%d.log",i,j);
	fp1 = fopen(log_name,"w");
	for(time=0;time<t8;time++)
	{
	sprintf(input_data, "%d", time);
        fputs(input_data,fp1);
        fputs("\t",fp1);
	double a1=1.204*pow(10,7);
	double b1=648;
	double c1=1.991;
	double a2=1.303*pow(10,7);
	double b2=301;
	double c2=1.595;
	double a3=1.165*pow(10,7);
	double b3=166.9;
	double c3=3.406;
	double a4=8.513*pow(10,6);
	double b4=557.4;
	double c4=3.393;
	if(time>=t2&&time<=t3)
	{
	int data=(int)(a1*exp(-pow(((time-b1)/c1),2)) + a2*exp(-pow(((time-b2)/c2),2))+a3*exp(-pow(((time-b3)/c3),2)) + a4*exp(-pow(((time-b4)/c4),2)));
	sprintf(input_data, "%d", data);
	fputs(input_data,fp1);
	fputs("\n",fp1);
	}
	else if(time>=t6&&time<=t7)
        {
	int data=(int)(a1*exp(-pow(((time-b1)/c1),2)) + a2*exp(-pow(((time-b2)/c2),2))+a3*exp(-pow(((time-b3)/c3),2)) + a4*exp(-pow(((time-b4)/c4),2)));
        sprintf(input_data, "%d", data);
        fputs(input_data,fp1);
        fputs("\n",fp1);
        }
	else
	{
	int data=0;
	sprintf(input_data, "%d", data);
	fputs(input_data,fp1);
	fputs("\n",fp1);
	}
	}
	fclose(fp1);
	}
	}
	}
}

void main()
{
	printf("Job start\n");
	DataBlock( data_length, block_length);
	DataSplit( block_length, split_length);
	Map( dataNode_size, mapper_perDN);
	Reduce( dataNode_size, reducer_size);
	printf("Job finish\n");
	printf("execute time is %ds.\n",time);
	Generic_Log();

}
