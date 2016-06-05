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
#include "CallContactParser.h"

#include "../resource.h"


#define L_ADDR_DELIMITER	_T("<sip:")
#define R_ADDR_DELIMITER	_T(">")
#define CUSTOM_DOMAIN_SEP	_T("+")


CCallContactParser::CCallContactParser()
{
}


CCallContactParser::~CCallContactParser()
{
}


BOOL CCallContactParser::ParseAddress(const CString& strAddress)
{
	int nFindL = -1;
	int nFindR = -1;
	CString strTempExpr;

	m_strUsername.Empty();
	m_strDisplayName.Empty();

	// Parse username...
	nFindL = strAddress.Find(L_ADDR_DELIMITER);
	
	if (nFindL != -1)
	{
		int nLenLDelimiter = ::_tcslen(L_ADDR_DELIMITER);

		nFindR = strAddress.Find(R_ADDR_DELIMITER, nFindL + nLenLDelimiter);

		if (nFindR > nFindL)
		{
			strTempExpr = strAddress.Mid(nFindL + nLenLDelimiter, nFindR - (nFindL + nLenLDelimiter));

			if (FALSE == strTempExpr.IsEmpty())
			{
				int nFindDomainSep = strTempExpr.Find(CUSTOM_DOMAIN_SEP);

				if (-1 == nFindDomainSep)
				{
					int nFindAt = strTempExpr.Find('@');

					if (nFindAt > 0)
					{
						CString strRealm;
						strRealm.LoadString(IDS_UOL_REALM);

						m_strUsername = strTempExpr.Left(nFindAt + 1) + strRealm;
					}
				}
				else
				{
					int nFindAt = strTempExpr.Find('@');

					if (nFindAt > 0)
					{
						m_strUsername = strTempExpr.Left(nFindDomainSep) + '@' + strTempExpr.Mid(nFindDomainSep + 1, nFindAt - nFindDomainSep - 1);
					}
				}
			}
		}
	}

	// Parse display name
	strTempExpr = strAddress.Left(nFindL);
	strTempExpr.Trim();

	if (FALSE == strTempExpr.IsEmpty())
	{
		int nFindQuoteL = strTempExpr.Find('\"');

		if (nFindQuoteL != -1)
		{
			int nFindQuoteR = strTempExpr.Find('\"', nFindQuoteL + 1);

			if (nFindQuoteR > nFindQuoteL)
			{
				m_strDisplayName = strTempExpr.Mid(nFindQuoteL + 1, nFindQuoteR - nFindQuoteL - 1);
			}
		}
		else
		{
			m_strDisplayName = strTempExpr;
		}
	}

	return (FALSE == m_strUsername.IsEmpty()) || (FALSE == m_strDisplayName.IsEmpty());
}


CString CCallContactParser::GetDisplayName() const
{
	return m_strDisplayName;
}


CString CCallContactParser::GetUsername() const
{
	return m_strUsername;
}