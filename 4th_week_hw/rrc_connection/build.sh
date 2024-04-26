rm -r src/*
rm -r build/*
mkdir src
mkdir build
asn1c lte-rrc-15.6.0.asn1 -D src -pdu=auto -no-gen-OER -fcompound-names -no-gen-example -fno-include-deps
gcc -g -Isrc -I. -o build/client client.cpp RRC*.cpp SendReceive.cpp src/*.c -lsctp -DPDU=auto -DASN_DISABLE_OER_SUPPORT
gcc -g -Isrc -I. -o build/server server.cpp RRC*.cpp SendReceive.cpp src/*.c -lsctp -DPDU=auto -DASN_DISABLE_OER_SUPPORT