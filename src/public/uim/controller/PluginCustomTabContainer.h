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

#include <interfaces/IUOLMessengerPluginCustomTabContainer.h>


class CPluginCustomTabContainerObserver;


class CPluginCustomTabContainer : public IUOLMessengerPluginCustomTabContainer2
{
public:
	CPluginCustomTabContainer();
	virtual ~CPluginCustomTabContainer();

	void RegisterObserver(CPluginCustomTabContainerObserver* pObserver);
	void UnregisterObserver(CPluginCustomTabContainerObserver* pObserver);
	
	void GetTabs(CAtlList<IUOLMessengerPluginCustomTabPtr>& listTabs);

	virtual BOOL AddTab(IUOLMessengerPluginCustomTabPtr pTabBuilder);
	virtual IUOLMessengerPluginCustomTabPtr RemoveTab(const CString& strTabName, const CString& strPluginInternalName);
	virtual IUOLMessengerPluginCustomTabPtr FindTab(const CString& strTabName, const CString& strPluginInternalName);
	virtual void ShowTab(const CString& strTabName, const CString& strPluginInternalName);
	virtual void ShowTab(int nTabIndex);

protected:
	void NotifyObservers(void (CPluginCustomTabContainerObserver::*pfnHandler)(IUOLMessengerPluginCustomTabPtr), IUOLMessengerPluginCustomTabPtr pTabBuilder);
	BOOL MatchTab(const CString& strTabName, const CString& strPluginInternalName, IUOLMessengerPluginCustomTabPtr pTabBuilder);

private:
	IUOLMessengerPluginCustomTabPtr FindTabImpl(const CString& strTabName, const CString& strPluginInternalName);


private:
	CComAutoCriticalSection		m_csTabs;

	CAtlList<CPluginCustomTabContainerObserver*>	m_listObservers;
	CAtlList<IUOLMessengerPluginCustomTabPtr>	m_listTabs;
};

MAKEAUTOPTR(CPluginCustomTabContainer);



class CPluginCustomTabContainerObserver
{
public:
	virtual ~CPluginCustomTabContainerObserver() {}

	virtual void OnAddTab(IUOLMessengerPluginCustomTabPtr pTabBuilder) = 0;
	virtual void OnRemoveTab(IUOLMessengerPluginCustomTabPtr pTabBuilder) = 0;
	virtual void OnShowTab(IUOLMessengerPluginCustomTabPtr pTabBuilder) = 0;
};

