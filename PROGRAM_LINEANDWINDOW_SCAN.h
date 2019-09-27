#ifndef  _PROGRAM_LINEANDWINDOW_SCAN_H
#define  _PROGRAM_LINEANDWINDOW_SCAN_H
int FIND_WINDOW();/*寻找空闲窗口*/
void ENTER_WINDOW(int WIN_NUM);/*乘客进入窗口*/ 
void PROCESS_WINDOW_TIME();/*处理安检口时间 +1s*/
void MAIN_SCAN();/*扫描 让乘客进入安检口*/
void PROCESS_WINDOW_RESTLINE();/*处理安检口休息队列*/ 
#endif
