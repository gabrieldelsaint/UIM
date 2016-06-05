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

#include "IUOLMessengerContact.h"


class __declspec(novtable) IUOLMessengerImagesProtocol
{
public:
	virtual ~IUOLMessengerImagesProtocol() {}
	virtual IUOLMessengerImagePtr GetDefaultImage(const CString& strProtocolID, DWORD dwId) = 0;
	virtual IUOLMessengerImagePtr GetUserImage(const CString& strProtocolID, DWORD dwStatus) = 0;
	virtual IUOLMessengerImagePtr GetUserStatusImage(const CString& strProtocolID, DWORD dwStatus) = 0;
	virtual IUOLMessengerImagePtr GetContactImage(const CString& strProtocolID, DWORD dwStatus) = 0;
	virtual IUOLMessengerImagePtr GetContactStatusImage(IUOLMessengerContactPtr contact) = 0;
	virtual IUOLMessengerImagePtr GetContactBlockedImage(const CString& strProtocolID) = 0;
	virtual IUOLMessengerImagePtr GetContactAuthorizationIcon(const CString& strProtocolID, BOOL bAuthorized = FALSE) = 0;
	virtual CString GetUserImagePath(const CString& strProtocolID, DWORD dwStatus) = 0;
	virtual CString GetContactImagePath(const CString& strProtocolID, DWORD dwStatus)= 0;

	virtual void InsertDefaultImage(const CString& strProtocolID, DWORD dwId, IUOLMessengerImagePtr pImage) = 0;
	virtual void InsertUserStatusImage(const CString& strProtocolID,DWORD dwStatus, IUOLMessengerImagePtr pImage) = 0;
	virtual void InsertContactStatusImage(const CString& strProtocolID,DWORD dwStatus, IUOLMessengerImagePtr pImage) = 0;
	virtual void InsertDefaultImage(const CString& strProtocolID, DWORD dwId, const CString& strFilePath) = 0;
	virtual void InsertUserImage(const CString& strProtocolID, DWORD dwId,const CString& strFile) = 0;
	virtual void InsertUserStatusImage(const CString& strProtocolID,DWORD dwStatus, const CString& strFilePath) = 0;
	virtual void InsertContactImage(const CString& strProtocolID,DWORD dwId, const CString& strFile) = 0;
	virtual void InsertContactStatusImage(const CString& strProtocolID,DWORD dwStatus, const CString& strFilePath) = 0;
	virtual void InsertContactBlockedImage(const CString& strProtocolID, IUOLMessengerImagePtr pImage) = 0;
	virtual void InsertContactAuthorizationIcon(const CString& strProtocolID, IUOLMessengerImagePtr pImage, BOOL bAuthorized) = 0;
};

MAKEAUTOPTR(IUOLMessengerImagesProtocol);


class __declspec(novtable) IUOLMessengerImagesProtocol2 : public IUOLMessengerImagesProtocol
{
public:
	virtual ~IUOLMessengerImagesProtocol2() {}
    virtual IUOLMessengerImagePtr GetContactUnknownStatusImage(IUOLMessengerContactPtr contact) = 0;
};

MAKEAUTOPTR(IUOLMessengerImagesProtocol2);


class __declspec(novtable) IUOLMessengerImagesProtocol3 : public IUOLMessengerImagesProtocol2
{
public:
	virtual ~IUOLMessengerImagesProtocol3() {}
	virtual IUOLMessengerImagePtr GetStatusButtonImage(const CString& strProtocolID, DWORD dwStatus) = 0;
	virtual void InsertStatusButtonImage(const CString& strProtocolID, DWORD dwStatus, IUOLMessengerImagePtr pImage) = 0;
};

MAKEAUTOPTR(IUOLMessengerImagesProtocol3);
