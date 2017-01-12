#include "Advanced_Header_File.h"
#include "My_Pin_Password.h"
#include <cctype>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

//replace string containers with array[30] containers

My_Pin_Password::My_Pin_Password()
{
		fStandard= new DynamicArray;
		fSave= new DynamicArray;
		fGenerate= new DynamicArray;
  		fList=new DynamicArray;
		fDisplay_Mask=1001110110;
}


My_Pin_Password::~My_Pin_Password()
{
	delete fStandard;
	delete fSave;
	delete fGenerate;
	delete fList;
	delete fLock;
}

void My_Pin_Password::loadfile()
{
	clearscreen();
	ifstream infile;
    infile.open("records.dll", ios::binary|ios::in);
	if(!infile.good())
		{
			cout<<"\nCouldn't locate the binary file needed for the program to carry out\nits functions\n";
			system("pause");
			/*cout<<"Please contact the developer for assistant at kosmaz2009@yahoo.com or\ncall 08139278033\n";
			cout<<"Terminating the program now\n";
			exit(1);*/
			first_run();
			exit(0);
		}

	int stand,saved,gen,gen_gen;
	cout<<"Loading file records from disk to heap memory\n";
	cout<<"Loading...\n";
    sstandard* standard_ptr=0;
    infile.seekg(0, ios::beg);
	infile.read((char*)&stand, sizeof(stand));
	for(int i=0;i<stand;++i)
		{
			sstandard new_standard;
   			initialize_array(new_standard);
			infile.read((char*)&new_standard, sizeof(sstandard));
            standard_ptr=new sstandard;
            initialize_array(standard_ptr);
			strcpy(standard_ptr->pin_password, new_standard.pin_password);
			fStandard->Append((void*)standard_ptr);
			standard_ptr=0;
		}


  ssave* save_ptr=0;
  infile.seekg(0, ios::cur);
  infile.read((char*)&saved, sizeof(saved));
	for(int j=0;j<saved;++j)
		{
			ssave new_save;
   			initialize_array(new_save);
			infile.read((char*)&new_save, sizeof(ssave));
			save_ptr=new ssave;
			initialize_array(save_ptr);
			strcpy(save_ptr->what, new_save.what);
	        strcpy(save_ptr->username, new_save.username);
	 		strcpy(save_ptr->password, new_save.password);
    		fSave->Append((void*)save_ptr);
		    save_ptr=0;
		}

    sgenerate* generate_ptr=0;
    infile.seekg(0, ios::cur);
	infile.read((char*)&gen, sizeof(gen));
	for(int k=0;k<gen;++k)
		{
			sgenerate new_generate;
   			initialize_array(new_generate);
	        infile.read((char*)&new_generate, sizeof(sgenerate));
			generate_ptr=new sgenerate;
			initialize_array(generate_ptr);
            strcpy(generate_ptr->device, new_generate.device);
            strcpy(generate_ptr->pin, new_generate.pin);
			fGenerate->Append((void*)generate_ptr);
    	    generate_ptr=0;
		}

	Generated* generated_ptr=0;
    infile.seekg(0, ios::cur);
	infile.read((char*)&gen_gen, sizeof(gen_gen));
	for(int l=0;l<gen_gen;++l)
		{
			Generated new_generated;
   			initialize_array(new_generated);
	        infile.read((char*)&new_generated, sizeof(Generated));
			generated_ptr=new Generated;
			initialize_array(generated_ptr);
            strcpy(generated_ptr->data, new_generated.data);
            generated_ptr->which=new_generated.which;
			fList->Append((void*)generated_ptr);
    	    generated_ptr=0;
		}
	cout<<"Loading completed successfully\n";
	infile.close();
	clearscreen();
	return;
}

void My_Pin_Password::savefile()
{
    clearscreen();
	ofstream outfile;

        outfile.open("records.dll", ios::binary|ios::out);

	int stand,saved,gen,gen_gen;
	cout<<"Saving file records from heap memory to disk\n";
	cout<<"Saving...\n";
	sstandard* standard_ptr=0;
	outfile.seekp(0, ios::beg);
	stand=fStandard->Length();
	outfile.write((char*)&stand, sizeof(stand));
	for(int i=1;i<stand+1;++i)
		{
		 	sstandard del_standard;
			initialize_array(del_standard);
			standard_ptr=(sstandard*)fStandard->Nth(i);
	  	    strcpy(del_standard.pin_password, standard_ptr->pin_password);
            outfile.write((char*)&del_standard, sizeof(sstandard));
			delete standard_ptr;
			standard_ptr=0;
		}

	ssave* save_ptr;
	outfile.seekp(0, ios::cur);
	saved=fSave->Length();
	outfile.write((char*)&saved, sizeof(saved));
	for(int j=1;j<saved+1;++j)
		{
		 	ssave del_save;
			initialize_array(del_save);
			save_ptr=(ssave*)fSave->Nth(j);
 		    strcpy(del_save.what, save_ptr->what);
		    strcpy(del_save.username, save_ptr->username);
			strcpy(del_save.password, save_ptr->password);
			outfile.write((char*)&del_save, sizeof(ssave));
	 	    delete save_ptr;
            save_ptr=0;
		}

    sgenerate* generate_ptr;
	outfile.seekp(0, ios::cur);
	gen=fGenerate->Length();
	outfile.write((char*)&gen, sizeof(gen));
	for(int k=1;k<gen+1;++k)
		{
		 	sgenerate del_generate;
			initialize_array(del_generate);
			generate_ptr=(sgenerate*)fGenerate->Nth(k);
			strcpy(del_generate.device, generate_ptr->device);
			strcpy(del_generate.pin, generate_ptr->pin);
			outfile.write((char*)&del_generate, sizeof(sgenerate));
			delete generate_ptr;
			generate_ptr=0;
		}
	Generated* generated_ptr;
	outfile.seekp(0, ios::cur);
	gen_gen=fList->Length();
	outfile.write((char*)&gen_gen, sizeof(gen_gen));
	for(int l=1;l<gen_gen+1;++l)
		{
		 	Generated del_generated;
			initialize_array(del_generated);
			generated_ptr=(Generated*)fList->Nth(l);
			strcpy(del_generated.data, generated_ptr->data);
			del_generated.which=generated_ptr->which;
			outfile.write((char*)&del_generated, sizeof(Generated));
			delete generated_ptr;
   			generated_ptr=0;
		}
	cout<<"Saving completed successfully\n";
	outfile.close();
	pausescreen();
	return;
}

void My_Pin_Password::displayall()
{
	displaystandards();
	displaysaved();
	displaygenerated();
	display_generated(fDisplay_Mask);
}

void My_Pin_Password::standard()
{
    clearscreen();
	cout<<"\nChoose from the options given below\n";
	cout<<"1.\tCreate new standard password/pin\n";
	cout<<"2.\tDisplay all standard passwords\n";
	cout<<"3.\tReturn to main menu\n";

	char in;
	pt0:
	cin.clear();
	cout<<endl<< "$:>";
	cin>>in;

	switch(in)
	{
		case '1':newstandard();
			break;
		case '2':displaystandards();
			break;
		case '3':{clearscreen(); Run(1);};
			break;
		default:goto pt0;
			break;
	}
	return;
}

void My_Pin_Password::save()
{
    clearscreen();
	cout<<"\nChoose from the options given below\n";
	cout<<"1.\tCreate new what, username, pin/password\n";
	cout<<"2.\tDisplay all saved what, username, pin/password\n";
	cout<<"3.\tReturn to main menu\n";

	char in;
	pt0:
	cin.clear();
	cout<<endl<< "$:>";
	cin>>in;

	switch(in)
	{
		case '1':newsave();
			break;
		case '2':displaysaved();
			break;
		case '3':{clearscreen(); Run(1);};
			break;
		default:goto pt0;
			break;
	}
	return;
}

void My_Pin_Password::generate()
{
 	clearscreen();
	cout<<"\nChoose from the options given below\n";
	cout<<"1.\tGenerate new pin for a list of devices that will be given to you\n";
	cout<<"2.\tDisplay all genrated pins for their corresponding devices\n";
	cout<<"3.\tReturn to main menu\n";

  char in;
	pt0:
	cin.clear();
	cout<<endl<< "$:>";
	cin>>in;

	switch(in)
	{
		case '1':newgenerate();
			break;
		case '2':displaygenerated();
			break;
		case '3':{clearscreen(); Run(1);};
			break;
		default:goto pt0;
			break;
	}
	return;
}

void My_Pin_Password::Run()
{
  clearscreen();
  cout<<"Create an Event?\tY/N\n";
  pt0:
  cin.clear();
  cout<< "$:>";
  char ch;
  cin>>ch;
  if(isupper(ch))
  	ch=tolower(ch);

  switch(ch)
  {
  	case 'y':
  	{
 	    fLock= new CryptoMechanism;
		loadfile();
		Run(0);
    }
    break;

	 case 'n':
	 	{
	 		cout<<"Terminating now...\n";
	 		system("pause");
	 		return;
	 	}
	 	break;
	 default: goto pt0;
	 	break;
  }
	return;
}

void My_Pin_Password::Run(int where)
{
	if(where==0)
	  {
 		clearscreen();
		goto pt0;
	  }
	else
		goto pt1;

	pt0:
	cout<<"\n\n\t\tWelcome Sir/Madam\nHow may i be of help to you today?\n";
	cout<<"please choose from the options given below\n";
	char choice;
	pt1:
	cout<<"1.\tStandard\n2.\tSave\n3.\tGenerate\n4.\tGenerate pin/password\n5.\tDisplay all\n6.\tchange virtual key\n7.\tEdit a record\n8.\tRemove a record\n9.\tExit\n";
	pt2:
	cin.clear();
	cout<< "$:>";
	cin>>choice;

	switch(choice)
		{
			case '1':standard();
				break;
			case '2':save();
				break;
			case '3':generate();
				break;
			case '4':generator();
				break;
			case '5':displayall();
				break;
		    case '6':change_VK();
				break;
		    case '7':edit_record();
				break;
			case '8':remove();
				break;
			case '9':
				{
				 	clearscreen();
					cout<<"Exit?\tY/N\n";
					char y_n;
					pt3:
				  	cin.clear();
					cout<< "$:>";
					cin>>y_n;
					if(isupper(y_n))
  	        		y_n=tolower(y_n);

					if(y_n=='y')
						{
							savefile();
							return;
						}
					else
					if(y_n=='n')
					  {
    	  			    clearscreen();
					   	goto pt1;
					  }
					else
						goto pt3;
				}
				break;
			default:goto pt2;
				break;
		}
		goto pt1;
		return;
}

void My_Pin_Password::newstandard()
{
 clearscreen();
 array_t pp;
 string string_pp;
 sstandard* standard_ptr= new sstandard;
 initialize_array(pp);
 initialize_array(standard_ptr);
 cout<<"standard pin/password :>";
 cin.ignore();
 getline(cin, string_pp);
 cout<<"saving new record...\n";
 (void)string_pp.copy(pp, string_pp.size());
 encrypt(pp);
 strcpy(standard_ptr->pin_password, pp);
 fStandard->Append((void*)standard_ptr);
 cout<<"New record successfully saved\n";
 cout<<endl;
 pausescreen();
 clearscreen();
 return;
}

void My_Pin_Password::displaystandards()
{
 	clearscreen();
	sstandard* standard_ptr=0;
	cout<<"\nsaved standard pins and passwords are:\n";
	for(int i=1;i< (fStandard->Length()+1);i++)
		{
			standard_ptr=(sstandard*)fStandard->Nth(i);
			decrypt(standard_ptr->pin_password);
   			cout<<"-------------------------------------------------------------------\n";
			cout<<i<<".\t"<< standard_ptr->pin_password<<endl;
			encrypt(standard_ptr->pin_password);
		}
		cout<<endl;
		standard_ptr=0;
 	pausescreen();
	clearscreen();
	return;
}

void My_Pin_Password::newsave()
{
  clearscreen();
  array_t wt,un,pw;
  string string_wt,string_un,string_pw;
  ssave* save_ptr= new ssave;
  initialize_array(wt);
  initialize_array(un);
  initialize_array(pw);
  initialize_array(save_ptr);
  cout<<"For What :>";
  cin.ignore();
  getline(cin, string_wt);
  cout<<"username :>";
  cin.ignore('\0');
  getline(cin, string_un);
  cout<<"password :>";
  cin.ignore('\0');
  getline(cin, string_pw);
  cout<<"saving new record...\n";
  (void)string_wt.copy(wt, string_wt.size());
  (void)string_un.copy(un, string_un.size());
  (void)string_pw.copy(pw, string_pw.size());
  encrypt(wt);
  encrypt(un);
  encrypt(pw);
  strcpy(save_ptr->what, wt);
  strcpy(save_ptr->username, un);
  strcpy(save_ptr->password, pw);
  fSave->Append((void*)save_ptr);
  cout<<"New record successfully saved\n";
  cout<<endl;
  pausescreen();
  clearscreen();
  return;
}

void My_Pin_Password::displaysaved()
{
  clearscreen();
  ssave* save_ptr=0;
	cout<<"\nsaved user names and passwords for user specified purposes are:\n";
	cout<<"  \tWhat::user name::password\n";
	for(int i=1;i< (fSave->Length()+1);i++)
		{
			save_ptr=(ssave*)fSave->Nth(i);
			decrypt(save_ptr->what);
			decrypt(save_ptr->username);
			decrypt(save_ptr->password);
   			cout<<"-------------------------------------------------------------------\n";
			cout<<i<<".\t"<< save_ptr->what<<"::"<< save_ptr->username<<"::"<< save_ptr->password<<endl;
			encrypt(save_ptr->what);
			encrypt(save_ptr->username);
			encrypt(save_ptr->password);
		}
		cout<<endl;
		save_ptr=0;
    pausescreen();
    clearscreen();
	return;
}

void My_Pin_Password::newgenerate()
{
 	 clearscreen();
	 array_t mydevice,mypin;
	 sgenerate* generate_ptr= new sgenerate;
     initialize_array(generate_ptr);
	 cout<<"Choose from the list of given devices below\n";
	 cout<<"1.\tTECNO N3\n";
	 cout<<"2.\tTECNO A+\n";
	 cout<<"3.\tTECNO N9\n";
	 cout<<"4.\tWINDOWS 7\n";
	 cout<<"5.\tWINDOwS 8\n";
	 cout<<"6.\tHDD 2\n";
	 char device;
	 pt0:
	 cin.clear();
	 cout<< "$:>";
	 cin>>device;
	 switch(device)
	 	{
	 		case '1':strcpy(mydevice, "TECNO N3");
	 			break;
			case '2':strcpy(mydevice, "TECNO A+");
				break;
	 		case '3':strcpy(mydevice, "TECNO N9");
	 			break;
	 		case '4':strcpy(mydevice, "WINDOWS 7");
	 			break;
	 		case '5':strcpy(mydevice, "WINDOWS 8");
	 			break;
			case '6':strcpy(mydevice, "HDD 2");
				break;
	 		default: goto pt0;
	 			break;
	 	}
	 random_number(mypin);
	 cout<<"Generated pin for the selected device is "<<mypin<<endl;
	 cout<<"saving new record...\n";
	 encrypt(mydevice);
	 encrypt(mypin);
	 strcpy(generate_ptr->device, mydevice);
	 strcpy(generate_ptr->pin, mypin);
	 fGenerate->Append((void*)generate_ptr);
	 cout<<"New record successfully saved\n";
	 cout<<endl;
  	 pausescreen();
  	 clearscreen();
	 return;
}

void My_Pin_Password::displaygenerated()
{
 	clearscreen();
    sgenerate* generate_ptr=0;
    cout<<"if Pin is less than 6 digits fill from the end with 0s until pin\nis equal to 6 digits";
	cout<<"\nsaved generated pins for specific devices are:\n";
	cout<<"  \tdevice::pin\n";
	for(int i=1;i< (fGenerate->Length()+1);i++)
		{
			generate_ptr=(sgenerate*)fGenerate->Nth(i);
			decrypt(generate_ptr->device);
			decrypt(generate_ptr->pin);
	  		cout<<"-------------------------------------------------------------------\n";
			cout<<i<<".\t"<< generate_ptr->device<<"::"<< generate_ptr->pin<<endl;
			encrypt(generate_ptr->device);
			encrypt(generate_ptr->pin);
		}
		cout<<endl;
		generate_ptr=0;
    pausescreen();
	clearscreen();
	return;
}

void My_Pin_Password::random_number(array_t& pin)
{
	int generatedpin;
	time_t TimeEpoch=time(0);
	srand(TimeEpoch);
	generatedpin=rand();
	char __int_char_array__[11];

#if defined (_WIN32) || (_WIN64)
	itoa(generatedpin, __int_char_array__, 10);
#elif defined (__linux__)
    string temp=kosmaz::to_string(generatedpin);
	char* __temp_int_char_array__=(char*)temp.c_str();
	strcpy(__int_char_array__,__temp_int_char_array__);
#endif // defined to_string && c_str

    __int_char_array__[10]='\0';
	strcpy(pin, __int_char_array__);
	return;
}

void My_Pin_Password::remove()
{
 	clearscreen();
	cout<<"\nChoose the file record to remove a record from\n";
	cout<<"1.\tStandard file record\n";
	cout<<"2.\tSave file record\n";
	cout<<"3.\tReturn to main menu\n";

	char rem;
	pt0:
	cin.clear();
	cout<< "$:>";
	cin>>rem;

	switch(rem)
		{
			case '1':
				{
					int fileno;
					cout<<"file number:>";
					cin>>fileno;
					sstandard* null_ptr=(sstandard*)fStandard->Remove(fileno);
					delete null_ptr;
					cout<<"Record successfully removed from standard file record\n\n";
				}
				break;
			case '2':
				{
					int fileno;
					cout<<"file number:>";
					cin>>fileno;
					ssave* null_ptr=(ssave*)fSave->Remove(fileno);
					delete null_ptr;
					cout<<"Record successfully removed from save file record\n\n";
				}
				break;
			case '3':
			{
				clearscreen();
		        Run(1);
		    }
				break;
			default:goto pt0;
				break;
		}
		pausescreen();
		clearscreen();
		return;
}

void My_Pin_Password::change_VK()
{
 clearscreen();
 cout<<"Removing old encryption virtual key from all records...\n";

 sstandard* standard_ptr=0;
 ssave* save_ptr=0;
 sgenerate* generate_ptr=0;

 for(int i=1; i<fStandard->Length()+1; i++)
 {
  standard_ptr=(sstandard*)fStandard->Nth(i);
  decrypt(standard_ptr->pin_password);
  standard_ptr=0;
 }

 for(int j=1; j<fSave->Length()+1; j++)
 {
  save_ptr=(ssave*)fSave->Nth(j);
  decrypt(save_ptr->what);
  decrypt(save_ptr->username);
  decrypt(save_ptr->password);
  save_ptr=0;
 }

 for(int k=1; k<fGenerate->Length()+1; k++)
 {
  generate_ptr=(sgenerate*)fGenerate->Nth(k);
  decrypt(generate_ptr->device);
  decrypt(generate_ptr->pin);
  generate_ptr=0;
 }
 cout<<"Removal operation successful\n\n";

 delete fLock;
 fLock=new CryptoMechanism(1);
 cout<<"\nRe-encrypting records with new virtual key\n";

 for(int i=1; i<fStandard->Length()+1; i++)
 {
  standard_ptr=(sstandard*)fStandard->Nth(i);
  encrypt(standard_ptr->pin_password);
  standard_ptr=0;
 }

 for(int j=1; j<fSave->Length()+1; j++)
 {
  save_ptr=(ssave*)fSave->Nth(j);
  encrypt(save_ptr->what);
  encrypt(save_ptr->username);
  encrypt(save_ptr->password);
  save_ptr=0;
 }

 for(int k=1; k<fGenerate->Length()+1; k++)
 {
  generate_ptr=(sgenerate*)fGenerate->Nth(k);
  encrypt(generate_ptr->device);
  encrypt(generate_ptr->pin);
  generate_ptr=0;
 }
 cout<<"Change of virtual key operation successful\n";
 pausescreen();
 clearscreen();
 return;
}

void My_Pin_Password::edit_record()
{
    clearscreen();
    cout<<"\nChoose the file record to edit a record number\n";
	cout<<"1.\tStandard file record\n";
	cout<<"2.\tSave file record\n";
	cout<<"3.\tReturn to main menu\n";

	char rem;
	pt0:
	cin.clear();
	cout<< "$:>";
	cin>>rem;

	switch(rem)
		{
			case '1':
				{
					int fileno;
					cout<<"file number:>";
					cin>>fileno;
					sstandard* new_ptr=(sstandard*)fStandard->Nth(fileno);
					array_t pp;
				    string string_pp;
					initialize_array(pp);
		            initialize_array(new_ptr);
					cout<<"standard pin/password :>";
					cin.ignore();
					getline(cin, string_pp);
					cout<<"saving new record...\n";
					(void)string_pp.copy(pp, string_pp.size());
					encrypt(pp);
					strcpy(new_ptr->pin_password, pp);
					new_ptr=0;
					cout<<"Record successfully changed in standard file record\n\n";
				}
				break;
			case '2':
				{
					int fileno;
					cout<<"file number:>";
					cin>>fileno;
					ssave* new_ptr=(ssave*)fSave->Nth(fileno);
 	   				array_t wt,un,pw;
   				    string string_wt,string_un,string_pw;
				    initialize_array(wt);
				    initialize_array(un);
				    initialize_array(pw);
		            initialize_array(new_ptr);
				    cout<<"For What :>";
				    cin.ignore();
				    getline(cin, string_wt);
				    cout<<"username :>";
				    cin.ignore('\0');
				    getline(cin, string_un);
				    cout<<"password :>";
				    cin.ignore('\0');
				    getline(cin, string_pw);
				    cout<<"saving new record...\n";
	                (void)string_wt.copy(wt, string_wt.size());
				    (void)string_un.copy(un, string_un.size());
				    (void)string_pw.copy(pw, string_pw.size());
			        encrypt(wt);
				    encrypt(un);
				    encrypt(pw);
				    strcpy(new_ptr->what, wt);
				    strcpy(new_ptr->username, un);
				    strcpy(new_ptr->password, pw);
	                new_ptr=0;
					cout<<"Record successfully changed in save file record\n\n";
				}
				break;
			case '3':Run(1);
				break;
			default:goto pt0;
				break;
		}
 pausescreen();
 clearscreen();
 return;
}

void My_Pin_Password::generator()
{
 	clearscreen();
	cout<<"\nChoose from the options given below\n";
	cout<<"1.\tGenerate a new pin\n";
	cout<<"2.\tGenerate a new password\n";
	cout<<"3.\tDisplay previous generated pins and passwords\n";
	cout<<"4.\tReturn to main menu\n";

	array_t seed;
	initialize_array(seed);
	random_number(seed);
  	char in;
	pt0:
	cin.clear();
	cout<<endl<< "$:>";
	cin>>in;

	switch(in)
	{
		case '1':pin_generator(seed);
			break;
	 	case '2':password_generator(seed,fDisplay_Mask);
		 	break;
		case '3':display_generated(fDisplay_Mask);
			break;
		case '4':{clearscreen(); Run(1);};
			break;
		default:goto pt0;
			break;
	}
	return;
}

void My_Pin_Password::pin_generator(array_t& seed)
{
 clearscreen();
 cout<<"generating new pin...\n";
 long pin=atoi(seed);
 if((pin%10000000)==pin)
 {
  bool state=true;
  long rem=pin%10000000;
  while(state)
  {
   srand(rem);
   int add=rand();
   if(add>9)
    while(add>9)
        add=add%10;
   pin*=10; pin+=add;
   if((pin%10000000)!=pin)
    state=false;
   rem=pin%10000000;
  }
 }
 cout<<"New generated pin: "<<pin<<endl;
 cout<<"Saving new pin to records...\n";
 initialize_array(seed);
 #if defined (_WIN32) || (_WIN64)
	itoa(pin,seed,10);
#elif defined (__linux__)
    string temp=kosmaz::to_string(pin);
	char* __temp_seed__=(char*)temp.c_str();
	strcpy(seed,__temp_seed__);
#endif // defined to_string && c_str
 Generated* generated_ptr=new Generated;
 generated_ptr->which=false;
 encrypt(seed);
 strcpy(generated_ptr->data, seed);
 fList->Append((void*)generated_ptr);
 cout<<"New pin successfully saved to records\n";
 cout<<endl;
 pausescreen();
 clearscreen();
 return;
}

void My_Pin_Password::password_generator(array_t& seed, long long display_mask)
{
 clearscreen();
 cout<<"generating new password...\n";
 long password=atoi(seed);
 cout<<"New generated password: "<<hex<<(password^display_mask)<<endl;
 cout<<dec;
 cout<<"Saving new password to records...\n";
 Generated* generated_ptr=new Generated;
 generated_ptr->which=true;
 encrypt(seed);
 strcpy(generated_ptr->data, seed);
 fList->Append((void*)generated_ptr);
 cout<<"New pin successfully saved to records\n";
 cout<<endl;
 pausescreen();
 clearscreen();
 return;
}

void My_Pin_Password::display_generated(long long display_mask)
{
    clearscreen();
    Generated* generated_ptr=0;
	cout<<"Saved generated pins and passwords are:\n";
	for(int i=1;i< (fList->Length()+1);i++)
		{
			generated_ptr=(Generated*)fList->Nth(i);
			decrypt(generated_ptr->data);
	  		if(generated_ptr->which==false)
 		  	{
			   cout<<"-------------------------------------------------------------------\n";
               cout<<i<<".\t"<<generated_ptr->data<<"(PIN)"<<endl;
		       encrypt(generated_ptr->data);
            }
            else
            {
              int password=atoi(generated_ptr->data);
              cout<<"-------------------------------------------------------------------\n";
              cout<<i<<".\t"<<hex<<(password^display_mask)<<dec<<"(PASSWORD)"<<endl;
		      encrypt(generated_ptr->data);
            }
		}
	cout<<dec<<endl;
	generated_ptr=0;
    pausescreen();
	clearscreen();
	return;
}

void My_Pin_Password::first_run()
{
	clearscreen();
	cout<<"1.\tcreate new record\n";
	cout<<"2.\tQuit\n";
	char choice;
	pt0:
	cout<<endl<< "$:>";
	cin.clear();
	cin>>choice;
	if(choice=='1')
	{
		delete fLock;
		fLock=new CryptoMechanism(1);
		fstream new_file("records.dll");
		Run(0);
	}
	else if(choice=='2')exit(1);
	else goto pt0;
	return;
}


void My_Pin_Password::dumpRecords()
{
    fLock= new CryptoMechanism;
    loadfile();

    for(int i=1; i<fStandard->Length()+1; ++i)
        decrypt(((sstandard*)fStandard->Nth(i))->pin_password);

    for(int i=1; i<fSave->Length()+1; ++i)
    {
        decrypt(((ssave*)fSave->Nth(i))->what);
        decrypt(((ssave*)fSave->Nth(i))->username);
        decrypt(((ssave*)fSave->Nth(i))->password);
    }

    for(int i=1; i<fGenerate->Length()+1; ++i)
    {
        decrypt(((sgenerate*)fGenerate->Nth(i))->device);
        decrypt(((sgenerate*)fGenerate->Nth(i))->pin);
    }

    for(int i=1; i<fList->Length()+1; ++i)
        decrypt(((Generated*)fList->Nth(i))->data);

    ofstream outfile;
    outfile.open("records.txt",ios::out);

    int stand,saved,/*gen,*/gen_gen;
    sstandard* standard_ptr=0;
    stand=fStandard->Length();
    outfile<<stand<<'\n';
    for(int i=1;i<stand+1;++i)
            {
                    sstandard del_standard;
                    initialize_array(del_standard);
                    standard_ptr=(sstandard*)fStandard->Nth(i);
                    strcpy(del_standard.pin_password, standard_ptr->pin_password);
                    outfile<<del_standard.pin_password<<'\n';
                    delete standard_ptr;
                    standard_ptr=0;
            }

    ssave* save_ptr=0;
    saved=fSave->Length();
    outfile<<saved<<'\n';
    for(int j=1;j<saved+1;++j)
            {
                    ssave del_save;
                    initialize_array(del_save);
                    save_ptr=(ssave*)fSave->Nth(j);
                    strcpy(del_save.what, save_ptr->what);
                    strcpy(del_save.username, save_ptr->username);
                    strcpy(del_save.password, save_ptr->password);
                    outfile<<del_save.what<<'\n'<<del_save.username<<'\n'<<del_save.password<<'\n';
                    delete save_ptr;
                    save_ptr=0;
            }

/*    sgenerate* generate_ptr=0;
    gen=fGenerate->Length();
    outfile<<gen<<'\n';
    for(int k=1;k<gen+1;++k)
            {
                    sgenerate del_generate;
                    initialize_array(del_generate);
                    generate_ptr=(sgenerate*)fGenerate->Nth(k);
                    strcpy(del_generate.device, generate_ptr->device);
                    strcpy(del_generate.pin, generate_ptr->pin);
                    outfile<<del_generate.device<<'\n'<<del_generate.pin<<'\n';
                    delete generate_ptr;
                    generate_ptr=0;
            }*/
    Generated* generated_ptr;
    gen_gen=fList->Length();
    outfile<<gen_gen<<'\n';
    for(int l=1;l<gen_gen+1;++l)
            {
                    Generated del_generated;
                    initialize_array(del_generated);
                    generated_ptr=(Generated*)fList->Nth(l);
                    strcpy(del_generated.data, generated_ptr->data);
                    del_generated.which=generated_ptr->which;
                    outfile<<del_generated.data<<'\n'<<(unsigned short)del_generated.which<<'\n';
                    delete generated_ptr;
                    generated_ptr=0;
            }
    outfile.close();
    return;
}
