FROM gcc:11.2

RUN apt-get update && apt-get install -y git cmake libsfml-dev libgtest-dev firefox

WORKDIR /build

COPY . ./

RUN cmake -S . -B build  && cmake --build build

CMD ["./build/bin/Chess"]
