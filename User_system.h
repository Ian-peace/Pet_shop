#ifndef USER_SYSTEM_H_INCLUDED
#define USER_SYSTEM_H_INCLUDED


using namespace std;

class User            //用户类
{
private:
    int id, pet_id;
    string name, tel;
    char sex;
public:
    User(string n, char s, int petid, int id_flag, string t);   //构造函数
    int get_id();
    int get_pet_id();
    string get_tel();
    string get_name();
    char get_sex();
};

User::User(string n, char s, int petid, int id_flag, string t)    //定义构造函数
{
    name = n;
    sex = s;
    pet_id = petid;
    id = id_flag + 1;
    tel = t;
}

int User::get_id()
{
    return id;
}


int User::get_pet_id()
{
    return pet_id;
}

char User::get_sex()
{
    return sex;
}

string User::get_name()
{
    return name;
}

string User::get_tel()
{
    return tel;
}


class member:public User
{
private:
    int leaguer_grade;
public:
    member(string n, char s, int petid, int id_flag, string t, int l) : User(n,s,petid,id_flag,t)
    {
        leaguer_grade = l;
    }
    int display();
};

int member::display()
{
    return leaguer_grade;
}


string na, tele;
char se;
int petid, l;

void User_add()                                           //添加用户信息
{
    cout << "请输入用户姓名：";
    cin >> na;
    cout << "用户性别：(f/m)";
    cin >> se;
    while(se != 'f' && se != 'm'){
        cout << "请重新输入用户性别：";
        cin >> se;
    }
    cout << "用户联系电话：";
    cin >> tele;
    cout << "用户宠物ID：";
    cin >> petid;
    cout << "用户会员级别：";
    cin >> l;
}


void User_list()                                          //浏览用户信息
{
    system("cls");
    int len = CountLines("User.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("User.txt", i) << endl;
    }
}


void User_delete()                                        //删除用户信息
{
    User_list();
    int Userid, le;
    le = CountLines("User.txt");
    cout << "\n请输入要删除用户的所在行数(0<n<=" << le << ")(输入-1返回上一菜单)：";
    cin >> Userid;
    if(Userid == -1) return;
    while(Userid <= 0 || Userid > le){
        cout << "超出范围，请重新输入：";
        cin >> Userid;
        if(Userid == -1) return;
    }
    DeleteLine("User.txt", Userid);
}



void user_sys()                                   //用户系统
{
    int t;
    Menu_user();
    int f = 0, ff = 1;
    cout << "请选择：";
    while(cin >> t){
        switch(t){
            case(1):
            {
                string  line;
                char str[1000];
                int id_flag, j = 0;               //用户id标记
                line = ReadLine("User.txt", CountLines("User.txt"));
                if(CountLines("User.txt") == 0) id_flag = 0;
                else{
                    for(int i = 0; i < line.length(); i++){
                        if(line[i] == '\t') break;
                        else if(line[i] >= '0' && line[i] <= '9') str[j++] = line[i];
                    }
                    id_flag = atoi(str);                     //获取现有用户最大id
                }

                User_add();
                member User(na, se, petid, id_flag, tele, l);        //建立用户对象

                ofstream fout("User.txt", ios::app|ios::in);          //输出到文件
                if(!fout){
                    cout << "Cannot open output file\n";
                }
                else{
                    fout << "用户编号：" << User.get_id() <<  "\t用户名字：" << User.get_name()
                         << "\t用户性别：" << User.get_sex()<< "\t用户宠物编号：" << User.get_pet_id()
                         << "\t用户会员级别：" << User.display() << endl;
                    fout.close();
                }
                break;
            }
            case(2):
                User_delete();
                break;
            case(3):
                User_list();
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
            Menu_user();
            cout << "请选择：";
        }
    }
}

#endif // USER_SYSTEM_H_INCLUDED
