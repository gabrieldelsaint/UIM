/* UOL Messenger
 * Copyright (c) 2005 Universo Online S/A
 *
 * Direitos Autorais Reservados
 * All rights reserved
 *
 * Este programa � software livre; voc� pode redistribu�-lo e/ou modific�-lo
 * sob os termos da Licen�a P�blica Geral GNU conforme publicada pela Free
 * Software Foundation; tanto a vers�o 2 da Licen�a, como (a seu crit�rio)
 * qualquer vers�o posterior.
 * Este programa � distribu�do na expectativa de que seja �til, por�m,
 * SEM NENHUMA GARANTIA; nem mesmo a garantia impl�cita de COMERCIABILIDADE
 * OU ADEQUA��O A UMA FINALIDADE ESPEC�FICA. Consulte a Licen�a P�blica Geral
 * do GNU para mais detalhes. 
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral do GNU junto
 * com este programa; se n�o, escreva para a Free Software Foundation, Inc.,
 * no endere�o 59 Temple Street, Suite 330, Boston, MA 02111-1307 USA. 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Universo Online S/A - A/C: UOL Messenger 5o. Andar
 * Avenida Brigadeiro Faria Lima, 1.384 - Jardim Paulistano
 * S�o Paulo SP - CEP 01452-002 - BRASIL  */
 
#include "stdafx.h"
#include "Register.h"



const int CRegister::m_ErrorParams = 1;
const int CRegister::m_ErrorRegister = 2;
const int CRegister::m_ErrorUnRegister = 3;
const int CRegister::m_ErrorInstance = 4;

const int CRegister::m_Ok = 0;

const CString CRegister::m_strMutex = "UOLIMSingleInstanceMutex";


CRegister::CRegister()
{
}

CRegister::~CRegister()
{
}

int CRegister::ExecCommand(const CString& strCmdLine)
{
	CString strOption;
	CString strAppName;
	int iStart = 0;

	if(!strCmdLine.IsEmpty())
	{
        strOption = strCmdLine.Tokenize(" ", iStart);
		strAppName = strCmdLine.Mid(iStart, strCmdLine.GetLength() - iStart);

		if (!strOption.IsEmpty() && !strAppName.IsEmpty())
		{
            if (strOption.Compare("-ie") == 0)
			{
                return (RegExeCommand(strAppName, " /RegServer"));
			}
			else if (strOption.Compare("-ia") == 0)
			{
				return (Register(strAppName));
			}
			else if(strOption.Compare("-ue") == 0)
			{
				return (RegExeCommand(strAppName, " /UnRegServer"));
			}
			else if(strOption.Compare("-ua") == 0)
			{
				return (UnRegister(strAppName));
			}
		}
	}

	return (m_ErrorParams);
}

int CRegister::Register(const CString& strAppName)
{
	int nError = m_ErrorRegister;

	HRESULT hr = ::CoInitialize(NULL);

	if (SUCCEEDED(hr))
	{
		try
		{
			ctrlcenter::IRegisterSoftwareComponentPtr pRegisterSoftwareComponent;

			hr = pRegisterSoftwareComponent.CreateInstance("ctrlcenter.RegisterSoftwareComponent");

			if (SUCCEEDED(hr))
			{
				_bstr_t bstrSoftwareID = strAppName;

				hr = pRegisterSoftwareComponent->QuerySoftwarePresence(bstrSoftwareID);

				if (hr == S_FALSE)
				{
					hr = pRegisterSoftwareComponent->RegisterSoftware(bstrSoftwareID);

					if (SUCCEEDED(hr))
					{
						nError = m_Ok;
					}
				}
				else if(hr == S_OK)
				{
					nError = m_Ok;
				}

				pRegisterSoftwareComponent.Release();
			}
			else
			{
				nError = m_ErrorInstance;
			}
		}
		catch (const _com_error& e) 
		{
			MSGASSERT(e.ErrorMessage());
		}

		::CoUninitialize();
	}
	
	return nError;
}

int CRegister::UnRegister(const CString& strAppName)
{
	int nError = m_ErrorUnRegister;

	HRESULT hr = ::CoInitialize(NULL);

	if (SUCCEEDED(hr))
	{
		try
		{
			ctrlcenter::IRegisterSoftwareComponentPtr pRegisterSoftwareComponent;

			hr = pRegisterSoftwareComponent.CreateInstance("ctrlcenter.RegisterSoftwareComponent");

			if (SUCCEEDED(hr))
			{
				_bstr_t bstrSoftwareID = strAppName;

				hr = pRegisterSoftwareComponent->UnregisterSoftware(bstrSoftwareID);

				if (SUCCEEDED(hr))
				{
					nError = m_Ok;
				}
			}
			else
			{
				nError = m_ErrorInstance;
			}

			pRegisterSoftwareComponent.Release();
		}
		catch (const _com_error& e) 
		{
			MSGASSERT(e.ErrorMessage());
		}

		::CoUninitialize();
	}

	return nError;
}

int CRegister::RegExeCommand(const CString& strComponent, const LPTSTR& lpszParam)
{
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	HRESULT hResult = 0;

	BOOL bOk = ::CreateProcess(strComponent, lpszParam, 0 ,0, FALSE, 0, 0, 0, &si, &pi);
	
	if (!bOk)
	{

        hResult = HRESULT_FROM_WIN32(GetLastError());

		return hResult;
	}

	::WaitForSingleObject(pi.hProcess, 10000);

	DWORD dw = 0;

	::GetExitCodeProcess(pi.hProcess, &dw);

	if (dw == STILL_ACTIVE) 
	{
		::TerminateProcess(pi.hProcess, (UINT)E_FAIL);
		::WaitForSingleObject(pi.hProcess, 5000);
		::GetExitCodeProcess(pi.hProcess, &dw);

		hResult = E_FAIL;
	}
	else
	{
		hResult = dw;
	}

    ::CloseHandle(pi.hProcess);
    ::CloseHandle(pi.hThread);

	return hResult;
}
