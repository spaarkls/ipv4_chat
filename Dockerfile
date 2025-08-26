FROM debian:12

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y gcc g++ make cmake iputils-ping net-tools && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app

RUN make

ENV IP_ADDRESS=0.0.0.0
ENV PORT=9080

CMD ./ipv4_chat $IP_ADDRESS $PORT