#ifndef _LIB_OPENAPI_PROXY_H_
#define _LIB_OPENAPI_PROXY_H_

/** Call openapi
 * @arg request JSON string
 * @arg timeout Timeout in seconds
 * @return Response JSON string
 * This function will return NULL when there is an error or timeout
 * The response JSON string is created by malloc() and need to be free()
 */
char* openapi_proxy_call(const char* request,size_t timeout);

#endif /* _LIB_OPENAPI_PROXY_H_ */
