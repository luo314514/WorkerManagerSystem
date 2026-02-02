#include "workerManager.h"
#include "work.h"
#include <iostream>
#include "boss.h"
#include "manager.h"
#include "employee.h"

using namespace std;

WorkerManager::WorkerManager() {
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    //文件不存在
    if(!ifs.is_open()){
        //cout << "文件不存在！！！"<< endl;
        //初始化人数
        this->m_EmpNum = 0;
        //初始化数组指针
        this->m_EmpArrary = NULL;
        this->m_FileEmpty = true;//初始化文件为空标志
        ifs.close();
        return;
    }
    //文件存在但为空
    char ch;
    ifs >> ch;
    if(ifs.eof()){
        //cout << "文件为空！！！" << endl;
        this->m_EmpNum = 0;
        this->m_FileEmpty = true;
        this->m_EmpArrary = NULL;
        ifs.close();
        return;
    }
    //文件存在，并且记录数据
    int num = this->get_EmpNum();
    cout << "职工人数为： " << num << endl;
    this->m_EmpNum = num;
    //根据职工数创建数组
    this->m_EmpArrary = new Worker *[this->m_EmpNum];
    //初始化职工,将文件中的数据写入数组中
    init_Emp();
}

WorkerManager::~WorkerManager() {
    if(this->m_EmpArrary != NULL){
        for(int i = 0;i < m_EmpNum;i++){
            delete m_EmpArrary[i];
        }
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
        this->save();//把数据保存到文件中
        this->m_FileEmpty = false;//添加成功后吧

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
int WorkerManager::get_EmpNum(){
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int dId;

    int num = 0;
    while(ifs >> id && ifs >> name && ifs >> dId){
        //记录人数
        num++;
    }
    ifs.close();
    return num;
}
//初始化数据
void WorkerManager::init_Emp(){
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int dId;
    int index = 0;
    while(ifs >> id && ifs >> name && ifs >> dId){
        Worker * worker = NULL;
        if(dId == 1){
            worker = new Employee(id,name,dId);
        }
        else if(dId == 2){
            worker = new Manager(id,name,dId);
        }
        else{
            worker = new Boss(id,name,dId);
        }
        //存放在数组中
        this->m_EmpArrary[index] = worker;
        index++;
    }
}
//显示职工
void WorkerManager::show_Emp(){
    if(this->m_FileEmpty){
        cout << "文件不存在或者记录为空!!" << endl;
    }
    else{
        for(int i = 0;i < m_EmpNum;i++){
            //利用多态调用接口
            this->m_EmpArrary[i]->showInfo();
        }
    }
}
//按照职工编号判断职工是否存在，若存在则返回职工在数组中的位置，不存在则返回-1
int WorkerManager::isExist(int id){
    int index = -1;
    for(int i = 0;i < this->m_EmpNum;i++){
        if(this->m_EmpArrary[i]->m_Id == id){
            index = i;
            break;
        }
    }
    return index;
}
//删除员工
void WorkerManager::del_Emp(){
    if(this->m_FileEmpty){
        cout << "文件不存在或记录不存在！！！" << endl;
    }
    else{
        cout << "请输入想要删除的员工的编号： " << endl;
        int id = 0;
        cin >> id;
        int index = this->isExist(id);
        if(index != -1){
            //数据前移覆盖要删除的职工
            for(int i = index;i < this->m_EmpNum;i++){
                this->m_EmpArrary[i] = this->m_EmpArrary[i + 1];
            }
            this->m_EmpNum--;//更新数组中记录的人员个数
            this->save();//保存到文件
            cout << "删除成功" << endl;
        }
        else{
            cout << "删除失败，未找到该职工！！！" << endl;
        }
    }
}
//修改职工
void WorkerManager::mod_Emp(){
    if(this->m_FileEmpty){
        cout << "文件不存在或记录为空!!!" << endl;
    }
    else{
        cout << "请输入要修改职工的编号： " << endl;
        int id;
        cin >> id;
        int ret = this->isExist(id);
        if(ret != -1){
            //查找到要修改员工的编号
            delete this->m_EmpArrary[ret];
            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
            cin >> newId;
            cout << "请输入新姓名: " << endl;
            cin >> newName;
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
                    worker = new Employee(newId,newName,dSelect);
                    break;
                case 2://经理
                    /* code */
                    worker = new Manager(newId,newName,dSelect);
                    break;
                case 3://老板
                    /* code */
                    worker = new Boss(newId,newName,dSelect);
                    break;
                default:
                    break;
            }
            //更改数据到数组中
            this->m_EmpArrary[ret] = worker;
            cout << "修改成功！" << this->m_EmpArrary[ret]->m_DeptId << endl;
            //保存到文件
            this->save();
        }
        else{
            cout << "修改失败，查无此人" << endl;
        }
    }
}
//查找职工
void WorkerManager::find_Emp(){
    if(this->m_FileEmpty){
        cout << "文件不存在或记录为空!!!" << endl;
    }
    else{
        cout << "请输入查找方式: " << endl;
        cout << "1、按职工编号查找" << endl;
        cout << "2、按姓名查找" << endl;

        int select = 0;
        cin >> select;

        if(select == 1){//按职工编号查找
            int id;
            cout << "请输入查找的职工编号: " << endl;
            cin >> id;

            int ret = isExist(id);
            if(ret != -1){
                cout << "查找成功！该职工信息如下： " << endl;
                this->m_EmpArrary[ret]->showInfo();
            }
            else{
                cout << "查找失败，查无此人！" << endl;
            }
        }
        else if(select == 2){
            string name;
            cout << "请输入查找的姓名： "<< endl;
            cin >> name;
            bool flag = false;
            for(int i = 0;i < m_EmpNum;i++){
                if(m_EmpArrary[i]->m_Name == name){
                    cout << "查找成功，职工编号为： " << m_EmpArrary[i]->m_Id
                     <<"号的信息如下：" << endl;
                     flag = true;
                     this->m_EmpArrary[i]->showInfo();
                }
                
            }
            if(flag == false){
                cout << "查找失败，查无此人!!" << endl;
            }
        }
        else{
            cout << "输入选型有误！！！" << endl;
        }
    }
}
//排序职工
void WorkerManager::sort_Emp(){
    if(this->m_FileEmpty){
        cout << "文件不存在或记录为空!!!" << endl;
    }
    else{
        cout << "请选择排序方式: " << endl;
        cout << "1、按职工号进行升序： " << endl;
        cout << "2、按职工号进行降序： " << endl;

        int select = 0;
        cin >> select;
        for(int i = 0;i < m_EmpNum; i++){
            int minOrmax = i;
            for(int j = i + 1;j < m_EmpNum;j++){
                if(select == 1){//升序
                    if(m_EmpArrary[minOrmax]->m_Id > m_EmpArrary[j]->m_Id){
                        minOrmax = j;
                    }
                }
                else{//降序
                    if(m_EmpArrary[minOrmax]->m_Id < m_EmpArrary[j]->m_Id){
                        minOrmax = j;
                    }
                }
            }
            if(i != minOrmax){
                Worker * temp = m_EmpArrary[i];
                m_EmpArrary[i] = m_EmpArrary[minOrmax];
                m_EmpArrary[minOrmax] = temp;
            }
        }
    }
    cout << "排序成功，排序后结果为： " << endl;
    this->save();
    this->show_Emp();
}
//清空文件
void WorkerManager::clean_File(){
    cout << "确认清空？" << endl;
    cout << "1、确认"  << endl;
    cout << "2、取消" << endl;
    int select = 0;
    cin >> select;

    if(select == 1){
        ofstream ofs(FILENAME,ios::trunc);
        ofs.close();
        if(this->m_EmpArrary != NULL){
            for(int i = 0;i < this->m_EmpNum;i++){
                if(this->m_EmpArrary[i] != NULL){
                    delete this->m_EmpArrary[i];
                }
            }
            this->m_EmpNum = 0;
            delete[] this->m_EmpArrary;
            this->m_EmpArrary = NULL;
            this->m_FileEmpty = true;
        }
        cout << "清空成功！！" << endl;
    }
}

