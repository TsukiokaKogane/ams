#ifndef  _PROGRAM_IO_H
#define  _PROGRAM_IO_H
void foward_output(PASSENGER_DATA *nowPtr,int totnum);/*文件蛇形队列前向输出*/
void backward_output(PASSENGER_DATA *nowPtr,int totnum);/*文件蛇形队列反向输出*/
void interval_output(int now_row);/*文件蛇形队列间隔输出*/ 
void BUFFERLINE_OUTPUT();/*文件蛇形队列输出*/ 
void foward_output_lite(PASSENGER_DATA *nowPtr,int totnum);/*命令行蛇形队列前向输出*/
void backward_output_lite(PASSENGER_DATA *nowPtr,int totnum);/*命令行蛇形队列反向输出*/
void interval_output_lite(int now_row);/*命令行蛇形队列间隔输出*/ 
void BUFFERLINE_OUTPUT_LITE();/*命令行蛇形队列输出*/ 
void FILE_OUTPUT();/*文件输出*/ 
void output_chart();/*输出图表*/ 
void CMD_OUTPUT();/*命令行输出*/ 
void ASK_FOR_QUIT();/*要求下班*/ 
void OUTPUT();
int CHECK_FOR_EXIT();/*检查跳出条件*/ 
void BASIC_INITIALIZATION();/*基本初始化*/ 
void FREE_SPACE();/*清理空间*/ 
void getInput();/*实时输入*/ 
void INUPUT_BY_KEYBORAD();/*键盘输入*/
void INPUT_BY_FILE();/*文件输入*/ 
#endif
