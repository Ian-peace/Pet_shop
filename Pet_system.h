#ifndef PET_SYSTEM_H_INCLUDED
#define PET_SYSTEM_H_INCLUDED


using namespace std;

class Pet           //������
{
private:
    int id, age, host_id;
    string name, category;
    char sex;
public:
    Pet();                                                             //���ع��캯��
    Pet(string n, char s, int a, int hostID, int flag, int id_flag);   //���캯��
    int get_id();
    int get_age();
    int get_host_id();
    string get_name();
    string get_category();
    char get_sex();
};

Pet::Pet(string n, char s, int a, int hostID, int flag, int id_flag)    //���幹�캯��
{
    name = n;
    sex = s;
    age = a;
    host_id = hostID;
    id = id_flag + 1;

    if(flag == 1) category = "Ȯ��";
    else if (flag == 2) category = "è��";
    else if (flag == 3) category = "����";
    else category = "����";
}

int Pet::get_id()
{
    return id;
}

int Pet::get_age()
{
    return age;
}

int Pet::get_host_id()
{
    return host_id;
}

string Pet::get_name()
{
    return name;
}

string Pet::get_category()
{
    return category;
}

char Pet::get_sex()
{
    return sex;
}


int CountLines(char *filename)                           //ͳ���ı�����
{
    ifstream ReadFile;
    int n=0;
    string tmp;
    ReadFile.open(filename,ios::in);//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�

    if(ReadFile.eof()) return 0;
    if(ReadFile.fail())//�ļ���ʧ��:����0
    {
        return 0;
    }
    else//�ļ�����
    {
        while(getline(ReadFile,tmp,'\n'))
        {
            n++;
        }
        ReadFile.close();
        return n;
    }
}

string ReadLine(char *filename,int line)                 //��ȡָ��������
{
    int lines,i=0;
    string temp;
    fstream file;
    file.open(filename,ios::in);
    lines=CountLines(filename);

    if(line<=0)
    {
        return "Error 1: �������󣬲���Ϊ0������";
    }
    if(file.fail())
    {
        return "Error 2: �ļ������ڡ�";
    }
    if(line>lines)
    {
        return "Error 3: ���������ļ����ȡ�";
    }
    while(getline(file,temp)&&i<line-1)
    {
        i++;
    }
    file.close();
    return temp;
}


void DeleteLine(char *filename, int line)                //ɾ���ض�������
{
    ifstream file(filename);
    string str;
    int cou = 1;
    ofstream outfile("test.txt", ios::out | ios::trunc);
    while (!file.eof()) {
        getline(file, str);
        if (str == "" && cou != line) cout << endl;
        else if (cou != line) //���Ҫ�޸����ݾ������޸�line������,�ٴ浽�ļ���
            outfile << str << endl;
        cou++;
    }
    outfile.close();
    file.close();
    ofstream outfile1(filename, ios::out | ios::trunc);
    fstream file1("test.txt");
    getline(file1, str);
    outfile1 << str;
    while (!file1.eof()) {
        getline(file1, str);
        outfile1 << endl << str;
    }
    outfile1.close();
    file1.close();
    system("del test.txt");//ɾ���м��ļ�
}


string n;
char s;
int a, hostID;

void Pet_add()                                           //��ӳ�����Ϣ
{
    cout << "���������������";
    cin >> n;
    cout << "�����Ա�(f/m)";
    cin >> s;
    while(s != 'f' && s != 'm'){
        cout << "��������������Ա�";
        cin >> s;
    }
    cout << "�������䣺";
    cin >> a;
    cout << "������������ID��";
    cin >> hostID;
}


void Pet_list()                                          //���������Ϣ
{
    system("cls");
    int len = CountLines("Pet.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("Pet.txt", i) << endl;
    }
}

void Pet_delete()                                        //ɾ��������Ϣ
{
    Pet_list();
    int petid, le;
    le = CountLines("Pet.txt");
    cout << "\n������Ҫɾ���������������(0<n<=" << le << ")(����-1������һ�˵�)��";
    cin >> petid;
    if(petid == -1) return;
    while(petid <= 0 || petid > le){
        cout << "������Χ�����������룺";
        cin >> petid;
        if(petid == -1) return;
    }
    DeleteLine("Pet.txt", petid);
}



void pet_sys()                                   //����ϵͳ
{
    int t;
    Menu_pet();
    int f = 0, ff = 1;
    cout << "��ѡ��";
    while(cin >> t){
        switch(t){
            case(1):
            {
                int cate_flag;                //����������
                Menu_pet_category();
                cout << "��ѡ��";
                cin >> cate_flag;

                string  line;
                char str[1000];
                int id_flag, j = 0;               //����id���
                line = ReadLine("Pet.txt", CountLines("Pet.txt"));
                if(CountLines("Pet.txt") == 0) id_flag = 0;
                else{
                    for(int i = 0; i < line.length(); i++){
                        if(line[i] == '\t') break;
                        else if(line[i] >= '0' && line[i] <= '9') str[j++] = line[i];
                    }
                    id_flag = atoi(str);                     //��ȡ�����û����id
                }
                Pet_add();
                Pet pet(n, s, a, hostID, cate_flag, id_flag);        //�����������

                ofstream fout("Pet.txt", ios::app|ios::in);          //������ļ�
                if(!fout){
                    cout << "Cannot open output file\n";
                }
                else{
                    fout << "�����ţ�" << pet.get_id() << "\t�������ࣺ" <<  pet.get_category() << "\t�������֣�" <<  pet.get_name()
                         << "\t�������䣺" << pet.get_age() << "\t�����Ա�" << pet.get_sex()<< "\t���˱�ţ�"<< pet.get_host_id() << endl;
                    fout.close();
                }
                break;
            }
            case(2):
                Pet_delete();
                break;
            case(3):
                Pet_list();
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
            Menu_pet();
            cout << "��ѡ��";
        }
    }
}

#endif // PET_SYSTEM_H_INCLUDED
