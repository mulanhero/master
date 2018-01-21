#ifndef ORTED_ORTEDSERVICE_CONSTANTS_H_
#define ORTED_ORTEDSERVICE_CONSTANTS_H_

#if HAVE_STDBOOL_H
#  include <stdbool.h>
#else
typedef enum {false, true} bool;
#endif /* !HAVE_STDBOOL_H */

#define OrtedServicePort_Key 	"OrtedGatewayRPCPort"
#define HandShake_MSG  			"orted-001"


#define NotReady 					0
#define Ready						1

#define MsgType_ReadyToRun 			1
#define MsgType_ReportPIDs 			2
#define MsgType_ReportProcExitCode	3
#define MsgType_HeatBeat 			4

#define RT_Succeed 					1
#define RT_Failed  					2

#define HeartBeat_Interval_ms  		100 //0.1s

#endif /* ORTED_ORTEDSERVICE_CONSTANTS_H_ */
