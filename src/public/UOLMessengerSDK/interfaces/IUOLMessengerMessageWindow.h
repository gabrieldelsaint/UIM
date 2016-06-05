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

#include "IUOLMessengerAccount.h"
#include "IUOLMessengerContact.h"

#include "IUOLMessengerConversation.h"
#include "IUOLMessengerConversationWindow.h"


class CUOLMessengerMessageWindowObserver;


class __declspec(novtable) IUOLMessengerMessageWindow
{
public:
	virtual ~IUOLMessengerMessageWindow() {}

	virtual int AddConversation(IUOLMessengerConversationPtr pConversation) = 0;
	virtual IUOLMessengerConversationPtr RemoveConversation(int nIndex) = 0;
	virtual IUOLMessengerConversationPtr GetConversation(int nIndex) const = 0;
	
	virtual int GetConversationCount() const = 0;

	virtual BOOL CanAddMoreConversation() = 0;

	virtual IUOLMessengerConversationPtr FindConversation(IUOLMessengerAccountPtr pAccount, const CString& strContactName) = 0;
	virtual IUOLMessengerConversationPtr FindConversation(IUOLMessengerContactPtr pContact) = 0;

	virtual void SetActiveNextConversation()=0;
	virtual void SetActiveConversation(int nIndex) = 0;
	virtual void SetActiveConversation(IUOLMessengerConversationPtr pConversation) = 0;
	virtual IUOLMessengerConversationPtr GetActiveConversation() const = 0;
	virtual int GetActiveConversationIndex() const = 0;

	virtual int GetConversationIndex(IUOLMessengerConversationPtr pConversation) const = 0;
	
	virtual void Show(int nCmdShow = SW_NORMAL) = 0;
	virtual void Hide() = 0;
	virtual void Raise() = 0;
	virtual void Flash() = 0;
	virtual void FlashConversation(IUOLMessengerConversationPtr pConversation) = 0;

	virtual BOOL HasFocus() const = 0;
	virtual BOOL IsVisible() const = 0;

	virtual void ShowInputFocus() = 0;

	virtual IUOLMessengerImageButtonContainerPtr GetToolbar() const = 0;

	virtual BOOL HasUnreadMessages() = 0;

	virtual void RegisterObserver(CUOLMessengerMessageWindowObserver* pObserver) = 0;
	virtual void UnregisterObserver(CUOLMessengerMessageWindowObserver* pObserver) = 0;
};

MAKEAUTOPTR(IUOLMessengerMessageWindow);


class __declspec(novtable) IUOLMessengerMessageWindow2 : public IUOLMessengerMessageWindow
{
public:
	virtual ~IUOLMessengerMessageWindow2() {}
	
	virtual void SetActivePriorConversation() = 0;
    
    virtual BOOL CanCloseChatWindow();

	virtual IUOLMessengerConversationWindow2* FindConversationWindow(IUOLMessengerConversationPtr pConversation) = 0;
};

MAKEAUTOPTR(IUOLMessengerMessageWindow2);


class __declspec(novtable) IUOLMessengerMessageWindow3 : public IUOLMessengerMessageWindow2
{
public:
	virtual ~IUOLMessengerMessageWindow3() {}
	
	virtual void SetActiveConversation(IUOLMessengerConversationPtr pConversation, BOOL bSetFocus) = 0;
};

MAKEAUTOPTR(IUOLMessengerMessageWindow3);


class CUOLMessengerMessageWindowObserver
{
public:
	virtual ~CUOLMessengerMessageWindowObserver() {}

	virtual void OnCreateConversationWindow(IUOLMessengerMessageWindow* pMessageWindow, IUOLMessengerConversationWindow* pConversationWindow) {}
	virtual void OnDestroyConversationWindow(IUOLMessengerMessageWindow* pMessageWindow, IUOLMessengerConversationWindow* pConversationWindow) {}
	virtual void OnActivateConversationWindow(IUOLMessengerMessageWindow* pMessageWindow, IUOLMessengerConversationWindow* pConversationWindow) {}
};