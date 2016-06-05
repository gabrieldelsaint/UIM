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

#include <interfaces/UOLMessengerPlugin.h>


class CPluginInfo
{
public:
	enum UpdateInfo
	{
		none,
		updateAvailable,
		installAvailable
	};

	CPluginInfo(const CString& strInternalName);
	~CPluginInfo();

	//CUOLMessengerPlugin* GetPlugin();

	CString GetInternalName() const;

	CString GetName() const;
	CString GetDesc() const;
	ULONGLONG GetVersion() const;

	CString GetDownloadUrl() const;
	CString GetDirName() const;
	CString GetFileName() const;

	CString GetIconUrl() const;
	IUOLMessengerImagePtr GetIcon();

	UpdateInfo GetUpdateInfo() const;

	BOOL IsInstallAvailable() const;
	BOOL IsUpdateAvailable() const;

protected:
	void SetPlugin(CUOLMessengerPlugin* pPlugin);

	void SetName(const CString& strName);
	void SetDesc(const CString& strDesc);
	void SetVersion(ULONGLONG lVersion);

	void SetDownloadUrl(const CString& strDownloadUrl);
	void SetDirName(const CString& strDirName);
	void SetFileName(const CString& strFileName);
	
	void SetIconUrl(const CString& strIconUrl);
	void SetIcon(IUOLMessengerImagePtr pIcon);
	void SetUpdateInfo(UpdateInfo enumUpdateInfo);

private:
	

protected:
	friend class CUOLMessengerPluginManager;

private:
	CUOLMessengerPlugin*	m_pPlugin;

	CString		m_strInternalName;
	CString		m_strName;
	CString 	m_strDesc;
	ULONGLONG	m_lVersion;

	CString		m_strDownloadUrl;
	CString 	m_strDirName;
	CString 	m_strFileName;

	CString		m_strIconUrl;
	IUOLMessengerImagePtr	m_pIcon;

	UpdateInfo			 m_enumUpdateInfo;
};

MAKEAUTOPTR(CPluginInfo);