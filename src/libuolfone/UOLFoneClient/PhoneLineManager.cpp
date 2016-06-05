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


#include "stdafx.h"
#include "PhoneLineManager.h"


CPhoneLineManager::CPhoneLineManager()
{
}


CPhoneLineManager::~CPhoneLineManager()
{
}


IUOLFoneClientPhoneLine* CPhoneLineManager::AddPhoneLine(LONG lPhoneLineId, IUOLFoneClientPhoneLineInfo* pPhoneLineInfo)
{
	ATLTRACE(_T("%s - lPhoneLineId = [%d]\n"), __FUNCTION__, lPhoneLineId);

	IUOLFoneClientPhoneLine* pPhoneLine = NULL;

	CComObject<CPhoneLine>* pFindPhoneLineObj = InternalGetPhoneLine(lPhoneLineId);

	if (pFindPhoneLineObj)
	{
		ATLTRACE(_T("%s - Removing old CPhoneLine object\n"), __FUNCTION__);

		// Release old phone line
		BOOL bRet = m_mapPhoneLines.RemoveKey(lPhoneLineId);
		ATLASSERT(bRet);

		pFindPhoneLineObj->Release();
	}

	CComObject<CPhoneLine>* pPhoneLineObj = NULL;

	HRESULT hr = CComObject<CPhoneLine>::CreateInstance(&pPhoneLineObj);

	if (SUCCEEDED(hr))
	{
		pPhoneLineObj->SetPhoneLineId(lPhoneLineId);
		pPhoneLineObj->SetPhoneLineInfo(pPhoneLineInfo);
		pPhoneLineObj->SetPhoneLineState(UFC_PHONE_LINE_STATE_UNREGISTERED);

		pPhoneLineObj->AddRef();
		m_mapPhoneLines.SetAt(lPhoneLineId, pPhoneLineObj);

		pPhoneLine = pPhoneLineObj;
		pPhoneLine->AddRef();
	}

	return pPhoneLine;
}


IUOLFoneClientPhoneLine* CPhoneLineManager::GetPhoneLine(LONG lPhoneLineId)
{
	IUOLFoneClientPhoneLine* pPhoneLine = NULL;

	CComObject<CPhoneLine>* pPhoneLineObj = InternalGetPhoneLine(lPhoneLineId);

	if (pPhoneLineObj)
	{
		pPhoneLine = pPhoneLineObj;
		pPhoneLine->AddRef();
	}

	return pPhoneLine;
}


IUOLFoneClientPhoneLine* CPhoneLineManager::RemovePhoneLine(LONG lPhoneLineId)
{
	ATLTRACE(_T("%s - lPhoneLineId = [%d]\n"), __FUNCTION__, lPhoneLineId);

	IUOLFoneClientPhoneLine* pPhoneLine = NULL;
		
	CComObject<CPhoneLine>* pPhoneLineObj = InternalGetPhoneLine(lPhoneLineId);

	if (pPhoneLineObj != NULL)
	{
		BOOL bRet = m_mapPhoneLines.RemoveKey(lPhoneLineId);
		ATLASSERT(bRet);

		pPhoneLine = pPhoneLineObj;
		pPhoneLine->AddRef();

		pPhoneLineObj->Release();
	}

	return pPhoneLine;
}


void CPhoneLineManager::RemoveAllPhoneLines()
{
	CPhoneLineMap::CPair* pPair;

	for (POSITION pos = m_mapPhoneLines.GetStartPosition(); pos; )
	{
		pPair = m_mapPhoneLines.GetNext(pos);

		CComObject<CPhoneLine>* pPhoneLineObj = pPair->m_value;
		pPhoneLineObj->Release();
	}

	m_mapPhoneLines.RemoveAll();
}


void CPhoneLineManager::SetPhoneLineState(LONG lPhoneLineId, EnumPhoneLineState state)
{	
	CComObject<CPhoneLine>* pPhoneLineObj = InternalGetPhoneLine(lPhoneLineId);

	if (pPhoneLineObj != NULL)
	{
		pPhoneLineObj->SetPhoneLineState(state);
	}
}


UINT CPhoneLineManager::GetPhoneLineCount()
{
	return (UINT) m_mapPhoneLines.GetCount();
}


CComObject<CPhoneLine>* CPhoneLineManager::InternalGetPhoneLine(LONG lPhoneLineId)
{
	CComObject<CPhoneLine>* pPhoneLineObj = NULL;

	CPhoneLineMap::CPair* pPair = m_mapPhoneLines.Lookup(lPhoneLineId);

	if (pPair)
	{
		pPhoneLineObj = pPair->m_value;
	}

	return pPhoneLineObj;
}
