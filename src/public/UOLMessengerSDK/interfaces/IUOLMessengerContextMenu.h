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


class IUOLMessengerContextMenu;
MAKEAUTOPTR(IUOLMessengerContextMenu);


class IUOLMessengerContextMenu
{
public:
	
	virtual ~IUOLMessengerContextMenu()	{};
	
	virtual IUOLMessengerContextMenuItemPtr AddCustomMenuItem(
			const CString& strLabel, IUOLMessengerMenuItemCallback* pCallback, 
			BOOL bAddSeparator = FALSE) { return NULL; };
	
	/*
	 * AddMenuItem
	 *
	 * First parameter must be a pointer to the implementation of the plugin executing 
	 * the method (i.e., "CUOLMessengerPlugin*").
	 * Only authorized plugins can execute these method.
	 *
	 * @param pUOLMessengerPlugin	Pointer to plugin executing method.
	 *
	 */
	virtual IUOLMessengerContextMenuItemPtr AddMenuItem(
			void* pUOLMessengerPlugin, int nCommandId, 
			const CString& strLabel, IUOLMessengerMenuItemCallback* pCallback, 
			BOOL bAddSeparator = FALSE) = 0;
	
	/*
	 * RemoveMenuItem
	 *
	 * First parameter must be a pointer to the implementation of the plugin executing 
	 * the method (i.e., "CUOLMessengerPlugin*").
	 * Only authorized plugins can execute these method.
	 *
	 * @param pUOLMessengerPlugin	Pointer to plugin executing method.
	 *
	 */
	virtual void RemoveMenuItem(
			void* pUOLMessengerPlugin, IUOLMessengerContextMenuItemPtr pItem) = 0;
	
	/*
	 * RemoveAllMenuItems
	 *
	 * First parameter must be a pointer to the implementation of the plugin executing 
	 * the method (i.e., "CUOLMessengerPlugin*").
	 * Only authorized plugins can execute these method.
	 *
	 * @param pUOLMessengerPlugin	Pointer to plugin executing method.
	 *
	 */
	virtual void RemoveAllMenuItems(void* pUOLMessengerPlugin) = 0;
	
	/*
	 * EnableMenuItem
	 *
	 * First parameter must be a pointer to the implementation of the plugin executing 
	 * the method (i.e., "CUOLMessengerPlugin*").
	 * Only authorized plugins can execute these method.
	 *
	 * @param pUOLMessengerPlugin	Pointer to plugin executing method.
	 *
	 */
	virtual BOOL EnableMenuItem(void* pUOLMessengerPlugin, 
			IUOLMessengerContextMenuItemPtr pItem, BOOL bEnable) = 0;
	
	/*
	 * AddSubMenu
	 *
	 * /////////////////////////////////// WARNING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 * 
	 * This method MUST be called from interface's thread (no worker threads allowed).
	 * 
	 * Calling it from a different thread causes undesired behavior on Windows 
	 * created to handle the popup menu.
	 *
	 * A suggested approach is to serialize the creation of the systray menu items 
	 * through windows messages (PostMessage or SendMessage methods).
	 * 
	 * /////////////////////////////////// WARNING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 *
	 * First parameter must be a pointer to the implementation of the plugin executing 
	 * the method (i.e., "CUOLMessengerPlugin*").
	 * Only authorized plugins can execute these method.
	 *
	 * @param pUOLMessengerPlugin	Pointer to plugin executing method.
	 *
	 */
	virtual IUOLMessengerContextMenuPtr AddSubMenu(
			void* pUOLMessengerPlugin, const CString& strLabel) = 0;
	
	/*
	 * RemoveSubMenu
	 *
	 * /////////////////////////////////// WARNING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 * 
	 * This method MUST be called from interface's thread (no worker threads allowed).
	 * 
	 * Calling it from a different thread causes undesired behavior on Windows 
	 * created to handle the popup menu.
	 *
	 * A suggested approach is to serialize the creation of the systray menu items 
	 * through windows messages (PostMessage or SendMessage methods).
	 * 
	 * /////////////////////////////////// WARNING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 *
	 * First parameter must be a pointer to the implementation of the plugin executing 
	 * the method (i.e., "CUOLMessengerPlugin*").
	 * Only authorized plugins can execute these method.
	 *
	 * @param pUOLMessengerPlugin	Pointer to plugin executing method.
	 *
	 */
	virtual void RemoveSubMenu(
			void* pUOLMessengerPlugin, IUOLMessengerContextMenuPtr pSubMenu) = 0;
};


