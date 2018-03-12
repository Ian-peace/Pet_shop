#ifndef PET_SYSTEM_H_INCLUDED
#define PET_SYSTEM_H_INCLUDED


using namespace std;

class Pet           //宠物类
{
private:
    int id, age, host_id;
    string name, category;
    char sex;
public:
    Pet();                                                             //重载构造函数
    Pet(string n, char s, int a, int hostID, int flag, int id_flag);   //构造函数
    int get_id();
    int get_age();
    int get_host_id();
    string get_name();
    string get_category();
    char get_sex();
};

Pet::Pet(string n, char s, int a, int hostID, int flag, int id_flag)    //定义构造函数
{
    name = n;
    sex = s;
    age = a;
    host_id = hostID;
    id = id_flag + 1;

    if(flag == 1) category = "犬类";
    else if (flag == 2) category = "猫类";
    else if (flag == 3) category = "鸟类";
    else category = "其他";
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


int CountLines(char *filename)                           //统计文本行数
{
    ifstream ReadFile;
    int n=0;
    string tmp;
    ReadFile.open(filename,ios::in);//ios::in 表示以只读的方式读取文件

    if(ReadFile.eof()) return 0;
    if(ReadFile.fail())//文件打开失败:返回0
    {
        return 0;
    }
    else//文件存在
    {
        while(getline(ReadFile,tmp,'\n'))
        {
            n++;
        }
        ReadFile.close();
        return n;
    }
}

string ReadLine(char *filename,int line)                 //读取指定行内容
{
    int lines,i=0;
    string temp;
    fstream file;
    file.open(filename,ios::in);
    lines=CountLines(filename);

    if(line<=0)
    {
        return "Error 1: 行数错误，不能为0或负数。";
    }
    if(file.fail())
    {
        return "Error 2: 文件不存在。";
    }
    if(line>lines)
    {
        return "Error 3: 行数超出文件长度。";
    }
    while(getline(file,temp)&&i<line-1)
    {
        i++;
    }
    file.close();
    return temp;
}


void DeleteLine(char *filename, int line)                //删除特定行内容
{
    ifstream file(filename);
    string str;
    int cou = 1;
    ofstream outfile("test.txt", ios::out | ios::trunc);
    while (!file.eof()) {
        getline(file, str);
        if (str == "" && cou != line) cout << endl;
        else if (cou != line) //如果要修改内容就在这修改line的内容,再存到文件中
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
    system("del test.txt");//删除中间文件
}


string n;
char s;
int a, hostID;

void Pet_add()                                           //添加宠物信息
{
    cout << "请输入宠物姓名：";
    cin >> n;
    cout << "宠物性别：(f/m)";
    cin >> s;
    while(s != 'f' && s != 'm'){
        cout << "请重新输入宠物性别：";
        cin >> s;
    }
    cout << "宠物年龄：";
    cin >> a;
    cout << "宠物所属主人ID：";
    cin >> hostID;
}


void Pet_list()                                          //浏览宠物信息
{
    system("cls");
    int len = CountLines("Pet.txt");
    for(int i = 1; i <= len; i++){
        cout << ReadLine("Pet.txt", i) << endl;
    }
}

void Pet_delete()                                        //删除宠物信息
{
    Pet_list();
    int petid, le;
    le = CountLines("Pet.txt");
    cout << "\n请输入要删除宠物的所在行数(0<n<=" << le << ")(输入-1返回上一菜单)：";
    cin >> petid;
    if(petid == -1) return;
    while(petid <= 0 || petid > le){
        cout << "超出范围，请重新输入：";
        cin >> petid;
        if(petid == -1) return;
    }
    DeleteLine("Pet.txt", petid);
}



void pet_sys()                                   //宠物系统
{
    int t;
    Menu_pet();
    int f = 0, ff = 1;
    cout << "请选择：";
    while(cin >> t){
        switch(t){
            case(1):
            {
                int cate_flag;                //宠物种类标记
                Menu_pet_category();
                cout << "请选择：";
                cin >> cate_flag;

                string  line;
                char str[1000];
                int id_flag, j = 0;               //宠物id标记
                line = ReadLine("Pet.txt", CountLines("Pet.txt"));
                if(CountLines("Pet.txt") == 0) id_flag = 0;
                else{
                    for(int i = 0; i < line.length(); i++){
                        if(line[i] == '\t') break;
                        else if(line[i] >= '0' && line[i] <= '9') str[j++] = line[i];
                    }
                    id_flag = atoi(str);                     //获取现有用户最大id
                }
                Pet_add();
                Pet pet(n, s, a, hostID, cate_flag, id_flag);        //建立宠物对象

                ofstream fout("Pet.txt", ios::app|ios::in);          //输出到文件
                if(!fout){
                    cout << "Cannot open output file\n";
                }
                else{
                    fout << "宠物编号：" << pet.get_id() << "\t宠物种类：" <<  pet.get_category() << "\t宠物名字：" <<  pet.get_name()
                         << "\t宠物年龄：" << pet.get_age() << "\t宠物性别：" << pet.get_sex()<< "\t主人编号："<< pet.get_host_id() << endl;
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
                cout << "您的输入非法，请重新输入：";
                ff = 0;
        }

        if(f) break;

        if(ff){
            system("cls");
            Menu_pet();
            cout << "请选择：";
        }
    }
}

#endif // PET_SYSTEM_H_INCLUDED
