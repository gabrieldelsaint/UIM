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

#include <interfaces/IUOLMessengerAccountManager.h>
#include <interfaces/IUOLMessengerProtocolManager.h>
#include "../ObserverRegister.h"
#include "../ObserverWrapper.h"
#include "../model/ISettings.h"
#include "../model/SettingsHandler.h"



class CAccountListEventListenerWrapper : public CObserverWrapper<CUOLMessengerAccountListEventListener>
{
public:
	CAccountListEventListenerWrapper(CUOLMessengerAccountListEventListener* pWrapped);

	virtual void OnAddAccount(IUOLMessengerAccountPtr pAccount);
	virtual void OnRemoveAccount(IUOLMessengerAccountPtr pAccount);
	virtual void OnAccountProtocolChanged(IUOLMessengerAccountPtr pAccount, const CString& strOldProtocolId);
	virtual void OnAccountUserIdChanged(IUOLMessengerAccountPtr pAccount, const CString& strOldUserId);
};

MAKEAUTOPTR(CAccountListEventListenerWrapper);



class CAccountListEventListenerNotifier
{
public:
	void RegisterListener(CUOLMessengerAccountListEventListener* pListener);
	void UnregisterListener(CUOLMessengerAccountListEventListener* pListener);
	void UnregisterAll();

	void NotifyAll(void (CUOLMessengerAccountListEventListener::*pEventHandler)(IUOLMessengerAccountPtr), IUOLMessengerAccountPtr pAccount);
	void NotifyAll(void (CUOLMessengerAccountListEventListener::*pEventHandler)(IUOLMessengerAccountPtr, const CString&), IUOLMessengerAccountPtr pAccount, const CString& strParam);

private:
	CAtlList<CAccountListEventListenerWrapperPtr>	m_listListeners;
	CComAutoCriticalSection		m_csListeners;
};




class CAccountManager : 
	public IUOLMessengerAccountManager,
	public ISettings
{
public:
	CAccountManager();
	virtual ~CAccountManager();

	virtual BOOL Init(IUOLMessengerFacade* pUOLMessengerFacade);
	virtual void Finalize();
	virtual void UpdateAccountsAuthenticationData();

protected:
	// IUOLMessengerAccountManager interface
	virtual BOOL LoadAccounts();
	virtual BOOL SaveAccounts();

	virtual IUOLMessengerAccountPtr CreateAccount(const CString& strUserId, const CString& strProtocolId);
	virtual BOOL AddAccount(IUOLMessengerAccountPtr pAccount);
	virtual BOOL RemoveAccount(IUOLMessengerAccountPtr pAccount);
	virtual BOOL RemoveAccount(const CString& strUserId, const CString& strProtocolId);
	virtual IUOLMessengerAccountPtr FindAccount(const CString& strUserId, const CString& strProtocolId);

	virtual void GetAccountList(CAtlList<IUOLMessengerAccountPtr>& listAccounts);
	virtual int GetAccountListCount();

	virtual BOOL SetAccountProtocol(IUOLMessengerAccountPtr pAccount, const CString& strProtocolId);
	virtual BOOL SetAccountUserId(IUOLMessengerAccountPtr pAccount, const CString& strUserId);

	virtual void AddAccountListEventListener(CUOLMessengerAccountListEventListener* pListener);
	virtual void RemoveAccountListEventListener(CUOLMessengerAccountListEventListener* pListener);

	// ISettings interface
	virtual void InitTagProcessMap();
	virtual void Load(MSXML::IXMLDOMNodePtr pNode, const CString& strKey);
	virtual void Save(MSXML::IXMLDOMNodePtr pNode, const CString& strKey);

private:
	DECLARE_SETTINGS_CALLBACK(CAccountManager, AccountNode);

private:
	IUOLMessengerFacade*	m_pUOLMessengerFacade;
	CAtlList<IUOLMessengerAccountPtr>		m_listAccounts;
	CAccountListEventListenerNotifier		m_eventListenerNotifier;

	CProcessMap			ms_tagProcess;
	CSettingsHandler	m_settingsHandler;

	// TODO: remove this list
	CAtlList<IUOLMessengerAccountPtr>	m_listRemovedAccounts;

	// Accounts with no protocol associated
	CAtlList<IUOLMessengerAccountPtr>	m_listUnboundAccounts;
};

MAKEAUTOPTR(CAccountManager);