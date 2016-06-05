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


template <typename T, typename TTraits = CElementTraits< T > > 
class CConstAtlListIterator
{
public:
	CConstAtlListIterator(const CAtlList<T, TTraits>* pAtlList = NULL) :
		m_pAtlList(pAtlList)
	{
		Reset();
	}

	CConstAtlListIterator(const CConstAtlListIterator& ref) 
	{           
		*this = ref;
	}

	const CConstAtlListIterator& operator=(const CConstAtlListIterator& ref) 
	{           
		m_pAtlList = ref.m_pAtlList;
		m_pos = ref.m_pos;

		return *this;
	}

	operator bool () const
	{
        return (m_pos != NULL);
	}

	typename CAtlList<T, TTraits>::INARGTYPE operator* () const
	{
		ATLASSERT(m_pAtlList != NULL);
		return m_pAtlList->GetAt(m_pos);
	}

	typename CConstAtlListIterator& operator++()
	{
		// preincrement
		ATLASSERT(m_pAtlList != NULL);
		m_pAtlList->GetNext(m_pos);

		return (*this);
	}

	typename CConstAtlListIterator operator++(int)
	{
		// postincrement
		ATLASSERT(m_pAtlList != NULL);
        CConstAtlListIterator ret = *this;

		++(*this);

		return ret;
	}

	typename CConstAtlListIterator& operator--()
	{
		// predecrement
		ATLASSERT(m_pAtlList != NULL);
		m_pAtlList->GetPrev(m_pos);

		return (*this);
	}

	typename CConstAtlListIterator operator--(int)
	{
		// postdecrement
		CConstAtlListIterator ret = *this;

		--(*this);

		return ret;
	}

	void Reset()
	{
		if (m_pAtlList != NULL)
		{
			m_pos = m_pAtlList->GetHeadPosition();
		}
		else
		{
			m_pos = NULL;
		}
	}

protected:
	const CAtlList<T, TTraits>*		m_pAtlList;
	POSITION               m_pos;      
};



template <typename T, typename TTraits = CElementTraits< T > > 
class CAtlListIterator : public CConstAtlListIterator<T, TTraits>
{
public:     
	CAtlListIterator(const CAtlList<T, TTraits>& atlList) :
		CConstAtlListIterator<T, TTraits>(&atlList)
	{
		Reset();
	}

	CAtlListIterator(const CAtlListIterator& ref) :
		CConstAtlListIterator<T, TTraits>(ref)
	{           
	}

	typename CAtlList<T, TTraits>::INARGTYPE operator* () const
	{
		return ((CAtlList<T, TTraits>::INARGTYPE) **((CConstAtlListIterator<T, TTraits>*) this));
	}

	typename CAtlListIterator& operator++()
	{
		++(* (CConstAtlListIterator<T, TTraits>*) this);

		return (*this);
	}

	typename CAtlListIterator operator++(int)
	{
		CAtlListIterator ret = *this;

		++(*this);

		return ret;
	}

	typename CAtlListIterator& operator--()
	{
		--(* (CConstAtlListIterator<T, TTraits>*) this);

		return *this;
	}

	typename CAtlListIterator operator--(int)
	{
		CAtlListIterator ret = *this;

		--(*this);

		return ret;
	}
};