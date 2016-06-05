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
#include "InternetConnectionMonitorThread.h"
#include "../UIMApplication.h"


const int CInternetConnectionMonitorThread::CHECK_CONNECTION_INTERVAL = 15000;


CInternetConnectionMonitorThread::CInternetConnectionMonitorThread() : 
	m_bIsConnected(FALSE)
{
}


CInternetConnectionMonitorThread::~CInternetConnectionMonitorThread()
{
}


BOOL CInternetConnectionMonitorThread::Init()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	BOOL bRet = m_eventCheckConnection.Create(NULL, TRUE, FALSE, NULL);

	if (bRet)
	{
		m_bIsConnected = CheckInternetConnection();

		bRet = Start();
	}
	else
	{
		static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
				GetLogger()->LogError(__FUNCTION__, 
				"m_eventCheckConnection.Create() failed.");
	}
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, "bRet = [%d]", bRet);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);

	return bRet;
}


void CInternetConnectionMonitorThread::Finalize()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, 
			"m_eventCheckConnection = [%x]", m_eventCheckConnection.m_h);
	
	if (m_eventCheckConnection)
	{
		m_eventCheckConnection.Set();

		Stop();
		MessageLoopWait();

		m_eventCheckConnection.Close();
	}
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


BOOL CInternetConnectionMonitorThread::IsConnected()
{
	return CheckInternetConnection();
}


void CInternetConnectionMonitorThread::RegisterCallback(IUOLMessengerInternetConnectionMonitorCallback* pCallback)
{
	POSITION pos = m_listCallbacks.Find(pCallback);

	if (!pos)
	{
		m_listCallbacks.AddTail(pCallback);
	}
}


void CInternetConnectionMonitorThread::UnregisterCallback(IUOLMessengerInternetConnectionMonitorCallback* pCallback)
{
	POSITION pos = m_listCallbacks.Find(pCallback);

	if (pos)
	{
		m_listCallbacks.RemoveAt(pos);
	}
	else
	{
		ATLASSERT(FALSE);
	}
}


void CInternetConnectionMonitorThread::Run()
{
	DWORD dwWaitReason;
	BOOL bConnected;

	while (TRUE)
	{
		dwWaitReason = ::WaitForSingleObject(m_eventCheckConnection, CHECK_CONNECTION_INTERVAL);

		if (dwWaitReason == WAIT_TIMEOUT)
		{
			bConnected = CheckInternetConnection();
			
			if (bConnected != m_bIsConnected)
			{
				::InterlockedExchange(&m_bIsConnected, bConnected);

				NotifyAll(&IUOLMessengerInternetConnectionMonitorCallback::OnInternetConnectionStateChanged, bConnected);

				if (!bConnected)
				{
					ATLTRACE(_T("No internet connection!!!\n"));
				}
			}
		}
		else if (dwWaitReason == WAIT_OBJECT_0)
		{
			break;
		}
		else
		{
			ATLASSERT(FALSE);
		}
	}
}


BOOL CInternetConnectionMonitorThread::CheckInternetConnection()
{
	DWORD dwConnectionFlags = 0;

	BOOL bConnected = ::InternetGetConnectedState(&dwConnectionFlags, 0);

#if 0
	CString strDebugMsg;
	strDebugMsg.Format(_T("ConnectionState = %d, flags = 0x%x\n"), bConnected, dwConnectionFlags); 

	::OutputDebugString((LPCTSTR) strDebugMsg);
#endif

	bConnected = bConnected && !(dwConnectionFlags & INTERNET_CONNECTION_OFFLINE);

	return bConnected;
}


void CInternetConnectionMonitorThread::NotifyAll(void (IUOLMessengerInternetConnectionMonitorCallback::*pfnHandler)(BOOL), BOOL bState)
{
	CAtlList<IUOLMessengerInternetConnectionMonitorCallback*> listHandlers;
	listHandlers.AddTailList(&m_listCallbacks);

	IUOLMessengerInternetConnectionMonitorCallback* pCallback;

	for (POSITION pos = listHandlers.GetHeadPosition(); pos; )
	{
		pCallback = listHandlers.GetNext(pos);

		if (FALSE == ::IsBadReadPtr(pCallback, sizeof(IUOLMessengerInternetConnectionMonitorCallback*)))
		{
			(pCallback->*pfnHandler)(bState);
		}
	}
}