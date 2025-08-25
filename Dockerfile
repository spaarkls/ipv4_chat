FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y g++ make cmake iputils-ping net-tools && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app

RUN make

ENTRYPOINT ["./ipv4_chat"]
CMD ["192.168.100.255", "9080"]
