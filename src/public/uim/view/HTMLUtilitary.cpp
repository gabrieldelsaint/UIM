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
#include ".\HTMLUtilitary.h"


#define			TAG_UNESCAPED_DOUBLE_QUOTES				"\""
#define			TAG_ESCAPED_DOUBLE_QUOTES				"\\\'"

#define			TAG_UNESCAPED_SINGLE_QUOTES				"\'"
#define			TAG_ESCAPED_SINGLE_QUOTES				"\\\""

#define			TAG_UNESCAPED_DASH						"#"
#define			TAG_ESCAPED_DASH						"[[dash]]"


CHTMLUtilitary::CHTMLUtilitary(void)
{
}


CHTMLUtilitary::~CHTMLUtilitary(void)
{
}


// Dont consider quoting inside the text that will be inserted into the 
// HTML here.
// Use "ReplaceIncludingQuotes".
CString CHTMLUtilitary::ScapeText(const CString& tagText)
{
	CString scapedTagText(tagText);
	
	// "#" character scaping...
	scapedTagText.Replace(TAG_UNESCAPED_DASH, TAG_ESCAPED_DASH);
	
	return scapedTagText;
}


CString CHTMLUtilitary::UnscapeText(const CString& tagText)
{
	CString unscapedTagText(tagText);
	
	// "#" character unscaping...
	unscapedTagText.Replace(TAG_ESCAPED_DASH, TAG_UNESCAPED_DASH);
	
	// Now we remove the "%20" from the info, if any...
	//
	unscapedTagText.Replace("%20", " ");
	
	return unscapedTagText;
}


BOOL CHTMLUtilitary::Replace(CString &str, const CString& strold, const CString& strnew)
{
	int pos;
	CString strAux;
	pos = str.Find(strold);
	if (pos>=0)
	{
		strAux = str.Left(pos);
		strAux+=strnew;
		strAux+=str.Right(str.GetLength()-pos-strold.GetLength());
		str = strAux;
		return TRUE;
	}
	return FALSE;
}


BOOL CHTMLUtilitary::ReplaceIncludingQuotes(CString &str, const CString& strold, 
		const CString& strnew, const char& charNewQuotes)
{
	int pos;
	CString strAux;
	
	if ( (charNewQuotes != '\"') && (charNewQuotes != '\'') )
	{
		return FALSE;
	}
	
	pos = str.Find(strold);
	if (pos>=0)
	{
		strAux = str.Left(pos - 1); // Get one step back to replace the quotes too.
		strAux += charNewQuotes;
		strAux+=strnew;
		strAux += charNewQuotes;
		strAux+=str.Right(str.GetLength()-pos-strold.GetLength()-1); // Last "-1" for last quote replace
		str = strAux;
		return TRUE;
	}
	return FALSE;
}

