
ÝG
ClientNamenodeProtocol.proto
hdfs.proto"L
GetBlockLocationsRequestProto
src (	
offset (
length ("H
GetBlockLocationsResponseProto&
	locations (2.LocatedBlocksProto"
GetServerDefaultsRequestProto"P
GetServerDefaultsResponseProto.
serverDefaults (2.FsServerDefaultsProto"«
CreateRequestProto
src (	"
masked (2.FsPermissionProto

clientName (	

createFlag (
createParent (
replication (
	blockSize ("
CreateResponseProto"5
AppendRequestProto
src (	

clientName (	"8
AppendResponseProto!
block (2.LocatedBlockProto">
SetReplicationRequestProto
src (	
replication ("-
SetReplicationResponseProto
result ("P
SetPermissionRequestProto
src (	&

permission (2.FsPermissionProto"
SetPermissionResponseProto"H
SetOwnerRequestProto
src (	
username (	
	groupname (	"
SetOwnerResponseProto"W
AbandonBlockRequestProto
b (2.ExtendedBlockProto
src (	
holder (	"
AbandonBlockResponseProto"ˆ
AddBlockRequestProto
src (	

clientName (	%
previous (2.ExtendedBlockProto(
excludeNodes (2.DatanodeInfoProto":
AddBlockResponseProto!
block (2.LocatedBlockProto"Ï
!GetAdditionalDatanodeRequestProto
src (	 
blk (2.ExtendedBlockProto%
	existings (2.DatanodeInfoProto$
excludes (2.DatanodeInfoProto
numAdditionalNodes (

clientName (	"G
"GetAdditionalDatanodeResponseProto!
block (2.LocatedBlockProto"Z
CompleteRequestProto
src (	

clientName (	!
last (2.ExtendedBlockProto"'
CompleteResponseProto
result ("A
ReportBadBlocksRequestProto"
blocks (2.LocatedBlockProto"
ReportBadBlocksResponseProto"/
ConcatRequestProto
trg (	
srcs (	"
ConcatResponseProto".
RenameRequestProto
src (	
dst (	"%
RenameResponseProto
result ("F
Rename2RequestProto
src (	
dst (	
overwriteDest ("
Rename2ResponseProto"4
DeleteRequestProto
src (	
	recursive ("%
DeleteResponseProto
result ("[
MkdirsRequestProto
src (	"
masked (2.FsPermissionProto
createParent ("%
MkdirsResponseProto
result ("O
GetListingRequestProto
src (	

startAfter (
needLocation ("B
GetListingResponseProto'
dirList (2.DirectoryListingProto",
RenewLeaseRequestProto

clientName (	"
RenewLeaseResponseProto";
RecoverLeaseRequestProto
src (	

clientName (	"+
RecoverLeaseResponseProto
result ("
GetFsStatusRequestProto"–
GetFsStatsResponseProto
capacity (
used (
	remaining (
under_replicated (
corrupt_blocks (
missing_blocks ("G
GetDatanodeReportRequestProto&
type (2.DatanodeReportTypeProto"@
GetDatanodeReportResponseProto
di (2.DatanodeInfoProto"5
!GetPreferredBlockSizeRequestProto
filename (	"3
"GetPreferredBlockSizeResponseProto
bsize ("?
SetSafeModeRequestProto$
action (2.SafeModeActionProto"*
SetSafeModeResponseProto
result ("
SaveNamespaceRequestProto"
SaveNamespaceResponseProto"
RollEditsRequestProto"0
RollEditsResponseProto
newSegmentTxId ("/
 RestoreFailedStorageRequestProto
arg (	"3
!RestoreFailedStorageResponseProto
result ("
RefreshNodesRequestProto"
RefreshNodesResponseProto"
FinalizeUpgradeRequestProto"
FinalizeUpgradeResponseProto"A
!ListCorruptFileBlocksRequestProto
path (	
cookie (	"N
"ListCorruptFileBlocksResponseProto(
corrupt (2.CorruptFileBlocksProto"(
MetaSaveRequestProto
filename (	"
MetaSaveResponseProto"&
GetFileInfoRequestProto
src (	"<
GetFileInfoResponseProto 
fs (2.HdfsFileStatusProto"*
GetFileLinkInfoRequestProto
src (	"@
GetFileLinkInfoResponseProto 
fs (2.HdfsFileStatusProto"-
GetContentSummaryRequestProto
path (	"G
GetContentSummaryResponseProto%
summary (2.ContentSummaryProto"T
SetQuotaRequestProto
path (	
namespaceQuota (
diskspaceQuota ("
SetQuotaResponseProto"0
FsyncRequestProto
src (	
client (	"
FsyncResponseProto"A
SetTimesRequestProto
src (	
mtime (
atime ("
SetTimesResponseProto"t
CreateSymlinkRequestProto
target (	
link (	#
dirPerm (2.FsPermissionProto
createParent ("
CreateSymlinkResponseProto")
GetLinkTargetRequestProto
path (	"0
GetLinkTargetResponseProto

targetPath (	"\
"UpdateBlockForPipelineRequestProto"
block (2.ExtendedBlockProto

clientName (	"H
#UpdateBlockForPipelineResponseProto!
block (2.LocatedBlockProto"¢
UpdatePipelineRequestProto

clientName (	%
oldBlock (2.ExtendedBlockProto%
newBlock (2.ExtendedBlockProto"
newNodes (2.DatanodeIDProto"
UpdatePipelineResponseProto"1
GetDelegationTokenRequestProto
renewer (	"L
GetDelegationTokenResponseProto)
token (2.BlockTokenIdentifierProto"M
 RenewDelegationTokenRequestProto)
token (2.BlockTokenIdentifierProto"9
!RenewDelegationTokenResponseProto
newExireTime ("N
!CancelDelegationTokenRequestProto)
token (2.BlockTokenIdentifierProto"$
"CancelDelegationTokenResponseProto"5
 SetBalancerBandwidthRequestProto
	bandwidth ("#
!SetBalancerBandwidthResponseProto""
 GetDataEncryptionKeyRequestProto"W
!GetDataEncryptionKeyResponseProto2
dataEncryptionKey (2.DataEncryptionKeyProto*8
CreateFlagProto

CREATE
	OVERWRITE

APPEND*6
DatanodeReportTypeProto
ALL
LIVE
DEAD*O
SafeModeActionProto
SAFEMODE_LEAVE
SAFEMODE_ENTER
SAFEMODE_GET2Í
ClientNamenodeProtocolT
getBlockLocations.GetBlockLocationsRequestProto.GetBlockLocationsResponseProtoT
getServerDefaults.GetServerDefaultsRequestProto.GetServerDefaultsResponseProto3
create.CreateRequestProto.CreateResponseProto3
append.AppendRequestProto.AppendResponseProtoK
setReplication.SetReplicationRequestProto.SetReplicationResponseProtoH
setPermission.SetPermissionRequestProto.SetPermissionResponseProto9
setOwner.SetOwnerRequestProto.SetOwnerResponseProtoE
abandonBlock.AbandonBlockRequestProto.AbandonBlockResponseProto9
addBlock.AddBlockRequestProto.AddBlockResponseProto`
getAdditionalDatanode".GetAdditionalDatanodeRequestProto#.GetAdditionalDatanodeResponseProto9
complete.CompleteRequestProto.CompleteResponseProtoN
reportBadBlocks.ReportBadBlocksRequestProto.ReportBadBlocksResponseProto3
concat.ConcatRequestProto.ConcatResponseProto3
rename.RenameRequestProto.RenameResponseProto6
rename2.Rename2RequestProto.Rename2ResponseProto3
delete.DeleteRequestProto.DeleteResponseProto3
mkdirs.MkdirsRequestProto.MkdirsResponseProto?

getListing.GetListingRequestProto.GetListingResponseProto?

renewLease.RenewLeaseRequestProto.RenewLeaseResponseProtoE
recoverLease.RecoverLeaseRequestProto.RecoverLeaseResponseProto@

getFsStats.GetFsStatusRequestProto.GetFsStatsResponseProtoT
getDatanodeReport.GetDatanodeReportRequestProto.GetDatanodeReportResponseProto`
getPreferredBlockSize".GetPreferredBlockSizeRequestProto#.GetPreferredBlockSizeResponseProtoB
setSafeMode.SetSafeModeRequestProto.SetSafeModeResponseProtoH
saveNamespace.SaveNamespaceRequestProto.SaveNamespaceResponseProto<
	rollEdits.RollEditsRequestProto.RollEditsResponseProto]
restoreFailedStorage!.RestoreFailedStorageRequestProto".RestoreFailedStorageResponseProtoE
refreshNodes.RefreshNodesRequestProto.RefreshNodesResponseProtoN
finalizeUpgrade.FinalizeUpgradeRequestProto.FinalizeUpgradeResponseProto`
listCorruptFileBlocks".ListCorruptFileBlocksRequestProto#.ListCorruptFileBlocksResponseProto9
metaSave.MetaSaveRequestProto.MetaSaveResponseProtoB
getFileInfo.GetFileInfoRequestProto.GetFileInfoResponseProtoN
getFileLinkInfo.GetFileLinkInfoRequestProto.GetFileLinkInfoResponseProtoT
getContentSummary.GetContentSummaryRequestProto.GetContentSummaryResponseProto9
setQuota.SetQuotaRequestProto.SetQuotaResponseProto0
fsync.FsyncRequestProto.FsyncResponseProto9
setTimes.SetTimesRequestProto.SetTimesResponseProtoH
createSymlink.CreateSymlinkRequestProto.CreateSymlinkResponseProtoH
getLinkTarget.GetLinkTargetRequestProto.GetLinkTargetResponseProtoc
updateBlockForPipeline#.UpdateBlockForPipelineRequestProto$.UpdateBlockForPipelineResponseProtoK
updatePipeline.UpdatePipelineRequestProto.UpdatePipelineResponseProtoW
getDelegationToken.GetDelegationTokenRequestProto .GetDelegationTokenResponseProto]
renewDelegationToken!.RenewDelegationTokenRequestProto".RenewDelegationTokenResponseProto`
cancelDelegationToken".CancelDelegationTokenRequestProto#.CancelDelegationTokenResponseProto]
setBalancerBandwidth!.SetBalancerBandwidthRequestProto".SetBalancerBandwidthResponseProto]
getDataEncryptionKey!.GetDataEncryptionKeyRequestProto".GetDataEncryptionKeyResponseProtoBK
%org.apache.hadoop.hdfs.protocol.protoBClientNamenodeProtocolProtosˆ 