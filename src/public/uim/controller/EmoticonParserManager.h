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

#include "../controller/Settings/SettingsManagerObserverNotifier.h"
#include "ParseEmoticon.h"


class CEmoticonParserManager : public CUOLMessengerSettingsManagerObserver
{
public:
	
	static CEmoticonParserManager* GetInstance(BOOL bCombineCustomEmoticons = TRUE);
	
	virtual ~CEmoticonParserManager();
	
	// Transformar texto com TAGS em um texto com referencias aos arquivos GIF.
	CString ParseHtmlText(const CString& strProtocolId, const CString& strMessage);
	
	// Procura em str alguma string , retorna o tamanho da tag encontrada (lenTag) e a posicao no retorno.
	int FindTAGinString(const CString& strProtocolId, TCHAR* str, int& lenTag, CNodeData* node);
	
	// Utilizada para consultar a tag informado o seu index, (limitacao do uso do COM (Anim)).
	CString Index2Tag(const CString& strProtocolId, int index);
	
	// Informar que precisa carregar novamente os gifs do tema.
	void UpdateTags(const CString& strProtocolId);
	void UpdateTags();
	
	// Carrega os gifs do tema.
	void PrepareTags(const CString& strProtocolId);
	void PrepareTags();
	
	// CUOLMessengerSettingsManagerObserver overridden functions
	virtual void OnEmoticonSettingsChanged();
	
	void UnregisterObserver();
	
protected:
	
	CEmoticonParserManager(BOOL bCombineCustomEmoticons);
	
	void InitializeParsersMap();
	
private:
	
	// TRUE indica que o set "Custom" serah combinado com todos os sets 
	// de protocolos que suportam o tratamento de custom emoticons.
	// FALSE indica que serao criados parsers para todos os sets 
	// individualmente (incluindo o "Custom").
	BOOL m_bCombineCustomEmoticons;
	
	// Indicates whether the parser maps were already initialized.
	BOOL m_bIsInitialized;
	
	typedef CAtlMap<CString, CParse*>	CParsersMap;
	CParsersMap		m_mapParsers;
};

