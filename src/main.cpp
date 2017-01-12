#include "My_Pin_Password.h"

int main()
{
	My_Pin_Password* run= new My_Pin_Password;

        /* to be uncommented when dumping records from there encryted form
         * and saving them in text form instead of binary form
         * this feature was used to move the records from this encryption standard
         * to a higher standard using Qt libraries and other high encryption APIs
         */
        run->dumpRecords();
	//run->Run();

	delete run;
	return 0;
}
