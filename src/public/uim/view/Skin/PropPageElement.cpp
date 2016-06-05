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
#include "PropPageElement.h"

#include "../preferences/AccountsPropPage.h"
#include "../preferences/ContactsPropPage.h"
#include "../preferences/MessagesPropPage.h"
#include "../preferences/StatusPropPage.h"
#include "../preferences/SoundsPropPage.h"
#include "../preferences/GeneralPropPage.h"
#include "../preferences/EmoticonsPropPage.h"
#include "../preferences/NetworkPropPage.h"
#include "../preferences/PluginsPropPage.h"


CElementPtr CAccountsPropPageBuilder::AllocElement()
{
	CAccountsPropPagePtr pWindow = new CAccountsPropPage();

	ATLASSERT(pWindow.get());

	return pWindow;
}

CElementPtr CContactsPropPageBuilder::AllocElement()
{
	CContactsPropPagePtr pWindow = new CContactsPropPage();

	ATLASSERT(pWindow.get());

	return pWindow;
}

CElementPtr CMessagesPropPageBuilder::AllocElement()
{
	CMessagesPropPagePtr pWindow = new CMessagesPropPage();

	ATLASSERT(pWindow.get());

	return pWindow;
}

CElementPtr CStatusPropPageBuilder::AllocElement()
{
	CStatusPropPagePtr pWindow = new CStatusPropPage();

	ATLASSERT(pWindow.get());

	return pWindow;
}

CElementPtr CSoundsPropPageBuilder::AllocElement()
{
	CSoundsPropPagePtr pWindow = new CSoundsPropPage();

	ATLASSERT(pWindow.get());

	return pWindow;
}

CElementPtr CNetworkPropPageBuilder::AllocElement()
{
	CNetworkPropPagePtr pWindow = new CNetworkPropPage();

	ATLASSERT(pWindow.get());

	return pWindow;
}

CElementPtr CEmoticonsPropPageBuilder::AllocElement()
{
	CEmoticonsPropPagePtr pWindow = new CEmoticonsPropPage();

	ATLASSERT(pWindow.get());

	return pWindow;
}

CElementPtr CGeneralPropPageBuilder::AllocElement()
{
	CGeneralPropPagePtr pWindow = new CGeneralPropPage();

	ATLASSERT(pWindow.get());

	return pWindow;
}


CElementPtr CPluginsPropPageBuilder::AllocElement()
{
	CPluginsPropPagePtr pWindow = new CPluginsPropPage();

	ATLASSERT(pWindow.get());

	return pWindow;
}