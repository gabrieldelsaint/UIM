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

#include <wmp.h>
#include <wmpids.h>
#include "SongListMng.h"
#include "RadioUOLView.h"
#include "htmlView.h"

static  _ATL_FUNC_INFO  PlayStateChangeInfo = { CC_STDCALL, VT_EMPTY, 1, {VT_I4} };
static  _ATL_FUNC_INFO  PlayListChangeInfo = { CC_STDCALL, VT_EMPTY, 1, {VT_I4} };
static  _ATL_FUNC_INFO  MediaErroInfo = { CC_STDCALL, VT_EMPTY, 1, {VT_I4} };
static  _ATL_FUNC_INFO  MouseClick = { CC_STDCALL, VT_EMPTY, 4, {VT_I4, VT_I4, VT_I4, VT_I4} };

extern const IID DIID__WMPOCXEvents;

#define IDC_WMP					1234
#define SERVER_BUSY_ERROR		-1072885328
#define SERVER_UNKNOWN_ERROR	0


class CRadioUOLMng 	:
	public IDispEventSimpleImpl<IDC_WMP, CRadioUOLMng, &DIID__WMPOCXEvents>
{
public:
	CRadioUOLMng();
	virtual ~CRadioUOLMng();
	CString GetCurrentTime() const;
	CString GetCurrentSong() const;

	CRadioConfig* GetConfig();

	virtual void UpdateDisplay();
	virtual void OnBuy() {}
	virtual void OnSearch() {}
	virtual void OnChannels() {}
	virtual void OnStyles(CPoint /*pt*/) {}
	virtual void OnMute() {}
	virtual void PlayURL(const CString& /*url*/);
	virtual void ShowSearch(int i);

	BEGIN_SINK_MAP(CRadioUOLMng)
		SINK_ENTRY_INFO(IDC_WMP, DIID__WMPOCXEvents, DISPID_WMPCOREEVENT_PLAYSTATECHANGE, OnPlayStateChange, &PlayStateChangeInfo)
		SINK_ENTRY_INFO(IDC_WMP, DIID__WMPOCXEvents, DISPID_WMPCOREEVENT_OPENSTATECHANGE, OpenStateChange, &PlayListChangeInfo)
		SINK_ENTRY_INFO(IDC_WMP, DIID__WMPOCXEvents, DISPID_WMPCOREEVENT_MEDIAERROR, OnMediaError, &MediaErroInfo)
        SINK_ENTRY_INFO(IDC_WMP, DIID__WMPOCXEvents, DISPID_WMPOCXEVENT_CLICK, OnMouseClick, &MouseClick)
	END_SINK_MAP()

	HRESULT STDMETHODCALLTYPE OnPlayStateChange(long /*NewState*/);
	HRESULT STDMETHODCALLTYPE OnMediaError(IDispatch * pMediaObject);
	HRESULT STDMETHODCALLTYPE OpenStateChange  (long NewState);
    HRESULT STDMETHODCALLTYPE OnMouseClick(short  nButton,  short  nShiftState,  long  fX,  long  fY);


protected:
	CComQIPtr<IWMPPlayer>			m_spPlayer;		// Smart pointer to IWMPPlayer interface.
	CComQIPtr<IWMPControls>			m_pC;			// Smart pointer to IWMPControls interface.
	CAxWindow						m_wndView;		// ActiveX host window class.
	CSongListMng*					m_songs;
	CRadioUOLView					m_uolView;
	IUOLMessengerFrameWindowPtr		m_pFrameWindow;
	CSampleFrameWindowViewPtr		m_pView;
	CRadioConfig*					m_pConfig;
	int								m_nPlayCount;
};

