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

#include <commands/SendDroppedFileCommand.h>

#include "../../resource.h"
#include "../UIMApplication.h"
#include <sys/stat.h>
#include "../../view/UIMFileDialog.h"


CSendDroppedFileCommand::CSendDroppedFileCommand(IUOLMessengerContactPtr pContact, HWND wnd, CString strFileName) : 
	m_pContact(pContact),
	m_wnd(wnd),
	m_strFileName(strFileName)
{
}


CSendDroppedFileCommand::~CSendDroppedFileCommand()
{
}


void CSendDroppedFileCommand::Execute()
{
	CString strMessage;

	if (m_pContact)
	{
		// Check if protocol support file transfer
		CIMProtocol* pProtocol = m_pContact->GetAccount()->GetProtocol();

		ATLASSERT(pProtocol);

		UOLLib::ISettings* pStringLoader =  static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->GetStringLoader();
		ATLASSERT(pStringLoader);

		if ((!pProtocol) ||
			(!pProtocol->HasFileTransferSupport()))
		{
			CString strFormat;
			strFormat = pStringLoader->GetValue("uol.resource.error.IDS_FILE_TRANSFER_NOT_SUPPORTED");
			strMessage.Format(strFormat, m_pContact->GetAccount()->GetProtocolName());

			CUIMApplication::GetApplication()->GetUIManager()->ShowMessageBox(m_wnd, strMessage, MB_OK | MB_ICONSTOP);

			return;
		}

		// Check if account is online
		if (FALSE == CUIMApplication::GetApplication()->GetAccountConnectionManager()->IsConnected(m_pContact->GetAccount()))
		{
			strMessage = pStringLoader->GetValue("uol.resource.error.IDS_FILE_TRANSFER_ACCOUNT_NOT_CONNECTED");

			CUIMApplication::GetApplication()->GetUIManager()->ShowMessageBox(m_wnd, strMessage, MB_OK | MB_ICONSTOP);
			
			return;
		}

		// Check if contact is online
		if (m_pContact->GetStatus() == IUOLMessengerContact::CS_OFFLINE)
		{
			strMessage = pStringLoader->GetValue("uol.resource.error.IDS_FILE_TRANSFER_CONTACT_NOT_ONLINE_MESSAGE");

			CUIMApplication::GetApplication()->GetUIManager()->ShowMessageBox(m_wnd, strMessage, MB_OK | MB_ICONERROR);

			return;
		}

		// Request file to send
		if (!m_strFileName.IsEmpty())
		{
			struct __stat64 stFileInfo = {0};

			int nStat = ::_tstat64(m_strFileName, &stFileInfo);

			ATLASSERT(0 == nStat);
			if (0 == nStat)
			{
				if (stFileInfo.st_size > 0)
				{
					CString strLastFolder = m_strFileName;
					strLastFolder.Left(strLastFolder.ReverseFind('\\'));

					CUIMApplication::GetApplication()->GetSettingsManager()->GetGeneralSettings()->SetLastSendFileFolder(strLastFolder);
					CUIMApplication::GetApplication()->GetFileTransferManager()->SendFile(m_pContact->GetAccount(), m_pContact->GetName(), m_strFileName);
				}
				else
				{
					static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
							GetLogger()->LogWarning(__FUNCTION__, 
							"O arquivo [%s] � inv�lido. A transfer�ncia de arquivos com 0KB n�o � aceita.", 
							m_strFileName);
					
					strMessage = pStringLoader->GetValue("uol.resource.error.IDS_FILE_TRANSFER_ZERO_SIZE_FILE_MESSAGE");
					CUIMApplication::GetApplication()->GetUIManager()->ShowMessageBox(m_wnd, strMessage, MB_OK | MB_ICONERROR);
				}
			}
		}
	}
}