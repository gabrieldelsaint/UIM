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

#pragma once

#include <interfaces/IUOLMessengerFacade.h>
#include <interfaces/IUOLMessengerAccountConnectionManager.h>
#include "../UOLMessengerAccountTraits.h"
#include "AccountConnection.h"
#include "AccountConnectionManagerObserverNotifier.h"


class CAccountConnectionManager : 
	public IUOLMessengerAccountConnectionManager3,
	public CUOLMessengerAccountListEventListener
{
public:
	CAccountConnectionManager();
	virtual ~CAccountConnectionManager();

	BOOL Init(IUOLMessengerFacade* pFacade);
	void PreFinalize();
	void Finalize();

	void NotifyConnected(IUOLMessengerAccountPtr pAccount);
	void NotifyDisconnected(IUOLMessengerAccountPtr pAccount);
	void NotifyReportDisconnect(IUOLMessengerAccountPtr pAccount, ConnectionError errorCode, const CString& strMessage);

protected:
	virtual int GetConnectedAccountsCount();
	virtual void GetConnectedAccountList(CAtlList<IUOLMessengerAccountPtr>& listAccounts);

	virtual BOOL Connect(IUOLMessengerAccountPtr pAccount); 
	virtual BOOL Disconnect(IUOLMessengerAccountPtr pAccount);
	virtual BOOL IsConnected(IUOLMessengerAccountPtr pAccount);
	virtual DWORD GetConnectionState(IUOLMessengerAccountPtr pAccount);

	virtual void ConnectAll(BOOL bAutoConnectOnly = FALSE);
	virtual void DisconnectAll();

	virtual void SetStatus(IUOLMessengerAccountPtr pAccount, DWORD dwStatus);
	virtual DWORD GetStatus(IUOLMessengerAccountPtr pAccount);
	virtual DWORD GetPreviousStatus(IUOLMessengerAccountPtr pAccount);

	virtual void UpdateServerAlias(IUOLMessengerAccountPtr pAccount);
	virtual BOOL UploadDisplayIcon(IUOLMessengerAccountPtr pAccount);

	virtual void AddReceivedAway(IUOLMessengerAccountPtr pAccount, const CString& strContact);
	virtual BOOL IsReceivedAway(IUOLMessengerAccountPtr pAccount, const CString& strContact);
	virtual void ResetReceivedAway(IUOLMessengerAccountPtr pAccount);

	virtual void SetIdleAll(UINT nSeconds);

	virtual void RegisterObserver(CUOLMessengerAccountConnectionManagerObserver* pObserver);
	virtual void UnregisterObserver(CUOLMessengerAccountConnectionManagerObserver* pObserver);

	virtual void RegisterAccountObserver(IUOLMessengerAccountPtr pAccount, CUOLMessengerAccountConnectionManagerObserver* pObserver);
	virtual void UnregisterAccountObserver(IUOLMessengerAccountPtr pAccount, CUOLMessengerAccountConnectionManagerObserver* pObserver);

	virtual BOOL UpdateExtendedCapabilities(IUOLMessengerAccount2Ptr pAccount);

	virtual void GetAccountValidStatus(IUOLMessengerAccountPtr pAccount, CAtlList<int>& listValidStatus);

	virtual void OnAddAccount(IUOLMessengerAccountPtr pAccount);
	virtual void OnRemoveAccount(IUOLMessengerAccountPtr pAccount);

private:
	CAccountConnectionPtr FindAccountConnection(IUOLMessengerAccountPtr pAccount);
	CAccountConnectionPtr CreateAccountConnection(IUOLMessengerAccountPtr pAccount);
	int GetProtocolUserStatus(CIMProtocol* pProtocol, DWORD dwUserStatus);
	CAccountConnectionManagerObserverNotifierPtr FindObserverNotifier(IUOLMessengerAccountPtr pAccount);
	void InternalSetStatus(CAccountConnectionPtr pAccountConnection, DWORD dwStatus, BOOL bAsync = FALSE);
	void InternalUpdateServerAlias(CAccountConnectionPtr pAccountConnection, BOOL bAsync = FALSE);
	BOOL InternalUploadDisplayIcon(CAccountConnectionPtr pAccountConnection, BOOL bAsync = FALSE);
	BOOL InternalUpdateExtendedCapabilities(CAccountConnectionPtr pAccountConnection);
	
	void DisconnectAll(BOOL bMakeItAsync);
	BOOL Disconnect(IUOLMessengerAccountPtr pAccount, BOOL bMakeItAsync);

private:
	IUOLMessengerFacade*	m_pFacade;

	typedef CAtlMap<IUOLMessengerAccountPtr, CAccountConnectionPtr, CUOLMessengerAccountTraits> CAccountConnectionMap;
	CAccountConnectionMap	m_mapAccountConnection;
	CComAutoCriticalSection m_csAccountConnections;

	typedef CAtlMap<IUOLMessengerAccountPtr, CAccountConnectionManagerObserverNotifierPtr, CUOLMessengerAccountTraits> CObserverNotifierMap;
	CObserverNotifierMap	m_mapAccountObserverNotifier;
	CComAutoCriticalSection m_csAccountObserverNotifier;

	CAccountConnectionManagerObserverNotifier	m_observerNotifier;
	CComAutoCriticalSection						m_csObserverNotifier;
};

MAKEAUTOPTR(CAccountConnectionManager);
