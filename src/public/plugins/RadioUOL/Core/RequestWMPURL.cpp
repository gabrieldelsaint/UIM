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
#include "requestwmpurl.h"

#include "util.h"

CRequestWMPURL::CRequestWMPURL(const CString& url,
							   const CString& regex,
								CAtlArray<CString>& SongInfo):
	m_strRegEx(regex),
	CRequest(url),
	m_strWMPURL(""),
	m_vSongInfo(SongInfo)

{
	m_strUrl = url;
}

CRequestWMPURL::~CRequestWMPURL(void)
{
}

BOOL CRequestWMPURL::Process()
{
	///
	// Obter as urls para recuperar as informacoes da musica
	m_vSongInfo.RemoveAll();
	int pos=0;
	int pstart;
	int pend;
	CString strRet = m_strBody;
	pos = pstart = strRet.Find("./display.php?");
	while (pstart>=0) {
		pos = pend = strRet.Find('\"',pos+1);
		CString tmpString = strRet.Mid(pstart, pend-pstart);
		m_vSongInfo.Add(tmpString);
		ATLTRACE("%s %s\n",__FUNCTION__, tmpString);
		pos = pstart = strRet.Find("./display.php?",pos);
	}

	///
	pstart = strRet.Find("<EMBED type=\"application/x-mplayer2");
	pend  = strRet.Find("</EMBED>");

	CString tmpString = strRet.Mid(pstart, pend-pstart);
	ATLASSERT(pend>pstart);
	m_strWMPURL = GetField(tmpString,m_strRegEx);
	m_strWMPURL.Trim();
	ATLASSERT(m_strWMPURL.IsEmpty()==FALSE);
	return 0;
}