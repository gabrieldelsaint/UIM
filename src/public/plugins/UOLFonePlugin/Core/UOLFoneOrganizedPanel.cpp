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
 

#include "StdAfx.h"
#include ".\UOLFoneOrganizedPanel.h"


/////////////////////////////////////////////////////////////////////
// CUOLFoneOrganizedPanel.
/////////////////////////////////////////////////////////////////////


CUOLFoneOrganizedPanel::CUOLFoneOrganizedPanel(void)
{
	m_componentsOrganizer.Initialize(this);
}


CUOLFoneOrganizedPanel::~CUOLFoneOrganizedPanel(void)
{
}


/////////////////////////////////////////////////////////////////////
// Organizing methods.
/////////////////////////////////////////////////////////////////////


void CUOLFoneOrganizedPanel::Initialize(int leftShift, 
		int topShift, int rightShift, int bottomShift, int verticalAlignment)
{
	m_componentsOrganizer.Initialize(this, leftShift, topShift, 
			rightShift, bottomShift, verticalAlignment);
}


void CUOLFoneOrganizedPanel::SetLeftShift(int leftShift)
{
	m_componentsOrganizer.SetLeftShift(leftShift);
}


void CUOLFoneOrganizedPanel::SetTopShift(int topShift)
{
	m_componentsOrganizer.SetTopShift(topShift);
}


void CUOLFoneOrganizedPanel::SetRightShift(int rightShift)
{
	m_componentsOrganizer.SetRightShift(rightShift);
}


void CUOLFoneOrganizedPanel::SetBottomShift(int bottomShift)
{
	m_componentsOrganizer.SetBottomShift(bottomShift);
}


void CUOLFoneOrganizedPanel::SetVerticalAlignment(int verticalAlignment)
{
	m_componentsOrganizer.SetVerticalAlignment(verticalAlignment);
}


INT CUOLFoneOrganizedPanel::AddLine(
		int componentSpace, int orientation, BOOL fillUp)
{
	return m_componentsOrganizer.AddLine(componentSpace, orientation, fillUp);
}


INT CUOLFoneOrganizedPanel::AddSeparatorLine(int height)
{
	return m_componentsOrganizer.AddSeparatorLine(height);
}


INT CUOLFoneOrganizedPanel::AddComponent(
		CWindow* component, LPCSTR wndClassName, int width,
		int maximmumHeight, int minimmumHeight, BOOL fillUp)
{
	return m_componentsOrganizer.AddComponent(component, wndClassName, width, 
			maximmumHeight, minimmumHeight, fillUp);
}


int	CUOLFoneOrganizedPanel::GetMinimumWindowWidth()
{
	return m_componentsOrganizer.GetMinimumWindowWidth();
}


int	CUOLFoneOrganizedPanel::GetMinimumWindowHeight()
{
	return m_componentsOrganizer.GetMinimumWindowHeight();
}


int CUOLFoneOrganizedPanel::GetLastLineHeight()
{
	return m_componentsOrganizer.GetLastLineHeight();
}


/////////////////////////////////////////////////////////////////////
// Messages handling.
/////////////////////////////////////////////////////////////////////


LRESULT CUOLFoneOrganizedPanel::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_componentsOrganizer.OrganizeComponents();
	
	return 0L;
}

