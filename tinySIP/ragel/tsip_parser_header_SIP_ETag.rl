
/*
* Copyright (C) 2009 Mamadou Diop.
*
* Contact: Mamadou Diop <diopmamadou(at)doubango.org>
*	
* This file is part of Open Source Doubango Framework.
*
* DOUBANGO is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*	
* DOUBANGO is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*	
* You should have received a copy of the GNU General Public License
* along with DOUBANGO.
*
*/

/**@file tsip_header_SIP_ETag.c
 * @brief SIP SIP-ETag header.
 *
 * @author Mamadou Diop <diopmamadou(at)doubango.org>
 *
 * @date Created: Sat Nov 8 16:54:58 2009 mdiop
 */
#include "tinySIP/headers/tsip_header_SIP_ETag.h"

#include "tinySIP/parsers/tsip_parser_uri.h"

#include "tsk_debug.h"
#include "tsk_memory.h"

#include <string.h>

/**@defgroup tsip_header_SIP_ETag_group SIP SIP_ETag header.
*/

/***********************************
*	Ragel state machine.
*/
%%{
	machine tsip_machine_parser_header_SIP_ETag;

	# Includes
	include tsip_machine_utils "./tsip_machine_utils.rl";
	
	action tag
	{
		tag_start = p;
	}

	action parse_etag
	{
		TSK_PARSER_SET_STRING(hdr_etag->value);
	}

	action eob
	{
	}
	
	SIP_ETag = "SIP-ETag"i HCOLON token>tag %parse_etag;
	
	# Entry point
	main := SIP_ETag :>CRLF @eob;

}%%

int tsip_header_SIP_ETag_tostring(const void* header, tsk_buffer_t* output)
{
	if(header)
	{
		const tsip_header_SIP_ETag_t *SIP_ETag = header;
		if(SIP_ETag->value){
			tsk_buffer_append(output, SIP_ETag->value, strlen(SIP_ETag->value));
		}
		return 0;
	}

	return -1;
}

tsip_header_SIP_ETag_t *tsip_header_SIP_ETag_parse(const char *data, size_t size)
{
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	tsip_header_SIP_ETag_t *hdr_etag = TSIP_HEADER_SIP_ETAG_CREATE_NULL();
	
	const char *tag_start;

	%%write data;
	%%write init;
	%%write exec;
	
	if( cs < %%{ write first_final; }%% )
	{
		TSK_OBJECT_SAFE_FREE(hdr_etag);
	}
	
	return hdr_etag;
}







//========================================================
//	SIP_ETag header object definition
//

static void* tsip_header_SIP_ETag_create(void *self, va_list * app)
{
	tsip_header_SIP_ETag_t *SIP_ETag = self;
	if(SIP_ETag)
	{
		TSIP_HEADER(SIP_ETag)->type = tsip_htype_SIP_ETag;
		TSIP_HEADER(SIP_ETag)->tostring = tsip_header_SIP_ETag_tostring;
		SIP_ETag->value = tsk_strdup(va_arg(*app, const char*));
	}
	else
	{
		TSK_DEBUG_ERROR("Failed to create new SIP_ETag header.");
	}
	return self;
}

static void* tsip_header_SIP_ETag_destroy(void *self)
{
	tsip_header_SIP_ETag_t *SIP_ETag = self;
	if(SIP_ETag)
	{
		TSK_FREE(SIP_ETag->value);
		TSK_OBJECT_SAFE_FREE(TSIP_HEADER_PARAMS(SIP_ETag));
	}
	else TSK_DEBUG_ERROR("Null SIP_ETag header.");

	return self;
}

static const tsk_object_def_t tsip_header_SIP_ETag_def_s = 
{
	sizeof(tsip_header_SIP_ETag_t),
	tsip_header_SIP_ETag_create,
	tsip_header_SIP_ETag_destroy,
	0
};
const void *tsip_header_SIP_ETag_def_t = &tsip_header_SIP_ETag_def_s;
