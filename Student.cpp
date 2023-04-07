#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
// Student class with its properties
class student
    {
        int r_no;
        char name[50];
        int e_marks, m_marks, s_marks, l2_marks, cs_marks;
        double avg;
        char grade;
        public:void getdata();
        void showdata() const;
        void calculate();
        int retrollno() const;
    }; 
    //calculate the average of the marks and the grade
void student::calculate()
    {
        avg=(e_marks+m_marks+s_marks+l2_marks+cs_marks)/5.0;
        if(avg>=90)grade='A';
        else if(avg>=75)grade='B';
        else if(avg>=50)grade='C';
        else grade='F';
    }
   //get the input from user  
void student::getdata()
    {
        cout<<"\nRoll Number: ";
        cin>>r_no;
        cout<<"\n\nStudent Name: ";
        cin.ignore();
        cin.getline(name,50);
        cout<<"\nMarks out of 100";
        cout<<"\nEnglish: ";
        cin>>e_marks;
        cout<<"\nMath:  ";
        cin>>m_marks;
        cout<<"\nScience:  ";
        cin>>s_marks;
        cout<<"\nBiology:  ";
        cin>>l2_marks;cout<<"\nComputer science:  ";
        cin>>cs_marks;
        calculate();
    }
    //function to display the student details
void student::showdata() const
    {
        cout<<"\nRoll number : "<<r_no;
        cout<<"\nName : "<<name;
        cout<<"\nEnglish : "<<e_marks;
        cout<<"\nMaths : "<<m_marks;
        cout<<"\nScience : "<<s_marks;
        cout<<"\nBiology : "<<l2_marks;
        cout<<"\nComputer Science :"<<cs_marks;
        cout<<"\nAverage Marks :"<<avg;
        cout<<"\nGrade :"<<grade;
    }
int  student::retrollno() const
    {
        return r_no;
    }
//function declaration
void create_student();
void display_sp(int);//display particular record
void display_all(); // display all records
void delete_student(int);//delete particular record
void change_student(int);//edit particular record
//MAIN 
int main()
    {
        char ch;
        cout<<setprecision(2); 
        do
            {
                char ch;
                int num;
                system("cls");
                cout<<"\n\n\n\tMENU";
                cout<<"\n\n\t1. Create Student Record";
                cout<<"\n\n\t2. Search Student Record";
                cout<<"\n\n\t3. Display all Students Records ";
                cout<<"\n\n\t4. Delete Student Record";
                cout<<"\n\n\t5. Modify Student Record";
                cout<<"\n\n\t6. Exit";
                cout<<"\n\n\tEnter your Choice: ";
                cin>>ch;
                system("cls");
                switch(ch)
                    {
                        case '1': create_student(); 
                                  break;
                        case '2': cout<<"\n\n\tRoll Number ";
                                  cin>>num;
                                  display_sp(num); 
                                  break;
                        case '3': display_all(); 
                                  break;
                        case '4': cout<<"\n\n\tRoll Number: "; 
                                  cin>>num;
                                  delete_student(num);
                                  break;
                        case '5': cout<<"\n\n\tRoll Number "; 
                                  cin>>num;change_student(num);
                                  break;
                        case '6': cout<<"Thank you!";
                                  exit(0);
                    }
            }
            while(ch!='6');
            return 0;
        }
    //write student details to file
    void create_student()
        {
            student stud;
            ofstream oFile;
            oFile.open("student.dat",ios::binary|ios::app);
            stud.getdata();
            oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
            oFile.close();    
            cout<<"\n\nStudent record Created ";
            cin.ignore();
            cin.get();
            }
            // read file records
            void display_all()
                {
                    student stud;
                    ifstream inFile;
                    inFile.open("student.dat",ios::binary);
                    if(!inFile)
                        {
                            cout<<"File does not exist !! Press any Key to exit";
                            cin.ignore();
                            cin.get();
                            return;
                        }
                        cout<<"\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
                        while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
                            {
                                stud.showdata();
                                cout<<"\n\n-*-*-*-\n";
                            }
                            inFile.close();
                            cin.ignore();
                            cin.get();
                            }
                            //based on the input roll number read data from file
                        void display_sp(int n)
                            {
                                student stud;
                                ifstream iFile;
                                iFile.open("student.dat",ios::binary);
                                if(!iFile)
                                {
                                    cout<<"File does not exist... Press any Key to exit";
                                    cin.ignore();
                                    cin.get();
                                    return;
                                    }
                                    bool flag=false;
                                    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
                                    {
                                        if(stud.retrollno()==n)
                                            {  
                                                stud.showdata();
                                                flag=true;
                                            }
                                    }
                                    iFile.close();
                                    
                                    if(flag==false)
                                    cout<<"\n\nRecord does not exist";
                                    cin.ignore();
                                    cin.get();
                            }
                            // modify record for a roll number
                            void change_student(int n)
                            {
                                bool found=false;
                                student stud;
                                fstream fl;
                                fl.open("student.dat",ios::binary|ios::in|ios::out);
                                if(!fl)
                                {
                                    cout<<"File does not exist. Press any Key to exit...";
                                    cin.ignore();
                                    cin.get();
                                    return;
                                }     
                                while(!fl.eof() && found==false)
                                    {
                                        fl.read(reinterpret_cast<char *> (&stud), sizeof(student));
                                        if(stud.retrollno()==n)
                                            {
                                                stud.showdata();
                                                cout<<"\nEnter New student details:"<<endl;
                                                stud.getdata();    
                                                int pos=(-1)*static_cast<int>(sizeof(stud));    
                                                fl.seekp(pos,ios::cur);    
                                                fl.write(reinterpret_cast<char *> (&stud), sizeof(student));    
                                                cout<<"\n\n\t Record Updated";    
                                                found=true;
                                                }
                                    }
                                    fl.close();
                                    if(found==false)
                                        cout<<"\n\n Record Not Found ";
                                    cin.ignore();cin.get();
                                }
                                //delete record with particular roll number
                                void delete_student(int n)
                                {
                                    student stud;
                                    ifstream iFile;
                                    iFile.open("student.dat",ios::binary);
                                    if(!iFile)
                                    {
                                        cout<<"File does not exist... Press any Key to exit...";
                                        cin.ignore();
                                        cin.get();
                                        return;
                                        }
                                        ofstream oFile;
                                        oFile.open("Temp.dat",ios::out);
                                        iFile.seekg(0,ios::beg);
                                        while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
                                        {
                                            if(stud.retrollno()!=n)
                                            {
                                                oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
                                            }
                                        }
                                        oFile.close();iFile.close();remove("student.dat");
                                        rename("Temp.dat","student.dat");
                                        cout<<"\n\n\tRecord Deleted! ..";
                                        cin.ignore();
                                        cin.get();
                                    }
