#ifndef  _PROGRAM_IO_H
#define  _PROGRAM_IO_H
void foward_output(PASSENGER_DATA *nowPtr,int totnum);/*�ļ����ζ���ǰ�����*/
void backward_output(PASSENGER_DATA *nowPtr,int totnum);/*�ļ����ζ��з������*/
void interval_output(int now_row);/*�ļ����ζ��м�����*/ 
void BUFFERLINE_OUTPUT();/*�ļ����ζ������*/ 
void foward_output_lite(PASSENGER_DATA *nowPtr,int totnum);/*���������ζ���ǰ�����*/
void backward_output_lite(PASSENGER_DATA *nowPtr,int totnum);/*���������ζ��з������*/
void interval_output_lite(int now_row);/*���������ζ��м�����*/ 
void BUFFERLINE_OUTPUT_LITE();/*���������ζ������*/ 
void FILE_OUTPUT();/*�ļ����*/ 
void output_chart();/*���ͼ��*/ 
void CMD_OUTPUT();/*���������*/ 
void ASK_FOR_QUIT();/*Ҫ���°�*/ 
void OUTPUT();
int CHECK_FOR_EXIT();/*�����������*/ 
void BASIC_INITIALIZATION();/*������ʼ��*/ 
void FREE_SPACE();/*����ռ�*/ 
void getInput();/*ʵʱ����*/ 
void INUPUT_BY_KEYBORAD();/*��������*/
void INPUT_BY_FILE();/*�ļ�����*/ 
#endif
