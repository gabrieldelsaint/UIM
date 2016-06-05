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
#include "TrayWindow.h"

CTrayWindow::CTrayWindow()
{
	// TODO: verificar porque ZeroMemory d� pau com SmartPtr da BOOST
	//	ZeroMemory(&m_nid, sizeof(NOTIFYICONDATA));
	m_nid.cbSize =  sizeof(NOTIFYICONDATA);
}

CTrayWindow::~CTrayWindow()
{

}

BOOL CTrayWindow::RemoveIcon()
{
	m_nid.uFlags			= NIF_MESSAGE ;
	m_nid.hWnd				= m_hWnd;	
	m_nid.hIcon				= m_hIcon;
	m_nid.uID				= 0;
	m_nid.uCallbackMessage	= WM_NOTIFYICON;

	return ::Shell_NotifyIcon(NIM_DELETE, &m_nid);
}

BOOL CTrayWindow::AddIcon()
{
	m_nid.uFlags			= NIF_ICON | NIF_MESSAGE ;
	m_nid.hWnd				= m_hWnd;	
	m_nid.hIcon				= m_hIcon;
	m_nid.uID				= 0;
	m_nid.uCallbackMessage	= WM_NOTIFYICON;

	return ::Shell_NotifyIcon(NIM_ADD, &m_nid);
}

BOOL CTrayWindow::SetTip(const CString& strTip)
{
	m_nid.uFlags			= NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.hWnd				= m_hWnd;	
	m_nid.hIcon				= m_hIcon;
	m_nid.uID				= 0;
	m_nid.uCallbackMessage	= WM_NOTIFYICON;

	ATLASSERT(strTip.GetLength() < 64);

	_tcsncpy(m_nid.szTip, (LPCTSTR)strTip, 64);


	return ::Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}

BOOL CTrayWindow::DisableTip()
{
	m_nid.uFlags			= NIF_ICON | NIF_MESSAGE;
	m_nid.hWnd				= m_hWnd;	
	m_nid.hIcon				= m_hIcon;
	m_nid.uID				= 0;
	m_nid.uCallbackMessage	= WM_NOTIFYICON;		
	m_nid.szTip[0]			= NULL;				

	return ::Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}

HWND CTrayWindow::Create(HWND hParent, HICON hIcon)
{
	m_hIcon = hIcon;

	HWND hwnd = __super::Create(hParent, NULL, NULL, 0, WS_EX_TOOLWINDOW);

	return hwnd;
}

void CTrayWindow::SetIcon(HICON hIcon)
{
	m_hIcon = hIcon;
}

BOOL CTrayWindow::UpdateIcon()
{
	m_nid.uFlags			= NIF_ICON | NIF_MESSAGE ;
	m_nid.hWnd				= m_hWnd;	
	m_nid.hIcon				= m_hIcon;
	m_nid.uID				= 0;
	m_nid.uCallbackMessage	= WM_NOTIFYICON;

	return ::Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}

void CTrayWindow::OnNotifyIcon(WPARAM /*wParam*/, LPARAM lParam)
{ 
	POINT pt;
	GetCursorPos(&pt);

	SendMessage(lParam, 0, MAKELPARAM(pt.x, pt.y));
}