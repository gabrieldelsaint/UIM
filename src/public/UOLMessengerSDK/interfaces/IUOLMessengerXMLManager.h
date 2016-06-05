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

#include "IUOLMessengerHistoryContact.h"

#include <atlcoll.h>
#include "stdafx.h"

class IUOLMessengerXMLManager;
MAKEAUTOPTR(IUOLMessengerXMLManager);

class __declspec(novtable) IUOLMessengerXMLManager
{
public:
	virtual ~IUOLMessengerXMLManager() {}
	
	virtual CString GetFrom() const = 0;
	virtual void SetFrom(const CString& strFrom) = 0;

	virtual CString GetTime() const = 0;
	virtual void SetTime(const CString& strFrom)= 0;

	virtual CString GetCallStatus() const = 0;
	virtual void SetCallStatus(const CString& strFrom)= 0;
	
	virtual CString GetContact() const = 0;
	virtual void SetContact(const CString& strFrom)= 0;

	virtual CString GetId() const = 0;
	virtual void SetId(const CString& strFrom)= 0;

	virtual CString GetDate() const = 0;
	virtual void SetDate(const CString& strFrom)= 0;

	virtual CString GetProtocol() const = 0;
	virtual void SetProtocol(const CString& strFrom)= 0;

	virtual CString GetType() const = 0;
	virtual void SetType(const CString& strFrom)= 0;

	virtual CString GetMessage() const = 0;
	virtual void SetMessage(const CString& strFrom)= 0;

	virtual void AddElements(CAtlMap<CString, CString> mapXMLElements) = 0;
	virtual void AddAttributes(CAtlMap<CString, CString> mapXMLAttributes) = 0;

	virtual void GetElements(CAtlMap<CString, CString> &mapXMLElements) = 0;
	virtual void GetAttributes(CAtlMap<CString, CString> &mapXMLAttributes) = 0;

};
