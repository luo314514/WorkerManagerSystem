#pragma once
#include "boss.h"
#include "manager.h"
#include "employee.h"
#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager {
public:
    WorkerManager();
    ~WorkerManager();
    void Show_Menu();//展示菜单
    int m_EmpNum;//记录文件中的人数个数
    Worker ** m_EmpArrary;//员工数组的指针
    void Add_Emp();//增加职工
    void exitSystem();//退出系统
    void save();//保存文件
    bool m_FileEmpty;//标志文件是否为空
    int get_EmpNum();//统计人数
    void init_Emp();//初始化数据
    void show_Emp();//显示职工
    void del_Emp();//删除员工
    int isExist(int id);//按照职工编号判断职工是否存在，若存在则返回职工在数组中的位置，不存在则返回-1
    void mod_Emp();//修改职工
    void find_Emp();//查找职工
    void sort_Emp();//排序职工
    void clean_File();//清空文件
};
