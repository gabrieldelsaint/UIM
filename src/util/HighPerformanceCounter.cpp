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
#include "highperformancecounter.h"

__int64 HighPerformanceCounter::Frequency;
int HighPerformanceCounter::Initialized = ::QueryPerformanceFrequency( (LARGE_INTEGER *)&Frequency );

HighPerformanceCounter::HighPerformanceCounter(void)
{	
}

HighPerformanceCounter::~HighPerformanceCounter(void)
{

}

BOOL HighPerformanceCounter::Start(void)
{
	if( ! Initialized )
        return FALSE;   // error - couldn't get frequency

      // get the starting counter value
	return QueryPerformanceCounter( (LARGE_INTEGER *)&BeginTime );
}

double HighPerformanceCounter::Stop(void)
{
	if( ! Initialized )
	{
        return 0.0; // error - couldn't get frequency
	}

      // get the ending counter value
	__int64 endtime;
	QueryPerformanceCounter( (LARGE_INTEGER *)&endtime );

	// determine the elapsed counts
	__int64 elapsed = endtime - BeginTime;

	// convert counts to time in seconds and return it
	return (double)elapsed / (double)Frequency;
}

BOOL  HighPerformanceCounter::Available()  
{
	return Initialized; 
}

__int64 HighPerformanceCounter::GetFreq()
{
	return Frequency; 
}


BOOL HighPerformanceCounter::QueryPerformanceCounter(LARGE_INTEGER* lpCounter)
{
	HANDLE hCurThread = ::GetCurrentThread();
	DWORD_PTR dw = ::SetThreadAffinityMask(hCurThread, 1);	

	if (0 == dw)
	{
		::ZeroMemory(lpCounter, sizeof(LARGE_INTEGER));

		return FALSE;
	}
	
	BOOL bRet = ::QueryPerformanceCounter(lpCounter);
	
	::SetThreadAffinityMask(hCurThread, dw);	

	return bRet;
}