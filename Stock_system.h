#ifndef STOCK_SYSTEM_H_INCLUDED
#define STOCK_SYSTEM_H_INCLUDED

double value;     //库存总价值
int id;           //库存物品id

void goods_add()                         //物品添加
{
    string name;
    double price;
    int amount;

    cout << "物品名称：";
    cin >> name;
    cout << "价格：";
    cin >> price;
    cout << "数量：";
    cin >> amount;

    /*----------------输入到文件-------------------------*/
    ofstream fout("stock.txt", ios::app|ios::in);
    if(!fout){
        cout << "Cannot open output file\n";
    }
    else{
        fout << "编号：" << ++id << endl;
        fout << "名称：" << name << endl;
        fout << "价格：" << price << endl;
        fout << "数量：" << amount << endl;
        fout << endl;
        fout.close();
    }
    value += price*amount;
}

void stock_value()                      //物品总价值
{
    cout << value << endl;
}

void stock_list()                       //物品浏览
{
    system("cls");
    int len = CountLines("stock.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("stock.txt", i) << endl;
    }
}

void stock_sys()                                   //账单系统
{
    /*----------------读取统计数据-------------*/

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

    /*------------------开始------------------*/
    int t;
    Menu_stock();
    int f = 0, ff = 1;
    cout << "请选择：";
    while(cin >> t){
        switch(t){
            case(1):
                goods_add();          //物品添加
                break;
            case(2):
                stock_list();         //物品浏览
                system("pause");
                break;
            case(3):
                stock_value();        //物品总价值
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
            Menu_stock();
            cout << "请选择：";
        }
    }

    /*---------------保存统计数据-----------------*/
    ofstream file1("stock_value.txt");
    if(!file1){
        cout << "Cannot open output file\n";
    }
    file1 << value << endl;
    file1 << id << endl;
    file1.close();
}

#endif // STOCK_SYSTEM_H_INCLUDED
