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


#define _UTIL_VER	0x0100

extern const int UTIL_WTL_VER;

class CUtilVersionVerifier
{
public:
	CUtilVersionVerifier()
	{
#ifdef _WTL_VER

		// A vers�o da WTL que voc� est� usando n�o � a mesma
		// que foi usada para gerar esta biblioteca.
		ATLASSERT(_WTL_VER == UTIL_WTL_VER);
#endif
	}
};

__declspec(selectany) CUtilVersionVerifier g_utilVersionVerifier;


// fun��es de uso geral

CString GetApplicationDir();



#ifdef _DEBUG
	#define ASSERT_THREAD_SAFE_FUNC \
		static DWORD dwAssertThreadSafeFuncMacro_ = ::GetCurrentThreadId();\
		ATLASSERT(dwAssertThreadSafeFuncMacro_ == ::GetCurrentThreadId());


	#ifndef _CRTDBG_MAP_ALLOC
		#define _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>	
	#endif 	//_CRTDBG_MAP_ALLOC
	
	
	#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)		 
	#define DEBUG_CLIENTBLOCK_WITH_PLACEMENT(placement) new(placement)	

#else 
	#define ASSERT_THREAD_SAFE_FUNC

	#define DEBUG_CLIENTBLOCK new
	#define DEBUG_CLIENTBLOCK_WITH_PLACEMENT(placement) new(placement)
#endif // _DEBUG

#ifndef new
	#define new DEBUG_CLIENTBLOCK
#endif

