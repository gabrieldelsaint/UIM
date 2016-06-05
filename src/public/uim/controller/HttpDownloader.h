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


class CHttpDownloaderCallback
{
public:
	virtual ~CHttpDownloaderCallback() {}

	// Events
	virtual void OnDownloadBegin() {}
	virtual void OnProgressChange(ULONG nProgress, ULONG nProgressMax) {}
	virtual void OnDownloadComplete(DWORD dwError) {}
};



class CHttpDownloaderStopFlag
{
public:
	virtual ~CHttpDownloaderStopFlag() {}

	virtual BOOL GetStopFlag() = 0;
};



class CHttpDownloader
{
public:
	/* Errors below "DE_CRACK_URL_ERROR" implies in "GetAdditionalErrorCode()" 
	 * being used to gatter additional information that is stored on 
	 * "m_dwAdditionalError" member.
	 * 
	 * Error "DE_HTTP_STATUS_CODE_ERROR" results on storing of HTTP error status 
	 * received on m_dwHTTPStatusCode member.
	 */
	enum DownloadError
	{
		DE_ERROR_SUCCESS = 0,
		DE_ERROR_FAILED,
		DE_INVALID_PARAM,
		DE_HTTP_STATUS_CODE_ERROR,
		DE_STOPPED,
		DE_CRACK_URL_ERROR,
		DE_INTERNET_OPEN_ERROR,
		DE_INTERNET_SET_OPTION_ERROR,
		DE_INTERNET_CONNECT_ERROR,
		DE_HTTP_OPEN_REQUEST_ERROR,
		DE_HTTP_SEND_REQUEST_ERROR,
		DE_HTTP_QUERY_STATUS_ERROR,
		DE_HTTP_QUERY_CONTENT_LENGTH_ERROR,
		DE_FILE_CREATION_ERROR,
		DE_INTERNET_QUERY_DATA_AVAILABLE_ERROR,
		DE_INTERNET_READ_ERROR,
		DE_FILE_WRITING_ERROR
	};

public:
	CHttpDownloader();

	void SetUrl(const CString& strUrl);
	void SetLocalFilePath(const CString& strLocalFilePath);
	void SetCallback(CHttpDownloaderCallback* pCallback);
	void SetStopFlag(CHttpDownloaderStopFlag* pStopFlag);
	
	CString GetUrl();
	CString GetLocalFilePath();
	
	void DisableCache(BOOL bDisable);
	BOOL IsCacheDisabled();
	
	DWORD DownloadFile();
	
	DWORD GetAdditionalErrorCode();
	DWORD GetHTTPStatusErrorCode();
	CString GetHTTPStatusErrorMessage();

private:
	DWORD DownloadFileImpl(const CString& strUrl, const CString& strLocalFilePath, CHttpDownloaderCallback* pCallback, CHttpDownloaderStopFlag* pStopFlag);

	void NotifyDownloadBegin(CHttpDownloaderCallback* pCallback);
	void NotifyProgressChange(CHttpDownloaderCallback* pCallback, ULONG nProgress, ULONG nProgressMax);
	void NotifyDownloadComplete(CHttpDownloaderCallback* pCallback, DWORD dwError);

private:
	CString		m_strUrl;
	CString		m_strLocalFilePath;
	CHttpDownloaderCallback*	m_pCallback;
	CHttpDownloaderStopFlag*		m_pStopFlag;
	BOOL		m_bDisableCache;
	
	DWORD		m_dwAdditionalError;
	DWORD		m_dwHTTPStatusCode;
	CString		m_strHTTPStatusMessage;
};