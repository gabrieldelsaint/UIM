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
 

#ifndef _PURPLE_PROTOCOL_ASYNC_EXEC_H
#define _PURPLE_PROTOCOL_ASYNC_EXEC_H


#include <list>
#include <string>
#include "PurpleProtocol.h"


// General structure to handle operations...
//
struct DUMMY_OPERATION
{
	int		iParamType;
};


typedef std::list<DUMMY_OPERATION*>  CAsyncOperationList;


class CPurpleProtocolAsyncExec
{
public:
	
	enum AsyncOperationType
	{
		AOT_DISCONNECT,
		AOT_SET_ALIAS,
		AOT_SET_USER_DISPLAY_ICON,
		AOT_SET_USER_STATUS,
		AOT_ALIAS_CONTACT, 
		AOT_SET_EXTENDED_CAPABILITIES
	};
	
public:
	
	CPurpleProtocolAsyncExec();
	virtual ~CPurpleProtocolAsyncExec();
	
	void StartAsyncOperations();
	void FinishAsyncOperations();
	BOOL IsFinishingAsyncOperations();
	
	IMProtocolError DisconnectAsync(CIMProtocol* pProtocol, 
			const std::string& strUser);
	
	IMProtocolError SetAliasAsync(CIMProtocol* pProtocol, 
			const std::string& strUser, const std::string& strAlias);
	
	IMProtocolError SetUserDisplayIconAsync(CIMProtocol* pProtocol, 
			const std::string& strUser, const std::string& strFile);
	
	IMProtocolError SetUserStatusAsync(CIMProtocol* pProtocol, 
			const std::string& strUser, int nStatus, const std::string& strStatusMessage);
	
	IMProtocolError AliasContactAsync(CIMProtocol* pProtocol, 
			const std::string& strUser, const std::string& strContact, const std::string& strAlias);
	
	IMProtocolError SetExtendedCapabilitiesAsync(CIMProtocol* pProtocol, 
			const std::string& strUser, CProtocolSettings2* pExtendedCapabilities);
	
protected:
	
	DUMMY_OPERATION* GetAsyncOperation();
	
private:
	
	BOOL		m_bInitialized;
	
	BOOL		m_bIsTerminating;
	
	CEvent		m_terminateEvent;
	GMutex*		m_pTerminatingMutex;
	GMutex*		m_pOperationListMutex;
	
	CAsyncOperationList		m_asyncExecList;
};


#endif // _PURPLE_PROTOCOL_ASYNC_EXEC_H

