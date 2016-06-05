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

/*
 * Essa classe visa concentrar uma implementa��o realizada em todos os 
 * componentes IWebBrowser2 utilizados no aplicativo que controla a 
 * exibicao ou nao do menu de contexto padrao do componente.
 * 
 * Com isso centralizaremos tambem um ajuste visando possibilitar a 
 * configuracao da exibicao desse menu antes de compilar a aplicacao.
 * 
 * E isso deverah ser feito atraves do define "_IE_CTRL_RELEASE_TO_QA" 
 * presente no ".cpp" dessa classe.
 * 
 */
 


#pragma once


template<class T>
class CIECTRLMenuHandler
{
public:
	
	CIECTRLMenuHandler()
	{
	}
	
protected:
	
	BEGIN_MSG_MAP(CIECTRLMenuHandler<T>)
		MESSAGE_HANDLER(WM_PARENTNOTIFY, OnParentNotify)
		MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
	END_MSG_MAP()
	
	inline LRESULT OnParentNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DWORD code = LOWORD(wParam);
		
#ifdef _IE_CTRL_RELEASE_TO_QA
		
		bHandled = FALSE;
		
#else
		
		if (code == WM_RBUTTONDOWN)
		{
			void HandleRButtonDown();
		}
		
#endif
		
		return 0L;
	}
	
	inline LRESULT OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DWORD code = HIWORD(lParam);
		
#ifdef _IE_CTRL_RELEASE_TO_QA
		
		return MA_ACTIVATE;
		
#else
		
		if (code == WM_RBUTTONDOWN)
		{
			return MA_ACTIVATEANDEAT;
		}
		else
		{
			return MA_ACTIVATE;
		}
		
#endif
		
		return 0L;
	}
	
	virtual void HandleMouseRButtonDown() {};
};

