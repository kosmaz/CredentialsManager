#include "CryptoMechanism.h"
#include "Advanced_Header_File.h"
using namespace std;



CryptoMechanism::CryptoMechanism (int change)
{
  fStart=0;
  fIncreament=2;
  const int tshuffle=1000;
  pt0:
  cout<<"virtual key:>";
  char* virtual_temp=kosmaz::hide_user_input();
  int virtual_key=atoi(virtual_temp);
  if(change)
  {
  	cout<<"\nconfirm virtual key:>";
  	char* temp=kosmaz::hide_user_input();
  	int temp_virtual_key=atoi(temp);
  	if(temp_virtual_key!=virtual_key)
	  {
  		cout<<"\n\nvirtual key doesn't match\n";
  		system("pause");
  		#if defined (_WIN32) || (_WIN64)
    system("cls");
#elif defined (__linux__)
    system("clear");
#endif
  		goto pt0;
	  }
  }
  cout<<'\n';
  srand(virtual_key);
  delete virtual_temp;

  for(int i=0;i<tmax;++i){
      fTable[i]=i+' ';
    }

  for(int k=0;k<tshuffle;++k)
    {
      int index1=rand()%tmax;
      int index2=rand()%tmax;

      int temp=fTable[index1];
      fTable[index1]=fTable[index2];
      fTable[index2]=temp;
    }
    MakeRTable();
}

void CryptoMechanism::Encrypt(array_t& msg)
{
	int k = fStart;
	for(int i=0; msg[i] != '\0'; ++i)
	 {
		char ch = msg[i];
		msg[i] = fTable[(ch-32 +k ) % tmax];
		k += fIncreament;
 	 }
	return;
}

void CryptoMechanism::MakeRTable()
{
	for(int i = 0;i < tmax; ++i)
	{
	 int tem = fTable[i];
	 tem -= ' ';
	 fRTable[tem] = i;
	}
	return;
}

void CryptoMechanism::Decrypt(array_t& msg)
{
	int ch;
	int k = fStart;

	for(int i=0; msg[i]!='\0'; ++i)
		{
			ch=msg[i];
      		int t = fRTable[ch - 32];
	  		t -= k;
      		while(t<0) t+= tmax;
      		msg[i]=char(t + ' ');
      		k += fIncreament;
   	}
   return;
}
