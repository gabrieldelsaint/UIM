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

#include "Element.h"
#include "ElementBuilder.h"
#include "COLORREF.h"
#include "../image/image.h"
#include "../image/imagebuilder.h"

class CPreferencesPropPageBuilder : public CElementBuilder
{
};

MAKEAUTOPTR(CPreferencesPropPageBuilder);

class CAccountsPropPageBuilder : public CPreferencesPropPageBuilder
{
public:
	virtual ~CAccountsPropPageBuilder() {}

	DECLARE_ELEMENT_NAME("AccountPropPage");
	virtual CElementPtr AllocElement();

	virtual CString GetName() const
	{
		return "__AccountsPropPageBuilderInstance";
	}
};


class CContactsPropPageBuilder : public CPreferencesPropPageBuilder
{
public:
	virtual ~CContactsPropPageBuilder() {}

	DECLARE_ELEMENT_NAME("ContactPropPage");
	virtual CElementPtr AllocElement();

	virtual CString GetName() const
	{
		return "__ContactsPropPageBuilderInstance";
	}
};

class CMessagesPropPageBuilder : public CPreferencesPropPageBuilder
{
public:
	virtual ~CMessagesPropPageBuilder() {}

	DECLARE_ELEMENT_NAME("MessagePropPage");
	virtual CElementPtr AllocElement();

	virtual CString GetName() const
	{
		return "__MessagesPropPageBuilderInstance";
	}
};

class CStatusPropPageBuilder : public CPreferencesPropPageBuilder
{
public:
	virtual ~CStatusPropPageBuilder() {}

	DECLARE_ELEMENT_NAME("StatusPropPage");
	virtual CElementPtr AllocElement();

	virtual CString GetName() const
	{
		return "__StatusPropPageBuilderInstance";
	}
};

class CSoundsPropPageBuilder : public CPreferencesPropPageBuilder
{
public:
	virtual ~CSoundsPropPageBuilder() {}

	DECLARE_ELEMENT_NAME("SoundPropPage");
	virtual CElementPtr AllocElement();

	virtual CString GetName() const
	{
		return "__SoundsPropPageBuilderInstance";
	}
};

class CEmoticonsPropPageBuilder : public CPreferencesPropPageBuilder
{
public:
	virtual ~CEmoticonsPropPageBuilder() {}

	DECLARE_ELEMENT_NAME("EmoticonPropPage");
	virtual CElementPtr AllocElement();

	virtual CString GetName() const
	{
		return "__EmoticonsPropPageBuilderInstance";
	}
};

class CNetworkPropPageBuilder : public CPreferencesPropPageBuilder
{
public:
	virtual ~CNetworkPropPageBuilder() {}

	DECLARE_ELEMENT_NAME("NetworkPropPage");
	virtual CElementPtr AllocElement();

	virtual CString GetName() const
	{
		return "__GroupNetworkPropPageBuilderInstance";
	}
};

class CGeneralPropPageBuilder : public CPreferencesPropPageBuilder
{
public:
	virtual ~CGeneralPropPageBuilder() {}

	DECLARE_ELEMENT_NAME("GeneralpropPage");
	virtual CElementPtr AllocElement();

	virtual CString GetName() const
	{
		return "__GeneralproppageBuilderInstance";
	}
};

class CPluginsPropPageBuilder : public CPreferencesPropPageBuilder
{
public:
	virtual ~CPluginsPropPageBuilder() {}

	DECLARE_ELEMENT_NAME("PluginsPropPage");
	virtual CElementPtr AllocElement();

	virtual CString GetName() const
	{
		return "__PluginsPropPageBuilderInstance";
	}
};


MAKEAUTOPTR(CAccountsPropPageBuilder);
MAKEAUTOPTR(CContactsPropPageBuilder);
MAKEAUTOPTR(CMessagesPropPageBuilder);
MAKEAUTOPTR(CStatusPropPageBuilder);
MAKEAUTOPTR(CSoundsPropPageBuilder);
MAKEAUTOPTR(CEmoticonsPropPageBuilder);
MAKEAUTOPTR(CNetworkPropPageBuilder);
MAKEAUTOPTR(CGeneralPropPageBuilder);
MAKEAUTOPTR(CPluginsPropPageBuilder);