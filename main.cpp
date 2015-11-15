#include <windows.h>
#include <stdio.h>
#include <netfw.h>
#include <iostream>

#pragma comment( lib, "ole32.lib" )


// Forward declarations
HRESULT     WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2);


int __cdecl main()
{
	using namespace std;
	//system("netsh advfirewall set allprofiies state on");

	/////////////////////////////////////////////////////////////////
	int k = -1;				//Переменная выбора
	while (k != 0)			//Визуализация меню
	{
		cout << "__________________________________________" << endl;
		cout << "Win Firewall config_______________________" << endl;
		cout << "__________________________________________" << endl;
		cout << "1. Firewall Off___________________________" << endl;
		cout << "2. Firewall On____________________________" << endl;
		cout << "3. Current config_________________________" << endl;
		cout << "0. Exit___________________________________" << endl;
		cout << "Yout chouse: ";
		cin >> k;
		cout << endl;
		switch (k)
		{
		case 1:
			system("netsh advfirewall set allprofiies state off");
			break;
		case 2:
			system("netsh advfirewall set allprofiies state on");
			break;
		case 3:
			system("netsh advfirewall firewall show rule name=all");
			break;
		case 0:
			system("exit");
			break;
		}
	}
	//////////////////////////////////////////////////////////////////
	HRESULT hrComInit = S_OK;
	HRESULT hr = S_OK;

	INetFwPolicy2 *pNetFwPolicy2 = NULL;
	///system("netsh advfirewall set allprofiies state off");

	// Initialize COM.
	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED
		);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (hrComInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(hrComInit))
		{
			printf("CoInitializeEx failed: 0x%08lx\n", hrComInit);
			goto Cleanup;
		}
	}

	// Retrieve INetFwPolicy2
	hr = WFCOMInitialize(&pNetFwPolicy2);
	if (FAILED(hr))
	{
		goto Cleanup;
	}

	// Disable Windows Firewall for the Domain profile
	hr = pNetFwPolicy2->put_FirewallEnabled(NET_FW_PROFILE2_DOMAIN, FALSE);
	if (FAILED(hr))
	{
		printf("put_FirewallEnabled failed for Domain: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Disable Windows Firewall for the Private profile
	hr = pNetFwPolicy2->put_FirewallEnabled(NET_FW_PROFILE2_PRIVATE, FALSE);
	if (FAILED(hr))
	{
		printf("put_FirewallEnabled failed for Private: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Disable Windows Firewall for the Public profile
	hr = pNetFwPolicy2->put_FirewallEnabled(NET_FW_PROFILE2_PUBLIC, FALSE);
	if (FAILED(hr))
	{
		printf("put_FirewallEnabled failed for Public: 0x%08lx\n", hr);
		goto Cleanup;
	}

Cleanup:

	// Release INetFwPolicy2
	if (pNetFwPolicy2 != NULL)
	{
		pNetFwPolicy2->Release();
	}

	// Uninitialize COM.
	if (SUCCEEDED(hrComInit))
	{
		CoUninitialize();
	}

	return 0;
}


// Instantiate INetFwPolicy2
HRESULT WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2)
{
	HRESULT hr = S_OK;

	hr = CoCreateInstance(
		__uuidof(NetFwPolicy2),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwPolicy2),
		(void**)ppNetFwPolicy2);

	if (FAILED(hr))
	{
		printf("CoCreateInstance for INetFwPolicy2 failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

Cleanup:
	return hr;
}
