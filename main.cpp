#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "Menu.h"
#include "Pet_system.h"
#include "User_system.h"
#include "Bill_system.h"
#include "Stock_system.h"

using namespace std;

int main()
{
    int n, ff = 0;
    while(true){
        system("cls");
        Menu_center();
        cout << "����������ִ�в�����Ӧ����ţ�";
        cin >> n;
        system("cls");
        switch(n){
            case(1):
                pet_sys();
                break;
            case(2):
                user_sys();
                break;
            case(3):
                bill_sys();
                break;
            case(4):
                stock_sys();
                break;
            case(0):
                ff = 1;
                break;
            default:
                Menu_center();
                cout << "��������Ƿ������������룺";
        }
        if(ff) break;
    }

    return 0;
}
