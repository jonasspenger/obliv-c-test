FROM ubuntu:20.04

RUN apt-get update
RUN apt-get install ocaml libc6-dev-i386 libgcrypt20-dev ocaml-findlib opam m4 --yes
RUN opam init --disable-sandboxing --yes \
  && opam switch create 4.06.0 --yes \
  && opam switch 4.06.0 \
  && eval `opam config env` \
  && opam install camlp4 ocamlfind ocamlbuild batteries --yes

WORKDIR /app
COPY ./LICENSE /app
COPY ./src /app/src
COPY ./obliv-c /app/obliv-c

WORKDIR /app/obliv-c
RUN eval `opam config env` \
  && ./configure && make

RUN echo "eval `opam config env`" >> ~/.bashrc

WORKDIR /app

CMD ["/bin/bash"]
