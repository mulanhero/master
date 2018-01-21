
ª
NamenodeProtocol.proto
hdfs.proto"I
GetBlocksRequestProto"
datanode (2.DatanodeIDProto
size ("C
GetBlocksResponseProto)
blocks (2.BlocksWithLocationsProto"
GetBlockKeysRequestProto"B
GetBlockKeysResponseProto%
keys (2.ExportedBlockKeysProto"
GetTransactionIdRequestProto"-
GetTransactionIdResponseProto
txId ("
RollEditLogRequestProto"H
RollEditLogResponseProto,
	signature (2.CheckpointSignatureProto")
'GetMostRecentCheckpointTxIdRequestProto"8
(GetMostRecentCheckpointTxIdResponseProto
txId ("k
ErrorReportRequestProto0
registration (2.NamenodeRegistrationProto
	errorCode (
msg (	"
ErrorReportResponseProto"H
RegisterRequestProto0
registration (2.NamenodeRegistrationProto"I
RegisterResponseProto0
registration (2.NamenodeRegistrationProto"O
StartCheckpointRequestProto0
registration (2.NamenodeRegistrationProto"F
StartCheckpointResponseProto&
command (2.NamenodeCommandProto"{
EndCheckpointRequestProto0
registration (2.NamenodeRegistrationProto,
	signature (2.CheckpointSignatureProto"
EndCheckpointResponseProto"3
GetEditLogManifestRequestProto
	sinceTxId ("P
GetEditLogManifestResponseProto-
manifest (2.RemoteEditLogManifestProto2Ú
NamenodeProtocolService<
	getBlocks.GetBlocksRequestProto.GetBlocksResponseProtoE
getBlockKeys.GetBlockKeysRequestProto.GetBlockKeysResponseProtoQ
getTransactionId.GetTransactionIdRequestProto.GetTransactionIdResponseProtor
getMostRecentCheckpointTxId(.GetMostRecentCheckpointTxIdRequestProto).GetMostRecentCheckpointTxIdResponseProtoB
rollEditLog.RollEditLogRequestProto.RollEditLogResponseProto=
versionRequest.VersionRequestProto.VersionResponseProtoB
errorReport.ErrorReportRequestProto.ErrorReportResponseProto9
register.RegisterRequestProto.RegisterResponseProtoN
startCheckpoint.StartCheckpointRequestProto.StartCheckpointResponseProtoH
endCheckpoint.EndCheckpointRequestProto.EndCheckpointResponseProtoW
getEditLogManifest.GetEditLogManifestRequestProto .GetEditLogManifestResponseProtoBE
%org.apache.hadoop.hdfs.protocol.protoBNamenodeProtocolProtosˆ 