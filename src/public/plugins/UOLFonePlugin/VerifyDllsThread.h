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

#include <util/MessageLoopThread.h>
#include "HttpDownloader.h"
#include "IVerifyDllsThreadCallback.h"
#include "./Core/UOLFoneFailureInfo.h"

//#include "../model/PluginInfo.h"


class CDownloadDllItem
{
public:
	CDownloadDllItem(const CString& strFromUrl, const CString& strLocalFilePath)
	{
		m_strFromUrl = strFromUrl;
		m_strLocalFilePath = strLocalFilePath;
	}

	CString m_strFromUrl;
	CString m_strLocalFilePath;
};

class CVerifyDllsThread : public CMessageLoopThread,
							 public CHttpDownloaderCallback,
							 public CHttpDownloaderStopFlag
{
public:
	CVerifyDllsThread();
	virtual ~CVerifyDllsThread();

	void SetCallback(IVerifyDllsThreadCallback* pCallback);

	DWORD GetInstallationError();

	void CancelVerification();
	void AddItem(const CString& strFromUrl, const CString& strLocalFilePath);
	
	CUOLFoneFailureInfoPtr GetLastFailureInfo();
	
protected:
	void Run();

	virtual void OnDownloadBegin();
	virtual void OnProgressChange(ULONG nProgress, ULONG nProgressMax);
	virtual void OnDownloadComplete(DWORD dwError);

	virtual BOOL GetStopFlag();

private:
	void RemoveOldDlls(const CString& strLatestDllLocalFilePath);
	int CompareVersions(const CString& strVersion1, const CString& strVersion2);

private:
	DWORD	m_dwErrorCode;
	LONG	m_nStopped;
	IVerifyDllsThreadCallback*	m_pCallback;
	CAtlList<CDownloadDllItem*> m_DownloadItems;
	DWORD	m_dwCurItem;
	
	CUOLFoneFailureInfoPtr		m_pLastFailureInfo;
};

MAKEAUTOPTR(CVerifyDllsThread);