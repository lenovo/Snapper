/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/
#include <Python.h>

#include <www/engine/engine_api.h>
#include <www/engine/rf_engine_error.h>
#include <www/engine/rf_debug.h>
#include <www/engine/rf_shm_session.h>

#include "extmod_types.h"

/*
 * initialize engine schema/model
 */
static PyObject* connector_init_engine(PyObject* self, PyObject *args)
{

	char *dir = NULL;
    PyObject* py_result;
	int rc = RFRC_SUCCESS;

    if (PyArg_ParseTuple(args, "s", &dir) == 0) 
        return BUILD_RC(RFRC_INVALID_PARAMS);

    if(dir == NULL || strlen(dir) == 0)
        return BUILD_RC(RFRC_INVALID_PARAMS);

    rc = snapper_init_engine(dir);
    if(rc != RFRC_SUCCESS)
    {
        RF_PRINT("failed in connector_init_engine: dir = %s\n", dir);
        return BUILD_RC(RFRC_FAILURE);
    }
    else
        return BUILD_RC(RFRC_SUCCESS);
}

/*
 * process request/response
 * return dict {"response":"respmsg", "http_status":status, "error":rc}
 */
static PyObject* connector_processor(PyObject* self, PyObject *args)
{
    char *uri = NULL, *headers = NULL, *body = NULL;
    int method, httpcode, rc;
    char *json_str = NULL;
    char resphdrs[RESP_HEADERS_LEN]={0};
    PyObject* py_result;

    if (PyArg_ParseTuple(args, "sIss", &uri, &method, &headers, &body) == 0) 
    {
        RF_PRINT_ERR("%s: invalid input", __FUNCTION__);
        return BUILD_RESP("","",500,RFRC_FAILURE);
    }

    if(uri == NULL || strlen(uri) == 0 || headers == NULL || body == NULL)
    {
        RF_PRINT_ERR("%s: invalid params", __FUNCTION__);
        return BUILD_RESP("","",500,RFRC_INVALID_PARAMS);
    }    

    json_str = snapper_request_handle(uri, method, headers, body, &httpcode, &rc, resphdrs);
    if(json_str == NULL)
    {
        RF_PRINT_ERR("failed in connector_processor: uri = %s, method = %d, http = %d, rc = %d\n", uri, method, httpcode, rc);
        py_result = BUILD_RESP("",resphdrs,httpcode,rc);
    }
    else
    {
        if(method == 1)//HEAD has no response body
            py_result = BUILD_RESP("",resphdrs,httpcode,rc);
        else
            py_result = BUILD_RESP(json_str,resphdrs,httpcode,rc);
    }

    if(json_str)
        free(json_str);
    return py_result;
}

/*
 * process request/response
 * return dict {"response":"respmsg", "http_status":status, "error":rc}
 */
static PyObject* connector_processor_schema(PyObject* self, PyObject *args)
{
    char *uri = NULL, *headers = NULL, *body = NULL;
    int method, httpcode, rc;
    char *json_str = NULL;
    char resphdrs[RESP_HEADERS_LEN]={0};
    PyObject* py_result;

    if (PyArg_ParseTuple(args, "sIss", &uri, &method, &headers, &body) == 0) 
    {
        RF_PRINT_ERR("%s: invalid input", __FUNCTION__);
        return BUILD_RESP("","",500,RFRC_FAILURE);
    }

    if(uri == NULL || strlen(uri) == 0 || headers == NULL || body == NULL)
    {
        RF_PRINT_ERR("%s: invalid params", __FUNCTION__);
        return BUILD_RESP("","",500,RFRC_INVALID_PARAMS);
    }    

    json_str = snapper_request_schema_handle(uri, method, headers, body, &httpcode, &rc, resphdrs);
    if(json_str == NULL)
    {
        RF_PRINT_ERR("failed in connector_processor: uri = %s, method = %d, http = %d, rc = %d\n", uri, method, httpcode, rc);
        py_result = BUILD_RESP("",resphdrs,httpcode,rc);
    }
    else
    {
        if(method == 1)//HEAD has no response body
            py_result = BUILD_RESP("",resphdrs,httpcode,rc);
        else
            py_result = BUILD_RESP(json_str,resphdrs,httpcode,rc);
    }

    if(json_str)
        free(json_str);
    return py_result;
}


static PyObject* connector_processor_nonauth(PyObject* self, PyObject *args)
{
    char *uri = NULL, *headers = NULL, *body = NULL;
    int method, httpcode, rc;
    char *json_str = NULL;
    char resphdrs[RESP_HEADERS_LEN]={0};
    PyObject* py_result;
    RF_PRINT_DBG("%s - \n", __FUNCTION__);

    if (PyArg_ParseTuple(args, "sIss", &uri, &method, &headers, &body) == 0) 
    {
        RF_PRINT_ERR("%s: invalid input", __FUNCTION__);
        return BUILD_RESP("","",500,RFRC_FAILURE);
    }

    if(uri == NULL || strlen(uri) == 0 || headers == NULL || body == NULL)
    {
        RF_PRINT_ERR("%s: invalid params", __FUNCTION__);
        return BUILD_RESP("","",500,RFRC_INVALID_PARAMS);
    }
    
    json_str = snapper_request_handle_non_auth(uri, method, headers, body, &httpcode, &rc, resphdrs);
    if(json_str == NULL)
    {
        RF_PRINT_ERR("failed in connector_processor: uri = %s, method = %d, http = %d, rc = %d\n", uri, method, httpcode, rc);
        py_result = BUILD_RESP("",resphdrs,httpcode,rc);
    }
    else
    {
        if(method == 1)//HEAD has no response body
            py_result = BUILD_RESP("",resphdrs,httpcode,rc);
        else
            py_result = BUILD_RESP(json_str,resphdrs,httpcode,rc);
    }

    if(json_str)
        free(json_str);
    return py_result;
}

/*
 * process authentication of SSE request 
 * return 
 */
static PyObject* connector_sse_auth(PyObject* self, PyObject *args)
{
    char *uri = NULL, *auth = NULL, *token = NULL, *remoteip = NULL;
    int method;
    int authtype = 0, authrc;
    char resphdrs[RESP_HEADERS_LEN]={0};
    PyObject* py_result = NULL;

    if (PyArg_ParseTuple(args, "sIsss", &uri, &method, &auth, &token, &remoteip) == 0) 
    {
        RF_PRINT_ERR("%s: invalid input", __FUNCTION__);
        return BUILD_RESP("","",500,RFRC_FAILURE);
    }

    if(uri == NULL || strlen(uri) == 0 || auth == NULL || token == NULL || remoteip == NULL)
    {
        RF_PRINT_ERR("%s: invalid params", __FUNCTION__);
        return BUILD_RESP("","",500,RFRC_INVALID_PARAMS);
    }    

    authrc = authen_handle(method, &authtype, (const char *)uri, auth, token, remoteip);
    if(authtype == 0)
    {
        RF_PRINT_ERR("connector_sse_auth: invalide auth type. uri = %s, method = %d, authtype = %d, auth = %s token = %s from %s\n", uri, method, authtype, auth, token, remoteip);
        return BUILD_RESP("",resphdrs,401,RFRC_AUTH_FAILED);

    }
    if(authrc != RFRC_SUCCESS)
    {
        RF_PRINT_ERR("connector_sse_auth: authentication failed. uri = %s, method = %d, authtype = %d, auth = %s token = %s  from %s\n", uri, method, authtype, auth, token, remoteip);
        return BUILD_RESP("",resphdrs,401,authrc);
    }

    py_result = BUILD_RESP("","",200,RFRC_SUCCESS);
    return py_result;
}

static PyObject* connector_sse_add_dest(PyObject* self, PyObject *args)
{
    char *desturl = NULL, *ctx = NULL, *prot = NULL, *subtype = NULL, *hdrs = NULL, *msgids = NULL, *res = NULL;
    unsigned int types;
    int dest_id = 0;
    PyObject* py_result = NULL;

    if (PyArg_ParseTuple(args, "Isssssss", &types, &desturl, &ctx, &prot, &subtype, &hdrs, &msgids, &res) == 0) 
    {
        RF_PRINT_ERR("%s: invalid input", __FUNCTION__);
        return Py_BuildValue("i", -1);
    }

    if(desturl == NULL || ctx == 0 || prot == NULL || subtype == NULL || hdrs == NULL || msgids == NULL || res == NULL)
    {
        RF_PRINT_ERR("%s: invalid params", __FUNCTION__);
        return Py_BuildValue("i", -1);
    }   
    dest_id = sse_add_destination(types, desturl, ctx, prot, subtype, hdrs, msgids, res);
    return Py_BuildValue("i", dest_id);
}

static PyObject* connector_sse_del_dest(PyObject* self, PyObject *args)
{
    int dest_id = 0;
    PyObject* py_result = NULL;

    if (PyArg_ParseTuple(args, "I", &dest_id) == 0) 
    {
        RF_PRINT_ERR("%s: invalid input", __FUNCTION__);
        return Py_BuildValue("i", RFRC_INVALID_PARAMS);
    }

    sse_del_destination(dest_id);
    return Py_BuildValue("i", RFRC_SUCCESS);
}

static PyObject* connector_sse_query_dest(PyObject* self, PyObject *args)
{
    int dest_id = 0;
    PyObject* py_result = NULL;

    if (PyArg_ParseTuple(args, "I", &dest_id) == 0) 
    {
        RF_PRINT_ERR("%s: invalid input", __FUNCTION__);
        return Py_BuildValue("i", RFRC_INVALID_PARAMS);
    }

    int result = sse_query_destination(dest_id);
    return Py_BuildValue("i", result);
}


static PyObject* scan_shm_session_expires(PyObject* self, PyObject *args)
{
    scan_session_expires();
    return Py_BuildValue("i", RFRC_SUCCESS);
}


static PyObject* scan_shm_session_logoff(PyObject* self, PyObject *args)
{
    scan_session_logoff();
    return Py_BuildValue("i", RFRC_SUCCESS);
}

static PyObject* refresh_topology(PyObject* self, PyObject *args)
{
    snapper_refresh_topology();
    return Py_BuildValue("i", RFRC_SUCCESS);
}

///////////////////////////////////////

static PyMethodDef connector_funcs[] = {
    {"connector_init_engine", (PyCFunction)connector_init_engine, METH_VARARGS, "connector_init_engine(): initialize schema\n"},
    {"connector_processor", (PyCFunction)connector_processor, METH_VARARGS, "connector_processor(): handle request/response of REST API \n"},
    {"connector_processor_schema", (PyCFunction)connector_processor_schema, METH_VARARGS, "connector_processor_schema(): handle request/response of REST API \n"},
    {"connector_processor_nonauth", (PyCFunction)connector_processor_nonauth, METH_VARARGS, "connector_processor(): handle request/response of REST API \n"},
    {"connector_sse_auth", (PyCFunction)connector_sse_auth, METH_VARARGS, "connector_sse_auth(): handle authentication for SSE request \n"},
    {"connector_sse_add_dest", (PyCFunction)connector_sse_add_dest, METH_VARARGS, "connector_sse_add_dest(): add destination SSE connection \n"},
    {"connector_sse_del_dest", (PyCFunction)connector_sse_del_dest, METH_VARARGS, "connector_sse_del_dest(): del destination SSE connection \n"},
    {"connector_sse_query_dest", (PyCFunction)connector_sse_query_dest, METH_VARARGS, "connector_sse_query_dest(): query SSE destination \n"},

    {"scan_shm_session_expires", (PyCFunction)scan_shm_session_expires, METH_VARARGS, "scan_shm_session_expires(): scan expired session\n"},
    {"scan_shm_session_logoff", (PyCFunction)scan_shm_session_logoff, METH_VARARGS, "scan_shm_session_logoff(): scan logoff session\n"},

    {"refresh_topology", (PyCFunction)refresh_topology, METH_VARARGS, "refresh_topology(): refresh topology changes\n"},

    {NULL, NULL, 0, NULL}
};

void init_connector(void)
{
    Py_InitModule("_connector", connector_funcs);
}

