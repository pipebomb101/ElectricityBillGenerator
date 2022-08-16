#include<iostream>
#include<fstream>
#include<process.h>
#include<stdio.h>

#include<string.h>
using namespace std;
struct bill
{
	int meterno, prevread, curread;
	char name[20], add[20];
}s;

class ebill
{
	int metno, unit, prevread, curread;
	char name[20], add[20], ch, date[20];
	float amnt, tot;

	public:
	void insert();
	void show();
	void search();
	void modify();
	void makebill();
	void display();
}x;

void ebill::insert()
{
	fstream F("std.dat",ios::binary|ios::out|ios::app);
	if(!F)
	{
		cout<<"File Not Found";
		s.meterno = 1;
		exit(0);
	}
	cout<<"\nEnter Name: ";
	gets(s.name);
	if(strlen(s.name) == 0)
	cout<<"Don't Leave This Field Empty";
	cout<<"Enter Address: ";
	gets(s.add);
	if(strlen(s.add) == 0)
	cout<<"Don't Leave This Field Empty";
	prevread = 0;
	curread = 0;
	s.meterno = s.meterno + 1;
	cout<<"Enter Meter Number: ";
	cin>>s.meterno;
	F.write((char*)&s,sizeof(s));
	F.close();
}

void ebill::show()
{
	fstream A("std.dat",ios::in|ios::binary|ios::app);
	if(!A)
	{
		cout<<"\n File Not Found";
		exit(0);
	}
	else
	{
		cout<<"\nBill Record: ";
		while(A.read((char*)&s,sizeof(s)))
		{
			cout<<"\n"<<s.meterno<<"\t"<<s.name<<"\t"<<s.add;
		}
	}
	A.close();
}

void ebill::search()
{
	int mno;
	fstream B("std.dat",ios::binary|ios::in);
	if(!B)
	{
		cout<<"\n File Not Found";
		exit(0);
	}
	cout<<"\nEnter Meter Number To Search: ";
	cin>>mno;
	while(B.read((char*)&s,sizeof(s)))
	{
		if(mno == s.meterno)
		{
			cout<<"\n Record Found";
			cout<<"\n Name: "<<s.name;
			cout<<"\n Address: "<<s.add;
			cout<<"\n Meter Number: "<<s.meterno;
		}
	}
	B.close();
}

void ebill::modify()
{
	int mno, count = 0;
	long int pos;
	fstream C("std.dat",ios::binary|ios::out|ios::in);
	if(!C)
	{
		cout<<"\n File Not Found";
		exit(0);
	}
	cout<<"\nEnter Meter Number To Be Modified: ";
	cin>>mno;
	while(C.read((char*)&s,sizeof(s)))
	{
		if(mno == s.meterno)
		{
			cout<<"\n Enter New Record: ";
			cout<<"\n Enter Name: ";
			gets(s.name);
			if(strlen(s.name)==0)
			cout<<"Don't Leave This Field Empty";
			cout<<" Enter Address: ";
			gets(s.add);
			if(strlen(s.add)==0)
			cout<<"Don't Leave This Field Empty";
			pos = count * sizeof(s);
			C.seekp(pos,ios::beg);
			C.write((char*)&s,sizeof(s));
		}
		count++;
		C.clear();
	}
	C.close();
}

void ebill::makebill()
{
	int x, y, mno;
	fstream D("std.dat",ios::in|ios::binary);
	if(!D)
	{
		cout<<"\n File Not Found";
		exit(0);
	}
	cout<<"\nEnter Meter Number To Make Bill ";
	cin>>mno;
	while(D.read((char*)&s,sizeof(s)))
	{
		if(mno == s.meterno)
		{
			cout<<"\nName         : "<<s.name;
			cout<<"\nAddress      : "<<s.add;
			cout<<"\nMeter Number : "<<s.meterno;
			prevread = curread;
			cout<<"\nPrevious Reading: "<<prevread;
			cout<<"\nCurrent Reading: ";
			cin>>curread;
			cout<<"Enter Date Of Bill(DD/MM/YYYY): ";
			gets(date);
			unit = curread - prevread;
			if(unit > 300)
			amnt = unit * 3.50;
			else if(unit > 200 && unit <= 300)
			amnt = unit * 3.00;
			else if(unit > 100 && unit <= 200)
			amnt = unit * 2.50;
			else
			amnt = unit * 2.00;
		}
	}
	D.write((char*)&s,sizeof(s));
	D.close();
}

void ebill::display()
{
	int mno;
	fstream E("std.dat",ios::binary|ios::in);
	if(!E)
	{
		cout<<"File Not Found";
		exit(0);
	}
	cout<<"Enter Meter Number To Display Bill: ";
	cin>>mno;
	while(E.read((char*)&s,sizeof(s)))
	{
		if(mno == s.meterno)
		{
			cout<<"\nTotal Unit  : "<<unit;
			cout<<"\nTotal Amount: "<<amnt;
			cout<<"\nDate Of Bill: ";
			puts(date);
		}
	}
	E.close();
}

int main()
{
	
	char rep,pass[25]="TNELECTRICITY",entry[25];
	int ch,k;
	ebill s1;
	cout<<"**TN ELECTRICITY BOARD**";
	do
	{
		cout<<"\n\nEnter: 1. For Officials 2.For Consumers\n";
		cin>>k;
		if(k==1)
		{
			cout<<"Enter the password: ";
			gets(entry);
			if(strcmpi(entry,pass)!=0)
			{
				cout<<"Password Invalid ... Try Again: ";
				gets(entry);
				while(strcmpi(entry,pass)!=0)
				{
					cout<<"Password Invalid ... Try Again: ";
					gets(entry);
				}
				cout<<"\n1.Enter New Record 2.List Of Electricity Bills";
				cout<<"\n3.Search A Bill    4.Modify A Bill";
				cout<<"\n5.Make A Bill      6.Display A Bill \n7.Exit ";
				cout<<"\nEnter Your Choice: \n";
				cin>>ch;
			}
		}
		if(k==2)
		{
			cout<<"Press:";
			cout<<"\n3.To Search Your Bill";
			cout<<"\n5.To Make Your Bill";
			cout<<"\n6.To Display Your Bill\n";
			cin>>ch;
		}
		switch(ch)
		{
			case 1: s1.insert();
				break;
			case 2: s1.show();
				break;
			case 3: s1.search();
				break;
			case 4: s1.modify();
				break;
			case 5: s1.makebill();
				break;
			case 6: s1.display();
				break;
			case 7: exit(0);
			default: cout<<"Invalid Choice";
		}
		cout<<"\nDo You Want To Continue?: \n";
		cin>>rep;
	}
	while(rep == 'y' || rep == 'Y');

	return 0;
}
