
ê
JournalProtocol.proto
hdfs.proto"Q
JournalInfoProto
	clusterID (	
layoutVersion (
namespaceID ("‚
JournalRequestProto&
journalInfo (2.JournalInfoProto

firstTxnId (
numTxns (
records (
epoch ("
JournalResponseProto"b
StartLogSegmentRequestProto&
journalInfo (2.JournalInfoProto
txid (
epoch ("
StartLogSegmentResponseProto"^
FenceRequestProto&
journalInfo (2.JournalInfoProto
epoch (

fencerInfo (	"V
FenceResponseProto
previousEpoch (
lastTransactionId (
inSync (2Ò
JournalProtocolService6
journal.JournalRequestProto.JournalResponseProtoN
startLogSegment.StartLogSegmentRequestProto.StartLogSegmentResponseProto0
fence.FenceRequestProto.FenceResponseProtoBD
%org.apache.hadoop.hdfs.protocol.protoBJournalProtocolProtosˆ 