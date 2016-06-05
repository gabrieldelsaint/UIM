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

#include "IUOLMessengerContactListSettings.h"
#include "IUOLMessengerGeneralSettings.h"
#include "IUOLMessengerMessageSettings.h"
#include "IUOLMessengerStatusSettings.h"
#include "IUOLMessengerNetworkSettings.h"
#include "IUOLMessengerSoundSettings.h"
#include "IUOLMessengerEmoticonSettings.h"


class CUOLMessengerSettingsManagerObserver;


class __declspec(novtable) IUOLMessengerSettingsManager
{
public:
	virtual ~IUOLMessengerSettingsManager() {}

	virtual BOOL LoadSettings() = 0;
	virtual BOOL SaveSettings() = 0;

	virtual IUOLMessengerContactListSettingsPtr GetContactListSettings() const = 0;
	virtual IUOLMessengerGeneralSettingsPtr GetGeneralSettings() const = 0;
	virtual IUOLMessengerMessageSettingsPtr GetMessageSettings() const = 0;
	virtual IUOLMessengerStatusSettingsPtr GetStatusSettings() const = 0;
	virtual IUOLMessengerNetworkSettingsPtr GetNetworkSettings() const = 0;

	virtual BOOL SetValue(const CString& strKey, const CString& strValue, BOOL bCanReplace = TRUE) = 0;
	virtual BOOL GetValue(const CString& strKey, CString& strValue) const = 0;
};

MAKEAUTOPTR(IUOLMessengerSettingsManager);



class __declspec(novtable) IUOLMessengerSettingsManager2 : public IUOLMessengerSettingsManager
{
public:
	virtual ~IUOLMessengerSettingsManager2() {}

	virtual IUOLMessengerSoundSettings2Ptr GetSoundSettings() const = 0;
	virtual IUOLMessengerEmoticonSettings2Ptr GetEmoticonSettings() const = 0;
};

MAKEAUTOPTR(IUOLMessengerSettingsManager2);



class __declspec(novtable) IUOLMessengerSettingsManager3 : public IUOLMessengerSettingsManager2
{
public:
	virtual ~IUOLMessengerSettingsManager3() {}
	
	virtual void RegisterObserver(CUOLMessengerSettingsManagerObserver* pObserver) = 0;
	virtual void UnregisterObserver(CUOLMessengerSettingsManagerObserver* pObserver) = 0;
};

MAKEAUTOPTR(IUOLMessengerSettingsManager3);




class CUOLMessengerSettingsManagerObserver
{
public:
	virtual ~CUOLMessengerSettingsManagerObserver() {}

	virtual void OnContactListSettingsChanged() { }
	virtual void OnGeneralSettingsChanged() { }
	virtual void OnMessageSettingsChanged() { }
	virtual void OnStatusSettingsChanged() { }
	virtual void OnNetworkSettingsChanged() { }
	virtual void OnSoundSettingsChanged() { }
	virtual void OnEmoticonSettingsChanged() { }
};


