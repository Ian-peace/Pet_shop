#ifndef STOCK_SYSTEM_H_INCLUDED
#define STOCK_SYSTEM_H_INCLUDED

double value;     //����ܼ�ֵ
int id;           //�����Ʒid

void goods_add()                         //��Ʒ���
{
    string name;
    double price;
    int amount;

    cout << "��Ʒ���ƣ�";
    cin >> name;
    cout << "�۸�";
    cin >> price;
    cout << "������";
    cin >> amount;

    /*----------------���뵽�ļ�-------------------------*/
    ofstream fout("stock.txt", ios::app|ios::in);
    if(!fout){
        cout << "Cannot open output file\n";
    }
    else{
        fout << "��ţ�" << ++id << endl;
        fout << "���ƣ�" << name << endl;
        fout << "�۸�" << price << endl;
        fout << "������" << amount << endl;
        fout << endl;
        fout.close();
    }
    value += price*amount;
}

void stock_value()                      //��Ʒ�ܼ�ֵ
{
    cout << value << endl;
}

void stock_list()                       //��Ʒ���
{
    system("cls");
    int len = CountLines("stock.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("stock.txt", i) << endl;
    }
}

void stock_sys()                                   //�˵�ϵͳ
{
    /*----------------��ȡͳ������-------------*/

    ifstream file("stock_value.txt");
    if(file.eof()){
        value = 0;
        id = 0;
    }
    else {
        file >> value;
        file >> id;
    }
    file.close();

    /*------------------��ʼ------------------*/
    int t;
    Menu_stock();
    int f = 0, ff = 1;
    cout << "��ѡ��";
    while(cin >> t){
        switch(t){
            case(1):
                goods_add();          //��Ʒ���
                break;
            case(2):
                stock_list();         //��Ʒ���
                system("pause");
                break;
            case(3):
                stock_value();        //��Ʒ�ܼ�ֵ
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
            Menu_stock();
            cout << "��ѡ��";
        }
    }

    /*---------------����ͳ������-----------------*/
    ofstream file1("stock_value.txt");
    if(!file1){
        cout << "Cannot open output file\n";
    }
    file1 << value << endl;
    file1 << id << endl;
    file1.close();
}

#endif // STOCK_SYSTEM_H_INCLUDED
