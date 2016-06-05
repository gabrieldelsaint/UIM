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
#include "element.h"

#include "../../controller/utils.h"

class CMenuElement;
class CMenuCommonBase;
class CSubMenuElement;
class CMenuItemElement;

MAKEAUTOPTR(CMenuElement);
MAKEAUTOPTR(CMenuCommonBase);
MAKEAUTOPTR(CSubMenuElement);
MAKEAUTOPTR(CMenuItemElement);


//////////////////////////////////////////////////////////////////////
// CMenuElement
//////////////////////////////////////////////////////////////////////

class CMenuElement : public CElement
{
public:
	DECLARE_ELEMENT_NAME("MENU");

	CMenuElement(void);
	virtual ~CMenuElement(void);

	CMenuHandle GetMenu();
	CMenuItemElement* GetMenuItemElement(int nId);
	CMenuItemElement* FindMenuItemElement(CString strCommand);

protected:
	virtual void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);
	virtual void OnElementBuilt();

private:
	CMenu								m_menu;
	CAtlMap<int, CMenuItemElement*>		m_mapItemElement;    
};


//////////////////////////////////////////////////////////////////////
// CMenuCommonBase
//////////////////////////////////////////////////////////////////////

class CMenuCommonBase : public CElement
{
public:
	CMenuCommonBase();
	virtual ~CMenuCommonBase();
	
	virtual void ProccessMenu(CMenuHandle& menuParent, int& nCommand, int nPosition, CAtlMap<int, CMenuItemElement*>* pMapItemElement);	

	BOOL EnableItem(BOOL bEnable = TRUE);

protected:
	virtual void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);	
	virtual	CString GetName() const;

protected:	
	CString m_strDesc;	
	
	int				m_nMenuPosition;
	CMenuHandle		m_menuHandle;
	CStringGUID		m_strGUIDName;
};
MAKEAUTOPTR(CMenuCommonBase);


//////////////////////////////////////////////////////////////////////
// CSubMenuElement
//////////////////////////////////////////////////////////////////////

class CSubMenuElement : public CMenuCommonBase
{
public:
	DECLARE_ELEMENT_NAME("SubMenu");

	CSubMenuElement();
	virtual ~CSubMenuElement();	

protected:
	virtual void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);
	virtual void ProccessMenu(CMenuHandle& menuParent, int& nCommand, int nPosition, CAtlMap<int, CMenuItemElement*>* pMapItemElement);
};


//////////////////////////////////////////////////////////////////////
// CMenuItemElement
//////////////////////////////////////////////////////////////////////

class CMenuItemElement : public CMenuCommonBase
{
public:
	DECLARE_ELEMENT_NAME("Item");

	CMenuItemElement();
	virtual ~CMenuItemElement();

	CString GetCommand() const;	

protected:
	virtual void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);
	virtual void ProccessMenu(CMenuHandle& menuParent, int& nCommand, int nPosition, CAtlMap<int, CMenuItemElement*>* pMapItemElement);

private:	
	CString m_strCommand;
};

//////////////////////////////////////////////////////////////////////
// CMenuSeparator
//////////////////////////////////////////////////////////////////////

class CMenuSeparator : public CMenuCommonBase
{
public:
	DECLARE_ELEMENT_NAME("MenuSeparator");

	CMenuSeparator();
	virtual ~CMenuSeparator();

protected:	
	void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);
	virtual void ProccessMenu(CMenuHandle& menuParent, int& nCommand, int nPosition, CAtlMap<int, CMenuItemElement*>* pMapItemElement);

private:		
};
