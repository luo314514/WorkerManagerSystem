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
};
