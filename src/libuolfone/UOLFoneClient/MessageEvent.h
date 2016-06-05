/* UOL Fone
 * Copyright (c) 2006 Universo Online S/A
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
 * Universo Online S/A - A/C: UOL Fone 5o. Andar
 * Avenida Brigadeiro Faria Lima, 1.384 - Jardim Paulistano
 * S�o Paulo SP - CEP 01452-002 - BRASIL  */


#pragma once

#include "interfaces/IUOLFoneClientMessageEvent.h"


class CMessageEvent :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IUOLFoneClientMessageEvent>
{
public:
	CMessageEvent();
	virtual ~CMessageEvent();

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_lEventType = UFC_MESSAGE_EVENT_TYPE_UNKNOWN;

		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

//	ULONG InternalAddRef()
//	{
//		ULONG l = __super::InternalAddRef();
//
//#ifdef _DEBUG
//		CString str;
//		str.Format("%s %i\n", __FUNCTION__, l);
//
//		::OutputDebugString(str);
//#endif
//		return l;
//	}
//
//	ULONG InternalRelease()
//	{
//		ULONG l = __super::InternalRelease();
//
//#ifdef _DEBUG
//		CString str;
//		str.Format("%s %i\n", __FUNCTION__, l);
//
//		::OutputDebugString(str);
//#endif	
//
//		return l;
//	}

	BEGIN_COM_MAP(CMessageEvent)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IUOLFoneClientMessageEvent)
	END_COM_MAP()

	STDMETHOD(GetEventType)(LONG* plEventType);
	STDMETHOD(GetFrom)(BSTR* pbstrFrom);
	STDMETHOD(GetTo)(BSTR* pbstrTo);
	STDMETHOD(GetContentType)(BSTR* pbstrContentType);
	STDMETHOD(GetContentSubtype)(BSTR* pbstrContentSubtype);
	STDMETHOD(GetContent)(BSTR* pbstrContent);

	LONG GetEventType();
	CString GetFrom();
	CString GetTo();
	CString GetContentType();
	CString GetContentSubtype();
	CString GetContent();

	void SetEventType(LONG lEventType);
	void SetFrom(const CString& strFrom);
	void SetTo(const CString& strTo);
	void SetContentType(const CString& strContentType);
	void SetContentSubtype(const CString& strContentSubtype);
	void SetContent(const CString& strContent);


private:
	LONG		m_lEventType;
	CString		m_strFrom;
	CString		m_strTo;
	CString		m_strContentType;
	CString		m_strContentSubtype;
	CString		m_strContent;
};