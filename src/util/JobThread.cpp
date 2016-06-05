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
#include ".\jobthread.h"

CJobThread::CJobThread(BOOL bThreadRecycle) : 
	m_bThreadRecycle(bThreadRecycle),
	m_bRunning(FALSE)
{
	AddMessageFilter(this);
}

CJobThread::~CJobThread(void)
{
	RemoveMessageFilter(this);

	Stop();
	Wait();
}

BOOL CJobThread::Start()
{
	return m_bRunning = __super::Start();
}

void CJobThread::Stop()
{
	{ CComCritSecLock<CComAutoCriticalSection> lock(m_criticalSection);
	
		m_bRunning = FALSE;	

		__super::Stop();
	}
}	

BOOL CJobThread::AddNewJob(IRunnableJobPtr pRunable)
{	
	BOOL bFirstJob;

	{ CComCritSecLock<CComAutoCriticalSection> lock(m_criticalSection);
		
		bFirstJob = (0 == m_listJobs.GetCount());

		m_listJobs.AddTail(pRunable);	

		if (FALSE == m_bRunning)
		{	
			if (::GetCurrentThreadId() != m_nThreadID)
			{
				Wait();
				Start();			
			}
			else
			{
				ATLASSERT(FALSE);
				return FALSE;			
			}			
		}			

		if (bFirstJob)
		{
			PostThreadMessage(WM_NULL);
		}	
	}

	return TRUE;
}

BOOL CJobThread::PreTranslateMessage(MSG* /*pMsg*/)
{
	IRunnableJobPtr pRunnable;

	{ CComCritSecLock<CComAutoCriticalSection> lock(m_criticalSection);

		if (FALSE == m_bRunning)
		{
			return FALSE;
		}

		if (0 == m_listJobs.GetCount())
		{
			if (FALSE == m_bThreadRecycle)
			{
				Stop();
			}

			return FALSE;
		}

		pRunnable = m_listJobs.RemoveHead();
	}

	pRunnable->RunJob();

	::PostThreadMessage(GetThreadID(), WM_USER, 0, 0);

	return FALSE;	
}
