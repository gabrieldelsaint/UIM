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
 
#ifndef _PURPLE_OSCAR_PROTOCOL_H_
#define _PURPLE_OSCAR_PROTOCOL_H_

#include "purpleprotocol.h"


class CPurpleOscarProtocol : public CPurpleProtocol
{
public:
	CPurpleOscarProtocol(const std::string& strProtocolId, const std::string& strProtocolName);
	virtual ~CPurpleOscarProtocol();

	int GetPrivacyFlags();

	bool HasReRequestAuthorizationSupport();
	bool IsValidUserName(const std::string& strUser);

	IMProtocolError CanRequestContactAuthorization(const std::string& strUser, const std::string& strContact, bool& bCanRequest);
	IMProtocolError RequestContactAuthorization(const std::string& strUser, const std::string& strContact);

	int ProcessSystemMessage(PurpleAccount* pAccount, MessageParam* pParam);
	int ProcessErrorMessage(PurpleAccount* pAccount, MessageParam* pParam);

	int ProcessNotifyMessage(PurpleAccount* pAccount, NotifyMessageParam* pParam);
	int ProcessRequestInput(PurpleAccount* pAccount, RequestInputParam* pParam);
	int ProcessRequestAction(PurpleAccount* pAccount, RequestActionParam* pParam);

protected:
	virtual bool GetStatusText(int status, std::string& statusText);
	virtual bool GetStatusCode(const std::string& statusText, int& nStatus);

	virtual void ProcessExtraSettings(PurpleAccount* pAccount, CProtocolSettings* pExtraSettings);

	virtual std::string FormatSendingMessage(const std::string& strMessage);
	virtual std::string FormatSentMessage(const std::string& strMessage);
	//virtual std::string FormatReceivedMessage(const std::string& strMessage);

	virtual bool GetConnectionErrorCode(ConnectionError& errorCode, const char* pszReason);

private:
	std::string StripHTML(const std::string& strMessage);

private:
	struct OscarStatus
	{
		int status;
		char* statusText;
	};

	static OscarStatus ms_status[];

	struct ConnectionErrorEntry
	{
		ConnectionError errorCode;
		char* pszText;
	};

	static ConnectionErrorEntry ms_pConnectionErrorEntries[];
};

#endif