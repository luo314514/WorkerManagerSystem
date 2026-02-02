#include "workerManager.h"
#include "work.h"
#include <iostream>

using namespace std;

WorkerManager::WorkerManager() {
    //初始化人数
    this->m_EmpNum = 0;
    //初始化数组指针
    this->m_EmpArrary = NULL;
}

WorkerManager::~WorkerManager() {
    if(this->m_EmpArrary != NULL){
        delete[] this->m_EmpArrary;
        this->m_EmpArrary = NULL;
    }
}
//展示菜单
void WorkerManager::Show_Menu() {
    cout << "*********************" << endl;
    cout << "****欢迎使用职工管理系统****" << endl;
    cout << "*****1.添加职工信息*****" << endl;
    cout << "*****2.显示职工信息*****" << endl;
    cout << "*****3.删除离职职工*****" << endl;
    cout << "*****4.修改职工信息*****" << endl;
    cout << "*****5.查找职工信息*****" << endl;
    cout << "*****6.按照编号排序*****" << endl;
    cout << "*****7.清空所有文档*****" << endl;
    cout << "*****0.退出管理系统*****" << endl;
    cout << "*********************" << endl;
    cout << endl;
}
//退出系统
void WorkerManager::exitSystem(){
     cout << "欢迎下次使用" << endl;
    exit(0);
}
//增加职工
void WorkerManager::Add_Emp(){
    cout << "请输入增加员工数量： " << endl;
    int addNum = 0;
    cin >> addNum;

    if(addNum > 0){
        //计算新空间大小
        int newSize = this->m_EmpNum + addNum;
        //开辟新空间
        Worker ** newSpace = new Worker*[newSize];
        //将原空间下的内容存放到新空间
        if(this->m_EmpArrary != NULL){
            for(int i = 0;i < this->m_EmpNum;i++){
                newSpace[i] = this->m_EmpArrary[i];
            }
        }
        //输入新数据
        for(int i = 0;i < addNum;i++){
            int id;
            string name;
            int dSelect;
            cout << "请输入第 " << i+1<<"个新职员编号: " << endl;
            cin >> id;

            cout << "请输入第 " << i+1<<"个新职工姓名： " << endl;
            cin >> name;

            cout << "请选择该职工的岗位： " << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> dSelect;

            Worker * worker = NULL;
            switch (dSelect)
            {
            case 1://普通员工
                /* code */
                worker = new Employee(id,name,1);
                break;
            case 2://经理
                /* code */
                worker = new Manager(id,name,2);
                break;
            case 3://老板
                /* code */
                worker = new Boss(id,name,3);
                break;
            default:
                break;
            }
            //将创建职工保存到数组里面
            newSpace[this->m_EmpNum + i] = worker;
        }
        //释放原有空间
        delete[] this->m_EmpArrary;
        //更改新空间的指向
        this->m_EmpArrary = newSpace;
        //更新新的个数
        this->m_EmpNum = newSize;
        //提示信息
        cout << "成功添加" << addNum << "名新职工!" << endl;
    }
    else{
        cout << "输入有误！！" << endl;
    }
}

//写文件
void WorkerManager::save(){
    ofstream ofs;
    ofs.open(FILENAME,ios::out);
    for(int i = 0;i < this->m_EmpNum;i++){
        ofs << this->m_EmpArrary[i]->m_Id << " "
            << this->m_EmpArrary[i]->m_Name << " "
            << this->m_EmpArrary[i]->m_DeptId << endl;
    }
    ofs.close();
}