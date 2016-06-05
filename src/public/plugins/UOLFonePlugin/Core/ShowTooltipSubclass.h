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
 * Essa classe � uma adapta��o da classe CShowTooltip para os casos 
 * onde o elemento que dever� apresentar o Tooltip nao seja criado, 
 * mas sim realize um SubclassWindow no elemento gr�fico principal.
 * 
 * Neste caso, o componente CShowTooltip original n�o funciona, 
 * pois n�o recebe a mensagem WM_CREATE, e consequentemente n�o 
 * criar� o componente de Tooltip.
 * 
 * Esse problema foi contornado, criando-se o componente Tooltip 
 * no primeiro momento em que ele se torne necess�rio na 
 * manipula��o da mensagem WM_MOUSEMOVE.
 * 
 * Al�m disso, ele � destinado a controle individual, por componente, 
 * do Tooltip a ser apresentado. Diferentemente do CShowToolTip 
 * que se destina a componentes containers de elementos que 
 * apresentar�o o seu Tooltip.
 * 
 */
 


#pragma once


template<class T>
class CShowTooltipSubclass
{
public:
	
	CShowTooltipSubclass()
	{
		m_bIsMouseOver = FALSE;
		m_isShowingTooltip = FALSE;
		m_toolTipCreated = FALSE;
		
		m_maxToolTipWidth = 220;
		
		m_pT = NULL;
		
		m_autoPopDelay = 0;
		m_initialDelay = 0;
		m_reshowDelay = 0;
	}
	
	void SetToolTipText(const CString& strTipText)
	{
		m_tooltipText = strTipText;
	}
	
	CString GetToolTipText()
	{
		return m_tooltipText;
	}
	
	void SetTooltipMaxWidth(int maxWidth)
	{
		m_maxToolTipWidth = maxWidth;
	}
	
	void SetToolTipDelays(int autoPopDelay, int initialDelay, int reshowDelay)
	{
		m_autoPopDelay = autoPopDelay;
		m_initialDelay = initialDelay;
		m_reshowDelay = reshowDelay;
		
		if (m_toolTipCtrl.IsWindow())
		{
			m_toolTipCtrl.SetDelayTime(TTDT_AUTOPOP, m_autoPopDelay);
			m_toolTipCtrl.SetDelayTime(TTDT_INITIAL, m_initialDelay);
			m_toolTipCtrl.SetDelayTime(TTDT_RESHOW, m_reshowDelay);
		}
	}
	
protected:
	
	BEGIN_MSG_MAP(CShowTooltipSubclass<T>)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
	END_MSG_MAP()
	
	inline LRESULT OnMouseMove(UINT uMsg, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		if (!m_pT)
		{
			m_pT = (T*)this;
		}
		
		//ATLTRACE("OnMouseMove() with m_bIsMouseOver = [%d], m_hWnd = [%u], and GetCapture = [%u]\n", 
		//		m_bIsMouseOver, m_pT->m_hWnd, ::GetCapture());
		
		if ( (!m_bIsMouseOver) || (::GetCapture() != m_pT->m_hWnd) )
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = m_pT->m_hWnd;
			tme.dwHoverTime = 0;
			
			if (::_TrackMouseEvent(&tme))
			{
				m_bIsMouseOver = TRUE;
				
				if ( (!m_isShowingTooltip) && (!m_tooltipText.IsEmpty()) && 
						(CreateToolTip()) && (m_toolTipCtrl.IsWindow()) )
				{
					m_isShowingTooltip = TRUE;
					
					m_toolTipCtrl.UpdateTipText((LPCSTR) m_tooltipText, m_pT->m_hWnd);
					m_toolTipCtrl.RelayEvent((LPMSG)m_pT->GetCurrentMessage());
				}
			}
		}
		
		bHandled = FALSE;
		
		return 0L;
	}

	inline LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		//ATLTRACE("OnMouseLeave() with m_bIsMouseOver = [%d], m_isShowingTooltip = [%d]\n", 
		//		m_bIsMouseOver, m_isShowingTooltip);
		
		m_bIsMouseOver = FALSE;
		
		if (m_isShowingTooltip)
		{
			m_isShowingTooltip = FALSE;
			m_toolTipCtrl.Pop();
		}

		bHandled = FALSE;
		
		return 0L;
	}
	
	BOOL CreateToolTip()
	{
		// Creating Tooltip control.
		
		if (!m_toolTipCreated)
		{
			m_toolTipCtrl.Create(m_pT->m_hWnd, NULL, NULL, TTS_NOPREFIX /*| TTS_BALLOON*/);
			
			if (m_autoPopDelay)
			{
				m_toolTipCtrl.SetDelayTime(TTDT_AUTOPOP, m_autoPopDelay);
			}
			
			if (m_initialDelay)
			{
				m_toolTipCtrl.SetDelayTime(TTDT_INITIAL, m_initialDelay);
			}
			
			if (m_reshowDelay)
			{
				m_toolTipCtrl.SetDelayTime(TTDT_RESHOW, m_reshowDelay);
			}
			
			m_toolTipCtrl.AddTool(m_pT->m_hWnd, _T(""));
			m_toolTipCtrl.SetMaxTipWidth(m_maxToolTipWidth);
			
			m_toolTipCreated = TRUE;
		}
		
		return m_toolTipCreated;
	}
	
	
private:
	
	BOOL			m_bIsMouseOver;
	
	CToolTipCtrl	m_toolTipCtrl;
	CString			m_tooltipText;
	BOOL			m_isShowingTooltip;
	BOOL			m_toolTipCreated;
	
	int				m_maxToolTipWidth;
	
	T				*m_pT;
	
	int					m_autoPopDelay;
	int					m_initialDelay;
	int					m_reshowDelay;
};

