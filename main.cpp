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
	int k = -1;
	int choice = -1;
	std::string s = "tmp";
	std::string res = "netsh advfirewall set currentprofile logging filename \"";
	

	while (k != 0)
	{
		std::cout << "***\tWinFirewall configuration" << std::endl;
		std::cout << "*********************************" << std::endl;

		std::cout << "***\t1 - WinFirewall On" << std::endl;
		std::cout << "***\t2 - WinFirewall Off" << std::endl;
		std::cout << "***\t3 - WinFirewall Reset" << std::endl;
		std::cout << "***\t4 - Change the path to save the logs" << std::endl;
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
			if(std::cin >> choice)
				if (choice == 1)
				{
					std::cout << "Are you sure? 1 - yes, any other - no" << std::endl;
					std::cin >> choice;
					if (choice == 1)
					{
						system("netsh advfirewall reset");
					}
				}
				break;
		case 4:
			std::cout << "enter the new path: example(C:\\\temp\\\pfirewall.log)\nYour new path: ";
			std::getline(std::cin, s);
			res += s;
			res += "\"";
			std::cout << "\n" << res << "\n";
			//Äîáàâü êîìàíäó netsh advfirewall set currentprofile logging filename «C:\temp\pfirewall.log»
			break;

		}
	}
	return 0;
}