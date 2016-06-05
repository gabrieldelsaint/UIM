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
 
#include "error.h"
#include "stdafx.h"


CRadioUOLError::CRadioUOLError(int nError)
{
	CString strMessage="";

	switch (nError)
	{
	case INTERNET_OFF:
		strMessage.LoadString(IDS_ERRORMSG_001);
		break;

	case CONFIG_FILE:
		strMessage.LoadString(IDS_ERRORMSG_002);
		break;

	case HTTP_READ:
		strMessage.LoadString(IDS_ERRORMSG_003);
		break;

	case UPDATERADIOUOLXML:
		strMessage.LoadString(IDS_ERRORMSG_004);
		break;

	case SAVECONFIG:
		strMessage.LoadString(IDS_ERRORMSG_005);
		break;

	case CONFIG_INTERNET_OFF:
		strMessage.LoadString(IDS_ERRORMSG_006);
		break;

	case STREAMING_ERRO:
		strMessage.LoadString(IDS_ERRORMSG_007);
		break;

	case INCOMPATIBLE_WMP_VWESION:
		strMessage.LoadString(IDS_ERRORMSG_008);
		break;

	case UNDEFINED:
		break;

	default:
		break;
	}
	
	if (strMessage.IsEmpty()==FALSE)
	{
		IUOLMessengerUIManagerPtr pUIManager = CFacadeWrapper::GetFacadeInstance()->GetUIManager();
		if (pUIManager!=NULL) {
			CWindow wnd(pUIManager->GetAppWindow());
			if (wnd.IsWindow())
			{
				ap_static_cast<IUOLMessengerUIManager4Ptr>(CFacadeWrapper::GetFacadeInstance()->GetUIManager())->ShowMessageBox(wnd.m_hWnd, strMessage, "R�dio UOL", MB_OK | MB_ICONERROR);
			}
			else 
			{
				ap_static_cast<IUOLMessengerUIManager4Ptr>(CFacadeWrapper::GetFacadeInstance()->GetUIManager())->ShowMessageBox(NULL, strMessage, "R�dio UOL", MB_OK | MB_ICONERROR);
			}
		}
	}
}