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
#include "UOLButtonImageSwitcher.h"

#include "../resource.h"
#include "image/Image.h"
#include "image/ImageBuilder.h"
#include "../controller/UIMApplication.h"



CUOLButtonImageSwitcher::CUOLButtonImageSwitcher(CImageButtonBasePtr pButton, HWND hWndParent) : 
	m_wndParent(hWndParent),
	m_bAuthenticated(FALSE)
{
	ATLASSERT(pButton.get());
	m_pButton = pButton;
}


CUOLButtonImageSwitcher::~CUOLButtonImageSwitcher()
{
}


void CUOLButtonImageSwitcher::Init()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	BOOL bAuthenticated = CUIMApplication::GetApplication()->GetAuthenticationManager()->IsAuthenticated();

	LoadButtonImage(bAuthenticated);

	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);

	pLoop->AddIdleHandler(this);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


void CUOLButtonImageSwitcher::Finalize()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);

	pLoop->RemoveIdleHandler(this);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


BOOL CUOLButtonImageSwitcher::OnIdle()
{
	UpdateButtonImage();

	return TRUE;
}


void CUOLButtonImageSwitcher::UpdateButtonImage()
{
	BOOL bAuthenticated = CUIMApplication::GetApplication()->GetAuthenticationManager()->IsAuthenticated();

	if (m_bAuthenticated != bAuthenticated)
	{
		LoadButtonImage(bAuthenticated);

		m_bAuthenticated = bAuthenticated;
	}
}


void CUOLButtonImageSwitcher::LoadButtonImage(BOOL bAuthenticatedImage)
{
	ATLTRACE(_T("%s - %d\n"), __FUNCTION__, bAuthenticatedImage);

	if (m_pButton.get())
	{
		UOLMessengerImage::CImagePtr pImage = UOLMessengerImage::CImageBuilder::LoadImageFromResource(_Module.GetModuleInstance(), bAuthenticatedImage ? IDB_UOL_BUTTON_AUTHENTICATED : IDB_UOL_BUTTON_NOT_AUTHENTICATED);

		if (pImage != NULL)
		{
			m_pButton->SetImage(pImage);

			if (m_wndParent.IsWindow())
			{
				m_wndParent.InvalidateRect(NULL);
				m_wndParent.UpdateWindow();
			}
		}
	}
}