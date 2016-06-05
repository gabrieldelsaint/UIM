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
#include "BackgroundElement.h"
#include "../IPainter.h"
#include "../../controller/utils.h"


class CPainterElement : public CElement,
						public IPainter
{
public:
	CPainterElement();
	virtual ~CPainterElement();

protected:
	virtual CString GetName() const = 0;
	virtual void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);

	virtual void Draw(CDCHandle& dc, const CRect& rect);
	virtual int GetTimeout() const;

    CStringGUID	            m_strGUID;

private:
	CBackgroundElementPtr	m_pBackground;
	int						m_nTimeout;    
};



class CGroupDefaultPainterElement : public CPainterElement
{
public:
	virtual ~CGroupDefaultPainterElement() {}

	DECLARE_ELEMENT_NAME("GroupDefaultPainter");

	virtual CString GetName() const
	{
		return "__GroupDefaultPainterInstance_" + m_strGUID;
	}
};


class CGroupSelectionPainterElement : public CPainterElement
{
public:
	virtual ~CGroupSelectionPainterElement() {}

	DECLARE_ELEMENT_NAME("GroupSelectionPainter");

	virtual CString GetName() const
	{
		return "__GroupSelectionPainterInstance_" + m_strGUID;
	}
};


class CContactDefaultPainterElement : public CPainterElement
{
public:
	virtual ~CContactDefaultPainterElement() {}

	DECLARE_ELEMENT_NAME("ContactDefaultPainter");

	virtual CString GetName() const
	{
		return "__ContactDefaultPainterInstance_" + m_strGUID;
	}
};


class CContactSelectionPainterElement : public CPainterElement
{
public:
	virtual ~CContactSelectionPainterElement() {}

	DECLARE_ELEMENT_NAME("ContactSelectionPainter");

	virtual CString GetName() const
	{
		return "__ContactSelectionPainterInstance_" + m_strGUID;
	}
};


class COnlinePainterElement : public CPainterElement
{
public:
	virtual ~COnlinePainterElement() {}

	DECLARE_ELEMENT_NAME("OnlinePainter");

	virtual CString GetName() const
	{
		return "__OnlinePainterInstance_" + m_strGUID;
	}
};



class COfflinePainterElement : public CPainterElement
{
public:
	virtual ~COfflinePainterElement() {}

	DECLARE_ELEMENT_NAME("OfflinePainter");

	virtual CString GetName() const
	{
		return "__OfflinePainterInstance_" + m_strGUID;
	}
};



class CTypingPainterElement : public CPainterElement
{
public:
	virtual ~CTypingPainterElement() {}

	DECLARE_ELEMENT_NAME("TypingPainter");

	virtual CString GetName() const
	{
		return "__TypingPainterInstance_" + m_strGUID;
	}
};



class CNewMessagePainterElement : public CPainterElement
{
public:
	virtual ~CNewMessagePainterElement() {}

	DECLARE_ELEMENT_NAME("NewMessagePainter");

	virtual CString GetName() const
	{
		return "__NewMessagePainterInstance_" + m_strGUID;
	}
};


class CFileTransferDefaultPainterElement : public CPainterElement
{
public:
	virtual ~CFileTransferDefaultPainterElement() {}

	DECLARE_ELEMENT_NAME("FileTransferDefaultPainter");

	virtual CString GetName() const
	{
		return "__FileTransferDefaultPainterInstance_" + m_strGUID;
	}
};


class CFileTransferSelectionPainterElement : public CPainterElement
{
public:
	virtual ~CFileTransferSelectionPainterElement() {}

	DECLARE_ELEMENT_NAME("FileTransferSelectionPainter");

	virtual CString GetName() const
	{
		return "__FileTransferSelectionPainterInstance_" + m_strGUID;
	}
};


class CPluginDefaultPainterElement : public CPainterElement
{
public:
	virtual ~CPluginDefaultPainterElement() {}

	DECLARE_ELEMENT_NAME("PluginDefaultPainter");

	virtual CString GetName() const
	{
		return "__PluginDefaultPainterInstance_" + m_strGUID;
	}
};


class CPluginSelectionPainterElement : public CPainterElement
{
public:
	virtual ~CPluginSelectionPainterElement() {}

	DECLARE_ELEMENT_NAME("PluginSelectionPainter");

	virtual CString GetName() const
	{
		return "__PluginSelectionPainterInstance_" + m_strGUID;
	}
};