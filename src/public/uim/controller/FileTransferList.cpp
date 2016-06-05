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
#include "FileTransferList.h"


CFileTransferList::CFileTransferList()
{
}


CFileTransferList::~CFileTransferList()
{
	m_listEntries.RemoveAll();
}


void CFileTransferList::RegisterObserver(CFileTransferListObserver* pObserver)
{
	POSITION posFind = m_listObservers.Find(pObserver);

	if (!posFind)
	{
		m_listObservers.AddTail(pObserver);
	}
}


void CFileTransferList::UnregisterObserver(CFileTransferListObserver* pObserver)
{
	POSITION posFind = m_listObservers.Find(pObserver);

	if (posFind != NULL)
	{
		m_listObservers.RemoveAt(posFind);
	}
}


BOOL CFileTransferList::AddFileTransfer(IUOLMessengerFileTransferNodePtr pFileTransferNode)
{
	if (pFileTransferNode != NULL)
	{
		IUOLMessengerFileTransferNodePtr pFindFileTransfer = FindFileTransferImpl(pFileTransferNode->GetFileTransferInternalName());

		if (!pFindFileTransfer)
		{
			m_listEntries.AddTail(pFileTransferNode);

			NotifyObservers(&CFileTransferListObserver::OnAddFileTransfer, pFileTransferNode);

			return TRUE;
		}
	}

	return FALSE;
}


BOOL CFileTransferList::RemoveFileTransfer(IUOLMessengerFileTransferNodePtr pFileTransferNode)
{
	POSITION pos = m_listEntries.Find(pFileTransferNode);

	if (pos)
	{
		m_listEntries.RemoveAt(pos);

		NotifyObservers(&CFileTransferListObserver::OnRemoveFileTransfer, pFileTransferNode);

		return TRUE;
	}

	return FALSE;
}


IUOLMessengerFileTransferNodePtr CFileTransferList::FindFileTransfer(const CString& strFileName)
{
	return FindFileTransferImpl(strFileName);
}


void CFileTransferList::GetEntries(CAtlList<IUOLMessengerFileTransferNodePtr>& listEntries)
{
	listEntries.RemoveAll();

	for (POSITION pos = m_listEntries.GetHeadPosition(); pos; )
	{
		IUOLMessengerFileTransferNodePtr pFileTransfer = m_listEntries.GetNext(pos);
		listEntries.AddTail(pFileTransfer);
	}
}


IUOLMessengerFileTransferNodePtr CFileTransferList::FindFileTransferImpl(const CString& strFileName)
{
	IUOLMessengerFileTransferNodePtr pFindFileTransfer;

	for (POSITION pos = m_listEntries.GetHeadPosition(); pos; )
	{
		IUOLMessengerFileTransferNodePtr pFileTransfer = m_listEntries.GetNext(pos);

		if (MatchFileTransfer(strFileName, pFileTransfer))
		{
			pFindFileTransfer = pFileTransfer;
			break;
		}
	}

	return pFindFileTransfer;
}


BOOL CFileTransferList::MatchFileTransfer(const CString& strFileName, IUOLMessengerFileTransferNodePtr pFileTransfer)
{
	return (0 == strFileName.Compare(pFileTransfer->GetFileTransferInternalName()));
}


void CFileTransferList::NotifyObservers(void (CFileTransferListObserver::*pfnHandler)(IUOLMessengerFileTransferNodePtr), IUOLMessengerFileTransferNodePtr pFileTransfer)
{
	CFileTransferListObserver* pObserver;

	for (POSITION pos = m_listObservers.GetHeadPosition(); pos; )
	{
		pObserver = m_listObservers.GetNext(pos);

		if (FALSE == ::IsBadReadPtr(pObserver, sizeof(CFileTransferListObserver*)))
		{
			(pObserver->*pfnHandler)(pFileTransfer);
		}
	}
}