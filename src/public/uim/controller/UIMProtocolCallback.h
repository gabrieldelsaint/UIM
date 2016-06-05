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
 
#include "UIMApplication.h"
#include "../../../public/protocols/improtocolcallback.h"
#include "../view/GroupListCtrl/GroupListCtrl.h"
#include "../view/UserStatusPanel.h"
#include "../view/IMContact.h"

using namespace GroupListCtrl;

class CUIMProtocolCallback //: public CIMProtocolCallback
{
public:
	CUIMProtocolCallback(CIMProtocol* pProtocol, CGroupListCtrl* pGroupListCtrl, CUserStatusPanel* pUserStatusPanel);
	virtual ~CUIMProtocolCallback(void);

	//virtual void OnConnected(const string& strUser);
	//virtual void OnDisconnected(const string& strUser);
	//virtual void OnReportDisconnect(const string& strUser, const string& strText);

	//virtual void OnContactListUpdate(const string& strUser, const CContactInfo& contactInfo, const string& strGroup);
	//virtual void OnContactRemoved(const string& strUser, const string& strContact);
	//virtual void OnContactGotInfo(const string& strUser, const string& strContact, const string& strInfo);
	//virtual void OnContactIconReceived(const string& strUser, const string& strContact, const char* pIconData, int nLen);
	//virtual void OnContactAliasReceived(const string& strUser, const string& strContact, const string& strAlias);

	//virtual void OnGroupRemoved(const string& strUser, const string& strGroup);

	//virtual void OnIMReceived(const string& strToUser, const string& strFromUser, const string& strText);
	//virtual void OnIMSent(const string& strFromUser, const string& strToUser, const string& strText);
	//virtual void OnIMSendError(const string& strFromUser, const string& strToUser, IMProtocolError sendError);

	//virtual void OnContactSignedOn(const string& strAccountUser, const string& strContact);
	//virtual void OnContactSignedOff(const string& strAccountUser, const string& strContact);
	//virtual void OnContactAway(const string& strAccountUser, const string& strContact);
	//virtual void OnContactAwayReturn(const string& strAccountUser, const string& strContact);
	//virtual void OnContactIdle(const string& strAccountUser, const string& strContact);
	//virtual void OnContactIdleReturn(const string& strAccountUser, const string& strContact);
	//virtual void OnContactTyping(const string& strAccountUser, const string& strContact, TypingState state);

	//virtual void OnConversationWindowClosed(const string& strAccountUser, const string& strContact);
	//virtual void OnConversationTimeout(const string& strAccountUser, const string& strContact);

	//virtual void OnPermitAdded(const string& strAccountUser, const string& strContact);
	//virtual void OnDenyAdded(const string& strAccountUser, const string& strContact);
	//virtual void OnPermitRemoved(const string& strAccountUser, const string& strContact);
	//virtual void OnDenyRemoved(const string& strAccountUser, const string& strContact);

private:
	virtual void AddMessage(CIMContactPtr pContact, const string& strText);

private:
	CIMProtocol*				m_pProtocol;
    CUIMApplication*			m_pApplication;
	CGroupListCtrl*				m_pGroupListCtrl;
	CUserStatusPanel*			m_pUserStatusPanel;
	CComAutoCriticalSection		m_cs;
};