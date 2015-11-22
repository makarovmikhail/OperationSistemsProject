
// MainDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "myFireWall.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <stdio.h>
#include <netfw.h>
#include <iostream>

#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "oleaut32.lib" )

#define NET_FW_IP_PROTOCOL_TCP_NAME L"TCP"
#define NET_FW_IP_PROTOCOL_UDP_NAME L"UDP"

#define NET_FW_RULE_DIR_IN_NAME L"In"
#define NET_FW_RULE_DIR_OUT_NAME L"Out"

#define NET_FW_RULE_ACTION_BLOCK_NAME L"Block"
#define NET_FW_RULE_ACTION_ALLOW_NAME L"Allow"

#define NET_FW_RULE_ENABLE_IN_NAME L"TRUE"
#define NET_FW_RULE_DISABLE_IN_NAME L"FALSE"


// Forward declarations
void        DumpFWRulesInCollection(INetFwRule* FwRule);
HRESULT     WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CMainlDlg



CMainlDlg::CMainlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RULES, m_ctrlList);
}

BEGIN_MESSAGE_MAP(CMainlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ON, &CMainlDlg::OnClickFireWallOn)
	ON_BN_CLICKED(IDC_BUTTON_OFF, &CMainlDlg::OnClickFireWallOff)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_RULE, &CMainlDlg::OnClickShowRule)
END_MESSAGE_MAP()


// обработчики сообщений CMainlDlg

BOOL CMainlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	m_ctrlList.InsertColumn(0, L"Name", LVCFMT_LEFT, 250);
	m_ctrlList.InsertColumn(1, L"Description", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(2, L"Application Name", LVCFMT_LEFT, 150);
	m_ctrlList.InsertColumn(3, L"Service Name", LVCFMT_LEFT, 250);
	m_ctrlList.InsertColumn(4, L"IP Protocol", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(5, L"Local Ports", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(6, L"Remote Ports", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(7, L"ICMP TypeCode", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(8, L"Local Addresseses", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(9, L"Remote Addresseses", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(10, L"Profile", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(11, L"Direction", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(12, L"Action", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(13, L"Interfaces", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(14, L"Interface Types", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(15, L"Enabled", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(16, L"Grouping", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(17, L"Edge Traversal", LVCFMT_LEFT, 100);











	//for (int i = 0; i < 10; ++i)
	//{
	//	CString sName;
	//	sName.Format(L"Name %d", i + 1);
	//	int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), sName, -1);

	//	m_ctrlList.SetItemText(nItem, 1, L"5");
	//}
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMainlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMainlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMainlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
void CMainlDlg::OnClickFireWallOn()			//Reaction on ON Button
{
	FireOn();
}


void CMainlDlg::OnClickFireWallOff()		//Reaction on OFF Button
{
	FireOff();
}


int CMainlDlg::FireOff()				//Off all profiles Win FireWall
{
	HRESULT hrComInit = S_OK;
	HRESULT hr = S_OK;

	INetFwPolicy2 *pNetFwPolicy2 = NULL;

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



int CMainlDlg::FireOn()			//On all profiles FireWall
{
	HRESULT hrComInit = S_OK;
	HRESULT hr = S_OK;

	INetFwPolicy2 *pNetFwPolicy2 = NULL;

	// Rule group to use
	BSTR bstrRuleGroup = SysAllocString(L"File and Printer Sharing");
	VARIANT_BOOL bIsEnabled = FALSE;

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

	// Check if the rule group is enabled for the Private profile
	hr = pNetFwPolicy2->put_FirewallEnabled(NET_FW_PROFILE2_PRIVATE, TRUE);
	// Check if the rule group is enabled for the Domain profile
	hr = pNetFwPolicy2->put_FirewallEnabled(NET_FW_PROFILE2_DOMAIN, TRUE);
	// Check if the rule group is enabled for the Public profile
	hr = pNetFwPolicy2->put_FirewallEnabled(NET_FW_PROFILE2_PUBLIC, TRUE);


	if (!bIsEnabled)
	{
		// Group is not enabled for the Private profile - need to enable it
		printf("Rule Group is NOT enabled for the Private profile. Calling EnableRuleGroup...");

		hr = pNetFwPolicy2->EnableRuleGroup(NET_FW_PROFILE2_PRIVATE, bstrRuleGroup, TRUE);
		if (FAILED(hr))
		{
			printf("EnableRuleGroup failed: 0x%08lx\n", hr);
			goto Cleanup;
		}
	}
	else
	{
		printf("Rule Group is enabled for the Private profile");
	}

Cleanup:

	// Free BSTR's
	SysFreeString(bstrRuleGroup);

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

void CMainlDlg::OnClickShowRule()
{
	// TODO: Add your control notification handler code here
	showAllRules();
}


int CMainlDlg::showAllRules()
{
	HRESULT hrComInit = S_OK;
	HRESULT hr = S_OK;

	ULONG cFetched = 0;
	CComVariant var;

	IUnknown *pEnumerator;
	IEnumVARIANT* pVariant = NULL;

	INetFwPolicy2 *pNetFwPolicy2 = NULL;
	INetFwRules *pFwRules = NULL;
	INetFwRule *pFwRule = NULL;
	long fwRuleCount;

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
			wprintf(L"CoInitializeEx failed: 0x%08lx\n", hrComInit);
			goto Cleanup;
		}
	}

	// Retrieve INetFwPolicy2
	hr = WFCOMInitialize(&pNetFwPolicy2);
	if (FAILED(hr))
	{
		goto Cleanup;
	}

	// Retrieve INetFwRules
	hr = pNetFwPolicy2->get_Rules(&pFwRules);
	if (FAILED(hr))
	{
		wprintf(L"get_Rules failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Obtain the number of Firewall rules
	hr = pFwRules->get_Count(&fwRuleCount);
	if (FAILED(hr))
	{
		wprintf(L"get_Count failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	wprintf(L"The number of rules in the Windows Firewall are %d\n", fwRuleCount);
	// Iterate through all of the rules in pFwRules
	pFwRules->get__NewEnum(&pEnumerator);

	if (pEnumerator)
	{
		hr = pEnumerator->QueryInterface(__uuidof(IEnumVARIANT), (void **)&pVariant);
	}

	while (SUCCEEDED(hr) && hr != S_FALSE)
	{
		var.Clear();
		hr = pVariant->Next(1, &var, &cFetched);

		if (S_FALSE != hr)
		{
			if (SUCCEEDED(hr))
			{
				hr = var.ChangeType(VT_DISPATCH);
			}
			if (SUCCEEDED(hr))
			{
				hr = (V_DISPATCH(&var))->QueryInterface(__uuidof(INetFwRule), reinterpret_cast<void**>(&pFwRule));
			}

			if (SUCCEEDED(hr))
			{
				// Output the properties of this rule
				variant_t InterfaceArray;
				variant_t InterfaceString;
				VARIANT_BOOL bEnabled;
				BSTR bstrVal;

				long lVal = 0;
				long lProfileBitmask = 0;

				NET_FW_RULE_DIRECTION fwDirection;
				NET_FW_ACTION fwAction;

				struct ProfileMapElement
				{
					NET_FW_PROFILE_TYPE2 Id;
					LPCWSTR Name;
				};

				ProfileMapElement ProfileMap[3];
				ProfileMap[0].Id = NET_FW_PROFILE2_DOMAIN;
				ProfileMap[0].Name = L"Domain";
				ProfileMap[1].Id = NET_FW_PROFILE2_PRIVATE;
				ProfileMap[1].Name = L"Private";
				ProfileMap[2].Id = NET_FW_PROFILE2_PUBLIC;
				ProfileMap[2].Name = L"Public";

				wprintf(L"---------------------------------------------\n");

				std::cout << "dd";
				int nItem;
				if (SUCCEEDED(pFwRule->get_Name(&bstrVal)))
				{
					wprintf(L"Name:             %s\n", bstrVal);
					/*MessageBox(bstrVal, L"cd", MB_OK |
						MB_ICONINFORMATION);*/
					nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), bstrVal, -1);
				}

				if (SUCCEEDED(pFwRule->get_Description(&bstrVal)))
				{
					wprintf(L"Description:      %s\n", bstrVal);
					m_ctrlList.SetItemText(nItem, 1, bstrVal);
				}

				if (SUCCEEDED(pFwRule->get_ApplicationName(&bstrVal)))
				{
					wprintf(L"Application Name: %s\n", bstrVal);
					m_ctrlList.SetItemText(nItem, 2, bstrVal);
				}

				if (SUCCEEDED(pFwRule->get_ServiceName(&bstrVal)))
				{
					wprintf(L"Service Name:     %s\n", bstrVal);
					m_ctrlList.SetItemText(nItem, 3, bstrVal);
				}

				if (SUCCEEDED(pFwRule->get_Protocol(&lVal)))
				{
					switch (lVal)
					{
					case NET_FW_IP_PROTOCOL_TCP:

						wprintf(L"IP Protocol:      %s\n", NET_FW_IP_PROTOCOL_TCP_NAME);
						m_ctrlList.SetItemText(nItem, 4, NET_FW_IP_PROTOCOL_TCP_NAME);
						break;

					case NET_FW_IP_PROTOCOL_UDP:

						wprintf(L"IP Protocol:      %s\n", NET_FW_IP_PROTOCOL_UDP_NAME);
						m_ctrlList.SetItemText(nItem, 4, NET_FW_IP_PROTOCOL_UDP_NAME);

						break;

					default:

						break;
					}

					if (lVal != NET_FW_IP_VERSION_V4 && lVal != NET_FW_IP_VERSION_V6)
					{
						if (SUCCEEDED(pFwRule->get_LocalPorts(&bstrVal)))
						{
							wprintf(L"Local Ports:      %s\n", bstrVal);
							m_ctrlList.SetItemText(nItem, 5, bstrVal);
						}

						if (SUCCEEDED(pFwRule->get_RemotePorts(&bstrVal)))
						{
							wprintf(L"Remote Ports:      %s\n", bstrVal);
							m_ctrlList.SetItemText(nItem, 6, bstrVal);

						}
					}
					else
					{
						if (SUCCEEDED(pFwRule->get_IcmpTypesAndCodes(&bstrVal)))
						{
							wprintf(L"ICMP TypeCode:      %s\n", bstrVal);
							m_ctrlList.SetItemText(nItem, 7, bstrVal);

						}
					}
				}

				if (SUCCEEDED(pFwRule->get_LocalAddresses(&bstrVal)))
				{
					wprintf(L"LocalAddresses:   %s\n", bstrVal);
					m_ctrlList.SetItemText(nItem, 8, bstrVal);

				}

				if (SUCCEEDED(pFwRule->get_RemoteAddresses(&bstrVal)))
				{
					wprintf(L"RemoteAddresses:  %s\n", bstrVal);
					m_ctrlList.SetItemText(nItem, 9, bstrVal);

				}

				if (SUCCEEDED(pFwRule->get_Profiles(&lProfileBitmask)))
				{
					// The returned bitmask can have more than 1 bit set if multiple profiles 
					//   are active or current at the same time

					for (int i = 0; i<3; i++)
					{
						if (lProfileBitmask & ProfileMap[i].Id)
						{
							wprintf(L"Profile:  %s\n", ProfileMap[i].Name);
							m_ctrlList.SetItemText(nItem, 10, ProfileMap[i].Name);

						}
					}
				}

				if (SUCCEEDED(pFwRule->get_Direction(&fwDirection)))
				{
					switch (fwDirection)
					{
					case NET_FW_RULE_DIR_IN:

						wprintf(L"Direction:        %s\n", NET_FW_RULE_DIR_IN_NAME);
						m_ctrlList.SetItemText(nItem, 11, NET_FW_RULE_DIR_IN_NAME);

						break;

					case NET_FW_RULE_DIR_OUT:

						wprintf(L"Direction:        %s\n", NET_FW_RULE_DIR_OUT_NAME);
						m_ctrlList.SetItemText(nItem, 11, NET_FW_RULE_DIR_IN_NAME);

						break;

					default:

						break;
					}
				}

				if (SUCCEEDED(pFwRule->get_Action(&fwAction)))
				{
					switch (fwAction)
					{
					case NET_FW_ACTION_BLOCK:

						wprintf(L"Action:           %s\n", NET_FW_RULE_ACTION_BLOCK_NAME);
						m_ctrlList.SetItemText(nItem, 12, NET_FW_RULE_ACTION_BLOCK_NAME);

						break;

					case NET_FW_ACTION_ALLOW:

						wprintf(L"Action:           %s\n", NET_FW_RULE_ACTION_ALLOW_NAME);
						m_ctrlList.SetItemText(nItem, 12, NET_FW_RULE_ACTION_ALLOW_NAME);

						break;

					default:

						break;
					}
				}

				if (SUCCEEDED(pFwRule->get_Interfaces(&InterfaceArray)))
				{
					if (InterfaceArray.vt != VT_EMPTY)
					{
						SAFEARRAY    *pSa = NULL;

						pSa = InterfaceArray.parray;

						for (long index = pSa->rgsabound->lLbound; index < (long)pSa->rgsabound->cElements; index++)
						{
							SafeArrayGetElement(pSa, &index, &InterfaceString);
							wprintf(L"Interfaces:       %s\n", (BSTR)InterfaceString.bstrVal);
							m_ctrlList.SetItemText(nItem, 13, (BSTR)InterfaceString.bstrVal);
						}
					}
				}

				if (SUCCEEDED(pFwRule->get_InterfaceTypes(&bstrVal)))
				{
					wprintf(L"Interface Types:  %s\n", bstrVal);
					m_ctrlList.SetItemText(nItem, 14, bstrVal);

				}

				if (SUCCEEDED(pFwRule->get_Enabled(&bEnabled)))
				{
					if (bEnabled)
					{
						wprintf(L"Enabled:          %s\n", NET_FW_RULE_ENABLE_IN_NAME);
						m_ctrlList.SetItemText(nItem, 15, NET_FW_RULE_ENABLE_IN_NAME);

					}
					else
					{
						wprintf(L"Enabled:          %s\n", NET_FW_RULE_DISABLE_IN_NAME);
						m_ctrlList.SetItemText(nItem, 15, NET_FW_RULE_DISABLE_IN_NAME);

					}
				}

				if (SUCCEEDED(pFwRule->get_Grouping(&bstrVal)))
				{
					wprintf(L"Grouping:         %s\n", bstrVal);
					m_ctrlList.SetItemText(nItem, 16, bstrVal);

				}

				if (SUCCEEDED(pFwRule->get_EdgeTraversal(&bEnabled)))
				{
					if (bEnabled)
					{
						wprintf(L"Edge Traversal:   %s\n", NET_FW_RULE_ENABLE_IN_NAME);
						m_ctrlList.SetItemText(nItem, 17, NET_FW_RULE_ENABLE_IN_NAME);

					}
					else
					{
						wprintf(L"Edge Traversal:   %s\n", NET_FW_RULE_DISABLE_IN_NAME);
						m_ctrlList.SetItemText(nItem, 17, NET_FW_RULE_DISABLE_IN_NAME);

					}
				}
			}
		}
	}

Cleanup:

	// Release pFwRule
	if (pFwRule != NULL)
	{
		pFwRule->Release();
	}

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

