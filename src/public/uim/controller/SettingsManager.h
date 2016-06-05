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

#include <interfaces/IUOLMessengerSettingsManager.h>
#include <interfaces/IUOLMessengerProfileManager.h>
#include "../model/UIMSettings.h"
#include "../controller/Settings/SettingsManagerObserverNotifier.h"


class CSettingsManager : public IUOLMessengerSettingsManager3
{
public:
	CSettingsManager(IUOLMessengerProfileManagerPtr pProfileManager);
	virtual ~CSettingsManager();
	
	void NotifyContactListSettingsChanged();
	void NotifyGeneralSettingsChanged();
	void NotifyMessageSettingsChanged();
	void NotifyStatusSettingsChanged();
	void NotifyNetworkSettingsChanged();
	void NotifySoundSettingsChanged();
	void NotifyEmoticonSettingsChanged();

protected:
	// IUOLMessengerSettingsManager interface
	virtual BOOL LoadSettings();
	virtual BOOL SaveSettings();

	virtual IUOLMessengerContactListSettingsPtr GetContactListSettings() const;
	virtual IUOLMessengerGeneralSettingsPtr GetGeneralSettings() const;
	virtual IUOLMessengerMessageSettingsPtr GetMessageSettings() const;
	virtual IUOLMessengerStatusSettingsPtr GetStatusSettings() const;
	virtual IUOLMessengerNetworkSettingsPtr GetNetworkSettings() const;

	virtual BOOL SetValue(const CString& strKey, const CString& strValue, BOOL bCanReplace = TRUE);
	virtual BOOL GetValue(const CString& strKey, CString& strValue) const;

	// IUOLMessengerSettingsManager2 interface
	virtual IUOLMessengerSoundSettings2Ptr GetSoundSettings() const;
	virtual IUOLMessengerEmoticonSettings2Ptr GetEmoticonSettings() const;
	
	// IUOLMessengerSettingsManager3 interface
	virtual void RegisterObserver(CUOLMessengerSettingsManagerObserver* pObserver);
	virtual void UnregisterObserver(CUOLMessengerSettingsManagerObserver* pObserver);

private:
	CUIMSettingsPtr						m_pAppSettings;
	IUOLMessengerSoundSettings2Ptr		m_pSoundSettings;
	IUOLMessengerEmoticonSettings2Ptr	m_pEmoticonSettings;
	CSettingsManagerObserverNotifier	m_observerNotifier;
};


MAKEAUTOPTR(CSettingsManager);
