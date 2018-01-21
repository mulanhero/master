rm -rf generated-sources
mkdir generated-sources
cd protos/ && protoc-c --c_out=../generated-sources/ *.proto
