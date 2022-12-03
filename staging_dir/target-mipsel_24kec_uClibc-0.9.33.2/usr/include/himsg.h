/*******************************************************************************
  Copyright (C), 2015-2050, GeekGeek Tech. Co., Ltd.
  Description: himsg.h himsg system api
  History   :
    1. 2015-12-18 hnan create

  Others:
*******************************************************************************/ 
#ifndef __HIMSG_H__
#define __HIMSG_H__


#include "himsg_common.h"


typedef struct himsg_msg_s
{
    unsigned int seqnum;  /* Sequence Number */
    char *payload;
    unsigned int payload_len; 
}himsg_msg_t;

typedef void (*himsg_connect_handler)(const void *handle, int name_id);

typedef void (*himsg_event_handler)(const void *handle, const char *event, \
    const himsg_msg_t *himsg);

/* reply_flag: 1 --> have response message, 0 --> none response message  
   name_id: name identification 
 */
typedef void (*himsg_method_handler)(void *handle, const char *method, \
    const himsg_msg_t *himsg, int name_id, const char reply_flag);

/* name_id: name identification 
   ret : error code
 */
typedef void (*himsg_response_handler)(void *handle, int name_id, 
    unsigned int ret, const himsg_msg_t *himsg);

typedef struct himsg_method_s
{
	char *name;
	himsg_method_handler method_handler;
}himsg_method_t;


/*******************************************************************************
  Description: Initialize himsg system.
  Input:  @param name: application name registered to himsgd                
  Output: @param handle      
  Return: himsg_ret_t       
  Others:      
*******************************************************************************/
himsg_ret_t himsg_init(char *name, void **handle);


/*******************************************************************************
  Description: reconnect
  Input:  @param name:               
  Output: @param handle      
  Return: himsg_ret_t       
  Others:      
*******************************************************************************/
himsg_ret_t himsg_reconnect(const void *handle);

/*******************************************************************************
  Description: Clean up himsg system.
  Input:  @param handle
  Output:       
  Return: himsg_ret_t       
  Others:      
*******************************************************************************/
himsg_ret_t himsg_cleanup(void **handle);

/*******************************************************************************
  Description: Set the connect callback. 
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others: In the callback function needs to re-subscribe event 
          The method do not register again
*******************************************************************************/
himsg_ret_t himsg_set_connect_callback(void *handle, 
    himsg_connect_handler connect_handler);

/*******************************************************************************
  Description: Set the disconnect callback. 
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others: 
*******************************************************************************/
himsg_ret_t himsg_set_disconnect_callback(void *handle, 
    himsg_connect_handler disconnect_handler);

/*******************************************************************************
  Description: get application path name registered to himsgd by name_id.
  Input:  @param name_id 
  Output: @param name
  Return: himsg_ret_t       
  Others:      
*******************************************************************************/
himsg_ret_t himsg_get_path_name(const void *handle, int name_id, 
    unsigned int timeout_milli_seconds, char *name, unsigned int name_len);


/*******************************************************************************
  Description: himsg_loop_get_fd
  Input:  @param handle
  Output:       
  Return: fd, error is -1     
  Others:      
*******************************************************************************/
int himsg_loop_get_fd(void *handle);

/*******************************************************************************
  Description: This function in an infinite blocking loop
  Input:  @param timeout_milli_seconds select time
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_loop_forever(void *handle, 
    unsigned int timeout_milli_seconds);

/*******************************************************************************
  Description: exit himsg_loop_forever
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_loop_exit(void *handle);


/*******************************************************************************
  Description: Carry out network read operations.This should only be used if 
               you are not using himsg_loop_forever()
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_loop_read(void *handle);

/*******************************************************************************
  Description: Publish a message on a given event.
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_event_publish(const void *handle, const char *event,
    const himsg_msg_t *msg);

/*******************************************************************************
  Description: Subscribe to a event.
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_event_subscribe(const void *handle, char *event);

/*******************************************************************************
  Description: Unsubscribe from a event.
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_event_unsubscribe(const void *handle, char *event);

/*******************************************************************************
  Description: Set the event callback.
  Input: @param handle
         @event_handler: This is called when a event is received from the broker
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_event_set_callback(const void *handle, 
    himsg_event_handler event_handler);

/*******************************************************************************
  Description: Set the event exec flag, execute /etc/himsg/himsg-call after
               broker received this event,
  Input: @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_event_set_exec(const void *handle, char *event);

/*******************************************************************************
  Description: unset the event exec flag
  Input: @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_event_unset_exec(const void *handle, char *event);


/*******************************************************************************
  Description: Add method
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_method_add(const void *handle, himsg_method_t *method, 
    const unsigned int n_methods);


/*******************************************************************************
  Description: Delete all method
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_method_delete(const void *handle);

/*******************************************************************************
  Description: send a msg with method.
  Input:  @param handle
          @param name : msg recipient name
          @param reply_flag : 1 have response
                        0 no response
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_method_send(const void *handle, const char *name,
    const char *method, const himsg_msg_t *msg, const char reply_flag);


/*******************************************************************************
  Description: send a msg with method.
  Input:  @param handle
          @param name : msg recipient name
          @param reply_flag : 1 have response
                              0 no response
          @param reply_timeout:milliseconds
  Output: @param reply_msg       
  Return: himsg_ret_t    
  Others: the memory of reply_msg and reply_msg->palyload allocated by the 
          function caller     
          input parameters reply_msg->palyload_len indicates the length of reply_msg->payload
          ouput parameters reply_msg->palyload_len indicates the length of real payload
*******************************************************************************/
himsg_ret_t himsg_method_call(const char *name, const char *method, 
    const himsg_msg_t *msg, const char reply_flag, unsigned int reply_timeout,
    himsg_msg_t *reply_msg);
    
/*******************************************************************************
  Description: Send a response message
  Input:  @param name_id: receiver name identification
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_response_send(const void *handle, int name_id, 
    unsigned int ret, const himsg_msg_t *msg);

/*******************************************************************************
  Description: Set response callback
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_response_set_callback(const void *handle, 
    himsg_response_handler response_handler);

/*******************************************************************************
  Description: Unset response callback
  Input:  @param handle
  Output:       
  Return: himsg_ret_t    
  Others:      
*******************************************************************************/
himsg_ret_t himsg_response_unset_callback(const void *handle);

#endif

