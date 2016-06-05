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


#include <interfaces/IUOLMessengerThemeManager.h>
#include <interfaces/IUOLMessengerCommonSettings.h>
#include <interfaces/IUOLMessengerSettingsManager.h>
#include "../model/ThemeSettings.h"



class CThemeManager : public IUOLMessengerThemeManager
{
private:
	BOOL InitTheme();

public:
	CThemeManager(IUOLMessengerCommonSettingsPtr pCommonSettings);
	virtual ~CThemeManager();

	EnLoadTheme LoadTheme();
	BOOL SaveTheme();

// xxx	virtual IUOLMessengerThemePtr GetCurrentTheme();
	virtual IUOLMessengerSoundSettingsPtr GetSoundSettings() const;
	virtual IUOLMessengerEmoticonSettingsPtr GetEmoticonSettings() const;
	virtual void GetThemeList(CAtlMap <CString, CString>& mapTheme);
	virtual BOOL ImportFile(int nDestFolder, CString strSourcePath, CString & strDestRelative);
	virtual CString GetSelectedThemeFolder();
	virtual CString GetSelectedThemePath();
	virtual void SetDefaultTheme();
	virtual void SetThemeChanged(BOOL bThemeChanged);
	virtual BOOL IsThemeChanged();

private:
	//CString GetDefaultThemePath();
	//BOOL UnzipToTemp(CString strThemePath);
	//BOOL ZipFromTemp();
	//BOOL UnzipToTemp();
	//BOOL RemoveTempThemeFolder();
	//void ListThemeFolder(const CString& strFolder, CAtlList <CString>& listThemeAllFiles);

private:
	//IUOLMessengerCommonSettingsPtr	m_pCommonSettings;
	//CThemeSettingsPtr				m_pAppTheme;

	//CString		m_strSelectedTheme;
	//CString		m_strSelectedThemeTempFolder;
	//BOOL		m_bThemeChanged;
};

MAKEAUTOPTR(CThemeManager);