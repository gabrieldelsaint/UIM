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

#include "IUOLMessengerContact.h"


class CUOLMessengerContactListObserver;


class __declspec(novtable) IUOLMessengerContactList
{
public:
	virtual ~IUOLMessengerContactList() {}

	virtual IUOLMessengerContactPtr CreateContact(IUOLMessengerAccountPtr pAccount, const CString& strUser);
	virtual BOOL AddContact(IUOLMessengerContactPtr pContact, const CString& strGroup) = 0;
	virtual IUOLMessengerContactPtr AddContact(IUOLMessengerAccountPtr pAccount, const CString& strUser, const CString& strGroup) = 0;
	virtual IUOLMessengerContactPtr RemoveContact(IUOLMessengerAccountPtr pAccount, const CString& strContact) = 0;
	virtual IUOLMessengerContactPtr RemoveContact(const CString& strAccountUserId, const CString& strAccountProtocolId, const CString& strContact) = 0;
	virtual IUOLMessengerContactPtr RemoveContact(IUOLMessengerAccountPtr pAccount, const CString& strContact, const CString& strGroup) = 0;
	virtual IUOLMessengerContactPtr RemoveContact(const CString& strAccountUserId, const CString& strAccountProtocolId, const CString& strContact, const CString& strGroup) = 0;
	virtual IUOLMessengerContactPtr FindContact(IUOLMessengerAccountPtr pAccount, const CString& strContact) = 0;
	virtual IUOLMessengerContactPtr FindContact(const CString& strAccountUserId, const CString& strAccountProtocolId, const CString& strContact) = 0;
	virtual IUOLMessengerContactPtr FindContact(IUOLMessengerAccountPtr pAccount, const CString& strContact, const CString& strGroup) = 0;
	virtual IUOLMessengerContactPtr FindContact(const CString& strAccountUserId, const CString& strAccountProtocolId, const CString& strContact, const CString& strGroup) = 0;
	virtual int FindContacts(IUOLMessengerAccountPtr pAccount, const CString& strContact, CAtlList<IUOLMessengerContactPtr>& listContacts) = 0;
	virtual int FindContacts(const CString& strAccountUserId, const CString& strAccountProtocolId, const CString& strContact, CAtlList<IUOLMessengerContactPtr>& listContacts) = 0;
	virtual int FindContacts(IUOLMessengerAccountPtr pAccount, CAtlList<IUOLMessengerContactPtr>& listContacts) = 0;
	virtual int FindContacts(const CString& strAccountUserId, const CString& strAccountProtocolId, CAtlList<IUOLMessengerContactPtr>& listContacts) = 0;
	virtual void RemoveAllContacts(IUOLMessengerAccountPtr pAccount) = 0;
	virtual void RemoveAllContacts(const CString& strAccountUserId, const CString& strAccountProtocolId) = 0;
	virtual BOOL MoveContact(IUOLMessengerAccountPtr pAccount, const CString& strContact, const CString& strOldGroup, const CString& strGroup) = 0;
	virtual BOOL MoveContact(const CString& strAccountUserId, const CString& strAccountProtocolId, const CString& strContact, const CString& strOldGroup, const CString& strGroup) = 0;

	virtual IUOLMessengerGroupPtr AddGroup(const CString& strGroup) = 0;
	virtual IUOLMessengerGroupPtr RemoveGroup(const CString& strGroup) = 0;
	virtual IUOLMessengerGroupPtr FindGroup(const CString& strGroup) = 0;
	virtual BOOL RenameGroup(const CString& strOldGroup, const CString& strNewGroup) = 0;
	virtual void RemoveAllGroups() = 0;

	virtual void GetGroupList(CAtlList<IUOLMessengerGroupPtr>& listGroups) = 0;

	virtual void RegisterObserver(CUOLMessengerContactListObserver* pObserver) = 0;
	virtual void UnregisterObserver(CUOLMessengerContactListObserver* pObserver) = 0;
};

MAKEAUTOPTR(IUOLMessengerContactList);

class CUOLMessengerContactListObserver
{
public:
	virtual ~CUOLMessengerContactListObserver() {}

	virtual void OnAddContact(IUOLMessengerContactPtr pContact) {}
	virtual void OnRemoveContact(IUOLMessengerContactPtr pContact) {}
	virtual void OnRemoveContacts(CAtlList<IUOLMessengerContactPtr>& listContacts) {}
	virtual void OnMoveContact(IUOLMessengerContactPtr pContact, const CString& strOldGroup) {}
	virtual void OnAddGroup(IUOLMessengerGroupPtr pGroup) {}
	virtual void OnRemoveGroup(IUOLMessengerGroupPtr pGroup) {}
	virtual void OnRemoveAllGroups() {}

	//virtual void OnRenameGroup(IUOLMessengerGroupPtr pGroup, const CString& strOldName) {}
};