#!/bin/bash

IMAGE="ipv4_chat"
CONTAINERNAME="chat1"

NETWORK="net"
SUBNET="172.20.0.0/16"
IP_ADDRESS="172.20.0.112"
PORT="9080"

docker network inspect $NETWORK || docker network create --subnet=$SUBNET $NETWORK

docker run -it --rm \
  --name $CONTAINERNAME \
  --network $NETWORK \
  --ip $IP_ADDRESS \
  -e IP_ADDRESS=$IP_ADDRESS \
  -e PORT=$PORT \
  $IMAGE
