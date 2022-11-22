# Build

```powershell
cd /Path/To/Template SDK
```

## Interactive

```powershell
docker run `
    --interactive `
    --tty `
    --gpus all `
    --name template-sdk `
    --volume '/Path/To/Template SDK/Code:/src' `
    --workdir /build `
    docker.io/eajkseajks/cpp-cuda:v1-ubuntu-22.04-sdk-core-latest
```

```powershell
docker start --interactive template-sdk
```

```bash
apt-get update

apt-get install --yes --no-install-recommends \
    cmake \
    doxygen \
    graphviz \
    libpython3.10-dev \
    python3.10

apt-get autoremove --yes

rm -rf /var/lib/apt/lists/*
```

```bash
cmake \
    -G "Unix Makefiles" \
    -D CMAKE_C_COMPILER=gcc \
    -D CMAKE_CXX_COMPILER=g++ \
    -D CMAKE_BUILD_TYPE=Release \
    -D PYBIND11_FINDPYTHON=ON \
    -D EAJKS_BUILD_FDK=OFF \
    -D EAJKS_BUILD_SDK=ON \
    /src

make package
```

```bash
apt install ./*.deb

export PATH=/opt/by-EAjks.Com/TemplateSDK/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/opt/by-EAjks.Com/TemplateSDK/lib/shared${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}

Benchmark -vvv
Demonstration -vvv
```

## Batch

```powershell
docker build `
    --build-arg IMAGE_REPOSITORY=docker.io/eajkseajks `
    --build-arg DEVELOPMENT_IMAGE_NAME=cpp-cuda `
    --build-arg DEVELOPMENT_IMAGE_TAG=v1-ubuntu-22.04-sdk-core-latest `
    --build-arg RUNTIME_IMAGE_NAME=cpp-cuda `
    --build-arg RUNTIME_IMAGE_TAG=v1-ubuntu-22.04-runtime-core-latest `
    --file DevOps/Docker/Template-SDK/v1.0.0/Dockerfile `
    --tag docker.io/eajkseajks/template-sdk:v1.0.0 `
    --tag docker.io/eajkseajks/template-sdk:latest `
    .
```
