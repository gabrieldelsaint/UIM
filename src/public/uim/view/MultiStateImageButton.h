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

#include "ImageButton.h"
#include <interfaces/IUOLMessengerMultiStateImageButton.h>

#include "ButtonStateInfo.h"


class CMultiStateImageButton : 
	public IUOLMessengerMultiStateImageButton,
	public CImageButton
{
public:
	CMultiStateImageButton(HWND hWndParent = NULL);
	virtual ~CMultiStateImageButton();

protected:
	virtual CString GetCaption() const;
	virtual void SetCaption(const CString& strCaption);

	virtual CString GetTip() const;
	virtual void SetTip(const CString& strTip);

	virtual CString GetCommandName() const;
	virtual void SetCommandName(const CString& strCommandName);

	virtual CString GetDragAndDropCommandName() const;
	virtual void SetDragAndDropCommandName(const CString& strCommandName);

	virtual int GetWidth() const;
	virtual void SetWidth(int nWidth);

	virtual BOOL IsPressed() const;
	virtual void SetPressed(BOOL bPressed);

	virtual BOOL IsPushButton() const;
	virtual void SetPushButton(BOOL bPushButton);

	virtual BOOL GetDrawTransparent() const;
	virtual void SetDrawTransparent(BOOL bTransparent);

	virtual BOOL IsAuto() const;
	virtual void SetAuto(BOOL bAuto);

	virtual BOOL IsVisible() const;
	virtual void SetVisible(BOOL bVisible);

	virtual IUOLMessengerImagePtr GetImage() const;
	virtual void SetImage(IUOLMessengerImagePtr pImage);

	virtual void AddEventListener(CUOLMessengerImageButtonEventListener2* pListener);
	virtual void RemoveEventListener(CUOLMessengerImageButtonEventListener2* pListener);

	virtual void SetActiveState(const CString& strStateName);
	virtual CString GetActiveState();

	virtual void AddStateInfo(IUOLMessengerButtonStateInfoPtr pButtonStateInfo);
	virtual IUOLMessengerButtonStateInfoPtr RemoveStateInfo(const CString& strStateName);
	virtual IUOLMessengerButtonStateInfoPtr GetStateInfo(const CString& strStateName);

	virtual void GetStateInfoList(CAtlList<IUOLMessengerButtonStateInfoPtr>& listStateInfos);

	virtual void AddElement(IElementPtr pElement);

	virtual void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);

protected:
	CString		m_strDefaultState;
	CString		m_strActiveState;

	typedef CAtlMap<CString, IUOLMessengerButtonStateInfoPtr> CButtonStateInfoMap;
	CButtonStateInfoMap	m_mapStateInfo;
};

MAKEAUTOPTR(CMultiStateImageButton);