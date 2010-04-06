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

/**@file tsip_ssession.h
 * @brief SIP ssession.
 *
 * @author Mamadou Diop <diopmamadou(at)doubango.org>
 *
 * @date Created: Sat Nov 8 16:54:58 2009 mdiop
 */
#ifndef TSIP_SSESSION_H
#define TSIP_SSESSION_H

#include "tinySIP_config.h"

#include "tsk_object.h"
#include "tsk_list.h"
#include "tsk_params.h"

TSIP_BEGIN_DECLS

//FD
struct tsip_message_s;

#define TSIP_SSESSION_CREATE(stack, ...)		tsk_object_new(tsip_ssession_def_t, stack, __VA_ARGS__)

typedef uint64_t tsip_ssession_id_t;			
#define TSIP_SSESSION_INVALID_ID				0
#define TSIP_SSESSION_INVALID_HANDLE			tsk_null

typedef enum tsip_ssession_param_type_e
{
	sstype_param,
	sstype_header,
	sstype_caps,
	sstype_context,
	sstype_null = 0
}
tsip_ssession_param_type_t;

#define TSIP_SSESSION_SET_PARAM(NAME_STR, VALUE_STR)			sstype_param, (const char*)NAME_STR, (const char*)VALUE_STR
#define TSIP_SSESSION_SET_HEADER(NAME_STR, VALUE_STR)			sstype_header, (const char*)NAME_STR, (const char*)VALUE_STR
#define TSIP_SSESSION_SET_CAPS(NAME_STR, VALUE_STR)				sstype_caps, (const char*)NAME_STR, (const char*)VALUE_STR /* RFC 3840 */
#define TSIP_SSESSION_SET_CONTEXT(CTX_PTR)						sstype_context, (const void*)CTX_PTR
#define TSIP_SSESSION_SET_NULL()								sstype_null

typedef struct tsip_ssession_s
{
	TSK_DECLARE_OBJECT;

	tsip_ssession_id_t id;
	const struct tsip_stack_s* stack;
	const void* context; // usr context
	tsk_params_L_t *params;
	tsk_params_L_t *caps;
	tsk_params_L_t *headers;

	tsk_bool_t owner;
}
tsip_ssession_t;

typedef void tsip_ssession_handle_t;


TINYSIP_API int tsip_ssession_set(tsip_ssession_handle_t *self, ...);
TINYSIP_API tsip_ssession_id_t tsip_ssession_get_id(const tsip_ssession_handle_t *self);
TINYSIP_API int tsip_ssession_take_ownership(tsip_ssession_handle_t *self);
TINYSIP_API tsk_bool_t tsip_ssession_have_ownership(const tsip_ssession_handle_t *self);
TINYSIP_API int tsip_ssession_respond(const tsip_ssession_handle_t *self, short status, const char* phrase, const void* payload, size_t size, const struct tsip_message_s* request, ...);
TINYSIP_API const void* tsip_ssession_get_context(const tsip_ssession_handle_t *self);

tsip_ssession_handle_t *tsip_ssession_create_2(const struct tsip_stack_s* stack, const struct tsip_message_s* message);
//const tsk_param_t* tsip_ssession_get_param(const tsip_ssession_handle_t *self, const char* pname);
//const tsk_param_t* tsip_ssession_get_header(const tsip_ssession_handle_t *self, const char* pname);
//const tsk_params_L_t* tsip_ssession_get_headers(const tsip_ssession_handle_t *self);
//const tsk_params_L_t* tsip_ssession_get_params(const tsip_ssession_handle_t *self);
//const tsk_params_L_t* tsip_ssession_get_caps(const tsip_ssession_handle_t *self);
int tsip_ssession_hangup(const tsip_ssession_t *self, const struct tsip_action_s* action);

typedef tsk_list_t tsip_ssessions_L_t; /**< List of @ref tsip_ssession_handle_t elements. */
TINYSIP_GEXTERN const tsk_object_def_t *tsip_ssession_def_t;

TSIP_END_DECLS

#endif /* TSIP_SSESSION_H */

