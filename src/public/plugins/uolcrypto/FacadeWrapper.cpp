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

#include "stdafx.h"
#include "resource.h"
#include "FacadeWrapper.h"


CFacadeWrapper::CFacadeWrapper() : 
		m_pFacade(NULL)
{
}


CFacadeWrapper::~CFacadeWrapper()
{
	m_pFacade = NULL;
}


void CFacadeWrapper::Init(IUOLMessengerFacade* pFacade)
{
	m_pFacade = pFacade;
}


void CFacadeWrapper::Finalize()
{
	m_pFacade = NULL;
}


CFacadeWrapper* CFacadeWrapper::GetInstance()
{
	static CFacadeWrapper instance;

	return &instance;
}


IUOLMessengerFacade* CFacadeWrapper::GetFacadeInstance()
{
	return CFacadeWrapper::GetInstance()->GetFacade();
}


IUOLMessengerFacade* CFacadeWrapper::GetFacade()
{
	return m_pFacade;
}


BOOL CFacadeWrapper::GetCurrentUserProfilePath(CString& profilePath)
{
	IUOLMessengerFacade* pUOLMessengerFacade = GetFacadeInstance();
	IUOLMessengerProfileManagerPtr pProfileManager = NULL;
	IUOLMessengerProfileElementPtr pProfileElement = NULL;
	CString currentProfile;
	BOOL result = FALSE;
	
	profilePath.Empty();
	
	if (pUOLMessengerFacade)
	{
		pProfileManager = pUOLMessengerFacade->GetProfileManager();
		
		if (pProfileManager != NULL)
		{
			currentProfile.Empty();
			currentProfile = pProfileManager->GetCurrentProfile();
			
			if (!currentProfile.IsEmpty())
			{
				if (pProfileManager->GetProfileElement(currentProfile, pProfileElement))
				{
					profilePath = pProfileElement->GetProfilePath();
					
					result = TRUE;
				}
			}
		}
	}
	
	return result;
}


BOOL CFacadeWrapper::LoadConfigFileStub(LPCTSTR resourceID, CString& configFileStub)
{
	BOOL bRtn = TRUE;
	LPTSTR lpRes;
	HRSRC hResInfo;
	HGLOBAL hRes;
	
	configFileStub.Empty();
	
	// Find the html resource.
	hResInfo = FindResource(ATL::_AtlBaseModule.GetResourceInstance(), 
			resourceID, RT_HTML);
	
	if (hResInfo == NULL)
	{
		return FALSE;
	}
	
	// Load the html resource. 
	hRes = LoadResource(ATL::_AtlBaseModule.GetResourceInstance(), hResInfo);
	
	if (hRes == NULL)
	{
		return FALSE;
	}
	
	// Lock the wave resource and play it.
	lpRes = (LPTSTR)LockResource(hRes);
	
	if (lpRes != NULL)
	{ 
		configFileStub.Format("%s", lpRes);
	}
	else
	{
		bRtn = 0;
	}
	
	return bRtn;
}