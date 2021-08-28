//******************************************************
// PROJECT ON STUDENT EXAMINATION MANAGEMENT
//******************************************************
// MADE BY-VARUN GUPTA
//******************************************************

//HEADER FILES USED
#include<fstream.h>
#include<iomanip.h>
#include<process.h>
#include<stdio.h>
#include<conio.h>

//**********************CLASS STARTS**************************

class student
{
 int rollno;
 char name[50];
 int p_marks, c_marks, m_marks, e_marks, cs_marks;
 float per;
 char grade;
 void calculate(); //function to calculate grade
 public:
 void getdata();   //function to accept data from user
 void showdata();  //function to show data on screen
 void show_tabular();
 int retrollno();  //function that return the value of roll number
};

//**********************CLASS ENDS HERE******************************
//**********************FUNCTION TO ASSIGN GRADE*********************

 void student::calculate()
 {
  per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5;
  if(per>=90)
  grade='A';
  else if(per>=80)
  grade='B';
  else if(per>=70)
  grade='C';
  else if(per>=60)
  grade='D';
  else if(per>=50)
  grade='E';
  else
  grade='F';
 }

 //*********************FUNCTION TO ENTER THE DATA*******************

 void student::getdata()
 {
  cout<<"\nEnter The roll number of student: ";
  cin>>rollno;
  cout<<"\n\nEnter The Name of student: ";
  gets(name);
  cout<<"\nEnter The marks in physics out of 100: ";
  cin>>p_marks;
  cout<<"\nEnter The marks in chemistry out of 100: ";
  cin>>c_marks;
  cout<<"\nEnter The marks in maths out of 100: ";
  cin>>m_marks;
  cout<<"\nEnter The marks in english out of 100: ";
  cin>>e_marks;
  cout<<"\nEnter The marks in computer science out of 100: ";
  cin>>cs_marks;
  calculate();
 }

 //*********************FUNCTON TO DISPLAY DATA*********************

 void student::showdata()
 {
  cout<<"\nRoll number of student: "<<rollno;
  cout<<"\nName of student: "<<name;
  cout<<"\nMarks in Physics: "<<p_marks;
  cout<<"\nMarks in Chemistry: "<<c_marks;
  cout<<"\nMarks in Maths: "<<m_marks;
  cout<<"\nMarks in English: "<<e_marks;
  cout<<"\nMarks in Computer Science:"<<cs_marks;
  cout<<"\nPercentage of student is:"<<per;
  cout<<"\nGrade of student is:"<<grade;
 }

 //*********************FUNCTION FOR CLASS STATISTICS***************

 void student::show_tabular()
 {
  cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<p_marks<<setw(4);
  cout<<c_marks<<setw(4)<<m_marks<<setw(4);
  cout<<e_marks<<setw(4)<<cs_marks<<setw(6)<<per<<setw(6)<<" "<<grade<<endl;
 }

 //*********************FUNCTION THAT RETURN ROLL NO.**************

 int  student::retrollno()
 {
  return rollno;
 }

 //######################################################################
 //                          FUNCTIONS PROTOTYPES
 //######################################################################

 void write_student();//write the record in binary file
 void display_all();//read all records from binary file
 void display_sp(int);//accept rollno and read record from binary file
 void modify_student(int);//accept rollno and update record of binary file
 void delete_student(int);//accept rollno and delete unwanted records from binary file
 void class_result(); //display all records in systematic manner from binary file
 void result(); //display result menu
 void intro();//display welcome screen
 void entry_menu(); //display entry menu on screen

 //******************************************************************
 //                            MAIN FUNCTION
 //******************************************************************

 void main()
 {
  int ch;
  clrscr();
  intro();
  do
  {
   clrscr();
   cout<<"\n\n\n\tMAIN MENU";
   cout<<"\n\n\t01. RESULT MENU";
   cout<<"\n\n\t02. ENTRY/EDIT/DISPLAY MENU";
   cout<<"\n\n\t03. EXIT";
   cout<<"\n\n\tPlease Select Your Option (1-3): ";
   cin>>ch;
   clrscr();
   switch(ch)
   {
    case 1: result();  //function call of result
	   break;
    case 2: entry_menu();   //function call of entry_menu
	   break;
    case 3: exit(0);        //program will exit
	   break;
    default :cout<<"\a";
   }
  }while(ch!='3');
 }
 //*********************************************************************
 //                       END OF MAIN FUNCTION
 //*********************************************************************
 //              FUNCTION TO WRITE DATA INTO THE FILE
 //*********************************************************************

  void write_student()
  {
   student st;
   ofstream outFile;
   outFile.open("student.dat",ios::binary|ios::app);
   st.getdata();
   outFile.write((char *) &st, sizeof(student));
   outFile.close();
   cout<<"\n\nStudent record Has Been Created!! ";
   getch();
  }

  //#####################################################################
  //                   FUNCTION TO DISPLAY ALL RECORDS
  //#####################################################################
  void display_all()
  {
   student st;
   ifstream inFile;
   inFile.open("student.dat",ios::binary);
   if(!inFile)
   {
    cout<<"File could not be open !! Press any Key...";
   }
   cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!\n\n";
   while(inFile.read((char *) &st, sizeof(student)))
   {
    st.showdata();
    cout<<"\n\n====================================\n";
   }
   inFile.close();
   getch();
  }

  //*********************************************************************
  //              FUNCTION TO DISPLAY SPECIFIC RECORD
  //*********************************************************************

   void display_sp(int n)
   {
    student st;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
     cout<<"File could not be open !! Press any Key...";
    }
    int flag=0;
    while(inFile.read((char *) &st, sizeof(student)))
    {
     if(st.retrollno()==n)
     {
      st.showdata();
      flag=1;
      getch();
     }
    }
    inFile.close();
    if(flag==0)
    cout<<"\n\nRecord not exist!!";
   }

   //*************************************************************
   //FUNCTION TO MODIFY A SPECIFIC RECORD
   //*************************************************************

   void modify_student(int n)
   {
    int found=0;
    student st;
    fstream File;
    File.open("student.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
     cout<<"File could not be open !! Press any Key...";
    }
    while(File.read((char *) &st, sizeof(student)) && found==0)
    {
     if(st.retrollno()==n)
     {
      st.showdata();
      cout<<"\n\nPlease Enter The New Details of student"<<endl;
      st.getdata();
      int pos=(-1)*sizeof(st);
      File.seekp(pos,ios::cur);
      File.write((char *) &st, sizeof(student));
      cout<<"\n\n\t Record Updated!!";
      found=1;
      getch();
     }
    }
    File.close();
    if(found==0)
    cout<<"\n\n Record Not Found!! ";
   }

    //#################################################################
    //FUNCTION TO DELETE A SPECIFIC RECORD
    //#################################################################

    void delete_student(int n)
    {
     student st;
     ifstream inFile;
     inFile.open("student.dat",ios::binary);
     if(!inFile)
     {
      cout<<"File could not be open !! Press any Key...";
     }
     ofstream outFile;
     outFile.open("Temp.dat",ios::out);
     inFile.seekg(0,ios::beg);
     while(inFile.read((char *) &st, sizeof(student)))
     {
      if(st.retrollno()!=n)
      {
       outFile.write((char *) &st, sizeof(student));
      }
     }
     outFile.close();
     inFile.close();
     remove("student.dat");
     rename("Temp.dat","student.dat");
     cout<<"\n\n\tRecord Deleted!!";
     getch();
    }

    //***************************************************************
    //FUNCTION TO DISPLAY ALL STUDENT GRADE REPORT OR CLASS STATICS
    //****************************************************************

     void class_result()
     {
      student st;
      ifstream inFile;
      inFile.open("student.dat",ios::binary);
      if(!inFile)
      {
       cout<<"File could not be open !! Press any Key...";
      }
      cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
      cout<<"==========================================================\n";
      cout<<"R.No  Name           P   C   M   E   CS %   Grade"<<endl;
      cout<<"==========================================================\n";
      while(inFile.read((char *) &st, sizeof(student)))
      {
       st.show_tabular();
       getch();
      }
      inFile.close();
     }

     //************************************************************
     //              FUNCTION TO DISPLAY RESULT MENU
     //************************************************************
      void result()
      {
       int ch;
       int rno;
       cout<<"\n\n\n\tRESULT MENU";
       cout<<"\n\n\n\t1. Class Result";
       cout<<"\n\n\t2. Student Report Card";
       cout<<"\n\n\t3. Back to Main Menu";
       cout<<"\n\n\n\tEnter Choice (1/2/3): ";
       cin>>ch;
       clrscr();
       switch(ch)
       {
	case 1:class_result(); break;
	case 2:cout<<"\n\n\tEnter Roll Number Of Student : ";
		  cin>>rno;
		display_sp(rno); break;
	default :cout<<"\a";
       }
      }

      //##################################################################
      //FUNCTION FOR THE WELCOME SCREEN
      //##################################################################

      void intro()
      {
       cout<<endl;
       cout<<"--------------------------------------------------------------";
       cout<<"--------------------------------------------------------------";
       cout<<"------------------------------------";
		 cout<<"\n\n\n\t\t\t\t      STUDENT";
		 cout<<"\n\t\t\t\t      -------";
		 cout<<"\n\t\t\t\tEXAMINATION MANAGEMENT";
		 cout<<"\n\t\t\t\t---------------------";
		 cout<<"\n\t\t\t\t      PROJECT";
		 cout<<"\n\t\t\t\t      -------";
		 cout<<"\n\n\n\tMADE BY: VARUN GUPTA";
		 cout<<"\n\n\tCOLLEGE: MERI COLLEGE OF ENGINEERING AND TECHNOLOGY";
		 cout<<"\n\n\tUNIVERSITY: MAHARSHI DAYANAND UNIVERSITY";
		 cout<<"\n\n\n\n--------------------------------------------------";
		 cout<<"--------------------------------------------------------------";
		 cout<<"------------------------------------------------";
		 getch();
		}

		//******************************************************************
		//             FUNCTION FOR ENTRY AND EDIT MENU
		//******************************************************************

		void entry_menu()
		{
		 int ch;
		 int num;
		 clrscr();
		 cout<<"\n\n\n\tENTRY/EDIT/DISPLAY MENU";
		 cout<<"\n\n\t1.CREATE STUDENT RECORD";
		 cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
		 cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
		 cout<<"\n\n\t4.MODIFY STUDENT RECORD";
		 cout<<"\n\n\t5.DELETE STUDENT RECORD";
		 cout<<"\n\n\t6.BACK TO MAIN MENU";
		 cout<<"\n\n\tPlease Enter Your Choice (1-6): ";
		 cin>>ch;
		 clrscr();
		 switch(ch)
		 {
	case 1:	write_student();
		break;
	case 2:	display_all();
		break;
	case 3:	cout<<"\n\n\tPlease Enter The roll number: "; cin>>num;
			display_sp(num);
			break;
	case 4:	cout<<"\n\n\tPlease Enter The roll number: "; cin>>num;
			modify_student(num);
			break;
	case 5:	cout<<"\n\n\tPlease Enter The roll number: "; cin>>num;
			delete_student(num);
			break;
		 }
		}

      //********************************************************************
      //                       END OF PROJECT
      //********************************************************************
      //                         THANK YOU
      //********************************************************************
