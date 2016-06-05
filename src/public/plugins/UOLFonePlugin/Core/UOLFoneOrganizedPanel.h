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


#include "WTLWndComponentsOrganizer.h"


class CUOLFoneOrganizedPanel : public CWindowImpl<CUOLFoneOrganizedPanel>
{
public:
	
	DECLARE_WND_SUPERCLASS("CUOLFoneOrganizedPanel", "STATIC")
	
	CUOLFoneOrganizedPanel(void);
	virtual ~CUOLFoneOrganizedPanel(void);
	
	void Initialize(int leftShift = 0, int topShift = 0, 
			int rightShift = 0, int bottomShift = 0, 
			int verticalAlignment = CWTLWndComponentsOrganizer::WINDOW_ALIGNMENT_TOP);
	
	void SetLeftShift(int leftShift);
	void SetTopShift(int topShift);
	void SetRightShift(int rightShift);
	void SetBottomShift(int bottomShift);
	void SetVerticalAlignment(int verticalAlignment);
	
	INT  AddLine(int componentSpace = 0, 
			int orientation = CWTLWndComponentsOrganizer::LINE_ORIENTATION_LEFT, 
			BOOL fillUp = FALSE);
	INT  AddSeparatorLine(int height);
	INT  AddComponent(CWindow* component, LPCSTR wndClassName, int width, 
			int maximmumHeight = 0, int minimmumHeight = 0, BOOL fillUp = FALSE);
	
	int	GetMinimumWindowWidth();
	int	GetMinimumWindowHeight();
	
	int GetLastLineHeight();
	
protected:
	
	BEGIN_MSG_MAP(CUOLFoneOrganizedColoredPanel)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
	END_MSG_MAP()
	
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
protected:
	
	CWTLWndComponentsOrganizer			m_componentsOrganizer;
};
