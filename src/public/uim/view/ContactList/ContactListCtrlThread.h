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

#include <interfaces/IUOLMessengerContact.h>
#include <interfaces/IUOLMessengerGroup.h>
#include <interfaces/IUOLMessengerContactListCtrl.h>

#include <util/Thread.h>
#include <util/IRunnable.h>


///////////////////////////////////////////////////////////////////////////////
// CContactListCtrlThread Class
///////////////////////////////////////////////////////////////////////////////

class CContactListCtrlThread : public IRunnable
{
public:
	CContactListCtrlThread(HWND hContactListCtrlWnd);
	virtual ~CContactListCtrlThread();
	
	virtual BOOL StartListCtrlThread();
	virtual BOOL StopListCtrlThread();
	
	void AsyncAddContact(IUOLMessengerContactPtr pContact);
	void AsyncRemoveContact(IUOLMessengerContactPtr pContact);
	void AsyncRemoveContacts(CAtlList<IUOLMessengerContactPtr>& listContacts);
	void AsyncMoveContact(IUOLMessengerContactPtr pContact, const CString& strOldGroup);
	void AsyncAddGroup(IUOLMessengerGroupPtr pGroup);
	void AsyncRemoveGroup(IUOLMessengerGroupPtr pGroup);
	void AsyncRemoveAllGroups();
	
public:
	
	enum OperationId
	{
		LIST_ADD_CONTACT = 0x299, 
		LIST_REMOVE_CONTACT, 
		LIST_REMOVE_CONTACTS, 
		LIST_MOVE_CONTACT, 
		LIST_ADD_GROUP, 
		LIST_REMOVE_GROUP, 
		LIST_REMOVE_ALL_GROUPS
	};
	
	struct ListOperationInfo
	{
		UINT uiOperationId;
	};
	
	struct ListContactOperationInfo
	{
		UINT uiOperationId;
		IUOLMessengerContactPtr pContact;
	};
	
	struct ListRemoveContactsInfo
	{
		UINT uiOperationId;
		CAtlList<IUOLMessengerContactPtr> listContacts;
	};
	
	struct ListMoveContactInfo
	{
		UINT uiOperationId;
		IUOLMessengerContactPtr pContact;
		CString strOldGroup;
	};
	
	struct ListGroupOperationInfo
	{
		UINT uiOperationId;
		IUOLMessengerGroupPtr pGroup;
	};
	
	struct ListRemoveAllGroupsInfo
	{
		UINT uiOperationId;
	};
	
protected:
	
	ListOperationInfo* GetNextOperation();
	void AddNewOperation(ListOperationInfo* pOperationInfo);
	
	void ClearAllOperations();
	
	void ExecuteOperation(ListOperationInfo* pOperationInfo);
	
	virtual void Run();
	
private:
	HWND								m_hContactListCtrlWnd;
	IUOLMessengerContactListCtrlPtr		m_pContactListCtrl;
	
	CAtlList<ListOperationInfo*>		m_operationsList;
	CComAutoCriticalSection				m_csOperationsList;
	
	CEvent		m_terminateEvent;
	CThread		m_thread;
	BOOL		m_bStopFlag;
};

MAKEAUTOPTR(CContactListCtrlThread);

