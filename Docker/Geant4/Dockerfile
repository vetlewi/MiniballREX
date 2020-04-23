FROM ubuntu:latest

RUN apt-get update && apt-get -y upgrade && apt-get -y autoremove
RUN apt-get -y install cmake build-essential libexpat1-dev libxerces-c-dev libxmu-dev wget

RUN wget https://root.cern/download/root_v6.20.04.Linux-ubuntu18-x86_64-gcc7.5.tar.gz
RUN tar -xf root_v6.20.04.Linux-ubuntu18-x86_64-gcc7.5.tar.gz -C /opt
RUN rm -f root_v6.20.04.Linux-ubuntu18-x86_64-gcc7.5.tar.gz

ENV ROOTSYS=/opt/root
ENV PATH=$ROOTSYS/bin:$PATH
ENV LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH
ENV DYLD_LIBRARY_PATH=$ROOTSYS/lib:$DYLD_LIBRARY_PATH
ENV CMAKE_PREFIX_PATH=$ROOTSYS/cmake:$CMAKE_PREFIX_PATH
ENV SHLIB_PATH=$ROOTSYS/lib:$SHLIB_PATH
ENV LIBPATH=$ROOTSYS/lib:$LIBPATH


RUN wget http://geant4-data.web.cern.ch/geant4-data/releases/geant4.10.06.p01.tar.gz
RUN tar -xf geant4.10.06.p01.tar.gz -C /opt
RUN rm -f geant4.10.06.p01.tar.gz

RUN mkdir /opt/geant4.10.06.p01/build
WORKDIR /opt/geant4.10.06.p01/build
RUN cmake -DGEANT4_INSTALL_DATA=ON -DGEANT4_BUILD_MULTITHREADED=ON -DGEANT4_INSTALL_EXAMPLES=OFF  ..
RUN make install -j8
WORKDIR /
RUN rm -rf /opt/geant4.10.06.p01

WORKDIR /