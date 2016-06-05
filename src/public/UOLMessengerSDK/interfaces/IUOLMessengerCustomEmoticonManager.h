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

#include "IUOLMessengerConversation.h"
#include "IUOLMessengerCustomEmoticon.h"


class CUOLMessengerCustomEmoticonManagerObserver;


class __declspec(novtable) IUOLMessengerCustomEmoticonManager
{
public:
	
	virtual ~IUOLMessengerCustomEmoticonManager() {}
	
	virtual BOOL SetCustomEmoticonStoreRootPath(const CString& strStoreRootPath) = 0;
	virtual BOOL SetDownloadingEmoticonFile(const CString& strDownloadingEmoticonFile) = 0;
	virtual BOOL SetDownloadingEmoticonSize(const CSize& emoticonSize) = 0;
	virtual CString GetDownloadingEmoticonFile() = 0;
	virtual CSize GetDownloadingEmoticonSize() = 0;
	
	virtual IUOLMessengerCustomEmoticonPtr FindCustomEmoticon(IUOLMessengerConversationPtr pConversation, const CString& strEmoticon) = 0;
	virtual IUOLMessengerCustomEmoticonPtr FindCustomEmoticon(IUOLMessengerCustomEmoticonPtr pCustomEmoticon) = 0;
	
	virtual void GetCustomEmoticonList(IUOLMessengerConversationPtr pConversation, CAtlList<IUOLMessengerCustomEmoticonPtr>& customEmoticonList);
	
	virtual void RegisterObserver(CUOLMessengerCustomEmoticonManagerObserver* pObserver) = 0;
	virtual void UnregisterObserver(CUOLMessengerCustomEmoticonManagerObserver* pObserver) = 0;
};

MAKEAUTOPTR(IUOLMessengerCustomEmoticonManager);



class CUOLMessengerCustomEmoticonManagerObserver
{
public:
	virtual ~CUOLMessengerCustomEmoticonManagerObserver() {}
	
	virtual void OnCustomEmoticonStored(IUOLMessengerCustomEmoticonPtr pCustomEmoticon) { }
};

