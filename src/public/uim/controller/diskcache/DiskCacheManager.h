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

#include "IDiskCacheManager.h"
#include "DiskCacheEntry.h"
#include "DownloadScheduler.h"
#include "../../ObserverRegister.h"


class CDiskCacheManager : 
	public IDiskCacheManager,
	public CDownloadSchedulerObserver
{
public:
	CDiskCacheManager();
	virtual ~CDiskCacheManager();

	virtual BOOL Init();
	virtual void Finalize();

protected:
	virtual IDiskCacheEntryPtr FetchUrl(const CString& strUrl, DWORD& dwError);
	virtual DWORD FetchUrl(const CString& strUrl, IDiskCacheEntryObserver* pObserver);
	
	virtual IDiskCacheEntryPtr GetCacheEntry(const CString& strUrl);
	
	virtual void Clear();

	virtual void OnDownloadComplete(IDownloadInfo* pDownloadInfo);

private:
	void LoadCacheEntries();
	CDiskCacheEntryPtr LoadCacheEntry(MSXML::IXMLDOMNodePtr pNode);
	void SaveCacheEntries();
	void SaveCacheEntry(MSXML::IXMLDOMDocumentPtr pDoc, MSXML::IXMLDOMNodePtr pNode, CDiskCacheEntryPtr pDiskCacheEntry);

	CDiskCacheEntryPtr AddCacheEntry(const CString& strUrl, const CString& strLocalPath);

	CString GetCacheDir();
	CString GetLocalPath();

	void ClearOrphanFiles();

	DWORD GetErrorCode(DWORD dwDownloadError);

private:
	CString		m_strCacheDir;
	CDownloadScheduler	m_downloadScheduler;

	typedef CAtlMap<CString, CDiskCacheEntryPtr> CDiskCacheEntryMap;
	CDiskCacheEntryMap	m_mapEntries;

	CComAutoCriticalSection		m_csEntries;

	typedef CAtlMap<CString, IDiskCacheEntryObserver*> CDiskCacheEntryObserverMap;
	CDiskCacheEntryObserverMap	m_mapEntryObservers;
};