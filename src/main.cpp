#include<iostream>
using namespace std;
#include "workerManager.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"

int main(){
	cout << "开始项目" << endl;	
	WorkerManager wm;
    int choice = 0;
    while(true){
        //展示菜单
        wm.Show_Menu();
        cout << "请输入您的选择: " << endl;
        cin >> choice;
        switch (choice)
        {
        case 0://退出系统
        {
            /* code */
            wm.exitSystem();
            break;
        }
        case 1://添加职工
        {
            /* code */
            break;
        }
        case 2://显示职工
        {
            /* code */
            break;
        }
        case 3://删除职工
        {
            /* code */
            break;
        }
        case 4://修改职工
        {
            /* code */
            break;
        }
        case 5://查找职工
        {
            /* code */
            break;
        }
        case 6://排序职工
        {
            /* code */
            break;
        }
        case 7://清空职工
        {
            /* code */
            break;
        }
        default:
            cout << "输入有误！！！" << endl;
            break;
        }
    }
	
	return 0;
}