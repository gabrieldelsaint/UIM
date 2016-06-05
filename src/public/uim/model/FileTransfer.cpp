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
#include "FileTransfer.h"


CFileTransfer::CFileTransfer(IUOLMessengerAccountPtr pAccount, const CString& strContactName, long lFileTransferId, CTime time) : 
	m_pAccount(pAccount),
	m_strContactName(strContactName),
	m_lId(lFileTransferId),
	m_Time(time),
	m_lTotalBytes(0),
	m_lTransferedBytes(0),
	m_dwOperation(0),
	m_transferStatus(FILE_TRANSFER_STATUS_NOT_STARTED)
{
}


CFileTransfer::~CFileTransfer()
{
}


IUOLMessengerAccountPtr CFileTransfer::GetAccount()
{
	return m_pAccount;
}


CString CFileTransfer::GetContactName()
{
	return m_strContactName;
}


long CFileTransfer::GetId()
{
	return m_lId;
}


CTime CFileTransfer::GetTime() const
{
	return m_Time;
}


DWORD CFileTransfer::GetTransferOperation()
{
	return m_dwOperation;
}


CString CFileTransfer::GetFileName()
{
	return m_strFileName;
}


CString CFileTransfer::GetLocalFilePath()
{
	return m_strLocalFilePath;
}


ULONG CFileTransfer::GetTotalBytes()
{
	return m_lTotalBytes;
}


ULONG CFileTransfer::GetTransferedBytes()
{
	return m_lTransferedBytes;
}


FileTransferStatus CFileTransfer::GetStatus()
{
	return m_transferStatus;
}


void CFileTransfer::RegisterProgressObserver(CFileTransferProgressObserver* pObserver)
{
	if (pObserver != NULL)
	{
		POSITION posFind = m_listObservers.Find(pObserver);

		if (!posFind)
		{
			m_listObservers.AddTail(pObserver);
		}
	}
}


void CFileTransfer::UnregisterProgressObserver(CFileTransferProgressObserver* pObserver)
{
	if (pObserver != NULL)
	{
		POSITION posFind = m_listObservers.Find(pObserver);

		if (posFind != NULL)
		{
			m_listObservers.RemoveAt(posFind);
		}
	}
}


void CFileTransfer::NotifyAll()
{
	CFileTransferProgressObserver* pObserver;

	for (POSITION pos = m_listObservers.GetHeadPosition(); pos; )
	{
		pObserver = m_listObservers.GetNext(pos);

		pObserver->UpdateProgress(this);
	}
}


void CFileTransfer::SetTransferOperation(DWORD dwOperation)
{
	m_dwOperation = dwOperation;
}


void CFileTransfer::SetFileName(const CString& strFileName)
{
	m_strFileName = strFileName;
}


void CFileTransfer::SetLocalFilePath(const CString& strFilePath)
{
	m_strLocalFilePath = strFilePath;
}


void CFileTransfer::SetTotalBytes(ULONG lBytes)
{
	m_lTotalBytes = lBytes;
}


void CFileTransfer::SetTransferedBytes(ULONG lBytes)
{
	m_lTransferedBytes = lBytes;
}


void CFileTransfer::SetStatus(FileTransferStatus transferStatus)
{
	m_transferStatus = transferStatus;
}