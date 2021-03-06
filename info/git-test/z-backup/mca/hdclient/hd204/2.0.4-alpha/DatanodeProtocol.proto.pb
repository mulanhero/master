
�&
DatanodeProtocol.protohadoop.hdfs
hdfs.proto"�
DatanodeRegistrationProto0

datanodeID (2.hadoop.hdfs.DatanodeIDProto2
storageInfo (2.hadoop.hdfs.StorageInfoProto1
keys (2#.hadoop.hdfs.ExportedBlockKeysProto
softwareVersion (	"�
DatanodeStorageProto
	storageID (	E
state (2..hadoop.hdfs.DatanodeStorageProto.StorageState:NORMAL")
StorageState

NORMAL 
	READ_ONLY"�
DatanodeCommandProto7
cmdType (2&.hadoop.hdfs.DatanodeCommandProto.Type?
balancerCmd (2*.hadoop.hdfs.BalancerBandwidthCommandProto.
blkCmd (2.hadoop.hdfs.BlockCommandProto;
recoveryCmd (2&.hadoop.hdfs.BlockRecoveryCommandProto6
finalizeCmd (2!.hadoop.hdfs.FinalizeCommandProto8
keyUpdateCmd (2".hadoop.hdfs.KeyUpdateCommandProto6
registerCmd (2!.hadoop.hdfs.RegisterCommandProto"�
Type
BalancerBandwidthCommand 
BlockCommand
BlockRecoveryCommand
FinalizeCommand
KeyUpdateCommand
RegisterCommand
UnusedUpgradeCommand
NullDatanodeCommand"2
BalancerBandwidthCommandProto
	bandwidth ("�
BlockCommandProto5
action (2%.hadoop.hdfs.BlockCommandProto.Action
blockPoolId (	'
blocks (2.hadoop.hdfs.BlockProto0
targets (2.hadoop.hdfs.DatanodeInfosProto"4
Action
TRANSFER

INVALIDATE
SHUTDOWN"N
BlockRecoveryCommandProto1
blocks (2!.hadoop.hdfs.RecoveringBlockProto"+
FinalizeCommandProto
blockPoolId (	"J
KeyUpdateCommandProto1
keys (2#.hadoop.hdfs.ExportedBlockKeysProto"
RegisterCommandProto"\
RegisterDatanodeRequestProto<
registration (2&.hadoop.hdfs.DatanodeRegistrationProto"]
RegisterDatanodeResponseProto<
registration (2&.hadoop.hdfs.DatanodeRegistrationProto"�
HeartbeatRequestProto<
registration (2&.hadoop.hdfs.DatanodeRegistrationProto0
reports (2.hadoop.hdfs.StorageReportProto
xmitsInProgress (:0
xceiverCount (:0
failedVolumes (:0"�
StorageReportProto
	storageID (	
failed (:false
capacity (:0
dfsUsed (:0
	remaining (:0
blockPoolUsed (:0"�
NNHAStatusHeartbeatProto:
state (2+.hadoop.hdfs.NNHAStatusHeartbeatProto.State
txid (" 
State

ACTIVE 
STANDBY"�
HeartbeatResponseProto/
cmds (2!.hadoop.hdfs.DatanodeCommandProto7
haStatus (2%.hadoop.hdfs.NNHAStatusHeartbeatProto"�
BlockReportRequestProto<
registration (2&.hadoop.hdfs.DatanodeRegistrationProto
blockPoolId (	5
reports (2$.hadoop.hdfs.StorageBlockReportProto"a
StorageBlockReportProto2
storage (2!.hadoop.hdfs.DatanodeStorageProto
blocks (B"J
BlockReportResponseProto.
cmd (2!.hadoop.hdfs.DatanodeCommandProto"�
ReceivedDeletedBlockInfoProto&
block (2.hadoop.hdfs.BlockProtoF
status (26.hadoop.hdfs.ReceivedDeletedBlockInfoProto.BlockStatus

deleteHint (	"7
BlockStatus
	RECEIVING
RECEIVED
DELETED"r
!StorageReceivedDeletedBlocksProto
	storageID (	:
blocks (2*.hadoop.hdfs.ReceivedDeletedBlockInfoProto"�
#BlockReceivedAndDeletedRequestProto<
registration (2&.hadoop.hdfs.DatanodeRegistrationProto
blockPoolId (	>
blocks (2..hadoop.hdfs.StorageReceivedDeletedBlocksProto"&
$BlockReceivedAndDeletedResponseProto"�
ErrorReportRequestProto<
registartion (2&.hadoop.hdfs.DatanodeRegistrationProto
	errorCode (
msg (	"P
	ErrorCode

NOTIFY 

DISK_ERROR
INVALID_BLOCK
FATAL_DISK_ERROR"
ErrorReportResponseProto"M
ReportBadBlocksRequestProto.
blocks (2.hadoop.hdfs.LocatedBlockProto"
ReportBadBlocksResponseProto"�
&CommitBlockSynchronizationRequestProto.
block (2.hadoop.hdfs.ExtendedBlockProto
newGenStamp (
	newLength (
	closeFile (
deleteBlock (1
newTaragets (2.hadoop.hdfs.DatanodeIDProto
newTargetStorages (	")
'CommitBlockSynchronizationResponseProto2�
DatanodeProtocolServicei
registerDatanode).hadoop.hdfs.RegisterDatanodeRequestProto*.hadoop.hdfs.RegisterDatanodeResponseProtoX
sendHeartbeat".hadoop.hdfs.HeartbeatRequestProto#.hadoop.hdfs.HeartbeatResponseProtoZ
blockReport$.hadoop.hdfs.BlockReportRequestProto%.hadoop.hdfs.BlockReportResponseProto~
blockReceivedAndDeleted0.hadoop.hdfs.BlockReceivedAndDeletedRequestProto1.hadoop.hdfs.BlockReceivedAndDeletedResponseProtoZ
errorReport$.hadoop.hdfs.ErrorReportRequestProto%.hadoop.hdfs.ErrorReportResponseProtoU
versionRequest .hadoop.hdfs.VersionRequestProto!.hadoop.hdfs.VersionResponseProtof
reportBadBlocks(.hadoop.hdfs.ReportBadBlocksRequestProto).hadoop.hdfs.ReportBadBlocksResponseProto�
commitBlockSynchronization3.hadoop.hdfs.CommitBlockSynchronizationRequestProto4.hadoop.hdfs.CommitBlockSynchronizationResponseProtoBE
%org.apache.hadoop.hdfs.protocol.protoBDatanodeProtocolProtos��