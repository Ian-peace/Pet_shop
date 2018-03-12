#ifndef USER_SYSTEM_H_INCLUDED
#define USER_SYSTEM_H_INCLUDED


using namespace std;

class User            //�û���
{
private:
    int id, pet_id;
    string name, tel;
    char sex;
public:
    User(string n, char s, int petid, int id_flag, string t);   //���캯��
    int get_id();
    int get_pet_id();
    string get_tel();
    string get_name();
    char get_sex();
};

User::User(string n, char s, int petid, int id_flag, string t)    //���幹�캯��
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

void User_add()                                           //����û���Ϣ
{
    cout << "�������û�������";
    cin >> na;
    cout << "�û��Ա�(f/m)";
    cin >> se;
    while(se != 'f' && se != 'm'){
        cout << "�����������û��Ա�";
        cin >> se;
    }
    cout << "�û���ϵ�绰��";
    cin >> tele;
    cout << "�û�����ID��";
    cin >> petid;
    cout << "�û���Ա����";
    cin >> l;
}


void User_list()                                          //����û���Ϣ
{
    system("cls");
    int len = CountLines("User.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("User.txt", i) << endl;
    }
}


void User_delete()                                        //ɾ���û���Ϣ
{
    User_list();
    int Userid, le;
    le = CountLines("User.txt");
    cout << "\n������Ҫɾ���û�����������(0<n<=" << le << ")(����-1������һ�˵�)��";
    cin >> Userid;
    if(Userid == -1) return;
    while(Userid <= 0 || Userid > le){
        cout << "������Χ�����������룺";
        cin >> Userid;
        if(Userid == -1) return;
    }
    DeleteLine("User.txt", Userid);
}



void user_sys()                                   //�û�ϵͳ
{
    int t;
    Menu_user();
    int f = 0, ff = 1;
    cout << "��ѡ��";
    while(cin >> t){
        switch(t){
            case(1):
            {
                string  line;
                char str[1000];
                int id_flag, j = 0;               //�û�id���
                line = ReadLine("User.txt", CountLines("User.txt"));
                if(CountLines("User.txt") == 0) id_flag = 0;
                else{
                    for(int i = 0; i < line.length(); i++){
                        if(line[i] == '\t') break;
                        else if(line[i] >= '0' && line[i] <= '9') str[j++] = line[i];
                    }
                    id_flag = atoi(str);                     //��ȡ�����û����id
                }

                User_add();
                member User(na, se, petid, id_flag, tele, l);        //�����û�����

                ofstream fout("User.txt", ios::app|ios::in);          //������ļ�
                if(!fout){
                    cout << "Cannot open output file\n";
                }
                else{
                    fout << "�û���ţ�" << User.get_id() <<  "\t�û����֣�" << User.get_name()
                         << "\t�û��Ա�" << User.get_sex()<< "\t�û������ţ�" << User.get_pet_id()
                         << "\t�û���Ա����" << User.display() << endl;
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
                cout << "��������Ƿ������������룺";
                ff = 0;
        }

        if(f) break;

        if(ff){
            system("cls");
            Menu_user();
            cout << "��ѡ��";
        }
    }
}

#endif // USER_SYSTEM_H_INCLUDED
