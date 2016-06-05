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

#include "../ContextMenu.h"
#include <interfaces/IUOLMessengerContact.h>


class CContactMenu : public IUOLMessengerMenuItemCallback
{
public:
	CContactMenu();
	virtual ~CContactMenu();

	IUOLMessengerContactPtr GetContact();
	BOOL IsBusy() const;

	void CreateMenu(IUOLMessengerContactPtr pContact);
	void AddItens(CAtlList<IUOLMessengerContextMenuItemPtr>& listItens);
	void AddSeparator();
	void ShowMenu(const CPoint& ptPoint);
	void DestroyMenu();
	
	CContextMenuPtr GetContextMenu();

protected:
	// IUOLMessengerMenuItemCallback interface
	virtual void OnCommand(IUOLMessengerContextMenuItem* pItem);

private:
	void CreateContextMenu();

private:
	static enum ContactCommand
	{
		CC_RENAME_CONTACT = 1,
		CC_REMOVE_CONTACT,
		CC_TURN_VISIBLE,
		CC_TURN_INVISIBLE,
		CC_BLOCK_CONTACT,
		CC_UNBLOCK_CONTACT,
		CC_SEND_MESSAGE,
		CC_SEND_FILE,
		CC_GET_INFO,
		CC_REQUEST_AUTHORIZATION,
		CC_SHOW_HISTORY,
		CC_LAST = CC_SHOW_HISTORY
	};

	IUOLMessengerContactPtr		m_pContact;
	CContextMenuPtr		m_pMainMenu;
	BOOL 				m_bBusy;
};

MAKEAUTOPTR(CContactMenu);