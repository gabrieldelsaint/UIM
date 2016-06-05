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
 
#pragma once

#include "IUOLMessengerAccount.h"


class __declspec(novtable) CFileTransferProgressObserver;


class __declspec(novtable) IUOLMessengerFileTransfer
{
public:
	enum FileTransferOperation
	{
		FTO_SEND = 0,
		FTO_RECEIVE
	};

public:
	virtual ~IUOLMessengerFileTransfer() {}

	virtual IUOLMessengerAccountPtr GetAccount() = 0;
	virtual CString GetContactName() = 0;
	virtual long GetId() = 0;

	virtual DWORD GetTransferOperation() = 0;
	virtual CString GetFileName() = 0;
	virtual CString GetLocalFilePath() = 0;
	virtual ULONG GetTotalBytes() = 0;
	virtual ULONG GetTransferedBytes() = 0;
	virtual FileTransferStatus GetStatus() = 0;

	virtual void RegisterProgressObserver(CFileTransferProgressObserver* pObserver) = 0;
	virtual void UnregisterProgressObserver(CFileTransferProgressObserver* pObserver) = 0;
	virtual void NotifyAll() = 0;
};
MAKEAUTOPTR(IUOLMessengerFileTransfer);


class __declspec(novtable) IUOLMessengerFileTransfer2: public IUOLMessengerFileTransfer
{
public:
	virtual ~IUOLMessengerFileTransfer2() {}

	virtual CTime GetTime() const = 0;
};
MAKEAUTOPTR(IUOLMessengerFileTransfer2);


class __declspec(novtable) CFileTransferProgressObserver
{
public:
	virtual ~CFileTransferProgressObserver() {}

	virtual void UpdateProgress(IUOLMessengerFileTransfer* pFileTransfer) = 0;
};