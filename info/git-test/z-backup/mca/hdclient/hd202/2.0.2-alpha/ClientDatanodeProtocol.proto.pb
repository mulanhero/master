
�

ClientDatanodeProtocol.proto
hdfs.proto"I
#GetReplicaVisibleLengthRequestProto"
block (2.ExtendedBlockProto"6
$GetReplicaVisibleLengthResponseProto
length ("
RefreshNamenodesRequestProto"
RefreshNamenodesResponseProto"?
DeleteBlockPoolRequestProto
	blockPool (	
force ("
DeleteBlockPoolResponseProto"r
!GetBlockLocalPathInfoRequestProto"
block (2.ExtendedBlockProto)
token (2.BlockTokenIdentifierProto"r
"GetBlockLocalPathInfoResponseProto"
block (2.ExtendedBlockProto
	localPath (	

!GetHdfsBlockLocationsRequestProto#
blocks (2.ExtendedBlockProto*
tokens (2.BlockTokenIdentifierProto"N
"GetHdfsBlockLocationsResponseProto
	volumeIds (

ClientDatanodeProtocolServicef
getReplicaVisibleLength$.GetReplicaVisibleLengthRequestProto%.GetReplicaVisibleLengthResponseProtoQ
refreshNamenodes.RefreshNamenodesRequestProto.RefreshNamenodesResponseProtoN
deleteBlockPool.DeleteBlockPoolRequestProto.DeleteBlockPoolResponseProto`
getBlockLocalPathInfo".GetBlockLocalPathInfoRequestProto#.GetBlockLocalPathInfoResponseProto`
getHdfsBlockLocations".GetHdfsBlockLocationsRequestProto#.GetHdfsBlockLocationsResponseProtoBK
%org.apache.hadoop.hdfs.protocol.protoBClientDatanodeProtocolProtos��