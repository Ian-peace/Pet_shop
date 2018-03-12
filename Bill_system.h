#ifndef BILL_SYSTEM_H_INCLUDED
#define BILL_SYSTEM_H_INCLUDED

#include <ctime>
using namespace std;

int sum_in;
int sum_out;
int id_in, id_out;

void register_in()              //������Ŀ�Ǽ�
{
    int cost;
    string event, current;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    current = asctime(timeinfo);             //��ȡ��ǰϵͳʱ��

    cout << "Current local time and date: " << current << endl;
    cout << "������������Ŀ������";
    cin >> event;
    cout << "������������ã�n>0):";
    cin >> cost;

    /*-----------------------------������ļ�-------------------------------*/

    ofstream fout("bill_income.txt", ios::app|ios::in);
    if(!fout){
        cout << "Cannot open output file\n";
    }
    else{
        fout << "��ţ�" << ++id_in << endl;
        fout << "���ڣ�" << current;
        fout << "���ã�" << cost << endl;
        fout << "��ע��" << event << endl;
        fout << endl;
        fout.close();
    }
    sum_in += cost;
}

void register_out()             //֧����Ŀ�Ǽ�
{
    int cost;
    string event, current;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    current = asctime(timeinfo);             //��ȡ��ǰϵͳʱ��

    cout << "Current local time and date: " << current << endl;
    cout << "������֧����Ŀ������";
    cin >> event;
    cout << "������֧�����ã�n>0):";
    cin >> cost;
    cost *= -1;

    /*-----------------------------������ļ�-------------------------------*/

    ofstream fout("bill_out.txt", ios::app|ios::in);
    if(!fout){
        cout << "Cannot open output file\n";
    }
    else{
        fout << "��ţ�" << ++id_out << endl;
        fout << "���ڣ�" << current;
        fout << "���ã�" << cost << endl;
        fout << "��ע��" << event << endl;
        fout << endl;
        fout.close();
    }
    sum_out += cost;
}

void income_list()              //������ϸ
{
    system("cls");
    int len = CountLines("bill_income.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("bill_income.txt", i) << endl;
    }
}

void pay_list()                 //֧����ϸ
{
    system("cls");
    int len = CountLines("bill_out.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("bill_out.txt", i) << endl;
    }
}

void sum_list()                 //����ӯ��
{
    cout << "������Ϊ��" << sum_in << endl;
    cout << "��֧��Ϊ��" << sum_out << endl;
    cout << "�ϼƣ�" << sum_in + sum_out << endl;
}

void bill_sys()                                   //�˵�ϵͳ
{
    /*----------------��ȡͳ������-------------*/

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

    /*------------------��ʼ------------------*/
    int t;
    Menu_bill();
    int f = 0, ff = 1;
    cout << "��ѡ��";
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
                cout << "��������Ƿ������������룺";
                ff = 0;
        }

        if(f) break;

        if(ff){
            system("cls");
            Menu_bill();
            cout << "��ѡ��";
        }
    }

    /*---------------����ͳ������-----------------*/
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
