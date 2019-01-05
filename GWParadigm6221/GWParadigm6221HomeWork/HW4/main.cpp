#include <iostream>
#include <regex>
using namespace std;
int num=0;
class student{
private:
    string StudentFirstName;
    string StudentLastName;
    string StudentGNoss;
    student* next;
    student* first;
    student* last;
public:
    student();
    void add();
    void add2(string a,string b,string c);
    void del();
    void show();
    void showAll();
    bool check(string a,string b);
    void checkbyLastName();
    void checkbyFirstName();
    void checkbyGID();
    
    
};

student::student()
{
    next=NULL;
    first=NULL;
    last=NULL;
}


void student::add()
{
    student* t = new student;
    student* p = first;
    cout<<"please input student's FirstName : "<<endl;
    cin>>t->StudentFirstName;
    cout<<"please input student's LastName : "<<endl;
    cin>>t->StudentLastName;
    cout<<"please input student's GID : "<<endl;
    cin>>t->StudentGNoss;
    while(p){
        if(p->StudentGNoss==t->StudentGNoss||(p->StudentLastName==t->StudentLastName&&p->StudentFirstName==t->StudentFirstName))
        {
            cout<<"Duplicates in not allowed"<<endl;
            return;
        }
        p=p->next;
    }
    num=num+1;
    if(first==NULL)
    {
        first=last=t;
        
    }
    else
    {
        last->next=t;
        last=t;
    }
}

bool student::check(string a,string b){
    
    regex Input(b);
    
    return regex_search(a, Input);
}

void student::checkbyFirstName(){
    string a;
    cout<<"Please input Firstname!"<<endl;
    cin>>a;
    a = '^' + a;
    student *t=first;
    int count=0;
    for(int i=0;i<num;i++){
        if(check(t->StudentFirstName,a))
        {
            count++;
            cout << "===============================\n";
            cout<<"Student No."<<count<<" :";
            cout<<t->StudentFirstName<<" "<<t->StudentLastName<<endl;
            cout<<"G#: "<<t->StudentGNoss<<endl;
        }
        t=t->next;
    }
    if(count==0)
        cout<<"No result!"<<endl;
}


void student::checkbyLastName(){
    string a;
    cout<<"Please input Lastname!"<<endl;
    cin>>a;
    a = '^' + a;
    student *t=first;
    int count=0;
    for(int i=0;i<num;i++){
        if(check(t->StudentLastName,a))
        {
            count++;
            cout << "===============================\n";
            cout<<"Student No."<<count<<" :";
            cout<<t->StudentFirstName<<" "<<t->StudentLastName<<endl;
            cout<<"G#: "<<t->StudentGNoss<<endl;
        }
        t=t->next;
    }
    if(count==0)
        cout<<"No result!"<<endl;
}

void student::checkbyGID(){
    string a;
    cout<<"Please input G#!"<<endl;
    cin>>a;
    student *t=first;
    int count=0;
    for(int i=0;i<num;i++){
        if(check(t->StudentGNoss,a))
        {
            count++;
            cout << "===============================\n";
            cout<<"Student No."<<count<<" :";
            cout<<t->StudentFirstName<<" "<<t->StudentLastName<<endl;
            cout<<"G#: "<<t->StudentGNoss<<endl;
        }
        t=t->next;
        
    }
    if(count==0)
        cout<<"No result!"<<endl;
}


void student::add2(string a,string b,string c)
{
    student* t = new student;
    student* p = first;
    t->StudentFirstName=a;
    t->StudentLastName=b;
    t->StudentGNoss=c;
    while(p){
        if(p->StudentGNoss==t->StudentGNoss||(p->StudentLastName==t->StudentLastName&&p->StudentFirstName==t->StudentFirstName))
        {
            cout<<"Duplicates in not allowed"<<endl;
            return;
        }
        p=p->next;
    }
    num=num+1;
    if(first==NULL)
    {
        first=last=t;
        
    }
    else
    {
        last->next=t;
        //last=last->next;
        last=t;
    }
}



void student::del(){
    string a;
    cout<<"Please input the student's G# : ";
    cin>>a;
    student *t = first;
    student *p=NULL;
    while(t){
        if(t->StudentGNoss==a)
            break;
        else{
            p=t;
            t=t->next;
        }
    }
    if(!t)
    {
        cout<<"Failed, please check the G# again!"<<endl;
        return;
    }
    if(!p)
    {
        first=first->next;
        cout<<"Delete Succeed!"<<a<<"has been deleted"<<endl;
        delete t;
    }
    else
    {
        p->next=t->next;
        cout<<"Delete Succeed!"<<a<<"has been deleted"<<endl;
        delete t;
    }
    
    num--;
}


void student::showAll()
{
    cout<<"Students Set:"<<endl;
    student *t = first;
    for(int i=0;i<num;i++){
        cout << "===============================\n";
        cout<<"Student No."<<i+1<<" :";
        cout<<t->StudentFirstName<<" "<<t->StudentLastName<<endl;
        cout<<"G#: "<<t->StudentGNoss<<endl;
        t=t->next;
    }
}

void showMenu()
{
    cout << "                               \n";
    cout << "===============================\n";
    cout << "      Student handle program\n\n";
    cout << "      1.Print the whole student set\n";
    cout << "      2.Add a new student\n";
    cout << "      3.Search the students with the firstname\n";
    cout << "      4.Search the students with the lastname\n";
    cout << "      5.Search the students with the G#\n";
    cout << "      6.Remove a student by G#\n";
    cout << "      0.Exit\n";
    cout << "===============================\n";
    cout << "                               \n";
}
int main(){
    char *FirstName[10]={"Tom","Bob","Jack","Rick","Harry","Aaron","Abell","Abdul","Hal","Handson"};
    char *LastName[10]={"Smith","Jones","James","Jackson","Consin","Granmes","Lee","Hardern","Tylor","Brown"};
    char *GID[10]={"G32133213","G23134324","G12353244","G52345678","G23426544","G23426122","G42367432","G42642152","G42633452","G21345675"};
    student school;
    string aaa;
    string bbb;
    string ccc;
    for (int i=0;i<10;i++){
        aaa=FirstName[i];
        bbb=LastName[i];
        ccc=GID[i];
        school.add2(aaa,bbb,ccc);
    }
    int h;
    while(1){
        showMenu();
        cout << "Please input the number corresponding with instructions : ";
        cin >>h;
        cout<<endl;
        switch (h) {
            case 1:
                school.showAll();
                break;
            case 2:
                school.add();
                break;
            case 3:
                school.checkbyFirstName();
                break;
            case 4:
                school.checkbyLastName();
                break;
            case 5:
                school.checkbyGID();
                break;
            case 6:
                school.del();
                break;
            case 0:
                return 0;
            default:cout<<"\nInvalid Input, please try again。"<<endl;
                break;
        }
    }
    
    
    return 0;
}

