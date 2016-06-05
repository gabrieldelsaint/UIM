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


class CStringGUID : public CString
{
public:
	CStringGUID()
	{
		GUID guid;
		::CoCreateGuid(&guid);

		LPOLESTR lpStr;
		::StringFromCLSID(guid, &lpStr);

		*static_cast<CString*>(this) = lpStr;

		::CoTaskMemFree(lpStr);
	}
};


template <class T>
BOOL IsBadReadPtr(CONST T* lp)
{
	return ::IsBadReadPtr(lp, sizeof(lp));
}


__interface IAuthenticationFlag
{
	void SetAuthenticated(LONG b, LPCTSTR szAuthCookie);
	LONG IsAuthenticated(int nUserType = -1) const;
};

__interface IShutdownFlag
{
	LONG KillReceived() const;
};

__interface ILiveUpdateFlag
{
	void SetLiveUpdateFlag(LONG bState);
	LONG GetLiveUpdateFlag() const;
};


CString GetIEUserAgent();

CString GetAppUserAgent();

CString GetDefaultBrowser();


// para msg refletidas
#define OCM_NOTIFY_CODE_HANDLER_EX(cd, func) \
if (uMsg == OCM_NOTIFY && cd == ((LPNMHDR)lParam)->code) \
{ \
	SetMsgHandled(TRUE); \
	lResult = func((LPNMHDR)lParam); \
	if(IsMsgHandled()) \
		return TRUE; \
}

#define OCM_COMMAND_CODE_HANDLER_EX(code, func) \
if (uMsg == OCM_COMMAND && code == HIWORD(wParam)) \
{ \
	SetMsgHandled(TRUE); \
	func((UINT)HIWORD(wParam), (int)LOWORD(wParam), (HWND)lParam); \
	lResult = 0; \
	if(IsMsgHandled()) \
		return TRUE; \
}

#define OCM_COMMAND_RANGE_HANDLER_EX(idFirst, idLast, func) \
if(uMsg == OCM_COMMAND && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast) \
{ \
	SetMsgHandled(TRUE); \
	func((UINT)HIWORD(wParam), (int)LOWORD(wParam), (HWND)lParam); \
	lResult = 0; \
	if(IsMsgHandled()) \
		return TRUE; \
}