#ifndef MY_PIN_PASSWORD_H
#define MY_PIN_PASSWORD_H

#include "DynamicArray.h"
#include "CryptoMechanism.h"

#if defined (__linux__)
#include <iostream>
#endif //__linux__

class My_Pin_Password
{
	public:
		My_Pin_Password();
		~My_Pin_Password();
		void Run();
        void dumpRecords();

	private:

		void standard();
		void save();
		void generate();
		void displayall();
		void remove();
 		void change_VK();
	    void edit_record();
	    void first_run();

		void newstandard();
		void displaystandards();

		void newsave();
		void displaysaved();

		void newgenerate();
		void displaygenerated();

        void generator();
        void pin_generator(array_t& seed);
        void password_generator(array_t& seed, long long display_mask);
        void display_generated(long long display_mask);

	 	void loadfile();
                void savefile();

		void Run(int where);
		void random_number(array_t& pin);

		inline void encrypt(array_t& record);
		inline void decrypt(array_t& record);

		struct sstandard{array_t pin_password;};
		struct ssave{array_t what, username, password;};
		struct sgenerate{array_t device, pin;};
  		struct Generated{array_t data; bool which;};

		inline void initialize_array(sstandard& container);
  		inline void initialize_array(ssave& container);
	    inline void initialize_array(sgenerate& container);
		inline void initialize_array(Generated& container);
	    inline void initialize_array(sstandard* container);
  		inline void initialize_array(ssave* container);
	    inline void initialize_array(sgenerate* container);
	    inline void initialize_array(Generated* container);
	    inline void initialize_array(array_t& array);

   		inline void clearscreen()
   		{
#if defined (_WIN32) || (_WIN64)
            system("cls");
#elif defined (__linux__)
            system("clear");
#endif
        }
	    inline void pausescreen()
	    {
#if defined (_WIN32) || (_WIN64)
            system("cls");
#elif defined (__linux__)
            std::cin.get();
            std::cin.get();
#endif
        }

		DynamicArray* fStandard;
		DynamicArray* fSave;
		DynamicArray* fGenerate;
  		DynamicArray* fList;
		CryptoMechanism* fLock;
	 	long long fDisplay_Mask;
};

inline void My_Pin_Password::encrypt(array_t& record)
{
	for(int i=0; i<99; i++)fLock->Encrypt(record);
	return;
}

inline void My_Pin_Password::decrypt(array_t& record)
{
	for(int i=0; i<99; i++)fLock->Decrypt(record);
	return;
}

inline void My_Pin_Password::initialize_array(sstandard& container)
{
	for(int i=0; i<limit; i++)container.pin_password[i]='\0';
    return;
}

inline void My_Pin_Password::initialize_array(ssave& container)
{
    for(int i=0; i<limit; i++)container.what[i]=container.username[i]=container.password[i]='\0';
    return;
}

inline  void My_Pin_Password::initialize_array(sgenerate& container)
{
    for(int i=0; i<limit; i++)container.device[i]=container.pin[i]='\0';
    return;
}

inline  void My_Pin_Password::initialize_array(Generated& container)
{
    for(int i=0; i<limit; i++)container.data[i]='\0';
    container.which=false;
    return;
}

inline void My_Pin_Password::initialize_array(sstandard* container)
{
	for(int i=0; i<limit; i++)container->pin_password[i]='\0';
    return;
}

inline void My_Pin_Password::initialize_array(ssave* container)
{
    for(int i=0; i<limit; i++)container->what[i]=container->username[i]=container->password[i]='\0';
    return;
}

inline  void My_Pin_Password::initialize_array(sgenerate* container)
{
    for(int i=0; i<limit; i++)container->device[i]=container->pin[i]='\0';
    return;
}

inline  void My_Pin_Password::initialize_array(Generated* container)
{
    for(int i=0; i<limit; i++)container->data[i]='\0';
    container->which=false;
    return;
}

inline void My_Pin_Password::initialize_array(array_t& array)
{
    for(int i=0; i<limit; i++)array[i]='\0';
    return;
}

#endif //MY_PIN_PASSWORD_H
