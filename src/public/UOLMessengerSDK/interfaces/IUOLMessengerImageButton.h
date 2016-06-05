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

#include <interfaces/IUOLMessengerImage.h>


class CUOLMessengerImageButtonEventListener;
class CUOLMessengerImageButtonEventListener2;


class __declspec(novtable) IUOLMessengerImageButton
{
public:
	virtual ~IUOLMessengerImageButton() {}

	virtual CString GetCaption() const = 0;
	virtual void SetCaption(const CString& strCaption) = 0;

	virtual CString GetTip() const = 0;
	virtual void SetTip(const CString& strTip) = 0;

	virtual CString GetCommandName() const = 0;
	virtual void SetCommandName(const CString& strCommandName) = 0;

	virtual CString GetDragAndDropCommandName() const = 0;
	virtual void SetDragAndDropCommandName(const CString& strCommandName) = 0;

	virtual int GetWidth() const = 0;
	virtual void SetWidth(int nWidth) = 0;

	virtual BOOL IsPressed() const = 0;
	virtual void SetPressed(BOOL bPressed) = 0;

	virtual BOOL IsPushButton() const = 0;
	virtual void SetPushButton(BOOL bPushButton) = 0;

	virtual BOOL GetDrawTransparent() const = 0;
	virtual void SetDrawTransparent(BOOL bTransparent) = 0;

	virtual BOOL IsAuto() const = 0;
	virtual void SetAuto(BOOL bAuto) = 0;

	virtual BOOL IsVisible() const = 0;
	virtual void SetVisible(BOOL bVisible) = 0;

	virtual IUOLMessengerImagePtr GetImage() const = 0;
	virtual void SetImage(IUOLMessengerImagePtr pImage) = 0;

	virtual void AddEventListener(CUOLMessengerImageButtonEventListener2* pListener) = 0;
	virtual void RemoveEventListener(CUOLMessengerImageButtonEventListener2* pListener) = 0;
};


class __declspec(novtable) IUOLMessengerImageButton2 : public IUOLMessengerImageButton
{
public:
	virtual void SetAttachment(LPVOID /*lpVoid*/) = 0;
	virtual LPVOID GetAttachment() = 0;
};


class __declspec(novtable) IUOLMessengerImageButton3 : public IUOLMessengerImageButton2
{
public:
	virtual CRect GetButtonRect() = 0;
	virtual void SetButtonRect(CRect rect) = 0;
};

class CUOLMessengerImageButtonEventListener
{
public:
	virtual ~CUOLMessengerImageButtonEventListener() {}

	virtual void OnLButtonDown(IUOLMessengerImageButton* pButton, const CPoint& ptClick) {}
	virtual void OnLButtonUp(IUOLMessengerImageButton* pButton, const CPoint& ptClick) {}
	virtual void OnLButtonDblClick(IUOLMessengerImageButton* pButton, const CPoint& ptClick) {}
	virtual void OnRButtonDown(IUOLMessengerImageButton* pButton, const CPoint& ptClick) {}
	virtual void OnRButtonDblClick(IUOLMessengerImageButton* pButton, const CPoint& ptClick) {}
};

class CUOLMessengerImageButtonEventListener2 : public CUOLMessengerImageButtonEventListener
{
public:
	virtual ~CUOLMessengerImageButtonEventListener2() {}

	virtual void OnMouseMove(IUOLMessengerImageButton* pButton, const CPoint& ptClick) {}	
};

MAKEAUTOPTR(IUOLMessengerImageButton);
MAKEAUTOPTR(IUOLMessengerImageButton2);