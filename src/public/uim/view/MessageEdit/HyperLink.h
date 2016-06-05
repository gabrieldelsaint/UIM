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
 Copyright (c) 1999, kSet Lab 
 Author: Konstantin Bukreev 
 E-mail: konstantin@mail.primorye.ru 

 Created: 12/27/1999 2:19:37 PM
 Version: 1.0.0

 Parts of code by:
	Ferdinand Prantl (prantl@ff.cuni.cz) and MFC Godeguru Site (http://www.codeguru.com)
*/

#ifndef _CHyperLink_93785d76_6b70_4912_a306_6abc33fc7f92
#define _CHyperLink_93785d76_6b70_4912_a306_6abc33fc7f92

#if _MSC_VER > 1000 
#pragma once
#endif // _MSC_VER > 1000

#ifdef _WININET_NEED_
#include <Wininet.h>
#include <winnetwk.h>
#include <winnls.h>
#endif

#include <intshcut.h>

class CRichEditHyperLink
{
public:
	enum {OPEN, EDIT, PRINT};	
public:
	static bool Open (TCHAR* pLink, int how, HWND hWnd = GetActiveWindow());
	static bool OpenUsingCom (TCHAR* pLink, int how, HWND hWnd = GetActiveWindow());
	static bool OpenUsingShellExecute (TCHAR* pLink, int how, HWND hWnd = GetActiveWindow());
	#ifdef _WININET_NEED_
	static bool ParseURL(TCHAR* pURL, URL_COMPONENTS& urlComponents, DWORD dwFlags = 0);
	static bool GetInternetScheme (TCHAR* pURL, INTERNET_SCHEME& nScheme, DWORD dwFlags = 0);
	#endif
};

#endif //_CHyperLink_93785d76_6b70_4912_a306_6abc33fc7f92

