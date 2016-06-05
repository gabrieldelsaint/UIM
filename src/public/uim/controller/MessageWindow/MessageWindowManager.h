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

#include <interfaces/IUOLMessengerMessageWindowManager.h>
#include "../../ObserverRegister.h"
#include "../../view/MessageWindow.h"



class CMessageWindowObserverNotifier : public CObserverRegister<CUOLMessengerMessageWindowManagerObserver>
{
public:
	void NotifyAll(void (CUOLMessengerMessageWindowManagerObserver::*pfnUpdate)(IUOLMessengerMessageWindow*), IUOLMessengerMessageWindow* pMessageWindow);
};




class CMessageWindowManager : 
	public IUOLMessengerMessageWindowManager2,
	public CMessageWindowFrameObserver,
	public CWindowImpl<CMessageWindowManager>
{
public:
	DECLARE_WND_CLASS("MessageWindowManager");

	CMessageWindowManager();
	virtual ~CMessageWindowManager();

	virtual BOOL Init();
	virtual void Finalize();

protected:
	virtual IUOLMessengerMessageWindowPtr CreateMessageWindow();
	virtual IUOLMessengerMessageWindowPtr FindConversationMessageWindow(IUOLMessengerContactPtr pContact, IUOLMessengerConversationPtr& pConversation);
	virtual IUOLMessengerMessageWindowPtr FindConversationMessageWindow(IUOLMessengerAccountPtr pAccount, const CString& strContactName, IUOLMessengerConversationPtr& pConversation);
    virtual IUOLMessengerMessageWindowPtr FindConversationMessageWindow(const CString& strChatKey, IUOLMessengerConversationPtr& pConversation);

	virtual BOOL DestroyMessageWindow(IUOLMessengerMessageWindow* pMessageWindow);

	virtual void GetMessageWindowList(CAtlList<IUOLMessengerMessageWindowPtr>& listMessageWindows);

	virtual IUOLMessengerMessageWindowPtr GetFirstMessageWindow();
	virtual IUOLMessengerMessageWindowPtr GetLastMessageWindow();

	virtual int GetMessageWindowCount() const;

	virtual void RegisterObserver(CUOLMessengerMessageWindowManagerObserver* pObserver);
	virtual void UnregisterObserver(CUOLMessengerMessageWindowManagerObserver* pObserver);

	enum
	{
		WM_USER_CREATE_MESSAGE_WINDOW = WM_USER + 0x200,
		WM_USER_DESTROY_MESSAGE_WINDOW
	};

	BEGIN_MSG_MAP(CMessageWindowManager)
		MESSAGE_HANDLER(WM_USER_CREATE_MESSAGE_WINDOW, OnCreateMessageWindow)
		MESSAGE_HANDLER(WM_USER_DESTROY_MESSAGE_WINDOW, OnDestroyMessageWindow)
	END_MSG_MAP()

	LRESULT OnCreateMessageWindow(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroyMessageWindow(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);

protected:
	virtual void OnCreateWindow(CMessageWindowFrame* pMessageWindowFrame);
	virtual void OnDestroyWindow(CMessageWindowFrame* pMessageWindowFrame);

private:
	CMessageWindowObserverNotifier	m_observerNotifier;

	CAtlList<CMessageWindowFramePtr> m_listMessageWindows;
};

MAKEAUTOPTR(CMessageWindowManager);