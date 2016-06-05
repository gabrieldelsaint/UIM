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

#include "IRunnable.h"
#include <atlsync.h>

class CThread : public IRunnable
{
public:
	CThread(IRunnable* pRunnable = NULL);
	virtual ~CThread(void);

	// Inicia uma nova thread que executar� o m�todo Run() do objeto apontado por m_pRunnable, 
	// se m_pRunnable for igual a NULL, this->Run() ser� executado.
	// Start() falhar� (retornar� FALSE) se a thread j� foi startada ou se ainda est� em execu��o. 
	virtual BOOL Start();
	
	// Aguarda por dwMilliseconds o t�rmino da thread. Retorna FALSE em caso de time-out ou se
	// a thread tentar chamar Wait() em si mesma.
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE) const;

	// Aguarda por dwMilliseconds o t�rmino da thread executando o loop de mensagems do Windows.
	// Retorna FALSE em caso de time-out ou se a thread tentar chamar Wait() em si mesma.
	// Retorna TRUE quando m_thread terminar ou quando a Thread que a chamou receber a messagem WM_QUIT.
	virtual BOOL MessageLoopWait(DWORD dwMilliseconds = INFINITE) const;	

	// Atribui o tamanho da pilha em BYTES da thread que ser� criada pelo m�todo Start()
	void	 SetStackSize(unsigned nStackSize); 

	// Devolve o ID da thread.
	unsigned GetThreadID() const;

	// Devolve o Handle da thread.
	HANDLE   GetThreadHandle() const;	

	// Retorna TRUE caso a thread j� tenha sido startada ou esteja ativa.
	// Retorna FALSE se a thread j� morreu.
	BOOL IsAlive() const;

	// Muda a prioridade desta thread
	BOOL SetThreadPriority(int nPriority);

	// Devolve a prioridade desta thread
	int  GetThreadPriority(int nPriority) const ;

	// Atribui um nome para esta thread.
	void SetName(LPCTSTR szThreadName);

	// Atribui um nome para a thread identificada por dwThreadID.
	static void SetThreadName(LPCSTR szThreadName, DWORD dwThreadID = ::GetCurrentThreadId() );

protected:
	virtual void Run();

private:
	CThread& operator=(const CThread& thread);

	static unsigned  __stdcall ThreadFunc(void* lpParam);

protected:
	HANDLE		m_hThread;
	unsigned	m_nThreadID;	
	unsigned	m_nStackSize;

private:
	IRunnable*	m_pRunnable;
	CString		m_strThreadName;
	CEvent		m_eventThread;
	
};

MAKEAUTOPTR(CThread);
