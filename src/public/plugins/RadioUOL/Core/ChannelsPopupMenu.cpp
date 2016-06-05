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
 
#include "StdAfx.h"
#include ".\channelspopupmenu.h"
#include <algorithm>

bool UDgreater ( CChannel * elem1, CChannel *elem2 )
{
	bool ret = (elem1->GetName().CompareNoCase(elem2->GetName())>0);
	return ret;
}


CChannelsPopupMenu::CChannelsPopupMenu( CAtlList<CStyle*>& styles):
	m_styles(styles)
{
	//CAtlList<CStyle*>& m_styles = m_songs.GetStyle();
	m_menuRoot.CreatePopupMenu();

	// Fill popup with styles and channels 
	for (POSITION pos = m_styles.GetHeadPosition(); pos; )
	{
		CStyle* pStyle;
		pStyle = m_styles.GetNext(pos);
//		CAtlList<CChannel*> &channels = pStyle->GetChannel();
		std::vector<CChannel*> &channels = pStyle->GetChannel();

		CMenu *newMenuNode;
		newMenuNode = new CMenu();
		newMenuNode->CreatePopupMenu();
		m_tempMenu.AddTail(newMenuNode);
		int i, max;
		max = (int) channels.size();
		

		//channels.sort();
		//std::random_shuffle(channels.begin(), channels.end()/*, SAscendingChannelOrder()*/);
		std::sort(channels.begin(), channels.end(), UDgreater);
		
		for (i=max-1; i>=0; i-- )
		{
			CChannel* pChannel;
			pChannel =  channels[i];
			int idChannel = atoi(pChannel->GetId());
			newMenuNode->AppendMenu(MF_STRING, idChannel, (LPCTSTR)pChannel->GetName() );
		} 
		m_menuRoot.AppendMenu(MF_POPUP, newMenuNode->m_hMenu, (LPCTSTR) pStyle->GetName());
	}
}

CChannelsPopupMenu::~CChannelsPopupMenu(void)
{
	// Remove all temp channels popup menus 
	for (POSITION pos = m_tempMenu.GetHeadPosition(); pos; )
	{
		CMenu *tmpMenu = m_tempMenu.GetNext(pos);
		delete tmpMenu;
	}
	m_tempMenu.RemoveAll();
}

void CChannelsPopupMenu::Show(HWND hwnd, int x, int y)
{
	// Show Popup
	ATLVERIFY(m_menuRoot.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, x,  y, hwnd)==TRUE);
}