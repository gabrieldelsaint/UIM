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
 
#ifndef _PURPLE_JABBER_PROTOCOL_H_
#define _PURPLE_JABBER_PROTOCOL_H_

#include "purpleprotocol.h"


class CPurpleJabberProtocol : public CPurpleProtocol
{
public:
	CPurpleJabberProtocol();
	CPurpleJabberProtocol(const std::string& strProtocolId, const std::string& strProtocolName);
	virtual ~CPurpleJabberProtocol();

	virtual bool HasContactBlockingSupport();
	virtual bool HasReRequestAuthorizationSupport();

	virtual bool AutoAddContactOnAuthorization();
	virtual std::string GetDefaultContactGroup();

	virtual bool IsValidUserName(const std::string& strUser);

	virtual IMProtocolError CanRequestContactAuthorization(const std::string& strUser, const std::string& strContact, bool& bCanRequest);
	virtual IMProtocolError RequestContactAuthorization(const std::string& strUser, const std::string& strContact);

	virtual void OnContactSignedOn(PurpleAccount* pAccount, PurpleBuddy* pBuddy);
	
	virtual int ProcessRequestAction(PurpleAccount* pAccount, RequestActionParam* pParam);

protected:
	virtual bool GetStatusText(int nStatus, std::string& statusText);
	virtual bool GetStatusCode(const std::string& statusText, int& nStatus);

	virtual void ProcessExtraSettings(PurpleAccount* pAccount, CProtocolSettings* pExtraSettings);
	virtual int ProcessNotifyFormatted(PurpleAccount* pAccount, NotifyFormattedParam* pParam);
	virtual int ProcessNotifyMessage(PurpleAccount* pAccount, NotifyMessageParam* pParam);

	virtual std::string GetNormalizedPurpleUserName(const std::string& strUserName);
	virtual std::string GetNormalizedCallbackUserName(const char* pszPurpleUserName);
	virtual std::string GetNormalizedContactName(const char* pszContact);

	virtual bool GetConnectionErrorCode(ConnectionError& errorCode, const char* pszReason);

public:
	static const char* PURPLE_JABBER_PLUGIN_ID;
	static const char* PURPLE_JABBER_PROTOCOL_NAME;

private:
	struct JabberStatus
	{
		int status;
		char* statusText;
	};

	static JabberStatus ms_status[];

	struct ConnectionErrorEntry
	{
		ConnectionError errorCode;
		char* pszText;
	};

	static ConnectionErrorEntry ms_pConnectionErrorEntries[];

	static const char* PURPLE_JABBER_DEFAULT_RESOURCE;
	static char PURPLE_JABBER_RESOURCE_SPLITTER;
};

#endif