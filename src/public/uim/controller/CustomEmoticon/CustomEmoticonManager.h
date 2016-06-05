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


#include <interfaces/IUOLMessengerCustomEmoticonManager.h>
#include "CustomEmoticon.h"
#include "../../ObserverRegister.h"
#include "../../view/Preferences/PictureExWnd.h"
#include "../../Cryptography.h"


class CCustomEmoticonObserverNotifier : public CObserverRegister<CUOLMessengerCustomEmoticonManagerObserver>
{
public:
	void NotifyAll(void (CUOLMessengerCustomEmoticonManagerObserver::*pfnUpdate)(IUOLMessengerCustomEmoticonPtr), IUOLMessengerCustomEmoticonPtr pCustomEmoticon);
};



class CCustomEmoticonManager : public IUOLMessengerCustomEmoticonManager
{
public:
	
	CCustomEmoticonManager();
	virtual ~CCustomEmoticonManager();
	
	virtual BOOL SetCustomEmoticonStoreRootPath(const CString& strStoreRootPath);
	virtual BOOL SetDownloadingEmoticonFile(const CString& strDownloadingEmoticonFile);
	virtual BOOL SetDownloadingEmoticonSize(const CSize& emoticonSize);
	virtual CString GetDownloadingEmoticonFile();
	virtual CSize GetDownloadingEmoticonSize();
	
	virtual CCustomEmoticonPtr CreateCustomEmoticon(IUOLMessengerConversationPtr pConversation, 
			const CString& strEmoticon);
	virtual BOOL UpdateCustomEmoticonData(CCustomEmoticonPtr pCustomEmoticon, const unsigned char* pEmoticonData, 
			unsigned int nEmoticonDataSize, const CString& strFileExtension);
	virtual BOOL UpdateCustomEmoticonData(IUOLMessengerConversationPtr pConversation, const CString& strEmoticon, 
			const unsigned char* pEmoticonData, unsigned int nEmoticonDataSize, const CString& strFileExtension);
	virtual BOOL StoreCustomEmoticon(CCustomEmoticonPtr pCustomEmoticon);
	virtual BOOL StoreCustomEmoticon(IUOLMessengerConversationPtr pConversation, const CString& strEmoticon);
	virtual BOOL DestroyCustomEmoticon(CCustomEmoticonPtr pCustomEmoticon);
	
	virtual IUOLMessengerCustomEmoticonPtr FindCustomEmoticon(IUOLMessengerConversationPtr pConversation, const CString& strEmoticon);
	virtual IUOLMessengerCustomEmoticonPtr FindCustomEmoticon(IUOLMessengerCustomEmoticonPtr pCustomEmoticon);
	
	virtual void GetCustomEmoticonList(IUOLMessengerConversationPtr pConversation, CAtlList<IUOLMessengerCustomEmoticonPtr>& customEmoticonList);
	
	static BOOL CalculateImagePresentationSize(LONG& lImageHeight, LONG& lImageWidth);
	static BOOL CalculateImagePresentationSize(LONG& lImageHeight, LONG& lImageWidth, LONG lHeightLimit, LONG lWidthLimit);
	
	static void EncodeShortcutToFileName(CString& strFileName);
	static void DecodeFileNameToShortcut(CString& strShortcut);
	
	virtual void RegisterObserver(CUOLMessengerCustomEmoticonManagerObserver* pObserver);
	virtual void UnregisterObserver(CUOLMessengerCustomEmoticonManagerObserver* pObserver);
	
protected:
	
	//IUOLMessengerCustomEmoticonPtr GetCustomEmoticon(IUOLMessengerConversationPtr pConversation, const CString& strEmoticon);
	IUOLMessengerCustomEmoticonPtr InternalFindCustomEmoticon(IUOLMessengerAccountPtr pAccount, IUOLMessengerContactPtr pContact, const CString& strEmoticon);
	
private:
	
	CCustomEmoticonObserverNotifier		m_observerNotifier;
	
	typedef CAtlMap<CString, CCustomEmoticonPtr> CCustomEmoticonIdMap;
	
	CCustomEmoticonIdMap		m_customEmoticonIdMap;
	
	CString						m_strStoreRootPath;
	CString						m_strDownloadingEmoticonFile;
	CSize						m_szDownloadingEmoticon;
	
	CStatic						m_customEmoticonSizeCalculatorWindow;
	CPictureExWnd				m_customEmoticonSizeCalculator;
};

MAKEAUTOPTR(CCustomEmoticonManager);

