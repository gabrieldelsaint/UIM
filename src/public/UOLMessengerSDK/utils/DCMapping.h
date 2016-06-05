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


class CDCMappingTraits
{
public:
	BOOL GetMapMode(int&) {return FALSE;}
	BOOL GetWindowExt(CSize&) {return FALSE;}
	BOOL GetViewportExt(CSize&) {return FALSE;}
	BOOL GetViewportOrg(CPoint&) {return FALSE;}
	BOOL GetWindowOrg(CPoint&) {return FALSE;}
};

template <class TDC, class TDCMappingTraits = CDCMappingTraits>
class CDCMapping
{
public:
	typename typedef TDCMappingTraits Traits;

	CDCMapping(TDC& dc, TDCMappingTraits& traits = TDCMappingTraits()) : 
		m_dc(dc), 
		m_traits(traits)
	{
		int nMap;
		CSize size;
		CPoint pt;

		if (m_traits.GetMapMode(nMap))
		{
			m_nOldMap = m_dc.SetMapMode(nMap);
		}	
		
		if (m_traits.GetWindowExt(size))
		{
			m_dc.SetWindowExt(size, &m_sizeOldWindowExt);
		}

		if (m_traits.GetViewportExt(size))
		{		
			m_dc.SetViewportExt(size, &m_sizeOldViewExt);
		}		

		if (m_traits.GetViewportOrg(pt))
		{		
			m_dc.SetViewportOrg(pt, &m_ptViewPortOrg); 
		}

		if (m_traits.GetWindowOrg(pt))
		{			
			m_dc.SetWindowOrg(pt, &m_ptOldWindowOrg);
		}
	}

	~CDCMapping()
	{
		int nMap;
		CSize size;
		CPoint pt;

		if (m_traits.GetWindowOrg(pt))
		{			
			m_dc.SetWindowOrg(m_ptOldWindowOrg, &m_ptOldWindowOrg);
		}

		if (m_traits.GetViewportOrg(pt))
		{		
			m_dc.SetViewportOrg(m_ptViewPortOrg, &m_ptViewPortOrg);
		}

		if (m_traits.GetViewportExt(size))
		{		
			m_dc.SetViewportExt(m_sizeOldViewExt, &m_sizeOldViewExt);
		}

		if (m_traits.GetWindowExt(size))
		{
			m_dc.SetWindowExt(m_sizeOldWindowExt, &m_sizeOldWindowExt);
		}

		if (m_traits.GetMapMode(nMap))
		{
			m_nOldMap = m_dc.SetMapMode(m_nOldMap);
		}
	}

private:
	TDCMappingTraits& m_traits;
	TDC&	m_dc;

	int		m_nOldMap;
	CSize	m_sizeOldWindowExt;	
	CSize	m_sizeOldViewExt;
	CPoint  m_ptViewPortOrg;
	CPoint  m_ptOldWindowOrg;
};