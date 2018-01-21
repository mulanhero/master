/*
 * urm_types.h
 *
 *  Created on: Jan 17, 2013
 *      Author: caoj7
 */

#ifndef URM_TYPES_H_
#define URM_TYPES_H_

typedef uint32_t urm_jobid_t;

typedef struct {
  opal_pointer_array_t* request_resources;
  uint32_t minimum_slot_required;
  urm_jobid_t jobid;
} urm_resource_request_t;

typedef struct {
  uint32_t resource_type;
  char* name;
  uint32_t amount;
  char** ext_attribs;
} urm_resource_t;

typedef struct {
  opal_pointer_array_t* urm_resource_array;
  uint32_t slot_id;
  uint32_t priority;

  char* host;
} urm_slot_t;

typedef struct {
  opal_pointer_array_t* slot_responses;
  char* host;
} urm_resource_response_t;

typedef struct {
  urm_jobid_t jobid;
} urm_create_new_job_response_t;

typedef struct {
  urm_jobid_t jobid;
  // TODO: note that this one still undefined, maybe it’s orte_job_t
  //urm_job_description_t* job_desc;
} urm_spawn_request;

typedef struct {
	uint32_t jobid;
} urm_create_new_job_request_t;


#endif /* URM_TYPES_H_ */
