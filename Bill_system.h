#ifndef BILL_SYSTEM_H_INCLUDED
#define BILL_SYSTEM_H_INCLUDED

#include <ctime>
using namespace std;

int sum_in;
int sum_out;
int id_in, id_out;

void register_in()              //收入项目登记
{
    int cost;
    string event, current;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    current = asctime(timeinfo);             //获取当前系统时间

    cout << "Current local time and date: " << current << endl;
    cout << "请输入收入项目描述：";
    cin >> event;
    cout << "请输入收入费用（n>0):";
    cin >> cost;

    /*-----------------------------输出到文件-------------------------------*/

    ofstream fout("bill_income.txt", ios::app|ios::in);
    if(!fout){
        cout << "Cannot open output file\n";
    }
    else{
        fout << "编号：" << ++id_in << endl;
        fout << "日期：" << current;
        fout << "费用：" << cost << endl;
        fout << "备注：" << event << endl;
        fout << endl;
        fout.close();
    }
    sum_in += cost;
}

void register_out()             //支出项目登记
{
    int cost;
    string event, current;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    current = asctime(timeinfo);             //获取当前系统时间

    cout << "Current local time and date: " << current << endl;
    cout << "请输入支出项目描述：";
    cin >> event;
    cout << "请输入支出费用（n>0):";
    cin >> cost;
    cost *= -1;

    /*-----------------------------输出到文件-------------------------------*/

    ofstream fout("bill_out.txt", ios::app|ios::in);
    if(!fout){
        cout << "Cannot open output file\n";
    }
    else{
        fout << "编号：" << ++id_out << endl;
        fout << "日期：" << current;
        fout << "费用：" << cost << endl;
        fout << "备注：" << event << endl;
        fout << endl;
        fout.close();
    }
    sum_out += cost;
}

void income_list()              //收入明细
{
    system("cls");
    int len = CountLines("bill_income.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("bill_income.txt", i) << endl;
    }
}

void pay_list()                 //支出明细
{
    system("cls");
    int len = CountLines("bill_out.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("bill_out.txt", i) << endl;
    }
}

void sum_list()                 //总体盈亏
{
    cout << "总收入为：" << sum_in << endl;
    cout << "总支出为：" << sum_out << endl;
    cout << "合计：" << sum_in + sum_out << endl;
}

void bill_sys()                                   //账单系统
{
    /*----------------读取统计数据-------------*/

    ifstream file("bill_sum.txt", ios::out|ios::in);
    if(file.eof()){
        sum_in = 0;
        sum_out = 0;
        id_in = 0;
        id_out = 0;
    }
    else {
        file >> sum_in;
        file >> sum_out;
        file >> id_in;
        file >> id_out;
    }
    file.close();

    /*------------------开始------------------*/
    int t;
    Menu_bill();
    int f = 0, ff = 1;
    cout << "请选择：";
    while(cin >> t){
        switch(t){
            case(1):
                register_in();
                break;
            case(2):
                register_out();
                break;
            case(3):
                income_list();
                system("pause");
                break;
            case(4):
                pay_list();
                system("pause");
                break;
            case(5):
                sum_list();
                system("pause");
                break;
            case(0):
                f = 1;
                break;
            default:
                cout << "您的输入非法，请重新输入：";
                ff = 0;
        }

        if(f) break;

        if(ff){
            system("cls");
            Menu_bill();
            cout << "请选择：";
        }
    }

    /*---------------保存统计数据-----------------*/
    ofstream file1("bill_sum.txt");
    if(!file1){
        cout << "Cannot open output file\n";
    }
    file1 << sum_in << endl;
    file1 << sum_out << endl;
    file1 << id_in << endl;
    file1 << id_out << endl;
    file1.close();
}

#endif // BILL_SYSTEM_H_INCLUDED
