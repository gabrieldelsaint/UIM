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
 
#include "purplefiletransferinfo.h"

#include "purpleutils.h"

using namespace std;


CPurpleFileTransferInfo::CPurpleFileTransferInfo(PurpleXfer* pXfer) :
	m_pXfer(pXfer)
{
	purple_xfer_ref(pXfer);	
}


CPurpleFileTransferInfo::~CPurpleFileTransferInfo()
{
	if (m_pXfer)
	{
		purple_xfer_unref(m_pXfer);
	}
}


CFileTransferInfo* CPurpleFileTransferInfo::Clone() const
{
	purple_xfer_ref(m_pXfer);

	return new CPurpleFileTransferInfo(m_pXfer);
}


long CPurpleFileTransferInfo::GetId() const
{
	return (long) m_pXfer->ui_data;
}


bool CPurpleFileTransferInfo::IsSending() const
{
	return (m_pXfer->type == PURPLE_XFER_SEND);
}


std::string CPurpleFileTransferInfo::GetFileName() const
{
	if (m_pXfer->filename != NULL)
	{
		string strFileName("");
		
		GetLocaleTextFromUTF8(m_pXfer->filename, strFileName);

		return strFileName;
	}

	return "";
}


std::string CPurpleFileTransferInfo::GetFileLocalPath() const
{
	if (m_pXfer->local_filename != NULL)
	{
		string strLocalFileName("");
		
		GetLocaleTextFromUTF8(m_pXfer->local_filename, strLocalFileName);

		return strLocalFileName;
	}

	return "";
}


unsigned long CPurpleFileTransferInfo::GetTotalBytes() const
{
	return m_pXfer->size;
}


unsigned long CPurpleFileTransferInfo::GetTransferedBytes() const
{
	return m_pXfer->bytes_sent;
}


FileTransferStatus CPurpleFileTransferInfo::GetTransferStatus() const
{
	FileTransferStatus status;

	if (m_pXfer->status == PURPLE_XFER_STATUS_ACCEPTED)
	{
		status = FILE_TRANSFER_STATUS_ACCEPTED;
	}
	else if (m_pXfer->status == PURPLE_XFER_STATUS_STARTED)
	{
		status = FILE_TRANSFER_STATUS_STARTED;
	}
	else if (m_pXfer->status == PURPLE_XFER_STATUS_DONE)
	{
		status = FILE_TRANSFER_STATUS_DONE;
	}
	else if (m_pXfer->status == PURPLE_XFER_STATUS_CANCEL_LOCAL)
	{
		status = FILE_TRANSFER_STATUS_CANCEL_LOCAL;
	}
	else if (m_pXfer->status == PURPLE_XFER_STATUS_CANCEL_REMOTE)
	{
		status = FILE_TRANSFER_STATUS_CANCEL_REMOTE;
	}
	else
	{
		// PURPLE_XFER_STATUS_UNKNOWN
		// PURPLE_XFER_STATUS_NOT_STARTED
		status = FILE_TRANSFER_STATUS_NOT_STARTED;
	}

	return status;
}