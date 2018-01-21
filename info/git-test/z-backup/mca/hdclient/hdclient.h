#ifndef ORTE_MCA_HDCLIENT_H
#define ORTE_MCA_HDCLIENT_H

#include "orte_config.h"
#include "orte/constants.h"
#include "orte/types.h"

#include "opal/mca/mca.h"
#include "opal/class/opal_list.h"

#include "orte/runtime/orte_globals.h"

BEGIN_C_DECLS


typedef int (*orte_hdclient_base_module_init_fn_t)(void);

typedef int (*orte_hdclient_base_module_finalize_fn_t)(void);

typedef void (*orte_hdclient_base_module_print_fn_t)(char *in);

/**
 * hdclient module
 */
struct orte_hdclient_base_module_2_0_0_t {
    /** init */
    orte_hdclient_base_module_init_fn_t         init;
    /** Finalization function pointer */
    orte_hdclient_base_module_finalize_fn_t     finalize;

    orte_hdclient_base_module_print_fn_t        print;
};
/** Convenience typedef */
typedef struct orte_hdclient_base_module_2_0_0_t orte_hdclient_base_module_2_0_0_t;
/** Convenience typedef */
typedef orte_hdclient_base_module_2_0_0_t orte_hdclient_base_module_t;

//**************
/** Interface for RML communication */
ORTE_DECLSPEC extern orte_hdclient_base_module_t orte_hdclient;




/*
 * hdclient component
 */

/**
 * Component init / selection
 * hdclient component
 */
struct orte_hdclient_base_component_2_0_0_t {
    /** Base MCA structure */
    mca_base_component_t base_version;
    /** Base MCA data */
    mca_base_component_data_t base_data;
};
/** Convenience typedef */
typedef struct orte_hdclient_base_component_2_0_0_t orte_hdclient_base_component_2_0_0_t;
/** Convenience typedef */
typedef orte_hdclient_base_component_2_0_0_t orte_hdclient_base_component_t;


/**
 * Macro for use in components that are of type hdclient
 */
#define ORTE_HDCLIENT_BASE_VERSION_2_0_0 \
  MCA_BASE_VERSION_2_0_0, \
  "hdclient", 2, 0, 0


END_C_DECLS

#endif
