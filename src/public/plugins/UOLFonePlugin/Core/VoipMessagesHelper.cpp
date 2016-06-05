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
 

#include "stdafx.h"
#include "VoipMessagesHelper.h"


CVoipMessagesHelper::CVoipMessagesHelper()
{
	// Initialize Pure Warning ID's list.
	//
	m_pureWarningIDs.AddTail("PUF0101");
	m_pureWarningIDs.AddTail("PUF0102");
	m_pureWarningIDs.AddTail("PUF0122");
	m_pureWarningIDs.AddTail("PUF0146");
	
	// Initialize Call Warning ID's list.
	//
	m_callWarningIDs.AddTail("PUF0110");
	m_callWarningIDs.AddTail("PUF0112");
	m_callWarningIDs.AddTail("PUF0119");
	m_callWarningIDs.AddTail("PUF0120");
	m_callWarningIDs.AddTail("PUF0404");
	
	// Initialize Pure Error ID's list.
	//
	m_pureErrorIDs.AddTail("PUF0105");
	m_pureErrorIDs.AddTail("PUF0106");
	m_pureErrorIDs.AddTail("PUF0107");
	m_pureErrorIDs.AddTail("PUF0108");
	m_pureErrorIDs.AddTail("PUF0109");
	m_pureErrorIDs.AddTail("PUF0113");
	m_pureErrorIDs.AddTail("PUF0114");
	m_pureErrorIDs.AddTail("PUF0115");
	m_pureErrorIDs.AddTail("PUF0116");
	m_pureErrorIDs.AddTail("PUF0117");
	m_pureErrorIDs.AddTail("PUF0118");
	m_pureErrorIDs.AddTail("PUF0142");
	m_pureErrorIDs.AddTail("PUF0145");
	m_pureErrorIDs.AddTail("PUF0147");
	m_pureErrorIDs.AddTail("PUF0148");
	m_pureErrorIDs.AddTail("PUF0149");
	m_pureErrorIDs.AddTail("PUF0150");
	m_pureErrorIDs.AddTail("PUF0151");
	
	// Initialize Call Error ID's list.
	//
	m_callErrorIDs.AddTail("PUF0103");
	m_callErrorIDs.AddTail("PUF0104");
	m_callErrorIDs.AddTail("PUF0111");
	m_callErrorIDs.AddTail("PUF0121");
}


CVoipMessagesHelper::~CVoipMessagesHelper()
{
	m_pureWarningIDs.RemoveAll();
	m_callWarningIDs.RemoveAll();
	m_callErrorIDs.RemoveAll();
}


BOOL CVoipMessagesHelper::IsPureWarningMessage(CString strMessage)
{
	CString strMessageId = ExtractMessageId(strMessage);
	
	if ( (!strMessageId.IsEmpty()) && 
			(m_pureWarningIDs.Find(strMessageId) != NULL) )
	{
		return TRUE;
	}
	
	return FALSE;
}


BOOL CVoipMessagesHelper::IsCallWarningMessage(CString strMessage)
{
	CString strMessageId = ExtractMessageId(strMessage);
	
	if ( (!strMessageId.IsEmpty()) && 
			(m_callWarningIDs.Find(strMessageId) != NULL) )
	{
		return TRUE;
	}
	
	return FALSE;
}


BOOL CVoipMessagesHelper::IsPureErrorMessage(CString strMessage)
{
	CString strMessageId = ExtractMessageId(strMessage);
	
	if ( (!strMessageId.IsEmpty()) && 
			(m_pureErrorIDs.Find(strMessageId) != NULL) )
	{
		return TRUE;
	}
	
	return FALSE;
}


BOOL CVoipMessagesHelper::IsCallErrorMessage(CString strMessage)
{
	CString strMessageId = ExtractMessageId(strMessage);
	
	if ( (!strMessageId.IsEmpty()) && 
			(m_callErrorIDs.Find(strMessageId) != NULL) )
	{
		return TRUE;
	}
	
	return FALSE;
}


CString CVoipMessagesHelper::ExtractMessageId(CString strMessage)
{
	int strIndex = -1;
	CString strMessageId;
	
	if ((strIndex = strMessage.Find("PUF")) != -1)
	{
		strMessageId = strMessage.Mid(strIndex, 7);
	}
	
	return strMessageId;
}

