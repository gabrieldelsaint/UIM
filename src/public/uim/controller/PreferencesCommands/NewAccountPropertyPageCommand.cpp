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
 
#include "StdAfx.h"
#include "NewAccountPropertyPageCommand.h"


CNewAccountPropertyPageCommand::CNewAccountPropertyPageCommand()
{
}


CNewAccountPropertyPageCommand::~CNewAccountPropertyPageCommand(void)
{
}


int CNewAccountPropertyPageCommand::GetPropPageCommandType()
{
	return IUOLMessengerPropertyPageCommandFactory::PP_COMMAND_TYPE_NEW_ACCOUNT;
}


BOOL CNewAccountPropertyPageCommand::GetAccountType(CString& accountType)
{
	accountType = m_accountType;
	
	return (!m_accountType.IsEmpty());
}


BOOL CNewAccountPropertyPageCommand::ProcessNewCommandValue(
		const int nCmdValueId, const CString strCmdValue)
{
	BOOL resultOk = TRUE;
	
	if (nCmdValueId == IUOLMessengerPropertyPageCommand::CVT_ACCOUNT_TYPE)
	{
		// An integer is expected for this command value type.
		// So, let us make the convertion before handle it.
		//
		int nCmdValue = atoi(strCmdValue);
		
		if (nCmdValue == IUOLMessengerPropertyPageCommand::ATV_PROTOCOL_UOL)
		{
			m_accountType = "prpl-uol";
		}
		else if (nCmdValue == IUOLMessengerPropertyPageCommand::ATV_PROTOCOL_MSN)
		{
			m_accountType = "prpl-msn";
		}
		else if (nCmdValue == IUOLMessengerPropertyPageCommand::ATV_PROTOCOL_ICQ)
		{
			m_accountType = "prpl-icq";
		}
		else if (nCmdValue == IUOLMessengerPropertyPageCommand::ATV_PROTOCOL_AIM)
		{
			m_accountType = "prpl-aim";
		}
		else if (nCmdValue == IUOLMessengerPropertyPageCommand::ATV_PROTOCOL_JABBER)
		{
			m_accountType = "prpl-jabber";
		}
		else if (nCmdValue == IUOLMessengerPropertyPageCommand::ATV_PROTOCOL_YAHOO)
		{
			m_accountType = "prpl-yahoo";
		}
		else
		{
			resultOk = FALSE;
		}
	}
	else if ( (nCmdValueId == IUOLMessengerPropertyPageCommand::CVT_ACCOUNT_USERNAME) || 
			(nCmdValueId == IUOLMessengerPropertyPageCommand::CVT_ACCOUNT_PASSWORD) || 
			(nCmdValueId == IUOLMessengerPropertyPageCommand::CVT_ACCOUNT_SAVE_PASSWORD_FLAG) )
	{
		// Do nothing.
		// The values map was updated, and the return will be TRUE.
	}
	else
	{
		resultOk = FALSE;
	}
	
	return resultOk;
}

