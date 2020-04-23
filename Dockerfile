FROM geant4:latest

RUN mkdir miniballREX
COPY * /miniballREX
RUN mkdir /miniballREX/build

WORKDIR /miniballREX/build
RUN cmake ..
RUN make -j30


ENTRYPOINT MiniballTRex