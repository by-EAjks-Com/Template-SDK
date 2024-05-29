# Building, Testing, and Deploying the TemplateSDK Container Image

```powershell
cd /Path/To/Template-SDK
```

## Prerequisites

### GPU Support on Linux

```bash
apt update
apt install --yes nvidia-container-toolkit
nvidia-ctk runtime configure --runtime=containerd && systemctl restart containerd
nvidia-ctk runtime configure --runtime=docker && systemctl restart docker
```

## Building in Interactive Mode

### On a Linux Host

```bash
docker run \
    --interactive \
    --tty \
    --gpus all \
    --name template-sdk \
    --volume '/Path/To/Template-SDK:/src' \
    --workdir /build \
    docker.io/eajkseajks/cpp-cuda:3.0.0-sdk-core-ubuntu-22.04
```

```powershell
docker start --interactive template-sdk
```

### On a Windows Host

```powershell
docker run `
    --interactive `
    --tty `
    --gpus all `
    --name template-sdk `
    --volume '/Path/To/Template-SDK:/src' `
    --workdir /build `
    docker.io/eajkseajks/cpp-cuda:3.0.0-sdk-core-ubuntu-22.04
```

```powershell
docker start --interactive template-sdk
```

### In the Linux Guest

#### Installing the Missing Development Libraries/Tools

```bash
apt-get update

apt-get install --yes --no-install-recommends \
    wget \
    doxygen \
    graphviz \
    libpython3.11-dev \
    python3.11

apt-get autoremove --yes --purge

rm -rf /var/lib/apt/lists/*
```

```bash
mkdir /tools

wget -c https://github.com/Kitware/CMake/releases/download/v3.29.3/cmake-3.29.3-linux-x86_64.tar.gz -O - | tar -xz -C /tools
```

#### Compiling with the Gnu GCC/G++ Compilers

```bash
. /opt/intel/oneapi/setvars.sh

/tools/cmake-3.29.3-linux-x86_64/bin/cmake \
    -G "Unix Makefiles" \
    -D CMAKE_C_COMPILER=gcc \
    -D CMAKE_CXX_COMPILER=g++ \
    -D CMAKE_BUILD_TYPE=Release \
    -D PYBIND11_FINDPYTHON=ON \
    /src/Code

make package
```

#### Compiling with the Intel ICX/ICPX Compilers

```bash
. /opt/intel/oneapi/setvars.sh

/tools/cmake-3.29.3-linux-x86_64/bin/cmake \
    -G "Unix Makefiles" \
    -D CMAKE_C_COMPILER=icx \
    -D CMAKE_CXX_COMPILER=icpx \
    -D CMAKE_BUILD_TYPE=Release \
    -D PYBIND11_FINDPYTHON=ON \
    /src/Code

make package
```

#### Testing

```bash
apt install ./*.deb

export PATH=/opt/by-EAjks.Com/Template-SDK/bin${PATH:+:${PATH}}

Benchmark -vvv
Demonstration -vvv
```

## Building in Batch Mode

```powershell
docker build `
    --build-arg IMAGE_REPOSITORY=docker.io/eajkseajks `
    --build-arg DEVELOPMENT_IMAGE_NAME=cpp-cuda `
    --build-arg DEVELOPMENT_IMAGE_TAG=3.0.0-sdk-core-ubuntu-22.04 `
    --build-arg RUNTIME_IMAGE_NAME=cpp-cuda `
    --build-arg RUNTIME_IMAGE_TAG=3.0.0-runtime-core-ubuntu-22.04 `
    --file DevOps/Docker/TemplateSDK/v1.0.0/Dockerfile `
    --tag docker.io/eajkseajks/templatesdk:v1.0.0 `
    --tag docker.io/eajkseajks/templatesdk:latest `
    .
```
