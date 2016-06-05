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


#include <interfaces/IUOLMessengerMessageTemplateRecord.h>
#include <interfaces/IUOLMessengerHistoryRecord.h>
#include "../view/ConversationWindow.h"


#define		CUSTOM_EMOTICON_IMAGE_TAG_CLASS_NAME						"CustomEmoticonClass"


class CMessageTemplateRecord : public IUOLMessengerMessageTemplateRecord
{
public:
	
	CMessageTemplateRecord(IUOLMessengerConversation2Ptr pConversation2, 
			IUOLMessengerConversation::MessageEntryPtr pMessageEntry);
	
	CMessageTemplateRecord(IUOLMessengerConversation2Ptr pConversation2, 
			IUOLMessengerConversation::MessageEntryPtr pMessageEntry, 
			CRequestFileTransferAsyncInfo* pFileTransferAsyncInfo);

	CMessageTemplateRecord(IUOLMessengerConversation2Ptr pConversation2,
			IUOLMessengerHistoryEventPtr pHistoryEvent);
	
	virtual ~CMessageTemplateRecord();
	
	IUOLMessengerConversation::MessageEntryPtr GetMessageEntry();
	
	CRequestFileTransferAsyncInfo* GetRequestFileTransferAsyncInfo();
	
protected:
	
	// IUOLMessengerMessageTemplateRecord interface.
	//
	virtual int GetRecordType() const;
	virtual IUOLMessengerConversationPtr GetConversation() const;
	virtual CString GetAuthor() const;
	virtual CString GetAuthorId() const;
	virtual CString GetAuthorIconPath() const;
	virtual CString GetAccountUserId() const;
	virtual CString GetAccountNickName() const;
	virtual CString GetAccountIconPath() const;
	virtual CString GetContactName() const;
	virtual CString GetContactAlias() const;
	virtual CString GetContactIconPath() const;
	virtual CString GetService() const;
	virtual CString GetMessage() const;
	virtual CString GetMessageParsed();
	virtual CTime GetTime() const;
	virtual int GetFileTransferId();
	virtual CString GetFileTransferName();
	
	HRESULT ProcessCustomEmoticons(CString& strMessage, CString strSmileys);
	
	HRESULT BuildCustomEmoticonImageTag(
			IUOLMessengerCustomEmoticonManagerPtr pCustomEmoticonManager, 
			CString& customEmoticonImageTag, CString customEmoticon);
	
	IUOLMessengerCustomEmoticonManagerPtr GetCustomEmoticonManager();
	
	BOOL SplitMessage(CString strOriginalMessage, CString& strInitialTags, 
			CString& strMessageText, CString& strFinalTags);

	CString FindAlias(const CString& strName) const;
	
//protected:
	//friend class CFileTransferManager;
	
private:
	
	IUOLMessengerConversation2Ptr					m_pConversation2;
	
	IUOLMessengerConversation::MessageEntryPtr		m_pMessageEntry;
	
	CRequestFileTransferAsyncInfo*					m_pFileTransferAsyncInfo;

	IUOLMessengerHistoryEventPtr					m_pHistoryEvent;
};

MAKEAUTOPTR(CMessageTemplateRecord);

