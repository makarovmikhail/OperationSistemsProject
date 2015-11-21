#include <windows.h>
#include <crtdbg.h>
#include <netfw.h>
#include <objbase.h>
#include <oleauto.h>
#include <stdio.h>
#include <iostream>
#include <string>


int main()
{
	int k = -1;							//Choice menu var	
	int choice = -1;					//sure var
	std::string s = "tmp";				//string IN
	std::string res = "netsh advfirewall set currentprofile logging filename \"";	//string result log
	

	while (k != 0)
	{
		std::cout << "***\tWinFirewall configuration" << std::endl;
		std::cout << "*********************************" << std::endl;

		std::cout << "***\t1 - WinFirewall On" << std::endl;
		std::cout << "***\t2 - WinFirewall Off" << std::endl;
		std::cout << "***\t3 - WinFirewall Reset" << std::endl;
		std::cout << "***\t4 - Change the path to save the logs" << std::endl;
		std::cout << "***\t5 - Inclusion separate profiles" << std::endl;
		std::cout << "***\t6 - Disable separate profiles" << std::endl;

		std::cout << "***\t0 - EXIT" << std::endl << std::endl;

		std::cin >> k;
		std::cout << std::endl;
		switch (k)
		{
		case 1:
			system("netsh advfirewall set allprofiles state on");
			break;
		case 2:
			system("netsh advfirewall set allprofiles state off");
			break;
		case 3:
			std::cout << "Sure? 1 - yes, any other - no" << std::endl;
			if (std::cin >> choice)
			if (choice == 1)
			{
				std::cout << "Are you sure? 1 - yes, any other - no" << std::endl;
				std::cin >> choice;
				if (choice == 1)
				{
					system("netsh advfirewall reset");
				}
			}
			choice = -1;
			break;
		case 4:
			std::cout << "enter the new path: example(C:\\\temp\\\pfirewall.log)\nYour new path: ";
			std::getline(std::cin, s);
			res += s;
			res += "\"";
			std::cout << "\n" << res << "\n";
			//Add command netsh advfirewall set currentprofile logging filename «C:\temp\pfirewall.log»
			break;
		case 5:
			while (choice != 1 && choice != 2 && choice != 3 && choice != 0)
			{
				std::cout << "1 - Domain" << std::endl;
				std::cout << "2 - Private" << std::endl;
				std::cout << "3 - Public" << std::endl;
				std::cout << "0 - Back to menu" << std::endl;

				if (std::cin >> choice)
				{
					if (choice == 1)
					{
						system("netsh advfirewall set domainprofile state on");
					}
					else if (choice == 2)
					{
						system("netsh advfirewall set privateprofile state on");
					}
					else if (choice == 3)
					{
						system("netsh advfirewall set publicprofile state on");
					}
				}
			}
			choice = -1;
			break;
		case 6:
			while (choice != 1 && choice != 2 && choice != 3 && choice != 0)
			{
				std::cout << "1 - Domain" << std::endl;
				std::cout << "2 - Private" << std::endl;
				std::cout << "3 - Public" << std::endl;
				std::cout << "0 - Back to menu" << std::endl;

				if (std::cin >> choice)
				{
					if (choice == 1)
					{
						system("netsh advfirewall set domainprofile state off");
					}
					else if (choice == 2)
					{
						system("netsh advfirewall set privateprofile state off");
					}
					else if (choice == 3)
					{
						system("netsh advfirewall set publicprofile state off");
					}
				}
			}
			break;
		}
	}
	return 0;
}